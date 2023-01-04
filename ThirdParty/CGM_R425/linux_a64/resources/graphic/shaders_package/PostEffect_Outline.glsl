void main(void)
{    
  vec4 col = vec4(0.0);
  col.w = ComputeOutline();

  FRAGCOLOR = col;
}

