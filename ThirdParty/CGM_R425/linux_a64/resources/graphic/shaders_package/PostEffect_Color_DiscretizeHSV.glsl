void main(void)
{ 
  vec4 color = GetColor(vTexCoord);

  // conversion HSV
  color.xyz = ConvertRGBToHSV(color.xyz);

  // modificateur
	color.x = vMod(color.x+cb_PostEffect.u_Hue,360.f);
	color.y = vClamp(color.y*cb_PostEffect.u_Saturation, 0.0, 1.0);
	color.z = (2-4*color.z)*(cb_PostEffect.u_Value*cb_PostEffect.u_Value)+(4*color.z-1)*cb_PostEffect.u_Value;

	// discretisation
	color.x = int(color.x*cb_PostEffect.u_NumHue/360.0);
	color.x *= 360.0/cb_PostEffect.u_NumHue;
	
	color.y = int(color.y*cb_PostEffect.u_NumSaturation);
	color.y *= 1.0/cb_PostEffect.u_NumSaturation;
	
  color.z = int(color.z*cb_PostEffect.u_NumValue);
	color.z *= 1.f/cb_PostEffect.u_NumValue;
	

  // conversion RGB
  color.xyz = ConvertHSVToRGB(color.xyz);
	
  FRAGCOLOR = color;
}

