// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATMapOfIntIntToInt.h
//
//===================================================================
// Sep 2008  Creation: ZFI
// 2010-04-16 Revisited: NDO
//===================================================================
#ifndef CATMapOfIntIntToInt_h
#define CATMapOfIntIntToInt_h

#include "PolyMathContainers.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"

#include "CATHTable_KK_D.h"

class CATCGMOutput;


/**
All CATMapOfTypeXToTypeY are implemented with a hash table.
Insertion, removal and lookup are of average complexity O(1). (Worst case could be O(N).)  
This implementation does support automatic resizing.  The dimension of the hash table is set 
at construction but the table will resize itself if it is too small.
*/
class ExportedByPolyMathContainers CATMapOfIntIntToInt
{

public:

  CATMapOfIntIntToInt (const int iDimension = 0) : _HashTable (iDimension, Compare, HashKey) {}
  ~CATMapOfIntIntToInt () {}

public:

  /**
   * Inserts a pair (key, value) in the map.
   * When a new key is inserted in the map, the method returns S_OK.
   * If the key is found in the map and the values match, then the method returns S_FALSE.
   * Otherwise, the pair cannot be inserted in the map and the method returns an error.
   */
  inline HRESULT Insert (const int key1, const int key2, const int data);

  /**
   * Removes a key from the map.  If the key is not found in the map, the method returns S_FALSE.
   */
  inline HRESULT Remove (const int key1, const int key2);

  /**
   * Updates the value associated to a key in the map.
   * The method returns S_OK if the key is successfully updated, S_FALSE if the key is not found in the map,
   * and an error otherwise.
   */
  inline HRESULT Update (const int key1, const int key2, const int data);

  /**
   * Returns TRUE and the value associated to a key.  Returns FALSE if the key is not found in the map.
   */
  inline CATBoolean Locate (const int key1, const int key2, int& data) const;

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
  inline HRESULT Insert (const int key1, const int key2, const int data, Handle& oHandle);

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
  static inline int GetData (Handle iHandle);

  /**
   * Updates the value given a handle.
   */
  inline HRESULT Update (Handle iHandle, const int data);

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
    Iterator (const CATMapOfIntIntToInt& map) : _It (map._HashTable) {}
    ~Iterator () {}

    Handle GetHandle () const {return _It.GetHandle ();}
    int GetKey1 () const {return CATPtrToINT32 ( _It.GetKey1 ());}
    int GetKey2 () const {return CATPtrToINT32 ( _It.GetKey2 ());}
    int GetData () const {return CATPtrToINT32( _It.GetData ());}

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

inline HRESULT CATMapOfIntIntToInt::Insert (const int key1, const int key2, const int data) 
{
  return _HashTable.Insert (CATINT32ToPtr (key1), CATINT32ToPtr (key2), CATINT32ToPtr (data));
}

inline HRESULT CATMapOfIntIntToInt::Remove (const int key1, const int key2) 
{
  return _HashTable.Remove (CATINT32ToPtr (key1), CATINT32ToPtr (key2));
}

inline HRESULT CATMapOfIntIntToInt::Update (const int key1, const int key2, const int data) 
{
  return _HashTable.Update (CATINT32ToPtr (key1), CATINT32ToPtr (key2), CATINT32ToPtr (data));
}

inline CATBoolean CATMapOfIntIntToInt::Locate (const int key1, const int key2, int& data) const
{
  void* d = 0;
  CATBoolean found = _HashTable.Locate (CATINT32ToPtr (key1), CATINT32ToPtr (key2), d);
  data = CATPtrToINT32 (d);
  return found;
}

inline HRESULT CATMapOfIntIntToInt::Insert (const int key1, const int key2, const int data, Handle& oHandle)
{
  return _HashTable.Insert (CATINT32ToPtr (key1), CATINT32ToPtr (key2), CATINT32ToPtr (data), oHandle);
}

inline CATMapOfIntIntToInt::Handle CATMapOfIntIntToInt::Find (const int key1, const int key2) const
{
  return _HashTable.Find (CATINT32ToPtr (key1), CATINT32ToPtr (key2));
}

inline void CATMapOfIntIntToInt::GetKeys (Handle iHandle, int& key1, int& key2)
{
  void* k1 = 0;
  void* k2 = 0;
  CATHTable_KK_D::GetKeys (iHandle, k1, k2);
  key1 = CATPtrToINT32 (k1);
  key2 = CATPtrToINT32 (k2);
}

inline int CATMapOfIntIntToInt::GetData (Handle iHandle)
{
  return CATPtrToINT32 (CATHTable_KK_D::GetData (iHandle));
}

inline HRESULT CATMapOfIntIntToInt::Update (Handle iHandle, const int data)
{
  return _HashTable.Update (iHandle, CATINT32ToPtr (data));
}

#endif
