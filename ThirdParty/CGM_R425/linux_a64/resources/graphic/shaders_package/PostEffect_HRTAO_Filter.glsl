/*
* Copyright (c) 2017-2019, NVIDIA CORPORATION.  All rights reserved.
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


//#include "../bindings/filter_ao_bindings.h"

//#include "common.h"

//layout(binding = ePositions, rg32f, set = 0) uniform image2D positionNormals;
//#define HRTAO_GBUFFER_FETCH
//#include "common_spatial_hash.h"


// GBuffer with depth in X plus encoded normal in Y


// Hash cell indices, one LOD per component
//layout(binding = eCellId, rgba32ui, set = 0) uniform uimage2D cellIndices;
// AO as provided by FinalizeAO
//layout(binding = eAO) uniform sampler2D resultAO;

//layout(location = 0) in vec2 uv;
layout(location = 0) out vec4 col;

vec4 fetchResultAO(in ivec2 pixel)
{
  #if defined(SO_HRTAO_AS_ARRAY)
    ivec3 coords = ivec3(pixel, HASH_SLOT_ID);
  #else
    ivec2 coords = pixel;
  #endif

  #ifdef IS_MSAA
    return texelFetch(resultAO, coords, gl_SampleID);
  #else
    return texelFetch(resultAO, coords, 0);
  #endif
}

// Retursn true if the shaded point at the pixel is considered similar to the reference position and normal
bool isSuitable(ivec2 pixel, vec3 refPos, vec3 refNrm)
{
#ifdef IS_MSAA
  vec3 pos = getPosition(pixel, gl_SampleID);
#else
  vec3 pos = getPosition(pixel);
#endif
  vec3 dir = vec3(vpX - pos.x, vpY - pos.y, vpZ - pos.z);
  // Compute the minimum world-space feature size represented by the hash map, based on the 
  // user-provided, image-space feature size, and the distance from the eye to the shaded point
  float featureSize = getFeatureSizeInWorldUnits(length(dir), uint(cb_PostEffect_HRTAO.cellSizeInPixels), 1e-10f, 1);
  float sqFeatureSize = featureSize*featureSize;

  vec3 fromRefPos = pos.xyz - refPos;
  // If the points are too far away from each other, they are not similar
  if (sqFeatureSize < dot(fromRefPos, fromRefPos))
  {
    return false;
  }

  // If the normals are too different, the points are not similar neither
#ifdef IS_MSAA
  vec3 nrm = getNormal(pixel, gl_SampleID);
#else
  vec3 nrm = getNormal(pixel);
#endif
  if (dot(nrm, refNrm) < 0.9)
    return false;
  // If both tests passed, the points are similar
  return true;
}

vec4 getFilteredAO(ivec2 pixel)
{
  int counter=0;
  vec4 res = vec4(0);
  // This filter is applied 4 times (once per LOD), with filterStep=0,1,2,3 
  int filterSize = int(exp2(cb_PostEffect_HRTAO.filterStep)+1); 
  int step = filterSize; 
  
  #ifdef IS_MSAA
  uvec4 cellId = imageLoad(cellIndices, pixel, gl_SampleID);
  #else
  uvec4 cellId = imageLoad(cellIndices, pixel);
  #endif

  // In FinalizeAO, the cell IDs are modified to reflect whether they have been used 
  // in the computation of the AO. For example, when few samples are available, 
  // the FinalizeAO will use all higher LODs to compensate at the expense of spatial resolution. Conversely, when many samples
  // are available, it will only use the finer LOD and mark the others as unused.
  // For each pass n, if the n-th LOD is not defined, simply copy the previous result
  // This allows to filter on larger areas when few samples are available, and smaller 
  // when many samples are present, hence preserving as much detail as possible
  if (cb_PostEffect_HRTAO.filterStep == 1 && cellId.y == HASH_CELL_NOT_FOUND)
    return fetchResultAO(pixel);

  if (cb_PostEffect_HRTAO.filterStep == 2 && cellId.z == HASH_CELL_NOT_FOUND)
    return fetchResultAO(pixel);

  if (cb_PostEffect_HRTAO.filterStep == 3 && cellId.w == HASH_CELL_NOT_FOUND)
    return fetchResultAO(pixel);


#ifdef IS_MSAA
  vec3 pos = getPosition(pixel, gl_SampleID);
  vec3 nrm = getNormal(pixel, gl_SampleID);
#else
  vec3 pos = getPosition(pixel);
  vec3 nrm = getNormal(pixel);
#endif
  // Since the filter is applied 4 time sequentially, we can use interleaved sampling
  // to reduce bandwidth needs
  for(int x = -filterSize; x <=filterSize; x+= step)
  {
    int px = pixel.x + x;
    if (px >= 0 && px < resX)
    {
      for(int y = -filterSize; y <=filterSize; y+=step)
      {
        int py = pixel.y + y;
        if (py >= 0 && py < resY)
        {
          // If the shaded points in neighboring pixels are similar, average them with the 
          // AO value at the current pixel
          if (isSuitable(ivec2(px, py), pos.xyz, nrm))
          {
            res += fetchResultAO(ivec2(px, py));
            counter++;
          }
        }
      }
    }
  }
  if(counter > 0)
    return res/float(counter);
  return vec4(1.0, 1.0, 1.0, 1.0);
}

void main()
{
  ivec2 pixel = ivec2(gl_FragCoord.xy);
  
  #ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
    #ifdef IS_MSAA
      MaterialEval matEval = decodeMaterialEval(imageLoad(materialInfo1, pixel, gl_SampleID), imageLoad(materialInfo2, pixel, gl_SampleID));
    #else
      MaterialEval matEval = decodeMaterialEval(imageLoad(materialInfo1, pixel), imageLoad(materialInfo2, pixel));
    #endif
  #endif

  // The last debug output is used to show cells in false colors,
  // hence the first 3 steps do not do anything.
  if (cb_PostEffect_HRTAO.displayCells == 6 && cb_PostEffect_HRTAO.filterStep < 3)
  {
    #ifdef SO_HRTAO_COLOR
      col = fetchResultAO(pixel);
    #else
      col = fetchResultAO(pixel).xxxx;
    #endif

    return;
  }
  
  #if defined(SO_HRTAO_AS_ARRAY)
    ivec3 coords = ivec3(pixel, HASH_SLOT_ID);
  #else
    ivec2 coords = pixel;
  #endif

  // Various outputs for debug purposes
  switch (cb_PostEffect_HRTAO.displayCells)
  {
  // Unfiltered AO
  case 0:
    col = fetchResultAO(pixel);
    break;

  // Filtered
  case 1:
    #ifdef SO_HRTAO_COLOR
      col = getFilteredAO(pixel);
    #else
      col = getFilteredAO(pixel).xxxx;
    #endif
    break;

  // Cell indices in false colors at LOD 0
  case 2:
    #ifdef IS_MSAA
      col = vec4(cellIndexToColor(imageLoad(cellIndices, pixel, gl_SampleID).x), 1);
    #else
      col = vec4(cellIndexToColor(imageLoad(cellIndices, pixel).x), 1);
    #endif
    break;

  // Cell indices in false colors at LOD 1 if used, white otherwise
  case 3:
    #ifdef IS_MSAA
      col = vec4(cellIndexToColor(imageLoad(cellIndices, pixel, gl_SampleID).y), 1);
    #else
      col = vec4(cellIndexToColor(imageLoad(cellIndices, pixel).y), 1);
    #endif
    break;

  // Cell indices in false colors at LOD 2 if used, white otherwise
  case 4:
    #ifdef IS_MSAA
      col = vec4(cellIndexToColor(imageLoad(cellIndices, pixel, gl_SampleID).z), 1);
    #else
      col = vec4(cellIndexToColor(imageLoad(cellIndices, pixel).z), 1);
    #endif
    break;

  // Cell indices in false colors at LOD 3 if used, white otherwise
  case 5:
    #ifdef IS_MSAA
      col = vec4(cellIndexToColor(imageLoad(cellIndices, pixel, gl_SampleID).w), 1);
    #else
      col = vec4(cellIndexToColor(imageLoad(cellIndices, pixel).w), 1);
    #endif
    break;

  // Heat map representing which LODs are used: blue means only the finest LOD is used, 
  // which in turn means many samples are available and very little to no work has been done for that pixel
  // Further colors (green, yellow, red) show when LODs 1, 2 and 3 have been used, meaning more and more work
  // has been done for the pixel
  case 6:
    #ifdef IS_MSAA
      col = vec4(cellIndicesToHeat(imageLoad(cellIndices, pixel, gl_SampleID)), 1);//*texelFetch(resultAO, pixel, gl_SampleID).x;
    #else
      col = vec4(cellIndicesToHeat(imageLoad(cellIndices, pixel)), 1);//*texelFetch(resultAO, pixel, 0).x;
    #endif
    break;

#ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
  //Material buffer roughness
  case 7:
    col = vec4(vec3(matEval.perceptualRoughness), 1.0);
    break;

  //Material buffer normal
  case 8:
    col = vec4(vec3(matEval.shadingNormal), 1.0);
    break;

  //Material buffer metallic
  case 9:
    col = vec4(vec3(matEval.metallic), 1.0);
    break;

  //Material buffer base color
  case 10:
    col = vec4(vec3(matEval.baseColor), 1.0);
        break;

  //eResultDiffuse
  case 11:
    #ifdef IS_MSAA
      col = vec4(imageLoad(resultDiffuse, coords, gl_SampleID).xyz, 1);
    #else
      col = vec4(imageLoad(resultDiffuse, coords).xyz, 1);
    #endif
    break;
    
  //eResultGlossy
  case 12:
    #ifdef IS_MSAA
      col = vec4(imageLoad(resultGlossy, coords, gl_SampleID).xyz, 1);
    #else
      col = vec4(imageLoad(resultGlossy, coords).xyz, 1);
    #endif
    break;

  //eResultFilteredDiffuse
  case 13:
    #ifdef IS_MSAA
      col = vec4(imageLoad(outputImageDiffuse, coords, gl_SampleID).xyz, 1);
    #else
      col = vec4(imageLoad(outputImageDiffuse, coords).xyz, 1);
    #endif
    break;

  //eResultFilteredGlossy
  case 14:
    #ifdef IS_MSAA
      col = vec4(imageLoad(outputImageGlossy, coords, gl_SampleID).xyz, 1);
    #else
      col = vec4(imageLoad(outputImageGlossy, coords).xyz, 1);
    #endif
    break;
#endif
}



}
