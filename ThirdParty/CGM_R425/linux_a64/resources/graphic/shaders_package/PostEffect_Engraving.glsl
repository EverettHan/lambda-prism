void main(void)
{    
	vec4 col = vec4(1.0);  

  // Line Effect

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
    
  // Edge Effect  
    
  vec4 pixColor = GetColor(vTexCoord);

  vec4 colOutline =  GetColor(vTexCoord, vec2(1,-1));
  colOutline += GetColor(vTexCoord, vec2( 0,-1));
  colOutline += GetColor(vTexCoord, vec2(-1,-1));
  colOutline += GetColor(vTexCoord, vec2( 1, 0));
  colOutline += GetColor(vTexCoord, vec2(-1, 0));
  colOutline += GetColor(vTexCoord, vec2( 1, 1));
  colOutline += GetColor(vTexCoord, vec2( 0, 1));
  colOutline += GetColor(vTexCoord, vec2(-1, 1));
  colOutline -= 8.0*pixColor;

  colOutline = vec4(vec3(GetLuminance(colOutline.xyz)), 1.0);

  col = vClamp(vec4(1.0)-colOutline*cb_PostEffect.u_EdgeStrength, 0.0, 1.0)*col;
  col.w = 1.0;

  FRAGCOLOR = col;
}

