struct distribution_ggx_parameters
{
  vec2 m_Alpha;
  float m_Anisotropy;
  float m_AlphaPrime;
};

void distribution_ggx_initialize(out distribution_ggx_parameters oParameters, in float iRoughness, in float iAnisotropy)
{
  oParameters.m_Alpha.x = vPow2(iRoughness);
  oParameters.m_Alpha.y = vPow2(iRoughness * (1.0 - iAnisotropy));
  oParameters.m_Anisotropy = iAnisotropy;
}

void distribution_ggx_initialize_area(out distribution_ggx_parameters oParameters, in float iRoughness, in float iAnisotropy, in float iAlphaPrime)
{
  oParameters.m_Alpha.x = vPow2(iRoughness);
  oParameters.m_Alpha.y = vPow2(iRoughness * (1.0 - iAnisotropy));
  oParameters.m_Anisotropy = iAnisotropy;
  oParameters.m_AlphaPrime = iAlphaPrime;
}

float smith_masking_shadowing(const float alpha2, const float x)
{
  const float denom = x + vSqrt(vMix(vPow2(x), 1.0, alpha2));
  return x / denom;
}

float distribution_ggx_g(in distribution_ggx_parameters iParameters, in vec3 iN, in vec3 iV, in vec3 iL, in vec3 iX, in vec3 iY, float iNoL, float iNoV)
{
  // separable form of the Smith joint masking-shadowing function
  // https://github.com/KhronosGroup/glTF/tree/9356622f7d7ace7b2ad5b838c37c1d0084b67969/specification/2.0#specular-brdf
  const float alpha2 = vPow2(iParameters.m_Alpha.x);
  return 4.0 * smith_masking_shadowing(alpha2, iNoL) * smith_masking_shadowing(alpha2, iNoV);
}

float distribution_ggx_d(in distribution_ggx_parameters iParameters, in float iNoH, in vec3 iH, in vec3 iX, in vec3 iY)
{
  const float alpha_x = iParameters.m_Alpha.x;
  const float alpha_y = iParameters.m_Alpha.y;
  const float alpha_x2 = alpha_x * alpha_x;
  const float alpha_y2 = alpha_y * alpha_y;
  const float NoH2 = iNoH * iNoH;
  const float XoH2 = vPow2(vDot(iX, iH));
  const float YoH2 = vPow2(vDot(iY, iH));

  if (iParameters.m_Anisotropy > 0.0)
    return (1.0 / (PI * alpha_x * alpha_y * vPow2(XoH2/alpha_x2 + YoH2/alpha_y2 + NoH2)));

  return (alpha_x2 / (PI * vPow2(vMax(NoH2 * (alpha_x2 - 1.0) + 1.0, 1e-6))));
}

#ifdef SO_EVISUPBR_SPECULAR_AA

// Another form of the GGX NDF which is more suitable for roughness filtering for specular anti-aliasing
float distribution_ggx_d_func(const in vec3 iH_ts, const in mat2 roughM)
{
  const float Hz = iH_ts.z;
  const vec2 Hxy = vec2(iH_ts.x, iH_ts.y);
  const mat2 roughMinv = inverse(roughM);
  const float chi = step(0.0f, Hz);
  return chi / (PI * sqrt(determinant(roughM)) * vPow2(dot(Hxy, roughMinv*Hxy) + Hz*Hz));
  //return 1.0 / (PI * sqrt(determinant(roughM)) * vPow2(dot(Hxy, roughMinv*Hxy) + Hz*Hz));
}

// Before using distribution_ggx_d_func() we have to prepare the tangent space
float distribution_ggx_d_2(const in distribution_ggx_parameters iParameters,
  const in vec3 iH, const in vec3 iX, const in vec3 iY, const in vec3 iN)
{
  const vec3 T = normalize(iX - dot(iX, iN) * iN);
  const vec3 B = cross(iN, T);
  const mat3 TBN = mat3(T, B, iN);
  const mat3 TBN_inv = inverse(TBN);
  const vec3 H_ts = TBN_inv * iH;
#ifdef FragmentStage
  // filtered version
  const mat2 roughM = NonAxisAlignedNDFFiltering2(H_ts, iParameters.m_Alpha*iParameters.m_Alpha);
#else
  // non-filtered version
  const mat2 roughM = mat2(iParameters.m_Alpha.x*iParameters.m_Alpha.x, 0.0, 0.0, iParameters.m_Alpha.y*iParameters.m_Alpha.y);
#endif
  return distribution_ggx_d_func(H_ts, roughM);
}

#endif // SO_EVISUPBR_SPECULAR_AA

vec3 distribution_ggx(in distribution_ggx_parameters iParameters, in fresnel_dielectric_parameters iFresnelParameters,
                      in vec3 iN, in vec3 iV, in vec3 iL, in vec3 iH, in vec3 iX, in vec3 iY,
                      in float iNoL, in float iNoV, in float iNoH, in float iLoH)
{
  const float iNoV_clamped = vMax(1e-6, iNoV);
  const float iNoL_clamped = vMax(1e-6, iNoL);
#ifdef SO_EVISUPBR_SPECULAR_AA
  const float d = distribution_ggx_d_2(iParameters, iH, iX, iY, iN);
#else
  const float d = distribution_ggx_d(iParameters, iNoH, iH, iX, iY);
#endif
  const float g = distribution_ggx_g(iParameters, iN, iV, iL, iX, iY, iNoL_clamped, iNoV_clamped);
  const float m = (d * g) / (4.0 * iNoV_clamped * iNoL_clamped);
  const vec3 f = fresnel_dielectric(iFresnelParameters, iLoH);
  return vMax(vec3(0.0), m * f);
}

//No-fresnel version
float distribution_ggx(in distribution_ggx_parameters iParameters,
                      in vec3 iN, in vec3 iV, in vec3 iL, in vec3 iH, in vec3 iX, in vec3 iY,
                      in float iNoL, in float iNoV, in float iNoH, in float iLoH)
{
  const float iNoV_clamped = vMax(1e-6, iNoV);
  const float iNoL_clamped = vMax(1e-6, iNoL);
#ifdef SO_EVISUPBR_SPECULAR_AA
  const float d = distribution_ggx_d_2(iParameters, iH, iX, iY, iN);
#else
  const float d = distribution_ggx_d(iParameters, iNoH, iH, iX, iY);
#endif
  const float g = distribution_ggx_g(iParameters, iN, iV, iL, iX, iY, iNoL, iNoV);
  const float m = (d * g) / (4.0 * iNoV_clamped * iNoL_clamped);
  return vMax(0.0, m);
}

//Area light version
vec3 distribution_ggx_area(in distribution_ggx_parameters iParameters, in fresnel_dielectric_parameters iFresnelParameters,
  in vec3 iN, in vec3 iV, in vec3 iL, in vec3 iH, in vec3 iX, in vec3 iY,
  in float iNoL, in float iNoV, in float iNoH, in float iLoH)
{
  float d = distribution_ggx_d(iParameters, iNoH, iH, iX, iY);
  d = max(d * iParameters.m_AlphaPrime, 0.0);
  const float g = distribution_ggx_g(iParameters, iN, iV, iL, iX, iY, iNoL, iNoV);
  const float m = (d * g) / vMax(1e-6, 4.0 * iNoL * iNoV);
  const vec3 f = fresnel_dielectric(iFresnelParameters, iLoH);
  return max(vec3(0.0), m * f);
}

float distribution_ggx_pdf(in distribution_ggx_parameters iParameters, in fresnel_dielectric_parameters iFresnelParameters,
                          in vec3 iN, in vec3 iV, in vec3 iL, in vec3 iH, in vec3 iX, in vec3 iY,
                          in float iNoL, in float iNoV, in float iNoH, in float iLoH)
{
  const float d = distribution_ggx_d(iParameters, iNoH, iH, iX, iY);
  return d * iNoH / (4.0 * iLoH);
}

vec3 distribution_ggx_sample(in distribution_ggx_parameters iParameters, vec2 iRand)
{
  const float phi = iRand.x * 2.0 * PI;
  const float a = iParameters.m_Alpha.x; //Isotropic only
  const float value = (1.0-iRand.y)/(1.0+(a*a-1.0)*iRand.y);
  const float cosTheta = vSqrt(value);
  const float sinTheta = vSqrt(1.0 - value);
  const vec3 H = vec3(sinTheta * vCos(phi), sinTheta * vSin(phi), cosTheta);
  return H;
}
