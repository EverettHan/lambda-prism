//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
//
// CATPolySurfaceVertexTextureLayerSerializer
//
//=============================================================================
// 2008-04-23   ZFI
//=============================================================================
#ifndef CATPolySurfaceVertexTextureLayerSerializer_H
#define CATPolySurfaceVertexTextureLayerSerializer_H

#include "PolySerializers.h"
#include "CATErrorDef.h"

class CATIPolySurface;
class CATIPolySurfaceVertexTextureCoordLayer;
class CATIPolySurfaceVertexTextureCoordConstLayer;
class CATIPolySurfaceVertexIterator;


/**
Serializes the vertex positions from a CATIPolySurface into a compact array of floats or doubles.  
The buffer must be allocated before calls to the serialize methods and it must be sufficiently large to 
contain three times the number of vertices (3 * CATIPolySurface::GetNbVertices ()).
 */
class ExportedByPolySerializers CATPolySurfaceVertexTextureLayerSerializer
{

public:

/** @name Serialization to a float buffer
    @{ */

  /**
   * Serializes the texture coordinates into a float buffer.
   * The buffer must be pre-allocated and its size should be at least iNbComponents * CATIPolySurface::GetNbVertices ().
   * By default, <tt>iNbComponents</tt> is equal to 3.
   */
  HRESULT SerializeTexCoords (CATIPolySurface& iSurface,
                              float *VertexTextureBuffer, const int iNbComponents = 3) const;
  
  /**
   * Serializes the texture coordinates into a float buffer.
   * The buffer must be pre-allocated and its size should be at least iNbComponents * CATIPolySurface::GetNbVertices ().
   * By default, <tt>iNbComponents</tt> is equal to 3.
   */
  HRESULT SerializeTexCoords (CATIPolySurfaceVertexTextureCoordConstLayer& VertexTexCoordlLayer, 
                              CATIPolySurfaceVertexIterator &it,
                              float *VertexTextureBuffer, const int iNbComponents = 3) const;

  /**
   * Serializes tangent and binormals into float buffers.
   */
  HRESULT SerializeTanBinormals (CATIPolySurface &iSurface,
                                 float *VertexTangentBuffer,
                                 float *VertexBinormalBuffer) const;

/** @} */

public:

/** @name Serialization to a double buffer
    @{ */

  /**
   * Serializes the texture coordinates into a double buffer.
   * The buffer must be pre-allocated and its size should be at least iNbComponents * CATIPolySurface::GetNbVertices ().
   * By default, <tt>iNbComponents</tt> is equal to 3.
   */
  HRESULT SerializeTexCoords (CATIPolySurface &iSurface,
                              double *VertexTextureBuffer, const int iNbComponents = 3) const;

  /**
   * Serializes tangent and binormals into double buffers.
   */
  HRESULT SerializeTanBinormals (CATIPolySurface &iSurface,
                                 double *VertexTangentBuffer,
                                 double *VertexBinormalBuffer) const;

/** @} */

};

#endif // !CATPolySurfaceVertexTextureLayerSerializer_H
