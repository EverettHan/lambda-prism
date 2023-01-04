layout (location = 0) out vec4 fragColor;

#define INV_GOLDEN_RATIO 0.6180339887

#define USE_GOLDEN_RATIO_LDS

// Last value only makes sense in progressive mode
#if defined(SO_CONVOLUTION_MULTI_PASS_PROGRESSIVE)
  #if defined(SO_CUBE_MAP_LAYER)
    #define S_CURRENT_ENV_MAP s_CurrentEnvMapCubeArray
  #else
    #define S_CURRENT_ENV_MAP s_CurrentEnvMapCube
  #endif
#endif

float VanDerCorput(uint iIndex)
{
  iIndex = (iIndex << 16u) | (iIndex >> 16u);
  iIndex = ((iIndex & 0x55555555u) << 1u) | ((iIndex & 0xAAAAAAAAu) >> 1u);
  iIndex = ((iIndex & 0x33333333u) << 2u) | ((iIndex & 0xCCCCCCCCu) >> 2u);
  iIndex = ((iIndex & 0x0F0F0F0Fu) << 4u) | ((iIndex & 0xF0F0F0F0u) >> 4u);
  iIndex = ((iIndex & 0x00FF00FFu) << 8u) | ((iIndex & 0xFF00FF00u) >> 8u);

  return float(iIndex) * 2.3283064365386963e-10;
}

vec2 LowDiscrepencySample(uint i, uint N)
{
  const float x = (float(i) + 0.5) / float(N);
#ifdef USE_GOLDEN_RATIO_LDS
  const float y = fract(float(i) * INV_GOLDEN_RATIO);
#else
  const float y = VanDerCorput(i);
#endif
  return vec2(x, y);
}

vec4 SampleMap(sampler2DArray iTexture, vec3 iRay, float iLevel)
{
  const vec3 coords = ComputeDualParaboloidFromDirection(iRay);
  return textureLod(iTexture, coords, iLevel);
}

vec4 SampleMap(sampler2D iTexture, vec3 iRay, float iLevel)
{
  const vec2 coords = ComputeTexCoordFromDirection(iRay);
  return textureLod(iTexture, coords, iLevel);
}

vec4 SampleMap(samplerCube iTexture, vec3 iRay, float iLevel)
{
  return textureLod(iTexture, iRay, iLevel);
}

vec3 GetSample(in vec3 iRay, in float iLevel)
{
  vec3 value = vec3(1.0, 0.0, 1.0);

  #if defined(SO_CONVOLUTION_DUAL_PARABOLOID_INPUT)
    value = SampleMap(s_EnvMapArray, iRay, iLevel).rgb;
  #elif defined(SO_CONVOLUTION_LATLONG_INPUT)
    value = SampleMap(s_EnvMap, iRay, iLevel).rgb;
  #else
    value = SampleMap(s_EnvMapCube, iRay, iLevel).rgb;
  #endif

  return value;
}

uint ComputeIndex(in uint i)
{
  const uint n = (i*cb_PrefilterEnvMap.u_SampleStride) / cb_PrefilterEnvMap.u_TotalSamples;
  const uint m = (i*cb_PrefilterEnvMap.u_SampleStride) % cb_PrefilterEnvMap.u_TotalSamples;
  return m+n;
}

vec4 PrefilterEnvMap(float iRoughness, vec3 iNormal)
{
  // Invert mip storage for EVisuPBR's sheen
  #if defined(EVisuPBR) && defined(Fur)
    iRoughness = 1.0 - iRoughness;
  #endif

  vec4 value = vec4(0.0);
  const vec3 clampValue = vec3(cb_PrefilterEnvMap.u_ClampValue);

  const uint start = cb_PrefilterEnvMap.u_SampleStart;
  const uint end = cb_PrefilterEnvMap.u_SampleEnd;

  for (uint i=start; i<end; i++) {
    const uint ind = ComputeIndex(i);
    const vec2 Xi = LowDiscrepencySample(ind, cb_PrefilterEnvMap.u_TotalSamples);
    const vec4 H_pdf = GetSampleVectorPDF(Xi[0], Xi[1], iRoughness, iNormal);
    const vec3 L = ComputeLightVector(iNormal, H_pdf.xyz);
    const float NoL = vMax(0.0, vDot(iNormal, L));

    if (NoL > 0.0) {
      const float NoH = vMax(0.0, vDot(iNormal, H_pdf.xyz));
      const float LoH = vMax(0.0, vDot(L, H_pdf.xyz));
      #ifndef GGX
        const float pdf = H_pdf.w;
      #else
        const float pdf = GetPDF_GGX(NoH, iRoughness);
      #endif
      const float mipLevel = GetMipLevel(NoH, LoH, NoL, iRoughness, pdf);
      const vec3 texSample = GetSample(L, mipLevel);
      value.rgb += GetWeight(NoL) * vMin(texSample, clampValue);
      value.w += GetWeight(NoL);
    }
  }

  return value;
}

vec3 ComputeNormalDirection()
{
  #ifdef SO_CONVOLUTION_USE_GEOMETRY_STAGE
    const int face = gl_Layer%6;
  #else
    const int face = cb_PrefilterEnvMap.u_Face;
  #endif
  return ComputeDirectionFromCube(face, TEXCOORD);
}

vec4 GetLastValue(in vec3 iRay)
{
// Last value only makes sense in progressive mode
#if defined(SO_CONVOLUTION_MULTI_PASS_PROGRESSIVE)
  #if defined(SO_CUBE_MAP_LAYER)
    vec4 coords = vec4(iRay, float(SO_CUBE_MAP_LAYER));
  #else
    vec3 coords = iRay;
  #endif

  return textureLod(S_CURRENT_ENV_MAP, coords, cb_PrefilterEnvMap.u_Mip);
#else
  return vec4(0.0);
#endif
}

vec4 ComputeFragColor(in vec4 iValue, in vec4 iLastValue)
{
  vec4 result = vec4(1.0, 0.0, 1.0, 1.0);

/*
** 1. SO_CONVOLUTION_MULTI_PASS
** This is simple multi-pass, with no partial result display
** Accumulation is done through the blend state and resolve is done in separate pass
** when all samples have been computed
*/
#ifdef SO_CONVOLUTION_MULTI_PASS
  result = iValue;

/*
** 2. SO_CONVOLUTION_MULTI_PASS_PROGRESSIVE
** This is multi-pass with display of partial results
** Accumulation and resolve are done right here
*/
#elif defined(SO_CONVOLUTION_MULTI_PASS_PROGRESSIVE)

  //Cancel the last resolve operation
  vec3 lastColor  = iLastValue.xyz * iLastValue.w;

  //Add the new samples
  vec3 color  = iValue.xyz + lastColor;

  //Compute new weight
  float weight = iValue.w + iLastValue.w;

  //Resolve and output with the new weight
  result = vec4(color/max(weight, 1e-3), max(weight, 1e-3));

/*
** 3. Otherwise: plain old single pass
** All samples have been computed already, so we just need to resolve
*/
#else
  result = vec4(iValue.xyz/iValue.w, 1.0);
#endif

  return result;
}

void main()
{
  const vec3 ray = ComputeNormalDirection();
  const vec4 lastValue = GetLastValue(ray);
  const vec4 value = PrefilterEnvMap(cb_PrefilterEnvMap.u_Roughness, ray);
  fragColor = ComputeFragColor(value, lastValue);
}
