/*
* Copyright (c) 2017-2022, NVIDIA CORPORATION.  All rights reserved.
*
* NVIDIA CORPORATION and its licensors retain all intellectual property
* and proprietary rights in and to this software, related documentation
* and any modifications thereto.  Any use, reproduction, disclosure or
* distribution of this software and related documentation without an express
* license agreement from NVIDIA CORPORATION is strictly prohibited.
*/

//#version 460
//#extension GL_GOOGLE_include_directive : enable
//#extension GL_EXT_shader_atomic_float : enable
//#extension GL_KHR_shader_subgroup_arithmetic : enable
//#extension GL_KHR_shader_subgroup_ballot : enable
//
//#extension GL_EXT_scalar_block_layout : enable
//
//#include "../bindings/skydome_cutpoint_bindings.h"
//#define SKYDOME_CUTPOINT_GENERATION
//#include "skydome_cutpoint_common.h"

// Compute the CDF using per-texel importance values
// Parallel prefix sum - https://developer.nvidia.com/gpugems/gpugems3/part-vi-gpu-computing/chapter-39-parallel-prefix-sum-scan-cuda
void main()
{
  uint index = atomicAdd(metadata.partitionID, 1);

  float importance = 0.f;

  uint pixelCount     = cb_PostEffect_HRTAO_SkydomeCutpoint.hdrEnvSizeX * cb_PostEffect_HRTAO_SkydomeCutpoint.hdrEnvSizeY;
  uint partitionCount = (pixelCount + CUTPOINT_SUBGROUP_SIZE - 1) / CUTPOINT_SUBGROUP_SIZE;

  if(index >= partitionCount)
    return;

  uint partitionBegin = index * CUTPOINT_SUBGROUP_SIZE;
  uint partitionEnd   = min(pixelCount, partitionBegin + CUTPOINT_SUBGROUP_SIZE);

  float aggregate = 0.f;
  for(uint i = partitionBegin; i < partitionEnd; i++)
  {

    ivec2 index2D = ivec2(i % cb_PostEffect_HRTAO_SkydomeCutpoint.hdrEnvSizeX, i / cb_PostEffect_HRTAO_SkydomeCutpoint.hdrEnvSizeX);
    aggregate += prefixSum[i] / metadata.envMapIntegral;
  }


  float exclusivePrefix                = 0.f;
  prefixSumPartitions[index].aggregate = aggregate;
  prefixSumPartitions[index].status    = PSumAgregateAvailable;

  if(index != 0)
  {
    uint previousPartitionIndex = index - 1;

    bool isFinished = false;
    while(!isFinished)
    {
      switch(prefixSumPartitions[previousPartitionIndex].status)
      {
        case PSumAgregateAvailable:
          exclusivePrefix += prefixSumPartitions[previousPartitionIndex].aggregate;
          if(previousPartitionIndex == 0)
            isFinished = true;
          else
            previousPartitionIndex--;
          break;
        case PSumPrefixAvailable:
          exclusivePrefix += prefixSumPartitions[previousPartitionIndex].inclusivePrefix;
          isFinished = true;
          break;
        case PSumInvalid:
        default:
          break;
      }
    }
  }

  prefixSumPartitions[index].inclusivePrefix = exclusivePrefix + aggregate;
  prefixSumPartitions[index].status          = PSumPrefixAvailable;

  float localPrefixSum = 0.f;
  for(uint i = partitionBegin; i < partitionEnd; i++)
  {
    ivec2 index2D = ivec2(i % cb_PostEffect_HRTAO_SkydomeCutpoint.hdrEnvSizeX, i / cb_PostEffect_HRTAO_SkydomeCutpoint.hdrEnvSizeX);
    localPrefixSum += prefixSum[i] / metadata.envMapIntegral;
    prefixSum[i] = localPrefixSum + exclusivePrefix;
  }
}
