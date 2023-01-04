#ifndef RTAO_BUFFER
  #define RTAO_BUFFER 0
#endif

vec3 cellIndexToColor(uint cellId)
{
  uint r = cellId & 0xFF;
  uint g = (cellId >> 8) & 0xFF;
  uint b = (cellId >> 16) & 0xFF;
  return vec3(float(r) / 255.0, float(g) / 255.0, float(b) / 255.0);
}

void main()
{
#if RTAO_BUFFER == 1
  #ifdef IS_MSAA
    vec4 texelValue = texelFetch(ao, ivec2(gl_FragCoord.xy), gl_SampleID);
  #else
    vec4 texelValue = texelFetch(ao, ivec2(gl_FragCoord.xy), 0);
  #endif

  FRAGCOLOR = vec4(vec3(texelValue.r), 1.0);

#elif RTAO_BUFFER == 2
  #ifdef IS_MSAA
    uvec4 texelValue = texelFetch(changeList, ivec2(gl_FragCoord.xy), gl_SampleID);
  #else
    uvec4 texelValue = texelFetch(changeList, ivec2(gl_FragCoord.xy), 0);
  #endif

  FRAGCOLOR = vec4(vec3(texelValue.r)/100.0, 1.0);

#elif RTAO_BUFFER == 3
  #ifdef IS_MSAA
    uvec4 texelValue = texelFetch(cellIndices, ivec2(gl_FragCoord.xy), gl_SampleID);
  #else
    uvec4 texelValue = texelFetch(cellIndices, ivec2(gl_FragCoord.xy), 0);
  #endif

  FRAGCOLOR = vec4(cellIndexToColor(texelValue.x), 1.0);
  
#endif

}
