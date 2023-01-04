vec3 ComputeColor(vec3 iCol, vec3 iColorModifier)
{
  vec3 hsvModifier = ConvertRGBToHSV(iColorModifier);
  vec3 hsv         = ConvertRGBToHSV(iCol);

  hsv.x = vMod(hsv.x + hsvModifier.x, 360.0);
  hsv.y = vClamp(hsv.y*hsvModifier.y, 0.0, 1.0);
  hsv.z = (2 - 4 * hsv.z)*(hsvModifier.z*hsvModifier.z) + (4 * hsv.z - 1)*hsvModifier.z;
  
  return ConvertHSVToRGB(hsv);
}


void main(void)
{ 
  vec4 col = GetColor(vTexCoord);
  
  col.xyz = vPow(col.xyz, cb_PostEffect.u_Gamma.xyz) * cb_PostEffect.u_Gain.xyz + cb_PostEffect.u_Lift.xyz;
    
  FRAGCOLOR = col;
}

