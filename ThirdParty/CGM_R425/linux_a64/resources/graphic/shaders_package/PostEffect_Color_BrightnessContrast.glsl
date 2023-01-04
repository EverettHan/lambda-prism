void main(void)
{   
  vec4  color = GetColor(vTexCoord);

	color = (color-0.5)*cb_PostEffect.u_Contrast + 0.5 + cb_PostEffect.u_Brightness;
  color.w = 1;
	
  FRAGCOLOR = color;
}

