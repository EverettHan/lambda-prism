// COPYRIGHT DASSAULT SYSTEMES 2015
//=============================================================================
//
// CATDynSolidBooleanOptionMC_Simplif: 
//  
//  
//
//
//=============================================================================
//
// Usage notes: 
//
//
//=============================================================================
//  
//=============================================================================

#ifndef CATDynSolidBooleanOptionMC_Simplif_h
#define CATDynSolidBooleanOptionMC_Simplif_h

#include "BOOPER.h"

struct ExportedByBOOPER CATDynSolidBooleanOptionMC_Simplif
{
  //Flag to disable the simplification of merged curves in CATDynSolidBoolean
  //0: Simplification enabled
  //1: No Simplification
  static short NoSimplif_MC;
};

#endif
