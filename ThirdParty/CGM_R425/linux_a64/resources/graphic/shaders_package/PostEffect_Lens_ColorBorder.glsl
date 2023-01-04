void main(void)
{ 
    vec2 coord = ConvertViewportToViewpoint(vTexCoord);

#ifdef INVERT_XY
  float alpha = coord.y;
#else
  float alpha = coord.x;
#endif

  alpha = vAbs(2.0*(alpha-0.5));
  alpha = vSaturate((alpha-1+cb_PostEffect.u_Size)/cb_PostEffect.u_Size);
  alpha *= alpha;
  alpha *= alpha;

  vec4 col = cb_PostEffect.u_Color;
  col.w *= alpha;

  FRAGCOLOR = col;
}

