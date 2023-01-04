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

layout(location = 0) rayPayloadEXT Payload_t g_Payload;

//#include "hash_key_access.h"
//#include "hash_data_access_color.h"
//#include "skydome_eval.h"

//values taken from lightingAdvanced.glsl
#define AmbientOcclusionType -1
#define SphereAreaType 0
#define TubeAreaType 1
#define DiskAreaType 2
#define RectangleAreaType 3

// Optimal sampling of rectangle area light source
// https://www.arnoldrenderer.com/research/egsr2013_spherical_rectangle.pdf

const float eps = 1e-5; 

struct SphQuad
{
  vec3 o, x, y, z; // local reference system ’R’
  float z0, z0sq; //
  float x0, y0, y0sq; // rectangle coords in ’R’
  float x1, y1, y1sq; //
  float b0, b1, b0sq, k; // misc precomputed constants
  float S; // solid angle of ’Q’
};

void SphQuadInit(out SphQuad squad, in vec3 s, in vec3 ex, in vec3 ey, in vec3 o)
{
  squad.o = o;
  float exl = length(ex), eyl = length(ey);
  // compute local reference system ’R’
  squad.x = ex / exl;
  squad.y = ey / eyl;
  squad.z = cross(squad.x, squad.y);
  // compute rectangle coords in local reference system
  vec3 d = s - o;
  squad.z0 = dot(d, squad.z);
  // flip ’z’ to make it point against ’Q’
  if (squad.z0 > 0) {
  squad.z *= -1;
  squad.z0 *= -1;
  }
  squad.z0sq = squad.z0 * squad.z0;
  squad.x0 = dot(d, squad.x);
  squad.y0 = dot(d, squad.y);
  squad.x1 = squad.x0 + exl;
  squad.y1 = squad.y0 + eyl;
  squad.y0sq = squad.y0 * squad.y0;
  squad.y1sq = squad.y1 * squad.y1;
  // create vectors to four vertices
  vec3 v00 = {squad.x0, squad.y0, squad.z0};
  vec3 v01 = {squad.x0, squad.y1, squad.z0};
  vec3 v10 = {squad.x1, squad.y0, squad.z0};
  vec3 v11 = {squad.x1, squad.y1, squad.z0};
  // compute normals to edges
  vec3 n0 = normalize(cross(v00, v10));
  vec3 n1 = normalize(cross(v10, v11));
  vec3 n2 = normalize(cross(v11, v01));
  vec3 n3 = normalize(cross(v01, v00));
  // compute internal angles (gamma_i)
  float g0 = acos(-dot(n0,n1));
  float g1 = acos(-dot(n1,n2));
  float g2 = acos(-dot(n2,n3));
  float g3 = acos(-dot(n3,n0));
  // compute predefined constants
  squad.b0 = n0.z;
  squad.b1 = n2.z;
  squad.b0sq = squad.b0 * squad.b0;
  squad.k = 2*PI - g2 - g3;
  // compute solid angle from internal angles
  squad.S = g0 + g1 - squad.k;
}

vec3 SphQuadSample(in SphQuad squad, in float u, in float v)
{
  // 1. compute ’cu’
  float au = u * squad.S + squad.k;
  float fu = (cos(au) * squad.b0 - squad.b1) / sin(au);
  float cu = 1/sqrt(fu*fu + squad.b0sq) * (fu>0 ? +1 : -1);
  cu = clamp(cu, -1, 1); // avoid NaNs
  // 2. compute ’xu’
  float xu = -(cu * squad.z0) / sqrt(1 - cu*cu);
  xu = clamp(xu, squad.x0, squad.x1); // avoid Infs
  // 3. compute ’yv’
  float d = sqrt(xu*xu + squad.z0sq);
  float h0 = squad.y0 / sqrt(d*d + squad.y0sq);
  float h1 = squad.y1 / sqrt(d*d + squad.y1sq);
  float hv = h0 + v * (h1-h0), hv2 = hv*hv;
  float yv = (hv2 < 1-eps) ? (hv*d)/sqrt(1-hv2) : squad.y1;
  // 4. transform (xu,yv,z0) to world coords
  return (squad.o + xu*squad.x + yv*squad.y + squad.z0*squad.z);
}

// uniform sampling on disk
// u: 1st rand value 0-1
// v: 2nd rand value 0-1

struct DiskLight
{
  vec3 c, u, s; // local reference system center, normal, up, side vectors
  float r; // radius
};

vec3 DiskSample(in DiskLight l, in float u, in float v)
{
  float theta = u * 2.0 * PI;
  float d = sqrt(v);
  float x = l.r * d * cos(theta);
  float y = l.r * d * sin(theta);
  return x * l.s + y * l.u + l.c;
}

#if HASH_SLOT_COUNT > 1
  void storeChangeListItem(uint index, HashRecordContrib contribution, uint slot, uint prev, uint pixelId)
  {
    SET_CL_ITEM(changeList, index, makeChangeListItem(contribution, slot, prev, pixelId));
  }
#else
  void storeChangeListItem(uint index, HashRecordContrib contribution, uint prev, uint pixelId)
  {
    SET_CL_ITEM(changeList, index, makeChangeListItem(contribution, prev, pixelId));
  }
#endif

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

vec3 getGeomT(in vec3 N) 
{
	vec3 normN = N;
	float x = normN.x;
	float y = normN.y;
	float z = normN.z;

	vec3 T = vec3(0.0);

	if (abs(z) > 0.0)
  {
		T.y += 0.0;
		T.x += 1.0;
		T.z += -x / z;
		return normalize(T);
	}

	if (abs(y) > 0.0)
  {
		T.x += 0.0;
		T.z += 1.0;
		T.y += -z / y;
		return normalize(T);
	}

	if (abs(x) > 0.0)
  {
		T.z += 0.0;
		T.y += 1.0;
		T.x += -y / x;
		return normalize(T);
	}

	return vec3(0.0);
}

void traceRaysDiskAreaLight(in uint lightSlot, in vec3 pos, in vec3 origin, in uint samples, inout uint seed, inout uint occlusion)
{  
  vec3 lightCenter = _sbCbAreaLights.Position[lightSlot];
  float radius = _sbCbAreaLights.Size[lightSlot].x;
  vec3 lightDirection = _sbCbAreaLights.MainDirection[lightSlot];
  vec3 lightSide = getGeomT(lightDirection);
  vec3 lightUp = normalize(cross(lightDirection, lightSide));

  DiskLight light;
  light.c = lightCenter;
  light.u = lightUp;
  light.s = lightSide;
  light.r = radius;
      
  for (uint i = 0; i < samples; i++) 
  {
    float r1 = radinv_fl(seed, 2);
    float r2 = radinv_fl(seed, 3);
    seed++;
    vec3 direction = DiskSample(light, r1, r2) - pos;
    float dist = length(direction);
    direction = direction / dist;
    g_Payload.isHit = true;
    uint mask = 0xFF;
    
    bool frontFacing = dot(lightDirection, direction) < 0.0;

    if(frontFacing)
    {
      traceRayEXT(topLevelAS, gl_RayFlagsOpaqueEXT | gl_RayFlagsTerminateOnFirstHitEXT | gl_RayFlagsSkipClosestHitShaderEXT, mask/*0xFF*/, 0, 1, 0, origin, 0.0, direction, dist, 0);
    }

    occlusion += g_Payload.isHit?1:0;
  }
}

void traceRaysSphereAreaLight(in uint lightSlot, in vec3 pos, in vec3 normal, in vec3 origin, in uint samples, inout uint seed, inout uint occlusion)
{  
  vec3 lightCenter = _sbCbAreaLights.Position[lightSlot];
  float radius = _sbCbAreaLights.Size[lightSlot].x;
  vec3 lightDirection = normalize(origin-lightCenter);
  vec3 lightSide = getGeomT(lightDirection);
  vec3 lightUp = normalize(cross(lightDirection, lightSide));

  DiskLight light;
  light.c = lightCenter;
  light.u = lightUp;
  light.s = lightSide;
  light.r = radius;
      
  for (uint i = 0; i < samples; i++) 
  {
    float r1 = radinv_fl(seed, 2);
    float r2 = radinv_fl(seed, 3);
    seed++;
    vec3 direction = DiskSample(light, r1, r2) - pos;
    float dist = length(direction);
    direction = direction / dist;

    g_Payload.isHit = true;
    uint mask = 0xFF;

    float nDotL = max(0, dot(direction, normal));

    if(nDotL > 0.0)
    {
      traceRayEXT(topLevelAS, gl_RayFlagsOpaqueEXT | gl_RayFlagsTerminateOnFirstHitEXT | gl_RayFlagsSkipClosestHitShaderEXT, mask/*0xFF*/, 0, 1, 0, origin, 0.0, direction, dist, 0);
    }

    occlusion += g_Payload.isHit?1:0;
  }
}

void traceRaysRectangleAreaLight(in uint lightSlot, in vec3 pos, in vec3 origin, in uint samples, inout uint seed, inout uint occlusion)
{
  vec3 lightCenter = _sbCbAreaLights.Position[lightSlot];
  vec2 lightDimensions = _sbCbAreaLights.Size[lightSlot];
  vec3 target = vec3(0.0);
  vec3 lightDirection = _sbCbAreaLights.MainDirection[lightSlot];

  vec2 lightDimensionsHalf = lightDimensions * 0.5;
  vec3 lightUp = lightDimensionsHalf.y * _sbCbAreaLights.OtherDirection[lightSlot];
  vec3 lightSide = normalize(cross(lightUp, lightDirection)) * lightDimensionsHalf.x;
  lightUp = normalize(cross(lightDirection, lightSide)) * lightDimensionsHalf.y;
  
  vec3 lightA = lightCenter - lightSide - lightUp;
  vec3 lightB = lightCenter + lightSide - lightUp;
  vec3 lightC = lightCenter + lightSide + lightUp;
  vec3 lightD = lightCenter - lightSide + lightUp;
    
  vec3 s = lightA;
  vec3 ex = lightB - lightA;
  vec3 ey = lightD - lightA;
  
  SphQuad areaLight;
  SphQuadInit(areaLight, s, ex, ey, pos);
    
  for (uint i = 0; i < samples; i++) 
  {
    float r1 = radinv_fl(seed, 2);
    float r2 = radinv_fl(seed, 3);
    seed++;
    vec3 direction = SphQuadSample(areaLight, r1, r2) - pos;
    float dist = length(direction);
    direction = direction / dist;
    uint mask = 0xFF;
    g_Payload.isHit = true;
        
    bool frontFacing = dot(lightDirection, direction) < 0.0;

    if(frontFacing)
    {
      traceRayEXT(topLevelAS, gl_RayFlagsOpaqueEXT | gl_RayFlagsTerminateOnFirstHitEXT | gl_RayFlagsSkipClosestHitShaderEXT, mask/*0xFF*/, 0, 1, 0, origin, 0.0, direction, dist, 0);
    }

    occlusion += g_Payload.isHit?1:0;
  }
}

void traceRaysAmbientOcclusion(in vec3 origin, in vec3 x, in vec3 y, in vec3 z, in uint samples, inout uint seed, inout uint occlusion)
{
  for (uint i = 0; i < samples; i++) 
  {
    float r1 = 2 * PI * radinv_fl(seed, 2);
    float r2 = radinv_fl(seed, 3);
    
    seed++;

    float sq = sqrt(1.0 - r2);

    vec3 direction = vec3(cos(r1) * sq, sin(r1) * sq, sqrt(r2));
    direction = direction.x * x + direction.y * y + direction.z * z;
  
    g_Payload.isHit = true;

    uint mask = 0xFF;

    traceRayEXT(topLevelAS, gl_RayFlagsOpaqueEXT | gl_RayFlagsTerminateOnFirstHitEXT | gl_RayFlagsSkipClosestHitShaderEXT, mask/*0xFF*/, 0, 1, 0, origin, 0.0, direction, RTAO_RADIUS, 0);

    occlusion += g_Payload.isHit?1:0;
  }
}

// the value returned by the following method is meant to avoid self intersection artifacts
// in the case of world matrix with a big scaling factor
float getRTLocalOffsetInWorldSpace(ivec2 pixel
#ifdef IS_MSAA
, int iSample
#endif
)
{
#ifdef SO_USE_LEGACY_RAY_ORIGIN_OFFSET
  return 0.0;
#else

#ifdef IS_MSAA
  return imageLoad(gBufferAdditionalData, pixel, iSample).x;
#else
  return imageLoad(gBufferAdditionalData, pixel).x;
#endif

#endif // ifdef SO_USE_LEGACY_RAY_ORIGIN_OFFSET
}

#if HASH_SLOT_COUNT > 1
void raygen(uint hash_slot, uint lightType, int lightSlot)
#else
void raygen(uint lightType, int lightSlot)
#endif
{
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
    return;

  // If the cell contains more than the target number of samples
  // there is nothing to do either
  #if HASH_SLOT_COUNT > 1
    uint weight = getWeight(HASH_CELL(cellId, hash_slot));
  #else
    uint weight = getWeight(HASH_CELL(cellId));
  #endif
  
  if (weight > cb_PostEffect_HRTAO.maxSamplesPerCell) 
    return;
  
  uint occlusion = 0;


  vec3 pos, normal;
  float localOffsetInWorldSpace;

  #ifdef IS_MSAA
    pos = getPosition( ivec2(launchID.xy), int(launchID.z));
    normal = getNormal(ivec2(launchID.xy), int(launchID.z));
    localOffsetInWorldSpace = getRTLocalOffsetInWorldSpace(ivec2(launchID.xy), int(launchID.z));
  #else
    pos = getPosition( ivec2(launchID.xy));
    normal = getNormal(ivec2(launchID.xy));
    localOffsetInWorldSpace = getRTLocalOffsetInWorldSpace(ivec2(launchID.xy));
  #endif

  // Move origin slightly away from the surface to avoid self-occlusion
  //float posOffset = 4*getFeatureSizeInWorldUnits(length(pos - vec3(vpX, vpY, vpZ)), 1, 1e-10, 0);
  //const vec3 origin = pos + normal * posOffset; 
  vec3 origin = offset_ray_origin(pos, normal);

  #ifndef SO_USE_LEGACY_RAY_ORIGIN_OFFSET
  {
    float worldOffset = distance(pos, origin);
    if(worldOffset < localOffsetInWorldSpace) // we want the max of the two offsets (one computed in world space and one computed previously in local space)
      origin = pos + localOffsetInWorldSpace * normal;
  }
  #endif // ifndef SO_USE_LEGACY_RAY_ORIGIN_OFFSET

  uint pixelsToUpdate = getPixelsToUpdate();
  #ifdef IS_MSAA
    uint totalPixels = launchSize.x * launchSize.y * launchSize.z;
  #else
    uint totalPixels = launchSize.x * launchSize.y;
  #endif

  uint samples = int(cb_PostEffect_HRTAO.rayBudgetPerPixel) / HASH_SLOT_COUNT; // spread the budget across all shadows

  //uint pixelsInACell = uint(cb_PostEffect_HRTAO.cellSizeInPixels * cb_PostEffect_HRTAO.cellSizeInPixels);
  
  //#if HASH_SLOT_COUNT > 1
  //  HashRecordContrib contribForCount = HASH_CELL(cellId, hash_slot);
  //#else
  //  HashRecordContrib contribForCount = HASH_CELL(cellId);
  //#endif

  //uint sampleLimit = uint(max(0, int(cb_PostEffect_HRTAO.maxSamplesPerCell) - int(getWeight(contribForCount))));
  //uint maxRayBudget = sampleLimit / pixelsInACell;
  //samples = min(samples, maxRayBudget);

  if (samples == 0)
  {
    float s = radinv_fl(hashPointLODOffset(pos, 0, 0, 0)+getFrameId(cb_PostEffect_HRTAO_Auto.frameIdx), 4);  
    
    #if HASH_SLOT_COUNT > 1
      bool zero_weight = getWeight(HASH_CELL(cellId, hash_slot)) == 0;
    #else
      bool zero_weight = getWeight(HASH_CELL(cellId)) == 0;
    #endif

    if (s < cb_PostEffect_HRTAO.rayBudgetPerPixel || zero_weight)
      samples = 1;
    else
      return;
  }

  vec3 x, y, z;
  compute_default_basis(normal, x, y, z);
  
  #if HASH_SLOT_COUNT > 1
    uint existingSampleCount = addSamples(cellId, samples, hash_slot);
  #else
    uint existingSampleCount = addSamples(cellId, samples);
  #endif
  
  uint seed = checksumLODPosOnly(pos, 0) + existingSampleCount;
  
  switch(lightType)
  {
    case AmbientOcclusionType:
      traceRaysAmbientOcclusion(origin, x, y, z, samples, seed, occlusion);
      break;
    case RectangleAreaType:
      traceRaysRectangleAreaLight(lightSlot, pos, origin, samples, seed, occlusion);
      break;
    case DiskAreaType:
      traceRaysDiskAreaLight(lightSlot, pos, origin, samples, seed, occlusion);
      break;
    case SphereAreaType:
      traceRaysSphereAreaLight(lightSlot, pos, normal, origin, samples, seed, occlusion);
      break;
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
  
  #if HASH_SLOT_COUNT > 1
    storeChangeListItem(clItemIndex, contrib, hash_slot, previousChangeToCell, pixelId);
  #else
    storeChangeListItem(clItemIndex, contrib, previousChangeToCell, pixelId);  
  #endif
}

void main()
{
  int slot = 0;
  
  #ifdef SO_HRTAO_ENABLE_AO
    #if HASH_SLOT_COUNT > 1
      raygen(slot, AmbientOcclusionType, -1); // light slot useless for AO
      slot++;
    #else
      raygen(AmbientOcclusionType, -1);
    #endif
    memoryBarrier(); // is it really necessary?
  #endif

  #ifdef SO_HRTAO_SHADOWS_COUNT
    int shadowMask = _sbCbAreaLights.Type[0]>>8;
    
    for(int i=0; i<_sbCbAreaLights.Count && slot < HASH_SLOT_COUNT; i++)
    {
      if((shadowMask & (1<<i)) != 0)
      {
        #if HASH_SLOT_COUNT > 1
          raygen(slot, _sbCbAreaLights.Type[i] & 0xFF, i);
          slot++;
        #else
          raygen(_sbCbAreaLights.Type[i] & 0xFF, i);
        #endif
        memoryBarrier();
      }
    }
  #endif
}
