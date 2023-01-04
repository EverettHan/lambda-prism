/*
* Copyright (c) 2017-2019, NVIDIA CORPORATION.  All rights reserved.
*
* NVIDIA CORPORATION and its licensors retain all intellectual property
* and proprietary rights in and to this software, related documentation
* and any modifications thereto.  Any use, reproduction, disclosure or
* distribution of this software and related documentation without an express
* license agreement from NVIDIA CORPORATION is strictly prohibited.
*/

//#version 450
//#extension GL_GOOGLE_include_directive : enable
//#extension GL_EXT_shader_explicit_arithmetic_types_float16 : enable
//#extension GL_EXT_shader_explicit_arithmetic_types_int16 : enable

//#include "common.h"

//#include "common_spatial_hash.h"
//#include "hash_data_type_color.h"

// Compute the per-pixel AO values from the hash map

//#include "../bindings/finalize_bindings.h"

// Hash cell indices, one LOD per component
//layout(binding = eCellId, rgba32ui, set = 0) uniform uimage2D cellIndices;

// Hash map contributions, containing the number of rays traced for that cell (16 bit, weight) and number of occlusions found (16 bit, contribution)
//layout(binding = eHashMapContribs) buffer hashMapBuffer { HashRecordContrib hashMap[]; };
// Local copy of the hash map contributions on the secondary GPU, if existing
//layout(binding = eLinkedHashMapContribs) buffer linkedHashMapBuffer { HashRecordContrib linkedHashMap[]; };

//layout(binding = eHashMapKeys) buffer hashMapKeysBuffer { HashRecordKey hashMapKeys[]; };

#ifdef SO_HRTAO_SHADOWS_COUNT
  #if HASH_SLOT_COUNT > 1
    #ifdef SO_HRTAO_ENABLE_AO
      #ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
        #define SHADOWS_FIRST_SLOT 1
        #define SHADOWS_FIRST_SLOT_LOC 2
      #else
        #define SHADOWS_FIRST_SLOT 1
        #define SHADOWS_FIRST_SLOT_LOC 1
      #endif
    #else
      #define SHADOWS_FIRST_SLOT 0
      #define SHADOWS_FIRST_SLOT_LOC 0
  #endif
#else
  #define SHADOWS_FIRST_SLOT 0
    #define SHADOWS_FIRST_SLOT_LOC 0
  #endif
#endif

// Output AO
#ifdef SO_HRTAO_ENABLE_AO
  layout(location = 0) out vec3 col;

  #ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
    layout(location = 1) out vec3 glossy;
  #endif
#endif

#ifdef SO_HRTAO_SHADOWS_COUNT
  #if SO_HRTAO_SHADOWS_COUNT>0
    layout(location = SHADOWS_FIRST_SLOT_LOC) out vec3 shadow1;
  #endif

  #if SO_HRTAO_SHADOWS_COUNT>1
    layout(location = SHADOWS_FIRST_SLOT_LOC+1) out vec3 shadow2;
  #endif

  #if SO_HRTAO_SHADOWS_COUNT>2
    layout(location = SHADOWS_FIRST_SLOT_LOC+2) out vec3 shadow3;
  #endif

  #if SO_HRTAO_SHADOWS_COUNT>3
    layout(location = SHADOWS_FIRST_SLOT_LOC+3) out vec3 shadow4;
  #endif
#endif

//#include "hash_data_access_color.h"
//#include "hash_key_access.h"

//#include "finalize_common.h"

void main()
{  
  ivec2 pixel = ivec2(gl_FragCoord.xy);

  if (pixel == ivec2(0, 0))
    resetPixelsToUpdate();

  uvec4 outCellIds = uvec4(HASH_CELL_NOT_FOUND);
  
  // Get the cell IDs for each of the 4 LODs
  #ifdef IS_MSAA
    uvec4 cellIds = imageLoad(cellIndices, ivec2(gl_FragCoord.xy), gl_SampleID);
  #else
    uvec4 cellIds = imageLoad(cellIndices, ivec2(gl_FragCoord.xy));
  #endif
  
  HASH_OUTPUT_VALUE lighting;

  #ifdef SO_HRTAO_ENABLE_AO
    #if HASH_SLOT_COUNT > 1
      lighting = finalizeHashValue(cellIds, outCellIds, 0);
    #else
      lighting = finalizeHashValue(cellIds, outCellIds);
    #endif

    #ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
      col = clamp(lighting.irradiance, vec3(0.0), vec3(1.0));
      glossy = clamp(lighting.specular, vec3(0.0), vec3(1.0));
    #else
      col = pow(clamp(lighting, vec3(0.0), vec3(1.0)), vec3(cb_PostEffect_HRTAO.aoPower));
    #endif
  #endif
    
  #if SO_HRTAO_SHADOWS_COUNT>0
    lighting = finalizeHashValue(cellIds, outCellIds, SHADOWS_FIRST_SLOT);

    #ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
      shadow1 = clamp(lighting.irradiance, vec3(0.0), vec3(1.0));
    #else
      shadow1 = lighting;
    #endif
  #endif
  
  #if SO_HRTAO_SHADOWS_COUNT>1
    lighting = finalizeHashValue(cellIds, outCellIds, SHADOWS_FIRST_SLOT+1);

    #ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
      shadow2 = clamp(lighting.irradiance, vec3(0.0), vec3(1.0));
    #else
      shadow2 = lighting;
    #endif
  #endif
  
  #if SO_HRTAO_SHADOWS_COUNT>2
    lighting = finalizeHashValue(cellIds, outCellIds, SHADOWS_FIRST_SLOT+2);

    #ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
      shadow3 = clamp(lighting.irradiance, vec3(0.0), vec3(1.0));
    #else
      shadow3 = lighting;
    #endif
  #endif
  
  #if SO_HRTAO_SHADOWS_COUNT>3
    lighting = finalizeHashValue(cellIds, outCellIds, SHADOWS_FIRST_SLOT+3);

    #ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
      shadow4 = clamp(lighting.irradiance, vec3(0.0), vec3(1.0));
    #else
      shadow4 = lighting;
    #endif
  #endif
  
  // Store the cells that have actually been used in the AO estimate. This will be used during screen-space filtering:
  // if only the finest level was needed, this means the AO is well-resolved, and thus only a small filtering kernel will be sufficient.
  // On the other hand, if the coarser LODs are used we know we can apply a large filtering kernel without loss of detail, hence
  // mitigating noise and filtering out block artifacts.

  memoryBarrier();

  #ifdef IS_MSAA
    imageStore(cellIndices, ivec2(gl_FragCoord.xy), gl_SampleID, outCellIds);
  #else
    imageStore(cellIndices, ivec2(gl_FragCoord.xy), outCellIds);
  #endif
}
