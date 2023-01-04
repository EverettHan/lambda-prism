//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2006, ALL RIGHTS RESERVED.
//===================================================================
//
// CATSetOfFloatPoints.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// January 2006 Creation: ndo
//===================================================================
#ifndef CATSetOfFloatPoints_H
#define CATSetOfFloatPoints_H

#include "PolyMathContainers.h"
#include "CATErrorDef.h"
#include "CATHTable_D.h"

class CATCompareFloatPoints;


/*
Container of unique float points. 
*/
class ExportedByPolyMathContainers CATSetOfFloatPoints
{

public:

  /*
   * Construction of a set of floats.  The first argument is the estimated size of the set (optional.)
   * The comparaison function between two floats can be customized (CATCompareFloatPoints.)
   * By default the comparison function is a lexicographic sort with strict equality between floats.
   */
  CATSetOfFloatPoints (const int iEstimatedSize = 0, 
                       const CATCompareFloatPoints* iCompareFunction = 0);

  ~CATSetOfFloatPoints ();

public:

  // A handle to a float point.  The handle is unique to each float and is stable upon insertion and deletion.
  typedef float* Handle;

public:

  /*
   * Insert a float point into the set.
   * The methods returns S_OK if the element is inserted and S_FALSE if the element is already in the set.
   * If the element is in the set, then the optional handle is set to the position of the element.
   * It returns E_FAIL for any error.
   */
  HRESULT Insert (const float x, const float y, const float z, Handle* opHandle = 0);

  /*
   * Finds a point into a set and return its handle.
   * A handle equals to 0 means that the point is not in the set.
   */
  Handle Find (const float x, const float y, const float z) const;

  /*
   * Remove a point from the set given its coordinates or a handle to its coordinates.
   */
  HRESULT Remove (const float x, const float y, const float z);
  HRESULT Remove (Handle iHandle);

  HRESULT RemoveAll ();

  /*
   * Given a handle, returns the coordinate of the point in the set.
   */ 
  inline HRESULT Get (const Handle iHandle, float& x, float& y, float& z) const;

public:

  // Iterator to cycle through all the points in the set.
  class Iterator
  {
  public:
    inline Iterator (const CATSetOfFloatPoints& set) : _It (set._FloatHandles) {}

    inline Handle operator* () const {return (Handle) *_It;}

    inline Iterator& Begin (const CATSetOfFloatPoints& set) {_It = set._FloatHandles; return *this;}
    inline CATBoolean End () const {return _It.End ();}
    inline Iterator& operator++ () {++_It; return *this;}

  private:
    CATHTable_D::Iterator _It;
  };

  friend class Iterator;

public:

  /**
   * Returns the number of points in the set.
   */
  inline int Size () const;

private:

  void* _PoolOfFloats;
  //const CATCompareFloatPoints* _CompareFloats;

  CATHTable_D _FloatHandles;

};


inline int CATSetOfFloatPoints::Size () const
{
  return _FloatHandles.Size ();
}

inline HRESULT CATSetOfFloatPoints::Get (const CATSetOfFloatPoints::Handle iHandle, float& x, float& y, float& z) const
{
  x = iHandle[0];
  y = iHandle[1];
  z = iHandle[2];
  return S_OK;
}

#endif // !CATSetOfFloatPoints_H
