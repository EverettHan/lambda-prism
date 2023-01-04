void main()
{
  vec3 dir = ComputeDirectionFromTexCoord(vTexCoord);

  FRAGCOLOR = vTexture(s_EnvMap, dir);
}
