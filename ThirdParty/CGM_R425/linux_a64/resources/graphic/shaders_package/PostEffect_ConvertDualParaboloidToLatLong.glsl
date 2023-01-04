void main()
{ 
  vec3 dir = ComputeDirectionFromTexCoord(vTexCoord);
  vec3 coords = ComputeDualParaboloidFromDirection(dir);

  FRAGCOLOR = vTexture(s_EnvMap, coords);
}
