// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATArrayOfIntegerSets.h
//
//===================================================================
// April 2008 Creation: ndo
//===================================================================
#ifndef CATArrayOfIntegerSets_H
#define CATArrayOfIntegerSets_H

#include "PolyMathContainers.h"
#include "CATIntegerSets.h"
//#include "CATPolyBuckets_T.h"
#include "CATErrorDef.h"

#include "CATDataType.h"  // For 64-bit platforms.  (Conversion between integers and pointers.)


/*
This is an array of sets of unsigned integers.  Unsigned integers can be inserted or removed from each set. 
The sets are independent from each others; an unsigned integer can be inserted in several sets.
A set index ranges from 0 to GetNbSets () exclusive in this implementation.
*/
class ExportedByPolyMathContainers CATArrayOfIntegerSets : protected CATIntegerSets
{

public:

  // Construct an array of integer sets with a size initially set to iNbSets.
  // Sets range from 0 to iNbSets - 1.
  CATArrayOfIntegerSets (const unsigned int iNbSets);

  ~CATArrayOfIntegerSets () { delete[] _Sets; _Sets = 0; }

public:

  // Add a new integer set.
  inline HRESULT AddSet ();

  inline unsigned int GetNbSets () const;

public:

  // Convert a set index to a handle.  Recall a NULL handle is an invalid handle.
  inline static HandleOfSet CastAsHandleOfSet (const unsigned int iSet) {return (HandleOfSet) CATINT32ToPtr (iSet + 1);}

public:

  // Add an (unsigned integer) element into a set. 
  inline HRESULT AddElement (const unsigned int iSet, const unsigned int iElement);

  // Add an (unsigned integer) element into a set. 
  // This method returns the index of the element in the set.
  inline HRESULT AddElement (const unsigned int iSet, const unsigned int iElement, unsigned int& oIndex);

  // Remove an (unsigned integer) element from a set.
  inline HRESULT RemoveElement (const unsigned int iSet, const unsigned int iElement);

  // Remove an element given its index in the set.
  HRESULT RemoveElementGivenItsIndex (const unsigned int iSet, const unsigned int iIndex);

  // Remove all elements from a set.
  inline HRESULT RemoveAllElements (const unsigned int iSet);

  // Return the number of (unsigned integer) elements into a set.
  inline unsigned int GetNbElements (const unsigned int iSet) const;

public:

  // Suggest to a set the number of elements that are going to be inserted.
  // This method does not need to be called as the set adapts their sizes to the number of elements inserted.
  // However, if it is called, it should be called prior to insertion of any element in the set.
  inline HRESULT Size (const unsigned int iSet, const unsigned int size);

public:

  // Iterator to cycle through all the elements from a set.
  class ExportedByPolyMathContainers Iterator : public ElementIterator
  {
  public:

    Iterator (const CATArrayOfIntegerSets& iIntegerSets, const unsigned int iSet) :
      ElementIterator ((const CATIntegerSets&) iIntegerSets, CastAsHandleOfSet (iSet)) {}

    Iterator (const Iterator& iIterator) : ElementIterator (iIterator) {}

  };

protected:

  // For CATIntegerSets.
  int* FindBuffer (HandleOfSet iHandle) const;

  // For CATIntegerSets.
  void UpdateBuffer (HandleOfSet iHandle, int* iBuffer); 

//private:

  //class Specialize_CATPolyBuckets_T (CATBucketsBuffers, int*);

private:

  // Set of unsigned integer sets (buckets).
  //CATBucketsBuffers _Sets;   // Buckets of integer sets. 
  int** _Sets;
  unsigned int _NbAllocated;
  unsigned int _NbSets;

private:

  // No implementation of copy constructor and operator =.
  CATArrayOfIntegerSets (const CATArrayOfIntegerSets& iOther) ;
  CATArrayOfIntegerSets& operator = (const CATArrayOfIntegerSets& iOther) ;

  void Reallocate (unsigned int sz);

};


inline HRESULT CATArrayOfIntegerSets::AddSet ()
{
  //return _Sets.PushBack (0) ? S_OK : E_OUTOFMEMORY;
  if (_NbSets == _NbAllocated)
  {
    unsigned int sz = _NbAllocated > 1 ? (unsigned int) (1.6 * (double) _NbAllocated) : 4;
    Reallocate (sz);
  }
  ++_NbSets;
  return S_OK;
}

inline unsigned int CATArrayOfIntegerSets::GetNbSets () const
{
  //return _Sets.Size ();
  return _NbSets;
}

inline HRESULT CATArrayOfIntegerSets::AddElement (const unsigned int iSet, const unsigned int iElement)
{
  return iSet < _NbSets ? CATIntegerSets::AddElement (CastAsHandleOfSet (iSet), iElement) : E_FAIL;
  //return iSet < _Sets.Size () ? CATIntegerSets::AddElement (CastAsHandleOfSet (iSet), iElement) : E_FAIL;
}

inline HRESULT CATArrayOfIntegerSets::AddElement (const unsigned int iSet, const unsigned int iElement, unsigned int& oIndex)
{
  return iSet < _NbSets ? CATIntegerSets::AddElement (CastAsHandleOfSet (iSet), iElement, oIndex) : E_FAIL;
  //return iSet < _Sets.Size () ? CATIntegerSets::AddElement (CastAsHandleOfSet (iSet), iElement, oIndex) : E_FAIL;
}

inline HRESULT CATArrayOfIntegerSets::RemoveElement (const unsigned int iSet, const unsigned int iElement)
{
  return iSet < _NbSets ? CATIntegerSets::RemoveElement (CastAsHandleOfSet (iSet), iElement) : E_FAIL;
  //return iSet < _Sets.Size () ? CATIntegerSets::RemoveElement (CastAsHandleOfSet (iSet), iElement) : E_FAIL;
}

inline HRESULT CATArrayOfIntegerSets::RemoveElementGivenItsIndex (const unsigned int iSet, const unsigned int iIndex)
{
  return iSet < _NbSets ? CATIntegerSets::RemoveElementGivenItsIndex (CastAsHandleOfSet (iSet), iIndex) : E_FAIL;
  //return iSet < _Sets.Size () ? CATIntegerSets::RemoveElementGivenItsIndex (CastAsHandleOfSet (iSet), iIndex) : E_FAIL;
}

inline HRESULT CATArrayOfIntegerSets::RemoveAllElements (const unsigned int iSet)
{
  return iSet < _NbSets ? CATIntegerSets::RemoveAllElements (CastAsHandleOfSet (iSet)) : E_FAIL;
  //return iSet < _Sets.Size () ? CATIntegerSets::RemoveAllElements (CastAsHandleOfSet (iSet)) : E_FAIL;
}

inline unsigned int CATArrayOfIntegerSets::GetNbElements (const unsigned int iSet) const
{
  return iSet < _NbSets ? CATIntegerSets::GetNbElements (CastAsHandleOfSet (iSet)) : 0;
  //return iSet < _Sets.Size () ? CATIntegerSets::GetNbElements (CastAsHandleOfSet (iSet)) : 0;
}

inline HRESULT CATArrayOfIntegerSets::Size (const unsigned int iSet, const unsigned int size)
{
  return iSet < _NbSets ? CATIntegerSets::Size (CastAsHandleOfSet (iSet), size) : E_FAIL;
  //return iSet < _Sets.Size () ? CATIntegerSets::Size (CastAsHandleOfSet (iSet), size) : E_FAIL;
}

#endif
