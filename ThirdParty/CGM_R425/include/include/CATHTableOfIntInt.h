// COPYRIGHT DASSAULT SYSTEMES 2004, ALL RIGHTS RESERVED.
//===================================================================
//
// CATHTableOfIntInt.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// jun 2004 Creation: dhp
//===================================================================
#ifndef CATHTableOfIntInt_h
#define CATHTableOfIntInt_h

#include "PolyMathContainers.h"
#include "CATBoolean.h"

#include "CATHashTable.h"

#include "CATListOfInt.h"

class ExportedByPolyMathContainers CATHTableOfIntInt
{

public :

  enum ElementComparison
  {
    eSymmetric = 0,  // (index0, index1) == (index1, index0).
    eNotSymmetric    // (index0, index1) != (index1, index0).
  };

  //
  // By default construct a hash table with symmetric comparison.
  //
  CATHTableOfIntInt (const int size);  

  // 
  // Specify whether to construct a symmetric hash table or not (see ElementComparison enum.) 
  //
  CATHTableOfIntInt (const int size, const int comparison);

  ~CATHTableOfIntInt (void);

  CATBoolean Insert (const int index0, const int index1);

  CATBoolean Locate (const int index0, const int index1) const;

  CATBoolean Remove (const int index0, const int index1);

  CATBoolean RemoveAll (void);

  CATBoolean GetIndices (CATListOfInt & indices0, CATListOfInt & indices1) const;

  /**
  * Returns the number of elements inserted in the table.
  */
  int Size (void) const;

  CATBoolean First (int & index0, int & index1) const;

private :

  void Clear (void);

  friend class CATHTableOfIntIntIterator;

  CATHashTable _hashTable;

};


class ExportedByPolyMathContainers CATHTableOfIntIntIterator
{

public:

  CATHTableOfIntIntIterator (const CATHTableOfIntInt& iHashTableIntInt);

  ~CATHTableOfIntIntIterator ();

  // Resets the iterator to the beginning.
  void Beginning ();

  // Gets the indices from the hash table from the current position of the iterator.
  // Returns TRUE if the iterator points to valid indices and FALSE otherwise.
  CATBoolean GetCurrent (int& index0, int& index1) const;

  // Increments the iterator and gets the indices from the hash table.
  // Returns TRUE if valid indices from the hash table are set and FALSE if the iterator reaches the end.
  // (See Beginning () to reset the iterator.)
  CATBoolean GetNext (int& index0, int& index1);

private :

  const CATHashTable* _HashTable;

  int _Bucket;
  int _Position;

};


#endif
