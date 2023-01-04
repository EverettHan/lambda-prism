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

#ifdef EXPOSE_HASH_TEX
HashRecordContrib fetchFromTexture(ivec2 pixel)
{
  HashRecordContrib contribution;
  contribution.contrib16Weight16 = texelFetch(changeList, pixel, 0).x;
  return contribution;
}

HashRecordContrib fetchFromLinkedTexture(ivec2 pixel)
{
  HashRecordContrib contribution;
  contribution.contrib16Weight16 = texelFetch(linkedChangeList, pixel, 0).x;
  return contribution;
}
#endif

// Set the payload of the change list item

#define SET_CL_ITEM(cl, index, item)                                                                                   \
  {                                                                                                                    \
    cl[(CL_ENTRY_SIZE-1) * index + 0]                     = item.x;                                                    \
    cl[(CL_ENTRY_SIZE-1) * index + 1]                     = item.y;                                                    \
    cl[(CL_ENTRY_SIZE-1) * resX * resY * resZ + index]    = item.z;                                                    \
  }

// Set the index of the previous change list item for the same cell id
#define SET_CL_PREVIOUS_ITEM(cl, index, prevId)                                                                        \
  {                                                                                                                    \
    cl[(CL_ENTRY_SIZE-1) * index + 1] = prevId;                                                                        \
  }

// Get the index of the pixel related to the change list item
#define GET_CL_PIXEL_ID(cl, index) cl[(CL_ENTRY_SIZE-1) * resY * resX * resZ + index]

// Get the contribution and sample count of the change list item
#define GET_CL_CONTRIB_PREV(cl, index, contrib, prev)                                                                  \
  contrib.contrib16Weight16 = cl[(CL_ENTRY_SIZE-1) * index];                                                           \
  prev                      = cl[(CL_ENTRY_SIZE-1) * index + 1];

// Get the number of elements in the change list
#define GET_CL_SIZE(cl) cl[CL_ENTRY_SIZE * resX * resY * resZ]


// Set the number of elements in the change list
#define SET_CL_SIZE(cl, size) cl[CL_ENTRY_SIZE * resX * resY * resZ] = size

// Reserve a slot in the change list
#define RESERVE_CL_ITEM atomicAdd(changeList[CL_ENTRY_SIZE * resX * resY * resZ], 1)

// Create a change list item from a contribution, the index of the previous change list item for the same pixel, and the corresponding pixel id
HASH_CHANGE_LIST_ITEM makeChangeListItem(HashRecordContrib c, uint previous, uint pixelId)
{
  return uvec3(c.contrib16Weight16, previous, pixelId);
}

// Create an empty change list item
HASH_CHANGE_LIST_ITEM makeEmptyChangeListItem()
{
  return uvec3(0, ~0u, ~0u);
}

// Erase the sample count from the contribution
void eraseWeight(inout HashRecordContrib c)
{
  c.contrib16Weight16 &= 0xFFFF;
}

// Get a null contribution
HASH_OUTPUT_VALUE zeroOutputValue()
{
  return HASH_OUTPUT_VALUE(0.f);
}

// Add two contributions
HashRecordContrib addContribWeight(HashRecordContrib c1, HashRecordContrib c2)
{
  HashRecordContrib r;
  r.contrib16Weight16 = c1.contrib16Weight16 + c2.contrib16Weight16;
  return r;
}

// Add a contribution to the hash entry at cellId. In the first pass we add contributions from the raytracing pass, which
// has already added the sample count. In this case we indicate isContribWeightBakedIn=true to avoid adding the weight twice
void addContribWeightToHashEntry(uint cellId, HashRecordContrib c, bool isContribWeightBakedIn)
{
  if(isContribWeightBakedIn)
    eraseWeight(c);

  hashMap[cellId] = addContribWeight(hashMap[cellId], c);
}

// Make a contribution from a number of non-hitting rays c and a total number of rays w
HashRecordContrib makeContrib(uint c, uint w)
{
  HashRecordContrib r;
  r.contrib16Weight16 = (c & 0xFFFF) + (w << 16);
  return r;
}

// Get the number of rays that did not hit a surface
uint getContrib(HashRecordContrib c)
{
  return c.contrib16Weight16 & 0xFFFF;
}

// Get the total number of rays traced
uint getWeight(HashRecordContrib c)
{
  return c.contrib16Weight16 >> 16;
}

// Indicates whether the contribution is empty
bool isZero(HashRecordContrib c)
{
  return getWeight(c) == 0;
}

bool allowedToAddWeights(HashRecordContrib a, HashRecordContrib b)
{
  return getWeight(a) + getWeight(b) < 0xFFFF;
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
uint addSamples(uint index, uint samples)
{
  return atomicAdd(hashMap[index].contrib16Weight16, samples << 16) >> 16;
}

// Add both counters to the hash map
void addContribution(uint index, HashRecordContrib c)
{
  atomicAdd(hashMap[index].contrib16Weight16, c.contrib16Weight16);
}

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
  atomicAdd(hashMap[cb_PostEffect_HRTAO.hashTableSize].contrib16Weight16, 1);
}
uint getPixelsToUpdate()
{
  return hashMap[cb_PostEffect_HRTAO.hashTableSize].contrib16Weight16;
}

#ifdef EXPOSE_LINKED_HASH
void addLinkedContribution(uint index, HashRecordContrib c)
{
  atomicAdd(linkedHashMap[index].contrib16Weight16, c.contrib16Weight16);
}
#endif
