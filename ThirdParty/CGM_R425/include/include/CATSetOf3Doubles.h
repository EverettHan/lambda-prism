// COPYRIGHT DASSAULT SYSTEMES 2012, ALL RIGHTS RESERVED.
//===================================================================
//
// CATSetOf3Doubles.h
//
//===================================================================
// February 2012  Creation: NDO
//===================================================================
#ifndef CATSetOf3Doubles_h
#define CATSetOf3Doubles_h

#include "PolyMathContainers.h"
#include "CATErrorDef.h"
#include "CATCompareDoublePoints.h"
#include "CATHTable_D.h"


/**
Implementation of a set of double triplets.
The set is implemented as a hash table.
*/
class ExportedByPolyMathContainers CATSetOf3Doubles
{

public:

  /** 
   * Handle to an element in the set.  Handles are stable when inserting or removing elements.
   */
  typedef const double* Handle;

public:

  /**
   * By default the comparison function is a lexicographic sort with strict equality between doubles.
   */
  CATSetOf3Doubles (const int iDimension = 0, const CATCompareDoublePoints* iCompareDoubles = 0);
  ~CATSetOf3Doubles () {}

public:

  /**
   * Inserts three consecutive doubles, d[], in the set.  
   * The pointer referencing the three doubles must remain valid during the use of this object.
   * The optional argument is a handle that will point to the element after its insertion.
   * The methods returns S_OK if the element is inserted and S_FALSE if the element is already in the set.
   * If the element is in the set, then the handle is set to the position of the element.
   * It returns E_FAIL for any error.
   */
  inline HRESULT Insert (const double* d, Handle* oHandle = 0);

  /**
   * Finds a set of three doubles in the set.
   */
  inline Handle Find (const double* d) const;

  /**
   * Removes the three doubles from the set.
   */
  inline HRESULT Remove (const double* d);

  /**
   * Returns the doubles given a handle.  Returns NULL if the handle is invalid.
   */
  inline const double* Get (Handle iHandle) const;

public:

  /**
   * Returns the number of elements in the set.
   */
  inline int Size () const;

  /**
   * Removes all elements from the set.
   */
  inline HRESULT RemoveAll ();

public:

  /**
   * Iterator through all the elements in the set.
   */
  class Iterator
  {
  public:
    inline Iterator (const CATSetOf3Doubles& set) : _It (set._SetOfDoubles) {}

    inline const double* operator* () {return (const double*) *_It;}
    inline Handle GetHandle () const {return (Handle) *_It;}

    inline Iterator& Begin (const CATSetOf3Doubles& set) {_It = CATHTable_D::Iterator (set._SetOfDoubles); return *this;}
    inline CATBoolean End () const {return _It.End ();}
    inline Iterator& operator++ () {++_It; return *this;}

  private:
    CATHTable_D::Iterator _It;
  };
  friend class Iterator;

public:

  /** 
   * Returns the handle to the first element of the set.
   */
  inline Handle First () const;

private:

  CATHTable_D _SetOfDoubles;

};


inline HRESULT CATSetOf3Doubles::Insert (const double* d, Handle* oHandle)
{
  CATHTable_D::Handle handle = 0;
  HRESULT hr = _SetOfDoubles.Insert ((void*) d, handle);
  if (oHandle && handle)
    *oHandle = (const double*) _SetOfDoubles.GetData (handle);
  return hr;
}


inline CATSetOf3Doubles::Handle CATSetOf3Doubles::Find (const double* d) const
{
  return (const double*) _SetOfDoubles.GetData (_SetOfDoubles.Find ((void*) d));
}


inline HRESULT CATSetOf3Doubles::Remove (const double* d)
{
  return d ? _SetOfDoubles.Remove ((void*) d) : S_FALSE;  // Return S_FALSE if element is not found.
}


inline const double* CATSetOf3Doubles::Get (Handle iHandle) const
{
  return iHandle;
}


inline int CATSetOf3Doubles::Size () const
{
  return _SetOfDoubles.Size ();
}


inline HRESULT CATSetOf3Doubles::RemoveAll ()
{
  return _SetOfDoubles.RemoveAll ();
}


inline CATSetOf3Doubles::Handle CATSetOf3Doubles::First () const
{
  CATHTable_D::Iterator it (_SetOfDoubles);
  return !it.End () ? (Handle) *it : 0;
}

#endif
