// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATMapOfPtrPtrToPtr.h
//
//===================================================================
//
// April 2010  Creation: NDO
//  
//===================================================================
#ifndef CATMapOfPtrPtrToPtr_h
#define CATMapOfPtrPtrToPtr_h

#include "PolyMathContainers.h"
#include "CATHTable_KK_D.h"
#include "CATBoolean.h"

class CATCGMOutput;


/*
All CATMapOfTypeXToTypeY are implemented with a hash table.
Insertion, removal and lookup are of average complexity O(1). (Worst case could be O(N).)  
This implementation does support automatic resizing.  The dimension of the hash table is set 
at construction but the table will resize itself if it is too small.
*/
class ExportedByPolyMathContainers CATMapOfPtrPtrToPtr
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

public:

  CATMapOfPtrPtrToPtr (const int iDimension = 0,
                       CompareFunction* ipCompareFunction = 0) : _HashTable (iDimension,ipCompareFunction) {}
  ~CATMapOfPtrPtrToPtr () {}

public:

  // Insert a pair (key, value) in the map.
  // When a new key is inserted in the map, the method returns S_OK.
  // If the key is found in the map and the values match, then the method returns S_FALSE.
  // Otherwise, the pair cannot be inserted in the map and the method returns an error.
  inline HRESULT Insert (const void* key1, const void* key2, void* data);

  // Remove a key from the map.  If the key is not found in the map, the method returns S_FALSE.
  inline HRESULT Remove (const void* key1, const void* key2);

  // Update the value associated to a key in the map.
  // The method returns S_OK if the key is successfully updated, S_FALSE if the key is not found in the map,
  // and an error otherwise.
  inline HRESULT Update (const void* key1, const void* key2, void* data);

  // Returns TRUE and the value associated to a key.  Returns FALSE if the key is not found in the map.
  inline CATBoolean Locate (const void* key1, const void* key2, void*& data) const;

public:

  // Handle-based access.

  // A handle to an element in the hash table.
  // A handle provides direct access to the element.
  // A NULL handle is an invalid handle.  Handles are NOT stable after insertion or removal of elements.
  typedef CATHTable_KK_D::Handle Handle;

  // Insert an element and return its handle.
  inline HRESULT Insert (const void* key1, const void* key2, void* data, Handle& oHandle);

  // Find the handle to the element in the hash table given its key.
  inline Handle Find (const void* key1, const void* key2) const;

  // Direct access to the key and the data given a handle.
  static inline void GetKeys (Handle iHandle, const void*& key1, const void*& key2);
  static inline void* GetData (Handle iHandle);

  // Direct update of the value given a handle.
  inline HRESULT Update (Handle iHandle, void* data);

public:

  // Return the number of elements in the map.
  int Size () const {return _HashTable.Size ();}

  // Return the size of the map in bytes.
  unsigned int SizeOf () const {return _HashTable.SizeOf ();}

  HRESULT RemoveAll () {return _HashTable.RemoveAll ();}

public:

  // Iterator to cycle through all the elements in the map.
  class ExportedByPolyMathContainers Iterator
  {
  public:
    Iterator (const CATMapOfPtrPtrToPtr& map) : _It (map._HashTable) {}
    ~Iterator () {}

    Handle GetHandle () const {return _It.GetHandle ();}
    const void* GetKey1 () const {return _It.GetKey1 ();}
    const void* GetKey2 () const {return _It.GetKey2 ();}
    void* GetData () const {return _It.GetData ();}

    Iterator& Begin () {_It.Begin (); return *this;}
    CATBoolean End () const {return _It.End ();}
    Iterator& operator++ () {++_It; return *this;}

  private:
    CATHTable_KK_D::Iterator _It;
  };

  friend class Iterator;

private:

  CATHTable_KK_D _HashTable;

public:

  // For debugging purposes.
  void Print (CATCGMOutput& stream) const;

};


inline HRESULT CATMapOfPtrPtrToPtr::Insert (const void* key1, const void* key2, void* data) 
{
  return _HashTable.Insert ((void*) key1, (void*) key2, data);
}

inline HRESULT CATMapOfPtrPtrToPtr::Remove (const void* key1, const void* key2) 
{
  return _HashTable.Remove ((void*) key1, (void*) key2);
}

inline HRESULT CATMapOfPtrPtrToPtr::Update (const void* key1, const void* key2, void* data)
{
  return _HashTable.Update ((void*) key1, (void*) key2, data);
}

inline CATBoolean CATMapOfPtrPtrToPtr::Locate (const void* key1, const void* key2, void*& data) const
{
  return _HashTable.Locate ((void*) key1, (void*) key2, data);
}

inline HRESULT CATMapOfPtrPtrToPtr::Insert (const void* key1, const void* key2, void* data, Handle& oHandle)
{
  return _HashTable.Insert ((void*) key1, (void*) key2, data, oHandle);
}

inline CATMapOfPtrPtrToPtr::Handle CATMapOfPtrPtrToPtr::Find (const void* key1, const void* key2) const
{
  return _HashTable.Find ((void*) key1, (void*) key2);
}

inline void CATMapOfPtrPtrToPtr::GetKeys (Handle iHandle, const void*& key1, const void*& key2)
{
  CATHTable_KK_D::GetKeys (iHandle, (void*&) key1, (void*&) key2);
}

inline void* CATMapOfPtrPtrToPtr::GetData (Handle iHandle)
{
  return CATHTable_KK_D::GetData (iHandle);
}

inline HRESULT CATMapOfPtrPtrToPtr::Update (Handle iHandle, void* data)
{
  return _HashTable.Update (iHandle, data);
}

#endif
