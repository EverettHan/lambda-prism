/*
* Copyright (c) 2017-2019, NVIDIA CORPORATION.  All rights reserved.
*
* NVIDIA CORPORATION and its licensors retain all intellectual property
* and proprietary rights in and to this software, related documentation
* and any modifications thereto.  Any use, reproduction, disclosure or
* distribution of this software and related documentation without an express
* license agreement from NVIDIA CORPORATION is strictly prohibited.
*/

// Reset the number of pixels to update during this frame
void resetPixelsToUpdate()
{
  #if HASH_SLOT_COUNT > 1
  for(int i=0; i<HASH_SLOT_COUNT; i++)
    setWeight(HASH_CELL(cb_PostEffect_HRTAO.hashTableSize, i), 0);
  #else
    setWeight(HASH_CELL(cb_PostEffect_HRTAO.hashTableSize), 0);
  #endif
}


// Get the AO value for a given cell, along with the number of samples (weight) it was computed from
#if HASH_SLOT_COUNT > 1
void getCellContrib(uint cellId, inout HASH_OUTPUT_VALUE ao, inout uint weight, uint slot)
#else
void getCellContrib(uint cellId, inout HASH_OUTPUT_VALUE ao, inout uint weight)
#endif
{
  if (cellId != HASH_CELL_NOT_FOUND)
  {
    // Get the contribution and weight of the first GPU
    #if HASH_SLOT_COUNT > 1
      HashRecordContrib contrib = HASH_CELL(cellId, slot);
    #else
      HashRecordContrib contrib = HASH_CELL(cellId);
    #endif

    // Deduce the AO value
    if (getWeight(contrib) > 0)
    {
      ao = getOutputValue(contrib);
      weight = getWeight(contrib);
      return;
    }
  }

  weight = 0;
  ao = zeroOutputValue();
}

// Combines AO values at multiple LODs to provide trade off noise for spatial smoothness
#if HASH_SLOT_COUNT > 1
HASH_OUTPUT_VALUE getHashOutputValueInternal(in uvec4 cellIds, inout uvec4 outCellIds, uint slot)
#else
HASH_OUTPUT_VALUE getHashOutputValueInternal(in uvec4 cellIds, inout uvec4 outCellIds)
#endif
{
  // Result AO
  HASH_OUTPUT_VALUE ao = zeroOutputValue();
  // Minimum of samples the AO value must be computed from: those samples will be accumulated 
  // from multiple LODs if needed
  const uint threshold = cb_PostEffect_HRTAO.minSampleCountPerCell;
  const float inverseTreshold = 1.0/float(threshold);

  HASH_OUTPUT_VALUE cellAo[4] = {zeroOutputValue(), zeroOutputValue(),zeroOutputValue(),zeroOutputValue()}; 
  uvec4 wAo = uvec4(0);

  // Get the AO value and weight for the finest LOD
  #if HASH_SLOT_COUNT > 1
    getCellContrib(cellIds.x, cellAo[0], wAo.x, slot);
  #else
    getCellContrib(cellIds.x, cellAo[0], wAo.x);
  #endif
  // Records which LODs will be used when estimating the AO: for example
  // if the finest cell contains many samples, outCellIds will only contain 
  // that finest cell cellIds.x, and HASH_CELL_NOT_FOUND for the other LODs 
  // since they will not be used. For now, we only mark the finest LOD there.
  outCellIds = uvec4(cellIds.x, uvec3(HASH_CELL_NOT_FOUND));
  
  // When combining LODs, we assign a weight to each of them, depending on the 
  // number of samples already available in finer LODs, and the target sample count
  HASH_OUTPUT_COMPONENT_TYPE weights[4] = {HASH_OUTPUT_COMPONENT_TYPE(0), HASH_OUTPUT_COMPONENT_TYPE(0), HASH_OUTPUT_COMPONENT_TYPE(0), HASH_OUTPUT_COMPONENT_TYPE(0)};

  uint combinedW = wAo.x;
  // The samples of the finest level are taken first, and we compute their weight
  // with respect to the target sample count
  weights[0] = max(HASH_OUTPUT_COMPONENT_TYPE(0.f), min(HASH_OUTPUT_COMPONENT_TYPE(1.f),    HASH_OUTPUT_COMPONENT_TYPE(wAo.x*inverseTreshold)));

  // If not enough samples are contained in the finest level, fill in with the information
  // in the coarser levels using the same principle. If a LOD gets used, we mark it in outCellIds
  if ( combinedW < threshold)
  {
    outCellIds.y = cellIds.y;
    #if HASH_SLOT_COUNT > 1
      getCellContrib(cellIds.y, cellAo[1], wAo.y, slot);
    #else
      getCellContrib(cellIds.y, cellAo[1], wAo.y);
    #endif
    weights[1] = max(HASH_OUTPUT_COMPONENT_TYPE(0.f), min(HASH_OUTPUT_COMPONENT_TYPE(1.f)-weights[0], HASH_OUTPUT_COMPONENT_TYPE(wAo.y*inverseTreshold)));
    combinedW += wAo.y;
    if (  combinedW < threshold)
    {
      outCellIds.z = cellIds.z;
      #if HASH_SLOT_COUNT > 1
        getCellContrib(cellIds.z, cellAo[2], wAo.z, slot);
      #else
        getCellContrib(cellIds.z, cellAo[2], wAo.z);
      #endif
      weights[2] = max(HASH_OUTPUT_COMPONENT_TYPE(0.f), min(HASH_OUTPUT_COMPONENT_TYPE(1.f)-weights[0]-weights[1], HASH_OUTPUT_COMPONENT_TYPE(wAo.z*inverseTreshold)));
      combinedW += wAo.z;
      if (combinedW < threshold)
      {
        outCellIds.w = cellIds.w;
        #if HASH_SLOT_COUNT > 1
          getCellContrib(cellIds.w, cellAo[3], wAo.w, slot);
        #else
          getCellContrib(cellIds.w, cellAo[3], wAo.w);
        #endif
        weights[3] = max(HASH_OUTPUT_COMPONENT_TYPE(0.f), min(HASH_OUTPUT_COMPONENT_TYPE(1.f)-weights[0]-weights[1]-weights[2], HASH_OUTPUT_COMPONENT_TYPE(wAo.w*inverseTreshold)));
      }
    }
  }

  // Normalize the contributions of all levels
  HASH_OUTPUT_COMPONENT_TYPE w= HASH_OUTPUT_COMPONENT_TYPE(0.0);
  if (wAo.x != 0)
    w+=weights[0];

  if (wAo.y != 0)
    w+=weights[1];

  if (wAo.z != 0)
    w+=weights[2];

  if (wAo.w != 0)
    w+=weights[3];

  if (w > 0.f)
    ao = mixLODs(cellAo[0], weights[0], cellAo[1], weights[1], cellAo[2], weights[2], cellAo[3], weights[3]);
  else
    ao = cellAo[0];

  return ao;
}

#if HASH_SLOT_COUNT > 1
HASH_OUTPUT_VALUE getHashOutputValue(in uvec4 cellIds, inout uvec4 outCellIds, uint slot)
#else
HASH_OUTPUT_VALUE getHashOutputValue(in uvec4 cellIds, inout uvec4 outCellIds)
#endif
{

  #if HASH_SLOT_COUNT > 1
    return getHashOutputValueInternal(cellIds, outCellIds, slot);
  #else
    return getHashOutputValueInternal(cellIds, outCellIds);
  #endif

}

#if HASH_SLOT_COUNT > 1
HASH_OUTPUT_VALUE finalizeHashValue(in uvec4 cellIds, inout uvec4 outCellIds, uint slot)
#else
HASH_OUTPUT_VALUE finalizeHashValue(in uvec4 cellIds, inout uvec4 outCellIds)
#endif
{

  #if HASH_SLOT_COUNT > 1
    HASH_OUTPUT_VALUE ao = getHashOutputValue(cellIds, outCellIds, slot);
  #else
    HASH_OUTPUT_VALUE ao = getHashOutputValue(cellIds, outCellIds);
  #endif

  return ao;
}
