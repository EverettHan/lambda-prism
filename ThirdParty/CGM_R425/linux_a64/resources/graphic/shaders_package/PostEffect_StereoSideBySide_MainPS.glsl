void main()
{
  vec2 texCoord = vTexCoord.xy;
  vec4 result;
  if (vTexCoord.x < 0.5)
  {
    if (ub_StereoMerge.u_SideBySide_Mode == 1)
      texCoord.x = 2.0*vTexCoord.x;
    else
      texCoord.x = vTexCoord.x + 0.25;
    result  = vTexture(s_LeftEyeMap, texCoord.xy);
  }
  else
  {
    if (ub_StereoMerge.u_SideBySide_Mode == 1)
      texCoord.x = 2.0*(vTexCoord.x-0.5);
    else
      texCoord.x = vTexCoord.x - 0.25;
	result = vTexture(s_RightEyeMap, texCoord.xy);
  }

  result.w = 1.f;
  FRAGCOLOR = result;
}

