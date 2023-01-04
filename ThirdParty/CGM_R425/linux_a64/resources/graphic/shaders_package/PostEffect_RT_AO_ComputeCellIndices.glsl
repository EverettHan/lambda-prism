layout(location = 0) out uvec4 cellIndices;

//#ifdef IS_MSAA
//  uniform coherent layout(rgba32f) image2DMS positions;
//#else
//  uniform coherent layout(rgba32f) image2D positions;
//#endif

// Hash map keys, each containing a checksum and the last time the cell was used
//layout(std430) buffer hashMapBufferKey
//{
//  HashRecordKey hashMapKeys[];
//};

// Hash map contributions, containing the number of rays traced for that cell (16 bit, weight) and number of occlusions found (16 bit, contribution)
//layout(std430) buffer hashMapBufferContrib
//{
//  HashRecordContrib hashMapContribs[];
//};

// Store metadata in an additional, inaccessible cell of the hash map
void incrementOccupiedCells()
{
  atomicAdd(hashMapKeys[cb_PostEffect_RT_AO.u_HashTableSize].secondaryKey, 1);
}

uint getOccupiedCells()
{
  return hashMapKeys[cb_PostEffect_RT_AO.u_HashTableSize].secondaryKey;
}

void incrementPixelsToUpdate()
{
  atomicAdd(hashMapContribs[cb_PostEffect_RT_AO.u_HashTableSize].contribWeight, 1);
}

uint getPixelsToUpdate()
{
  return hashMapContribs[cb_PostEffect_RT_AO.u_HashTableSize].contribWeight;
}

// Allocate a cell for a given shaded point, at a given LOD
uint allocCell(vec4 pos, vec3 nrm, int lodOffset, inout bvec4 clearFlags)
{
  uint result = 0;
  // Compute the hash key for that point
  uint hashValOrig = hashPointLODOffset(pos.xyz, nrm, lodOffset, getSessionId(cb_PostEffect_RT_AO_Auto.u_FrameIdx));
  uint hashVal = hashValOrig;
  // Compute the checksum value for that point
  uint check = checksumLODOffset(pos.xyz, nrm, lodOffset);

  // Perform a linear search from the hash key onwards, until we find an available slot
  // 64 is chosen empirically - in practical cases a slot is always found within that range
  for (uint i = 0; i < 64; i++)
  {
    // Could be used as a semaphore to protect a cell while it is being updated
    //if (hashMapKeys[hashVal].lastAccess !=
    //0xFFFFFFFF) // Ensure we are not currently erasing the record
    {
      // If the cell is empty (checksum==0) or corresponding to the shaded point, the cell is found
      result = atomicCompSwap(hashMapKeys[hashVal].secondaryKey, 0, check);
      if (result == 0 || result == check) {
        break;
      }
      else {
        // Otherwise, check the last time the cell was used: if it was not used in the last 10 frames, 
        // replace it.
        uint lastAccess = hashMapKeys[hashVal].lastAccess;
        if (abs(int(cb_PostEffect_RT_AO_Auto.u_FrameIdx) - int(lastAccess)) > 10)
        {
          // Could be used as a semaphore to protect a cell while it is being updated
          // Not used here due to the cost of atomic, and no visible artifacts so far
          //uint overwrite = atomicCompSwap(hashMapKeys[hashVal].lastAccess,
          //                                lastAccess, 0xFFFFFFFF);
          // uint overwrite = hashMapKeys[hashVal].lastAccess;
          //if (overwrite == lastAccess) 
          {
            // Reset the hash map entry
            hashMapKeys[hashVal].secondaryKey = check;
            // Mark as if we found an empty slot
            result = 0;
            break;
          }
        }
      }
    }
    // Increment the hash value for the linear search
    hashVal = (hashVal + 1) % cb_PostEffect_RT_AO.u_HashTableSize;
  }
  // If we found an empty slot (0) or a slot corresponding to the shaded point (check)
  if (result == 0 || result == check)
  {
    // Update the time stamp of the cell to the current frame
    hashMapKeys[hashVal].lastAccess = cb_PostEffect_RT_AO_Auto.u_FrameIdx;
    // If the cell has been newly allocated
    if (result == 0)
    {
      // Reset the contributions of the cell
      hashMapContribs[hashVal].contribWeight = 0;
    }

    return hashVal;
  }
  else
    // If the linear search failed, indicate no cell has been found, which will result in no AO for that pixel
    return HASH_CELL_NOT_FOUND;
}

void main(void)
{
  ivec2 index = ivec2(gl_FragCoord.xy);
  bvec4 clearFlags = bvec4(false);

  #ifdef IS_MSAA
    vec4 pos = imageLoad(positions, ivec2(index), gl_SampleID);
  #else
    vec4 pos = imageLoad(positions, ivec2(index));
  #endif

  // Return if no geometry has been hit through that pixel
  if (pos.xyz == vec3(0)) {
    cellIndices = uvec4(HASH_CELL_NOT_FOUND);
    return;
  }
  vec3 normal = decompress_unit_vec(floatBitsToUint(pos.w));

  // Allocate a cell at the ideal LOD for that point
  uint hashVal = allocCell(pos, normal.xyz, 0, clearFlags);
  cellIndices.x = hashVal;
  if (hashVal != HASH_CELL_NOT_FOUND)
  {
    uint currentSampleCount = getWeight(hashMapContribs[hashVal].contribWeight);

    // If the ideal cell does not contain its maximum number of samples, we will need the
    // rougher LODs
    if (currentSampleCount <= cb_PostEffect_RT_AO.u_MaxSamplesPerCell)
    {
      // Allocate cells for 3 more LODs
      cellIndices.y = allocCell(pos, normal.xyz, 1, clearFlags);
      cellIndices.z = allocCell(pos, normal.xyz, 2, clearFlags);
      cellIndices.w = allocCell(pos, normal.xyz, 3, clearFlags);
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
}
