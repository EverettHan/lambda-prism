struct distribution_modified_lambert_parameters
{
  vec3 albedo;
  float metallic;
  float transparency;
};

void distribution_modified_lambert_init(out distribution_modified_lambert_parameters params, in vec3 albedo, in float metallic, in float transparency)
{
  params.albedo = albedo;
  params.metallic = metallic;
  params.transparency = transparency;
}

vec3 distribution_modified_lambert(in distribution_modified_lambert_parameters params, in float NoV, in float NoL, in vec3 F1, in vec3 F2)
{
  return max(vec3(0.0), params.albedo * (1.0 - params.metallic) * (1.0 - params.transparency) / PI * (1.0  - max(F1, F2)));
}
