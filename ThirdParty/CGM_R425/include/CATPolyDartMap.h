// COPYRIGHT DASSAULT SYSTEMES 2022, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyDartMap
//
//=============================================================================
// 2022-02-07   NDO: New
//=============================================================================
#pragma once

#include "CATMapOfPtrToInt.h"


// Reserved (private).
// Map of darts to integers.
template<class DART>
class CATPolyDartMap
{

public:

  inline CATPolyDartMap (const int iDimension = 0);
  inline ~CATPolyDartMap () {}

  /**
   * A handle to a pair (dart, value).
   * A handle provides direct access to the pair (dart, value).
   * A NULL handle is an invalid handle.  Handles are NOT stable after insertion or removal of elements.
   */
  typedef CATMapOfPtrToInt::Handle Handle;

  /**
   * Inserts a pair (dart, value) in the map.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> The dart is inserted in the map.
   *   <li> <tt>S_FALSE</tt> The dart is already in the map and the values match.
   *   <li> <tt>E_FAIL</tt> The dart cannot be inserted in the map because the values do not match.
   * </ul>
   */
  HRESULT Insert (DART* d, int value) { return _Map.Insert ((void*) d, value); }

  /**
   * Inserts or updates a pair (dart, value) in the map.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> The dart is inserted in the map or its value is updated.
   *   <li> <tt>S_FALSE</tt> The dart is already in the map and its value does not need to be updated.
   *   <li> <tt>E_FAIL</tt> The dart cannot be inserted in the map because some error occured.
   * </ul>
   */
  HRESULT InsertOrUpdate (DART* d, int value) { return _Map.InsertOrUpdate ((void*) d, value); }

  /**
   * Removes a dart from the map.  
   * If the dart is not found in the map, the method returns S_FALSE.
   */
  HRESULT Remove (DART* d) { return _Map.Remove ((void*) d); }

  /**
   * Removes a dart from the map.  
   * If the dart is not found in the map, the method returns S_FALSE.
   * The method also returns the value associated to the dart being removed.
   */
  HRESULT Remove (DART* d, int& value) { return _Map.Remove ((void*) d, value); }

  /**
   * Updates the value associated to a dart in the map.
   * The method returns S_OK if the value is successfully updated, S_FALSE if the dart is not found in the map,
   * and an error otherwise.
   */
  HRESULT Update (DART* d, int value) { return _Map.Update ((void*) d, value); }

  /**
   * Returns true and the value associated to a dart.  
   * Returns false if the dart is not found in the map.
   */
  bool Locate (DART* d, int& value) const { return _Map.Locate ((void*) d, value); }

public:

  /**
   * Returns the number of darts in the map.
   */
  unsigned int Size () const { return _Map.Size (); }

  HRESULT RemoveAll () { return _Map.RemoveAll (); }

public:

  /**
   * Iterator cycling through all the darts in the map.
   */
  class Iterator
  {
  public:

    Iterator (const CATPolyDartMap& map) : _It (map._Map) {}
    ~Iterator () {}

    Handle GetHandle () const { return _It.GetHandle (); }
    DART* Dart () const { return _It.GetKey (); }
    int Value () const { return _It.GetData (); }

    Iterator& Begin () { _It.Begin (); return *this; }
    bool End () const { return _It.End (); }
    Iterator& operator++ () { ++_It; return *this; }

  private:

    CATMapOfPtrToInt::Iterator _It;

  };

  friend class Iterator;

private:

  CATMapOfPtrToInt _Map;

};


template<class DART>
inline CATPolyDartMap<DART>::CATPolyDartMap (const int iDimension) :
  _Map (iDimension)
{
}
