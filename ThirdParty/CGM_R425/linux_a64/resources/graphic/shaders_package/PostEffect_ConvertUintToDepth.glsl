// TODO : XML EFFECTS MIGRATION !

void main()
{
#ifndef IS_MSAA
  gl_FragDepth = vUintBitsToFloat(vTexture(s_SourceTex, vTexCoord).x);
#else //MS version
  ivec2 texCoord = ivec2(vTexCoord * vTextureSize(s_SourceTex));
  gl_FragDepth = vUintBitsToFloat(vTexelFetch(s_SourceTex, texCoord, gl_SampleID).x);
#endif //IS_MSAA
}
