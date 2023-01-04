// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATHTable_D.h
//
//===================================================================
// May 2009  Creation: NDO
//===================================================================
#ifndef CATHTable_D_h
#define CATHTable_D_h

#include "PolyMathContainers.h"
#include "CATMathInline.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"
#include "CATCompareElements.h"

#include "CATDataType.h"  // For 64-bit platforms.  (Conversion between integers and pointers.)

#define CATHTABLE_DEFAULT_HASH_TABLE_DIMENSION 31


/**
This class implements a hash table of elements.
Insertion, removal and lookup are of average complexity O(1). (Worst case could be O(N).)  
This implementation supports automatic resizing.  
The hash table will resize itself if it is too small when inserting new elements.
*/
class ExportedByPolyMathContainers CATHTable_D
{

public:

  typedef unsigned int HashKeyFunction (void*);

  /**
   * A handle to an element in the hash table.
   * A handle provides direct access to the element.
   * A NULL handle is an invalid handle.  Handles are NOT stable after insertion or removal of elements.
   */
  typedef CATULONGPTR* Handle;

public:

  /**
   * Constructs a hash table of elements.
   * @param iEstimatedSize
   *  The estimated number of elements.
   * @param iCompareElements
   *  The class for comparison of the elements in the hash table.
   * @param iHashFunction
   *  A pointer to a hash function.  This parameter is ignored if a comparison instance has been set.
   *  Do not use. See CATCompareElements for the hash function instead.
   */
  CATHTable_D (int iEstimatedSize = 0,
               const CATCompareElements* iCompareElements = 0,
               HashKeyFunction*	iHashFunction = 0);

  /**
   * Copy constructor.
   */
  CATHTable_D (const CATHTable_D& iRHS);

  ~CATHTable_D ();

public:

/** @name Insertion, Removal.
    @{ */

  /**
   * Inserts an element in the hash table.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> when a new element is inserted in the table.
   *   <li> <tt>S_FALSE</tt> when the inserted element is already in the table
   *        or when an equivalent element (according to the comparison instance) is
   *        already in the table.
   *   <li> <tt>E_FAIL</tt> when any error occurs (memory allocation failure).
   * </ul>
   */
  INLINE HRESULT Insert (void* data);

  /**
   * Removes an element from the table.
   * The method returns <tt>S_FALSE</tt> if the element is not found in the table.
   */
  HRESULT Remove (void* data);

/** @} */

public:

/** @name Insertion, Removal, Locate with handles.
    @{ */

  /**
   * Inserts an element and returns its handle.
   */
  HRESULT Insert (void* data, Handle& oHandle);

  /**
   * Finds the handle to an element in the table.  Returns the null handle, if no element is found.
   */
  Handle Find (void* data) const;

  /**
   * Finds the handle to an element in the table whose hash number is equal to the input hash number. 
   * If there are several elements with the same hash number, the method returns the handle to one of these elements
   * (no specific order.)
   * Returns the null handle, if no element is found.
   */
  Handle FindOne (const unsigned int iHashNumber) const;

  /**
   * Returns the element given its handle.
   */
  static INLINE void* GetData (Handle iHandle);

/** @} */

public:

  /**
   * Returns the number of elements in the table.
   */
  INLINE int Size () const;

  HRESULT RemoveAll ();

public:

  // Iterator to cycle through all the elements in the hash table.
  class ExportedByPolyMathContainers Iterator
  {
  public:

    Iterator () : _Index (0), _NbElements (0), _DataBuckets (0) {}
    Iterator (const CATHTable_D& htable);
    inline Iterator (const Iterator& iRHS) : _Index (iRHS._Index), _NbElements (iRHS._NbElements), _DataBuckets (iRHS._DataBuckets) {}

    ~Iterator () {_DataBuckets = 0;}

    inline Iterator& Begin () {_Index = 0; return *this;}
    inline CATBoolean End () const {return _Index >= _NbElements;}
    inline Iterator& operator++ () {++_Index; return *this;}
    inline Iterator& operator+= (const unsigned int iCount) { _Index += static_cast<int>(iCount); return *this; }

    inline Iterator& operator = (const Iterator& iRHS)
    {
      _Index = iRHS._Index;
      _NbElements = iRHS._NbElements;
      _DataBuckets = iRHS._DataBuckets;
      return *this;
    }

    inline Handle GetHandle () const {return (Handle) (_DataBuckets + 2*_Index);}
    inline void* operator* () const {return (void*) (*(_DataBuckets + 2*_Index));}

  private:
    int _Index;
    int _NbElements;
    const CATULONGPTR* _DataBuckets;
  };

  friend class Iterator;

private:

  HashKeyFunction* _HashFunction;
  const CATCompareElements* _CompareElements;

  int          _NbAllocatedBuckets; // Dimension of the hash table (maximum number of buckets to be stored in the hash table.)
  CATULONGPTR* _pAllocatedBuckets;  // Address of the allocated memory  
  CATULONGPTR* _pFirstFreeBucket;   // Address of the first free bucket

  // Buckets are by default CATULONGPTR.
  CATULONGPTR  _StaticBuckets[3 * CATHTABLE_DEFAULT_HASH_TABLE_DIMENSION];  // Static array (93 = 3 * _NbAllocatedBuckets with _NbAllocatedBuckets = 31) 

  int          _NbFreeBuckets;      // Number of free buckets.
  int          _NbStoredElems;      // Number of stored elements in the hash table.

private:

  HRESULT ReAllocate ();

  INLINE unsigned int ComputeHashNumber (void* data) const;  // Compute the hash number.
  INLINE unsigned int ComputeKey (void* data) const;         // Compute the key (hash number modulo # of allocated buckets.)
  INLINE int DataAreEqual (void* data1, void* data2) const;  // Compare two elements.

private:

  // Assignment operator not allowed.
  CATHTable_D& operator = (const CATHTable_D& rhs);

};


INLINE int CATHTable_D::Size () const
{
  return _NbStoredElems;
}


INLINE unsigned int CATHTable_D::ComputeHashNumber (void* data) const
{
  return _CompareElements ? _CompareElements->Hash (data) : _HashFunction (data);
}

INLINE unsigned int CATHTable_D::ComputeKey (void* data) const
{
  return ComputeHashNumber (data) % _NbAllocatedBuckets;
}

INLINE int CATHTable_D::DataAreEqual (void* data1, void* data2) const
{
  return _CompareElements ? !_CompareElements->Compare (data1, data2) : (data1 == data2);
}

INLINE HRESULT CATHTable_D::Insert (void* iKey)
{
  Handle handle;
  return Insert (iKey, handle);
}

INLINE void* CATHTable_D::GetData (CATHTable_D::Handle iHandle)
{
  return iHandle ? (void*) iHandle[0] : 0;
}

#endif
