// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolyBodyFrameLayers.h
//
//===================================================================
// September 2011  Creation: NDO
//===================================================================
#ifndef CATIPolyBodyFrameLayers_H
#define CATIPolyBodyFrameLayers_H

#include "PolyhedralAttributes.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATPolyRefCounted.h"

class CATPolyCell;
class CATPolyFace;

class CATIPolyVertexPositionConstLayer;
class CATIPolySurfaceVertexNormalConstLayer;
class CATIPolySurfaceVertexTextureCoordConstLayer;
class CATIPolyLayerIterator;


/**
 * Interface to access the various data layers associated to the cells of a CATPolyBody
 * for each frame in a sequence.
 * 
 * The layers supported are:
 * <ul>
 *   <li> Vertex position layer (point, curve and surface vertex position.)
 *   <li> Surface vertex normal layer.
 *   <li> Surface vertex texture coordinate layer.
 *  </ul>
 *
 * Access to a specific layer is provided given a CATPolyCell and a frame number (unsigned int.)
 * Frame numbers range from 1 to GetNbFrames () inclusive.
 * The layers must be released after a call to the Get methods.
 * 
 * The methods return:
 * <ul>
 *   <li> <tt>S_OK</tt> If a layer is available for the given cell and frame.
 *   <li> <tt>S_FALSE</tt> If no layer is available for the given cell and frame.
 *   <li> <tt>E_FAIL</tt> If an error occurs.
 * </ul>
 */
class ExportedByPolyhedralAttributes CATIPolyBodyFrameLayers : public CATPolyRefCounted
{

public:

  virtual ~CATIPolyBodyFrameLayers ();

public:

  virtual unsigned int GetNbFrames () const = 0;

public:

  /**
   * Returns the vertex position layer for a CATPolyCell and a frame.
   * Frame numbers range from 1 to GetNbFrames () inclusive.
   */
  virtual HRESULT GetVertexPositionLayer (CATPolyCell* iCell, const unsigned int iFrame, CATIPolyVertexPositionConstLayer*& oLayer) const = 0;

  /**
   * Returns the surface vertex normal layer for a CATPolyCell and a frame.
   * Frame numbers range from 1 to GetNbFrames () inclusive.
   */
  virtual HRESULT GetVertexNormalLayer (CATPolyFace* iFace, const unsigned int iFrame, CATIPolySurfaceVertexNormalConstLayer*& oLayer) const = 0;

  /**
   * Returns the surface vertex texture coordinate layer for a CATPolyCell and a frame.
   * Frame numbers range from 1 to GetNbFrames () inclusive.
   */
  virtual HRESULT GetVertexTextureCoordLayer (CATPolyFace* iFace, const unsigned int iFrame, CATIPolySurfaceVertexTextureCoordConstLayer*& oLayer) const = 0;

  /**
   * Returns an iterator of data layers for a CATPolyCell and a frame.
   * Frame numbers range from 1 to GetNbFrames () inclusive.
   */
  virtual HRESULT GetLayerIterator (CATPolyFace* iFace, const unsigned int iFrame, CATIPolyLayerIterator*& oLayerIterator) const = 0;

protected:

  CATIPolyBodyFrameLayers () {}

};

#endif
