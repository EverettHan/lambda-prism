//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
//
// CATPolySurfaceVertexPositionLayerSerializer
//
//=============================================================================
// 2008-02-29   BPG: New
//=============================================================================
#ifndef CATPolySurfaceVertexPositionLayerSerializer_H
#define CATPolySurfaceVertexPositionLayerSerializer_H

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "PolyhedralUtilities.h"
#include "CATErrorDef.h"

class CATIPolySurface;
class CATIPolySurfaceVertexPositionConstLayer;
class CATIPolySurfaceVertexIterator;


/**
Serializes the vertex positions from a CATIPolySurface into a compact array of floats or doubles.  
The buffer must be allocated before calls to the serialize methods and it must be sufficiently large to 
contain three times the number of vertices (3 * CATIPolySurface::GetNbVertices ()).
 */
class ExportedByPolyhedralUtilities CATPolySurfaceVertexPositionLayerSerializer
{

public:

/** @name Serialization to a float buffer
    @{ */

  /**
   * Serializes the vertex coordinate layer into a float buffer.
   * The buffer must be pre-allocated and its size should be at least 3 * CATIPolySurface::GetNbVertices ().
   */
  HRESULT Serialize (CATIPolySurface &iSurface,
                     float *VertexPositionBuffer) const;

  /**
   * Given a vertex position const layer and an iterator, serializes the data into a float buffer.
   * The buffer must be pre-allocated and its size should be at least 3 * CATIPolySurface::GetNbVertices ().
   */
  HRESULT Serialize (CATIPolySurfaceVertexPositionConstLayer &VertexPositionLayer, CATIPolySurfaceVertexIterator &it,
                     float *VertexPositionBuffer) const;

  /**
   * Serializes the vertex coordinate layer into a float buffer.
   * The buffer must be pre-allocated and its size should be at least 4 * CATIPolySurface::GetNbVertices ().
   */
  HRESULT SerializeHomogeneous (CATIPolySurface &iSurface,
                     float *VertexPositionBuffer) const;

  /**
   * Given a vertex position const layer and an iterator, serializes the data into a float buffer.
   * The buffer must be pre-allocated and its size should be at least 4 * CATIPolySurface::GetNbVertices ().
   */
  HRESULT SerializeHomogeneous (CATIPolySurfaceVertexPositionConstLayer &VertexPositionLayer, CATIPolySurfaceVertexIterator &it,
                     float *VertexPositionBuffer) const;

/** @} */

public:

/** @name Serialization to a double buffer
    @{ */

  /**
   * Serializes the vertex coordinate layer into a double buffer.
   * The buffer must be pre-allocated and its size should be at least 3 * CATIPolySurface::GetNbVertices ().
   */
  HRESULT Serialize (CATIPolySurface &iSurface,
                     double *VertexPositionBuffer) const;

  /**
   * Given a vertex position const layer and an iterator, serializes the data into a double buffer.
   * The buffer must be pre-allocated and its size should be at least 3 * CATIPolySurface::GetNbVertices ().
   */
  HRESULT Serialize (CATIPolySurfaceVertexPositionConstLayer &VertexPositionLayer, CATIPolySurfaceVertexIterator &it,
                     double *VertexPositionBuffer) const;

  /**
   * Serializes the vertex coordinate layer into a double buffer.
   * The buffer must be pre-allocated and its size should be at least 4 * CATIPolySurface::GetNbVertices ().
   */
  HRESULT SerializeHomogeneous (CATIPolySurface &iSurface,
                     double *VertexPositionBuffer) const;

  /**
   * Given a vertex position const layer and an iterator, serializes the data into a double buffer.
   * The buffer must be pre-allocated and its size should be at least 4 * CATIPolySurface::GetNbVertices ().
   */
  HRESULT SerializeHomogeneous (CATIPolySurfaceVertexPositionConstLayer &VertexPositionLayer, CATIPolySurfaceVertexIterator &it,
                     double *VertexPositionBuffer) const;

/** @} */

};

#endif // !CATPolySurfaceVertexPositionLayerSerializer_H
