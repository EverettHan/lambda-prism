// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyPreAllocatedFrameLayers.h
//
//===================================================================
// September 2011  Creation: ZFI
//===================================================================

#ifndef CATPolyBodyPreAllocatedFrameLayers_H
#define CATPolyBodyPreAllocatedFrameLayers_H

#include "PolyLayers.h"

#include "CATIPolyBodyFrameLayers.h"
#include "CATMapOfPtrToPtr.h"
#include "CATListPV.h"

class CATIPolySurfaceVertexPositionLayer;
class CATIPolySurfaceVertexNormalLayer;
class CATIPolySurfaceVertexTextureCoordLayer;


class ExportedByPolyLayers CATPolyBodyPreAllocatedFrameLayers : public CATIPolyBodyFrameLayers
{
public:
  CATPolyBodyPreAllocatedFrameLayers();
  virtual ~CATPolyBodyPreAllocatedFrameLayers ();
  
public:

 /**
  * Returns the vertex position layer for a CATPolyCell and a frame.
  * Frame numbers range from 1 to GetNbFrames () inclusive.
  */
  HRESULT GetVertexPositionLayer (CATPolyCell* iCell, const unsigned int iFrame, CATIPolySurfaceVertexPositionLayer*& oLayer);

  /**
   * Returns the surface vertex normal layer for a CATPolyCell and a frame.
   * Frame numbers range from 1 to GetNbFrames () inclusive.
   */
  HRESULT GetVertexNormalLayer (CATPolyFace* iFace, const unsigned int iFrame, CATIPolySurfaceVertexNormalLayer*& oLayer);

  /**
   * Returns the surface vertex texture coordinate layer for a CATPolyCell and a frame.
   * Frame numbers range from 1 to GetNbFrames () inclusive.
   */
  HRESULT GetVertexTextureCoordLayer (CATPolyFace* iFace, const unsigned int iFrame, CATIPolySurfaceVertexTextureCoordLayer*& oLayer);

  /**
   * Returns an iterator of data layers for a CATPolyCell and a frame.
   * Frame numbers range from 1 to GetNbFrames () inclusive.
   */
  HRESULT GetLayerIterator (CATPolyFace* iFace, const unsigned int iFrame, CATIPolyLayerIterator*& oLayerIterator) const;

public:

  HRESULT GetVertexPositionLayer (CATPolyCell* iCell, const unsigned int iFrame, CATIPolyVertexPositionConstLayer*& oLayer) const ;
  HRESULT GetVertexNormalLayer (CATPolyFace* iFace, const unsigned int iFrame, CATIPolySurfaceVertexNormalConstLayer*& oLayer) const ;
  HRESULT GetVertexTextureCoordLayer (CATPolyFace* iFace, const unsigned int iFrame, CATIPolySurfaceVertexTextureCoordConstLayer*& oLayer) const ;

  unsigned int GetNbFrames()const;

private:
  CATListPV _FramePositions, _FrameNormals, _FrameTexCoords;
};

#endif
