/*
 * Copyright (c) 2018, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

//#define HASH_NORMAL_SCALE 3.0
#define HASH_NORMAL_SCALE 16.0
#define HASH_CELL_NOT_FOUND ~0u

#ifndef M_PI
#define M_PI 3.141592653589
#endif

#ifndef M_ONE_OVER_PI
#define M_ONE_OVER_PI 0.318309886183
#endif

#define HashRecordKey uint

/*
  Don't delete this, the fake parser is not able to detect the above #define
  It needs to see a struct (even commented) to be able to declare the associated SSBO...
  Very very ugly
*/

// struct HashRecordKey
// {
//   uint dummy;
// };


struct ChangeListCounters
{
  uint counter;
  uint total;
};


//layout(push_constant) uniform spatialHashConstants
//{
//  mat4  inverseProjectionMatrix;
//  uint  hashTableSize;
//  uint  resX;
//  uint  resY;
//  uint  aoSamplesPerPass;
//
//  uint  frameIdx;
//  float vpX;
//  float vpY;
//  float vpZ;
//
//  float cellSizeInPixels;
//  int maxSamplesPerCell;
//  int displayCells;
//  float aoRadius;
//
//  float pixelAngle;
//  float aoPower;
//  float rayBudgetPerPixel;
//  uint filterStep;
//
//  uint useNvlink;
//  int minSampleCountPerCell;
//  uint hashVisualizeMode;
//  uint cleanupPass;
//
//  uint cellLifespan;
//  int pad1;
//  uint pad2;
//  uint pad3;
//
//};

#ifdef HRTAO_GBUFFER_FETCH
vec3 getPosition(ivec2 pixel
#ifdef IS_MSAA
, int iSample
#endif
)
{
#ifdef IS_MSAA
  return uintBitsToFloat(imageLoad(positionNormals, pixel, iSample).xyz);
#else
  return uintBitsToFloat(imageLoad(positionNormals, pixel).xyz);
#endif
  //const float resX = _sbCbCamera.ScreenSize.x;
  //const float resY = _sbCbCamera.ScreenSize.y;
  //const mat4 inverseProjectionMatrix = _sbCbCamera.ProjInverseMatrix;
  //
  //
  //float depth = imageLoad(positionNormals, pixel).x;
  //if (depth == 0.0)
  //  return vec3(0);  
  //vec4 coord = vec4(pixel.x/float(resX), pixel.y/float(resY), depth/**2.0-1.0*/, 1);
  //coord.xy = 2*coord.xy - vec2(1,1);
  //vec4 pos = inverseProjectionMatrix*coord;
  //return pos.xyz/pos.w;
}
vec3 getNormal(ivec2 pixel
#ifdef IS_MSAA
, int iSample
#endif
)
{
  //uint compressedNormal = floatBitsToUint(imageLoad(positionNormals, pixel).y);
#ifdef IS_MSAA
  uint compressedNormal = imageLoad(positionNormals, pixel, iSample).w;
#else
  uint compressedNormal = imageLoad(positionNormals, pixel).w;
#endif

  if (compressedNormal == 0)
    return vec3(0);
  return decompress_unit_vec(compressedNormal);
} 

uint getPackedNormal(ivec2 pixel
#ifdef IS_MSAA
, int iSample
#endif
)
{
#ifdef IS_MSAA
  return imageLoad(positionNormals, pixel, iSample).w;
#else
  return imageLoad(positionNormals, pixel).w;
#endif
}
#endif

// Quantize the octant-based normal for hashing instead of using a discretization on the vec3 normal
uint quantizeNormal(uint normal)
{
  return ((normal >> 30) << 2) | ((normal >> 14) & 0x3);
}



vec3 cellIndexToColor(uint cellId)
{
  uint r = cellId & 0xFF;
  uint g = (cellId >> 8) & 0xFF;
  uint b = (cellId >> 16) & 0xFF;
  return vec3(float(r) / 255.0, float(g) / 255.0, float(b) / 255.0);
}

vec3 cellIndicesToHeat(uvec4 cellIds)
{
  //red = LOD #3 used
  //yellow = LOD #2 used
  //green = LOD #1 used
  //blue = LOD #0 used
  
  if (cellIds.w != HASH_CELL_NOT_FOUND)
    return vec3(1,0,0); 

  if(cellIds.z != HASH_CELL_NOT_FOUND)
    return vec3(1, 1, 0);

  if(cellIds.y != HASH_CELL_NOT_FOUND)
    return vec3(0, 1, 0);

  return vec3(0,0,1);

}


int wangHash(int seed)
{
  seed = (seed ^ 61) ^ (seed >> 16);
  seed *= 9;
  seed = seed ^ (seed >> 4);
  seed *= 0x27d4eb2d;
  seed = seed ^ (seed >> 15);
  return seed;
}

int xorshift32(int x64)
{
  x64 ^= x64 << 13;
  x64 ^= x64 >> 7;
  x64 ^= x64 << 17;
  return x64;
}


float getFeatureSizeInWorldUnits(float distance, uint featureSizeInPixels, float minFeatureSize, uint lodOffset)
{

  float featureSize = tan(cb_PostEffect_HRTAO_Auto.pixelAngle*featureSizeInPixels) * distance;

  float log2Size = log2(featureSize/minFeatureSize)+lodOffset;
  float featureSizeRound = exp2(floor(log2Size))*minFeatureSize;

  return featureSizeRound;


}

float getContinuousFeatureSizeInWorldUnits(float distance, uint featureSizeInPixels, float minFeatureSize, uint lodOffset)
{

  float featureSize = tan(cb_PostEffect_HRTAO_Auto.pixelAngle * featureSizeInPixels) * distance;

  float log2Size         = log2(featureSize / minFeatureSize) + lodOffset;
  float featureSizeRound = exp2(log2Size) * minFeatureSize;

  return featureSizeRound;
}

float getFeatureSizeInWorldUnitsNormal(vec3 pos, uint featureSizeInPixels, float minFeatureSize, uint lodOffset, uint normal)
{

  vec3  dir         = vec3(vpX - pos.x, vpY - pos.y, vpZ - pos.z);
  float distance    = length(dir);
  float featureSize = tan(cb_PostEffect_HRTAO_Auto.pixelAngle * featureSizeInPixels) * distance;

  vec3  n     = decompress_unit_vec(normal);
  float nDotd = max(0.f, dot(normalize(dir), n));

  //featureSize /= nDotd * 0.5f + 0.5f;
  featureSize /= nDotd * 0.2f + 0.8f;


  float log2Size         = log2(featureSize / minFeatureSize) + lodOffset;
  float featureSizeRound = exp2(floor(log2Size)) * minFeatureSize;

  return featureSizeRound;
}

// 3D periodic function used to slightly alter the shape of the hash cells: the cell walls will not longer be straight,
// practically avoiding aliasing artifacts on flat surfaces aligned with cell boundaries
vec3 waveFunction(vec3 pos, float featureSize)
{
  vec3 wave = vec3(sin(mod(pos.x + featureSize * 0.3f, featureSize) * 2.f * M_PI / (featureSize)) * featureSize * 0.02f,
                   sin(mod(pos.y + featureSize * 0.7f, featureSize) * 2.f * M_PI / (featureSize)) * featureSize * 0.02f,
                   sin(mod(pos.z + featureSize * 0.1f, featureSize) * 2.f * M_PI / (featureSize)) * featureSize * 0.02f);
  return wave;
}

uint hashPointLODOffsetInternal_Original(vec3 pos, uint normal, uint lodOffset, uint sessionId)
{

  vec3 dir = vec3(vpX - pos.x, vpY - pos.y, vpZ - pos.z);

  int hashVal = 0;  
  
  float featureSize = getFeatureSizeInWorldUnitsNormal(pos, uint(cb_PostEffect_HRTAO.cellSizeInPixels), 1e-10f, lodOffset, normal);

  vec3 wave = waveFunction(pos, featureSize);

  pos.x += wave.y + wave.z;
  pos.y += wave.x + wave.z;
  pos.z += wave.y + wave.x;

  ivec3 upos = ivec3(int((pos.z / featureSize)), int((pos.x / featureSize)), int((pos.y / featureSize)));

  ivec3 upos2 = (upos / 2)*2;
  ivec3 delta = upos2 - upos;
  upos        = upos2;

  hashVal = wangHash(upos.x + hashVal);
  hashVal = wangHash(upos.y + hashVal);
  hashVal = wangHash(upos.z + hashVal);

  hashVal = wangHash(hashVal + floatBitsToInt(featureSize));
  uint quantizedNormal = quantizeNormal(normal);
  hashVal = wangHash(int(quantizedNormal) + hashVal);
  hashVal = wangHash(int(sessionId) + hashVal);
  
  // Place cells in a 2x2x2 neighborhood together for locality
  hashVal += delta.x + 2 * delta.y + 4 * delta.z;

  hashVal = hashVal % int(cb_PostEffect_HRTAO.hashTableSize);
  return uint(abs(hashVal));
}



uint hashPointLODOffset(vec3 pos, uint normal, uint lodOffset, uint sessionId)
{
  uint base = hashPointLODOffsetInternal_Original(pos, normal, lodOffset + 0, sessionId);

  return base;
}

uint checksumLODOffsetInternal_Original(vec3 pos, uint normal, uint lodOffset)
{

  vec3 dir     = vec3(vpX - pos.x, vpY - pos.y, vpZ - pos.z);
  int  hashVal = 0;

  float featureSize = getFeatureSizeInWorldUnitsNormal(pos, uint(cb_PostEffect_HRTAO.cellSizeInPixels), 1e-10f, lodOffset, normal);


  vec3 wave = waveFunction(pos, featureSize);


  pos.x += wave.y + wave.z;
  pos.y += wave.x + wave.z;
  pos.z += wave.y + wave.x;


  ivec3 upos = ivec3(int((pos.z / featureSize)), int((pos.x / featureSize)), int((pos.y / featureSize)));

  ivec3 upos2 = (upos / 2) * 2;
  ivec3 delta = upos2 - upos;
  upos        = upos2;

  hashVal = xorshift32(upos.z + hashVal);
  hashVal = xorshift32(upos.x + hashVal);
  hashVal = xorshift32(upos.y + hashVal);

  uint quantizedNormal =quantizeNormal(normal);

  hashVal = xorshift32(int(quantizedNormal) + hashVal);
  hashVal = xorshift32(hashVal+floatBitsToInt(featureSize));

  hashVal += delta.x + 2 * delta.y + 4 * delta.z;

  uint result = uint(abs(hashVal));
  if (result == 0)
    result = 1;
  
  return result;
}




uint checksumLODOffset(vec3 pos, uint normal, uint lodOffset)
{
  uint base = checksumLODOffsetInternal_Original(pos, normal, lodOffset + 0);
  return base;
}

uint checksumLODPosOnly(vec3 pos, uint lodOffset)
{

  vec3  dir         = vec3(vpX - pos.x, vpY - pos.y, vpZ - pos.z);
  int   hashVal     = 0;
  float featureSize = getFeatureSizeInWorldUnits(length(dir), uint(cb_PostEffect_HRTAO.cellSizeInPixels), 1e-10f, lodOffset);

  ivec3 upos = ivec3(int((pos.z / featureSize)), int((pos.x / featureSize)), int((pos.y / featureSize)));

  ivec3 upos2 = (upos / 2) * 2;
  ivec3 delta = upos2 - upos;
  upos        = upos2;


  hashVal = xorshift32(upos.z + hashVal);
  hashVal = xorshift32(upos.x + hashVal);
  hashVal = xorshift32(upos.y + hashVal);

  hashVal = xorshift32(hashVal + floatBitsToInt(featureSize));

  hashVal += delta.x + 2 * delta.y + 4 * delta.z;

  uint result = uint(abs(hashVal));
  if(result == 0)
    result = 1;

  return result;
}

uint getSessionId(uint frameIndex)
{
  return frameIndex >> 16;
}

uint getFrameId(uint frameIndex)
{
  return frameIndex & 0xFFFF;
}
