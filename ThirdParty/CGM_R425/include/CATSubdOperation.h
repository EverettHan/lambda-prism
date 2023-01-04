// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CATSubdOperation :
// type enumere 
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Oct. 98  Creation                               L. Laloy, I.Dupont, X.Dupont
//
// Aug. 19  Modif                                                         DLR6   
//          Add debug methods to dump the name of the current operation
//          Please update that method in the .cpp file
//          when you create a new type of operation
//=============================================================================
#ifndef CATSubdOperation_H
#define CATSubdOperation_H

#undef CATSubdOperation_Dump
//#define CATSubdOperation_Dump

#ifdef CATSubdOperation_Dump
class CATCGMOutput;
#include "CATUnicodeString.h"
#endif // CATSubdOperation_Dump

typedef enum
{
   CATSubdOperationUnset                  = -1,
   CATSubdOperationIntersection           = 0,
   CATSubdOperationUnion                  = 1,
   CATSubdOperationDifference             = 2,
   CATSubdOperationDelta                  = 3,
   CATSubdOperationPosage                 = 4,
   CATSubdOperationProjection             = 5,
   CATSubdOperationSmartProjection        = 6,
   CATSubdOperationSewing                 = 7,
   CATSubdOperationHealing                = 8,
   CATSubdOperationCheckAutoIntersection  = 9,
   CATSubdOperationIntersectWireShell     = 10,
   CATSubdOperationCompatible             = 11,
   CATSubdOperationManifolder             = 12,
   CATSubdOperationVolumeExpansion        = 13,
   CATSubdOperationRelimitByVolume        = 14,
   CATSubdOperationTrim                   = 15
} 
CATSubdOperation;

#ifdef CATSubdOperation_Dump
void              SubdOper_Dump           (CATSubdOperation iOper, CATCGMOutput & ioOutput);
CATUnicodeString  SubdOper_GetDumpString  (CATSubdOperation iOper);
#endif // CATSubdOperation_Dump

#endif
