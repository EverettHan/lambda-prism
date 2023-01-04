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


float computeImportance(ivec2 index)
{
  vec4 hdrVal = imageLoad(hdrEnv, ivec2(index));

  const float step_phi   = float(2.0 * M_PI) / float(cb_PostEffect_HRTAO_SkydomeCutpoint.hdrEnvSizeX);
  const float step_theta = float(M_PI) / float(cb_PostEffect_HRTAO_SkydomeCutpoint.hdrEnvSizeY);

  const float theta0     = float(index.y) * step_theta;
  const float cos_theta0 = cos(theta0);


  const float theta1     = float(index.y + 1) * step_theta;
  const float cos_theta1 = cos(theta1);


  const float area = (cos_theta0 - cos_theta1) * step_phi;

  float envLuminance = max(hdrVal.x, max(hdrVal.y, hdrVal.z));

  // Always keep at least one section marked visible to avoid the corner 
  // case where all pixels are masked out
  if(index != ivec2(0) && cb_PostEffect_HRTAO_SkydomeCutpoint.useMask == 1 && !hasSampledNeighbor(index))
    envLuminance = 0.f;


  float importanceValue = area * envLuminance;

  return importanceValue;
}

// Compute the envmap integral and store importance values per texel
void main()
{
  uint index      = uint(gl_GlobalInvocationID.x);
  uint pixelCount = cb_PostEffect_HRTAO_SkydomeCutpoint.hdrEnvSizeX * cb_PostEffect_HRTAO_SkydomeCutpoint.hdrEnvSizeY;

  if(index >= pixelCount)
    return;

  ivec2 index2D = ivec2(index % cb_PostEffect_HRTAO_SkydomeCutpoint.hdrEnvSizeX, index / cb_PostEffect_HRTAO_SkydomeCutpoint.hdrEnvSizeX);

  float importanceValue = computeImportance(index2D);

  subgroupBarrier();

  float subgroupSum = subgroupAdd(importanceValue);
  if(gl_SubgroupInvocationID == 0)
    atomicAdd(metadata.envMapIntegral, subgroupSum);

  uint cutpointIndex       = linearToCutpointIndex(index);
  prefixSum[cutpointIndex] = importanceValue;
}
