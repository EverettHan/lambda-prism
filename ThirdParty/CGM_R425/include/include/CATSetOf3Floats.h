// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATSetOf3Floats.h
//
//===================================================================
// February 2009  Creation: NDO
//===================================================================
#ifndef CATSetOf3Floats_h
#define CATSetOf3Floats_h

#include "PolyMathContainers.h"
#include "CATCompareFloatPoints.h"
#include "CATErrorDef.h"
#include "CATHTable_D.h"

//class CATCGMOutput;


/**
Implementation of a set of float triplets.
The set is implemented as a hash table.
*/
class ExportedByPolyMathContainers CATSetOf3Floats
{

public:

  /** 
   * Handle to an element in the set.  Handles are stable when inserting or removing elements.
   */
  typedef const float* Handle;

public:

  /**
   * By default the comparison function is a lexicographic sort with strict equality between floats.
   */
  CATSetOf3Floats (const int iDimension = 0, const CATCompareFloatPoints* iCompareFloats = 0);
  ~CATSetOf3Floats () {}

public:

  /**
   * Inserts three consecutive floats, d[], in the set.  
   * The pointer referencing the three floats must remain valid during the use of this object.
   * The optional argument is a handle that will point to the element after its insertion.
   * The methods returns S_OK if the element is inserted and S_FALSE if the element is already in the set.
   * If the element is in the set, then the handle is set to the position of the element.
   * It returns E_FAIL for any error.
   */
  inline HRESULT Insert (const float* d, Handle* oHandle = 0);

  /**
   * Finds a set of three floats in the set.
   */
  inline Handle Find (const float* d) const;

  /**
   * Removes the three floats from the set.
   */
  inline HRESULT Remove (const float* d);

  /**
   * Returns the floats given a handle.  Returns NULL if the handle is invalid.
   */
  inline const float* Get (Handle iHandle) const;

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
    inline Iterator (const CATSetOf3Floats& set) : _It (set._SetOfFloats) {}

    inline const float* operator* () {return (const float*) *_It;}
    inline Handle GetHandle () const {return (Handle) *_It;}

    inline Iterator& Begin (const CATSetOf3Floats& set) {_It = CATHTable_D::Iterator (set._SetOfFloats); return *this;}
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

  // For debugging purposes.
  //void Print (CATCGMOutput& stream) const;

private:

  CATHTable_D _SetOfFloats;

};


inline HRESULT CATSetOf3Floats::Insert (const float* d, Handle* oHandle)
{
  CATHTable_D::Handle handle = 0;
  HRESULT hr = _SetOfFloats.Insert ((void*) d, handle);
  if (oHandle && handle)
    *oHandle = (const float*) _SetOfFloats.GetData (handle);
  return hr;
}


inline CATSetOf3Floats::Handle CATSetOf3Floats::Find (const float* d) const
{
  return (const float*) _SetOfFloats.GetData (_SetOfFloats.Find ((void*) d));
}


inline HRESULT CATSetOf3Floats::Remove (const float* d)
{
  return d ? _SetOfFloats.Remove ((void*) d) : S_FALSE;  // Return S_FALSE if element is not found.
}


inline const float* CATSetOf3Floats::Get (Handle iHandle) const
{
  return iHandle;
}


inline int CATSetOf3Floats::Size () const
{
  return _SetOfFloats.Size ();
}


inline HRESULT CATSetOf3Floats::RemoveAll ()
{
  return _SetOfFloats.RemoveAll ();
}


inline CATSetOf3Floats::Handle CATSetOf3Floats::First () const
{
  CATHTable_D::Iterator it (_SetOfFloats);
  return !it.End () ? (Handle) *it : 0;
}

#endif
