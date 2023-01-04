
vec3 ComputeAlbedo()
{
  return v4_color.rgb;
}

vec3 ComputeSpecularReflectance()
{
  return 0.04 * v4_color.rgb;
}

vec3 ComputeViewNormal()
{
  return v3_normal;
}
