// COPYRIGHT DASSAULT SYSTEMES 2005, ALL RIGHTS RESERVED.
//===================================================================
//
// CATMapOfIntToFloat.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// February 2005 Creation: NDO, ZFI
//===================================================================

#ifndef CATMapOfIntToFloat_h
#define CATMapOfIntToFloat_h

#include "PolyMathContainers.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATPolyRedBlackTree_K_D.h"

class CATCGMOutput;


class ExportedByPolyMathContainers CATMapOfIntToFloat
{

public:

  CATMapOfIntToFloat () {}
  ~CATMapOfIntToFloat () {}

public:

  // Insert a pair (key, value) in the map.
  // When a new key is inserted in the map, the method returns S_OK.
  // If the key is found in the map and the values match, then the method returns S_FALSE.
  // Otherwise, the pair cannot be inserted in the map and the method returns an error.
  inline HRESULT Insert (const int key, const float value);

  // Remove a key from the map.  If the key is not found in the map, the method returns S_FALSE.
  inline HRESULT Remove (const int key);

  // Update the value associated to a key in the map.
  // The method returns S_OK if the key is successfully updated, S_FALSE if the key is not found in the map,
  // and an error otherwise.
  inline HRESULT Update (const int key, const float value);

  // Returns TRUE and the value associated to a key.  Returns FALSE if the key is not found in the map.
  inline CATBoolean Locate (const int key, float& value) const;

public:

  // Return the number of elements in the map.
  inline int Size () const;

  inline HRESULT RemoveAll ();

private:

  // Map of pointer to pointer.
  class Specialize_CATPolyRedBlackTree_K_D (MapOfIntToFloat, int, float);

public:

  // Iterator to cycle through all the elements in the map.
  class Iterator
  {
  public:
    inline Iterator (const CATMapOfIntToFloat& map) : _It (map.Map ().Begin ()) {}

    inline int GetKey () const {return _It.GetKey ();}
    inline float GetData () const {return _It.GetData ();}

    inline Iterator& Begin (const CATMapOfIntToFloat& map) {_It = map.Map ().Begin (); return *this;}
    inline CATBoolean End () const {return _It.End ();}
    inline Iterator& operator++ () {++_It; return *this;}

  private:
    MapOfIntToFloat::Iterator _It;
  };

private:

  MapOfIntToFloat _Map;

public: 

  // For poor compilers!
  inline const MapOfIntToFloat& Map () const {return _Map;}

public:

  // For debugging purposes.
  void Print (CATCGMOutput& stream) const;

public:

  // DEPRECATED
  CATMapOfIntToFloat (const int) {}

};

inline HRESULT CATMapOfIntToFloat::Insert (const int key, const float data)
{
  return _Map.Insert (key, data);
}

inline HRESULT CATMapOfIntToFloat::Remove (const int key)
{
  return _Map.Erase (key);
}

inline HRESULT CATMapOfIntToFloat::Update (const int key, const float data)
{
  CATMapOfIntToFloat::MapOfIntToFloat::Iterator it (_Map.Find (key));
  if (!it.End ())
  {
    it.GetData () = data;
    return S_OK;
  }
  return S_FALSE;
}

inline CATBoolean CATMapOfIntToFloat::Locate (const int key, float& value) const
{
  CATMapOfIntToFloat::MapOfIntToFloat::Iterator it (_Map.Find (key));
  if (!it.End ())
  {
    value = it.GetData ();
    return TRUE;
  }
  return FALSE;
}

inline int CATMapOfIntToFloat::Size () const
{
  return _Map.Size ();
}

inline HRESULT CATMapOfIntToFloat::RemoveAll ()
{
  return _Map.Clear ();
}

#endif
