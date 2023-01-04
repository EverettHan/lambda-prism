// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATBucketsOfDouble.h
//
//===================================================================
//
// May 2008 Creation: zfi
//===================================================================
#ifndef CATBucketsOfDouble_h
#define CATBucketsOfDouble_h

#include "PolyMathContainers.h"
#include "CATPolyBuckets_T.h"
#include "CATBoolean.h"


/**
* A class implementing a resizable vector of doubles.
*/
class ExportedByPolyMathContainers CATBucketsOfDouble
{

public:

  CATBucketsOfDouble (void) {}
  ~CATBucketsOfDouble (void) {}

public:

  /**
   * Given an index greater or equal to 1, sets the double value.
   * The vector will resize itself if the index is greater than the size.
   */
  CATBoolean Set (const int index, const double value);

  /**
   * Given an index greater or equal to 1, gets the double value.
   * The index must be in the interval [1, Size ()].
   */
  CATBoolean Get (const int index, double & value) const;

public:

  /**
   * Returns the double given a <bf>valid</bf> index.
   * The index must be in the interval [1, Size ()].
   */
  inline double operator [] (const int index) const;

  /**
   * Returns a reference to the double given a <bf>valid</bf> index.
   * The index must be in the interval [1, Size ()].
   */
  inline double& operator [] (const int index);

public:

  inline int Size (void) const {return _Doubles.Size ();}
  inline int GetMaxIndex (void) const {return _Doubles.Size ();}

  inline void Clear (CATBoolean iKeepAlloc = 0) {_Doubles.Clear (iKeepAlloc);}

private :

  class Specialize_CATPolyBuckets_T (CATBucketsDoubles, double);

private :

  CATBucketsDoubles _Doubles;

};

inline double CATBucketsOfDouble::operator [] (const int index) const
{
  return _Doubles[index];
}

inline double& CATBucketsOfDouble::operator [] (const int index)
{
  return _Doubles[index];
}

#endif
