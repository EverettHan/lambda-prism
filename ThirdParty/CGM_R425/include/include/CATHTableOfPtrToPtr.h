// COPYRIGHT DASSAULT SYSTEMES 2004, ALL RIGHTS RESERVED.
//===================================================================
//
// CATHTableOfPtrToPtr.h
//
//===================================================================
// September 2008 Creation: NDO
//===================================================================
#ifndef CATHTableOfPtrToPtr_h
#define CATHTableOfPtrToPtr_h

#include "PolyMathContainers.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"

#include "CATHTable_K_D.h"

class CATCGMOutput;


/**
This class is a hash table mapping a key to a value.
Insertion, removal and lookup are of average complexity O(1). (Worst case could be O(N).)  
This implementation does support automatic resizing.  The dimension of the hash table is set 
at construction but the table will resize itself if it is too small.
*/
class ExportedByPolyMathContainers CATHTableOfPtrToPtr
{

public:

  CATHTableOfPtrToPtr (const int iDimension = 0, const CATCompareElements* iCompareKeys = 0) : _HashTable (iDimension, iCompareKeys) {}
  ~CATHTableOfPtrToPtr () {}

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
  HRESULT Insert (void* key, void* data) {return _HashTable.Insert (key, data);}

  /**
   * Inserts or updates a pair (key, value) in the map.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> A new key is inserted or updated in the map.
   *   <li> <tt>S_FALSE</tt> The key is already in the map and does not need to be updated.
   *   <li> <tt>E_FAIL</tt> The pair cannot be inserted in the map because some error occured.
   * </ul>
   */
  HRESULT InsertOrUpdate (void* key, void* data) {return _HashTable.InsertOrUpdate (key, data);}

  /** 
   * Removes a key from the map.  If the key is not found in the map, the method returns S_FALSE.
   */
  HRESULT Remove (void* key) {return _HashTable.Remove (key);}

  /** 
   * Removes a key from the map.  If the key is not found in the map, the method returns S_FALSE.
   * The method also returns the value that is associated to the key being removed.
   */
  HRESULT Remove (void* key, void*& data) {return _HashTable.Remove (key, data);}

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
  HRESULT Update (void* key, void* data) {return _HashTable.Update (key, data);}

  /** 
   * Returns TRUE and the value associated to a key.  Returns FALSE if the key is not found in the map.
   */
  CATBoolean Locate (void* key, void*& data) const {return _HashTable.Locate (key, data);}

public:

  /**
   * Returns the number of elements in the map.
   */
  int Size () const {return _HashTable.Size ();}

  /**
   * Returns the size of the allocated memory used by the map in bytes.
   */
  unsigned int SizeOf () const {return _HashTable.SizeOf ();}

  HRESULT RemoveAll () {return _HashTable.RemoveAll ();}

public:

  /**
   * Inserts an element and returns its handle.
   */
  HRESULT Insert (void* key, void* data, Handle& oHandle) {return _HashTable.Insert (key, data, oHandle);}

  /** 
   * Finds the handle to the element in the hash table given its key.
   */
  Handle Find (void* key) const {return _HashTable.Find (key);}

  /** 
   * Returns the key given a handle.
   */
  static void* GetKey (Handle iHandle) {return CATHTable_K_D::GetKey (iHandle);}

  /** 
   * Returns the value given a handle.
   */
  static void* GetData (Handle iHandle) {return CATHTable_K_D::GetData (iHandle);}

  /** 
   * Updates the value given a handle.
   */
  HRESULT Update (Handle iHandle, void* data) {return _HashTable.Update (iHandle, data);}

public:

  /**
   * Iterator to cycle through all the elements in the map.
   */
  class ExportedByPolyMathContainers Iterator
  {
  public:
    Iterator (const CATHTableOfPtrToPtr& map) : _It (map._HashTable) {}
    ~Iterator () {}

    Handle GetHandle () const {return _It.GetHandle ();}
    void* GetKey () const {return _It.GetKey ();}
    void* GetData () const {return _It.GetData ();}

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

#endif
