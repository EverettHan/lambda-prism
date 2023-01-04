vec4 ComputeColor(const vec2 iPixelDelta, inout float oValue)
{ 
  float dotSize = float(cb_PostEffect.u_DotSizeInPixel);

  vec2 coordPixel = ConvertViewportToViewpoint(vTexCoord)*cb_PostEffectAuto.u_ViewpointSize.xy;

  vec2 delta = coordPixel - iPixelDelta*dotSize;
  delta = vec2(int(delta.x)%cb_PostEffect.u_DotSizeInPixel, int(delta.y)%cb_PostEffect.u_DotSizeInPixel);

  vec2 startPtPixel = coordPixel - delta;
  vec2 startPt = ConvertViewpointToViewport(startPtPixel/cb_PostEffectAuto.u_ViewpointSize.xy);
 
  vec4 col = vec4(0.0);               
  for (int j=0; j<cb_PostEffect.u_DotSizeInPixel; j++)
  {
    for (int i=0; i<cb_PostEffect.u_DotSizeInPixel; i++)
    {
      col += GetColor(startPt, vec2(i,j));   
    }
  }
  
  vec2 pt = coordPixel - startPtPixel - vec2(dotSize)*0.5;
	oValue = pt.x*pt.x+pt.y*pt.y;

  return col;
}

void main(void)
{    
  vec4 col = vec4(1.0);
  vec4 tmpCol = vec4(0);
  
  float dotSize = float(cb_PostEffect.u_DotSizeInPixel);
	float radius = dotSize*1.44*0.5;

  vec4 value = vec4(0);
	col.x = ComputeColor(vec2( 0,     0.25), value.x).x;
	col.y = ComputeColor(vec2(-0.25, -0.25), value.y).y;
	col.z = ComputeColor(vec2( 0.25, -0.25), value.z).z;

  col = col/(dotSize*dotSize);		
  col = vec4(1.0) - col;
  col *= radius;

  vec4 colMin = col-vec4(1.0);
	if (col.x<0) col.x = 0;
	if (col.y<0) col.y = 0;
	if (col.z<0) col.z = 0;
  colMin = colMin*colMin;

	vec4 colMax = col+vec4(1.0);
  colMax = colMax *colMax ;

	col = vSmoothstep(colMin, colMax, value+1.0);
  col.w = 1.0;
  
  FRAGCOLOR = col;
}

