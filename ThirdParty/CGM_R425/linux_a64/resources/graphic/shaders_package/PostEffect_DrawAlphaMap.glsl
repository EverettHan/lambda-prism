void main()
{
#ifdef SOURCE_ARRAY_ID
  vec4 col = GetEffectTexture(s_SourceTex, vec3(vTexCoord.xy, SOURCE_ARRAY_ID));
#else
  vec4 col = GetEffectTexture(s_SourceTex, vTexCoord);
#endif

  col.rgb = cb_PostEffect.u_Color.rgb;
  col.a *= cb_PostEffect.u_Color.a;

  FRAGCOLOR = col;
}
