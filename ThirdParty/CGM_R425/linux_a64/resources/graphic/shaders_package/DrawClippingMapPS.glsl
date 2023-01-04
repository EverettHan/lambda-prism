//#if (GLSLVersion >= 420)
//  // gf8: fail gracefully
//#ifdef ImageArray
//uniform restrict coherent layout(r32i) iimage2DArray clippingMap;
//#else
//uniform restrict coherent layout(r32i) iimage2D clippingMap;
//#endif
//#endif

layout(location = 0) out vec4 fragDummy;

void main(void)
{
#if (GLSLVersion >= 420)
  // gf8: fail gracefully
#ifdef ImageArray
  vImageStore(clippingMap, ivec3(gl_FragCoord.xy, vMapID), ivec4(vOffset,0,0,0));
#else
  vImageStore(clippingMap, ivec2(gl_FragCoord.xy), ivec4(vOffset,0,0,0));
#endif
  discard;
#endif
  fragDummy = vec4(0.0);
}
