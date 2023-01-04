void main(void)
{   
  vec4 col;
  if (IsBackground(vTexCoord.xy))
  {
    col = cb_CID.u_BackgroundColor;
  }
  else
  {
    col = cb_CID.u_MeshColor;
  }

  float ratio = ComputeOutline();
  col = (1.0 - ratio) * col + ratio * cb_CID.u_EdgeColor;
  FRAGCOLOR = col;
}

