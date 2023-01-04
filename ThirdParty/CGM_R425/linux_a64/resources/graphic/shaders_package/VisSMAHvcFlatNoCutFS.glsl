
vec3 ComputeAlbedo()
{
  return v4_color.rgb;
}

float ComputeOpacity()
{
  return v4_color.a;
}

vec3 ComputeSpecularReflectance()
{
  return 0.04 * v4_color.rgb;
}
