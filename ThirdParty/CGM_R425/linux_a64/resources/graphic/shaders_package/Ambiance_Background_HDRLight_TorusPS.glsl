void main()
{	
  vec3 viewDir = vNormalize(vRay);
  float value = vDot(viewDir, cb_BgTorus.u_Direction.xyz);
  value = value * 0.5 + 0.5;

  value -= cb_BgTorus.u_Angle;
  value = vAbs(value);

  if (value < cb_BgTorus.u_Thickness * 0.5)
  {
    value = 1.0;
  }
  else
  {
    value -= cb_BgTorus.u_Thickness * 0.5;
    if (value < cb_BgTorus.u_ThicknessBlur)
    {
      value = 1.0 - value / cb_BgTorus.u_ThicknessBlur;
      value = value * value;
      value = value * value;
    }
    else
    {
      value = 0.0;
    }
  }

  vec4 col = vec4(cb_BgTorus.u_Color * cb_BgTorus.u_Intensity, value);

  
  FRAGCOLOR = col;
}
