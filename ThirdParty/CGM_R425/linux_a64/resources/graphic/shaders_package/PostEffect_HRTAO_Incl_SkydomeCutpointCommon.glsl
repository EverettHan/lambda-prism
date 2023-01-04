/*
* Copyright (c) 2017-2022, NVIDIA CORPORATION.  All rights reserved.
*
* NVIDIA CORPORATION and its licensors retain all intellectual property
* and proprietary rights in and to this software, related documentation
* and any modifications thereto.  Any use, reproduction, disclosure or
* distribution of this software and related documentation without an express
* license agreement from NVIDIA CORPORATION is strictly prohibited.
*/

#ifdef __cplusplus
#define uint uint32_t
#endif

#define CUTPOINT_SUBGROUP_SIZE 32
#define CUTPOINT_VISIBILITY_MASK_SIZE 32
#define CUTPOINT_TILING 8

//struct SkydomeCutpointConstants
//{
//  uint hdrEnvSizeX;
//  uint hdrEnvSizeY;
//  uint useMask;
//  uint hdrEnvSizeTotal;
//};

struct SkydomeCutpointMetadata
{
  uint  partitionID;
  float envMapIntegral;
};

struct PrefixSumPartition
{
  uint  status;
  float aggregate;
  float inclusivePrefix;
  uint  pad;
};

const uint PSumInvalid           = 0;
const uint PSumAgregateAvailable = 1;
const uint PSumPrefixAvailable   = 2;

//const uint blockSizeX = 256;
//const uint blockSizeY = 1;

#ifndef M_PI
#define M_PI 3.141592653589
#endif

#ifndef __cplusplus
#ifdef SKYDOME_CUTPOINT_GENERATION
//layout(push_constant) uniform skydomeCutpointConstants
//{
//  SkydomeCutpointConstants c;
//};
//
//
//layout(binding = eHdrEnv, rgba32f, set = 0) uniform image2D hdrEnv;
//layout(binding = ePrefixSumOutput, set = 0, scalar) buffer prefixSumOutputBuffer
//{
//  float prefixSum[];
//};
//layout(binding = ePrefixSumPartitions, set = 0) volatile buffer prefixSumPartitionsBuffer
//{
//  PrefixSumPartition prefixSumPartitions[];
//};
//
//layout(binding = eCutpointMap, set = 0) buffer cutPointBuffer
//{
//  uint startIndices[];
//};
//
//layout(binding = eMetadata, set = 0) buffer metadataBuffer
//{
//  SkydomeCutpointMetadata metadata;
//};
//
//layout(binding = eVisibilityMask, set = 0) buffer visibilityBuffer
//{
//  uint visibility[];
//};

layout(local_size_x = blockSizeX, local_size_y = blockSizeY, local_size_z = 1) in;


uint linearToCutpointIndex(uint index)
{
  return index;
  uint x = index % cb_PostEffect_HRTAO_SkydomeCutpoint.hdrEnvSizeX;
  uint y = index / cb_PostEffect_HRTAO_SkydomeCutpoint.hdrEnvSizeX;

  uint tileIndexX = x / CUTPOINT_TILING;
  uint tileIndexY = y / CUTPOINT_TILING;

  uint indexInTileX = x % CUTPOINT_TILING;
  uint indexInTileY = y % CUTPOINT_TILING;

  uint indexInTile = x + y * CUTPOINT_TILING;

  uint tileCountX = (cb_PostEffect_HRTAO_SkydomeCutpoint.hdrEnvSizeX + CUTPOINT_TILING - 1) / CUTPOINT_TILING;

  uint tileIndex = tileIndexX + tileCountX * tileIndexY;
  return tileIndex * CUTPOINT_TILING * CUTPOINT_TILING + indexInTile;
}

bool hasSampledNeighbor(ivec2 index)
{
  ivec2 index2DInMask = ivec2((index.x + CUTPOINT_VISIBILITY_MASK_SIZE - 1) / CUTPOINT_VISIBILITY_MASK_SIZE,
                              (index.y + CUTPOINT_VISIBILITY_MASK_SIZE - 1) / CUTPOINT_VISIBILITY_MASK_SIZE);

  uint indexInMask =
      index2DInMask.x
      + ((cb_PostEffect_HRTAO_SkydomeCutpoint.hdrEnvSizeX + CUTPOINT_VISIBILITY_MASK_SIZE - 1) / CUTPOINT_VISIBILITY_MASK_SIZE) * index2DInMask.y;

  uint indexInUint = indexInMask % 32;
  uint uintIndex   = indexInMask / 32;
  return (visibility[uintIndex] & (1 << indexInUint)) != 0;
}
#else

uint cutpointToLinearIndex(uint index)
{
  return index;
  uint indexInTile = index % (CUTPOINT_TILING * CUTPOINT_TILING);
  uint tileIndex   = index / (CUTPOINT_TILING * CUTPOINT_TILING);

  ivec2 hdrSize    = ivec2(cb_PostEffect_HRTAO_SkydomeCutpoint.hdrEnvSizeX, cb_PostEffect_HRTAO_SkydomeCutpoint.hdrEnvSizeY);//textureSize(hdrEnv, 0);
  uint  tileCountX = (hdrSize.x + CUTPOINT_TILING - 1) / CUTPOINT_TILING;

  uint tileIndexX = tileIndex % tileCountX;
  uint tileIndexY = tileIndex / tileCountX;

  uint indexInTileX = indexInTile % CUTPOINT_TILING;
  uint indexInTileY = indexInTile / CUTPOINT_TILING;

  uint x = tileIndexX * CUTPOINT_TILING + indexInTileX;
  uint y = tileIndexY * CUTPOINT_TILING + indexInTileY;

  return x + y * hdrSize.x;
}


vec3 environment_sample_cutpoint(vec3 sampleValue)
{
  ivec2 hdrSize    = ivec2(cb_PostEffect_HRTAO_SkydomeCutpoint.hdrEnvSizeX, cb_PostEffect_HRTAO_SkydomeCutpoint.hdrEnvSizeY);//textureSize(hdrEnv, 0);
  uint  pixelCount     = hdrSize.x * hdrSize.y;
  uint  partitionCount = (pixelCount + CUTPOINT_SUBGROUP_SIZE - 1) / CUTPOINT_SUBGROUP_SIZE;  // FIXME
  uint  partitionID    = uint(sampleValue.x * float(partitionCount));

  uint partitionStartIndex     = cutpoints[partitionID];
  uint nextPartitionStartIndex = partitionID == partitionCount ? pixelCount : cutpoints[partitionID + 1];
  uint partitionSize           = nextPartitionStartIndex - partitionStartIndex;
  uint currentIndex            = partitionStartIndex;
  uint currentSize             = partitionSize / 2;

#if 1
  currentIndex += currentSize;
  while(currentSize > 0)
  {
    currentSize /= 2;
    if(cutpointsCdf[currentIndex] > sampleValue.x)
      currentIndex -= currentSize;
    else
      currentIndex += currentSize;
  }

#else
  float partitionValue  = float(partitionID) / float(partitionCount);
  float partitionExtent = 1.f / float(partitionCount);
  sampleValue.x         = (sampleValue.x - partitionValue) / partitionExtent;
  currentIndex += uint(sampleValue.x * partitionSize);
#endif

  currentIndex = cutpointToLinearIndex(currentIndex);

  uint       width  = hdrSize.x;
  uint       height = hdrSize.y;
  uint       py     = currentIndex / width;
  const uint px     = currentIndex % width;

  //py = height - py - 1;  // Image is upside down


  // uniformly sample spherical area of pixel
  const float u       = float(px + sampleValue.y) / float(width);
  const float phi     = u * (2.0f * M_PI) - M_PI;
  float       sin_phi = sin(phi);
  float       cos_phi = cos(phi);

  const float step_theta = M_PI / float(height);
  const float theta0     = float(py) * step_theta;
  const float cos_theta  = cos(theta0) * (1.0f - sampleValue.z) + cos(theta0 + step_theta) * sampleValue.z;
  const float theta      = acos(cos_theta);
  const float sin_theta  = sin(theta);
  //return vec3(cos_phi * sin_theta, -cos_theta, sin_phi * sin_theta);

  vec3 to_light               = vec3(cos_phi * sin_theta, cos_theta, sin_phi * sin_theta);
  
  to_light = vec3(to_light.z, to_light.x, -to_light.y);


  //return vec3(cos_phi * sin_theta, sin_phi * sin_theta, cos_theta);

  /*
  
  float theta = acos(v.z);
  float phi = atan(v.x, v.y);

  return vec2(phi * ONE_OVER_PI * 0.5 + 0.5, 1.0 - theta * ONE_OVER_PI);

  */

  return to_light;
}

void updateVisibilityMask(ivec2 index)
{
  ivec2 hdrSize    = ivec2(cb_PostEffect_HRTAO_SkydomeCutpoint.hdrEnvSizeX, cb_PostEffect_HRTAO_SkydomeCutpoint.hdrEnvSizeY);//textureSize(hdrEnv, 0);
  ivec2 index2DInMask = ivec2((index.x + CUTPOINT_VISIBILITY_MASK_SIZE - 1) / CUTPOINT_VISIBILITY_MASK_SIZE,
                              (index.y + CUTPOINT_VISIBILITY_MASK_SIZE - 1) / CUTPOINT_VISIBILITY_MASK_SIZE);

  uint indexInMask = index2DInMask.x
                     + ((hdrSize.x + CUTPOINT_VISIBILITY_MASK_SIZE - 1) / CUTPOINT_VISIBILITY_MASK_SIZE) * index2DInMask.y;
  //visibility[indexInMask] = 1;
  uint indexInUint = indexInMask % 32;
  uint uintIndex   = indexInMask / 32;
  atomicOr(visibility[uintIndex], 1 << indexInUint);
}

#endif  // SKYDOME_CUTPOINT_GENERATION


#endif
