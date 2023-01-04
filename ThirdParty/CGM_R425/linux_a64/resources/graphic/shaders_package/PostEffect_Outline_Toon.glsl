void main(void)
{    
  float ratio = ComputeOutline();
  
  float l = GetLuminance(GetColor(vTexCoord).xyz);
  l  = vMax(l, GetLuminance(GetColor(vTexCoord, vec2( 1, 0)).xyz));
  l  = vMax(l, GetLuminance(GetColor(vTexCoord, vec2(-1, 0)).xyz));
  l  = vMax(l, GetLuminance(GetColor(vTexCoord, vec2( 0, 1)).xyz));
  l  = vMax(l, GetLuminance(GetColor(vTexCoord, vec2( 0,-1)).xyz));
    
  vec4 col = vec4(0,0,0, cb_OutlineToon.u_RatioDark*ratio);
  if (l<cb_OutlineToon.u_LuminanceLimit) 
  {
    vec4 col2 = vec4(1,1,1, ratio*cb_OutlineToon.u_RatioLight);
    col = vMix(col2, col, l/cb_OutlineToon.u_LuminanceLimit);
  }

  FRAGCOLOR = col;
}

