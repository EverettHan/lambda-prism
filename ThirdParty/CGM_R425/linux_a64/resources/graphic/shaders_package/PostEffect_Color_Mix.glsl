void main(void)
{ 
  vec4 color = GetColor(vTexCoord);

#ifdef COLOR_MODE2
  // 0: u_Color
  // 1: 1
  color = (1-cb_PostEffect.u_Color)*color+cb_PostEffect.u_Color;
#else
  // 0  : 0
  // 0.5: u_Color
  // 1  : 1
	color = (2-4*cb_PostEffect.u_Color)*(color*color)+(4*cb_PostEffect.u_Color-1)*color;
#endif

	color.w = cb_PostEffect.u_Color.w;
	
  FRAGCOLOR = color;
}

