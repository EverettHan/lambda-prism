/*
 * Copyright (c) 2018, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

// Access to the HashMapKeys: checksum, list access timestamp and pixel index corresponding to the last change for the entries

#define NO_PREVIOUS_ITEM (~0u >> 7)

// The index of the last change, last usage timestamp and the bit indicating whether a cell has been modified are stored in a single 32-bit word:
//  pppp pppp pppp pppp pppp pppp pttt tttT
//         
// The last change index p is stored in the 25 higher bits, the timestamp t in the lower 7 bits and the touched flag T in the lowest bit. 
// This allows a maximum of 33.5M entries, hence supporting 8K resolution with 1 entry per pixel

uint unpackLastPixel(uint lastpixelLastAccess)
{
  return lastpixelLastAccess >> 7;
}

uint unpackLastAccess(uint lastpixelLastAccess)
{
  return (lastpixelLastAccess >> 1) & 0x3F;
}
const uint maxLastAccess = 0x40;

bool unpackWasTouched(uint lastpixelLastAccess)
{
  return (lastpixelLastAccess & 0x1) == 1;
}

uint packLastPixelLastAccessWasTouched(uint lastPixel, uint lastAccess, bool wasTouched)
{
  return (lastPixel << 7) + ((lastAccess & 0x3F) << 1) + (wasTouched ? (0x1) : (0x0));
}

uint getSecondaryKey(uint hashMapKeyIndex)
{
  return hashMapKeys[hashMapKeyIndex];
}

uint getLastPixel25AndLastAccess7(uint hashMapKeyIndex)
{
  return hashMapKeys[cb_PostEffect_HRTAO.hashTableSize + 1 + hashMapKeyIndex];
}

uint getCellPixel(uint hashMapKeyIndex)
{
  return (hashMapKeys[2 * (cb_PostEffect_HRTAO.hashTableSize + 1) + hashMapKeyIndex] & ~(0x7F << 25));
}



uint framesSinceLastAccess(uint frameIdx, uint hashMapKeyIndex)
{
  uint fId = frameIdx & 0x3F;
  uint lastAccess = unpackLastAccess(getLastPixel25AndLastAccess7(hashMapKeyIndex));
  if(fId < lastAccess)
    fId += maxLastAccess;

  return fId - lastAccess;
}

uint getLastPixel(uint hashMapKeyIndex)
{
  return unpackLastPixel(getLastPixel25AndLastAccess7(hashMapKeyIndex));
}

uint setLastPixel(uint lastPixel, uint hashMapKeyIndex, out bool newlyTouched)
{

  uint lastAccess = cb_PostEffect_HRTAO_Auto.frameIdx & 0x3F;

  uint newVal = packLastPixelLastAccessWasTouched(lastPixel, lastAccess, true);

  uint previousValue = atomicExchange(hashMapKeys[cb_PostEffect_HRTAO.hashTableSize + 1 + hashMapKeyIndex], newVal);

  newlyTouched = !unpackWasTouched(previousValue);

  return unpackLastPixel(previousValue);
}

void resetLastPixel(uint hashMapKeyIndex)
{
  uint lastAccess = unpackLastAccess(getLastPixel25AndLastAccess7(hashMapKeyIndex));
  hashMapKeys[cb_PostEffect_HRTAO.hashTableSize + 1 + hashMapKeyIndex] = packLastPixelLastAccessWasTouched(~0u, lastAccess, false);
}

void setLastAccess(uint hashMapKeyIndex, uint lastAccess)
{
  hashMapKeys[cb_PostEffect_HRTAO.hashTableSize + 1 + hashMapKeyIndex] = packLastPixelLastAccessWasTouched(~0u, lastAccess, false);
}
