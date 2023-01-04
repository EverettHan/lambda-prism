
// To avoid ugly precision problems on gl_PointCoord in FS, we round up the position in screen space...
// Not so cute, but does the work!
void AlignPoint(inout vec4 position)
{
  position.xy /= position.w;
  position.xy = vFma(position.xy, vec2(0.5), vec2(0.5));
  position.xy = vFloor(position.xy * cb_Viewport.u_ViewportSize) + 0.5; 
  position.xy *= cb_Viewport.u_PixelSize;
  position.xy = vFma(position.xy, vec2(2.0), vec2(-1.0));
  position.xy *= position.w;
}
