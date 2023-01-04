void main(void)
{ 
  vec4 color = GetColor(vTexCoord);

	color.x = int(color.x*cb_PostEffect.u_NumValue);
	color.y = int(color.y*cb_PostEffect.u_NumValue);
	color.z = int(color.z*cb_PostEffect.u_NumValue);
	
	color *= 1.f/cb_PostEffect.u_NumValue;
	
	color.w = 1.f;

  FRAGCOLOR = color;
}

