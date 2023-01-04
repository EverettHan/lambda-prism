void main()
{
  vec3 dir = ComputeDirectionFromTexCoord(vTexCoord);
  vec2 coords = ComputeTexCoordFromDirection(dir); //should be the same as vTexCoord

  FRAGCOLOR = vTexture(s_EnvMap, coords);
}
