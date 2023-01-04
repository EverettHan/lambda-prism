void main(void)
{ 
  vec4 pixColor = GetColor(vTexCoord);

  vec4 color = GetColor(vTexCoord, vec2(1,-1));
  color += GetColor(vTexCoord, vec2( 0,-1));
  color += GetColor(vTexCoord, vec2(-1,-1));
  color += GetColor(vTexCoord, vec2( 1, 0));
  color += GetColor(vTexCoord, vec2(-1, 0));
  color += GetColor(vTexCoord, vec2( 1, 1));
  color += GetColor(vTexCoord, vec2( 0, 1));
  color += GetColor(vTexCoord, vec2(-1, 1));
  color -= 8.0*pixColor;

  color = vClamp(vec4(1.0)-color*cb_PostEffect.u_EdgeStrength, 0.0, 1.0)*pixColor;

  color.w = 1.0;

  FRAGCOLOR = color;
}

