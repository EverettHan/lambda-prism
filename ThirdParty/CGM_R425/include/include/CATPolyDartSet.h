// COPYRIGHT DASSAULT SYSTEMES 2022, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyDartSet
//
//=============================================================================
// 2022-02-07   NDO: New
//=============================================================================
#pragma once

#include "CATSetOfPtr.h"
#include "CATCompareElements.h"
#include "CATPolyCell.h"
#include "CATIPolyPoint.h"


// Reserved (private).
// Comparator of the tags of the K-cells associated to darts.
template<class DART, size_t K>
class CATCompareDarts : public CATCompareElements
{
public:

  /**
   * Compares the tags of the K-cell associated to darts.
   */
  inline int Compare (DART* da, DART* db) const;

  inline unsigned int Hash (DART* d) const;

  // Comparison function for std::sort.
  bool operator () (DART* da, DART* db) const { return Compare (da, db) < 0; }

private:

  int Compare (const void* da, const void* db) const
  {
    return Compare ((DART*) da, (DART*) db);
  }

  unsigned int Hash (const void* d) const
  {
    return Hash ((DART*) d);
  }
};

template<class DART, size_t K>
inline int CATCompareDarts<DART, K>::Compare (DART* da, DART* db) const
{
  const CATPolyCell* ca = da ? da->template GetCell<K> () : 0;
  const CATPolyCell* cb = db ? db->template GetCell<K> () : 0;
  unsigned int ta = ca ? ca->GetCellTag () : 0;
  unsigned int tb = cb ? cb->GetCellTag () : 0;
  return ta < tb ? -1 : ta > tb ? +1 : 0;
}

template<class DART, size_t K>
inline unsigned int CATCompareDarts<DART, K>::Hash (DART* d) const
{
  const CATPolyCell* C = d ? d->template GetCell<K> () : 0;
  return C ? C->GetCellTag () : 0;
}


template<class DART>
class CATCompareDartsPoints : public CATCompareElements
{
public:

  /**
   * Compares the points associated to darts.
   */
  inline int Compare (DART* da, DART* db) const
  {
    const CATIPolyPoint* pa = da ? da->GetPoint () : 0;
    const CATIPolyPoint* pb = db ? db->GetPoint () : 0;
    return pa < pb ? -1 : pa > pb ? +1 : 0;  // Comparaison depends on pointer values.
  }

  inline unsigned int Hash (DART* d) const
  {
    const CATIPolyPoint* P = d ? d->GetPoint () : 0;
    return CATPtrToUINT32 (P);  // Conversion to unsigned int.
  }

  // Comparison function for std::sort.
  bool operator () (DART* da, DART* db) const { return Compare (da, db) < 0; }

private:

  int Compare (const void* da, const void* db) const
  {
    return Compare ((DART*)da, (DART*)db);
  }

  unsigned int Hash (const void* d) const
  {
    return Hash ((DART*)d);
  }
};


template<class DART>
class CATCompareDartsCurves : public CATCompareElements
{
public:

  /**
   * Compares the curves associated to darts.
   */
  inline int Compare (DART* da, DART* db) const
  {
    const CATIPolyCurve* ca = da ? da->GetCurve () : 0;
    const CATIPolyCurve* cb = db ? db->GetCurve () : 0;
    return ca < cb ? -1 : ca > cb ? +1 : 0;  // Comparaison depends on pointer values.
  }

  inline unsigned int Hash (DART* d) const
  {
    const CATIPolyCurve* C = d ? d->GetCurve () : 0;
    return CATPtrToUINT32 (C);  // Conversion to unsigned int.
  }

  // Comparison function for std::sort.
  bool operator () (DART* da, DART* db) const { return Compare (da, db) < 0; }

private:

  int Compare (const void* da, const void* db) const
  {
    return Compare ((DART*)da, (DART*)db);
  }

  unsigned int Hash (const void* d) const
  {
    return Hash ((DART*)d);
  }
};


// Reserved (private).
// Set of darts.
template<class DART>
class CATPolyDartSet
{

public:

  inline CATPolyDartSet (const int iDimension = 0, const CATCompareElements* iCompare = 0);
  ~CATPolyDartSet () {}

  /**
   * A handle to a dart in the set.
   * A handle provides direct access to the dart.
   * A NULL handle is an invalid handle.  Handles are NOT stable after insertion or removal of elements.
   */
  typedef CATSetOfPtr::Handle Handle;

  /**
   * Inserts a dart in the set.
   * @return
   *   * S_OK on insertion;
   *   * S_FALSE if the dart is already inserted.
   */
  HRESULT Insert (DART* d, Handle* oHandle = 0) { return _Set.Insert ((void*) d, oHandle); }

  /**
   * Removes a dart from the set.
   *   * S_OK on removal;
   *   * S_FALSE if the dart is already removed.
   */
  inline HRESULT Remove (DART* d) { return _Set.Remove ((void*)d); }

  /**
   * Finds the handle to a dart in the set.  Returns the null handle, if no dart is found.
   */
  inline Handle Find (DART* d) const { return _Set.Find ((void*)d); }

  // Returns the dart given a handle.
  inline DART* Get (Handle iHandle) const { return _Set.Get (iHandle); }

public:

  /**
   * Returns the number of darts in the set.
   */
  unsigned int Size () const { return _Set.Size (); }

  HRESULT RemoveAll () { return _Set.RemoveAll (); }

public:

  /**
   * Iterator cycling through all the darts in the set.
   */
  class Iterator
  {
  public:

    Iterator () {}
    Iterator (const CATPolyDartSet& set) : _It (set._Set) {}
    Iterator (const Iterator& iRHS) : _It (iRHS._It) {}
    ~Iterator () {}

    Iterator& Begin () { _It.Begin (); return *this; }
    bool End () const { return _It.End (); }
    Iterator& operator++ () { ++_It; return *this; }
    Iterator& operator+= (unsigned int iCount) { _It += iCount; return *this; }

    Iterator& operator = (const Iterator& iRHS) { _It = iRHS._It; return *this; }

    Handle GetHandle () const { return  _It.GetHandle (); };
    DART* Dart () const { return (DART*) *_It; }
    DART* operator* () const { return (DART*) *_It; }

  private:

    CATSetOfPtr::Iterator _It;

  };

  friend class Iterator;

private:

  CATSetOfPtr _Set;

};

template<class DART>
inline CATPolyDartSet<DART>::CATPolyDartSet (const int iDimension, const CATCompareElements* iCompare) :
  _Set (iDimension, iCompare)
{
}
