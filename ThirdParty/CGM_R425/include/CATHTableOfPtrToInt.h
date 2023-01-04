// COPYRIGHT DASSAULT SYSTEMES 2004, ALL RIGHTS RESERVED.
//===================================================================
//
// CATHTableOfPtrToInt.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// September 2008 Creation: NDO
//===================================================================
#ifndef CATHTableOfPtrToInt_h
#define CATHTableOfPtrToInt_h

#include "PolyMathContainers.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"

#include "CATHTable_K_D.h"
#include "CATDataType.h"  // For 64-bit platforms.  (Conversion between integers and pointers.)

class CATCGMOutput;


/**
This class is a hash table mapping a key to a value.
Insertion, removal and lookup are of average complexity O(1). (Worst case could be O(N).)  
This implementation does support automatic resizing.  The dimension of the hash table is set 
at construction but the table will resize itself if it is too small.
*/
class ExportedByPolyMathContainers CATHTableOfPtrToInt
{

public:

  CATHTableOfPtrToInt (const int iDimension = 0) : _HashTable (iDimension) {}
  ~CATHTableOfPtrToInt () {}

  /**
   * A handle to an element in the hash table.
   * A handle provides direct access to the element.
   * A NULL handle is an invalid handle.  Handles are NOT stable after insertion or removal of elements.
   */
  typedef CATULONGPTR* Handle;

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
  HRESULT Insert (const void* key, const int data) {return _HashTable.Insert ((void*) key, CATINT32ToPtr (data));}

  /**
   * Inserts or updates a pair (key, value) in the map.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> A new key is inserted or updated in the map.
   *   <li> <tt>S_FALSE</tt> The key is already in the map and does not need to be updated.
   *   <li> <tt>E_FAIL</tt> The pair cannot be inserted in the map because some error occured.
   * </ul>
   */
  HRESULT InsertOrUpdate (const void* key, const int data) {return _HashTable.InsertOrUpdate ((void*) key, CATINT32ToPtr (data));}

  /** 
   * Removes a key from the map.  If the key is not found in the map, the method returns S_FALSE.
   */
  HRESULT Remove (const void* key) {return _HashTable.Remove ((void*) key);}

  /** 
   * Removes a key from the map.  If the key is not found in the map, the method returns S_FALSE.
   * The method also returns the value that is associated to the key being removed.
   */
  INLINE HRESULT Remove (const void* key, int& data);

  /**
   * Updates the value associated to a key in the map.
   * The method returns S_OK if the key is successfully updated, S_FALSE if the key is not found in the map,
   * and an error otherwise.
   */
  HRESULT Update (const void* key, const int data) {return _HashTable.Update ((void*) key, CATINT32ToPtr (data));}

  /** 
   * Returns TRUE and the value associated to a key.  Returns FALSE if the key is not found in the map.
   */
  INLINE CATBoolean Locate (const void* key, int& data) const;

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

  /**
   * Inserts an element and return its handle.
   */
  HRESULT Insert (const void* key, const int data, Handle& oHandle) {return _HashTable.Insert ((void*) key, CATINT32ToPtr (data), oHandle);}

  /** 
   * Finds the handle to the element in the hash table given its key.
   */
  Handle Find (const void* key) const {return _HashTable.Find ((void*) key);}

  /** 
   * Returns the key given a handle.
   */
  static const void* GetKey (Handle iHandle) {return CATHTable_K_D::GetKey (iHandle);}

  /** 
   * Returns the value given a handle.
   */
  static int GetData (Handle iHandle) {return CATPtrToINT32 (CATHTable_K_D::GetData (iHandle));}

  /** 
   * Updates the value given a handle.
   */
  HRESULT Update (Handle iHandle, const int data) {return _HashTable.Update (iHandle, CATINT32ToPtr (data));}

public:

  /**
   * Iterator to cycle through all the elements in the map.
   */
  class ExportedByPolyMathContainers Iterator
  {
  public:
    Iterator (const CATHTableOfPtrToInt& map) : _It (map._HashTable) {}
    ~Iterator () {}

    Handle GetHandle () const { return _It.GetHandle();}
    const void* GetKey () const {return _It.GetKey ();}
    int GetData () const {return CATPtrToINT32( _It.GetData ());}

    Iterator& Begin () {_It.Begin (); return *this;}
    CATBoolean End () const {return _It.End ();}
    Iterator& operator++ () {++_It; return *this;}

  private:
    CATHTable_K_D::Iterator _It;
  };

  friend class Iterator;

private:

  CATHTable_K_D _HashTable;

public:

  // For debugging purposes.
  void Print (CATCGMOutput& stream) const;

};


INLINE HRESULT CATHTableOfPtrToInt::Remove (const void* key, int& data)
{
  void* d = 0;
  HRESULT hr = _HashTable.Remove ((void*) key, d);
  data = CATPtrToINT32 (d);
  return hr;
}


INLINE CATBoolean CATHTableOfPtrToInt::Locate (const void* key, int& data) const
{
  void* d = 0;
  CATBoolean found = _HashTable.Locate ((void*) key, d);
  data = CATPtrToINT32 (d);
  return found;
}

#endif
