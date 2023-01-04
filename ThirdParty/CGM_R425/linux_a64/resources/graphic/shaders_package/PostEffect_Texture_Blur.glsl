
void main(void)
{ 
  float ratio = GetLuminance(vTexture(s_BlurMap,	ConvertViewportToViewpoint(vTexCoord)*cb_PostEffect.u_Scale).xyz);
  vec2 direction = cb_PostEffect.u_Direction*ratio*cb_PostEffect.u_Strength/float(cb_PostEffect.u_Quality);

#ifdef INVERT_XY
  direction = vec2(direction.y, direction.x);
#endif
  
  direction *= cb_PostEffectAuto.u_ViewpointFixRatio;
  direction = ConvertViewpointToViewportRatio(direction);
  
  vec4 color = vec4(0);
  for (int i=-cb_PostEffect.u_Quality; i<=cb_PostEffect.u_Quality; i++)
  {
    color += GetColor(vTexCoord+direction*i);
  }

  color *= 1.0/float(cb_PostEffect.u_Quality*2+1);

  color.w = 1.0;
	
  FRAGCOLOR = color;
}

