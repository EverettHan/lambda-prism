#ifdef Lighting

#define LIGHT_TYPE_POINT        0
#define LIGHT_TYPE_SPOT         1
#define LIGHT_TYPE_DIRECTIONAL  2
#define LIGHT_TYPE_PROFILE      3
#define LIGHT_TYPE_AREA         4
#define LIGHT_TYPE_IBL          5

// For now, DoStdLighting implementation for mobile platforms is separate until a convenient optimization is found
#if !defined(GLESPlatform) && (GLSLVersion >= 400)

LightingResult DoStdLighting(inout LightingData iData, in BRDFParameters iParameters)
{
  int i;
  LightingResult res;
  res.radiance = vec3(0.);

  #ifdef SO_EVISUPBR_SUBSURFACE
    res.translucency = vec3(0.0);
  #endif

  int shadowLayer  = 0;
  int lightIndex   = 0;
  iData.visibility = 1.0;

  // --------------------------------------------------------------------------
  #ifdef NumberOfPointLights
    #ifdef PDSFX_ENABLE_CUSTOM_BRDF_LAYER
      iData.lightType = LIGHT_TYPE_POINT;
    #endif

    for(i = 0; i < vMin(NumberOfPointLights, _V_MAX_LIGHTS); ++i)
    {
    #ifdef LightChannels
      if ((cb_cbVolMaterial.u_LightChannels & cb_LightChannels.PointChannels[i]) == 0)
        continue;
    #endif

    #ifdef UsePassThroughTransition
      iData.L = (_vPrivGetViewTransition() * vec4(_sbLightsSB2.PointPosition[i], 1.0)).xyz - iData.P;
    #else
      iData.L = _sbLightsSB2.PointPosition[i] - iData.P;
    #endif
      vec3 lightDist = vec3(1.0, 0.0, vDot(iData.L, iData.L));
      lightDist.y = vSqrt(lightDist.z);
      iData.L *= 1.0 / lightDist.y;
      const float lightAttenuation = 1.0 / vDot(_sbLightsSB2.PointAttenuation[i], lightDist);
      iData.irradiance = lightAttenuation * _sbLightsSB2.PointColor[i] * _sbLightsSB2.PointPower[i];
      iData.visibility = vMax(ComputeVisibilityPointLights(_sbLightsSB2.PointShadowLayer[i], i, _sbLightsSB2.PointPosition[i]), iData.minVisibility);
      iData.lightID = i;

    #if defined(TransparentShadow)
      const vec3 preRadiance = res.radiance;
    #endif

      ComputeRenderingEquation(iData, iParameters, res);

    #if defined(TransparentShadow)
      const vec3 curRadiance = res.radiance - preRadiance;
      if (curRadiance.r > 0.0 || curRadiance.g > 0.0 || curRadiance.b > 0.0) {
        ComputeTransparentShadowPointLights(res, _sbLightsSB2.PointShadowLayer[i], _sbLightsSB2.PointPosition[i], i);
      }
    #endif // TransparentShadow
    }
  #endif // NumberOfPointLights

  // --------------------------------------------------------------------------
  #ifdef NumberOfSpotLights
    #ifdef PDSFX_ENABLE_CUSTOM_BRDF_LAYER
      iData.lightType = LIGHT_TYPE_SPOT;
    #endif

    for(i = 0; i < vMin(NumberOfSpotLights, _V_MAX_LIGHTS); ++i)
    {
    #ifdef LightChannels
      if ((cb_cbVolMaterial.u_LightChannels & cb_LightChannels.SpotChannels[i]) == 0)
        continue;
    #endif

    #ifdef UsePassThroughTransition
      iData.L = (_vPrivGetViewTransition() * vec4(_sbLightsSB2.SpotPosition[i], 1.0)).xyz - iData.P;
    #else
      iData.L = _sbLightsSB2.SpotPosition[i] - iData.P;
    #endif
      vec3 lightDist = vec3(1.0, 0.0, vDot(iData.L, iData.L));
      lightDist.y = vSqrt(lightDist.z);
      iData.L *= 1./lightDist.y;
      const float lightAttenuation = 1.0 / vDot(_sbLightsSB2.SpotAttenuation[i], lightDist);
    #ifdef UsePassThroughTransition
      const float angle = vMax(0.0, vDot(iData.L, (_vPrivGetViewInverseTransposeTransition() * vec4(_sbLightsSB2.SpotDirection[i], 0.0)).xyz));
    #else
      const float angle = vMax(0.0, vDot(iData.L, _sbLightsSB2.SpotDirection[i]));
    #endif
      const float outerAngle = _sbLightsSB2.SpotPhi[i];
      const float innerAngle = _sbLightsSB2.SpotTheta[i];
      const float spotFactor = vSmoothstep(outerAngle, innerAngle, angle);
      iData.irradiance = lightAttenuation * _sbLightsSB2.SpotPower[i] * _sbLightsSB2.SpotColor[i] * spotFactor;

      iData.visibility = vMax(ComputeVisibility(_sbLightsSB2.SpotShadowLayer[i]), iData.minVisibility);
      iData.lightID = i;

    #if defined(TransparentShadow)
      const vec3 preRadiance = res.radiance;
    #endif

      ComputeRenderingEquation(iData, iParameters, res);

    #if defined(TransparentShadow)
      const vec3 curRadiance = res.radiance - preRadiance;
      if (curRadiance.r > 0.0 || curRadiance.g > 0.0 || curRadiance.b > 0.0) {
        ComputeTransparentShadow(res, _sbLightsSB2.SpotShadowLayer[i]);
      }
    #endif // TransparentShadow
    }
  #endif // NumberOfSpotLights

  // --------------------------------------------------------------------------
  #ifdef NumberOfDirLights
    #ifdef PDSFX_ENABLE_CUSTOM_BRDF_LAYER
      iData.lightType = LIGHT_TYPE_DIRECTIONAL;
    #endif

    #if defined(ShadowMap) && defined(CloudShadows)
      #ifdef _PDSFX1_FS_Position
        const vec3 viewPos = ComputeViewPosition();
      #else
        const vec3 viewPos = _SBViewPos;
      #endif
      const float cloudShadows = GetCloudShadows(viewPos);
    #endif

    for(i = 0; i < vMin(NumberOfDirLights, _V_MAX_LIGHTS); ++i)
    {
    #ifndef PDSFX_ENABLE_CUSTOM_BRDF_LAYER
      // FBJ: Optim, but doesn't work for Globe with PDSFX_ENABLE_CUSTOM_BRDF_LAYER, I don't know why
      if (_sbLightsSB2.DirPowerPerAreaUnit[i] == 0)
          continue;
    #endif

    #ifdef LightChannels
      if ((cb_cbVolMaterial.u_LightChannels & cb_LightChannels.DirChannels[i]) == 0)
        continue;
    #endif

      iData.visibility = vMax(ComputeVisibility(_sbLightsSB2.DirShadowLayer[i]), iData.minVisibility);

    // Inject cloud shadow
    #if defined(ShadowMap) && defined(CloudShadows)
      iData.visibility *= cloudShadows;
    #endif

      iData.L = - vNormalize(_sbLightsSB2.DirDirection[i]);
    #ifdef UsePassThroughTransition
      iData.L = (_vPrivGetViewInverseTransposeTransition() * vec4(iData.L, 0.0)).xyz;
    #endif
      iData.irradiance = _sbLightsSB2.DirPowerPerAreaUnit[i] * _sbLightsSB2.DirColor[i];
      iData.lightID = i;

    #if defined(TransparentShadow)
      const vec3 preRadiance = res.radiance;
    #endif

      ComputeRenderingEquation(iData, iParameters, res);

    #if defined(TransparentShadow)
      const vec3 curRadiance = res.radiance - preRadiance;
      if (curRadiance.r > 0.0 || curRadiance.g > 0.0 || curRadiance.b > 0.0) {
        ComputeTransparentShadow(res, _sbLightsSB2.DirShadowLayer[i]);
      }
    #endif // TransparentShadow
    }
  #endif // NumberOfDirLights

  // --------------------------------------------------------------------------
  #ifdef NumberOfLightsWithProfile
    ComputeProfileLighting(res, iData, iParameters);
  #endif // NumberOfLightsWithProfile

  // --------------------------------------------------------------------------
  #ifdef NumberOfAreaLights
    ComputeAreaLighting(res, iData, iParameters);
  #endif // NumberOfAreaLights

  // --------------------------------------------------------------------------
  ComputeTransparency(iData, iParameters, res);

  return res;
}

#else // GLES2Platform
// Optimizations first step: only one directional light is managed.
// "for" loop is very expensive and MUST be avoided at all cost.
// Compiler is not smart enough to unroll the loop by itself.

LightingResult DoStdLighting(in LightingData iData, in BRDFParameters iParameters)
{
  LightingResult res;
  res.radiance = vec3(0.);

#if defined(ShadowMap)
  if((_sbLightsSB2.CastShadow) != 0)
  {
    iData.visibility = ComputeShadows();
  }
#endif // defined(ShadowMap)

#ifdef NumberOfDirLights
  //if (NumberOfDirLights>0)
  {
    iData.L = -vNormalize(_sbLightsSB2.DirDirection[0]);
    iData.irradiance = _sbLightsSB2.DirColor[0] * _sbLightsSB2.DirPowerPerAreaUnit[0];
    ComputeRenderingEquation(iData, iParameters, res);
  }

  if (NumberOfDirLights>1)
  {
    iData.L = -vNormalize(_sbLightsSB2.DirDirection[1]);
    iData.irradiance = _sbLightsSB2.DirColor[1] * _sbLightsSB2.DirPowerPerAreaUnit[1];
    ComputeRenderingEquation(iData, iParameters, res);
  }
#endif // NumberOfDirLights

  ComputeTransparency(iData, iParameters, res);

  return res;
}

#endif // GLES2Platform

/****************************************************** STUFF NOT INTEGRATED********************************************************************************/

// Tiled lighting (forward +)
#ifdef TiledLighting
uniform sampler2D LightPerTile;
uniform sampler2D TiledLightInfo;

vec3 DoTiledLighting(vec3 albedo, vec3 specularColor)
{
  vec3 N = ComputeWorldNormal(cv);
#ifdef DoubleSidedLighting
  if (!gl_FrontFacing)
  {
    N = -N;
  }
#endif // DoubleSidedLighting
  vec3  V = vNormalize(_vPrivGetWorldEyePos() - WorldPos);
  ivec3 numTexel = { 60, 60, 1 };
  ivec2 size = vTextureSize(TiledLightInfo, 0);
  int   maxNumLightsPerTile = size.x;
  //
  vec3 posTexel = ProjPos.xyz / ProjPos.w;

  posTexel.x = int(( posTexel.x + 1.) * 0.5f * numTexel.x);
  posTexel.y = int((-posTexel.y + 1.) * 0.5f * numTexel.y);
  posTexel.z = 0;

  int curTexel    = int(posTexel.z + numTexel.z * (posTexel.y + numTexel.y * posTexel.x));
  vec3 finalColor = vec3(0, 0, 0);

  for (int i = 0; i < maxNumLightsPerTile; i++)
  {
    // Get the ID of light
    vec2 dataLightMapping = 255.f * vTexelFetch(LightPerTile, ivec2(i, curTexel), 0).xy;
    int lightID = int(dataLightMapping.x * 256.f + dataLightMapping.y);
    if (lightID <= 0) break;
    lightID -= 1;
    // Get the data of light
    vec4 data1 = vTexelFetch(TiledLightInfo, ivec2(0, lightID), 0);
    vec4 data2 = vTexelFetch(TiledLightInfo, ivec2(1, lightID), 0);
    vec4 lightPos = vec4(data1.xyz, 1);
    vec3 lightCol = data2.zyw;
    float  radius = data1.w;
    vec3 L = lightPos.xyz - WorldPos.xyz;
    float lightDist2 = dot(L, L);
    L = vNormalize(L);
    // attenuation
    float attRatio = (radius*radius - lightDist2) / (radius * radius);
    if (attRatio<0) attRatio = 0;
    lightCol *= attRatio;
    vec3 contrib;
    contrib = albedo * ComputeDiffuseBRDF(lightCol, L, N, V, cv);
    contrib += specularColor * ComputeSpecularBRDF(L, N, V, cv);
    finalColor += contrib;
  }

  return finalColor;
}
#endif // TiledLighting

#endif // Lighting
