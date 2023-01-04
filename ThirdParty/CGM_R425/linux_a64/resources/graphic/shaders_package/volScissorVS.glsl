
void main(void)
{
  vec4 hPos = vec4(vGetPosition(), 1);
  gl_Position = vGetViewProjMatrix() * (cb_cbVolScissor.World * hPos);  
}

