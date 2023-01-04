
void WeightedAverageColor(const vec4 iColor, inout vec4 ioColor)
{ 
  float luminance = GetLuminance(iColor.xyz); 
  float ratio     = 1.0/(1.0+cb_PostEffect.u_Strength*luminance);

  ioColor = vFma(vec4(iColor.xyz, 1.0), vec4(ratio), ioColor);
}

void WeightedAverageColor(const ivec2 iOffset, inout vec4 ioColor)
{
  WeightedAverageColor(GetColor(vTexCoord, iOffset), ioColor);
}

void main(void)
{   
  vec4 col = GetColor(vTexCoord);
  float luminance = GetLuminance(col.xyz); 
 
  if (luminance > cb_PostEffect.u_Threshold)
  {
    vec4 tmpcol = vec4(0,0,0,0.0001);

    WeightedAverageColor(col, tmpcol);
    WeightedAverageColor(ivec2( 1,  0), tmpcol);
    WeightedAverageColor(ivec2( 1,  1), tmpcol);
    WeightedAverageColor(ivec2( 0,  1), tmpcol);
    WeightedAverageColor(ivec2(-1,  1), tmpcol);
    WeightedAverageColor(ivec2(-1,  0), tmpcol);
    WeightedAverageColor(ivec2(-1, -1), tmpcol);
    WeightedAverageColor(ivec2( 0, -1), tmpcol);
    WeightedAverageColor(ivec2( 1, -1), tmpcol);

    col.xyz = tmpcol.xyz/tmpcol.w;
  }
        
  FRAGCOLOR = col; 
}
