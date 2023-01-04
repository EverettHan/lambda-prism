//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2006, ALL RIGHTS RESERVED.
//===================================================================
//
// CATMapOfFloatsToPtr.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// January 2006 Creation: ndo
//===================================================================

#ifndef CATMapOfFloatsToPtr_H
#define CATMapOfFloatsToPtr_H

#include "PolyMathContainers.h"
#include "CATSetOfFloatPoints.h"
#include "CATMapOfPtrToPtr.h"

#include "CATBoolean.h"


class ExportedByPolyMathContainers CATMapOfFloatsToPtr
{

public:

  /*
   * By default the comparison function is a lexicographic sort with strict equality between floats.
   * However, the comparaison function is customizable by derivation from CATCompareFloatPoints.
   */
  inline CATMapOfFloatsToPtr (const CATCompareFloatPoints* iCompareFunction = 0);

  CATMapOfFloatsToPtr (const int iDimension) {}  // Deprecated.
  ~CATMapOfFloatsToPtr () {}

public:

  /*
   * Insert a triplet of floats into the map.
   * When a new point is inserted, the method returns S_OK.
   * If the point is found in the map and the values match, then the method returns S_FALSE.
   * If the point cannot be inserted into the map, because it is already associated to a different value
   * or another error, the method returns E_FAIL.
   */
  HRESULT Insert (const float x, const float y, const float z,
                  const void* iValue);

  HRESULT Remove (const float x, const float y, const float z,
                  const void*& oValue);

  HRESULT Remove (const float x, const float y, const float z);

  /*
   * Update the value associated to the point in the map.
   * Returns
   *   S_OK of the value is updated successfully.
   *   S_FALSE if the point is not found in the map.
   *   E_FAIL if an error occurs.
   */
  HRESULT Update (const float x, const float y, const float z,
                  const void* iValue);

  CATBoolean Locate (const float x, const float y, const float z,
                     const void*& oValue) const;

public:

  // Iterator to cycle through all the elements in the map.
  class ExportedByPolyMathContainers Iterator
  {
  public:
    Iterator (const CATMapOfFloatsToPtr& map) : _SetOfPoints (map._SetOfPoints), _It (map._MapHandleToValue) {}
    ~Iterator () {}

    void GetFloats (float& x, float& y, float& z) const {_SetOfPoints.Get ((CATSetOfFloatPoints::Handle) _It.GetKey (), x, y, z);}
    void* GetData () const {return _It.GetData ();}

    Iterator& Begin () {_It.Begin (); return *this;}
    CATBoolean End () const {return _It.End ();}
    Iterator& operator++ () {++_It; return *this;}

  private:
    const CATSetOfFloatPoints& _SetOfPoints;
    CATMapOfPtrToPtr::Iterator _It;
  };

  friend class Iterator;

public:

  /**
   * Returns the number of elements inserted in the map.
   */
  inline int Size () const;

  inline HRESULT RemoveAll ();

public:

  /**
   * Returns the set of points stored in the map.
   */
  inline const CATSetOfFloatPoints& GetSetOfPoints () const;

  /**
   * Given a handle for a point, returns the value associated to this point.
   * The handle is returned by the iterator through the set of points.
   */
  inline CATBoolean Fetch (CATSetOfFloatPoints::Handle h, const void*& oValue) const;

private:

  CATSetOfFloatPoints _SetOfPoints;
  CATMapOfPtrToPtr _MapHandleToValue;

};


inline CATMapOfFloatsToPtr::CATMapOfFloatsToPtr (const CATCompareFloatPoints* iCompareFunction) :
  _SetOfPoints (0, iCompareFunction)
{
}

inline int CATMapOfFloatsToPtr::Size () const
{
  return _SetOfPoints.Size ();
}

inline HRESULT CATMapOfFloatsToPtr::RemoveAll ()
{
  _SetOfPoints.RemoveAll ();
  return _MapHandleToValue.RemoveAll ();
}

inline const CATSetOfFloatPoints& CATMapOfFloatsToPtr::GetSetOfPoints () const
{
  return _SetOfPoints;
}

inline CATBoolean CATMapOfFloatsToPtr::Fetch (CATSetOfFloatPoints::Handle h, const void*& oValue) const
{
  return _MapHandleToValue.Locate (h, (void*&) oValue);
}

#endif // !CATMapOfFloatsToPtr_H
