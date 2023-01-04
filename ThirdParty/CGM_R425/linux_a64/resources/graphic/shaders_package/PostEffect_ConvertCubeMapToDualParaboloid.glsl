void main(void)
{
  vec3 dir = ComputeDirectionFromDualParaboloid(gTexCoord, gl_Layer);
  dir = vec3(-dir.z, dir.x, -dir.y);
  FRAGCOLOR = vTextureCubeMap(s_EnvMap, dir);
}

