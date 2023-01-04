/*
 * Copyright (c) 2018, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

// Macros and functions to access change lists and hash map data for the ambient occlusion mode

#define FLOAT16_MAX (65504.0f)

// Set the payload of the change list item
#if HASH_SLOT_COUNT > 1 
  #define SET_CL_ITEM(cl, index, item)                                                                                   \
  {                                                                                                                      \
    cl[(CL_ENTRY_SIZE-1) * index + 0]                                  = item.c.contrib16Weight16;                       \
    cl[(CL_ENTRY_SIZE-1) * index + 1]                                  = item.slot;                                      \
    cl[(CL_ENTRY_SIZE-1) * index + 2]                                  = item.previous;                                  \
    cl[(CL_ENTRY_SIZE-1) * resX * resY * resZ * HASH_SLOT_COUNT + index] = item.pixelId;                                 \
  }
#else
  #define SET_CL_ITEM(cl, index, item)                                                                                   \
  {                                                                                                                      \
    cl[(CL_ENTRY_SIZE-1) * index + 0]                                  = item.c.contrib16Weight16;                       \
    cl[(CL_ENTRY_SIZE-1) * index + 1]                                  = item.previous;                                  \
    cl[(CL_ENTRY_SIZE-1) * resX * resY * resZ * HASH_SLOT_COUNT + index] = item.pixelId;                                 \
  }
#endif

// Set the index of the previous change list item for the same cell id
#if HASH_SLOT_COUNT > 1
  #define SET_CL_PREVIOUS_ITEM(cl, index, prevId) cl[(CL_ENTRY_SIZE-1) * index + 2] = prevId;
#else
  #define SET_CL_PREVIOUS_ITEM(cl, index, prevId) cl[(CL_ENTRY_SIZE-1) * index + 1] = prevId;
#endif

// Get the index of the pixel related to the change list item
#define GET_CL_PIXEL_ID(cl, index) cl[(CL_ENTRY_SIZE-1) * resY * resX * resZ * HASH_SLOT_COUNT + index]

// Get the contribution and sample count of the change list item
#if HASH_SLOT_COUNT > 1
  #define GET_CL_CONTRIB_PREV(cl, index, contrib, prev, slot)                                                          \
  {                                                                                                                    \
    contrib.contrib16Weight16    = cl[(CL_ENTRY_SIZE-1) * index + 0];                                                  \
    slot                         = cl[(CL_ENTRY_SIZE-1) * index + 1];                                                  \
    prev                         = cl[(CL_ENTRY_SIZE-1) * index + 2];                                                  \
  }
#else
  #define GET_CL_CONTRIB_PREV(cl, index, contrib, prev)                                                                \
  {                                                                                                                    \
    contrib.contrib16Weight16    = cl[(CL_ENTRY_SIZE-1) * index + 0];                                                  \
    prev                         = cl[(CL_ENTRY_SIZE-1) * index + 1];                                                  \
  }
#endif

// Get the number of elements in the change list
#define GET_CL_SIZE(cl) cl[CL_ENTRY_SIZE * resX * resY * resZ * HASH_SLOT_COUNT]


// Set the number of elements in the change list
#define SET_CL_SIZE(cl, size) cl[CL_ENTRY_SIZE * resX * resY * resZ * HASH_SLOT_COUNT] = size

// Reserve a slot in the change list
#define RESERVE_CL_ITEM atomicAdd(changeList[CL_ENTRY_SIZE * resX * resY * resZ * HASH_SLOT_COUNT], 1)

// Alias for a cell in the hashmap
#if HASH_SLOT_COUNT > 1
  #define HASH_CELL(id, slot) (hashMap[(id)].slots[(slot)])
#else
  #define HASH_CELL(id) (hashMap[(id)])
#endif

uint packPixelIdRoughness(uint pixelId, float roughness)
{
  return pixelId;
}

float unpackRoughness(uint pixelIdRoughness)
{
  return 0.0;
}

uint unpackPixelId(uint pixelIdRoughness)
{
  return pixelIdRoughness;
}

// Create a change list item from a contribution, the index of the previous change list item for the same pixel, and the corresponding pixel id
#if HASH_SLOT_COUNT > 1
HASH_CHANGE_LIST_ITEM makeChangeListItem(HashRecordContrib c, uint slot, uint previous, uint pixelId)
#else
HASH_CHANGE_LIST_ITEM makeChangeListItem(HashRecordContrib c, uint previous, uint pixelId)
#endif
{ 
  ChangeListItem item;
  item.c = c;

  #if HASH_SLOT_COUNT > 1
    item.slot = slot;
  #endif

  item.previous = previous;
  item.pixelId = pixelId;

  return item;
}

#if HASH_SLOT_COUNT > 1
HASH_CHANGE_LIST_ITEM makeChangeListItem(HashRecordContrib c, uint slot, uint previous, uint pixelId, float roughness)
#else
HASH_CHANGE_LIST_ITEM makeChangeListItem(HashRecordContrib c, uint previous, uint pixelId, float roughness)
#endif
{ 
  #if HASH_SLOT_COUNT > 1
    return makeChangeListItem(c, slot, previous, pixelId);
  #else
    return makeChangeListItem(c, previous, pixelId);
  #endif
}

// Create an empty change list item
#if HASH_SLOT_COUNT > 1
HASH_CHANGE_LIST_ITEM makeEmptyChangeListItem(uint slot)
#else
HASH_CHANGE_LIST_ITEM makeEmptyChangeListItem()
#endif
{    
  ChangeListItem clItem;
  clItem.c.contrib16Weight16 = 0;

#if HASH_SLOT_COUNT > 1
  clItem.slot = slot;
#endif

  clItem.previous = ~0u;
  clItem.pixelId = ~0u;

  return clItem;
}

// Erase the sample count from the contribution
void eraseWeight(inout HashRecordContrib c)
{
  c.contrib16Weight16 &= 0xFFFF;
}

// Get a null contribution
HASH_OUTPUT_VALUE zeroOutputValue()
{
  return HASH_OUTPUT_VALUE(0.0f);
}

// Add two contributions
HashRecordContrib addContribWeight(HashRecordContrib c1, HashRecordContrib c2)
{
  HashRecordContrib r;
  r.contrib16Weight16 = c1.contrib16Weight16 + c2.contrib16Weight16;
  return r;
}

// Get the total number of rays traced
uint getWeight(HashRecordContrib c)
{
  return c.contrib16Weight16 >> 16;
}

bool allowedToAddWeights(HashRecordContrib a, HashRecordContrib b)
{
  return getWeight(a) + getWeight(b) < 0xFFFF;
}

// Add a contribution to the hash entry at cellId. In the first pass we add contributions from the raytracing pass, which
// has already added the sample count. In this case we indicate isContribWeightBakedIn=true to avoid adding the weight twice
#if HASH_SLOT_COUNT > 1
void addContribWeightToHashEntry(uint cellId, HashRecordContrib c, bool isContribWeightBakedIn, uint pixelId, uint slot)
#else
void addContribWeightToHashEntry(uint cellId, HashRecordContrib c, bool isContribWeightBakedIn, uint pixelId)
#endif
{
  if(isContribWeightBakedIn)
    eraseWeight(c);


  #if HASH_SLOT_COUNT > 1
    if(!allowedToAddWeights(c, HASH_CELL(cellId, slot)))
      return;
    HASH_CELL(cellId, slot) = addContribWeight(HASH_CELL(cellId, slot), c);
  #else
    if(!allowedToAddWeights(c, HASH_CELL(cellId)))
      return;
    HASH_CELL(cellId) = addContribWeight(HASH_CELL(cellId), c);
  #endif
}

// Make a contribution from a number of non-hitting rays c and a total number of rays w
HashRecordContrib makeContrib(uint c, uint w)
{
  HashRecordContrib r;
  r.contrib16Weight16 = (c & 0xFFFF) + (w << 16);
  return r;
}

HASH_OUTPUT_VALUE mixLODs(HASH_OUTPUT_VALUE l0, float w0, HASH_OUTPUT_VALUE l1, float w1, HASH_OUTPUT_VALUE l2, float w2, HASH_OUTPUT_VALUE l3, float w3)
{
  HASH_OUTPUT_VALUE v = (l0*w0+l1*w1+l2*w2+l3*w3)/(w0+w1+w2+w3);
  return v;
}

// Get the number of rays that did not hit a surface
uint getContrib(HashRecordContrib c)
{
  return c.contrib16Weight16 & 0xFFFF;
}

// Indicates whether the contribution is empty
bool isZero(HashRecordContrib c)
{
  return getWeight(c) == 0;
}

// Get the final AO value for the contribution
HASH_OUTPUT_VALUE getOutputValue(HashRecordContrib c)
{
  return getContrib(c) / float(getWeight(c));
}

// Set the total number of rays for the contribution c 
void setWeight(inout HashRecordContrib c, uint weight)
{
  c.contrib16Weight16 = (c.contrib16Weight16 & 0xFFFF) + (weight << 16);
}

// Get the number of rays that did not hit a surface and the total number of rays
uvec2 getcontrib16Weight16(HashRecordContrib c)
{
  return uvec2(c.contrib16Weight16 & 0xFFFF, c.contrib16Weight16 >> 16);
}

// Reset the counters of the contribution to 0
void resetContrib(inout HashRecordContrib contrib)
{
  contrib.contrib16Weight16 = 0u;
}

// Add samples to the total ray count of the cell, and return the previous ray count

#if HASH_SLOT_COUNT > 1
  uint addSamples(uint index, uint samples, uint slot)
  {
    return atomicAdd(HASH_CELL(index, slot).contrib16Weight16, samples << 16) >> 16;
  }
#else
  uint addSamples(uint index, uint samples)
  {
    return atomicAdd(HASH_CELL(index).contrib16Weight16, samples << 16) >> 16;
  }
#endif

// Add both counters to the hash map
#if HASH_SLOT_COUNT > 1
  void addContribution(uint index, HashRecordContrib c, uint slot)
  {
    atomicAdd(HASH_CELL(index, slot).contrib16Weight16, c.contrib16Weight16);
  }
#else
  void addContribution(uint index, HashRecordContrib c)
  {
    atomicAdd(HASH_CELL(index).contrib16Weight16, c.contrib16Weight16);
  }
#endif

// Return an empty contribution
HashRecordContrib zeroContrib()
{
  HashRecordContrib contrib;
  contrib.contrib16Weight16 = 0u;
  return contrib;
}


// Get the number of pixels requiring new rays to be traced. This will be used to
// compute the ray budget
uint getPixelsToUpdate(HashRecordContrib afterLastContrib)
{
  return afterLastContrib.contrib16Weight16;
}

void incrementPixelsToUpdate()
{
#if HASH_SLOT_COUNT > 1
  atomicAdd(HASH_CELL(cb_PostEffect_HRTAO.hashTableSize, 0).contrib16Weight16, 1);
#else
  atomicAdd(HASH_CELL(cb_PostEffect_HRTAO.hashTableSize).contrib16Weight16, 1);
#endif
}

uint getPixelsToUpdate()
{
#if HASH_SLOT_COUNT > 1
  return HASH_CELL(cb_PostEffect_HRTAO.hashTableSize, 0).contrib16Weight16;
#else
  return HASH_CELL(cb_PostEffect_HRTAO.hashTableSize).contrib16Weight16;
#endif
}
