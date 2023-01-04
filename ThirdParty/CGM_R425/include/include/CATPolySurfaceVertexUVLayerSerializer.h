//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
//
// CATPolySurfaceVertexUVLayerSerializer
//
//=============================================================================
// 2008-02-29   BPG: New
//=============================================================================
#ifndef CATPolySurfaceVertexUVLayerSerializer_H
#define CATPolySurfaceVertexUVLayerSerializer_H

#include "PolySerializers.h"
#include "CATErrorDef.h"

class CATIPolySurface;
class CATIPolySurfaceVertexUVConstLayer;
class CATIPolySurfaceVertexIterator;


/**
Serializes the vertex uv from a CATIPolySurface into a compact array of floats or doubles.  
The buffer must be allocated before calls to the serialize methods and it must be sufficiently large to 
contain twice the number of vertices (3 * CATIPolySurface::GetNbVertices ()).
*/
class ExportedByPolySerializers CATPolySurfaceVertexUVLayerSerializer
{

public:

/** @name Serialization to a float buffer
    @{ */

  /**
   * Serializes the vertex uv layer into a float buffer.
   * The buffer must be pre-allocated and its size should be at least 2 * CATIPolySurface::GetNbVertices ().
   */
  HRESULT Serialize(CATIPolySurface &iSurface,
                    float *VertexUVBuffer) const;

  /**
   * Given a vertex uv const layer and an iterator, serializes the data into a float buffer.
   * The buffer must be pre-allocated and its size should be at least 2 * CATIPolySurface::GetNbVertices ().
   */
  HRESULT Serialize (CATIPolySurfaceVertexUVConstLayer &VertexUVLayer, CATIPolySurfaceVertexIterator &it,
                     float *VertexUVBuffer) const;

/** @} */

public:

/** @name Serialization to a double buffer
    @{ */

  /**
   * Serializes the vertex uv layer into a float buffer.
   * The buffer must be pre-allocated and its size should be at least 2 * CATIPolySurface::GetNbVertices ().
   */
  HRESULT Serialize (CATIPolySurface &iSurface,
                     double *VertexUVBuffer) const;

  /**
   * Given a vertex uv const layer and an iterator, serializes the data into a double buffer.
   * The buffer must be pre-allocated and its size should be at least 2 * CATIPolySurface::GetNbVertices ().
   */
  HRESULT Serialize(CATIPolySurfaceVertexUVConstLayer &VertexUVLayer, CATIPolySurfaceVertexIterator &it,
                    double *VertexUVBuffer) const;

/** @} */

};

#endif // !CATPolySurfaceVertexUVLayerSerializer_H
