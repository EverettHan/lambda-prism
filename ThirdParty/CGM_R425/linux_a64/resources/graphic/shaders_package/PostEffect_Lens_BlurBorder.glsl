void main(void)
{ 
  vec2 coord = ConvertViewportToViewpoint(vTexCoord)-vec2(0.5);
  float ratio = vDot(coord, coord);
  ratio *= ratio;
  ratio *= cb_PostEffect.u_Size/cb_PostEffect.u_Quality;

  vec2 direction = vec2(1.0, 0.0);
#ifdef INVERT_XY
  direction.xy = direction.yx;
#endif
  
  direction *= cb_PostEffectAuto.u_ViewpointFixRatio;
  direction = ConvertViewpointToViewportRatio(direction*ratio);

  vec4 col = vec4(0);
  for (int i=-cb_PostEffect.u_Quality; i<=cb_PostEffect.u_Quality; i++)
  {
    col += GetColor(vTexCoord+direction*i);
  }

  col *= 1.0/float(2*cb_PostEffect.u_Quality+1);

  FRAGCOLOR = col;
}

