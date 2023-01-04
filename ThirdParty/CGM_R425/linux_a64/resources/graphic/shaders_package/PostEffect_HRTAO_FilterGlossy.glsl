/*
* Copyright (c) 2017-2022, NVIDIA CORPORATION.  All rights reserved.
*
* NVIDIA CORPORATION and its licensors retain all intellectual property
* and proprietary rights in and to this software, related documentation
* and any modifications thereto.  Any use, reproduction, disclosure or
* distribution of this software and related documentation without an express
* license agreement from NVIDIA CORPORATION is strictly prohibited.
*/

// Hierarchical, bilateral filter to clean-up discretization artifacts while preserving the highest available level of detail

//#version 450
//#extension GL_GOOGLE_include_directive : enable


//#include "../bindings/filter_glossy_bindings.h"

//#include "common.h"

//layout(binding = ePositions, rgba32f, set = 0) uniform image2D positionNormals;
//#include "common_spatial_hash.h"


// Hash cell indices, one LOD per component
//layout(binding = eCellId, rgba32ui, set = 0) uniform uimage2D cellIndices;
// Diffuse and Glossy outputs provided by Finalize
//layout(binding = eDiffuse, rgba32f, set = 0) uniform image2D resultDiffuse;
//layout(binding = eGlossy, rgba32f, set = 0) uniform image2D resultGlossy;


//layout(binding = eOutputImagesDiffuse, rgba32f, set = 0) uniform image2D outputImagesDiffuse[2];
//layout(binding = eOutputImagesGlossy, rgba32f, set = 0) uniform image2D outputImagesGlossy[2];

float sq(float x)
{
  return x * x;
}

uint pow2(uint v)
{
  return 1 << v;
}


uint getFrameId()
{
  return getFrameId(cb_PostEffect_HRTAO_Auto.frameIdx);
}

#if HASH_SLOT_COUNT > 1
  #ifdef IS_MSAA
    #define myImageLoad(img, pixel) imageLoad(img, ivec3(pixel.xy, HASH_SLOT_ID), pixel.z)
    #define myImageLoadNoArray(img, pixel) imageLoad(img, pixel.xy, pixel.z)
  #else
    #define myImageLoad(img, pixel) imageLoad(img, ivec3(pixel.xy, HASH_SLOT_ID))
    #define myImageLoadNoArray(img, pixel) imageLoad(img, pixel.xy)
  #endif
#else
  #ifdef IS_MSAA
    #define myImageLoad(img, pixel) imageLoad(img, pixel.xy, pixel.z)
    #define myImageLoadNoArray(img, pixel) imageLoad(img, pixel.xy, pixel.z)
  #else
    #define myImageLoad(img, pixel) imageLoad(img, pixel.xy)
    #define myImageLoadNoArray(img, pixel) imageLoad(img, pixel.xy)
  #endif
#endif

#ifdef IS_MSAA
vec3 getPosition(ivec3 pixel)
#else
vec3 getPosition(ivec2 pixel)
#endif
{
  vec4 pn = uintBitsToFloat(myImageLoadNoArray(positionNormals, pixel));
  return pn.xyz;
}

#ifdef IS_MSAA
vec3 getNormal(ivec3 pixel, out bool isValid)
#else
vec3 getNormal(ivec2 pixel, out bool isValid)
#endif
{
  uvec4 pn = myImageLoadNoArray(positionNormals, pixel);
  if(pn.w == 0)
  {
    isValid = false;
    return vec3(0.f);
  }
  isValid = true;
  return decompress_unit_vec(pn.w);
}

// Returns true if the shaded point at the pixel is considered similar to the reference position and normal
#ifdef IS_MSAA
bool isSuitable(ivec3 pixel, vec3 refPos, vec3 refNrm, float featureSizeDiffuse, float featureSizeGlossy, out bool suitableDiffuse, out bool suitableGlossy)
#else
bool isSuitable(ivec2 pixel, vec3 refPos, vec3 refNrm, float featureSizeDiffuse, float featureSizeGlossy, out bool suitableDiffuse, out bool suitableGlossy)
#endif
{
  suitableDiffuse = suitableGlossy = false;

  vec3 pos, nrm;
  pos      = getPosition(pixel);
  vec3 dir = vec3(vpX - pos.x, vpY - pos.y, vpZ - pos.z);

  vec3 fromRefPos = pos.xyz - refPos;

  bool isValid;
  nrm = getNormal(pixel, isValid);

  if(!isValid)
    return false;

  // If the normals are too different, the points are not similar neither
  if(dot(nrm, refNrm) < 0.99)
    return false;

  // Both points have to be roughly on the same plane
  float distFromRefPos = length(fromRefPos);
  if(abs(dot(fromRefPos / distFromRefPos, nrm)) > 0.01f)
    return false;

  // If the points are too far away from each other, they are not similar
  if(featureSizeDiffuse >= distFromRefPos)
  {
    suitableDiffuse = true;
  }
  if(featureSizeGlossy >= distFromRefPos)
  {
    suitableGlossy = true;
  }

  // If all tests passed, the points are similar
  return suitableDiffuse || suitableGlossy;
}

#ifdef IS_MSAA
vec4 getPixelDiffuse(ivec3 pixel)
#else
vec4 getPixelDiffuse(ivec2 pixel)
#endif
{
  if(cb_PostEffect_HRTAO.filterStep == 0)
    return myImageLoad(resultDiffuse, pixel);
  return myImageLoad(outputImageDiffuse, pixel);
}

#ifdef IS_MSAA
vec4 getPixelDiffusePrevious(ivec3 pixel)
#else
vec4 getPixelDiffusePrevious(ivec2 pixel)
#endif
{
  if(cb_PostEffect_HRTAO.filterStep <= 1)
    return myImageLoad(resultDiffuse, pixel);
  return myImageLoad(outputImageDiffusePrev, pixel);
}

#ifdef IS_MSAA
vec4 getPixelGlossy(ivec3 pixel)
#else
vec4 getPixelGlossy(ivec2 pixel)
#endif
{
  if(cb_PostEffect_HRTAO.filterStep == 0)
    return myImageLoad(resultGlossy, pixel);
  return myImageLoad(outputImageGlossy, pixel);
}

#ifdef IS_MSAA
vec4 getPixelGlossyPrevious(ivec3 pixel)
#else
vec4 getPixelGlossyPrevious(ivec2 pixel)
#endif
{
  if(cb_PostEffect_HRTAO.filterStep <= 1)
    return myImageLoad(resultGlossy, pixel);
  return myImageLoad(outputImageGlossyPrev, pixel);
}

struct RunningStat
{
  int   n;
  float oldM, newM, oldS, newS;
};

void initStat(inout RunningStat s)
{
  s.n = 0;
}

void pushStat(inout RunningStat s, float x)
{
  s.n++;
  // See Knuth TAOCP vol 2, 3rd edition, page 232
  if(s.n == 1)
  {
    s.oldM = s.newM = x;
    s.oldS          = 0.0;
  }
  else
  {
    s.newM = s.oldM + (x - s.oldM) / s.n;
    s.newS = s.oldS + (x - s.oldM) * (x - s.newM);

    // set up for next iteration
    s.oldM = s.newM;
    s.oldS = s.newS;
  }
}

float meanStat(RunningStat s)
{
  if(s.n == 0)
    return 0.f;
  return s.newM;
}

float varianceStat(RunningStat s)
{
  return ((s.n > 1) ? s.newS / (s.n - 1) : 0.0);
}

#ifdef IS_MSAA
void getFilteredGlossy(ivec3 pixel, uint lodOffsetDiffuse, uint lodOffsetGlossy, out vec4 diffuse, out vec4 glossy)
#else
void getFilteredGlossy(ivec2 pixel, uint lodOffsetDiffuse, uint lodOffsetGlossy, out vec4 diffuse, out vec4 glossy)
#endif
{
  diffuse = getPixelDiffuse(pixel);
  glossy  = getPixelGlossy(pixel);

  vec4  refDiffuse          = getPixelDiffusePrevious(pixel);
  float refLuminanceDiffuse = CIELuminance(refDiffuse.xyz);
  float refVarianceDiffuse  = refDiffuse.w;

  vec4  refGlossy          = getPixelGlossyPrevious(pixel);
  float refLuminanceGlossy = CIELuminance(refGlossy.xyz);
  float refVarianceGlossy  = refGlossy.w;

  int totalFilterSize = int(pow2(5));

  int step           = min(2, int(cb_PostEffect_HRTAO.filterStep + 1));
  int filterSize = 2 * step;

  if(cb_PostEffect_HRTAO.displayCells == 0) // Unfiltered debug output
  {
    return;
  }

  vec3 pos = getPosition(pixel);
  bool isValid;
  vec3 nrm = getNormal(pixel, isValid);

  if(!isValid)
  {
    diffuse = glossy = vec4(0.f);
    return;
  }
  vec3  dir      = vec3(vpX - pos.x, vpY - pos.y, vpZ - pos.z);
  float distance = length(dir);
  // Compute the minimum world-space feature size represented by the hash map, based on the
  // user-provided, image-space feature size, and the distance from the eye to the shaded point
  float featureSizeDiffuse = 2 * getContinuousFeatureSizeInWorldUnits(distance, uint(cb_PostEffect_HRTAO.cellSizeInPixels), 1e-10f, lodOffsetDiffuse);
  float featureSizeGlossy = 2 * getContinuousFeatureSizeInWorldUnits(distance, uint(cb_PostEffect_HRTAO.cellSizeInPixels), 1e-10f, lodOffsetGlossy);

  // Since the filter is applied 4 time sequentially, we can use interleaved sampling
  // to reduce bandwidth needs
  RunningStat statDiffuse, statGlossy;
  initStat(statDiffuse);
  initStat(statGlossy);
  float counterDiffuse = 1.f, counterGlossy = 1.f;
  for(int x = -filterSize; x <= filterSize; x += step)
  {
    int px = pixel.x + x;
    if(px >= 0 && px < resX)
    {

      for(int y = -filterSize; y <= filterSize; y += step)
      {
        if(x == 0 && y == 0)
          continue;
        int py = pixel.y + y;
        if(py >= 0 && py < resY)
        {
          // If the shaded points in neighboring pixels are similar, average them with the
          // lighting value at the current pixel
          bool suitableDiffuse = true, suitableGlossy = true;
        #ifdef IS_MSAA
          if(isSuitable(ivec3(px, py, pixel.z), pos, nrm, featureSizeDiffuse, featureSizeGlossy, suitableDiffuse, suitableGlossy))
        #else
          if(isSuitable(ivec2(px, py), pos, nrm, featureSizeDiffuse, featureSizeGlossy, suitableDiffuse, suitableGlossy))
        #endif
          {
            #ifdef IS_MSAA
              vec4 valueDiffuse = getPixelDiffuse(ivec3(px, py, pixel.z));
              vec4 valueGlossy  = getPixelGlossy(ivec3(px, py, pixel.z));
            #else
              vec4 valueDiffuse = getPixelDiffuse(ivec2(px, py));
              vec4 valueGlossy  = getPixelGlossy(ivec2(px, py));
            #endif


            float distanceInPixels = max(abs(x), abs(y));
            float weight           = 1.f - clamp((distanceInPixels / filterSize), 0.f, 1.f);

            float luminanceDiffuse     = CIELuminance(valueDiffuse.xyz);
            float luminanceDiffDiffuse = abs(luminanceDiffuse - refLuminanceDiffuse);

            float luminanceGlossy     = CIELuminance(valueGlossy.xyz);
            float luminanceDiffGlossy = abs(luminanceGlossy - refLuminanceGlossy);

            // Variance-based weighting to reduce footprint when variance decreases. See https://cg.ivd.kit.edu/publications/2017/svgf/svgf_preprint.pdf
            float wlDiffuse = cb_PostEffect_HRTAO.filterStep == 0 ? 1.f : clamp(exp(-luminanceDiffDiffuse / (4.f * refVarianceDiffuse)), 0.f, 1.f);
            float wlGlossy = cb_PostEffect_HRTAO.filterStep == 0 ? 1.f : clamp(exp(-luminanceDiffGlossy / (16.f * refVarianceGlossy)), 0.f, 1.f);

            {
              if(suitableDiffuse)
              {
                diffuse += valueDiffuse * weight * wlDiffuse;
                counterDiffuse += weight * wlDiffuse;
                pushStat(statDiffuse, luminanceDiffuse);
              }
              if(suitableGlossy)
              {
                glossy += valueGlossy * weight * wlGlossy;
                counterGlossy += weight * wlGlossy;
                pushStat(statGlossy, luminanceGlossy);
              }
            }
          }
        }
      }
    }
  }

  float varianceDiffuse = varianceStat(statDiffuse);
  float varianceGlossy  = varianceStat(statGlossy);
  diffuse               = vec4(diffuse.xyz / float(max(1, counterDiffuse)), sqrt(varianceDiffuse));
  glossy                = vec4(glossy.xyz / float(max(1, counterGlossy)), sqrt(varianceGlossy));
}

layout(local_size_x = 16, local_size_y = 16, local_size_z = 1) in;

void main()
{
  uvec2 index = gl_GlobalInvocationID.xy;

  if(index.x >= resX || index.y >= resY)
    return;


  #ifdef IS_MSAA
    ivec3 pixel = ivec3(index.x, index.y, gl_GlobalInvocationID.z);
  #else
    ivec2 pixel = ivec2(index.x, index.y);
  #endif
  
  uvec4 currentCellId = myImageLoadNoArray(cellIndices, pixel);

  if(currentCellId.x == HASH_CELL_NOT_FOUND)
  {
    return;
  }

  uint currentLod = 0;
  if(currentCellId.y != HASH_CELL_NOT_FOUND)
    currentLod = 1;
  if(currentCellId.z != HASH_CELL_NOT_FOUND)
    currentLod = 2;
  if(currentCellId.w != HASH_CELL_NOT_FOUND)
    currentLod = 3;

  vec4 diffuse = vec4(0.f), glossy = vec4(0.f);

  getFilteredGlossy(pixel, currentLod + 1, currentLod + 2, diffuse, glossy);

  // Debug outputs
  if(cb_PostEffect_HRTAO.displayCells >= 2 && cb_PostEffect_HRTAO.displayCells <= 5) // Cell IDs
  {
    diffuse = vec4(cellIndexToColor(currentCellId[cb_PostEffect_HRTAO.displayCells - 2]), 1.f);
  }
  if(cb_PostEffect_HRTAO.displayCells == 6) // Workload
  {
    switch(currentLod)
    {
      case 3:
        diffuse = vec4(1, 0, 0, 1) * diffuse;
        break;
      case 2:
        diffuse = vec4(1, 1, 0, 1) * diffuse;
        break;
      case 1:
        diffuse = vec4(0, 1, 0, 1) * diffuse;
        break;
      case 0:
        diffuse = vec4(0, 0, 1, 1) * diffuse;
        break;
    }
  }

  #if HASH_SLOT_COUNT > 1
    ivec3 coords = ivec3(pixel.xy, HASH_SLOT_ID);
  #else
    ivec2 coords = ivec2(pixel.xy);
  #endif

  #ifdef IS_MSAA
    imageStore(outputImageDiffusePrev, coords, pixel.z, diffuse);
    imageStore(outputImageGlossyPrev, coords, pixel.z, glossy);
  #else
    imageStore(outputImageDiffusePrev, coords, diffuse);
    imageStore(outputImageGlossyPrev, coords, glossy);
  #endif
}
