uniform coherent layout(r32ui) uimage2DArray DecalTransparZMap;

struct DecalTransparData_t
{
  uvec4 first;
  uvec4 second;
  uvec4 third;
};

layout(std430) coherent restrict buffer DecalTransparData
{
  DecalTransparData_t g_DecalTransparData[];
};

/** Takes a depth and stencil value, and packs it into a DEPTH_24_STENCIL_8 uint.
 *  @param iDepth The depth floating point value to pack
 *  @param iStencil The stencil uint8 value to pack
 *  @return The resulting uint32 containing depth and stencil
 */
uint vPackDepthStencil(in float iDepth, in uint iStencil)
{
  float normz = clamp(iDepth, -1.0, 1.0);
  float linz = floor(normz * (1 << 23));
  uint linUintZ = uint(int(linz) + (1 << 23)); // faudrait peut etre clamp à 1 << 24 - 1
  uint res = (linUintZ << 8) | iStencil; 
  return res;
}

/** Takes a DEPTH_24_STENCIL_8 uint and extracts depth and stencil values from it.
 *  @param iValue The uint32 value containing depth and stencil
 *  @param oDepth The extracted depth floating point value
 *  @param oStencil The extracted uint8 stencil value
 */
void vUnpackDepthStencil(in uint iValue, out float oDepth, out uint oStencil)
{
  uint linUintZ = iValue >> 8;
  int linIntZ = int(linUintZ  - (1 << 23) ); 
  oDepth = (float(linIntZ) / float(1 << 23)); 
  oStencil = (iValue & 0xFFu);
}

/** Returns 1-dimensional index from 2-dimensional frag coords. Needs cbPostEffect_Main_Auto
 *  @return Value suitable for indexing into 1D array
 */
uint vGetLinearFragmentIndex(in vec2 iSize)
{
  return uint(gl_FragCoord.y) * uint(iSize.x) + uint(gl_FragCoord.x);
}
