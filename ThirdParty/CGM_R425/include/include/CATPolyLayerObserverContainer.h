// COPYRIGHT DASSAULT SYSTEMES 2018, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyLayerObserverContainer.h
//
//===================================================================
// October 2018  Creation: NDO
//===================================================================
#ifndef CATPolyLayerObserverContainer_H
#define CATPolyLayerObserverContainer_H

#include "PolyLayers.h"
#include "CATListPV.h"

class CATIPolyLayer;
class CATIPolyLayerIterator;
class CATIPolySurfaceObserver;
//#include "CATIPolyLayer.h"
//#include "CATIPolySurfaceObserver.h"
#include "CATErrorDef.h"


/**
 * Container of (CATIPolyLayer, CATIPolySurfaceObserver) pairs.
 */
class ExportedByPolyLayers CATPolyLayerObserverContainer 
{

public:

  CATPolyLayerObserverContainer () {}

  ~CATPolyLayerObserverContainer ();

public:

  /**
   * Adds a pair (layer, observer) to the container.
   * The layer or the observer can be null.
   */
  HRESULT Add (CATIPolyLayer* iLayer, CATIPolySurfaceObserver* iObserver);

  /**
   * Removes a layer from the container.
   * The observer associated to the layer from the pair (layer, observer),
   * if any, is also removed.
   */
  HRESULT Remove (CATIPolyLayer* iLayer);

  /**
  * Removes an observer from the container.
  * The layer associated to the layer from the pair (layer, observer),
  * if any, is also removed.
  */
  HRESULT Remove (CATIPolySurfaceObserver* iObserver);

public:

  /**
   * Iterator through the pairs of (layer, observer).
   */
  class Iterator
  {

  public:

    inline Iterator (const CATPolyLayerObserverContainer& LOC) :
      _LOL (LOC._LayerObserverList),
      _Size (_LOL.Size ()),
      _Index (1)
    {}

    inline Iterator& Begin ()
    {
      _Index = 1;
      return *this;
    }

    inline bool End () const
    {
      return _Index > _Size;
    }

    inline Iterator& operator++ ()
    {
      _Index += 2;
      return *this;
    }

  public:

    inline CATIPolyLayer* GetLayer ()
    {
      return (CATIPolyLayer*) _LOL[_Index];  // Index is odd.
    }

    inline CATIPolySurfaceObserver* GetObserver ()
    {
      return (CATIPolySurfaceObserver*) _LOL[_Index+1];  // Index is odd.
    }

  private:

    const CATListPV& _LOL;  // Layer-Observer list.
    unsigned int _Size;
    unsigned int _Index;

  };

public:

  /**
   * Iterator through the pairs of (layer, observer) in reverse order.
   */
  class ReverseIterator
  {

  public:

    inline ReverseIterator (const CATPolyLayerObserverContainer& LOC) :
      _LOL (LOC._LayerObserverList),
      _Size (_LOL.Size ()),
      _Index (_Size)  // Even
    {}

    inline ReverseIterator& Begin ()
    {
      _Index = _Size;  // Even
      return *this;
    }

    inline bool End () const
    {
      return _Index == 0 || _Index > _Size;
    }

    inline ReverseIterator& operator++ ()
    {
      _Index -= 2;
      return *this;
    }

  public:

    inline CATIPolyLayer* GetLayer ()
    {
      return (CATIPolyLayer*)_LOL[_Index-1];  // Index is even.
    }

    inline CATIPolySurfaceObserver* GetObserver ()
    {
      return (CATIPolySurfaceObserver*)_LOL[_Index];  // Index is even.
    }

  private:

    const CATListPV& _LOL;  // Layer-Observer list.
    unsigned int _Size;
    unsigned int _Index;

  };

public:

  /**
   * Returns the most recently added layer matching the input class id.
   * @param oLayer [out, IUnknown#Release]
   */
  HRESULT GetLayer (const CLSID& id, CATIPolyLayer*& oLayer) const;

  /**
   * Returns true if there is a layer of given id in the container.
   */
  bool HasLayer (const CLSID& id) const;

public:

  /**
   * Returns an iterator through the layers.
   */
  static CATIPolyLayerIterator* NewIterator (const CATPolyLayerObserverContainer& container);

  /**
  * Returns an iterator through the layers matching a specific class id.
  */
  static CATIPolyLayerIterator* NewIterator (const CATPolyLayerObserverContainer& container, const CLSID& id);

private:

  CATListPV _LayerObserverList;

  friend class Iterator;
  friend class CATPolyLayerIteratorLOCImpl;
  friend class CATPolyLayerIteratorLOCIDImpl;

};

#endif // !CATPolyLayerObserverContainer_H
