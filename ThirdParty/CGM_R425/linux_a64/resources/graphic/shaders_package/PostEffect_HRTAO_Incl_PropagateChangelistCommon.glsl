/*
* Copyright (c) 2017-2019, NVIDIA CORPORATION.  All rights reserved.
*
* NVIDIA CORPORATION and its licensors retain all intellectual property
* and proprietary rights in and to this software, related documentation
* and any modifications thereto.  Any use, reproduction, disclosure or
* distribution of this software and related documentation without an express
* license agreement from NVIDIA CORPORATION is strictly prohibited.
*/

// Propagate a change list from the current LOD to the next

void propagateChangelist()
{
  uint index = gl_GlobalInvocationID.x;

  if (index >= getInputSize(true))
    return;

  uint pixelId = getInputPixelId(index, true);

  if (pixelId == ~0u)
  {
    setPreviousItem(index, 0, true);
    return;
  }
  

  int smp = 0;
  
  if(resZ > 1)
    smp = int(pixelId/(resX*resY)); //z coordinate is sampleID when in MSAA

  pixelId = pixelId%(resX*resY);
  ivec2 pixel = ivec2( pixelId%resX, pixelId/resX); 
  
  uint cellId = getParentId(pixel, smp);
  if (cellId != HASH_CELL_NOT_FOUND)
  {
    bool newlyTouched = false;
    uint previousChangeToCell = setLastPixel(index, cellId, newlyTouched);
  
    if (newlyTouched)
    {
      uint touchedListOffset = (cb_PostEffect_HRTAO.filterStep % 2 == 1) ? 0 : (resX * resY * resZ + 1);
      uint touchedCellIndex = atomicAdd(headsList[resX * resY * resZ + touchedListOffset], 1);
      headsList[touchedListOffset + touchedCellIndex] = cellId;
    }
        
    setPreviousItem(index, previousChangeToCell, true);  
  }
  else
  {
    setPreviousItem(index, 0, true);
  }
}
