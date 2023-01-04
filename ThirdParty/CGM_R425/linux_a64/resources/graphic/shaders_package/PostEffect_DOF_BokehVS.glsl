void main(void)
{
  vec4 vPosition = vec4(vGetPosition(), 1);
  gl_Position = vPosition;
}
