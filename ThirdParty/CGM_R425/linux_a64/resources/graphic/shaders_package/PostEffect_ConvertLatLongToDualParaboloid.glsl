void main(void)
{
  vec3 dir = ComputeDirectionFromDualParaboloid(gTexCoord, gl_Layer);
  
  vec2 coords = ComputeTexCoordFromDirection(dir);

  FRAGCOLOR = vTexture(s_EnvMap, coords);
}

