// COPYRIGHT DASSAULT SYSTEMES 2004, ALL RIGHTS RESERVED.
//===================================================================
//
// CATBucketsOfInt.h
//
//===================================================================
//
// oct 2004 Creation: dhp
//===================================================================
#ifndef CATBucketsOfInt_h
#define CATBucketsOfInt_h

#include "PolyMathContainers.h"
#include "CATPolyBuckets_T.h"
#include "CATBoolean.h"


/**
* A class implementing a resizable vector of integers.
*/
class ExportedByPolyMathContainers CATBucketsOfInt
{

public:

  CATBucketsOfInt (void) {}
  ~CATBucketsOfInt (void) {}

public:

  /**
   * Given an index greater or equal to 1, sets the integer value.
   * The vector will resize itself if the index is greater than the size.
   */
  CATBoolean Set (const int index, const int value);

  /**
   * Given an index greater or equal to 1, gets the integer value.
   * The index must be in the interval [1, Size ()].
   */
  CATBoolean Get (const int index, int & value) const;

public:

  /**
   * Returns the integer given a <bf>valid</bf> index.
   * The index must be in the interval [1, Size ()].
   */
  inline int operator [] (const int index) const;

  /**
   * Returns a reference to the integer given a <bf>valid</bf> index.
   * The index must be in the interval [1, Size ()].
   */
  inline int& operator [] (const int index);

public:

  inline int Size (void) const {return _Integers.Size ();}
  inline int GetMaxIndex (void) const {return _Integers.Size ();}

  inline void Clear (CATBoolean iKeepAlloc = 0) {_Integers.Clear (iKeepAlloc);}

private :

  class Specialize_CATPolyBuckets_T (CATBucketsIntegers, int);

private :

  CATBucketsIntegers _Integers;

};

inline int CATBucketsOfInt::operator [] (const int index) const
{
  return _Integers[index];
}

inline int& CATBucketsOfInt::operator [] (const int index)
{
  return _Integers[index];
}

#endif
