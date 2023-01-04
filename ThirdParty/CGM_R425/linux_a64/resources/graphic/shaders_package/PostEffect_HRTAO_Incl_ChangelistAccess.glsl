/*
 * Copyright (c) 2018, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

// Get the target hash cell id at the current LOD and the hash cell id of its parent
uvec2 getCellAndParentId(ivec2 pixel, int iSampleOrLOD)
{
  uvec4 cellIds = texelFetch(cellIndices, pixel, iSampleOrLOD);
  switch(cb_PostEffect_HRTAO.filterStep)
  {
    case 0:
      return cellIds.xy;
    case 1:
      return cellIds.yz;
    case 2:
      return cellIds.zw;
    case 3:
      return uvec2(cellIds.w, HASH_CELL_NOT_FOUND);
    default:  // must not happen
      return uvec2(HASH_CELL_NOT_FOUND);
  }
}

// Get the cell id of the current parent LOD
uint getParentId(ivec2 pixel, int iSampleOrLOD)
{
  uvec4 cellIds = texelFetch(cellIndices, pixel, iSampleOrLOD);
  switch(cb_PostEffect_HRTAO.filterStep)
  {
    case 0:
      return cellIds.y;
    case 1:
      return cellIds.z;
    case 2:
      return cellIds.w;
    case 3:
      return HASH_CELL_NOT_FOUND;
    default:  // must not happen
      return HASH_CELL_NOT_FOUND;
  }
}

// Set a change list item in the appropriate change list according to the current step
void setOutputItem(uint index, HASH_CHANGE_LIST_ITEM item, bool invert)
{
  if(cb_PostEffect_HRTAO.filterStep % 2 == (invert ? 1 : 0))
  {
    SET_CL_ITEM(changeListB, index, item);
  }
  else
  {
    SET_CL_ITEM(changeListA, index, item);
  }
}


// Set the index of the previous change list item for that change list item
void setPreviousItem(uint index, uint prev, bool invert)
{
  if(cb_PostEffect_HRTAO.filterStep % 2 == (invert ? 1 : 0))
  {
    SET_CL_PREVIOUS_ITEM(changeListA, index, prev);
  }
  else
  {
    SET_CL_PREVIOUS_ITEM(changeListB, index, prev);
  }
}

// Get the index of the pixel corresponding to a given change list item index
uint getPackedInputPixelId(uint item, bool invert)
{
  if(cb_PostEffect_HRTAO.filterStep % 2 == (invert ? 1 : 0))
  {
    return GET_CL_PIXEL_ID(changeListA, item);
  }
  else
  {
    return GET_CL_PIXEL_ID(changeListB, item);
  }
}

uint getInputPixelId(uint item, bool invert)
{
  return unpackPixelId(getPackedInputPixelId(item, invert));
}

// Get the contribution, contrib slot and the index of the previous change list item for the same hash cell id
#if HASH_SLOT_COUNT > 1
  uint getInputContribPrev(uint item, out HashRecordContrib contrib, bool invert, out uint slot)
#else
  uint getInputContribPrev(uint item, out HashRecordContrib contrib, bool invert)
#endif
{
  uint prev;
  if(cb_PostEffect_HRTAO.filterStep % 2 == (invert ? 1 : 0))
  {
    #if HASH_SLOT_COUNT > 1
      GET_CL_CONTRIB_PREV(changeListA, item, contrib, prev, slot);
    #else
      GET_CL_CONTRIB_PREV(changeListA, item, contrib, prev);
    #endif
    return prev;
  }
  else
  {
    #if HASH_SLOT_COUNT > 1
      GET_CL_CONTRIB_PREV(changeListB, item, contrib, prev, slot);
    #else
      GET_CL_CONTRIB_PREV(changeListB, item, contrib, prev);
    #endif
    return prev;
  }
}

// Get the number of change list items at the current step
uint getInputSize(bool invert)
{
  if(cb_PostEffect_HRTAO.filterStep % 2 == (invert ? 1 : 0))
    return GET_CL_SIZE(changeListA);
  else
    return GET_CL_SIZE(changeListB);
}
