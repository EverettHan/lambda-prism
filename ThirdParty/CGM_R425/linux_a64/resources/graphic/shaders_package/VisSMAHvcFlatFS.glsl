
vec3 ComputeAlbedo()
{
  if( vIsFrontFacing() )
    return v4_color.rgb;
  return v4_colorBack.rgb;
}

float ComputeOpacity()
{
  return v4_color.a;
}

vec3 ComputeSpecularReflectance()
{
  if( vIsFrontFacing() )
    return 0.04 * v4_color.rgb;
  return 0.04 * v4_colorBack.rgb;
}
