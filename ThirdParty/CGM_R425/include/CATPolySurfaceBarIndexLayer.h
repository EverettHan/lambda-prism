// COPYRIGHT DASSAULT SYSTEMES 2014, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySurfaceBarIndexLayer.h
//
//===================================================================
// May 2014  Creation NDO
//===================================================================
#ifndef CATPolySurfaceBarIndexLayer_H
#define CATPolySurfaceBarIndexLayer_H

#include "PolyLayers.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"

#include "CATMapOfIntIntToInt.h"


/**
 * Layer associating a bar defined by a pair of vertices from a CATIPolySurface to an index in an array.
 * Indices starts at 1 and are incremented each time a bar is added.
 * The index 0 is invalid.
 * After removal of a bar, its index is recycled for the next bar added.
 */
class ExportedByPolyLayers CATPolySurfaceBarIndexLayer 
{

public :

  CATPolySurfaceBarIndexLayer (const unsigned int iEstimatedNbEntities = 0);

  ~CATPolySurfaceBarIndexLayer ();

  inline void SetIncrement (const unsigned int iIncrement);
  inline unsigned int AllocatedSize () const;

public:

  /**
   * Adds a bar and returns its index.
   */
  HRESULT Add (const int v0, const int v1, unsigned int& b);

  /**
   * Finds the index of the bar between the two vertices v0 and v1.
   * If the bar is not found, then adds a bar and returns its index.
   */
  HRESULT FindOrAddBar (const int v0, const int v1, unsigned int& b);

  /**
  * Removes a bar given its index.
  * The index is recycled for the next bar.
  */
  HRESULT Remove (unsigned int b);

  /**
   * Removes a bar and invalidates its index.
   * The index is recycled for the next bar.
   */
  inline HRESULT Remove (const int v0, const int v1);

  /**
   * Returns the vertices defining the bar.
   */
  inline void GetBar (unsigned int b, int& v0, int& v1) const;

  /**
   * Gets the index of a bar.
   */
  inline unsigned int GetIndex (const int v0, const int v1) const;

public:

  /**
   * Iterator through all the bars that have been added to this layer.
   */
  class Iterator
  {
  public:
    Iterator (const CATPolySurfaceBarIndexLayer& layer) : _It (layer._MapEntityToIndex) {}
    ~Iterator () {}

    void GetBar (int& v0, int& v1) const {v0 = _It.GetKey1 (); v1 = _It.GetKey2 ();}
    int GetStartVertex () const {return _It.GetKey1 ();}
    int GetEndVertex () const {return _It.GetKey2 ();}
    unsigned int GetIndex () const {return (unsigned int) _It.GetData ();}

    Iterator& Begin () {_It.Begin (); return *this;}
    CATBoolean End () const {return _It.End ();}
    Iterator& operator++ () {++_It; return *this;}

  private:
    CATMapOfIntIntToInt::Iterator _It;
  };

  friend class Iterator;

private:

  CATMapOfIntIntToInt _MapEntityToIndex;

  unsigned int _AllocatedSize;  
  unsigned int _Increment;

  struct Bar
  {
    int _V[2];
  };

  Bar* _Bars;  // Array of bars.

  unsigned int _LastUndefinedIndex;  // For recycling.

private:

  HRESULT Reallocate (const int iNbBarsToAllocate);

  HRESULT MapInsert (const int v0, const int v1, unsigned int index, CATMapOfIntIntToInt::Handle& h);

  inline void PushUndefinedIndex (unsigned int index);
  inline unsigned int PopUndefinedIndex ();

};

inline void CATPolySurfaceBarIndexLayer::SetIncrement (const unsigned int iIncrement)
{
  _Increment = iIncrement;
}

inline unsigned int CATPolySurfaceBarIndexLayer::AllocatedSize () const
{
  return _AllocatedSize;
}

inline unsigned int CATPolySurfaceBarIndexLayer::GetIndex (const int v0, const int v1) const
{
  int index = 0;
  CATBoolean found = (v0 < v1) ? _MapEntityToIndex.Locate (v0, v1, index) : _MapEntityToIndex.Locate (v1, v0, index);
  return found ? (unsigned int) index : 0;
}

inline void CATPolySurfaceBarIndexLayer::GetBar (unsigned int b, int& v0, int& v1) const
{
  // No range check.
  if (_Bars)
  {
    v0 = _Bars[b-1]._V[0];
    v1 = _Bars[b-1]._V[1];
  }
}

inline void CATPolySurfaceBarIndexLayer::PushUndefinedIndex (unsigned int index)
{
  if (_Bars)
  {
    _Bars[index-1]._V[0] = (int) _LastUndefinedIndex;
    _Bars[index-1]._V[1] = 0;
    _LastUndefinedIndex = index;
  }
}

inline unsigned int CATPolySurfaceBarIndexLayer::PopUndefinedIndex ()
{
  unsigned int index = _LastUndefinedIndex;
  if (index && _Bars)
    _LastUndefinedIndex = (unsigned int) _Bars[index-1]._V[0];
  return index;
}

inline HRESULT CATPolySurfaceBarIndexLayer::Remove (const int v0, const int v1)
{
  return Remove (GetIndex (v0, v1));
}

#endif
