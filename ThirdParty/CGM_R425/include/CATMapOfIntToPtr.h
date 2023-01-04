// COPYRIGHT DASSAULT SYSTEMES 2004, ALL RIGHTS RESERVED.
//===================================================================
//
// CATMapOfIntToPtr.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// June 2004 Creation: NDO
//===================================================================
#ifndef CATMapOfIntToPtr_h
#define CATMapOfIntToPtr_h

#include "PolyMathContainers.h"

#define CATMAPOFINTTOPTR_USE_HTABLE 1

#ifdef CATMAPOFINTTOPTR_USE_HTABLE

#include "CATHTableOfIntToPtr.h"

class ExportedByPolyMathContainers CATMapOfIntToPtr : public CATHTableOfIntToPtr
{

public:

  CATMapOfIntToPtr () : CATHTableOfIntToPtr (0) {}

  CATMapOfIntToPtr( const CATMapOfIntToPtr& iOther ) : CATHTableOfIntToPtr( iOther ) {}

  CATMapOfIntToPtr (const int iDimension) : CATHTableOfIntToPtr (iDimension) {}

};

#else

#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATPolyRedBlackTree_K_D.h"

class CATCGMOutput;


/*
All CATMapOfTypeXToTypeY are implemented as a balanced binary tree (red-black tree).
Insertion, removal and lookup are of complexity O(log N) where N is the number of elements in the map.
See also CATHTableOfTypeXToTypeY for an implementation of the map using a Hash Table.
*/
class ExportedByPolyMathContainers CATMapOfIntToPtr
{

public:

  CATMapOfIntToPtr () {}
  ~CATMapOfIntToPtr () {}

public:

  // Insert a pair (key, value) in the map.
  // When a new key is inserted in the map, the method returns S_OK.
  // If the key is found in the map and the values match, then the method returns S_FALSE.
  // Otherwise, the pair cannot be inserted in the map and the method returns an error.
  inline HRESULT Insert (const int key, void* data);

  // Remove a key from the map.  If the key is not found in the map, the method returns S_FALSE.
  inline HRESULT Remove (const int key);

  // Update the value associated to a key in the map.
  // The method returns S_OK if the key is successfully updated, S_FALSE if the key is not found in the map,
  // and an error otherwise.
  inline HRESULT Update (const int key, void* data);

  // Returns TRUE and the value associated to a key.  Returns FALSE if the key is not found in the map.
  inline CATBoolean Locate (const int key, void*& data) const;

public:

  // Return the number of elements in the map.
  inline int Size () const;

  inline HRESULT RemoveAll ();

private:

  // Map of integer to pointer.
  class Specialize_CATPolyRedBlackTree_K_D (MapOfIntToPtr, int, void*);

public:

  // Iterator to cycle through all the elements in the map.
  class Iterator
  {
  public:
    inline Iterator (const CATMapOfIntToPtr& map) : _It (map.Map ().Begin ()) {}

    inline int GetKey () const {return _It.GetKey ();}
    inline void* GetData () const {return _It.GetData ();}

    inline Iterator& Begin (const CATMapOfIntToPtr& map) {_It = map.Map ().Begin (); return *this;}
    inline CATBoolean End () const {return _It.End ();}
    inline Iterator& operator++ () {++_It; return *this;}

  private:
    MapOfIntToPtr::Iterator _It;
  };

private:

  MapOfIntToPtr _Map;

public: 

  // For poor compilers!
  inline const MapOfIntToPtr& Map () const {return _Map;}

public:

  // For debugging purposes.
  void Print (CATCGMOutput& stream) const;

};

inline HRESULT CATMapOfIntToPtr::Insert (const int key, void* data)
{
  return _Map.Insert (key, data);
}

inline HRESULT CATMapOfIntToPtr::Remove (const int key)
{
  return _Map.Erase (key);
}

inline HRESULT CATMapOfIntToPtr::Update (const int key, void* data)
{
  CATMapOfIntToPtr::MapOfIntToPtr::Iterator it (_Map.Find (key));
  if (!it.End ())
  {
    it.GetData () = data;
    return S_OK;
  }
  return S_FALSE;
}

inline CATBoolean CATMapOfIntToPtr::Locate (const int key, void*& value) const
{
  CATMapOfIntToPtr::MapOfIntToPtr::Iterator it (_Map.Find (key));
  if (!it.End ())
  {
    value = it.GetData ();
    return TRUE;
  }
  return FALSE;
}

inline int CATMapOfIntToPtr::Size () const
{
  return _Map.Size ();
}

inline HRESULT CATMapOfIntToPtr::RemoveAll ()
{
  return _Map.Clear ();
}

#endif

#endif
