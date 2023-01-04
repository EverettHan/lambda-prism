#if defined(MultiviewSinglePass) && (MultiviewSinglePass > 1)
  #ifndef WA_ARRAY_ID
    #define WA_ARRAY_ID vGetViewID()
  #endif
#endif

in vec2 vTexCoord;

out vec4 fragColor;

void main()
{
#ifndef WA_MSAA
  #ifdef WA_ARRAY_ID
    vec3 coord =  vec3(vTexCoord, float(WA_ARRAY_ID));
  #else
    vec2 coord =  vTexCoord;
  #endif
  
  vec4  sumColor =  vTexture(WA_ColorAccumulation, coord);
  float n        =  vTexture(WA_DepthAccumulation, coord).r;
#else //WA_MSAA
  #ifdef WA_ARRAY_ID
    ivec3 coord = ivec3(vTexCoord * textureSize(WA_ColorAccumulation).xy, WA_ARRAY_ID);
  #else
    ivec2 coord = ivec2(vTexCoord * textureSize(WA_ColorAccumulation));
  #endif

  vec4  sumColor =  vTexelFetch(WA_ColorAccumulation, coord, gl_SampleID);
  float n        =  vTexelFetch(WA_DepthAccumulation, coord, gl_SampleID).r;
#endif //WA_MSAA
  
  if(n <= 0.1 || sumColor.a == .0)
    discard;

  vec3  avgColor = sumColor.rgb / sumColor.a;
  float avgAlpha = sumColor.a   / n;

  float tmp = 0.0;

  //Avoid NAN with the pow function
  if(avgAlpha < 1.0)
    tmp = vPow(1.0 - avgAlpha, n);

  fragColor = vec4(avgColor, 1-tmp);
}
