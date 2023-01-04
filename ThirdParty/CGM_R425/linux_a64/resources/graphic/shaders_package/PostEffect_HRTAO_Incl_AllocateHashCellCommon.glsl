/*
* Copyright (c) 2017-2019, NVIDIA CORPORATION.  All rights reserved.
*
* NVIDIA CORPORATION and its licensors retain all intellectual property
* and proprietary rights in and to this software, related documentation
* and any modifications thereto.  Any use, reproduction, disclosure or
* distribution of this software and related documentation without an express
* license agreement from NVIDIA CORPORATION is strictly prohibited.
*/

// Compute the hash ID and reserve the cells in the hash map at 4 successive LODs


// Store metadata in an additional, inaccessible cell of the hash map
// void incrementOccupiedCells()
// {
//   if (frameIdx%2==0)
//     atomicAdd(hashMapKeys[hashTableSize], 1);
//   else
//     atomicAdd(hashMapKeys[2*hashTableSize+1], 1);
// }
// uint getOccupiedCells()
// {
//   if (frameIdx%2==0)
//     return hashMapKeys[2*hashTableSize+1];
//   else
//     return hashMapKeys[hashTableSize];
// }


// Write whether the cell will need to be cleared on the secondary device
// Removed NVLINK support in this version
//void setClearFlag(inout bvec4 clearFlags, int lodOffset)
//{
//  switch(lodOffset)
//  {
//    case 0:
//      clearFlags.x = true;
//      break;
//    case 1:
//      clearFlags.y = true;
//      break;
//    case 2:
//      clearFlags.z = true;
//      break;
//    case 3:
//      clearFlags.w = true;
//      break;
//  }
//}
//
//// Write the clear flags in the lower-weight bits of the mantissa of the world-space positions
//void writeClearFlags(ivec2 index, vec4 pos, bvec4 clearFlags)
//{
//  // //ivec2 index = ivec2(gl_FragCoord.xy);
//
//  // uvec3 ures = uvec3(floatBitsToUint(pos.x), floatBitsToUint(pos.y), floatBitsToUint(pos.z));
//  // // First LOD in the last bit of X
//  // if (clearFlags.x)
//  //   ures.x |=  1;
//  // // Second LOD in the next-to-last bit of X
//  // if (clearFlags.y)
//  //   ures.x |=  2;
//  // // Third LOD in the last bit of Y
//  // if (clearFlags.z)
//  //   ures.y |=  1;
//  // // Fourth LOD in the last bit of Z
//  // if (clearFlags.w)
//  //   ures.z |=  1;
//
//  // vec4 res = vec4(uintBitsToFloat(ures.x), uintBitsToFloat(ures.y), uintBitsToFloat(ures.z), pos.w);
//
//  // imageStore(positions, index, res);
//}

// Allocate a cell for a given shaded point, at a given LOD
uint checkCellLodSearch(vec4 pos, uint nrm, inout bvec4 clearFlags, int lodOffset, inout int searchLodOffset)
{

  uint result = 0;
  // // Compute the hash key for that point
  uint check        = checksumLODOffset(pos.xyz, nrm, lodOffset + searchLodOffset);
  uint hashVal      = hashPointLODOffset(pos.xyz, nrm, lodOffset + searchLodOffset, getSessionId(cb_PostEffect_HRTAO_Auto.frameIdx));
  bool rehashed     = true;
  bool hasCollision = false;

  uint hopsToSucceed = 0;
  for(uint i = 0; i < 100; i++)
  {
    // Compute the hash key for that point
    if(!rehashed)
    {
      hashVal = hashPointLODOffset(pos.xyz, nrm, lodOffset + searchLodOffset, getSessionId(cb_PostEffect_HRTAO_Auto.frameIdx));
      // Compute the checksum value for that point
      check = checksumLODOffset(pos.xyz, nrm, lodOffset + searchLodOffset);
    }
    else
      rehashed = false;

    // Could be used as a semaphore to protect a cell while it is being updated
    //if (hashMapKeys[hashVal].lastAccess !=
    //0xFFFFFFFF) // Ensure we are not currently erasing the record
    {

      {
        if(hashMapKeys[hashVal] == check)
        {
          return hashVal;
        }
        if(hashMapKeys[hashVal] == 0)
        {
          return HASH_CELL_NOT_FOUND;
        }
      }
      //else
    }
    hasCollision = true;
    hopsToSucceed++;
    // If no free slot has been found after 32 hops, continue the search at a coarser LOD
    if(i % 32 == 31)
      searchLodOffset++;
    else
    {
      // If the target slot is used, rehash the key
      hashVal  = uint(wangHash(int(hashVal))) % cb_PostEffect_HRTAO.hashTableSize;
      rehashed = true;
    }
  }
}

// Allocate a cell for a given shaded point, at a given LOD
uint allocCellLodSearch(vec4 pos, uint nrm, inout bvec4 clearFlags, int lodOffset, inout int searchLodOffset)
{

  uint result = 0;
  // // Compute the hash key for that point
  uint check        = checksumLODOffset(pos.xyz, nrm, lodOffset + searchLodOffset);
  uint hashVal      = hashPointLODOffset(pos.xyz, nrm, lodOffset + searchLodOffset, getSessionId(cb_PostEffect_HRTAO_Auto.frameIdx));
  bool rehashed     = true;
  bool hasCollision = false;
  if(cb_PostEffect_HRTAO.hashVisualizeMode != -1)
  {
    atomicAdd(hashMapVisualizeData.allocations, 1);
  }
  uint hopsToSucceed = 0;
  for(uint i = 0; i < 100; i++)
  {
    // Compute the hash key for that point
    if(!rehashed)
    {
      hashVal = hashPointLODOffset(pos.xyz, nrm, lodOffset + searchLodOffset, getSessionId(cb_PostEffect_HRTAO_Auto.frameIdx));
      // Compute the checksum value for that point
      check = checksumLODOffset(pos.xyz, nrm, lodOffset + searchLodOffset);
    }
    else
      rehashed = false;

    // Could be used as a semaphore to protect a cell while it is being updated
    //if (hashMapKeys[hashVal].lastAccess !=
    //0xFFFFFFFF) // Ensure we are not currently erasing the record
    {

      {
        if(hashMapKeys[hashVal] == check)
        {
          result = check;
          break;
        }
      }
      //else
      {
        // If the cell is empty (checksum==0) or corresponding to the shaded point, the cell is found
        result = atomicCompSwap(hashMapKeys[hashVal], 0, check);
        if(result == 0 || result == check)
        {
          //result=0
          break;
        }
      }
    }
    hasCollision = true;
    hopsToSucceed++;
    // If no free slot has been found after 32 hops, continue the search at a coarser LOD
    if(i % 32 == 31)
      searchLodOffset++;
    else
    {
      // If the target slot is used, rehash the key
      hashVal  = uint(wangHash(int(hashVal))) % cb_PostEffect_HRTAO.hashTableSize;
      rehashed = true;
    }
  }

  // If we found an empty slot (0) or a slot corresponding to the shaded point (check)
  if(result == 0 || result == check)
  {
    if(cb_PostEffect_HRTAO.hashVisualizeMode != -1 && hasCollision)
    {
      atomicAdd(hashMapVisualizeData.collisions, 1);
      atomicAdd(hashMapVisualizeData.hopsToSucceed, hopsToSucceed);
      atomicMax(hashMapVisualizeData.maxHopsToSucceed, hopsToSucceed);
    }
    setLastAccess(hashVal, getFrameId(cb_PostEffect_HRTAO_Auto.frameIdx));

    // If the cell has been newly allocated
    if(result == 0)
    {
      // Reset the contributions of the cell
      #if HASH_SLOT_COUNT > 1
        for(int i=0; i<HASH_SLOT_COUNT; i++)
        {
          HASH_CELL(hashVal, i) = zeroContrib();
        }
      #else
        HASH_CELL(hashVal) = zeroContrib();
      #endif
      // Update the time stamp of the cell to the current frame
    }

    return hashVal;
  }
  else
  {
    if(cb_PostEffect_HRTAO.hashVisualizeMode != -1)
    {
      atomicAdd(hashMapVisualizeData.fails, 1);
    }
    // If the linear search failed, indicate no cell has been found, which will result in no AO for that pixel
    return HASH_CELL_NOT_FOUND;
  }
}


uint allocCell(vec4 pos, uint nrm, int lodOffset, inout bvec4 clearFlags, inout int searchLodOffset)
{
  return allocCellLodSearch(pos, nrm, clearFlags, lodOffset, searchLodOffset);
}


uvec4 allocateHashCell(ivec2 index, out vec4 posNormal)
{

  bvec4 clearFlags  = bvec4(false);
  #ifdef IS_MSAA
    vec4 pos = vec4(getPosition(index, gl_SampleID), 1);
  #else
    vec4 pos = vec4(getPosition(index), 1);
  #endif

  uvec4 cellIndices = uvec4(HASH_CELL_NOT_FOUND);

  // Return if no geometry has been hit through that pixel
  if(pos.xyz == vec3(0))
  {
    return cellIndices;
  }
  
  #ifdef IS_MSAA
    uint normal = getPackedNormal(index, gl_SampleID);
  #else
    uint normal = getPackedNormal(index);
  #endif
  
  posNormal.xyz = pos.xyz;
  posNormal.w   = uintBitsToFloat(normal);

  int searchLodOffset = 0;

  // Allocate a cell at the ideal LOD for that point
  uint hashVal  = allocCell(pos, normal, 0, clearFlags, searchLodOffset);
  cellIndices.x = hashVal;

  if(hashVal != HASH_CELL_NOT_FOUND)
  {
    bool needLODs = false;

    #if HASH_SLOT_COUNT > 1
      for(int i=0; i<HASH_SLOT_COUNT; i++)
      {
        uint currentSampleCount = getWeight(HASH_CELL(hashVal, i));

        if(currentSampleCount <= cb_PostEffect_HRTAO.maxSamplesPerCell)
        {
          needLODs = true;
          break;
        }
      }
    #else
      uint currentSampleCount = getWeight(HASH_CELL(hashVal));
      needLODs = currentSampleCount <= cb_PostEffect_HRTAO.maxSamplesPerCell;
    #endif

    // If the ideal cell does not contain its maximum number of samples, we will need the
    // rougher LODs

    //Disable for now...
    if(needLODs /*&& false*/)
    {
      // Allocate cells for 3 more LODs
      cellIndices.y = allocCell(pos, normal, 1, clearFlags, searchLodOffset);
      cellIndices.z = allocCell(pos, normal, 2, clearFlags, searchLodOffset);
      cellIndices.w = allocCell(pos, normal, 3, clearFlags, searchLodOffset);
      // Increment the counter of pixel needing to be updated
      incrementPixelsToUpdate();
    }
    else
    {
      // If the cell is already fully resolved, no need for other LODs at that pixel
      cellIndices.y = HASH_CELL_NOT_FOUND;
      cellIndices.z = HASH_CELL_NOT_FOUND;
      cellIndices.w = HASH_CELL_NOT_FOUND;
    }
  }
  //else //second allocation attempt?
  //{
  //  cellIndices.x = allocCell(pos, normal, 1, clearFlags, searchLodOffset);
  //  cellIndices.y = allocCell(pos, normal, 2, clearFlags, searchLodOffset);
  //  cellIndices.z = allocCell(pos, normal, 3, clearFlags, searchLodOffset);
  //  cellIndices.w = HASH_CELL_NOT_FOUND;
  //}

  return cellIndices;
}
