void ComputeCommonValues()
{
}

vec3 ComputeObjectPosition()
{
  return vec3(vGetAttribPosition());
}

vec3 ComputeObjectNormal()
{
  return vec3(vGetAttribNormal());
}

//vec4 ComputeObjectTexCoord0()
//{
//}

//vec4 ComputeObjectTexCoord1()
//{
//}

//vec4 ComputeObjectTexCoord2()
//{
//}

//vec3 ComputeObjectTangent()
//{
//}

//vec3 ComputeObjectBinormal()
//{
//}

void ComputeVaryingValues()
{
  XRiteCarPaint2_vLocalPosition = vec3(vGetAttribPosition());
  XRiteCarPaint2_vLocalNormal = vec3(vGetAttribNormal());
}
