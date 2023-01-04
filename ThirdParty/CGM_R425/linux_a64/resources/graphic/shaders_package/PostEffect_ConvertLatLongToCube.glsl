void main()
{
  vec3 dir = ComputeDirectionFromCube(gl_Layer, gTexCoord);
  
  vec2 coords = ComputeTexCoordFromDirection(dir);
  
  FRAGCOLOR = vTexture(s_EnvMap, coords);
}
