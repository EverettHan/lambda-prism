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

//#include "common.h"
//#include "common_spatial_hash.h"
//#include "hash_data_type_ao.h"

// Compute the per-pixel AO values from the hash map

//#include "../bindings/finalize_bindings.h"

// Hash cell indices, one LOD per component
//layout(binding = eCellId, rgba32ui, set = 0) uniform uimage2D cellIndices;

// Hash map contributions, containing the number of rays traced for that cell (16 bit, weight) and number of occlusions found (16 bit, contribution)
//layout(binding = eHashMapContribs) buffer hashMapBuffer { HashRecordContrib hashMap[]; };
// Local copy of the hash map contributions on the secondary GPU, if existing
//layout(binding = eLinkedHashMapContribs) buffer linkedHashMapBuffer { HashRecordContrib linkedHashMap[]; };

//layout(binding = eHashMapKeys) buffer hashMapKeysBuffer { HashRecordKey hashMapKeys[]; };

// Screen-space coordinates
//layout(location = 0) in vec2 uv;
// Output AO
layout(location = 0) out HASH_OUTPUT_VALUE col;


//#include "hash_data_access_ao.h"
//#include "hash_key_access.h"
//#include "finalize_common.h"

void main()
{
  col = finalizeHashValue();
  col = pow(clamp(col, HASH_OUTPUT_VALUE(0.0), HASH_OUTPUT_VALUE(1.0)), cb_PostEffect_HRTAO.aoPower);
}
