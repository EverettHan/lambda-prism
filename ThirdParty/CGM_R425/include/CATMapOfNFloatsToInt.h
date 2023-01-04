//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2006, ALL RIGHTS RESERVED.
//===================================================================
//
// CATMapOfNFloatsToInt.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// January 2006 Creation: ndo
// Feb 2009 zfi (see CATMapOfNFloatsToInt)
//===================================================================

#ifndef CATMapOfNFloatsToInt_H
#define CATMapOfNFloatsToInt_H

#include "PolyMathContainers.h"

#include "CATBoolean.h"
#include "CATHashTable.h"

class ExportedByPolyMathContainers CATMapOfNFloatsToInt
{

public :

  CATMapOfNFloatsToInt (const int iDimension, const int iEstimatedSize);
  ~CATMapOfNFloatsToInt (void);

  CATBoolean Insert (const float iCoords[],const int iValue);

  CATBoolean Locate (const float iCoords[], int& oValue) const;

  CATBoolean Remove (const float iCoords[], int& oValue);

  CATBoolean Remove (const float iCoords[]);

  CATBoolean RemoveAll (void);

  CATBoolean Update (const float iCoords[], const int iValue);

  /**
  * Returns the number of elements inserted in the map.
  */
  int Size (void) const;

  /**
  * Returns the maximum number of elements that can be inserted in the map without any collision.
  */
  int MaxSize(void) const;


private :

  void Clear (void);

  CATHashTable _HashTable;
  int _Dimension;

};

#endif // !CATMapOfNFloatsToInt_H
