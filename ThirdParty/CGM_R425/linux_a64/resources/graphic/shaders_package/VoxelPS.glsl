#if defined(VoxelMapGeneration) 

flat in int v_MainDirection;

void ComputeVoxelMap()
{
  vec4 colorData = vec4(1.0);

  int voxelSize = vImageSize(voxelMap).x;
  
  ivec3 pos;
  float posZ = gl_FragCoord.z * voxelSize;
  if (v_MainDirection == 0)       pos = ivec3(posZ, voxelSize - 1 - gl_FragCoord.x, gl_FragCoord.y);  // X
  else if (v_MainDirection == 1)  pos = ivec3(gl_FragCoord.x, posZ, gl_FragCoord.y);                  // Y
  else                            pos = ivec3(voxelSize - 1 - gl_FragCoord.x, gl_FragCoord.y, posZ);  // Z

#ifdef DEBUG_DIR
  if (v_MainDirection != DEBUG_DIR) discard;
#endif
  
  vImageStore(voxelMap, pos, colorData);

  // Rasterization along z View direction
#ifdef USE_DERIVATIVE
  float dzMax = vMax(dFdx(gl_FragCoord.z), dFdy(gl_FragCoord.z)); 
  float dzMin = vMin(dFdx(gl_FragCoord.z), dFdy(gl_FragCoord.z)); 
  ivec3 axisPos = ivec3(0);
  axisPos[v_MainDirection] = 1;
  if (dzMax >  0.0) vImageStore(voxelMap, pos + axisPos, colorData);
  if (dzMin < -0.0) vImageStore(voxelMap, pos - axisPos, colorData);
#endif
}

#endif 


