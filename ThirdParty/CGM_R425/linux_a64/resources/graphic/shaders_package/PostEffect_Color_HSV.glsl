void main(void)
{ 
  vec4 color = GetColor(vTexCoord);

  color.xyz = ConvertRGBToHSV(color.xyz);

	color.x = vMod(color.x+cb_PostEffect.u_Hue, 360.0);
	color.y = vClamp(color.y*cb_PostEffect.u_Saturation, 0.0, 1.0);
	color.z = (2-4*color.z)*(cb_PostEffect.u_Value*cb_PostEffect.u_Value)+(4*color.z-1)*cb_PostEffect.u_Value;
	
	color.xyz = ConvertHSVToRGB(color.xyz);
  color.w = 1.0;

  FRAGCOLOR = color;
}

