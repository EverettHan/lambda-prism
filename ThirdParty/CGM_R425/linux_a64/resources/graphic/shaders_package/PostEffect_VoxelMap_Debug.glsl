#ifndef DEBUG_MIP
#define DEBUG_MIP 0
#endif

float ComputeTmax(float iPosition, float iDir)
{
  if (iDir > 0.0)
  {
    return (1.0 - fract(iPosition)) / iDir;
  }
  else
  {
    return fract(iPosition) / (-iDir);
  }
}

const vec3 s_PlaneOrig[6] = vec3[]
(
  vec3(0, 0, 0),
  vec3(1.0, 1.0, 1.0),
  vec3(0, 0, 0),
  vec3(1.0, 1.0, 1.0),
  vec3(0, 0, 0),
  vec3(1.0, 1.0, 1.0)
);

const vec3 s_PlaneNormal[6] = vec3[]
(
  vec3(-1.0, 0, 0),
  vec3(1.0, 0, 0),
  vec3(0, -1.0, 0),
  vec3(0, 1.0, 0),
  vec3(0, 0, -1.0),
  vec3(0, 0, 1.0)
);

const ivec2 s_PlaneComp[6] = ivec2[]
(
  ivec2(1, 2),
  ivec2(1, 2),
  ivec2(0, 2),
  ivec2(0, 2),
  ivec2(0, 1),
  ivec2(0, 1)
);

void main()
{
  vec4 col = vec4(0, 0, 0, 0);
    

  //--------------------------------------------------
  // Raytracing with 6 cube faces of bounding box

  vec3 rayOrig = (cb_VoxelMap_Debug_Auto.transfoViewToVoxel * vec4(0,0,0,1)).xyz; 
  vec3 rayDir  = vRay;
  rayDir = vNormalize(rayDir);
  
  int foundFace = -1;
  vec3 pos;
  float t = 0;
  for (int i = 0; i < 6; i++)
  {
    float tmp = IntersectPlane(rayOrig, rayDir, s_PlaneOrig[i], s_PlaneNormal[i]);
    pos = rayOrig + tmp*rayDir;

    if (   pos[s_PlaneComp[i][0]] > 0 && pos[s_PlaneComp[i][0]] < 1.0
        && pos[s_PlaneComp[i][1]] > 0 && pos[s_PlaneComp[i][1]] < 1.0)
    {
      if (foundFace < 0 || tmp < t)
      {
        foundFace = i;
        t = tmp;
      }
    }
  }

  if (foundFace < 0) discard;
  

  //--------------------------------------------------
  // Voxel view
  
  int numVoxel = vTextureSize(s_SourceTex, DEBUG_MIP).x;
  
  if (t <= 0) t = 0;
  t += 0.01 / float(numVoxel);
  pos = rayOrig + t*rayDir;

  vec3  voxelPos          = pos * vec3(numVoxel);
  ivec3 voxelPos_Integer  = ivec3(voxelPos);
  
  if ((voxelPos_Integer.x < 0) || (voxelPos_Integer.x >= numVoxel)
      || (voxelPos_Integer.y < 0) || (voxelPos_Integer.y >= numVoxel)
      || (voxelPos_Integer.z < 0) || (voxelPos_Integer.z >= numVoxel)) discard;

  ivec3 step              = ivec3((rayDir.x >= 0) ? 1 : -1, (rayDir.y >= 0) ? 1 : -1, (rayDir.z >= 0) ? 1 : -1);
  vec3  delta             = 1.0 / abs(rayDir);
  vec3  tMax              = vec3(ComputeTmax(voxelPos.x, rayDir.x), ComputeTmax(voxelPos.y, rayDir.y), ComputeTmax(voxelPos.z, rayDir.z));
  
  int   j           = 0;
  float colorFactor = (foundFace < 2) ? 0.4 : ((foundFace < 4) ? 0.7 : 1.0);

  while (j<2000)
  {
    vec3 value = vTexelFetch(s_SourceTex, voxelPos_Integer, DEBUG_MIP).xyz;

#ifdef DEBUG_DIR
#if DEBUG_DIR==0
    value = vec3(value.x);
#elif DEBUG_DIR==1
    value = vec3(value.y);
#else
    value = vec3(value.z);
#endif
#endif

    if ( value.x > cb_VoxelMap_Debug.u_OccRef
      || value.y > cb_VoxelMap_Debug.u_OccRef
      || value.z > cb_VoxelMap_Debug.u_OccRef)
    {
#if DEBUG_COLORMODE==1
      col.xyz = vec3(colorFactor);
#else
      col.xyz = vec3(voxelPos_Integer) / float(numVoxel) * colorFactor;
#endif
      col.w   = 1.0;
      break;
    }
   
    if (tMax.x < tMax.y && tMax.x < tMax.z)
    {
      tMax.x += delta.x;
      voxelPos_Integer.x += step.x;
      colorFactor = 0.4;
    }
    else if (tMax.y < tMax.z && tMax.y < tMax.z)
    {
      tMax.y += delta.y;
      voxelPos_Integer.y += step.y;
      colorFactor = 0.7;
    }
    else
    {
      tMax.z += delta.z;
      voxelPos_Integer.z += step.z;
      colorFactor = 1.0;
    }

    if (   (voxelPos_Integer.x < 0) || (voxelPos_Integer.x >= numVoxel)
        || (voxelPos_Integer.y < 0) || (voxelPos_Integer.y >= numVoxel)
        || (voxelPos_Integer.z < 0) || (voxelPos_Integer.z >= numVoxel)) discard;

    j++;
  }
  

  //--------------------------------------------------
  // zTest with current model

#ifdef DEBUG_ZTEST
  float zRef    = -ConvertZBufferToZView(GetZ(vTexCoord.xy));
  float zVoxel  = (cb_VoxelMap_Debug_Auto.transfoVoxelToView * vec4(vec3(voxelPos_Integer) / float(numVoxel), 1)).z;
  
  if ((zRef - zVoxel) >(4.0 * cb_VoxelMap_Debug_Auto.viewBoundingBox.w/float(numVoxel))) discard;
#endif
  
  col.w *= cb_VoxelMap_Debug.u_DebugAlpha;
  FRAGCOLOR = col;
}
