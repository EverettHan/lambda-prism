
vec3 ComputeAlbedo(in vec3 iBarycentrics)
{
  //return vec3(0.0, 0.0, 1.0);
  return vec3(cb_EVisuPBR.albedo.xyz);
}
