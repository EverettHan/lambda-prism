
float ComputeAngleValue(const in float iAngle, const in float iSize, const in float iBlurSize)
{
  float value = iAngle;
  if (iBlurSize > 0 && iSize < 1.0)
  {
    value = (value - iSize) / ((1.0 - iSize) * iBlurSize);
    value = vClamp(value, 0.0, 1.0);
    value = 1.0 - value;
    value *= value;
    value *= value;
  }
  else
  {
    value = (value > iSize ? 0.0 : 1.0);
  }

  return value;
}

void main()
{
  float resValue = 1.0;

  vec3 viewDir = vNormalize(vRay.xyz);
  
  vec3 biZenith       = vCross(cb_BgQuad.u_ZenithDirection, cb_BgQuad.u_QuadDirection);
  biZenith = vNormalize(biZenith);

  vec3 mainDirection  = vCross(biZenith, cb_BgQuad.u_ZenithDirection);

  {
    vec3 dir1 = viewDir - vDot(viewDir, mainDirection) * mainDirection;
    dir1 = vNormalize(dir1);

    float angle1 = 1.0 - vAcos(vDot(dir1, cb_BgQuad.u_ZenithDirection)) * INV_PI;
    angle1 *= 2.0;
    
    resValue *= ComputeAngleValue(angle1, cb_BgQuad.u_Thickness, cb_BgQuad.u_ThicknessBlur);
  }

  {
    vec3 dir2 = viewDir - vDot(viewDir, biZenith) * biZenith;
    dir2 = vNormalize(dir2);

    float angle2 = 1.0 - vAcos(vDot(dir2, cb_BgQuad.u_ZenithDirection)) * INV_PI;
    angle2 *= 2.0;

    resValue *= ComputeAngleValue(angle2, cb_BgQuad.u_Length, cb_BgQuad.u_LengthBlur);
  }
  
  FRAGCOLOR = vec4(cb_BgQuad.u_Color*cb_BgQuad.u_Intensity, resValue);
}
