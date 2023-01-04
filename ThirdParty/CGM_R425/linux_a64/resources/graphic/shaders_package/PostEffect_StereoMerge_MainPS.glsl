void main()
{
  vec4 leftColor  = vTexture(s_LeftEyeMap, vTexCoord.xy);
	vec4 rightColor = vTexture(s_RightEyeMap, vTexCoord.xy);
	
	vec4 result = g_LeftMatrix * leftColor+ g_RightMatrix * rightColor; 
	result.w = 1.f;

  FRAGCOLOR = result; 
}




