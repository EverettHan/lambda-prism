void main()
{
  vec4 colDynamic = GetEffectTexture(s_SourceTex_Dynamic, vTexCoord);
  vec4 colStatic  = GetEffectTexture(s_SourceTex, vTexCoord);

  FRAGCOLOR = vMix(colDynamic, colStatic, cb_PostEffect.u_Ratio);
}
