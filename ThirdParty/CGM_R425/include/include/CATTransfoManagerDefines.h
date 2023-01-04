/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CATTransfoManagerDefines : some defines for the CATTransfoManager
//
//=============================================================================
// Usage notes:
//=============================================================================
// Nov. 1998     Creation                                       I. Levy
//=============================================================================
#ifndef CATTransfoManagerDefines_h
#define CATTransfoManagerDefines_h

#define CATTransfoManagerUnknown                           0
#define CATTransfoManagerDuplicate                         1
#define CATTransfoManagerReplace                           2
#define CATTransfoManagerDuplicateInNewFactory             3
#define CATTransfoManagerReplaceInNewFactory               4
#define CATTransfoManagerNonLinear                         5
#define CATTransfoManagerNonLinearInNewFactory             6
#define CATTransfoManagerAffinityReplace                   7
#define CATTransfoManagerFullDuplicate                     8
#define CATTransfoManagerFullDuplicateInNewFactory         9

enum CATResetType 
{
  CATTransfoManager_ResetStd         =  0  // Clean Out (default)
 ,CATTransfoManager_ResetOutInEntry  =  1  // Clean Out given InEntry
 ,CATTransfoManager_ResetInvariance  =  2  // Clean Invariance data
 ,CATTransfoManager_ResetCount       =  4  // Clean Count data
 ,CATTransfoManager_ResetBox         =  8  // Clean Box data
};

#endif
