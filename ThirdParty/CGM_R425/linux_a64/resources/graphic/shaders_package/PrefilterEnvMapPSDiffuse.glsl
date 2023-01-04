vec4 GetSampleVectorPDF(in float iX, in float iY, in float iRoughness, in vec3 iN)
{
  const float phi = 2.0 * PI * iX;
  const float sinTheta = vSqrt(iY);
  const float cosTheta = vSqrt(1.0 - iY);
  const vec3 H = vec3(sinTheta * vCos(phi), sinTheta * vSin(phi), cosTheta);
  const float pdf = cosTheta * INV_PI;
  return vec4(Tangent2World(H, iN), pdf);
}

float GetWeight(in float NoL)
{
  return 1.0;
}

float GetMipLevel(in float iNoH, in float iLoH, in float iNoL,
  in float iRoughness, in float pdf)
{
#ifdef SO_CONVOLUTION_FILTERED
  const vec3 size = vTextureSize(s_EnvMapArray, 0);
  const float N = cb_PrefilterEnvMap.u_TotalSamples;
  return 1.0 + 0.5 * log2(float(size.x*size.y) / (N*pdf*5.76));

  ////const float scale = 1.2;
  ////float d = 4.0*pow(scale, 2.0);
  ////float omegaS = 1.0 / (N*pdf);
  ////float omegaP = d/(size.x*size.y);
  ////return 1.0+0.5 * log2(omegaS/omegaP);
#else
  return 0.0;
#endif
}

vec3 ComputeLightVector(in vec3 iNormal, in vec3 iH)
{
  return iH;
}
