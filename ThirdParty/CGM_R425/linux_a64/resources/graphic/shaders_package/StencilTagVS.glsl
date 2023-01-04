
void main()
{
  vec4 localPosition = vec4(vGetPosition().xy, -1., 1.);
  gl_Position = localPosition;
}
