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

#if HASH_SLOT_COUNT > 1
  void storeChangeListItem(uint index, HashRecordContrib contribution, uint slot, uint prev, uint pixelId, float roughness)
  {
    SET_CL_ITEM(changeList, index, makeChangeListItem(contribution, slot, prev, pixelId, roughness));
  }
#else
  void storeChangeListItem(uint index, HashRecordContrib contribution, uint prev, uint pixelId, float roughness)
  {
    SET_CL_ITEM(changeList, index, makeChangeListItem(contribution, prev, pixelId, roughness));
  }
#endif

uint reserveChangeListItem()
{
  return RESERVE_CL_ITEM;
}

struct SampleValue
{
  vec3  coord;
  float value;
};
SampleValue sampleValues[10];
uint        sampleCount = 0;

//void setSample(uint i, vec3 coord, float value)
//{
//  if(i >= 10)
//    return;
//  sampleValues[i].coord = coord;
//  sampleValues[i].value = value;
//}
//

void addSample(vec3 coord)
{
  if(sampleCount >= 10)
    return;
  sampleValues[sampleCount].coord = coord;
  sampleValues[sampleCount].value = 1.f;
  sampleCount++;
}

float l1Dist(vec3 p1, vec3 p2)
{
  return abs(p2.x - p1.x) + abs(p2.y - p1.y) + abs(p2.z - p1.z);
}

bool hasSimilarSample(vec3 p)
{
  float       contrib   = 0.f;
  float       weightSum = 0.f;
  const float maxDist   = 1;
  for(uint i = 0; i < sampleCount; i++)
  {
    float d = l1Dist(p, sampleValues[i].coord);
    float w = max(0.f, maxDist - d);
    if(w > 0.f)
      return true;
  }
  return false;
}


bool sameSide(vec3 v1, vec3 v2, vec3 v3, vec3 v4, vec3 p)
{
  vec3  normal = cross(v2 - v1, v3 - v1);
  float dotV4  = dot(normal, v4 - v1);
  float dotP   = dot(normal, p - v1);
  return sign(dotV4) == sign(dotP);
}

bool pointInTetrahedron(vec3 v1, vec3 v2, vec3 v3, vec3 v4, vec3 p)
{
  return sameSide(v1, v2, v3, v4, p) && sameSide(v2, v3, v4, v1, p) && sameSide(v3, v4, v1, v2, p)
         && sameSide(v4, v1, v2, v3, p);
}

float tetraVolume(vec3 v1, vec3 v2, vec3 v3, vec3 v4)
{
  vec3 a = v1 - v4;
  vec3 b = v2 - v4;
  vec3 c = v3 - v4;
  return abs(dot(a, cross(b, c))) / 6.f;
}
// Scalar triple product
float scTP(vec3 a, vec3 b, vec3 c)
{
  return dot(a, cross(b, c));
}

vec4 baryTetra(vec3 a, vec3 b, vec3 c, vec3 d, vec3 p)
{
  vec3 vap = p - a;
  vec3 vbp = p - b;

  vec3 vab = b - a;
  vec3 vac = c - a;
  vec3 vad = d - a;

  vec3 vbc = c - b;
  vec3 vbd = d - b;
  // ScTP computes the scalar triple product
  float va6 = scTP(vbp, vbd, vbc);
  float vb6 = scTP(vap, vac, vad);
  float vc6 = scTP(vap, vad, vab);
  float vd6 = scTP(vap, vab, vac);
  float v6  = 1 / scTP(vab, vac, vad);
  return vec4(va6 * v6, vb6 * v6, vc6 * v6, vd6 * v6);
}

float sqDist(vec3 x, vec3 y)
{
  float d = dot(x - y, x - y);
  return d;
}

uint getClosestSample(vec3 p)
{
  uint  res     = ~0u;
  float minDist = 1e30f;
  for(uint i = 0; i < 10; i++)
  {
    float d = sqDist(p, sampleValues[i].coord);
    if(d < minDist)
    {
      minDist = d;
      res     = i;
    }
  }
  return res;
}

uint getSecondSample(vec3 p, uint closestIndex)
{
  uint  res       = ~0u;
  vec3  direction = normalize(p - sampleValues[closestIndex].coord);
  float maxProd   = 0.f;
  float minDist   = 1e30f;
  for(uint i = 0; i < 10; i++)
  {
    if(i == closestIndex)
      continue;
    vec3  localVec = (p - sampleValues[closestIndex].coord);
    float l        = length(localVec);
    float prod     = dot(localVec / l, direction);

    if(prod <= 0.f)
      continue;
    if(prod > maxProd && l < minDist)
    {
      maxProd = prod;
      minDist = minDist;
      res     = i;
    }
  }
  return res;
}

//float l1Dist(vec3 p1, vec3 p2)
//{
//  return abs(p2.x-p1.x) + abs(p2.y-p1.y) + abs(p2.z-p1.z);
//}
//
//float getSampleValue(vec3 p)
//{
//  float contrib = 0.f;
//  float weightSum = 0.f;
//  const float maxDist = 1;
//  for(uint i=0; i < 10; i++)
//  {
//    float d = l1Dist(p, sampleValues[i].coord);
//    float w = max(0.f, maxDist - d);
//    contrib += sampleValues[i].value.x;
//    weightSum += w;
//
//  }
//  return (contrib / (weightSum*maxDist));
//}


float getSampleValueLinear(vec3 p)
{
  uint closest = getClosestSample(p);
  uint other   = getSecondSample(p, closest);

  //  float closestDist = length(sampleValues[closest].coord - p);
  //  float otherDist   = length(sampleValues[other].coord - p);

  float closestDist = sqDist(sampleValues[closest].coord, p);
  float otherDist   = sqDist(sampleValues[other].coord, p);


  float totalDist = closestDist + otherDist;

  float closestWeight = otherDist / totalDist;
  float otherWeight   = 1.f - closestWeight;
  return sampleValues[closest].value * closestWeight + sampleValues[other].value * otherWeight;
}


float getSampleValueClosest(vec3 p)
{
  float minDist = 1e30f;
  float res     = 0.f;
  float wSum    = 0.f;
  for(uint i = 0; i < 10; i++)
  {
    float d = sqDist(p, sampleValues[i].coord);
    if(d < minDist)
    {
      minDist = d;
      res     = sampleValues[i].value;
    }
    //float w = 1.f / (sqDist(p, sampleValues[i].coord));
    //res += sampleValues[i].value / w;
    //wSum += w;
  }
  return res;  // / wSum;
}


float getSampleValueTetra(vec3 p)
{
  uint  v0 = ~0u, v1 = ~0u, v2 = ~0u, v3 = ~0u;
  float volume = 1e30f;
  //v1 = vec3(-10.f, -10.f, -10.f);
  //v2 = vec3(10.f, -10.f, -10.f);
  //v3 = vec3(0.f, 10.f, -10.f);
  //v4 = vec3(0.f, 0.f, 10.f);

  for(uint i0 = 0; i0 < 10; i0++)
  {
    for(uint i1 = 0; i1 < 10; i1++)
    {
      if(i1 == i0)
        continue;
      for(uint i2 = 0; i2 < 10; i2++)
      {
        if(i2 == i1 || i2 == i0)
          continue;
        for(uint i3 = 0; i3 < 10; i3++)
        {
          if(i3 == i2 || i3 == i1 || i3 == i0)
            continue;
          if(pointInTetrahedron(sampleValues[i0].coord, sampleValues[i1].coord, sampleValues[i2].coord, sampleValues[i3].coord, p))
          {
            float vol =
                tetraVolume(sampleValues[i0].coord, sampleValues[i1].coord, sampleValues[i2].coord, sampleValues[i3].coord);
            if(vol < volume)
            {
              v0     = i0;
              v1     = i1;
              v2     = i2;
              v3     = i3;
              volume = vol;
            }
          }
        }
      }
    }
  }
  if(v0 != ~0u && v1 != ~0u && v2 != ~0u && v3 != ~0u)
  {
    vec4 bary =
        abs(baryTetra(sampleValues[v0].coord, sampleValues[v1].coord, sampleValues[v2].coord, sampleValues[v3].coord, p));
    //bary /= (bary.x + bary.y + bary.z + bary.w);
    //bary = vec4(0.5f);
    return bary.x * sampleValues[v0].value;
    //+bary.y* sampleValues[v1].value + bary.z* sampleValues[v2].value + bary.w* sampleValues[v3].value;
  }
  else
    return (0.f);
}


//values taken from lightingAdvanced.glsl
#define AmbientOcclusionType -1
#define SphereAreaType 0
#define TubeAreaType 1
#define DiskAreaType 2
#define RectangleAreaType 3


const float eps = 1e-5; 

//An Area-Preserving Parametrization for Spherical Rectangles
//https://www.arnoldrenderer.com/research/egsr2013_spherical_rectangle.pdf
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

// Converting PDF from area to solid angle
// https://www.shadertoy.com/view/ltsyzl
float PdfAtoW(float aPdfA, float aDist2, float aCosThere)
{
  float absCosTheta = abs(aCosThere);
  if( absCosTheta < eps )
    return 0.0;
  
  return aPdfA * aDist2 / absCosTheta;
}

vec3 DiskSample(in DiskLight l, in float u, in float v)
{
  float theta = u * 2.0 * PI;
  float d = sqrt(v);
  float x = l.r * d * cos(theta);
  float y = l.r * d * sin(theta);
  return x * l.s + y * l.u + l.c;
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

#ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
vec3 traceRaysDiskAreaLight(in uint lightSlot, in vec3 pos, in vec3 normal, in vec3 origin, in uint samples, inout uint seed, in MaterialEval matEval, in vec3 viewDir, in uint sampleSplit, inout vec4 perPixelEval)
#else
vec3 traceRaysDiskAreaLight(in uint lightSlot, in vec3 pos, in vec3 normal, in vec3 origin, in uint samples, inout uint seed)
#endif
{
  vec3 envValues = vec3(0.0);

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
      
#ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
  for (uint i = 0; i < sampleSplit; i++) //for now we compute only diffuse, so we take half the samples
#else
  for (uint i = 0; i < samples; i++) 
#endif
  {
    float r1 = radinv_fl(seed, 2);
    float r2 = radinv_fl(seed, 3);
    seed++;
    vec3 direction = DiskSample(light, r1, r2) - pos;
    float d2 = dot(direction, direction);
    float dist = sqrt(d2);
    direction = direction / dist;

    float pdfA = 1.0 / (PI * radius * radius);

    g_Payload.isHit = true;
    uint mask = 0xFF;

    float nDotL = max(0, dot(direction, normal));
    float pdfW = PdfAtoW(pdfA, d2, nDotL);
    
    bool frontFacing = dot(lightDirection, direction) < 0.0;

    if(nDotL > 0.0 && frontFacing)
    {
      traceRayEXT(topLevelAS, gl_RayFlagsOpaqueEXT | gl_RayFlagsTerminateOnFirstHitEXT | gl_RayFlagsSkipClosestHitShaderEXT, mask/*0xFF*/, 0, 1, 0, origin, 0.0, direction, dist, 0);
    }

    if(!g_Payload.isHit)
      envValues += vec3(nDotL/pdfW);
  }

  return envValues;
}

#ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
vec3 traceRaysSphereAreaLight(in uint lightSlot, in vec3 pos, in vec3 normal, in vec3 origin, in uint samples, inout uint seed, in MaterialEval matEval, in vec3 viewDir, in uint sampleSplit, inout vec4 perPixelEval)
#else
vec3 traceRaysSphereAreaLight(in uint lightSlot, in vec3 pos, in vec3 normal, in vec3 origin, in uint samples, inout uint seed)
#endif
{  
  vec3 envValues = vec3(0.0);

  vec3 lightCenter = _sbCbAreaLights.Position[lightSlot];
  float radius = _sbCbAreaLights.Size[lightSlot].x;
  vec3 lightDirection = normalize(origin-lightCenter);
  vec3 lightSide = getGeomT(lightDirection);
  vec3 lightUp = normalize(cross(lightDirection, lightSide));

  float powerPerAreaUnit = _sbCbAreaLights.PowerPerAreaUnit[lightSlot];
  vec3 lightColor = _sbCbAreaLights.Color[lightSlot];

  DiskLight light;
  light.c = lightCenter;
  light.u = lightUp;
  light.s = lightSide;
  light.r = radius;
  
#ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
  for (uint i = 0; i < sampleSplit; i++) //for now we compute only diffuse, so we take half the samples
#else
  for (uint i = 0; i < samples; i++) 
#endif
  {
    float r1 = radinv_fl(seed, 2);
    float r2 = radinv_fl(seed, 3);
    seed++;
    vec3 direction = DiskSample(light, r1, r2) - pos;
    float d2 = dot(direction, direction);
    float dist = sqrt(d2);
    direction = direction / dist;

    //float pdfA = 1.0 / (PI * radius * radius);

    g_Payload.isHit = true;
    uint mask = 0xFF;
    
    float nDotL = max(0, dot(direction, normal));
    //float pdfW = PdfAtoW(pdfA, d2, nDotL); //no pdf yet... we're just computing visibility for now

    if(nDotL > 0.0)
    {
      traceRayEXT(topLevelAS, gl_RayFlagsOpaqueEXT | gl_RayFlagsTerminateOnFirstHitEXT | gl_RayFlagsSkipClosestHitShaderEXT, mask/*0xFF*/, 0, 1, 0, origin, 0.0, direction, dist, 0);
      
      if(!g_Payload.isHit)
        envValues += vec3(1.0);
      
      #ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
        perPixelEval += vec4(vec3(0.0), 1.0f); //TODO
      #endif
    }
  }

  return envValues;
}

#ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
vec3 traceRaysRectangleAreaLight(in uint lightSlot, in vec3 pos, in vec3 normal, in vec3 origin, in uint samples, inout uint seed, in MaterialEval matEval, in vec3 viewDir, in uint sampleSplit, inout vec4 perPixelEval)
#else
vec3 traceRaysRectangleAreaLight(in uint lightSlot, in vec3 pos, in vec3 normal, in vec3 origin, in uint samples, inout uint seed)
#endif
{
  vec3 envValues = vec3(0.0);

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
    
#ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
  for (uint i = 0; i < sampleSplit; i++) //for now we compute only diffuse, so we take half the samples
#else
  for (uint i = 0; i < samples; i++) 
#endif
  {
    float r1 = radinv_fl(seed, 2);
    float r2 = radinv_fl(seed, 3);
    seed++;
    vec3 direction = SphQuadSample(areaLight, r1, r2) - pos;
    float dist = length(direction);
    direction = direction / dist;
    g_Payload.isHit = true;
    uint mask = 0xFF;
    
    float nDotL = max(0, dot(direction, normal));
    
    bool frontFacing = dot(lightDirection, direction) < 0.0;

    if(nDotL > 0.0 && frontFacing)
    {
      traceRayEXT(topLevelAS, gl_RayFlagsOpaqueEXT | gl_RayFlagsTerminateOnFirstHitEXT | gl_RayFlagsSkipClosestHitShaderEXT, mask/*0xFF*/, 0, 1, 0, origin, 0.0, direction, dist, 0);
    }
    
    if(!g_Payload.isHit)
      envValues += vec3(1.0);
  }

  return envValues;
}

vec3 traceRaysReflections(in vec3 pos, in vec3 normal, in vec3 origin, in uint samples, inout uint seed)
{
  vec3 envValues = vec3(0.0);

  for (uint i = 0; i < samples; i++) 
  {
    vec3  sampleValue = vec3(radinv_fl(seed, 2), radinv_fl(seed, 3), radinv_fl(seed, 4));
    vec3 direction = environment_sample_cutpoint(sampleValue);
    float nDotL = max(0, dot(direction, normal));

    seed++;
  
    g_Payload.isHit = true;

    if(nDotL > 0.0)
    {
      uint mask = 0xFF;
    
      traceRayEXT(topLevelAS, gl_RayFlagsOpaqueEXT | gl_RayFlagsTerminateOnFirstHitEXT, mask/*0xFF*/, 0, 1, 0, origin, 0.0, direction, RTAO_RADIUS, 0);
    
      vec2 envUV = getSphericalUv(direction);
      vec4 envSample = textureLod(hdrEnv, envUV, 0);
      float pdf = envSample.w;
      vec3 hitCol = g_Payload.isHit ? g_Payload.color : envSample.xyz;
      vec3 envVal = hitCol * nDotL / (pdf * PI);
                    
      if(pdf == 0.f)
        envVal = vec3(0.f);

      envValues += envVal;
    }
  }

  return envValues;
}

#ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
vec3 traceRaysEnvironmentLightReference(in vec3 pos, in vec3 normal, in vec3 origin, in uint samples, inout uint seed, in MaterialEval matEval, in vec3 viewDir, in uint sampleSplit, inout vec4 perPixelEval)
{
  //ground truth / reference
  vec3 return_value = vec3(0.0);
  perPixelEval = vec4(0.0);

  for(uint i = 0; i < samples; i++)
  {
    vec3 sample_value = vec3(radinv_fl(seed, 2), radinv_fl(seed, 3), radinv_fl(seed, 4));
    seed++;

    //we want to sample according to two PDFs: environment (using cutpoint) for the diffuse BRDF, and specular BRDF directly

    if(i < sampleSplit)
    {
      //diffuse sampling & pdf
      vec3 env_direction = environment_sample_cutpoint(sample_value);
      float nDotL_diff = max(0, dot(env_direction, normal));
      if(nDotL_diff > 0.0)
      {      
        const uint rayMask = 0xFF;
        g_Payload.isHit = true;
        traceRayEXT(topLevelAS, gl_RayFlagsOpaqueEXT | gl_RayFlagsTerminateOnFirstHitEXT | gl_RayFlagsSkipClosestHitShaderEXT, rayMask /*0xFF*/, 0, 1, 0, origin, 0.0, env_direction, RTAO_RADIUS, 0);
                  
        if(!g_Payload.isHit)
        {
          vec2 env_uv_diff = getSphericalUv(env_direction);
          vec4 env_sample_diff = textureLod(hdrEnv, env_uv_diff, 0);
          float env_pdf = env_sample_diff.w;
          vec3 diffuse_brdf = BsdfEvalDiffuseOnly(viewDir, matEval, env_direction);
          return_value += env_sample_diff.xyz * diffuse_brdf * nDotL_diff / env_pdf;
        }
      }
    }
    else
    {
      //specular sampling & pdf
      vec3 specular_direction = BsdfSampleSpecular(viewDir, sample_value, matEval);
      float nDotL_spec = max(0, dot(specular_direction, normal));
      if(nDotL_spec > 0.0)
      {      
        const uint rayMask = 0xFF;
        g_Payload.isHit = true;
        traceRayEXT(topLevelAS, gl_RayFlagsOpaqueEXT | gl_RayFlagsTerminateOnFirstHitEXT | gl_RayFlagsSkipClosestHitShaderEXT, rayMask /*0xFF*/, 0, 1, 0, origin, 0.0, specular_direction, RTAO_RADIUS, 0);
                    
        if(!g_Payload.isHit)
        {
          vec2 env_uv_spec = getSphericalUv(specular_direction);
          vec4 env_sample_spec = textureLod(hdrEnv, env_uv_spec, 0);
          float specular_pdf = BsdfPdfSpecular(viewDir, matEval, specular_direction);
          vec3 specular_brdf = BsdfEvalSpecularOnly(viewDir, matEval, specular_direction);
          perPixelEval += vec4(env_sample_spec.xyz * specular_brdf * nDotL_spec / specular_pdf, 1.0);
        }
        else
        {
          perPixelEval += vec4(vec3(0.0), 1.0);
        }
      }
    }
  }

  return return_value;
}

//https://www.pbr-book.org/3ed-2018/Monte_Carlo_Integration/Importance_Sampling#MultipleImportanceSampling
float BalanceHeuristic(in uint nf, in float fPdf, in uint ng, in float gPdf)
{
    return (nf * fPdf) / (nf * fPdf + ng * gPdf);
}

float PowerHeuristic(in uint nf, in float fPdf, in uint ng, in float gPdf)
{
    float f = nf * fPdf;
    float g = ng * gPdf;
    return (f * f) / (f * f + g * g);
}

#define MISWeightingFunction PowerHeuristic

vec3 traceRaysEnvironmentLight(in vec3 pos, in vec3 normal, in vec3 origin, in uint samples, inout uint seed, in MaterialEval matEval, in vec3 viewDir, in uint sampleSplit, inout vec4 perPixelEval)
{
  vec3 envValues = vec3(0);
  perPixelEval = vec4(0.0);

  float envSampleRatio = float(sampleSplit) / float(samples);

  const uint envSamplesCount = sampleSplit;
  const uint bsdfSamplesCount = samples - sampleSplit;

  for(uint i = 0; i < samples; i++)
  {
    vec3 direction;

    float nDotL;
    vec3  sampleValue = vec3(radinv_fl(seed, 2), radinv_fl(seed, 3), radinv_fl(seed, 4));
    seed++;

    float bsdfPdf;
    bool  isBsdfSample;

    if(i < sampleSplit)
    {
      isBsdfSample = false;
      direction    = environment_sample_cutpoint(sampleValue);
      bsdfPdf      = BsdfPdf(viewDir, matEval, direction);
    }
    else
    {
      isBsdfSample = true;
      direction    = BsdfSampleSpecular(viewDir, sampleValue, matEval);
      bsdfPdf      = BsdfPdfSpecular(viewDir, matEval, direction);
    }
    nDotL = max(0, dot(direction, normal));

    g_Payload.isHit = true;

    if(nDotL > 0.f)
    {

      const uint rayMask = 0xFF;
      traceRayEXT(topLevelAS, gl_RayFlagsOpaqueEXT | gl_RayFlagsTerminateOnFirstHitEXT | gl_RayFlagsSkipClosestHitShaderEXT, rayMask /*0xFF*/, 0, 1, 0, origin, 0.0, direction, RTAO_RADIUS, 0);

      ivec2 envSize = ivec2(textureSize(hdrEnv, 0));
      vec2  envUV   = getSphericalUv(direction);
      ivec2 coord   = ivec2(envUV * envSize);
      coord.x       = clamp(coord.x, 0, envSize.x - 1);
      coord.y       = clamp(coord.y, 0, envSize.y - 1);

      // Choose the environment mip level according to the surface roughness, but
      // keep at least a resolution of 128x128
      int lodCount = int(1.0 + floor(log2(max(envSize.x, envSize.y))));
      lodCount = max(1, lodCount - 7);
      float envLod   = matEval.perceptualRoughness * lodCount;

      vec4 env     = textureLod(hdrEnv, envUV, envLod);
      env.w        = textureLod(hdrEnv, envUV, 0).w;
      float envPdf = env.w;
      updateVisibilityMask(coord);

      if(envPdf == 0.f)
        env.xyz = vec3(0.f);

      float misWeight = 1.f;
      float pdf;

      if(isBsdfSample)
      {
        //misWeight = (1.f - envSampleRatio) * bsdfPdf / ((1.f - envSampleRatio) * bsdfPdf + envSampleRatio * envPdf);
        misWeight = MISWeightingFunction(bsdfSamplesCount, bsdfPdf, envSamplesCount, envPdf);
        pdf       = bsdfPdf;
      }
      else
      {
        if(envPdf == 0.f)
          env.xyz = vec3(0.f);
        //misWeight = envSampleRatio * envPdf / (envSampleRatio * envPdf + (1.f - envSampleRatio) * bsdfPdf);
        misWeight = MISWeightingFunction(envSamplesCount, envPdf, bsdfSamplesCount, bsdfPdf);
        pdf       = envPdf;
      }

      vec3 diffuseContrib, specContrib;
      BsdfEvalSeparate(viewDir, matEval, direction, diffuseContrib, specContrib);

      vec3 envVal = env.xyz * misWeight * nDotL / pdf;

      if(pdf == 0.f)
        envVal = vec3(0.f);

      if(!g_Payload.isHit)
      {
        envValues += envVal / PI;
        perPixelEval += vec4(specContrib * envVal, 1.0f);
      }
      else
      {
        envValues += cb_PostEffect_HRTAO.ambientFactor * envVal / PI;
        perPixelEval += vec4(vec3(0.0), 1.0f);
      }
    }
  }
  return envValues;
}
#else
vec3 traceRaysEnvironmentLight(in vec3 pos, in vec3 normal, in vec3 origin, in uint samples, inout uint seed)
{
  vec3 envValues = vec3(0.0);

  for (uint i = 0; i < samples; i++) 
  {
    vec3 direction;

    vec3  sampleValue = vec3(radinv_fl(seed, 2), radinv_fl(seed, 3), radinv_fl(seed, 4));
    
    direction = environment_sample_cutpoint(sampleValue);
    
    float nDotL = max(0, dot(direction, normal));

    seed++;
  
     g_Payload.isHit = true;

    if(nDotL > 0.0)
    {
      uint mask = 0xFF;
    
      #ifdef Supports_GL_NV_ray_tracing
        traceNV(topLevelAS, gl_RayFlagsOpaqueNV | gl_RayFlagsTerminateOnFirstHitNV | gl_RayFlagsSkipClosestHitShaderNV, mask/*0xFF*/, 0, 1, 0, origin, 0.0, direction, RTAO_RADIUS, 0);
      #else
        traceRayEXT(topLevelAS, gl_RayFlagsOpaqueEXT | gl_RayFlagsTerminateOnFirstHitEXT | gl_RayFlagsSkipClosestHitShaderEXT, mask/*0xFF*/, 0, 1, 0, origin, 0.0, direction, RTAO_RADIUS, 0);
      #endif
    
        vec2 envUV = getSphericalUv(direction);
        vec4 envSample = textureLod(hdrEnv, envUV, 0);
        float pdf = envSample.w;
        vec3 envVal = envSample.xyz * nDotL / (pdf * PI);
        
          if(pdf == 0.f)
            envVal = vec3(0.f);
            
      if (!g_Payload.isHit)
      {
        envValues += envVal;
      }
      else
      {
        envValues += cb_PostEffect_HRTAO.ambientFactor * envVal;
      }
    }
  }

  return envValues;
}
#endif

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
  
  bool hasEnoughDiffuseSamples = false;

  #ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
    if (weight > cb_PostEffect_HRTAO.maxSamplesPerCell)
      hasEnoughDiffuseSamples = true;
  #endif

  ivec2 pxCoord = ivec2(launchID.xy);
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
  
  vec3 viewDir = normalize(pos - vec3(vpX, vpY, vpZ));
  // Move origin slightly away from the surface to avoid self-occlusion
  // float posOffset = 4*getFeatureSizeInWorldUnits(length(pos - vec3(vpX, vpY, vpZ)), 1, 1e-10, 0);
  // const vec3 origin = pos + normal * posOffset; 
  vec3 origin = offset_ray_origin(pos, normal);

  #ifndef SO_USE_LEGACY_RAY_ORIGIN_OFFSET
  {
    float worldOffset = distance(pos, origin);
    if(worldOffset < localOffsetInWorldSpace) // we want the max of the two offsets (one computed in world space and one computed previously in local space)
      origin = pos + localOffsetInWorldSpace * normal;
  }
  #endif // ifndef SO_USE_LEGACY_RAY_ORIGIN_OFFSET

  #ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
    #ifdef IS_MSAA
      uvec4 matInfo1 = imageLoad(materialInfo1, ivec2(launchID.xy), int(launchID.z));
      uvec4 matInfo2 = imageLoad(materialInfo2, ivec2(launchID.xy), int(launchID.z));
    #else
      uvec4 matInfo1 = imageLoad(materialInfo1, ivec2(launchID.xy));
      uvec4 matInfo2 = imageLoad(materialInfo2, ivec2(launchID.xy));
    #endif
    MaterialEval matEval = decodeMaterialEval(matInfo1, matInfo2);
    
    vec3 viewDirection = normalize(origin - vec3(vpX, vpY, vpZ));

    //if(dot(-viewDirection, matEval.shadingNormal) <= 0.01f)
    //  return;
  #endif

  uint pixelsToUpdate = getPixelsToUpdate();
  #ifdef IS_MSAA
    uint totalPixels = launchSize.x * launchSize.y * launchSize.z;
  #else
    uint totalPixels = launchSize.x * launchSize.y;
  #endif
  
  uint samples = int(cb_PostEffect_HRTAO.rayBudgetPerPixel) / HASH_SLOT_COUNT; // spread the budget across all shadows
   
  #ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
  samples += samples %2;//round up to even number
  #endif

  //uint pixelsInACell = uint(cb_PostEffect_HRTAO.cellSizeInPixels * cb_PostEffect_HRTAO.cellSizeInPixels);
  //
  //#if HASH_SLOT_COUNT > 1
  //  HashRecordContrib contribForCount = HASH_CELL(cellId, hash_slot);
  //#else
  //  HashRecordContrib contribForCount = HASH_CELL(cellId);
  //#endif
  //
  //uint sampleLimit = uint(max(0, int(cb_PostEffect_HRTAO.maxSamplesPerCell) - int(getWeight(contribForCount))));
  //uint maxRayBudget = sampleLimit / pixelsInACell;
  //samples = min(samples, maxRayBudget);

  if (samples == 0)
  {
    float s = radinv_fl(hashPointLODOffset(pos, 0, 0, 0) + getFrameId(cb_PostEffect_HRTAO_Auto.frameIdx), 4);
    
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
  
  #if HASH_SLOT_COUNT > 1
    uint existingSampleCount = addSamples(cellId, samples, hash_slot);
  #else
    uint existingSampleCount = addSamples(cellId, samples);
  #endif
  
  uint seed = checksumLODPosOnly(pos, 0) + existingSampleCount;

  vec3 envValues = vec3(0.0);
  
  #ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
    vec4 perPixelEval = vec4(0.0);
    uint sampleSplit = samples / 2;
  #endif

  switch(lightType)
  {
    case AmbientOcclusionType:
      #ifdef SO_HRTAO_ENABLE_DEBUG_REFLECTIONS
        envValues = traceRaysReflections(pos, normal, origin, samples, seed);
      #else
        #ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
          envValues = traceRaysEnvironmentLight(pos, normal, origin, samples, seed, matEval, viewDir, sampleSplit, perPixelEval);
        #else
          envValues = traceRaysEnvironmentLight(pos, normal, origin, samples, seed);
        #endif
      #endif
      break;
    case RectangleAreaType:
      #ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
        envValues = traceRaysRectangleAreaLight(lightSlot, pos, normal, origin, samples, seed, matEval, viewDir, sampleSplit, perPixelEval);
      #else
        envValues = traceRaysRectangleAreaLight(lightSlot, pos, normal, origin, samples, seed);
      #endif
      break;
    case DiskAreaType:
      #ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
        envValues = traceRaysDiskAreaLight(lightSlot, pos, normal, origin, samples, seed, matEval, viewDir, sampleSplit, perPixelEval);
      #else
        envValues = traceRaysDiskAreaLight(lightSlot, pos, normal, origin, samples, seed);
      #endif
      break;
    case SphereAreaType:
      #ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
        envValues = traceRaysSphereAreaLight(lightSlot, pos, normal, origin, samples, seed, matEval, viewDir, sampleSplit, perPixelEval);
      #else
        envValues = traceRaysSphereAreaLight(lightSlot, pos, normal, origin, samples, seed);
      #endif
      break;
  }


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

  HashRecordContrib contrib;
  
  float roughnessToStore = 0.0;

  #ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
    vec3 glossyContrib = vec3(0.0);
    uint glossyWeight = 0;

    if(uint(perPixelEval.w) != 0)
    {
      glossyContrib = vec3(perPixelEval.xyz);
      glossyWeight = max(1, uint(perPixelEval.w));
    }

    if(hasEnoughDiffuseSamples)
      contrib = makeContrib(vec3(0.f), 0, glossyContrib, glossyWeight);
    else
      contrib = makeContrib(vec3(envValues), sampleSplit, glossyContrib, glossyWeight);

    roughnessToStore = matEval.perceptualRoughness;
  #else
    contrib = makeContrib(HASH_OUTPUT_VALUE(envValues), samples, vec3(0.0), 0);
  #endif

  #if HASH_SLOT_COUNT > 1
    storeChangeListItem(clItemIndex, contrib, hash_slot, previousChangeToCell, pixelId, roughnessToStore);
  #else
    storeChangeListItem(clItemIndex, contrib, previousChangeToCell, pixelId, roughnessToStore);  
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
