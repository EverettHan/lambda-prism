/*
* Copyright (c) 2017-2019, NVIDIA CORPORATION.  All rights reserved.
*
* NVIDIA CORPORATION and its licensors retain all intellectual property
* and proprietary rights in and to this software, related documentation
* and any modifications thereto.  Any use, reproduction, disclosure or
* distribution of this software and related documentation without an express
* license agreement from NVIDIA CORPORATION is strictly prohibited.
*/

//#version 460
//#extension GL_ARB_separate_shader_objects : enable

//#extension GL_GOOGLE_include_directive : enable



//#include "common.h"
//#include "common_spatial_hash.h"
//#include "hash_data_type_ao.h"

 
//#include "../bindings/commit_changelist_bindings.h"

layout(local_size_x = 256, local_size_y = 1, local_size_z = 1) in;


// Hash cell indices, one LOD per component
//layout(binding = eInputCellIds, set=0) uniform usampler2D cellIndices;
// Change list from the last raytracing on GPU0: for each pixel, the change list stores a uvec4, for which each
// component contains a number of occlusions (16bit) and number of rays traced for a particular LOD (16bit)
//layout(binding = eChangeListA, set = 0) buffer changeListABuffer { HASH_CHANGE_LIST_BASE_TYPE changeListA[];};

// Hash map contributions, containing the number of rays traced for that cell (16 bit, weight) and number of occlusions found (16 bit, contribution)
//layout(binding = eHashMapKeys, set=0) buffer hashMapKeysBuffer { HashRecordKey hashMapKeys[]; };
//layout(binding = eHashMapContribs, set=0) buffer hashMapContribsBuffer { HashRecordContrib hashMap[]; };
//layout(binding = eChangeListB, set = 0) buffer changeListBBuffer { HASH_CHANGE_LIST_BASE_TYPE changeListB[];};
//layout(binding = eHeadsList, set = 0) buffer headsListBuffer { uint headsList[];};

//#include "hash_key_access.h"
//#include "hash_data_access_ao.h"
//#include "changelist_access.h"

//#include "commit_changelist_common.h"


void main() {
  commitChangelist();
}
