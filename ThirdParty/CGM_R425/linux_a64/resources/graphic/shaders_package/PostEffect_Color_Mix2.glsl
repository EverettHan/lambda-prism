void main(void)
{ 
  vec4 colMix = cb_PostEffect.u_Color1;
  if (IsBackground(vTexCoord)) colMix = cb_PostEffect.u_Color2;

  vec4 color = GetColor(vTexCoord);
  color = (2-4*colMix)*(color*color)+(4*colMix-1)*color;
  color = vClamp(color, 0.0, 1.0);
	
  color.w = colMix.w;

  FRAGCOLOR = color;
}

