struct fresnel_dielectric_parameters
{
  vec3 albedo;
  float ior;
  vec3 specularTint;
  float specular;
  float metallic;
};

vec3 fresnel_schlick(in vec3 iF0, in vec3 iF90, in float iLoH)
{
  const float power = vPow5(1.0 - iLoH);
  return vMix(iF0, iF90, power);
}

void fresnel_dielectric_init(out fresnel_dielectric_parameters params, in vec3 albedo, in float ior, in vec3 specularTint, in float specular, in float metallic)
{
  params.albedo = albedo;
  params.ior = ior;
  params.specularTint = specularTint;
  params.specular = specular;
  params.metallic = metallic;
}

vec3 fresnel_dielectric(in fresnel_dielectric_parameters params, in float iLoH)
{
  const float F_0 = vPow2((1.0 - params.ior) / (1.0 + params.ior));
  const vec3 rho_sr0 = (1.0 - params.metallic) * F_0 * params.specular * params.specularTint + params.metallic * params.albedo;
  const float rho_sr90 = (1.0 - params.metallic) * params.specular + params.metallic;
  const float sintheta_t_sqr = vPow2(1.0/params.ior) * (1.0 - vPow2(iLoH));
  const float costheta_t_sqr = 1.0 - sintheta_t_sqr;
  return (sintheta_t_sqr >= 1.0) ? vec3(1.0) : (rho_sr0 + (rho_sr90 - rho_sr0) * vPow5(1.0 - sqrt(costheta_t_sqr)));

  //return fresnel_schlick(rho_sr0, vec3(rho_sr90), iLoH);
}
