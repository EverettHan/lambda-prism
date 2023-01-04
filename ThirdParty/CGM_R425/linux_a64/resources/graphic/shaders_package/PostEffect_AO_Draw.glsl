
void main()
{
  vec4 result = cb_PostEffect_AO.u_Color; 
  result.w *= GetEffectTexture(s_AoMap, vTexCoord).x;
  FRAGCOLOR = result; 
}

