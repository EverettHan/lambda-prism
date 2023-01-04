// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATMapOfPtrToInt.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
// April 2008 Creation: NDO
//===================================================================
#ifndef CATMapOfPtrToInt_h
#define CATMapOfPtrToInt_h

#include "PolyMathContainers.h"
#include "CATHTableOfPtrToInt.h"


/**
This class is a hash table mapping a key to a value.
Insertion, removal and lookup are of average complexity O(1). (Worst case could be O(N).)  
This implementation does support automatic resizing.  The dimension of the hash table is set 
at construction but the table will resize itself if it is too small.
*/
class ExportedByPolyMathContainers CATMapOfPtrToInt : public CATHTableOfPtrToInt
{

public:

  CATMapOfPtrToInt () : CATHTableOfPtrToInt (0) {}
  CATMapOfPtrToInt (const int iDimension) : CATHTableOfPtrToInt (iDimension) {}

};

#endif

