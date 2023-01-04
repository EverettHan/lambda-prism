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
//#extension GL_EXT_scalar_block_layout : enable
//
//#include "../bindings/skydome_cutpoint_bindings.h"
//#define SKYDOME_CUTPOINT_GENERATION
//#include "skydome_cutpoint_common.h"

// Finalize the partitions for the cutpoint method
void main()
{
  uint index = uint(gl_GlobalInvocationID.x);

  uint pixelCount     = cb_PostEffect_HRTAO_SkydomeCutpoint.hdrEnvSizeX * cb_PostEffect_HRTAO_SkydomeCutpoint.hdrEnvSizeY;
  uint partitionCount = (pixelCount + CUTPOINT_SUBGROUP_SIZE - 1) / CUTPOINT_SUBGROUP_SIZE;

  if(index >= partitionCount)
    return;

  float minValue = float(index) / float(partitionCount);


  // Binary search for index
  if(index == 0)
  {
    startIndices[0] = 0;
    return;
  }


  uint currentIndex = 0;
  uint currentSize  = pixelCount / 2;
  currentIndex += currentSize;
  while(currentSize > 0)
  {
    currentSize /= 2;
    if(prefixSum[currentIndex] > minValue)
      currentIndex -= currentSize;
    else
      currentIndex += currentSize;
  }


  startIndices[index] = currentIndex;

  uint minIndex = index * CUTPOINT_SUBGROUP_SIZE;
  uint maxIndex = min(minIndex + CUTPOINT_SUBGROUP_SIZE, pixelCount);

  for(uint i = minIndex; i < maxIndex; i++)
  {
    uint x           = i % cb_PostEffect_HRTAO_SkydomeCutpoint.hdrEnvSizeX;
    uint y           = i / cb_PostEffect_HRTAO_SkydomeCutpoint.hdrEnvSizeX;
    vec4 hdrEnvValue = imageLoad(hdrEnv, ivec2(x, y));

    float envLuminance = max(hdrEnvValue.x, max(hdrEnvValue.y, hdrEnvValue.z));

    if(!(x==0 && y == 0) && cb_PostEffect_HRTAO_SkydomeCutpoint.useMask == 1 && !hasSampledNeighbor(ivec2(x, y)))
      envLuminance = 0.f;


    float probability = envLuminance / metadata.envMapIntegral;

    imageStore(hdrEnv, ivec2(x, y), vec4(hdrEnvValue.xyz, probability));
  }
}
