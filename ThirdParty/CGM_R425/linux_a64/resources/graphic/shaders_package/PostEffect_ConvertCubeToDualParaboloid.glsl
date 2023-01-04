void main(void)
{
  vec3 dir = ComputeDirectionFromDualParaboloid(gTexCoord, gl_Layer);

  FRAGCOLOR = vTexture(s_EnvMapCube, dir);
}

