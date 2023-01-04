// TODO : XML EFFECTS MIGRATION !

#ifndef GLES2Platform
layout(location = 0) out uint fragColor;
#define FRAGCOLOR fragColor
#else
#define FRAGCOLOR gl_FragColor
#endif

void main()
{

#ifndef IS_MSAA
  uint depth = vFloatBitsToUint(vTexture(s_SourceTex, vTexCoord).x);
#else //We are in MSAA
  ivec2 texCoord = ivec2(vTexCoord * vTextureSize(s_SourceTex));
  uint depth = vFloatBitsToUint(vTexelFetch(s_SourceTex, texCoord, gl_SampleID).x);
#endif //IS_MSAA

  FRAGCOLOR = depth;
}
