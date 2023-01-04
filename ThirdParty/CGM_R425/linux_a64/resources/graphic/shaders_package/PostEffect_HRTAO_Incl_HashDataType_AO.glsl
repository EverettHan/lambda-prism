/*
 * Copyright (c) 2018, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

// Data types used in AO mode

struct HashRecordContrib
{
  uint contrib16Weight16;
};

//  /!\  Don't remove this part (even the comments!)
//  /!\  This is a by-pass to allow the shader builder to find this custom type...(otherwise it won't detect the macro)
#define HashRecordContribSlots HashRecordContrib
//  /!\  struct HashRecordContribSlots { uint dummy; };
//  /!\  End of by-pass

#define HASH_OUTPUT_VALUE float
#define HASH_OUTPUT_COMPONENT_TYPE float
#define HASH_CHANGE_LIST_ITEM uvec3

// /!\ Don't remove this part (even the comments)
// /!\ This is a by-pass to allow the shader builder to find this custom type...(it won't detect preprocessor macro)
#define HASH_CHANGE_LIST_BASE_TYPE uint
// struct HASH_CHANGE_LIST_BASE_TYPE { uint dummy; };
// End of by-pass


#define HASH_SAMPLER_TYPE usampler2d

// Number of 32-bit words comprising an entry
#define CL_ENTRY_SIZE 3
