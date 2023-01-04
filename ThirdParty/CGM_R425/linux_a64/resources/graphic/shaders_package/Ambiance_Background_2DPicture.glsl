void main(void)
{
  vec2 coord = ConvertViewportToViewpoint(vTexCoord);
  vec4 color = DrawPicture(s_Picture, coord, cb_PostEffectAuto.u_ViewpointSize.xy, 0);
  FRAGCOLOR = color;
}
