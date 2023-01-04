void main(void)
{ 
  const int size = int(cb_PostEffect.u_Size);
  
  float ratio = 0;
  if (IsBackground(vTexCoord))
  {
    for (int i=-size; i<=size; i++)
    {
      for (int j=-size; j<=size; j++)
      {
        if(IsBackground(vTexCoord, vec2(i,j))==false)
        {
          ratio = 1;
        }
      }
    }
  }

  vec4  color = vec4(cb_PostEffect.u_Color.xyz, cb_PostEffect.u_Color.w*ratio);
  
  FRAGCOLOR = color;
}

