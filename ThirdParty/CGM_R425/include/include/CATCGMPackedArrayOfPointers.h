/* -*-c++-*- */
#ifndef CATCGMPackedArrayOfPointers_h
#define CATCGMPackedArrayOfPointers_h

// COPYRIGHT DASSAULT SYSTEMES  2000

#include "CATMathematics.h"
#include "CATDataType.h"

/**
 * Packed array of pointer
 */
typedef struct  _CATCGMPackedArrayOfPointers
{
   CATLONG32           number;
   void          *array[1];
} 
CATCGMPackedArrayOfPointers;

/**
 * Allocating and Freeing a packed array of pointer
 * Allocation return a CATCGMPackedArrayOfPointers with number assigned to specfied size.
 */

ExportedByCATMathematics \
  CATCGMPackedArrayOfPointers *new_CATCGMPackedArrayOfPointers(const CATLONG32 maxNumberOfPointer);

ExportedByCATMathematics \
  void delete_CATCGMPackedArrayOfPointers(CATCGMPackedArrayOfPointers * &packed);

ExportedByCATMathematics \
  CATCGMPackedArrayOfPointers * duplicate_CATCGMPackedArrayOfPointers(CATCGMPackedArrayOfPointers * ipacked);

#endif

