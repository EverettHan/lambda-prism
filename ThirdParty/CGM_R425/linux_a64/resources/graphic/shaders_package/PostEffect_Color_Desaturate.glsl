void main(void)
{ 
  vec4  color     = GetColor(vTexCoord);
	float luminance = GetLuminance(color.xyz);
  
  FRAGCOLOR = vec4(luminance, luminance, luminance, 1.f);
}

