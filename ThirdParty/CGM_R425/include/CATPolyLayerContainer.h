// COPYRIGHT DASSAULT SYSTEMES 2013, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyLayerContainer.h
//
//===================================================================
// January 2013  Creation: NDO
//===================================================================
#ifndef CATPolyLayerContainer_H
#define CATPolyLayerContainer_H

#include "PolyLayers.h"
#include "CATListPV.h"
#include "CATPolyRefCounted.h"
#include "CATIPolyLayer.h"

class CATIPolyLayerIterator;
class CATPolyLayerObserverContainer;


/**
 * Container of CATIPolyLayer.
 */
class ExportedByPolyLayers CATPolyLayerContainer : public CATPolyRefCounted
{

public:

  CATPolyLayerContainer () {}

  ~CATPolyLayerContainer ();

public:

  HRESULT AddLayer (CATIPolyLayer* iLayer);
  HRESULT RemoveLayer (CATIPolyLayer* iLayer);

public:

  unsigned int Size () const { return _Layers.Size (); }

  /**
   * Return the kth layer.  Do not release the layer returned (unless you call AddRef () explicitely.)
   */
  CATIPolyLayer* operator [] (unsigned int k) const { return (CATIPolyLayer*)_Layers[k + 1]; }

  /**
   * Given an index between 0 and Size () - 1 returns a layer.
   * @param oLayer [out, IUnknown#Release] 
   */
  inline HRESULT GetLayer (unsigned int index, CATIPolyLayer*& oLayer) const;
  
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
   * Creates an instance of an iterator through the layers.
   * @return
   *   An iterator that must be released.
   */
  static CATIPolyLayerIterator* NewIterator (const CATPolyLayerContainer& container);

  /**
   * Creates an instance of an iterator through the layers matching a specific class id .
   * @return
   *   An iterator that must be released.
   */
  static CATIPolyLayerIterator* NewIterator (const CATPolyLayerContainer& container, const CLSID& id);

private:

  CATListPV _Layers;

};


namespace Poly
{
  ExportedByPolyLayers CATIPolyLayerIterator* NewCustomLayerIterator (CATIPolyLayer* iLayer0, CATIPolyLayer* iLayer1,
    const CATPolyLayerContainer* container, const CLSID* id = 0);

  ExportedByPolyLayers CATIPolyLayerIterator* NewCustomLayerIterator (CATIPolyLayer* iLayer0, CATIPolyLayer* iLayer1, CATIPolyLayer* iLayer2,
    const CATPolyLayerContainer* container, const CLSID* id = 0);

  ExportedByPolyLayers CATIPolyLayerIterator* NewCustomLayerIterator (CATIPolyLayer* iLayer0, CATIPolyLayer* iLayer1,
    const CATPolyLayerObserverContainer* container, const CLSID* id = 0);
}


inline HRESULT CATPolyLayerContainer::GetLayer (unsigned int index, CATIPolyLayer*& oLayer) const
{
  oLayer = 0;
  ++index;
  oLayer = (CATIPolyLayer*)_Layers[index];
  if (oLayer)
    oLayer->AddRef ();
  return oLayer ? S_OK : S_FALSE;
}

#endif // !CATPolyLayerContainer_H
