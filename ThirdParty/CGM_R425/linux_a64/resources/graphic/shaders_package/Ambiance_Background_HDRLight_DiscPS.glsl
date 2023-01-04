void main()
{	
  vec3 viewDir = vNormalize(vRay);
  float value = vDot(viewDir, cb_BgDisc.u_Direction.xyz);
  value = value * 0.5 + 0.5;

  if (value < cb_BgDisc.u_Thickness * 0.5)
  {
    value = 1.0;
  }
  else
  {
    value -= cb_BgDisc.u_Thickness * 0.5;
    if (value < cb_BgDisc.u_ThicknessBlur)
    {
      value = 1.0 - value / cb_BgDisc.u_ThicknessBlur;
      value = value * value;
      value = value * value;
    }
    else
    {
      value = 0.0;
    }
  }

  vec4 col = vec4(cb_BgDisc.u_Color * cb_BgDisc.u_Intensity, value);

  
  FRAGCOLOR = col;
}
