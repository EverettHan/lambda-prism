void main()
{
#ifdef SOURCE_ARRAY_ID
  vec4 texelValue = GetEffectTexture(s_SourceTex, vec3(vTexCoord.xy, SOURCE_ARRAY_ID));
  float depthValue = GetEffectTexture(s_SourceDepthTex, vec3(vTexCoord.xy, SOURCE_ARRAY_ID)).x;
#else
  vec4 texelValue = GetEffectTexture(s_SourceTex, vTexCoord);
  float depthValue = GetEffectTexture(s_SourceDepthTex, vTexCoord).x;
#endif

  FRAGCOLOR = texelValue;
  gl_FragDepth = depthValue;
}
