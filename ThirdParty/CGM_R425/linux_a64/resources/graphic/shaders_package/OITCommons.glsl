#ifdef OIT

uvec4 _ConvertPixelToUint(vec4 iColor)
{
  uvec4 result;

#if defined  OIT_HDR
  //We are in HDR
  result.x = packHalf2x16(iColor.rg);
  result.y = packHalf2x16(iColor.ba);
#else
  result.x = packUnorm4x8(iColor);
#endif //OIT_HDR

/*#ifdef IS_MSAA
  result.w = uint(gl_SampleMaskIn[0]);
#endif*/

  return result;
}

/*
uvec4 _ConvertPixelToUint(vec4 iColor, float iDepth, uint iCoverage)
{
  uvec4 result;

#if defined  OIT_HDR
  //We are in HDR
  result.x = packHalf2x16(iColor.rg);
  result.y = packHalf2x16(iColor.ba);

  result.z = floatBitsToUint(iDepth);
#else
  result.x = packUnorm4x8(iColor);
  result.y = floatBitsToUint(iDepth);
#endif //OIT_HDR

  result.w = iCoverage;

  return result;
}
*/

uvec4 _ConvertWA(vec4 iColor, float iCounter)
{
  uvec4 result;
  result.x = packHalf2x16(iColor.rg);
  result.y = packHalf2x16(iColor.ba);

  result.z = floatBitsToUint(iCounter);

  return result;
}

vec4 _GetAccumulationColor(uvec4 iFrag)
{
  vec4 result;
  result.rg = unpackHalf2x16(iFrag.x);
  result.ba = unpackHalf2x16(iFrag.y);

  return result;
}

/*
float _GetCounter(uvec4 iFrag)
{
  return uintBitsToFloat(iFrag.z);
}
*/

/*
uint _GetDepthComponent(uvec4 iValue)
{
#if defined OIT_HDR
  return iValue.z;
#else
  return iValue.y;
#endif
}
*/

vec4 _GetColor(uvec4 iColor)
{
  vec4 result;
#if defined OIT_HDR
  result.rg = unpackHalf2x16(iColor.x);
  result.ba = unpackHalf2x16(iColor.y);
#else
  result = unpackUnorm4x8(iColor.x);  
#endif //HDR
  return result;
}

/*
uint _GetCoverageComponent(uvec4 iValue)
{
  return iValue.w;
}

float _GetLinearZ(float iDepth)
{
  float z = iDepth;
  float zNear = vGetNearFarLogFactor().x;
  float zFar = vGetNearFarLogFactor().y;

  return 2*zFar*zNear / (zFar + zNear - (zFar - zNear)*(2*z -1));

}
*/

const float g_depthFightThreshold = 0.00001f;

uint getDepthTag()
{
  return 1 << 31; // sign bit; not used for depth, which are always positive
}

uint depthUntag(uint iDepthValue)
{
  return iDepthValue & ~(getDepthTag());
}

bool isTagged(uint iDepthValue)
{
  return (iDepthValue & getDepthTag()) != 0;
}

#endif //OIT
