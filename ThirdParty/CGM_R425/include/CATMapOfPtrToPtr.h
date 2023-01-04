// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATMapOfPtrToPtr.h
//
//===================================================================
// August 2008 Creation: NDO
//===================================================================
#ifndef CATMapOfPtrToPtr_h
#define CATMapOfPtrToPtr_h

#include "PolyMathContainers.h"
#include "CATHTableOfPtrToPtr.h"

#define CATMAPOFPTRTOPTR_USE_HTABLE 1


class ExportedByPolyMathContainers CATMapOfPtrToPtr : public CATHTableOfPtrToPtr
{

public:

  CATMapOfPtrToPtr (const int iDimension = 0, const CATCompareElements* iCompareKeys = 0) : CATHTableOfPtrToPtr (iDimension, iCompareKeys) {}

};

#endif
