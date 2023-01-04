
vec3 ComputeAlbedo()
{
  //return vec3(1.0, 0.0, 0.0);
  return cb_cbVolMaterial.u_DiffuseColor.rgb;
}

void ComputeCommonValues()
{

}

vec3 ComputeViewNormal()
{
  return vGetViewNormal();
}
