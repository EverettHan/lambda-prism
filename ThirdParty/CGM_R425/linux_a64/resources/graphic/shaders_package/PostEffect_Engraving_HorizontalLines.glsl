void main(void)
{    
	vec4 col = vec4(1.0);  
  
  vec2 coordPixel = ConvertViewportToViewpoint(vTexCoord)*cb_PostEffectAuto.u_ViewpointSize.xy;

  float delta = int(coordPixel.y)%cb_PostEffect.u_LineSizeInPixel;

  vec2 startPt = vec2(coordPixel.x, coordPixel.y-delta);
  startPt = ConvertViewpointToViewport(startPt/cb_PostEffectAuto.u_ViewpointSize.xy);
              
  float luminance = 0;
	for (int j=0; j<cb_PostEffect.u_LineSizeInPixel; j++)
	{
		vec4 tmpCol = GetColor(startPt, vec2(0,j));   
		luminance += GetLuminance(tmpCol.xyz);
	}

  float lineSize = float(cb_PostEffect.u_LineSizeInPixel);
  luminance = luminance/lineSize;		
  luminance = 1.0 - luminance;
  luminance *= lineSize;
	
	float lMax = luminance + 1.0;
	float lMin = luminance - 1.0;
				
	float r = vSmoothstep(lMin, lMax, delta*0.6 + 1.5);
  col = vec4(r,r,r, 1.0);

  FRAGCOLOR = col;
}

