void main(void)
{

  vec4 pos = vGetWorldViewMatrix() * vec4(vGetPosition(), 1.0);

  pos = vGetProjMatrix() * pos;

  gl_Position = pos;
  vColor = vec4(vGetColor().xyz, 0.2);
}
