void main(void)
{
  vec2 pos = vGetPosition();
#ifdef SCREEN_SPACE
  gl_Position = cb_ClippingMap.Matrix * vec4(pos.x, pos.y, 0.0, 1.0);
#else
  gl_Position = vGetViewProjMatrix() * cb_ClippingMap.Matrix * vec4(pos.x, pos.y, 0.0, 1.0);
#endif
  uvec2 attrib = vGetAttribUInt2();
	vOffset = int(attrib.x);
	vMapID = int(attrib.y);
}
