/*
 * Copyright (c) 2018, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

// Data types used in fp16 RGB mode

 struct HashRecordContrib
 {
   uint r;
   uint g;
   uint b;
   uint w;

   #ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
     uint glossyr;
     uint glossyg;
     uint glossyb;
     uint glossyw;
   #endif
 };

#if HASH_SLOT_COUNT <= 1
  #define HashRecordContribSlots HashRecordContrib
#else
  struct HashRecordContribSlots
  {
    HashRecordContrib slots[HASH_SLOT_COUNT];
  };
#endif

//  /!\  struct HashRecordContribSlots { uint dummy; };

struct ChangeListItem
{
  HashRecordContrib c;

  uint previous;
  uint pixelId; 
  
#if HASH_SLOT_COUNT > 1
  uint slot;
#endif
};

//#define HASH_INTERNAL_VALUE f16vec3
#ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
  struct HashOutputValue
  {
    vec3 irradiance;
    vec3 specular;
  };
  #define HASH_OUTPUT_VALUE HashOutputValue
#else
  #define HASH_OUTPUT_VALUE vec3
#endif

#define HASH_OUTPUT_COMPONENT_TYPE float

#define HASH_CHANGE_LIST_BASE_TYPE uint
#define HASH_CHANGE_LIST_ITEM ChangeListItem

// Don't remove this comment!
// This is a by-pass to allow the shader builder to find this custom type...(it won't detect preprocessor macro)
//
// struct HASH_CHANGE_LIST_BASE_TYPE
// {
//   uint dummy;
// };
//
// End of by-pass

#define HASH_SAMPLER_TYPE sampler2d

// Number of 32-bit words comprising an entry
#ifdef SO_HRTAO_ENABLE_SPECULAR_SHADOWS
  #if HASH_SLOT_COUNT > 1
    #define CL_ENTRY_SIZE 11
  #else
    #define CL_ENTRY_SIZE 10
  #endif
#else
  #if HASH_SLOT_COUNT > 1
    #define CL_ENTRY_SIZE 7
  #else
    #define CL_ENTRY_SIZE 6
  #endif
#endif

