/* Copyright (c) 2019, NVIDIA CORPORATION. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of NVIDIA CORPORATION nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

 // Main raytracing shader, tracing rays and storing the results in the hash map and/or changelist

//#version 460
//#extension GL_NV_ray_tracing : require
//#extension GL_GOOGLE_include_directive : enable
//#extension GL_KHR_shader_subgroup_ballot: enable
//#extension GL_EXT_gpu_shader5 : enable
//#extension GL_EXT_shader_16bit_storage : enable
//#extension GL_EXT_shader_explicit_arithmetic_types_int16 : enable
//#extension GL_EXT_shader_explicit_arithmetic_types_float16 : enable


//const float PI = 3.141592653589;

#define RTAO_RADIUS cb_PostEffect_HRTAO.aoRadius
#define RTAO_POWER 1.0

//#include "../bindings/raytracing_bindings.h"

//#include "common.h"
// GBuffer world-space positions, plus normals encoded in the W component
//layout(binding = eGBuffer, rg32f, set = 0) uniform image2D positionNormals;
//#define HRTAO_GBUFFER_FETCH
//#include "common_spatial_hash.h"
//#include "hash_data_type_color.h"



// Prime and permutations table for radinv_fl
//layout(binding = ePrimePerm, set=0) uniform primePermB
//{
//  uint val[360];
//} primePermBuffer
//;

//#include "sampling.h"


// Acceleration structure for raytracing
//layout(binding = eTopLevelAS, set = 0) uniform accelerationStructureNV topLevelAS;
// Change list storing the raytracing result: for each pixel, the change list stores a uvec4, for which each
// component contains a number of occlusions (16bit) and number of rays traced for a particular LOD (16bit)
//layout(binding = eRaytracingOutput, set = 0) buffer changeListBuffer { HASH_CHANGE_LIST_BASE_TYPE changeList[]; };

// Hash map contributions, containing the number of rays traced for that cell (16 bit, weight) and number of occlusions found (16 bit, contribution)
//layout(binding = eHashMapContribs) buffer hashMapBuffer { HashRecordContrib hashMap[]; };

// Hash map contributions, containing the number of rays traced for that cell (16 bit, weight) and number of occlusions found (16 bit, contribution)
//layout(binding = eHashMapKeys) buffer hashMapBufferKey { HashRecordKey hashMapKeys[]; };


// Hash cell indices, one LOD per component
//layout(binding = eCellId, set=0) uniform usampler2D cellIndices;

//layout(binding = eHdrEnv, set=0) uniform sampler2D hdrEnv;

//layout(binding = eTouchedCells) buffer touchedCellsBuffer { uint touchedCells[]; };

// Ray payload, which will be set to false if no geometry is hit
layout(location = 0) rayPayloadEXT bool isHit;

//#include "hash_key_access.h"
//#include "hash_data_access_color.h"
//#include "skydome_eval.h"


void storeChangeListItem(uint index, HashRecordContrib contribution, uint prev, uint pixelId)
{
  SET_CL_ITEM(changeList, index, makeChangeListItem(contribution, prev, pixelId));
}



uint reserveChangeListItem()
{
  return RESERVE_CL_ITEM;
}


// Get the number of pixels requiring new rays to be traced. This will be used to 
// compute the ray budget 
//uint getPixelsToUpdate() { return getWeight(hashMap[hashTableSize]); }

// Generate an arbitrary orthonormal basis from a normal vector
void compute_default_basis(const vec3 normal, out vec3 x, out vec3 y,
                           out vec3 z) {
  z = normal;
  const float yz = -z.y * z.z;
  y = normalize(((abs(z.z) > 0.99999f)
                     ? vec3(-z.x * z.y, 1.0f - z.y * z.y, yz)
                     : vec3(-z.x * z.z, yz, 1.0f - z.z * z.z)));

  x = cross(y, z);
}

void main() {


  uvec3 launchSize = vGetLaunchSize();
  uvec3 launchID = vGetLaunchID();

  // Fetch the cell ID at the finest level for that pixel. If not found, we know 
  // there is nothing to do
  #ifdef IS_MSAA
    uvec4 cellIds = texelFetch(cellIndices, ivec2(launchID.xy), int(launchID.z));
  #else
    uvec4 cellIds = texelFetch(cellIndices, ivec2(launchID.xy), 0);
  #endif
  uint cellId = cellIds.x;
  if (cellId == HASH_CELL_NOT_FOUND)
  {
    return;
  }
  // If the cell contains more than the target number of samples
  // there is nothing to do either
  uint weight = getWeight(hashMap[cellId]);
  
  if (weight > cb_PostEffect_HRTAO.maxSamplesPerCell) 
  {
    return;
  } 
  
  uint occlusion = 0;
  // Lookup Gbuffer data

  uint pxId = getCellPixel(cellId);
  int smp = int(pxId/(resX*resY));
  pxId = pxId % (resX*resY);
  ivec2 pxCoord = ivec2(pxId % resX, pxId / resX);
  vec3 pos, normal;
  //if (getFrameId(frameIdx) != 0)
  {
  #ifdef IS_MSAA
    pos = getPosition( ivec2(launchID.xy), int(launchID.z));
    normal = getNormal(ivec2(launchID.xy), int(launchID.z));
  #else
    pos = getPosition( ivec2(launchID.xy));
    normal = getNormal(ivec2(launchID.xy));
  #endif
  }


  // Move origin slightly away from the surface to avoid self-occlusion
  float posOffset = 4*getFeatureSizeInWorldUnits(length(pos - vec3(vpX, vpY, vpZ)), 1, 1e-10, 0);
  const vec3 origin = pos + normal * posOffset; 

  uint pixelsToUpdate = getPixelsToUpdate();
  #ifdef IS_MSAA
  uint totalPixels = launchSize.x * launchSize.y * launchSize.z;
  #else
  uint totalPixels = launchSize.x * launchSize.y;
  #endif

  uint samples = int(cb_PostEffect_HRTAO.rayBudgetPerPixel); 

  uint pixelsInACell = uint(cb_PostEffect_HRTAO.cellSizeInPixels * cb_PostEffect_HRTAO.cellSizeInPixels);
  HashRecordContrib contribForCount = hashMap[cellId];
 uint sampleLimit = uint(max(0, int(cb_PostEffect_HRTAO.maxSamplesPerCell) - int(getWeight(contribForCount))));
  uint maxRayBudget = sampleLimit / pixelsInACell;
  samples = min(samples, maxRayBudget);


  if (samples == 0)
  {
    float s = radinv_fl(hashPointLODOffset(pos, 0, 0, 0)+getFrameId(cb_PostEffect_HRTAO_Auto.frameIdx), 4);  
    if (s < cb_PostEffect_HRTAO.rayBudgetPerPixel || getWeight(hashMap[cellId]) == 0)
      samples = 1;
    else
    {
      return;
    }
  }
  
  vec3 x, y, z;
  compute_default_basis(normal, x, y, z);

  
  uint existingSampleCount = addSamples(cellId, samples); 
  
  uint seed = checksumLODOffset(pos, 0, 0) + existingSampleCount;
  
  for (uint i = 0; i < samples; i++) 
  {
  
    float r1 = 2 * PI * radinv_fl(seed, 2);
  
    float r2 = radinv_fl(seed, 3);
    
    seed++;

    float sq = sqrt(1.0 - r2);

    vec3 direction = vec3(cos(r1) * sq, sin(r1) * sq, sqrt(r2));
    direction = direction.x * x + direction.y * y + direction.z * z;
  
    isHit = true;


    uint mask = 0xFF;
    
    traceRayEXT(topLevelAS, gl_RayFlagsOpaqueEXT | gl_RayFlagsTerminateOnFirstHitEXT | gl_RayFlagsSkipClosestHitShaderEXT, mask/*0xFF*/, 0, 1, 0, origin, 0.0, direction, RTAO_RADIUS, 0);

    occlusion += isHit?1:0;


  }

  uint contribution = samples - occlusion;

  #ifdef IS_MSAA
    uint pixelId = launchSize.x*launchSize.y*launchID.z + launchSize.x*launchID.y + launchID.x;
  #else
    uint pixelId = launchSize.x*launchID.y + launchID.x;
  #endif

  uint clItemIndex = reserveChangeListItem();


  bool newlyTouched = false;
  uint previousChangeToCell = setLastPixel(clItemIndex, cellId, newlyTouched);

  if (newlyTouched)
  {
    uint touchedCellIndex = atomicAdd(touchedCells[launchSize.x*launchSize.y*launchSize.z], 1);
    touchedCells[touchedCellIndex] = cellId;
  }

  HashRecordContrib contrib = makeContrib(contribution, samples);
  
  storeChangeListItem(clItemIndex, contrib, previousChangeToCell, pixelId);   
}
