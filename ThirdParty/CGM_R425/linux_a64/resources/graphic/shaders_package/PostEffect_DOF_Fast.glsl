float GetBlurRadius(vec2 iPt)
{
  float focus = ConvertZViewToZBuffer(cb_PostEffectAuto.u_FocusDistance);
    
  float z = GetZ(iPt);
  float radius = vAbs(z-focus)/(1.0-focus);
  
  return radius;
}
							  
void main(void)
{ 
  float blurRadius = GetBlurRadius(vTexCoord)*cb_PostEffect.u_BlurSize;  
  
  vec2 delta = vec2(1.0,0.0);
#ifdef INVERT_XY
  delta = vec2(delta.y, delta.x);
#endif
  delta *= blurRadius;
  delta = ConvertViewpointToViewportRatio(delta);
  delta *= cb_PostEffectAuto.u_ViewpointFixRatio;
  
  vec4 col = vec4(0.0);
  vec2 coord = vTexCoord - delta;    
  delta *= 1.0/float(cb_PostEffect.u_BlurQuality);

  float num = 0;
  for (int i=-cb_PostEffect.u_BlurQuality; i<=cb_PostEffect.u_BlurQuality; i++)
  {
    float ratio = 0.01 + GetBlurRadius(coord)*(1.0+cb_PostEffect.u_BlurQuality-vAbs(float(i)));
    
    col += GetColor(coord) * ratio;
    num += ratio;

    coord += delta;
  }  
  
  col *= 1.0/num;
	col.w = 1;
		
  FRAGCOLOR = col;
}

