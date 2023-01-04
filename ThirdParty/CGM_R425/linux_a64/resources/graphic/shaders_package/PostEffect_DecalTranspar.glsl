
//uniform coherent layout(r32ui) uimage2DArray DecalTransparZMap;

struct DecalTransparData_t
{
  uvec4 first;
  uvec4 second;
  uvec4 third;
};

//layout(std430) coherent restrict readonly buffer DecalTransparData
//{
//  DecalTransparData_t g_DecalTransparData[];
//};

//void _BlendF2B(inout vec3 ioDstColor, inout float ioDstAlpha, in vec3 iSrcColor, in float iSrcAlpha)
//{
//  ioDstColor = ioDstAlpha * (iSrcAlpha * iSrcColor) + ioDstColor;
//  ioDstAlpha = (1.0 - iSrcAlpha) * ioDstAlpha;
//}

uint _GetFragmentIndex()
{
  return uint(gl_FragCoord.y) * uint(imageSize(DecalTransparZMap).x) + uint(gl_FragCoord.x);
}

void _UnpackDepthStencil(in uint iValue, out float oDepth, out uint oStencil)
{
  uint linUintZ = iValue >> 8;
  int linIntZ = int(linUintZ  - (1 << 23) ); 
  oDepth = (float(linIntZ) / float(1 << 23)); 
  oStencil = (iValue & 0xFFu);
  
  //oStencil = (iValue & 0xFF);
  //uint uintz = iValue >> 8;
  //oDepth = float(uintz) / (1 << 24);
}

void main(void)
{
  #ifndef IS_MSAA
    vec4 finalColor = vTexelFetch(backBuffer, ivec2(gl_FragCoord.xy), 0);
  #else
    vec4 finalColor = vTexelFetch(backBuffer, ivec2(gl_FragCoord.xy), gl_SampleID);
  #endif

  vec4 sumColor = vTexture(s_Tail, vTexCoord.xy);
  float n = vTexture(s_TailDepth, vTexCoord.xy).r;
  
  if(n > 0.01 && sumColor.a > 0.01)
  {
    vec3  avgColor = max(sumColor.rgb, vec3(0.0)) / sumColor.a;
    float avgAlpha = sumColor.a / n;
    
    float tmp = max(vPow(1.0 - avgAlpha, n),0);
  
    vec4 src = vec4(avgColor, 1.0-tmp);
    finalColor.rgb = src.a * src.rgb + (1.0-src.a) * finalColor.rgb;
    finalColor.a = src.a + (1-src.a)*finalColor.a;
  }
  
  const int nbLayerOIT = 5;
  ivec3 fragPosList = ivec3(gl_FragCoord.xy, 0);
  vec4 data;
  
  for(int i=nbLayerOIT-1; i >= 0; --i)
  {
    fragPosList.z = int(i);
      
    uint ind = imageLoad(DecalTransparZMap, fragPosList).x;
  
    if(ind == 0xFFFFFFFFu)
      continue;
  
    ind = _GetFragmentIndex();
    data = uintBitsToFloat(g_DecalTransparData[nbLayerOIT * ind + i].first);

    vec4 src = data;
    finalColor.rgb = src.a * src.rgb + (1.0-src.a) * finalColor.rgb;
    finalColor.a = src.a + (1-src.a)*finalColor.a;
  }
  
  FRAGCOLOR = finalColor;

  //++ Test
  //int i = 0;
  //fragPosList = ivec3(gl_FragCoord.xy, i);
  //  uint ind = imageLoad(DecalTransparZMap, fragPosList).x;
  //
  //  if(ind == 0xFFFFFFFFu)
  //    discard;
  //
  //ind =  _GetFragmentIndex();
  //data = uintBitsToFloat(g_DecalTransparData[nbLayerOIT * ind + i].first);
  //FRAGCOLOR = data;
  //-- Test
}
