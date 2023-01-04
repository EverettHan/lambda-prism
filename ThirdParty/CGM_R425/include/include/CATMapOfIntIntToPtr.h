// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATMapOfIntIntToPtr.h
//
//===================================================================
// Sep 2008  Creation: ZFI
// 2013-10-07 Revisited: NDO
//===================================================================
#ifndef CATMapOfIntIntToPtr_h
#define CATMapOfIntIntToPtr_h

#include "PolyMathContainers.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"

#define CATMAPOFINTINTTOPTR_USE_HTABLE 1

#ifdef CATMAPOFINTINTTOPTR_USE_HTABLE

#include "CATHTable_KK_D.h"

class CATCGMOutput;


/**
All CATMapOfTypeXToTypeY are implemented with a hash table.
Insertion, removal and lookup are of average complexity O(1). (Worst case could be O(N).)  
This implementation does support automatic resizing.  The dimension of the hash table is set 
at construction but the table will resize itself if it is too small.
*/
class ExportedByPolyMathContainers CATMapOfIntIntToPtr
{

public:

  CATMapOfIntIntToPtr (const int iDimension = 0) : _HashTable (iDimension, Compare, HashKey) {}
  ~CATMapOfIntIntToPtr () {}

public:

  /**
   * Inserts a pair (key, value) in the map.
   * When a new key is inserted in the map, the method returns S_OK.
   * If the key is found in the map and the values match, then the method returns S_FALSE.
   * Otherwise, the pair cannot be inserted in the map and the method returns an error.
   */
  inline HRESULT Insert (const int key1, const int key2, void* data);

  /**
   * Removes a key from the map.  If the key is not found in the map, the method returns S_FALSE.
   */
  inline HRESULT Remove (const int key1, const int key2);

  /**
   * Updates the value associated to a key in the map.
   * The method returns S_OK if the key is successfully updated, S_FALSE if the key is not found in the map,
   * and an error otherwise.
   */
  inline HRESULT Update (const int key1, const int key2, void* data);

  /**
   * Returns TRUE and the value associated to a key.  Returns FALSE if the key is not found in the map.
   */
  inline CATBoolean Locate (const int key1, const int key2, void*& data) const;

public:

/** @name Handle-Based Access
    @{ */

  /**
   * A handle to an element in the hash table.
   * A handle provides direct access to the element.
   * A NULL handle is an invalid handle.  Handles are NOT stable after insertion or removal of elements.
   */
  typedef CATHTable_KK_D::Handle Handle;

  /**
   * Inserts an element and returns its handle.
   */
  inline HRESULT Insert (const int key1, const int key2, void* data, Handle& oHandle);

  /**
   * Finds the handle to the element in the hash table given its key.
   */
  inline Handle Find (const int key1, const int key2) const;

  /**
   * Returns the keys given a handle.
   */
  static inline void GetKeys (Handle iHandle, int& key1, int& key2);

  /**
   * Returns the data given a handle.
   */
  static inline void* GetData (Handle iHandle);

  /**
   * Updates the value given a handle.
   */
  inline HRESULT Update (Handle iHandle, void* data);

/** @} */

public:

  /**
   * Returns the number of elements in the map.
   */
  int Size () const {return _HashTable.Size ();}

  /**
   * Returns the size of the map in bytes.
   */
  unsigned int SizeOf () const {return _HashTable.SizeOf ();}

  HRESULT RemoveAll () {return _HashTable.RemoveAll ();}

public:

/** @name Iterator
    @{ */

  /**
   * Iterator to cycle through all the elements in the map.
   */
  class ExportedByPolyMathContainers Iterator
  {
  public:
    Iterator (const CATMapOfIntIntToPtr& map) : _It (map._HashTable) {}
    ~Iterator () {}

    Handle GetHandle () const {return _It.GetHandle ();}
    int GetKey1 () const {return CATPtrToINT32 ( _It.GetKey1 ());}
    int GetKey2 () const {return CATPtrToINT32 ( _It.GetKey2 ());}
    void* GetData () const {return _It.GetData ();}

    Iterator& Begin () {_It.Begin (); return *this;}
    CATBoolean End () const {return _It.End ();}
    Iterator& operator++ () {++_It; return *this;}

  private:
    CATHTable_KK_D::Iterator _It;
  };

  friend class Iterator;

/** @} */

private:

  CATHTable_KK_D _HashTable;

  static int Compare (void* iKey11, void* iKey12, void* iKey21, void* iKey22);
  static unsigned int HashKey (void* iKey1, void* iKey2);

public:

  // For debugging purposes.
  void Print (CATCGMOutput& stream) const;

};

inline HRESULT CATMapOfIntIntToPtr::Insert (const int key1, const int key2, void* data) 
{
  return _HashTable.Insert (CATINT32ToPtr (key1), CATINT32ToPtr (key2), data);
}

inline HRESULT CATMapOfIntIntToPtr::Remove (const int key1, const int key2) 
{
  return _HashTable.Remove (CATINT32ToPtr (key1), CATINT32ToPtr (key2));
}

inline HRESULT CATMapOfIntIntToPtr::Update (const int key1, const int key2, void* data) 
{
  return _HashTable.Update (CATINT32ToPtr (key1), CATINT32ToPtr (key2), data);
}

inline CATBoolean CATMapOfIntIntToPtr::Locate (const int key1, const int key2, void*& data) const
{
  return _HashTable.Locate (CATINT32ToPtr (key1), CATINT32ToPtr (key2), data);
}

inline HRESULT CATMapOfIntIntToPtr::Insert (const int key1, const int key2, void* data, Handle& oHandle)
{
  return _HashTable.Insert (CATINT32ToPtr (key1), CATINT32ToPtr (key2), data, oHandle);
}

inline CATMapOfIntIntToPtr::Handle CATMapOfIntIntToPtr::Find (const int key1, const int key2) const
{
  return _HashTable.Find (CATINT32ToPtr (key1), CATINT32ToPtr (key2));
}

inline void CATMapOfIntIntToPtr::GetKeys (Handle iHandle, int& key1, int& key2)
{
  void* k1 = 0;
  void* k2 = 0;
  CATHTable_KK_D::GetKeys (iHandle, k1, k2);
  key1 = CATPtrToINT32 (k1);
  key2 = CATPtrToINT32 (k2);
}

inline void* CATMapOfIntIntToPtr::GetData (Handle iHandle)
{
  return CATHTable_KK_D::GetData (iHandle);
}

inline HRESULT CATMapOfIntIntToPtr::Update (Handle iHandle, void* data)
{
  return _HashTable.Update (iHandle, data);
}


#else


#include "CATMapOfIntToPtr.h"

// Previous implementation.
class ExportedByPolyMathContainers CATMapOfIntIntToPtr
{

public:

  CATMapOfIntIntToPtr ();
  ~CATMapOfIntIntToPtr ();

public:

  HRESULT Insert (const int key1, const int key2, void* data);

  HRESULT Update (const int key1, const int key2, void* value);

  CATBoolean Locate (const int key1, const int key2, void*& data) const;

public:
  HRESULT Remove (const int key1, const int key2);
//  HRESULT Remove (const int key2);
  HRESULT RemoveAll ();

public:

class ExportedByPolyMathContainers Iterator
  {
  public:
    Iterator (const CATMapOfIntIntToPtr& map);
    ~Iterator () ;

    int GetKey1 () const;
    int GetKey2 () const;
    void* GetData () const;

    Iterator& Begin ();
    CATBoolean End () const;
    Iterator& operator++ ();

  private:
    CATMapOfIntToPtr::Iterator* iter1;
    CATMapOfIntToPtr::Iterator* iter2;
    const CATMapOfIntIntToPtr& _Map;
  };

public: 
  // For poor compilers!
  const CATMapOfIntToPtr& MapToFinalMap () const {return _MapToFinalMap;}

private:
  CATMapOfIntToPtr _MapToFinalMap;

};

#endif

#endif
