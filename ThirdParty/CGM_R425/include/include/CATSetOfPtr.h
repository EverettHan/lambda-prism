// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATSetOfPtr.h
//
//===================================================================
// September 2008 Creation: NDO
//===================================================================
#ifndef CATSetOfPtr_h
#define CATSetOfPtr_h

#include "PolyMathContainers.h"
#include "CATHTable_D.h"

class CATCGMOutput;

#define CATSETOFINT_USE_HTABLE_D 1


/**
Implementation of a set of integers as a hash table.
Insertion, removal and lookup are of average complexity O(1). (Worst case is O(N) 
where N is the number of elements in the set.)  
*/
class ExportedByPolyMathContainers CATSetOfPtr
{

public:

  CATSetOfPtr (const int iDimension = 0, const CATCompareElements* iCompare = 0) : _HashTable (iDimension, iCompare) {}

  /**
   * Copy constructor.
   */
  CATSetOfPtr (const CATSetOfPtr& iRHS) : _HashTable (iRHS._HashTable) {}

  ~CATSetOfPtr () {}

public:

  /**
   * A handle to an element in the hash table.
   * A handle provides direct access to the element.
   * A NULL handle is an invalid handle.  Handles are NOT stable after insertion or removal of elements.
   */
  typedef void* Handle;

public:

/** @name Insertion, Removal and Locate.
    @{ */

  /**
   * Inserts an element and returns its handle.
   * The optional argument is a handle that will point to the element after its insertion.
   * The methods returns <tt>S_OK</tt> if the element is inserted and <tt>S_FALSE</tt> if the element is already in the set.
   * If the element is in the set, then the handle is set to the position of the element.
   * It returns <tt>E_FAIL</tt> or any other failure code for any error.
   */
  inline HRESULT Insert (void* data, Handle* oHandle = 0);

  /**
   * Removes an element from the set.
   * The method returns <tt>S_OK</tt> if the element is removed and 
   * <tt>S_FALSE</tt> if the element is not found in the set.
   */
  inline HRESULT Remove (void* data);

  /**
   * Finds the handle to an element in the set.  Returns the null handle, if no element is found.
   */
  inline Handle Find (void* data) const;

  /**
   * Finds the handle to an element in the set whose hash number is equal to the input hash number. 
   * If there are several elements with the same hash number, the method returns the handle to one of these elements
   * (no specific order.)
   * Returns the null handle, if no element is found.
   */
  inline Handle FindOne (const unsigned int iHashNumber) const;

  // Returns the element given a handle.  Returns NULL if the handle is invalid.
  inline void* Get (Handle iHandle) const;

/** @} */

public:

  /**
   * Returns the number of elements in the set.
   */
  inline int Size () const;

  /**
   * Removes all elements.
   */
  inline HRESULT RemoveAll ();

public:

  /**
   * Iterator to cycle through all the elements in the set.
   */
  class Iterator
  {
  public:

    inline Iterator () {}
    inline Iterator (const CATSetOfPtr& set) : _It (set._HashTable) {}
    inline Iterator (const Iterator& iRHS) : _It (iRHS._It) {}

    inline Iterator& Begin () {_It.Begin (); return *this;}
    inline CATBoolean End () const {return _It.End ();}
    inline Iterator& operator++ () {++_It; return *this;}
    inline Iterator& operator+= (const unsigned int iCount) { _It += iCount; return *this; }

    inline Iterator& operator = (const Iterator& iRHS)
    {
      _It = iRHS._It;
      return *this;
    }

    inline Handle GetHandle () const {return  _It.GetHandle(); };
    inline void*  GetData   () const {return *_It;}
    inline void*  operator* () const {return *_It;}


  private:
    CATHTable_D::Iterator _It;
  };

  friend class Iterator;

private:

  CATHTable_D _HashTable;

public:

  // For debugging purposes.
  void Print (CATCGMOutput& stream) const;

};

inline HRESULT CATSetOfPtr::Insert (void* data, Handle* oHandle)
{
  CATHTable_D::Handle handle = 0;
  HRESULT hr = _HashTable.Insert (data, handle);
  if (oHandle)
    *oHandle = handle;
  return hr;
}

inline HRESULT CATSetOfPtr::Remove (void* data)
{
  return _HashTable.Remove (data);
}

inline CATSetOfPtr::Handle CATSetOfPtr::Find (void* data) const
{
  return _HashTable.Find (data);
}

inline CATSetOfPtr::Handle CATSetOfPtr::FindOne (const unsigned int iHashNumber) const
{
  return _HashTable.FindOne (iHashNumber);
}

inline int CATSetOfPtr::Size () const
{
  return _HashTable.Size ();
}

inline HRESULT CATSetOfPtr::RemoveAll ()
{
  return _HashTable.RemoveAll ();
}

inline void* CATSetOfPtr::Get (Handle iHandle) const
{
  return _HashTable.GetData ((CATHTable_D::Handle) iHandle);
}

#endif
