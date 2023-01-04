// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATHTable_KK_D.h
//
//===================================================================
//
// April 2010  Creation: NDO
//  
//===================================================================
#ifndef CATHTable_KK_D_h
#define CATHTable_KK_D_h

#include "PolyMathContainers.h"
#include "CATMathInline.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"

#include "CATDataType.h"  // For 64-bit platforms.  (Conversion between integers and pointers.)

#define CATHTABLE_DEFAULT_HASH_TABLE_DIMENSION 31


class ExportedByPolyMathContainers CATHTable_KK_D
{

public:

  /*
   * Compare function of type: int (*Compare) (const void*, const void*, const void*, const void*)
   * The comparaison function should be symmetric and return 0 if the two elements are equal.
   * Returns
   *   +1 if (p11, p12) > (p21, p22)
   *    0 if (p11, p12) = (p21, p22)
   *   -1 if (p11, p12) < (p21, p22)
  */
  typedef int CompareFunction (void* p11, void* p12, void* p21, void* p22);

  typedef unsigned int HashKeyFunction (void* p11, void* p12);

  // A handle to an element in the hash table.
  // A handle provides direct access to the element.
  // A NULL handle is an invalid handle.  Handles are NOT stable after insertion or removal of elements.
  typedef CATULONGPTR* Handle;

public:

  CATHTable_KK_D (int iEstimatedSize = 0,
                  CompareFunction* ipCompareFunction = 0,
                  HashKeyFunction*	ipHashKeyFunction = 0);

  ~CATHTable_KK_D ();

public:

  // Insert a pair (key, value) in the map.
  // When a new key is inserted in the map, the method returns S_OK.
  // If the key is found in the map and the values match, then the method returns S_FALSE.
  // Otherwise, the pair cannot be inserted in the map and the method returns an error.
  HRESULT Insert (void* key1, void* key2, void* value);

  // Remove a key from the map.  If the key is not found in the map, the method returns S_FALSE.
  HRESULT Remove (void* key1, void* key2);

  // Update the value associated to a key in the map.
  // The method returns S_OK if the key is successfully updated, S_FALSE if the key is not found in the map,
  // and an error otherwise.
  HRESULT Update (void* key1, void* key2, void* value);

  // Returns TRUE and the value associated to a key.  Returns FALSE if the key is not found in the map.
  CATBoolean Locate (void* key1, void* key2, void*& value) const;

public:

  // Handle-based access.

  // Insert an element and return its handle.
  HRESULT Insert (void* key1, void* key2, void* value, Handle& oHandle);

  // Find the handle to the element in the hash table given its key.
  Handle Find (void* key1, void* key2) const;

  // Direct access to the key and the data given a handle.
  static INLINE void GetKeys (Handle iHandle, void*& key1, void*& key2);
  static INLINE void* GetData (Handle iHandle);

  // Direct update of the value given a handle.
  INLINE HRESULT Update (Handle iHandle, void* value);

public:

  // Return the number of elements in the map.
  inline int Size () const;

  // Return the size of the allocated memory used by the map in bytes.
  unsigned int SizeOf () const;

  HRESULT RemoveAll ();

public:

  // Iterator to cycle through all the elements in the map.
  class ExportedByPolyMathContainers Iterator
  {
  public:
    Iterator (const CATHTable_KK_D& htable);
    ~Iterator () {_DataBuckets = 0;}

    inline Handle GetHandle () const {return (Handle) (_DataBuckets + 4*_Index);}
    inline void* GetKey1 () const {return (void*) (*(_DataBuckets + 4*_Index));}
    inline void* GetKey2 () const {return (void*) (*(_DataBuckets + 4*_Index + 1));}
    inline void* GetData () const {return (void*) (*(_DataBuckets + 4*_Index + 2));}

    inline Iterator& Begin () {_Index = 0; return *this;}
    inline CATBoolean End () const {return _Index >= _NbElements;}
    inline Iterator& operator++ () {++_Index; return *this;}

  private:
    int _Index;
    int _NbElements;
    const CATULONGPTR* _DataBuckets;
  };

  friend class Iterator;

private:

  HashKeyFunction* _pHashKeyFunction;
  CompareFunction* _pCompareFunction;

  int          _NbAllocatedBuckets; // Dimension of the hash table (maximum number of buckets to be stored in the hash table.)
  CATULONGPTR* _pAllocatedBuckets;  // Address of the allocated memory  
  CATULONGPTR* _pFirstFreeBucket;   // Address of the first free bucket

  // Buckets are by default CATULONGPTR.
  CATULONGPTR  _StaticBuckets[5 * CATHTABLE_DEFAULT_HASH_TABLE_DIMENSION];  // Static array (155 = 5 * _NbAllocatedBuckets with _NbAllocatedBuckets = 31) 

  int          _NbFreeBuckets;      // Number of free buckets. 
  int          _NbStoredElems;      // Number of stored elements in the hash table.

private:

  HRESULT ReAllocate ();

  INLINE unsigned int ComputeHashNumber (void* key1, void* key2) const;
  INLINE int KeysAreEqual (void* key11, void* key12, void* key21, void* key22) const;

};


inline int CATHTable_KK_D::Size () const
{
  return _NbStoredElems;
}


INLINE unsigned int CATHTable_KK_D::ComputeHashNumber (void* key1, void* key2) const
{
  unsigned int h = _pHashKeyFunction (key1, key2) % _NbAllocatedBuckets;
  return h;
}


INLINE int CATHTable_KK_D::KeysAreEqual (void* key11, void* key12, void* key21, void* key22) const
{
  return !_pCompareFunction (key11, key12, key21, key22);
}


INLINE void CATHTable_KK_D::GetKeys (CATHTable_KK_D::Handle iHandle, void*& key1, void*& key2)
{
  if (iHandle)
  {
    key1 = (void*) iHandle[0];
    key2 = (void*) iHandle[1];
  }
  else
  {
    key1 = 0;
    key2 = 0;
  }
}


INLINE void* CATHTable_KK_D::GetData (CATHTable_KK_D::Handle iHandle)
{
  return iHandle ? (void*) iHandle[2] : 0;
}


INLINE HRESULT CATHTable_KK_D::Update (CATHTable_KK_D::Handle iHandle, void* value)
{
  if (iHandle)
  {
    iHandle[2] = (CATULONGPTR) value;
    return S_OK;
  }
  return S_FALSE;
}

#endif
