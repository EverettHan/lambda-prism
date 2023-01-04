// Since some time at the beginning of 2020
// DSPBR2019x sheen switched from Inverted Ashikhmin (Sheen19xCosWeighted no defined)
// to cosine-weighted distribution (Sheen19xCosWeighted defined)
// Appropriate BRDF must be used if which define is commented/uncommented
#define Sheen19xCosWeighted

vec2 logComplex(in float val)
{
  const float real = log(abs(val));
  const float im = atan(0.0, val);
  return vec2(real, im);
}

vec2 invComplex(in vec2 val)
{
  const float coef = 1.0 / max(dot(val, val), 1e-6);
  return vec2(coef*val.x, -coef*val.y);
}

vec4 GetSampleVectorPDF(in float iX, in float iY, in float iRoughness, in vec3 iN)
{
  const float phi = 2.0 * PI * iX;

  // DSPBR 2019x aka Velvet - AshikhminInverted
  #if defined(EVisuPBR) && defined(SO_EVISUPBR_ver19x) && !defined(Sheen19xCosWeighted)
    const float b2 = iRoughness * iRoughness;
    const float interiorTerm = 4.0*b2*vExp(1.0/b2) / (4.0*b2*iY + iY - 1.0);
    const vec2 exteriorTerm = b2 * logComplex(interiorTerm);
    const float sinTheta_sqr = min(length(invComplex(exteriorTerm)), 1.0);
    //// cosTheta_sqr = 1.0 - sinTheta_sqr
    const float sinTheta = vSqrt(sinTheta_sqr);
    const float cosTheta = vSqrt(1.0 - sinTheta_sqr);
    //// value2 = -cotTheta*cotTheta/b2 = -cosTheta*cosTheta/(sinTheta*sinTheta*b2)
    //// value2 = -cosTheta_sqr / (sinTheta_sqr*b2)
    const float value2 = (sinTheta_sqr - 1.0) / (sinTheta_sqr * b2);
    const float pdf = cosTheta * (INV_PI / (1.0 + 4.0*b2)) * (1.0 + 4.0 * exp(value2) / (sinTheta_sqr*sinTheta_sqr));
  #endif
  // DSPBR 2019x aka Velvet - CosWeighted
  #if defined(EVisuPBR) && defined(SO_EVISUPBR_ver19x) && defined(Sheen19xCosWeighted)
    const float sinTheta = vSqrt(iY);
    const float cosTheta = vSqrt(1.0 - iY);
    const float pdf = cosTheta * INV_PI;
  #endif

  // DSPBR 2021x aka Soft Velvet
  #if defined(EVisuPBR) && defined(SO_EVISUPBR_ver21x)
    const float roughness = vMax(iRoughness, 0.07);
    const float sinTheta = vPow(iY, roughness / (2.0 * roughness + 1.0));
    const float cosTheta = vSqrt(1.0 - sinTheta*sinTheta);
    const float r_inv = 1.0 / roughness;
    const float pdf = 0.5 * INV_PI * (2.0 + r_inv) * vPow(sinTheta, r_inv) * cosTheta;
  #endif

  #ifdef GGX
    const float a2 = vPow4(iRoughness);
    const float value = (1.0-iY) / (1.0+(a2-1.0)*iY);
    const float cosTheta = vSqrt(value);
    const float sinTheta = vSqrt(1.0 - value);
    const float d = (a2-1.0) * value + 1.0;
    const float pdf = cosTheta * a2 * INV_PI / (d * d);
  #endif

  #if defined(Fur) && !defined(EVisuPBR) && !defined(SO_EVISUPBR_ver19x) && !defined(SO_EVISUPBR_ver21x)
    //TODO develop? Or this is now absolutely obsolete?
    const float sinTheta = 0.0;
    const float cosTheta = 1.0;
    const float pdf = 0.0;
  #endif

  // Satin
  #ifdef noFur
    const float a2 = vPow4(iRoughness);
    const float inv_8a2 = 1.0 / (8.0 * a2);
    const float loga = 8.0 * a2 * vLog(1.0-iY);
    const float value = loga / (loga - 1.0); //sinTheta_sqr
    const float sinTheta = vSqrt(value);
    const float cosTheta = vSqrt(1.0 - value);
    const float pdf = INV_PI * inv_8a2 * vExp(loga * inv_8a2) / vPow3(cosTheta);
  #endif

  const vec3 H = vec3(sinTheta * vCos(phi), sinTheta * vSin(phi), cosTheta);
  return vec4(Tangent2World(H, iN), pdf);
}

float GetPDF_GGX(in float iNoH, in float iRoughness)
{
  const float a2 = vPow4(iRoughness);
  const float D = vPow2(iNoH) * (a2 - 1.0) + 1.0;
  return 0.25 * a2 / (PI * vPow2(D));
}

float GetWeight(in float NoL)
{
  #ifndef GGX
    // DSPBR 2019x, 2021x, (and all the legacy Fabrics)
    return 1.0;
  #else
    // GGX
    return NoL;
  #endif
}

float GetMipLevel(in float iNoH, in float iLoH, in float iNoL,
  in float iRoughness, in float pdf)
{
  #ifdef SO_CONVOLUTION_FILTERED
    #if defined(SO_CONVOLUTION_DUAL_PARABOLOID_INPUT)
      const ivec3 size = vTextureSize(s_EnvMapArray, 0);
    #elif defined(SO_CONVOLUTION_LATLONG_INPUT)
      const ivec2 size = vTextureSize(s_EnvMap, 0);
    #else
      const ivec2 size = vTextureSize(s_EnvMapCube, 0);
    #endif // defined(SO_CONVOLUTION_DUAL_PARABOLOID_INPUT)

    const float N = cb_PrefilterEnvMap.u_TotalSamples;
    return 1.0 + 0.5 * log2(float(size.x*size.y) / (N*pdf*5.76));

    ////const float scale = 1.2;
    ////float d = 4.0*pow(scale, 2.0);
    ////float omegaS = 1.0 / (N*pdf);
    ////float omegaP = d/(size.x*size.y);
    ////return 1.0+0.5 * log2(omegaS/omegaP);
  #else
    return 0.0;
  #endif // SO_CONVOLUTION_FILTERED
}

vec3 ComputeLightVector(in vec3 iNormal, in vec3 iH)
{
  return 2.0 * vDot(iNormal, iH) * iH - iNormal;
}
