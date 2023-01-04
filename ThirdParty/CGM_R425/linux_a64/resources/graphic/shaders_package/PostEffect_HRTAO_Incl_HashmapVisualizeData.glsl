/*
 * Copyright (c) 2018, NVIDIA CORPORATION.  All rights reserved.
 *
 * NVIDIA CORPORATION and its licensors retain all intellectual property
 * and proprietary rights in and to this software, related documentation
 * and any modifications thereto.  Any use, reproduction, disclosure or
 * distribution of this software and related documentation without an express
 * license agreement from NVIDIA CORPORATION is strictly prohibited.
 */

#ifdef __cplusplus
#define uint uint32_t
#endif
struct HashMapVisualizeData
{
    // Hash map fill rate histogram: first entry is the number of hash map chunks filled between 0 and 10%, 
    // second for 10-20% etc
    uint histogram[10];
    // Number of allocated cells
    uint allocations;
    // Number of allocations that required collision management
    uint collisions;
    // Number of failed allocations
    uint fails;
    // Total number of 'hops' done to resolve all collisions
    uint hopsToSucceed;
    // Maximum number of 'hops' done to resolve a single collision 
    uint maxHopsToSucceed;
};
