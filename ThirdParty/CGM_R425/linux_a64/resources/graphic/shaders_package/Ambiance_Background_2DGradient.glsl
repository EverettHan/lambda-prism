void main()
{

  vec4 degrade      = vec4(vTexCoord.y);
  
  vec4 colorBG      = cb_cbBackground.BackGroundColor;
  vec4 colorDesired = cb_cbBackground.GraduatedColor;
  
  vec4 colorFinal = vMix(colorBG, colorDesired, degrade);

  FRAGCOLOR = vec4(colorFinal); //Don't care about alpha channel.
}
