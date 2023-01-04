/*
 * Copyright (c) 2018, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

// Macros and functions to access change lists and hash map data for the fp16 RGB storage mode

#define FLOAT16_MAX (65504.0f)

// Set the members of a change list item: RGB color, index of the previous change list item for the same hash cell, and pixel ID
#ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
  #if HASH_SLOT_COUNT > 1
    #define SET_CL_ITEM(cl, index, item)                                                                                   \
    {                                                                                                                      \
      cl[(CL_ENTRY_SIZE-1) * index + 0]                  = item.c.r;                                                       \
      cl[(CL_ENTRY_SIZE-1) * index + 1]                  = item.c.g;                                                       \
      cl[(CL_ENTRY_SIZE-1) * index + 2]                  = item.c.b;                                                       \
      cl[(CL_ENTRY_SIZE-1) * index + 3]                  = item.c.w;                                                       \
      cl[(CL_ENTRY_SIZE-1) * index + 4]                  = item.c.glossyr;                                                 \
      cl[(CL_ENTRY_SIZE-1) * index + 5]                  = item.c.glossyg;                                                 \
      cl[(CL_ENTRY_SIZE-1) * index + 6]                  = item.c.glossyb;                                                 \
      cl[(CL_ENTRY_SIZE-1) * index + 7]                  = item.c.glossyw;                                                 \
      cl[(CL_ENTRY_SIZE-1) * index + 8]                  = item.slot;                                                      \
      cl[(CL_ENTRY_SIZE-1) * index + 9]                  = item.previous;                                                  \
      cl[(CL_ENTRY_SIZE-1) * resX * resY * resZ * HASH_SLOT_COUNT + index] = item.pixelId;                                 \
    }                                                                                                                      
  #else                                                                                                                  
    #define SET_CL_ITEM(cl, index, item)                                                                                   \
    {                                                                                                                      \
      cl[(CL_ENTRY_SIZE-1) * index + 0]                  = item.c.r;                                                       \
      cl[(CL_ENTRY_SIZE-1) * index + 1]                  = item.c.g;                                                       \
      cl[(CL_ENTRY_SIZE-1) * index + 2]                  = item.c.b;                                                       \
      cl[(CL_ENTRY_SIZE-1) * index + 3]                  = item.c.w;                                                       \
      cl[(CL_ENTRY_SIZE-1) * index + 4]                  = item.c.glossyr;                                                 \
      cl[(CL_ENTRY_SIZE-1) * index + 5]                  = item.c.glossyg;                                                 \
      cl[(CL_ENTRY_SIZE-1) * index + 6]                  = item.c.glossyb;                                                 \
      cl[(CL_ENTRY_SIZE-1) * index + 7]                  = item.c.glossyw;                                                 \
      cl[(CL_ENTRY_SIZE-1) * index + 8]                  = item.previous;                                                  \
      cl[(CL_ENTRY_SIZE-1) * resX * resY * resZ + index] = item.pixelId;                                                   \
    } 
  #endif
#else
  #if HASH_SLOT_COUNT > 1
    #define SET_CL_ITEM(cl, index, item)                                                                                   \
    {                                                                                                                      \
      cl[(CL_ENTRY_SIZE-1) * index + 0]                  = item.c.r;                                                       \
      cl[(CL_ENTRY_SIZE-1) * index + 1]                  = item.c.g;                                                       \
      cl[(CL_ENTRY_SIZE-1) * index + 2]                  = item.c.b;                                                       \
      cl[(CL_ENTRY_SIZE-1) * index + 3]                  = item.c.w;                                                       \
      cl[(CL_ENTRY_SIZE-1) * index + 4]                  = item.slot;                                                      \
      cl[(CL_ENTRY_SIZE-1) * index + 5]                  = item.previous;                                                  \
      cl[(CL_ENTRY_SIZE-1) * resX * resY * resZ * HASH_SLOT_COUNT + index] = item.pixelId;                                 \
    }                                                                                                                      
  #else                                                                                                                  
    #define SET_CL_ITEM(cl, index, item)                                                                                   \
    {                                                                                                                      \
      cl[(CL_ENTRY_SIZE-1) * index + 0]                  = item.c.r;                                                       \
      cl[(CL_ENTRY_SIZE-1) * index + 1]                  = item.c.g;                                                       \
      cl[(CL_ENTRY_SIZE-1) * index + 2]                  = item.c.b;                                                       \
      cl[(CL_ENTRY_SIZE-1) * index + 3]                  = item.c.w;                                                       \
      cl[(CL_ENTRY_SIZE-1) * index + 4]                  = item.previous;                                                  \
      cl[(CL_ENTRY_SIZE-1) * resX * resY * resZ + index] = item.pixelId;                                                   \
    } 
  #endif
#endif

// Set the index of the previous change list item for the same hash cell
#ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
  #if HASH_SLOT_COUNT > 1
    #define SET_CL_PREVIOUS_ITEM(cl, index, prevId) cl[(CL_ENTRY_SIZE-1) * index + 9] = prevId;
  #else
    #define SET_CL_PREVIOUS_ITEM(cl, index, prevId) cl[(CL_ENTRY_SIZE-1) * index + 8] = prevId; 
  #endif
#else
  #if HASH_SLOT_COUNT > 1
    #define SET_CL_PREVIOUS_ITEM(cl, index, prevId) cl[(CL_ENTRY_SIZE-1) * index + 5] = prevId;
  #else
    #define SET_CL_PREVIOUS_ITEM(cl, index, prevId) cl[(CL_ENTRY_SIZE-1) * index + 4] = prevId; 
  #endif
#endif

// Set the pixel ID for the change list item
#define GET_CL_PIXEL_ID(cl, index) cl[(CL_ENTRY_SIZE-1) * resY * resX * resZ * HASH_SLOT_COUNT + index]

#ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
  #if HASH_SLOT_COUNT > 1
    #define GET_CL_CONTRIB_PREV(cl, index, contrib, prev, slot)                                                            \
    {                                                                                                                      \
      contrib.r       = cl[(CL_ENTRY_SIZE-1) * index + 0];                                                                 \
      contrib.g       = cl[(CL_ENTRY_SIZE-1) * index + 1];                                                                 \
      contrib.b       = cl[(CL_ENTRY_SIZE-1) * index + 2];                                                                 \
      contrib.w       = cl[(CL_ENTRY_SIZE-1) * index + 3];                                                                 \
      contrib.glossyr = cl[(CL_ENTRY_SIZE-1) * index + 4];                                                                 \
      contrib.glossyg = cl[(CL_ENTRY_SIZE-1) * index + 5];                                                                 \
      contrib.glossyb = cl[(CL_ENTRY_SIZE-1) * index + 6];                                                                 \
      contrib.glossyw = cl[(CL_ENTRY_SIZE-1) * index + 7];                                                                 \
      slot            = cl[(CL_ENTRY_SIZE-1) * index + 8];                                                                 \
      prev            = cl[(CL_ENTRY_SIZE-1) * index + 9];                                                                 \
    }
  #else
    #define GET_CL_CONTRIB_PREV(cl, index, contrib, prev)                                                                  \
    {                                                                                                                      \
      contrib.r       = cl[(CL_ENTRY_SIZE-1) * index + 0];                                                                 \
      contrib.g       = cl[(CL_ENTRY_SIZE-1) * index + 1];                                                                 \
      contrib.b       = cl[(CL_ENTRY_SIZE-1) * index + 2];                                                                 \
      contrib.w       = cl[(CL_ENTRY_SIZE-1) * index + 3];                                                                 \
      contrib.glossyr = cl[(CL_ENTRY_SIZE-1) * index + 4];                                                                 \
      contrib.glossyg = cl[(CL_ENTRY_SIZE-1) * index + 5];                                                                 \
      contrib.glossyb = cl[(CL_ENTRY_SIZE-1) * index + 6];                                                                 \
      contrib.glossyw = cl[(CL_ENTRY_SIZE-1) * index + 7];                                                                 \
      prev            = cl[(CL_ENTRY_SIZE-1) * index + 8];                                                                 \
    }
  #endif
#else
  #if HASH_SLOT_COUNT > 1
    #define GET_CL_CONTRIB_PREV(cl, index, contrib, prev, slot)                                                            \
    {                                                                                                                      \
      contrib.r = cl[(CL_ENTRY_SIZE-1) * index + 0];                                                                       \
      contrib.g = cl[(CL_ENTRY_SIZE-1) * index + 1];                                                                       \
      contrib.b = cl[(CL_ENTRY_SIZE-1) * index + 2];                                                                       \
      contrib.w = cl[(CL_ENTRY_SIZE-1) * index + 3];                                                                       \
      slot      = cl[(CL_ENTRY_SIZE-1) * index + 4];                                                                       \
      prev      = cl[(CL_ENTRY_SIZE-1) * index + 5];                                                                       \
    }
  #else
    #define GET_CL_CONTRIB_PREV(cl, index, contrib, prev)                                                                  \
    {                                                                                                                      \
      contrib.r = cl[(CL_ENTRY_SIZE-1) * index + 0];                                                                       \
      contrib.g = cl[(CL_ENTRY_SIZE-1) * index + 1];                                                                       \
      contrib.b = cl[(CL_ENTRY_SIZE-1) * index + 2];                                                                       \
      contrib.w = cl[(CL_ENTRY_SIZE-1) * index + 3];                                                                       \
      prev      = cl[(CL_ENTRY_SIZE-1) * index + 4];                                                                       \
    }
  #endif
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
  uint quantifiedRoughness = uint(floor(roughness * 127.f));
  return pixelId << 7 | quantifiedRoughness;
}

float unpackRoughness(uint pixelIdRoughness)
{
  return float(pixelIdRoughness & 0x7f) / 127.f;
}

uint unpackPixelId(uint pixelIdRoughness)
{
  return pixelIdRoughness >> 7;
}

// Create a change list item 
#if HASH_SLOT_COUNT > 1
HASH_CHANGE_LIST_ITEM makeChangeListItem(HashRecordContrib c, uint slot, uint previous, uint pixelId, float roughness)
#else
HASH_CHANGE_LIST_ITEM makeChangeListItem(HashRecordContrib c, uint previous, uint pixelId, float roughness)
#endif
{
  ChangeListItem item;
  item.c = c;

  #if HASH_SLOT_COUNT > 1
    item.slot = slot;
  #endif

  item.previous = previous;
  item.pixelId = packPixelIdRoughness(pixelId, roughness);
  return item;
}

#if HASH_SLOT_COUNT > 1
HASH_CHANGE_LIST_ITEM makeChangeListItem(HashRecordContrib c, uint slot, uint previous, uint pixelIdRoughness)
#else
HASH_CHANGE_LIST_ITEM makeChangeListItem(HashRecordContrib c, uint previous, uint pixelIdRoughness)
#endif
{
  ChangeListItem item;
  item.c        = c;

  #if HASH_SLOT_COUNT > 1
    item.slot = slot;
  #endif

  item.previous = previous;
  item.pixelId  = pixelIdRoughness;
  return item;
}

// Create an empty item
#if HASH_SLOT_COUNT > 1
HASH_CHANGE_LIST_ITEM makeEmptyChangeListItem(uint slot)
#else
HASH_CHANGE_LIST_ITEM makeEmptyChangeListItem()
#endif
{
  ChangeListItem item;
  item.c.r = 0;
  item.c.g = 0;
  item.c.b = 0;
  item.c.w = 0;

  #ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
    item.c.glossyr = 0;
    item.c.glossyg = 0;
    item.c.glossyb = 0;
    item.c.glossyw = 0;
  #endif

  #if HASH_SLOT_COUNT > 1
    item.slot = slot;
  #endif

  item.previous = ~0u;
  item.pixelId = ~0u;

  return item;
}

// Remove the sample count from the contribution
void eraseWeight(inout HashRecordContrib c)
{
  c.w = 0;
}

// Return a null RGB output value
HASH_OUTPUT_VALUE zeroOutputValue()
{
  HASH_OUTPUT_VALUE r;
  #ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
    r.irradiance = vec3(0.f, 0.f, 0.f);
    r.specular   = vec3(0.f, 0.f, 0.f);
  #else
    r = HASH_OUTPUT_VALUE(0.0);
  #endif
  return r;
}

uvec2 combine16BitPairs(uvec2 p1, uvec2 p2)
{
  //return p2;
  //f16vec3 rgb1, rgb2;
  vec3 rgb1, rgb2;
  rgb1.rg = unpackFloat2x16(p1.x);
  rgb1.b  = uint16BitsToHalf(uint16_t(p1.y & 0xFFFF));
  rgb2.rg = unpackFloat2x16(p2.x);
  rgb2.b  = uint16BitsToHalf(uint16_t(p2.y & 0xFFFF));

  uvec2 r;
  r.x             = packFloat2x16(f16vec2(min(vec2(FLOAT16_MAX), rgb1.rg + rgb2.rg)));
  uint16_t weight = uint16_t((p1.y >> 16) + (p2.y >> 16));
  //float16_t b      = rgb1.b + rgb2.b;
  float b = min(FLOAT16_MAX, rgb1.b + rgb2.b);
  r.y     = uint(halfBitsToUint16(float16_t(b))) | (uint(weight) << 16);

  return r;
}

uvec4 combine32BitPairs(uvec4 p1, uvec4 p2)
{
  vec3 rgb1;
  rgb1.r = uintBitsToFloat(p1.x);
  rgb1.g = uintBitsToFloat(p1.y);
  rgb1.b = uintBitsToFloat(p1.z);

  vec3 rgb2;
  rgb2.r = uintBitsToFloat(p2.x);
  rgb2.g = uintBitsToFloat(p2.y);
  rgb2.b = uintBitsToFloat(p2.z);

  uvec4 r;
  r.x = floatBitsToUint(rgb1.r + rgb2.r);
  r.y = floatBitsToUint(rgb1.g + rgb2.g);
  r.z = floatBitsToUint(rgb1.b + rgb2.b);
  r.w = p1.w + p2.w;

  return r;
}

uvec2 normalize16BitPair(uvec2 p)
{
  uint16_t weight = uint16_t(p.y >> 16);
  if(weight <= 1)
    return p;
  vec3 rgb;
  rgb.rg = unpackFloat2x16(p.x);
  rgb.b  = uint16BitsToHalf(uint16_t(p.y & 0xFFFF));

  rgb /= float(weight);
  // Storage is in 16-bit, clamping the result to avoid overflow
  rgb = min(rgb, vec3(FLOAT16_MAX));
  uvec2 r;
  r.x = packFloat2x16(f16vec2(rgb.rg));

  float b = rgb.b;
  r.y     = uint(halfBitsToUint16(float16_t(b))) | (uint(1) << 16);
  return r;
}

uvec4 normalize32BitPair(uvec4 p)
{
  uint weight = p.w;

  if(weight <= 1)
    return p;

  vec3 rgb;
  rgb.r = uintBitsToFloat(p.r);
  rgb.g = uintBitsToFloat(p.g);
  rgb.b = uintBitsToFloat(p.b);

  rgb /= float(weight);

  uvec4 r;
  r.x = floatBitsToUint(rgb.r);
  r.y = floatBitsToUint(rgb.g);
  r.z = floatBitsToUint(rgb.b);
  r.w = 1;

  return r;
}

uvec2 average16BitPairs(uvec2 p1, uvec2 p2, float p1W)
{

  if(p1.y >> 16 == 0)
    return normalize16BitPair(p2);
  if(p2.y >> 16 == 0)
    return normalize16BitPair(p1);

  //f16vec3 rgb1, rgb2;
  vec3 rgb1, rgb2;
  rgb1.rg = unpackFloat2x16(p1.x);
  rgb1.b  = uint16BitsToHalf(uint16_t(p1.y & 0xFFFF));
  rgb2.rg = unpackFloat2x16(p2.x);
  rgb2.b  = uint16BitsToHalf(uint16_t(p2.y & 0xFFFF));

  //uint16_t weight = uint16_t((p1.y >> 16) + (p2.y >> 16));

  rgb1 *= (p1W);
  rgb2 *= ((1.f - p1W) / float(p2.y >> 16));

  vec3 result = rgb1 + rgb2;
  // Storage is in 16-bit, clamping the result to avoid overflow
  result = min(result, vec3(FLOAT16_MAX));

  uvec2 r;
  r.x = packFloat2x16(f16vec2(result.rg));

  //float b = rgb1.b + rgb2.b;
  r.y = uint(halfBitsToUint16(float16_t(result.b))) + (uint(1) << 16);

  return r;
}

uvec4 average32BitPairs(uvec4 p1, uvec4 p2, float p1W)
{
  if(p1.w == 0)
    return normalize32BitPair(p2);
  if(p2.w == 0)
    return normalize32BitPair(p1);

  vec3 rgb1;
  rgb1.r = uintBitsToFloat(p1.r);
  rgb1.g = uintBitsToFloat(p1.g);
  rgb1.b = uintBitsToFloat(p1.b);
  
  vec3 rgb2;
  rgb2.r = uintBitsToFloat(p2.r);
  rgb2.g = uintBitsToFloat(p2.g);
  rgb2.b = uintBitsToFloat(p2.b);

  rgb1 *= (p1W);
  rgb2 *= ((1.f - p1W) / float(p2.w));

  vec3 result = rgb1 + rgb2;

  uvec4 r;
  r.x = floatBitsToUint(result.x);
  r.y = floatBitsToUint(result.y);
  r.z = floatBitsToUint(result.z);
  r.w = 1;

  return r;
}

HashRecordContrib addContribWeight(HashRecordContrib c1, HashRecordContrib c2)
{
  #ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
    uvec4 diffuse = combine32BitPairs(uvec4(c1.r, c1.g, c1.b, c1.w), uvec4(c2.r, c2.g, c2.b, c2.w));
    uvec4 glossy = combine32BitPairs(uvec4(c1.glossyr, c1.glossyg, c1.glossyb, c1.glossyw), uvec4(c2.glossyr, c2.glossyg, c2.glossyb, c2.glossyw));
    
    HashRecordContrib r;
    r.r = diffuse.x;
    r.g = diffuse.y;
    r.b = diffuse.z;
    r.w = diffuse.w;
    
    r.glossyr = glossy.x;
    r.glossyg = glossy.y;
    r.glossyb = glossy.z;
    r.glossyw = glossy.w;
  #else
    HashRecordContrib r;
    
    HASH_OUTPUT_VALUE rgb1, rgb2;
    rgb1.r = uintBitsToFloat(c1.r);
    rgb1.g = uintBitsToFloat(c1.g);
    rgb1.b = uintBitsToFloat(c1.b);
    
    rgb2.r = uintBitsToFloat(c2.r);
    rgb2.g = uintBitsToFloat(c2.g);
    rgb2.b = uintBitsToFloat(c2.b);
    
    r.r = floatBitsToUint(rgb1.r + rgb2.r);
    r.g = floatBitsToUint(rgb1.g + rgb2.g);
    r.b = floatBitsToUint(rgb1.b + rgb2.b);
    
    r.w = c1.w + c2.w;
  #endif

  return r;
}

#ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS

  // Add a contribution to the hash contents
  #if HASH_SLOT_COUNT > 1
  void addContribWeightToHashEntry(in uint cellId, HashRecordContrib c, in bool isContribWeightBakedIn, in uint pixelIdRoughness, in uint slot)
  #else
  void addContribWeightToHashEntry(in uint cellId, HashRecordContrib c, in bool isContribWeightBakedIn, in uint pixelIdRoughness)
  #endif
  {
    vec3 hashValue;
    #if HASH_SLOT_COUNT > 1
      hashValue.r = uintBitsToFloat(HASH_CELL(cellId, slot).r);
      hashValue.g = uintBitsToFloat(HASH_CELL(cellId, slot).g);
      hashValue.b = uintBitsToFloat(HASH_CELL(cellId, slot).b);
      uint hashWeight = HASH_CELL(cellId, slot).w;
    #else
      hashValue.r = uintBitsToFloat(HASH_CELL(cellId).r);
      hashValue.g = uintBitsToFloat(HASH_CELL(cellId).g);
      hashValue.b = uintBitsToFloat(HASH_CELL(cellId).b);
      uint hashWeight = HASH_CELL(cellId).w;
    #endif

    vec3 cValue;
    cValue.r = uintBitsToFloat(c.r);
    cValue.g = uintBitsToFloat(c.g);
    cValue.b = uintBitsToFloat(c.b);
    uint cWeight = c.w;

    bool wasEmpty = (hashWeight == 0);

    if((uint(hashWeight) + uint(cWeight)) < 1<<20)
    {
      hashValue = (hashValue * hashWeight + cValue) / (hashWeight + cWeight);
      hashWeight += cWeight;
      
      #if HASH_SLOT_COUNT > 1
        HASH_CELL(cellId, slot).r = floatBitsToUint(hashValue.r);
        HASH_CELL(cellId, slot).g = floatBitsToUint(hashValue.g);
        HASH_CELL(cellId, slot).b = floatBitsToUint(hashValue.b);
        HASH_CELL(cellId, slot).w = hashWeight;
      #else
        HASH_CELL(cellId).r = floatBitsToUint(hashValue.r);
        HASH_CELL(cellId).g = floatBitsToUint(hashValue.g);
        HASH_CELL(cellId).b = floatBitsToUint(hashValue.b);
        HASH_CELL(cellId).w = hashWeight;
      #endif
    }
    else
    {
      hashWeight += cWeight;
    }

    float roughness           = unpackRoughness(pixelIdRoughness);
    float localDynAccumFactor = clamp(pow(roughness, cb_PostEffect_HRTAO.dynamicAccumExponent), 0.f, cb_PostEffect_HRTAO.staticAccumFactor);
    //const float dynamicAccumFactor = 0.9f;
    //const float staticAccumFactor  = 0.99f;
    float accumFactor = cb_PostEffect_HRTAO.staticAccumFactor - (cb_PostEffect_HRTAO.staticAccumFactor - localDynAccumFactor /*dynamicAccumFactor*/) * (cb_PostEffect_HRTAO_Auto.motionFactor);

    //float accumFactor = motionFactor == 0.f ? 0.97f : 0.3f;
    //float accumFactor = 0.8f+smoothstep(0.1f, 0.99f, 1.f-motionFactor)*0.15;

    if(wasEmpty)
      accumFactor = 0.f;
    uvec4 glossy = average32BitPairs(
      #if HASH_SLOT_COUNT > 1
        uvec4(HASH_CELL(cellId, slot).glossyr, HASH_CELL(cellId, slot).glossyg, HASH_CELL(cellId, slot).glossyb, HASH_CELL(cellId, slot).glossyw),
      #else
        uvec4(HASH_CELL(cellId).glossyr, HASH_CELL(cellId).glossyg, HASH_CELL(cellId).glossyb, HASH_CELL(cellId).glossyw),
      #endif
      uvec4(c.glossyr, c.glossyg, c.glossyb, c.glossyw), 
      accumFactor);

      
    #if HASH_SLOT_COUNT > 1
      HASH_CELL(cellId, slot).glossyr = glossy.x;
      HASH_CELL(cellId, slot).glossyg = glossy.y;
      HASH_CELL(cellId, slot).glossyb = glossy.z;

      if(!isContribWeightBakedIn)
        HASH_CELL(cellId, slot).glossyw += c.glossyw;
      else
        HASH_CELL(cellId, slot).glossyw = HASH_CELL(cellId, slot).glossyw;
    #else
      HASH_CELL(cellId).glossyr = glossy.x;
      HASH_CELL(cellId).glossyg = glossy.y;
      HASH_CELL(cellId).glossyb = glossy.z;

      if(!isContribWeightBakedIn)
        HASH_CELL(cellId).glossyw += c.glossyw;
      else
        HASH_CELL(cellId).glossyw = HASH_CELL(cellId).glossyw;
    #endif
  }
#else
  // Add a contribution to the hash contents
  #if HASH_SLOT_COUNT > 1
  void addContribWeightToHashEntry(uint cellId, HashRecordContrib c, bool isContribWeightBakedIn, uint pixelIdRoughness, uint slot)
  #else
  void addContribWeightToHashEntry(uint cellId, HashRecordContrib c, bool isContribWeightBakedIn, uint pixelIdRoughness)
  #endif
  {
    vec3 hashValue;
  
    #if HASH_SLOT_COUNT > 1
      HashRecordContrib h = HASH_CELL(cellId, slot);
    #else
      HashRecordContrib h = HASH_CELL(cellId);
    #endif

    hashValue.r = uintBitsToFloat(h.r);
    hashValue.g = uintBitsToFloat(h.g);
    hashValue.b = uintBitsToFloat(h.b);
    uint hashWeight = h.w;

    vec3 cValue;
    cValue.r = uintBitsToFloat(c.r);
    cValue.g = uintBitsToFloat(c.g);
    cValue.b = uintBitsToFloat(c.b);
    uint cWeight = c.w;

    if (isContribWeightBakedIn)
      hashWeight -= cWeight;

    hashValue = (hashValue*hashWeight + cValue)/(hashWeight+cWeight);
    hashWeight += cWeight;
  
    h.r = floatBitsToUint(hashValue.r);
    h.g = floatBitsToUint(hashValue.g);
    h.b = floatBitsToUint(hashValue.b);
    h.w = hashWeight;

    #if HASH_SLOT_COUNT > 1
      HASH_CELL(cellId, slot) = h;
    #else
      HASH_CELL(cellId) = h;
    #endif
  }
#endif

#if 0

// Add a contribution to the hash contents
#if HASH_SLOT_COUNT > 1
void addContribWeightToHashEntry(uint cellId, HashRecordContrib c, bool isContribWeightBakedIn, uint pixelIdRoughness, uint slot)
#else
void addContribWeightToHashEntry(uint cellId, HashRecordContrib c, bool isContribWeightBakedIn, uint pixelIdRoughness)
#endif
{
  vec3 hashValue;
  
  #if HASH_SLOT_COUNT > 1
    HashRecordContrib h = HASH_CELL(cellId, slot);
  #else
    HashRecordContrib h = HASH_CELL(cellId);
  #endif

  hashValue.r = uintBitsToFloat(h.r);
  hashValue.g = uintBitsToFloat(h.g);
  hashValue.b = uintBitsToFloat(h.b);
  uint hashWeight = h.w;

  vec3 cValue;
  cValue.r = uintBitsToFloat(c.r);
  cValue.g = uintBitsToFloat(c.g);
  cValue.b = uintBitsToFloat(c.b);
  uint cWeight = c.w;
  
  bool wasEmpty = (hashWeight == 0);
  
  #ifndef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
    if (isContribWeightBakedIn)
      hashWeight -= cWeight;
  #endif

  hashValue = (hashValue*hashWeight + cValue)/(hashWeight+cWeight);
  hashWeight += cWeight;
  
  h.r = floatBitsToUint(hashValue.r);
  h.g = floatBitsToUint(hashValue.g);
  h.b = floatBitsToUint(hashValue.b);
  h.w = hashWeight;
  
  #ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
    //glossy contrib

    float roughness = unpackRoughness(pixelIdRoughness);
    float localDynAccumFactor = clamp(pow(roughness, cb_PostEffect_HRTAO.dynamicAccumExponent), 0.f, cb_PostEffect_HRTAO.staticAccumFactor);
    float accumFactor = cb_PostEffect_HRTAO.staticAccumFactor - (cb_PostEffect_HRTAO.staticAccumFactor - localDynAccumFactor) * (cb_PostEffect_HRTAO_Auto.motionFactor);

    if(wasEmpty)
      accumFactor = 0.f;

    uvec4 glossyHash = average32BitPairs(
      uvec4(h.glossyr, h.glossyg, h.glossyb, h.glossyw), 
      uvec4(c.glossyr, c.glossyg, c.glossyb, c.glossyw), 
      accumFactor
    );

    uint existingWeight = h.glossyw;

    if(!isContribWeightBakedIn)
      existingWeight += c.glossyw;
  
    h.glossyr = glossyHash.r;
    h.glossyg = glossyHash.g;
    h.glossyb = glossyHash.b;
    h.glossyw = existingWeight;
  #endif

  #if HASH_SLOT_COUNT > 1
    HASH_CELL(cellId, slot) = h;
  #else
    HASH_CELL(cellId) = h;
  #endif
}

#endif

// Make a contribution from an RGB value and a sample count
HashRecordContrib makeContrib(vec3 c, uint w, vec3 glossy, uint glossyW)
{
  HashRecordContrib r;
  
  r.r = floatBitsToUint(c.r);
  r.g = floatBitsToUint(c.g);
  r.b = floatBitsToUint(c.b);
  r.w = w;
  
#ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
  r.glossyr = floatBitsToUint(glossy.r);
  r.glossyg = floatBitsToUint(glossy.g);
  r.glossyb = floatBitsToUint(glossy.b);
  r.glossyw = glossyW;
#endif

  return r;
}

HASH_OUTPUT_VALUE mixLODs(HASH_OUTPUT_VALUE l0, float w0, HASH_OUTPUT_VALUE l1, float w1, HASH_OUTPUT_VALUE l2, float w2, HASH_OUTPUT_VALUE l3, float w3)
{
  HASH_OUTPUT_VALUE v;
  #ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS

    v.irradiance = vec3(
       (l0.irradiance * w0
      + l1.irradiance * w1
      + l2.irradiance * w2
      + l3.irradiance * w3)
      / (w0 + w1 + w2 + w3)
    );

    v.specular = vec3(
       (l0.specular * w0
      + l1.specular * w1
      + l2.specular * w2
      + l3.specular * w3)
      / (w0 + w1 + w2 + w3)
    );

  #else
    v = (l0*w0+l1*w1+l2*w2+l3*w3)/(w0+w1+w2+w3);
  #endif


  return v;
}

//ao = (cellAo[0]*weights[0]+cellAo[1]*weights[1]+cellAo[2]*weights[2]+cellAo[3]*weights[3])/w;

// Get the RGB contribution
HASH_OUTPUT_VALUE getContrib(HashRecordContrib c)
{
  vec3 result;
  result.r = uintBitsToFloat(c.r);
  result.g = uintBitsToFloat(c.g);
  result.b = uintBitsToFloat(c.b);

  #ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
    vec3 glossy;
    glossy.r = uintBitsToFloat(c.glossyr);
    glossy.g = uintBitsToFloat(c.glossyg);
    glossy.b = uintBitsToFloat(c.glossyb);

    HASH_OUTPUT_VALUE v;
    v.irradiance = result;
    v.specular = glossy;
    return v;
  #else
    return result;
  #endif
}

// Get the sample count
uint getWeight(HashRecordContrib c)
{
  return c.w;
}

// Return true if the contribution is null
bool isZero(HashRecordContrib c)
{
  return getWeight(c) == 0;

}

bool allowedToAddWeights(HashRecordContrib a, HashRecordContrib b)
{
  return true;
}

// Get the RGB value of the contribution
HASH_OUTPUT_VALUE getOutputValue(HashRecordContrib c)
{
  return getContrib(c);
}

// Set the sample count 
void setWeight(inout HashRecordContrib c, uint weight)
{
  c.w = weight;
}


// Reset the RGB and sample count
void resetContrib(inout HashRecordContrib contrib)
{
  contrib.r = 0;
  contrib.g = 0;
  contrib.b = 0;
  contrib.w = 0;

  #ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
    contrib.glossyr = 0;
    contrib.glossyg = 0;
    contrib.glossyb = 0;
    contrib.glossyw = 0;
  #endif
}

// Add samples to the sample count in the hash map, and return the old sample count in the map
#ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
  #if HASH_SLOT_COUNT > 1
    uint addSamples(uint index, uint samples, uint slot)
    {
      return atomicAdd(HASH_CELL(index, slot).glossyw, samples);     
    }
  #else
    uint addSamples(uint index, uint samples)
    {
      return atomicAdd(HASH_CELL(index).glossyw, samples);     
    }
  #endif
#else
  #if HASH_SLOT_COUNT > 1
    uint addSamples(uint index, uint samples, uint slot)
    {
      return atomicAdd(HASH_CELL(index, slot).w, samples);     
    }
  #else
    uint addSamples(uint index, uint samples)
    {
      return atomicAdd(HASH_CELL(index).w, samples);     
    }
  #endif
#endif

// Create an empty contribution
HashRecordContrib zeroContrib()
{
  HashRecordContrib contrib;
  contrib.r = 0u;
  contrib.g = 0u;
  contrib.b = 0u;
  contrib.w = 0u;
  
  #ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
    contrib.glossyr = 0u;
    contrib.glossyg = 0u;
    contrib.glossyb = 0u;
    contrib.glossyw = 0u;
  #endif

  return contrib;
}


// Get the number of pixels requiring new rays to be traced. This will be used to
// compute the ray budget
uint getPixelsToUpdate(HashRecordContrib afterLastContrib)
{
  return afterLastContrib.w;
}

void incrementPixelsToUpdate()
{
#if HASH_SLOT_COUNT > 1
  atomicAdd(HASH_CELL(cb_PostEffect_HRTAO.hashTableSize, 0).w, 1);
#else
  atomicAdd(HASH_CELL(cb_PostEffect_HRTAO.hashTableSize).w, 1);
#endif
}

uint getPixelsToUpdate()
{
#if HASH_SLOT_COUNT > 1
  return HASH_CELL(cb_PostEffect_HRTAO.hashTableSize, 0).w;
#else
  return HASH_CELL(cb_PostEffect_HRTAO.hashTableSize).w;
#endif
}
