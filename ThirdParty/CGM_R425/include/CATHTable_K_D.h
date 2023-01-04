// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATHTable_K_D.h
//
//===================================================================
//
// May 2009  Creation: NDO - Adapted from CATCGMHashTableWithAssoc.
//  
//===================================================================
#ifndef CATHTable_K_D_h
#define CATHTable_K_D_h

#include "PolyMathContainers.h"
#include "CATMathInline.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"
#include "CATCompareElements.h"

#include "CATDataType.h"  // For 64-bit platforms.  (Conversion between integers and pointers.)

#define CATHTABLE_DEFAULT_HASH_TABLE_DIMENSION 31


/**
This class is a hash table mapping a key to a value.
Insertion, removal and lookup are of average complexity O(1). (Worst case could be O(N).)  
This implementation does support automatic resizing.  The dimension of the hash table is set 
at construction but the table will resize itself if it is too small.
*/
class ExportedByPolyMathContainers CATHTable_K_D
{

public:

  // Could be done in a virtual class.
  typedef unsigned int HashKeyFunction (void*);

  /**
   * A handle to an element in the hash table.
   * A handle provides direct access to the element.
   * A NULL handle is an invalid handle.  Handles are NOT stable after insertion or removal of elements.
   */
  typedef CATULONGPTR* Handle;

public:

  CATHTable_K_D (int iEstimatedSize = 0,
                 const CATCompareElements* iCompareKeys = 0,
                 HashKeyFunction*	ipHashKeyFunction = 0);

  /**
   * @brief retarded copy ctor ( iterate over all data using iterator )
   */
  CATHTable_K_D( const CATHTable_K_D& iOther );

  ~CATHTable_K_D ();

public:

  /**
   * Inserts a pair (key, value) in the map.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> A new key is inserted in the map.
   *   <li> <tt>S_FALSE</tt> The key is already in the map and the values match.
   *   <li> <tt>E_FAIL</tt> The pair cannot be inserted in the map because the values do not match or some other error.
   * </ul>
   */
  HRESULT Insert (void* key, void* value);

  /**
   * Inserts or updates a pair (key, value) in the map.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> A new key is inserted or updated in the map.
   *   <li> <tt>S_FALSE</tt> The key is already in the map and does not need to be updated.
   *   <li> <tt>E_FAIL</tt> The pair cannot be inserted in the map because some error occured.
   * </ul>
   */
  HRESULT InsertOrUpdate (void* key, void* value);

  /** 
   * Removes a key from the map.  If the key is not found in the map, the method returns S_FALSE.
   */
  INLINE HRESULT Remove (void* key);

  /** 
   * Removes a key from the map.  If the key is not found in the map, the method returns S_FALSE.
   * The method also returns the value that is associated to the key being removed.
   */
  HRESULT Remove (void* key,  void*& value);

  /**
   * Updates the value associated to a key in the map.
   * The method returns S_OK if the key is successfully updated, S_FALSE if the key is not found in the map,
   * and an error otherwise.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> A value is successfully updated.
   *   <li> <tt>S_FALSE</tt> The key is not in the map.
   *   <li> <tt>E_FAIL</tt> Some error occured.
   * </ul>
   */
  HRESULT Update (void* key, void* value);

  /** 
   * Returns TRUE and the value associated to a key.  Returns FALSE if the key is not found in the map.
   */
  CATBoolean Locate (void* key, void*& value) const;

public:

  // Handle-based access.

  /**
   * Inserts an element and returns its handle.
   * @param oHandle
   *   The handle to the element in the map. This is an output parameter which is set to a valid handle even
   *   when the method fails because a different value is already stored in the map for this key.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> A new key is inserted in the map.
   *   <li> <tt>S_FALSE</tt> The key is already in the map and the values match.  The handle to the value is set.
   *   <li> <tt>E_FAIL</tt> The pair cannot be inserted in the map because the values do not match or some other error.
   *                        The handle is set if the value cannot be inserted because it does not match the stored value.
   *                      
   * </ul>
   */
  HRESULT Insert (void* key, void* value, Handle& oHandle);

  /** 
   * Finds the handle to the element in the hash table given its key.
   */
  Handle Find (void* key) const;

  /** 
   * Returns the key given a handle.
   */
  static INLINE void* GetKey (Handle iHandle);

  /** 
   * Returns the value given a handle.
   */
  static INLINE void* GetData (Handle iHandle);

  /** 
   * Updates the value given a handle.
   */
  INLINE HRESULT Update (Handle iHandle, void* value);

public:

  /**
   * Returns the number of elements in the map.
   */
  INLINE int Size () const;

  /**
   * Returns the size of the allocated memory used by the map in bytes.
   */
  unsigned int SizeOf () const;

  HRESULT RemoveAll ();

public:

  /**
   * Iterator to cycle through all the elements in the map.
   */
  class ExportedByPolyMathContainers Iterator
  {
  public:
    Iterator (const CATHTable_K_D& htable);
    ~Iterator () {_DataBuckets = 0;}

    INLINE Handle GetHandle () const {return (Handle) (_DataBuckets + 3*_Index);}
    INLINE void* GetKey () const {return (void*) (*(_DataBuckets + 3*_Index));}
    INLINE void* GetData () const {return (void*) (*(_DataBuckets + 3*_Index + 1));}

    INLINE Iterator& Begin () {_Index = 0; return *this;}
    INLINE CATBoolean End () const {return _Index >= _NbElements;}
    INLINE Iterator& operator++ () {++_Index; return *this;}

  private:
    int _Index;
    int _NbElements;
    const CATULONGPTR* _DataBuckets;
  };

  friend class Iterator;

private:

  HashKeyFunction* _HashFunction;
  const CATCompareElements* _CompareKeys;

  int          _NbAllocatedBuckets; // Dimension of the hash table (maximum number of buckets to be stored in the hash table.)
  CATULONGPTR* _pAllocatedBuckets;  // Address of the allocated memory  
  CATULONGPTR* _pFirstFreeBucket;   // Address of the first free bucket

  // Buckets are by default CATULONGPTR.
  CATULONGPTR  _StaticBuckets[4 * CATHTABLE_DEFAULT_HASH_TABLE_DIMENSION];  // Static array (124 = 4 * _NbAllocatedBuckets with _NbAllocatedBuckets = 31) 

  int          _NbFreeBuckets;      // Number of free buckets. 
  int          _NbStoredElems;      // Number of stored elements in the hash table.

private:

  HRESULT ReAllocate ();

  INLINE unsigned int ComputeHashNumber (void* key) const;  // Compute the hash number (modulo # of allocated buckets.)
  INLINE int KeysAreEqual (void* key1, void* key2) const;   // Compare two elements.

};


INLINE HRESULT CATHTable_K_D::Remove (void* key)
{
  void* value = 0;
  return Remove (key, value);
}


INLINE int CATHTable_K_D::Size () const
{
  return _NbStoredElems;
}


INLINE unsigned int CATHTable_K_D::ComputeHashNumber (void* key) const
{
  unsigned int h = _CompareKeys ? _CompareKeys->Hash (key) : _HashFunction (key);
  return h % _NbAllocatedBuckets;
}


INLINE int CATHTable_K_D::KeysAreEqual (void* key1, void* key2) const
{
  return _CompareKeys ? !_CompareKeys->Compare (key1, key2) : (key1 == key2);
}


INLINE void* CATHTable_K_D::GetKey (CATHTable_K_D::Handle iHandle)
{
  return iHandle ? (void*) iHandle[0] : 0;
}


INLINE void* CATHTable_K_D::GetData (CATHTable_K_D::Handle iHandle)
{
  return iHandle ? (void*) iHandle[1] : 0;
}


INLINE HRESULT CATHTable_K_D::Update (CATHTable_K_D::Handle iHandle, void* value)
{
  if (iHandle)
  {
    iHandle[1] = (CATULONGPTR) value;
    return S_OK;
  }
  return S_FALSE;
}

#endif
