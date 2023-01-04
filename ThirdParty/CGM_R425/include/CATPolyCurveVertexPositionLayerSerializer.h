//=============================================================================
// COPYRIGHT Dassault Systemes 2008
//=============================================================================
//
// CATPolyCurveVertexPositionLayerSerializer
//
//=============================================================================
// 2008-03-07   BPG: New
//=============================================================================
#ifndef CATPolyCurveVertexPositionLayerSerializer_H
#define CATPolyCurveVertexPositionLayerSerializer_H

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "PolyhedralUtilities.h"
#include "CATErrorDef.h"

class CATIPolyCurve;


/**
Serializes the vertex positions from a CATIPolyCurve into a compact array of floats or doubles.  
The buffer must be allocated before calls to the serialize methods and it must be sufficiently large to 
contain three times the number of vertices (3 * CATIPolyCurve::GetNbVertices ()).

This serializer also provides methods that allocate the buffer.  See below.
 */
class ExportedByPolyhedralUtilities CATPolyCurveVertexPositionLayerSerializer
{

public:

/** @name Serialization to a float buffer
    @{ */

  /**
   * Serializes the vertex coordinate layer into a float buffer.
   * The buffer must be pre-allocated and its size should be at least 3 * CATIPolyCurve::GetNbVertices ().
   */
  HRESULT Serialize(CATIPolyCurve &iCurve,
                    float *VertexPositionBuffer) const;

  /**
   * Serializes the vertex coordinate layer into a float buffer.
   *
   * This specific method allocates the buffer.  It must be deleted by a call to <tt>delete []</tt>.
   * @param iCurve
   *   The input curve whose vertex position layer is to be serialized.
   * @param oVertexPositionBuffer
   *   The output buffer allocated by the method.  It must be deleted.
   * @param oVertexPositionBufferSize
   *   The size of the vertex buffer.
   */
  HRESULT Serialize(CATIPolyCurve &iCurve,
                    float *& oVertexPositionBuffer, int &oVertexPositionBufferSize) const;

/** @} */

public:

/** @name Serialization to a double buffer
    @{ */

  /**
   * Serializes the vertex normal layer into a double buffer.
   * The buffer must be pre-allocated and its size should be at least 3 * CATIPolyCurve::GetNbVertices ().
   */
  HRESULT Serialize(CATIPolyCurve &iCurve,
                    double *VertexPositionBuffer) const;

  /**
   * Serializes the vertex coordinate layer into a double buffer.
   *
   * This specific method allocates the buffer.  It must be deleted by a call to <tt>delete []</tt>.
   * @param iCurve
   *   The input curve whose vertex position layer is to be serialized.
   * @param oVertexPositionBuffer
   *   The output buffer allocated by the method.  It must be deleted.
   * @param oVertexPositionBufferSize
   *   The size of the vertex buffer.
   */
  HRESULT Serialize (CATIPolyCurve &iCurve,
                     double *& oVertexPositionBuffer, int &oVertexPositionBufferSize) const;

/** @} */

};

#endif // !CATPolyCurveVertexPositionLayerSerializer_H
