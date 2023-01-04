void main(void)
{ 
  vec4 col = GetColor(vTexCoord);

#ifdef CORRECT_LINEAR_INTERPOLATION
  col.xyz = vFma(col.xyz, vec3(cb_PostEffect.u_CorrectLinearInterpolation.y), vec3(cb_PostEffect.u_CorrectLinearInterpolation.x));
#endif

  col.xyz = vTexture(s_LookupTable, col.xyz).xyz;

  FRAGCOLOR = col;
}

