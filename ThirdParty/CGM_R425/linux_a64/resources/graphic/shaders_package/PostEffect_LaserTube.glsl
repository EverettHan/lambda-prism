
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
  
  vec3 normal = GetNormal(vTexCoord).xyz;
  normal = (cb_PostEffectAuto.u_ViewInverseMatrix * vec4(normal, 0.0)).xyz;
  normal = vNormalize(normal);

  vec3 ray = vRay.xyz;
  ray = vNormalize(ray);
    
  ray = vReflect(ray, normal);
  
  vec3 viewDir = vNormalize(ray.xyz);

  vec3 projViewDirOnSection = viewDir - vDot(viewDir, cb_PostEffect.u_TubeDirection) * cb_PostEffect.u_TubeDirection;
  projViewDirOnSection = vNormalize(projViewDirOnSection);

  //------------------------------
  // Neon Thickness
  {
    vec3 zenith = cb_PostEffect.u_ZenithDirection - vDot(cb_PostEffect.u_ZenithDirection, cb_PostEffect.u_TubeDirection) * cb_PostEffect.u_TubeDirection;
    zenith = vNormalize(zenith);

    vec3  biZenith = vCross(zenith, cb_PostEffect.u_TubeDirection);

    float dotZenith = -vDot(viewDir, zenith);
    float angle = vAcos(vDot(projViewDirOnSection, biZenith)) * INV_PI;
    if (dotZenith > 0)
    {
      angle = (-angle);
    }
    angle = angle + 0.5;
    if (angle < 0)
    {
      angle += 2.0;
    }
    
    float minAngle = cb_PostEffect.u_Angle;
    float maxAngle = 2 - minAngle;

    angle = (angle - minAngle) / (maxAngle - minAngle);
      
    if (angle>0 && angle<1.0)
    {
      angle *= float(cb_PostEffect.u_Number);
      angle = vMod(angle, 1.0);
      angle = vAbs((angle - 0.5) * 2.0);

      resValue *= ComputeAngleValue(angle, cb_PostEffect.u_Thickness, cb_PostEffect.u_ThicknessBlur);

      //------------------------------
      // Neon Length 

      {
        angle = vDot(viewDir, projViewDirOnSection);
        angle = vAcos(angle) * INV_PI;
        angle = vAbs((angle - 0.5) * 2.0);
        angle = 1.0 - angle;

        resValue *= ComputeAngleValue(angle, cb_PostEffect.u_Length, cb_PostEffect.u_LengthBlur);
      }
    }
    else
    {
      resValue = 0;
    }
  }
    
  FRAGCOLOR = vec4(0,1,0, resValue);
}
