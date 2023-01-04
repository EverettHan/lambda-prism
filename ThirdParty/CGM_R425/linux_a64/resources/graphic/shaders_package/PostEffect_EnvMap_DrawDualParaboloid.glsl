void main()
{
  vec3 dir = ComputeDirectionFromTexCoord(vTexCoord);
  vec3 coords = ComputeDualParaboloidFromDirection(dir);

  FRAGCOLOR = vTexture(s_EnvMap, coords);


  //coords = vec3(vec2(vTexCoord.x, vTexCoord.y), 1.0);

  //if(vTexCoord.x < 0.5)
  //{
  //  coords.x *= 2.0;
  //  coords.z = 0.0;
  //}
  //else
  //{
  //  coords.x *= 2.0;
  //  coords.x -= 1.0;
  //  coords.z = 1.0;
  //}

  //FRAGCOLOR = vTexture(s_EnvMap, coords);
}
