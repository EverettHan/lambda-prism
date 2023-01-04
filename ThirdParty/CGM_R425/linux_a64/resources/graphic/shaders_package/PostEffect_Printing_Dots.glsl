void main(void)
{    
	vec4 col = vec4(1.0);  
  
  vec2 coordPixel = ConvertViewportToViewpoint(vTexCoord)*cb_PostEffectAuto.u_ViewpointSize.xy;

  vec2 delta = vec2(int(coordPixel.x)%cb_PostEffect.u_DotSizeInPixel, int(coordPixel.y)%cb_PostEffect.u_DotSizeInPixel);

  vec2 startPtPixel = coordPixel - delta;
  vec2 startPt = ConvertViewpointToViewport(startPtPixel/cb_PostEffectAuto.u_ViewpointSize.xy);
              
  float luminance = 0;
  for (int j=0; j<cb_PostEffect.u_DotSizeInPixel; j++)
  {
    for (int i=0; i<cb_PostEffect.u_DotSizeInPixel; i++)
    {
      vec4 tmpCol = GetColor(startPt, vec2(i,j));   
      luminance += GetLuminance(tmpCol.xyz);
    }
  }

  float dotSize = float(cb_PostEffect.u_DotSizeInPixel);
  luminance = luminance/(dotSize*dotSize);		
  luminance = 1.0 - luminance;
  
	float radius = dotSize*1.44*0.5;
  luminance *= radius;
	    
	float lMax = luminance + 1.0;
	float lMin = luminance - 1.0;
	if (lMin<0) lMin = 0;
  
  vec2 pt = coordPixel - startPtPixel - vec2(dotSize)*0.5;
	float value = pt.x*pt.x+pt.y*pt.y;
	value = vSmoothstep(lMin*lMin, lMax*lMax, value+1);
	
	col = vec4(value, value, value, 1.f);
  
  FRAGCOLOR = col;
}

