void main()
{
  vec4 viewPosition = vGetWorldViewMatrix() * vec4(vGetPosition().xyz, 1.0);
  gl_Position = vGetProjectionMatrix() * viewPosition;

  // LogDepth
#ifdef NeedViewPos
  vSetViewPosPostTransform(viewPosition);
#endif

  vFrontColor = vGetColor();
  vTexCoord.xy = vGetTexCoord().xy;
  vUsingFreeTypeTexture = vGetTexCoord().z;
}
