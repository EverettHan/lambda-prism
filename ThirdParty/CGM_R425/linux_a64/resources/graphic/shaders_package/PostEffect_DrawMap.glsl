void main()
{
#ifdef SOURCE_ARRAY_ID
  vec4 texelValue = GetEffectTexture(s_SourceTex, vec3(vTexCoord.xy, SOURCE_ARRAY_ID));
#else
  vec4 texelValue = GetEffectTexture(s_SourceTex, vTexCoord);
#endif
  
#ifdef FORCE_ONECHANEL
  texelValue.rgb = vec3(texelValue.r);
#endif

  FRAGCOLOR = texelValue;
}
