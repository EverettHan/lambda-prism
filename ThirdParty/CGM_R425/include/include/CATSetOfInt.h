// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATSetOfInt.h
//
//===================================================================
// October 2008 Creation: NDO
//===================================================================
#ifndef CATSetOfInt_h
#define CATSetOfInt_h

#include "PolyMathContainers.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"

#include "CATHTable_D.h"

class CATCGMOutput;


/**
Implementation of a set of integers as a hash table.
Insertion, deletion and lookup of elements in the set is o(Log N) time where N is
the number of elements in the set.  
*/
class ExportedByPolyMathContainers CATSetOfInt
{

public:

  /**
   * Constructs a set of integers.
   * @param iDimension
   *   An estimated number of elements to be inserted in the set.
   * @param iCompare
   *   A service to compare two elements from the set.
   *   See CATCompareElements (safe to cast the void* as integer.)
   */
  CATSetOfInt (const int iDimension = 0, const CATCompareElements* iCompare = 0) : _HashTable (iDimension, iCompare, HashKey) {}

  /**
   * Copy constructor.
   */
  CATSetOfInt (const CATSetOfInt& iRHS) : _HashTable (iRHS._HashTable) {}

  ~CATSetOfInt () {}

public:

  /**
   * Inserts an integer element in the set.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> when a new element is inserted in the table.
   *   <li> <tt>S_FALSE</tt> when the inserted element is already in the table
   *        or when an equivalent element (according to the comparison instance) is
   *        already in the set.
   *   <li> <tt>E_FAIL</tt> when any error occurs (memory allocation failure).
   * </ul>
   */
  INLINE HRESULT Insert (const int iElement);

  /**
   * Inserts an element and returns the equivalent integer.
   * @param iElement
   *   The elements inserted in the set.
   * @param oElementInSet
   *   An output parameter returning the equivalent element from the set.
   *   If the element inserted is not in the set, then the integer returned is 
   *   equal to the element.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> when a new element is inserted in the table.
   *   <li> <tt>S_FALSE</tt> when the inserted element is already in the table
   *        or when an equivalent element (according to the comparison instance) is
   *        already in the set.
   *   <li> <tt>E_FAIL</tt> when any error occurs (memory allocation failure).
   * </ul>
   */
  INLINE HRESULT Insert (const int iElement, int& oElementInSet);

  /**
   * Removes an element from the set.
   * The method returns <tt>S_FALSE</tt> if the element is not found in the set.
   */
  INLINE HRESULT Remove (const int iElement);

  /**
   * Returns <tt>TRUE</tt> and the value is found in the set.  Returns <tt>FALSE</tt> if not found.
   */
  INLINE CATBoolean Find (const int iElement) const;

public:

  /**
   * Returns the number of elements in the set.
   */
  INLINE int Size () const;

  INLINE HRESULT RemoveAll ();

public:

  /**
   * Return one element of the set
   * @return
   * S_OK if there was an element, S_FALSE otherwise
   */
  HRESULT GetOneElement(int & oElement) const;

  // Iterator to cycle through all the elements in the map.
  class Iterator
  {
  public:

    INLINE Iterator () {}
    INLINE Iterator (const CATSetOfInt& set) : _It (set._HashTable) {}

    INLINE Iterator& Begin () {_It.Begin (); return *this;}
    INLINE CATBoolean End () const {return _It.End ();}
    INLINE Iterator& operator++ () {++_It; return *this;}
    INLINE Iterator& operator+= (const unsigned int iCount) { _It += iCount; return *this; }

    INLINE int operator* () const {return CATPtrToINT32 (*_It);}

  private:
    CATHTable_D::Iterator _It;
  };

  friend class Iterator;

private:

  CATHTable_D _HashTable;
  static unsigned int HashKey (void* iKey);

public:

  // For debugging purposes.
  void Print (CATCGMOutput& stream) const;

private:

  // Assignment operator not allowed.
  CATSetOfInt& operator = (const CATSetOfInt& rhs);

};

INLINE HRESULT CATSetOfInt::Insert (const int iElement)
{
  return _HashTable.Insert (CATINT32ToPtr (iElement));
}

INLINE HRESULT CATSetOfInt::Insert (const int iElement, int& oElementInSet)
{
  CATHTable_D::Handle h = 0;
  HRESULT hr = _HashTable.Insert (CATINT32ToPtr (iElement), h);
  if (h)
    oElementInSet = CATPtrToINT32 (_HashTable.GetData (h));
  return hr;
}

INLINE HRESULT CATSetOfInt::Remove (const int iElement)
{
  return _HashTable.Remove (CATINT32ToPtr (iElement));
}

INLINE CATBoolean CATSetOfInt::Find (const int iElement) const
{
  return _HashTable.Find (CATINT32ToPtr (iElement)) ? TRUE : FALSE;
}

INLINE int CATSetOfInt::Size () const
{
  return _HashTable.Size ();
}

INLINE HRESULT CATSetOfInt::RemoveAll ()
{
  return _HashTable.RemoveAll ();
}

#endif
