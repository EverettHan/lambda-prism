void main(void)
{ 
  vec2 tc = vTexCoord;

  #ifdef SO_CUBE_MAP_FLIP_Y
    tc.y = 1.0 - tc.y;
  #endif

  vec3 dir = ComputeDirectionFromTexCoord(tc);
  
  #ifdef SO_APPLY_IBL_TRANSFORM
    dir = vec3(-dir.z, dir.x, -dir.y);
    dir = vec3(cb_IBL.u_IBLTransfoMatrix * vec4(dir, 0.0));
    dir = vec3(dir.y, -dir.z, -dir.x);
  #endif
  
  #ifdef SO_CUBE_MAP
    vec3 coords = dir;
  #else
    vec2 coords = ComputeTexCoordFromDirection(dir);
  #endif
  
  //#ifdef SO_CUBE_MAP
  //  #define SAMPLE_ENV_MAP vTextureCubeMap
  //#else
  //  #define SAMPLE_ENV_MAP vTexture
  //#endif
  

  FRAGCOLOR = vec4(vTexture(s_EnvMap, coords).xyz, 1.0) * cb_IBL.u_IBLDiffuseScaleFactor;
}
