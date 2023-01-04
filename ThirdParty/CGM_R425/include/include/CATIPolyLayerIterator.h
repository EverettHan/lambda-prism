// COPYRIGHT DASSAULT SYSTEMES 2018, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyLayerIterator.h
//
//===================================================================
// September 2018  Creation: NDO
//===================================================================
#pragma once

#include "CATIPolyLayer.h"
#include "CATPolyRefCounted.h"
#include "CATErrorDef.h"


/**
 * An iterator through data layers.
 */
class CATIPolyLayerIterator : public CATPolyRefCounted
{

protected:

  virtual ~CATIPolyLayerIterator () {}

public:

  virtual CATIPolyLayerIterator& Begin () = 0;

  virtual bool End () const = 0;

  virtual CATIPolyLayerIterator& operator++ () = 0;

public:

  /**
   * Returns the current data layer.
   * @param oLayer
   *   The ouput layer.  The returned layer must be released (ref-counted.)
   */
  virtual HRESULT GetLayer (CATIPolyLayer*& oLayer) = 0;

  /**
   * Returns the current data layer.
   * You must call AddRef () explicitely on the returned pointer if you are keeping a reference.
   * Do not release the returned data layer unless you call AddRef () explicitely. 
   */
  virtual CATIPolyLayer* Get () = 0;
  virtual CATIPolyLayer* operator* () = 0;

};


// Helper class.
class CATPolyOneLayerIterator : public CATIPolyLayerIterator
{
public:

  CATPolyOneLayerIterator (CATIPolyLayer& layer) :
    _Layer (layer),
    _End (false)
  {
    _Layer.AddRef ();
  }

  ~CATPolyOneLayerIterator ()
  {
    _Layer.Release ();
  }

public:

  CATIPolyLayerIterator& Begin ()
  {
    _End = false;
    return *this;
  }

  bool End () const
  {
    return _End;
  }

  CATIPolyLayerIterator& operator++ ()
  {
    _End = true;
    return *this;
  }

public:

  HRESULT GetLayer (CATIPolyLayer*& oLayer)
  {
    if (oLayer)
      oLayer->Release ();
    oLayer = &_Layer;
    _Layer.AddRef ();
    return S_OK;
  }

  CATIPolyLayer* Get ()
  {
    return &_Layer;
  }

  CATIPolyLayer* operator* ()
  {
    return &_Layer;
  }

private:

  CATIPolyLayer& _Layer;
  bool _End;
};
