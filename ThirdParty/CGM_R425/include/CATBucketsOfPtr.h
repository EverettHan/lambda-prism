// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATBucketsOfPtr.h
//
//===================================================================
//
// September 2008 Creation: NDO
//===================================================================
#ifndef CATBucketsOfPtr_h
#define CATBucketsOfPtr_h

#include "PolyMathContainers.h"
#include "CATPolyBuckets_T.h"
#include "CATBoolean.h"


/**
* A class implementing a resizable vector of pointers.
*/
class ExportedByPolyMathContainers CATBucketsOfPtr
{

public:

  CATBucketsOfPtr () {}
  ~CATBucketsOfPtr () {}

public:

  /**
   * Given an index greater or equal to 1, sets the pointer value.
   * The vector will resize itself if the index is greater than the size.
   */
  CATBoolean Set (const int index, void* value);

  /**
   * Given an index greater or equal to 1, gets the pointer value.
   * The index must be in the interval [1, Size ()].
   */
  CATBoolean Get (const int index, void*& value) const;

public:

  /**
   * Returns the pointer given a <bf>valid</bf> index.
   * The index must be in the interval [1, Size ()].
   */
  inline void* operator [] (const int index) const;

  /**
   * Returns a reference to the pointer given a <bf>valid</bf> index.
   * The index must be in the interval [1, Size ()].
   */
  inline void*& operator [] (const int index);

public:

  inline int Size (void) const {return _Pointers.Size ();}
  inline int GetMaxIndex () const {return _Pointers.Size ();}

  inline void Clear () {_Pointers.Clear ();}

private :

  class Specialize_CATPolyBuckets_T (CATBucketsPointers, void*);

private :

  CATBucketsPointers _Pointers;

};

inline void* CATBucketsOfPtr::operator [] (const int index) const
{
  return _Pointers[index];
}

inline void*& CATBucketsOfPtr::operator [] (const int index)
{
  return _Pointers[index];
}

#endif
