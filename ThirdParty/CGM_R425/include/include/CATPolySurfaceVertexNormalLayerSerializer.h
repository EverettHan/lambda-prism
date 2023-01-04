//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
//
// CATPolySurfaceVertexNormalLayerSerializer
//
//=============================================================================
// 2008-02-29   BPG: New
//=============================================================================
#ifndef CATPolySurfaceVertexNormalLayerSerializer_H
#define CATPolySurfaceVertexNormalLayerSerializer_H

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "PolyhedralUtilities.h"
#include "CATErrorDef.h"

class CATIPolySurface;
class CATIPolySurfaceVertexNormalConstLayer;
class CATIPolySurfaceVertexIterator;


/**
Serializes the vertex normals from a CATIPolySurface into a compact array of floats or doubles.  
The buffer must be allocated before calls to the serialize methods and it must be sufficiently large to 
contain three times the number of vertices (3 * CATIPolySurface::GetNbVertices ()).
 */
class ExportedByPolyhedralUtilities CATPolySurfaceVertexNormalLayerSerializer
{

public:

/** @name Serialization to a float buffer
    @{ */

  /**
   * Serializes the vertex normal layer into a float buffer.
   * The buffer must be pre-allocated and its size should be at least 3 * CATIPolySurface::GetNbVertices ().
   */
  HRESULT Serialize (CATIPolySurface &iSurface,
                     float *VertexNormalBuffer) const;

  /**
   * Given a vertex normal const layer and an iterator, serializes the data into a float buffer.
   * The buffer must be pre-allocated and its size should be at least 3 * CATIPolySurface::GetNbVertices ().
   */
  HRESULT Serialize (CATIPolySurfaceVertexNormalConstLayer &VertexNormalLayer, CATIPolySurfaceVertexIterator &it,
                     float *VertexNormalBuffer) const;


  /**
   * Serializes the vertex normal layer into a float buffer.
   * The buffer must be pre-allocated and its size should be at least 4 * CATIPolySurface::GetNbVertices ().
   */
  HRESULT SerializeHomogeneous (CATIPolySurface &iSurface,
                     float *VertexNormalBuffer) const;

  /**
   * Given a vertex normal const layer and an iterator, serializes the data into a float buffer.
   * The buffer must be pre-allocated and its size should be at least 4 * CATIPolySurface::GetNbVertices ().
   */
  HRESULT SerializeHomogeneous (CATIPolySurfaceVertexNormalConstLayer &VertexNormalLayer, CATIPolySurfaceVertexIterator &it,
                     float *VertexNormalBuffer) const;

/** @} */

public:

/** @name Serialization to a double buffer
    @{ */

  /**
   * Serializes the vertex normal layer into a double buffer.
   * The buffer must be pre-allocated and its size should be at least 3 * CATIPolySurface::GetNbVertices ().
   */
  HRESULT Serialize (CATIPolySurface &iSurface,
                     double *VertexNormalBuffer) const;

  /**
   * Given a vertex normal const layer and an iterator, serializes the data into a double buffer.
   * The buffer must be pre-allocated and its size should be at least 3 * CATIPolySurface::GetNbVertices ().
   */
  HRESULT Serialize (CATIPolySurfaceVertexNormalConstLayer &VertexNormalLayer, CATIPolySurfaceVertexIterator &it,
                     double *VertexNormalBuffer) const;


  /**
   * Serializes the vertex normal layer into a double buffer.
   * The buffer must be pre-allocated and its size should be at least 4 * CATIPolySurface::GetNbVertices ().
   */
  HRESULT SerializeHomogeneous (CATIPolySurface &iSurface,
                     double *VertexNormalBuffer) const;

  /**
   * Given a vertex normal const layer and an iterator, serializes the data into a double buffer.
   * The buffer must be pre-allocated and its size should be at least 4 * CATIPolySurface::GetNbVertices ().
   */
  HRESULT SerializeHomogeneous (CATIPolySurfaceVertexNormalConstLayer &VertexNormalLayer, CATIPolySurfaceVertexIterator &it,
                     double *VertexNormalBuffer) const;

/** @} */

};

#endif // !CATPolySurfaceVertexNormalLayerSerializer_H
