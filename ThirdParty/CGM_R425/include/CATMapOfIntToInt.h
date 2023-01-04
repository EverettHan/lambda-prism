// COPYRIGHT DASSAULT SYSTEMES 2005, ALL RIGHTS RESERVED.
//===================================================================
//
// CATMapOfIntToInt.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
// February 2005 Creation: NDO
//===================================================================
#ifndef CATMapOfIntToInt_h
#define CATMapOfIntToInt_h

#include "PolyMathContainers.h"
#include "CATHTableOfIntToInt.h"


/**
This class is a hash table mapping a key to a value.
Insertion, removal and lookup are of average complexity O(1). (Worst case could be O(N).)  
This implementation does support automatic resizing.  The dimension of the hash table is set 
at construction but the table will resize itself if it is too small.
*/
class ExportedByPolyMathContainers CATMapOfIntToInt : public CATHTableOfIntToInt
{

public:

  CATMapOfIntToInt () : CATHTableOfIntToInt (0) {}
  CATMapOfIntToInt (const int iDimension) : CATHTableOfIntToInt (iDimension) {}

};

#endif
