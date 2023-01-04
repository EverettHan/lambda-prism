float GetLuminance(const vec3 iColor)
{ 
  const vec3 LUMINANCE = vec3(0.3, 0.6, 0.1);
	return vDot(LUMINANCE, iColor.xyz);
}

vec3 ConvertRGBToHSV(const vec3 iColor)
{
  float colMax = vMax(max(iColor.x, iColor.y), iColor.z);
	float colMin = vMin(min(iColor.x, iColor.y), iColor.z);
	
	float v = colMax;
	
	float s = 0;
	if (colMax!=0) s = 1.0-colMin/colMax;
	
	float h = 0;
	float deltaCol = colMax-colMin;
  if (deltaCol!=0)
	{
	  if (colMax==iColor.x)      h = 60.0*(iColor.y-iColor.z)/deltaCol+360.0;
	  else if (colMax==iColor.y) h = 60.0*(iColor.z-iColor.x)/deltaCol+120.0;
	  else if (colMax==iColor.z) h = 60.0*(iColor.x-iColor.y)/deltaCol+240.0;
	}

  h = vMod(h, 360.0);  // attention avant c'etait du fmod, est-ce que ca va ca a la place????
	
	return vec3(h,s,v);
}

vec3 ConvertRGBToHSL(const vec3 iColor)
{
  // To implement
  vec3 col = vec3(0,0,0);
  return col;
}

vec3 ConvertHSVToRGB(const vec3 iColor)
{
  float h = iColor.x;
  float s = iColor.y;
  float v = iColor.z;
  
	int hi = int(h/60) % 6;
	
	float f = h/60-hi;
	float l = v*(1-s);
	float m = v*(1-f*s);
	float n = v*(1-(1-f)*s);
	
	vec3 col = vec3(0,0,0);
	switch (hi)
	{
	  case 0:
	    col = vec3(v, n, l);
	    break;
	    
	  case 1:
	    col = vec3(m, v, l);
	    break;
	    
	  case 2:
	    col = vec3(l, v, n);
	    break;
	    
	  case 3:
	    col = vec3(l, m, v);
	    break;
	    
	  case 4:
	    col = vec3(n, l, v);
	    break;
	    
	  case 5:
	    col = vec3(v, l, m);
	    break;
	}
	
	return col;
}

vec3 ConvertHSLToRGB(const vec3 iColor)
{
  // To implement
  vec3 col = vec3(0,0,0);
  return col;
}

