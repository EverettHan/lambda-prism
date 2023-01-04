layout(location = 0) rayPayloadEXT D_PAYLOAD_DECLARATION;

float ComputeAORadius(vec3 origin, vec3 direction)
{
  vec4 clipPlaneInView = _sbCbGlobalClipping.clipPlanes[0];

  if(all(equal(clipPlaneInView, vec4(0))))
     return cb_PostEffect_RT_AO.u_AoRadius;

  vec4 originView      = _sbCbCamera.ViewMatrix * vec4(origin, 1);
  vec4 directionView   = _sbCbCamera.ViewMatrix * vec4(direction, 0);

  float dotPlanePos = dot(clipPlaneInView, vec4( originView.xyz, 1));
  float dotPlaneDir = dot(clipPlaneInView.xyz, normalize(directionView.xyz));
  
  float distanceToPlane = -  dotPlanePos / dotPlaneDir;
  
  float aoRadius;

  if(distanceToPlane < 0)
    aoRadius = cb_PostEffect_RT_AO.u_AoRadius;
  else
    aoRadius = vMin(distanceToPlane, cb_PostEffect_RT_AO.u_AoRadius);

  return aoRadius;
}


#ifdef D_HRTAO

#ifdef IS_MSAA
  #define UIMAGE2D uimage2DMS
  #define TEXTURE2D texture2DMS
  #define UTEXTURE2D utexture2DMS
#else
  #define UIMAGE2D uimage2D
  #define TEXTURE2D texture2D
  #define UTEXTURE2D utexture2D
#endif

//layout(set = eBindPoint_MaterialResources, binding = 0, r32ui) uniform UIMAGE2D changeList;
//layout(set = eBindPoint_MaterialResources, binding = 1) uniform accelerationStructureNV TopLevelAS;
//layout(set = eBindPoint_MaterialResources, binding = 2) buffer hashMapBuffer { HashRecordContrib hashMap[]; };
//layout(set = eBindPoint_MaterialResources, binding = 3) uniform TEXTURE2D positions;
//layout(set = eBindPoint_MaterialResources, binding = 4) uniform UTEXTURE2D cellIndices;

#define PI 3.1415926538

vec3 Tangent2World(vec3 iTS, vec3 iNormal)
{
  vec3 res;

  vec3 up = abs(iNormal.z) < 0.9999 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);
  vec3 tX = normalize(cross(up, iNormal));
  vec3 tY = normalize(cross(iNormal, tX));

  res.x = tX.x*iTS.x + tY.x*iTS.y + iNormal.x*iTS.z;
  res.y = tX.y*iTS.x + tY.y*iTS.y + iNormal.y*iTS.z;
  res.z = tX.z*iTS.x + tY.z*iTS.y + iNormal.z*iTS.z;

  return res;
}

uint getPixelsToUpdate() { return hashMap[cb_PostEffect_RT_AO.u_HashTableSize].contribWeight; }

void compute_default_basis(const vec3 normal, out vec3 x, out vec3 y,
  out vec3 z) {
  // ZAP's default coordinate system for compatibility
  z = normal;
  const float yz = -z.y * z.z;
  y = normalize(((abs(z.z) > 0.99999f)
    ? vec3(-z.x * z.y, 1.0f - z.y * z.y, yz)
    : vec3(-z.x * z.z, yz, 1.0f - z.z * z.z)));

  x = cross(y, z);
}

void StoreInChangeList(in uvec4 iValue)
{
#ifdef IS_MSAA
  imageStore(changeList, ivec2(vGetLaunchID().xy), int(vGetLaunchID().z), iValue);
#else
  imageStore(changeList, ivec2(vGetLaunchID().xy), iValue);
#endif
}

void main()
{
  ivec2 texIndex = ivec2(vGetLaunchID().xy);

  #ifdef IS_MSAA
    uvec4 cellIds = texelFetch(cellIndices, texIndex, int(vGetLaunchID().z));
  #else
    uvec4 cellIds = texelFetch(cellIndices, texIndex, 0);
  #endif

  uint cellId = cellIds.x;

  if (cellId == HASH_CELL_NOT_FOUND)
  {
    StoreInChangeList(uvec4(0));
    return;
  }

  uint weight = getWeight(hashMap[cellId].contribWeight);
  if (weight > cb_PostEffect_RT_AO.u_MaxSamplesPerCell)
  {
    StoreInChangeList(uvec4(0));
    return;
  }

  uint occlusion = 0;
  // Lookup Gbuffer data
#ifdef IS_MSAA
  vec4 pos4 = texelFetch(positions, texIndex, int(vGetLaunchID().z));
#else
  vec4 pos4 = texelFetch(positions, texIndex, 0);
#endif

  vec3 pos = pos4.xyz;
  vec3 normal = decompress_unit_vec(floatBitsToUint(pos4.w));


  // Move origin slightly away from the surface to avoid self-occlusion
  float posOffset = getFeatureSizeInWorldUnits(length(pos - _sbCbCamera.EyeWorldPos), 1, 1e-10, 0);
  const vec3 origin = pos + normalize(normal) * posOffset*0.1;

  uint pixelsToUpdate = getPixelsToUpdate();
  uint totalPixels = vGetLaunchSize().x * vGetLaunchSize().y * vGetLaunchSize().z;

  uint samples = min(10, min(cb_PostEffect_RT_AO.u_MaxSamplesPerCell / 10, int(float(cb_PostEffect_RT_AO.u_RayBudgetPerPixel) * float(totalPixels) / float(pixelsToUpdate))));

  if (samples == 0)
  {
    float s = radinv_fl(hashPointLODOffset(pos, normal, 0, 0) + getFrameId(cb_PostEffect_RT_AO_Auto.u_FrameIdx), 4);
    if (s < cb_PostEffect_RT_AO.u_RayBudgetPerPixel || getWeight(hashMap[cellId].contribWeight) == 0)
      samples = 1;
    else
    {
      StoreInChangeList(uvec4(0));
      return;
    }
  }

  vec3 x, y, z;
  compute_default_basis(normal, x, y, z);

  uint existingSampleCount = atomicAdd(hashMap[cellId].contribWeight, samples << 16);

  uint seed = checksumLODOffset(pos, normal, 0) + getWeight(existingSampleCount);

  for (float i = 0; i < samples; i++)
  {
    float r1 = 2 * PI * radinv_fl(seed, 2);
    float r2 = radinv_fl(seed, 3);

    seed++;

    float sq = sqrt(1.0 - r2);

    vec3 direction = vec3(cos(r1) * sq, sin(r1) * sq, sqrt(r2));
    direction = direction.x * x + direction.y * y + direction.z * z;

    g_HitValue = 0.0;

    float aoRadius = ComputeAORadius(origin, direction);

    traceRayEXT(TopLevelAS, gl_RayFlagsOpaqueEXT | gl_RayFlagsTerminateOnFirstHitEXT, 0xff, 0, 1, 0, origin, 0.0, direction, aoRadius, 0);

    occlusion += (g_HitValue != 0.0) ? 1 : 0;
  }

  uint contribution = samples - occlusion;

  atomicAdd(hashMap[cellId].contribWeight, contribution);
  contribution += (samples << 16);
  StoreInChangeList(uvec4(contribution));
}

#else

layout(set = eBindPoint_MaterialResources, binding = 0, r8) uniform image2D RaytraceOutput;
layout(set = eBindPoint_MaterialResources, binding = 1) uniform accelerationStructureNV TopLevelAS;
#ifdef IS_MSAA
layout(set = eBindPoint_MaterialResources, binding = 2) uniform texture2DMS RaytraceNormalMap;
layout(set = eBindPoint_MaterialResources, binding = 3) uniform texture2DMS RaytraceZMap;
layout(set = eBindPoint_MaterialResources, binding = 4) uniform texture2DMS RaytraceWorldPosMap;

vec4 ResolveDepthAndNormal(ivec2 iTexIndex)
{
  vec4 result = vec4(0.0, 0.0, 0.0, 1.0);

  for (int i = 0; i < IS_MSAA; ++i)
  {
    float d = texelFetch(RaytraceZMap, iTexIndex, i).r;
    result.w = min(result.w, d);
    if(d != 1.0)
      result.xyz += texelFetch(RaytraceNormalMap, iTexIndex, i).xyz*2.0-1.0;
  }

  result.xyz = normalize(result.xyz);

  return result;
}

#else
layout(set = eBindPoint_MaterialResources, binding = 2) uniform texture2D RaytraceNormalMap;
layout(set = eBindPoint_MaterialResources, binding = 3) uniform texture2D RaytraceZMap;
layout(set = eBindPoint_MaterialResources, binding = 4) uniform texture2D RaytraceWorldPosMap;

vec4 ResolveDepthAndNormal(ivec2 iTexIndex)
{
  vec4 result = vec4(0.0, 0.0, 0.0, 1.0);

  result.xyz = texelFetch(RaytraceNormalMap, iTexIndex, 0).xyz * 2.0 - 1.0;
  result.w = texelFetch(RaytraceZMap, iTexIndex, 0).r;

  return result;
}
#endif

#define PI 3.1415926538

vec3 Tangent2World(vec3 iTS, vec3 iNormal)
{
  vec3 res;

  vec3 up = abs(iNormal.z) < 0.9999 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);
  vec3 tX = normalize(cross(up, iNormal));
  vec3 tY = normalize(cross(iNormal, tX));

  res.x = tX.x*iTS.x + tY.x*iTS.y + iNormal.x*iTS.z;
  res.y = tX.y*iTS.x + tY.y*iTS.y + iNormal.y*iTS.z;
  res.z = tX.z*iTS.x + tY.z*iTS.y + iNormal.z*iTS.z;

  return res;
}

void main()
{
  ivec2 texIndex = ivec2(gl_LaunchIDNV.xy);

  vec4 depthAndNormal = ResolveDepthAndNormal(texIndex);

  float depth = depthAndNormal.w;

 //// Miss?
 if (depth >= 1.0)
 {
   imageStore(RaytraceOutput, texIndex, vec4(1.0));
   return;
 }

#ifdef UseWorldPos
  vec4 tex = texelFetch(RaytraceWorldPosMap, texIndex, 0);
  vec3 normal = decompress_unit_vec(floatBitsToUint(tex.w));
  vec3 worldSpacePos = tex.xyz;
#else
  vec3 normal = depthAndNormal.xyz;
  normal = normalize((_sbCbCamera.ViewInverseMatrix * vec4(normal, 0.0)).xyz);
  const vec2 pixelCenter = vec2(vGetLaunchID().xy) + vec2(0.5);
  const vec2 inUV = pixelCenter / vec2(vGetLaunchSize().xy);
  vec2 d = inUV * 2.0 - 1.0;
  depth = depth*2.0 - 1.0;
  float ze = (_sbCbCamera.ProjectionRatio.y / (depth - _sbCbCamera.ProjectionRatio.x));
  vec4 viewPos = _sbCbCamera.ProjInverseMatrix * (vec4(d, depth, 1.0) * ze);
  vec3 worldSpacePos = vec3(_sbCbCamera.ViewInverseMatrix * viewPos);
#endif

  worldSpacePos = offset_ray(worldSpacePos, normal);

  float tmin = 0.0f;
  float tmax = cb_PostEffect_RT_AO.u_AoRadius;
  float occlusion = 0.0;

  int seed = encrypt_tea(915927258, 1547188273, ivec4(texIndex, 0, 0), 6);

  for (int x = 0; x < D_NUM_AO_SAMPLE; ++x)
  {
    vec2 sampleDir = generate_sample2d(seed);

    vec3 dir;
    float u1 = sampleDir.x;
    float u2 = sampleDir.y;
    float r = sqrt(u1);
    float phi = u2 * PI * 2.0;
    dir.x = r*cos(phi);
    dir.y = r*sin(phi);
    dir.z = sqrt(max(0.0, 1.0 - u1));
    dir = Tangent2World(dir, normal);

    float aoRadius = ComputeAORadius(worldSpacePos, dir);

    traceRayEXT(TopLevelAS, gl_RayFlagsOpaqueEXT | gl_RayFlagsCullBackFacingTrianglesEXT | gl_RayFlagsTerminateOnFirstHitEXT, 0xff, 0, 1, 0, worldSpacePos, tmin, dir, aoRadius, 0);

    //float occ = g_HitValue / cb_PostEffect_RT_AO.u_AoRadius;
    if (g_HitValue > 0.0)
      occlusion += 1.0;
  }
  
  occlusion /= float(D_NUM_AO_SAMPLE);

  occlusion = pow(clamp(1.0-occlusion, 0.0, 1.0), cb_PostEffect_RT_AO.u_AoPower);

  imageStore(RaytraceOutput, texIndex, vec4(occlusion));
}

#endif
