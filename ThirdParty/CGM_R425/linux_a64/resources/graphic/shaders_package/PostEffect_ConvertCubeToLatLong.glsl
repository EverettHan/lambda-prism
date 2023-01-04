void main(void)
{ 
  vec3 r = ComputeDirectionFromTexCoord(vTexCoord);
  
  vec4 color = vTexture(s_EnvMap, r);
  color.w = 1.0;
  
  FRAGCOLOR = color;
}

