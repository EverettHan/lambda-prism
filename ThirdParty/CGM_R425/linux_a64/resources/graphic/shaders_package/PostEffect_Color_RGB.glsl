void main(void)
{ 
  vec4 color = GetColor(vTexCoord);

	color.xyz = (2-4*color.xyz)*(cb_PostEffect.u_Color*cb_PostEffect.u_Color)+(4*color.xyz-1)*cb_PostEffect.u_Color;
	
  FRAGCOLOR = color;
}

