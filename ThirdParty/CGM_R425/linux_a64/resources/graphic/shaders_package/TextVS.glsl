void main(void)
{
  vec4 pos = vec4(vGetPosition(), 1.0);
#ifdef NoViewProj
  pos = vGetWorldMatrix() * pos;
#else
  pos = vGetProjMatrix() * vGetWorldViewMatrix() * pos;
#endif

  gl_Position = pos;
  vTexCoord = vGetTexCoord();
}
