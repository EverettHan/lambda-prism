/*
* Copyright (c) 2017-2019, NVIDIA CORPORATION.  All rights reserved.
*
* NVIDIA CORPORATION and its licensors retain all intellectual property
* and proprietary rights in and to this software, related documentation
* and any modifications thereto.  Any use, reproduction, disclosure or
* distribution of this software and related documentation without an express
* license agreement from NVIDIA CORPORATION is strictly prohibited.
*/

// Get the number of linked lists entry points, that is equivalent to the number of modified hash cells
uint getHeadsListSize(uint touchedListOffset)
{
  return headsList[resY * resX * resZ + touchedListOffset];
}

// Commit the change list into the hash map data
void commitChangelist()
{
  uint touchedListOffset = (cb_PostEffect_HRTAO.filterStep % 2 == 0) ? 0 : (resX * resY * resZ + 1);

  // Reset the change lists sizes for the next step
  if(gl_GlobalInvocationID.x == 0)
  {
    if(cb_PostEffect_HRTAO.filterStep % 2 == 0)
    {
      SET_CL_SIZE(changeListB, HASH_SLOT_COUNT * getHeadsListSize(touchedListOffset));
      headsList[2 * resX * resY * resZ + 1] = 0;
    }
    else
    {
      SET_CL_SIZE(changeListA, HASH_SLOT_COUNT * getHeadsListSize(touchedListOffset));
      headsList[resX * resY * resZ] = 0;
    }
  }
  
  uint index = gl_GlobalInvocationID.x;

  if(index >= getHeadsListSize(touchedListOffset))
    return;

  // Get the target cell id
  uint cellId = headsList[index + touchedListOffset];
  // The hash key for that cell contains the index of the last change list item related to the entry
  uint headItem = getLastPixel(cellId);

  #if HASH_SLOT_COUNT > 1
    HashRecordContrib allContribWeights[HASH_SLOT_COUNT];
    
    for(int i=0; i<HASH_SLOT_COUNT; i++)
      allContribWeights[i] = zeroContrib();
  #endif

  // Fetch the contribution of that change list item, slot index, and the index of the previous change list item related to the same cell
  HashRecordContrib contribWeight;
  uint prev;

  #if HASH_SLOT_COUNT > 1
    uint slot;
    prev = getInputContribPrev(headItem, contribWeight, false, slot);
    allContribWeights[slot] = contribWeight;
  #else
    prev = getInputContribPrev(headItem, contribWeight, false);
  #endif
    
  uint previousClId = prev;

  if(previousClId != headItem && previousClId != 0)
  {
    // Walk through the change list items for the target cell and mix their contributions
    while(previousClId != NO_PREVIOUS_ITEM)
    {
      HashRecordContrib previousContrib;

      #if HASH_SLOT_COUNT > 1
        previousClId = getInputContribPrev(previousClId, previousContrib, false, slot);
        allContribWeights[slot] = addContribWeight(allContribWeights[slot], previousContrib);
      #else
        previousClId = getInputContribPrev(previousClId, previousContrib, false);
        contribWeight = addContribWeight(contribWeight, previousContrib);
      #endif
    }
  }

  #if HASH_SLOT_COUNT > 1
    for(int i=0; i<HASH_SLOT_COUNT; i++)
    {
      uint pixelId = getPackedInputPixelId(headItem, false);
      // Add the total contribution to the hash map
      addContribWeightToHashEntry(cellId, allContribWeights[i], cb_PostEffect_HRTAO.filterStep == 0, pixelId, i);

      // Create a new change list item for the coarser LOD and add it to the other change list
      HASH_CHANGE_LIST_ITEM item = makeChangeListItem(allContribWeights[i], i, ~0u, pixelId);
      setOutputItem(HASH_SLOT_COUNT * index + i, item, false);
    }
  #else
    uint pixelId = getPackedInputPixelId(headItem, false);
    // Add the total contribution to the hash map
    addContribWeightToHashEntry(cellId, contribWeight, cb_PostEffect_HRTAO.filterStep == 0, pixelId);

    // Create a new change list item for the coarser LOD and add it to the other change list
    HASH_CHANGE_LIST_ITEM item    = makeChangeListItem(contribWeight, ~0u, pixelId);
    setOutputItem(index, item, false);
  #endif

}
