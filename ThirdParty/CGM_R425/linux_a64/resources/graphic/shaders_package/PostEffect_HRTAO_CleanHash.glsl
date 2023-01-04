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
//#extension GL_KHR_shader_subgroup_ballot: enable


//#include "common.h"
//#include "common_spatial_hash.h"


//#include "../bindings/clean_hash_bindings.h"

layout(local_size_x = 256, local_size_y = 1, local_size_z = 1) in;


// Hash map contributions, containing the number of rays traced for that cell (16 bit, weight) and number of occlusions found (16 bit, contribution)
//layout(binding = eHashMapKeys, set=0) buffer hashMapKeysBuffer { HashRecordKey hashMapKeys[]; };
//layout(binding = eTouchedList, set=0) buffer touchedListBuffer { uint touchedCells[]; };

//#include "hash_key_access.h"


//void addOccupiedCells(uint counter)
//{
//  if (frameIdx%2==0)
//    atomicAdd(hashMapKeys[hashTableSize], counter);
//  else
//    atomicAdd(hashMapKeys[2*hashTableSize], counter);
//}
//
//void incrementOccupiedCells()
//{
//  if (frameIdx%2==0)
//    atomicAdd(hashMapKeys[hashTableSize], 1);
//  else
//    atomicAdd(hashMapKeys[2*hashTableSize], 1);
//}
//uint getOccupiedCells()
//{
//  if (frameIdx%2==0)
//    return hashMapKeys[2*hashTableSize];
//  else
//    return hashMapKeys[hashTableSize];
//}
//
void main() {
    uint index = gl_GlobalInvocationID.x;


    if (cb_PostEffect_HRTAO.cleanupPass == 0)
    {
      if (index >= cb_PostEffect_HRTAO.hashTableSize)
        return;

      uint key = hashMapKeys[index];
      
      if (key !=0 || getFrameId(cb_PostEffect_HRTAO_Auto.frameIdx) == 0)
      {
        //float fillRate = float(getOccupiedCells())/float(hashTableSize);

        uint lifespan = cb_PostEffect_HRTAO.cellLifespan;//(cellLifespan*(hashTableSize-getOccupiedCells()))/hashTableSize;

        bool hasValidEntry = framesSinceLastAccess(cb_PostEffect_HRTAO_Auto.frameIdx, index) <= lifespan;
        
        if (!hasValidEntry || getFrameId(cb_PostEffect_HRTAO_Auto.frameIdx) == 0)
          hashMapKeys[index] = 0;
        else
        {
        
          //incrementOccupiedCells();
          if (getLastPixel(index) != NO_PREVIOUS_ITEM)

            resetLastPixel(index);
        }
      }
    }
    else
    {
      uint touchedListOffset = (cb_PostEffect_HRTAO.filterStep%2==0)?0:(resX*resY*resZ+1);
      if (touchedCells[resY*resX*resZ+touchedListOffset] == 0)
        return;
      if (getLastPixel(index) != NO_PREVIOUS_ITEM)
        resetLastPixel(index);

    }
  }
