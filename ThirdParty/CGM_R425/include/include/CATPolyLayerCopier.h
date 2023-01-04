// COPYRIGHT DASSAULT SYSTEMES 2021, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyLayerCopier.h
//
//===================================================================
// June 2021   Revisited: NDO
//===================================================================
#pragma once

#include "PolyLayers.h"
#include "CATErrorDef.h"
#include "CATMapOfPtrToPtr.h"

class CATIPolyObject;
class CATIPolyPoint;
class CATIPolyCurve;
class CATIPolySurface;
class CATIPolyLayer;
class CATMapOfIntToInt;
class CATPolyLayerCopierRegistry;


/**
A class to copy a layer from a polyhedral object and add the copy to another polyhedral object.
*/
class ExportedByPolyLayers CATPolyLayerCopier
{

public:

  CATPolyLayerCopier ();

  ~CATPolyLayerCopier ();

public:

  class Filter
  {
  public:

    /**
     * Returns <tt>true</tt> to skip a layer.
     */
    virtual bool Skip (const CATIPolyLayer& iLayer) = 0;

  };

public:

  /**
   * Method that copies a layer associated to a polyhedral object onto another polyhedral object.
   * The method adds the layer to the destination object.
   * @param iLayer
   *   The input layer.
   * @param oLayer
   *   The layer that was filled in with the data from the input layer.
   *   The returned layer must be released (ref-counted.)
   * @return
   *   The method returns S_OK and the new layer upon a successful copy.
   *   The method returns S_FALSE
   */
  HRESULT Copy (const CATIPolyObject& iSourceObject, const CATIPolyLayer& iLayer,
    CATIPolyObject& iDestinationObject, CATIPolyLayer*& oLayer,
    CATMapOfIntToInt* iVertexMap = 0, CATMapOfIntToInt* iTriangleMap = 0);

  /**
   * Method that copies all the native layers associated to a polyhedral object onto another polyhedral object.
   * The method adds the layer to the destination object.
   * @param iSourceObject
   *   The source polyhedral object.
   * @param oDestinationObject
   *   The destination object.
   * @param iFilter
   *   An optional filter to skip layers.
   *   Without a layer, all the native layers are copied.
   * @return
   *   The method returns S_OK upon a successful copy of the layers.
   */
  HRESULT Copy (const CATIPolyObject& iSourceObject, CATIPolyObject& iDestinationObject, Filter* iFilter = 0,
    CATMapOfIntToInt* iVertexMap = 0, CATMapOfIntToInt* iTriangleMap = 0);

private:

  CATPolyLayerCopierRegistry& _Registry;
  CATMapOfPtrToPtr _LayerMap;  // Map of input layers to their copies.

};
