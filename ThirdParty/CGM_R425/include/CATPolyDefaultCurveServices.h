// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyDefaultCurveServices.h
//
//===================================================================
// July 2011  Creation: NDO
//===================================================================
#ifndef CATPolyDefaultCurveServices_H
#define CATPolyDefaultCurveServices_H

#include "PolyMeshTools.h"
#include "CATErrorDef.h"


/** @file 
 * Default services that can be applied to CATIPolyCurve.
 * These services are implemented in PolyhedralObjects.
 *
 * @see CATPolyServices.h
*/

class CATIPolyCurve;
class CATIPolySurfaceVertexLine;
class CATPolyEdge;
class CATPolyLine;

class CATPolyBoundingSphere;
class CATPolyAABB;
class CATPolyOBB;
class CATMathTransformation;

#include "CATLISTV_CATMathPoint.h"


/** @name Construction Services
    @{ */

/**
 * Creates a CATPolyLine from a list of points.
 */
ExportedByPolyMeshTools CATPolyLine* CATPolyCreatePolyLine (const CATLISTV(CATMathPoint)& iPoints);

/** @} */


/**
 * Returns the parent CATPolyEdge if this CATIPolySurfaceVertexLine belongs to a CATPolyBody.
 * (Default implementation.)
 * @param iPolyCurve
 *   The input curve.
 * @param oPolyEdge
 *   The output edge to which the CATIPolyCurve is attached.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if a CATPolyEdge is successfully returned.
 *   <li> <tt>S_FALSE</tt> if the CATIPolyCurve is not attached to any CATPolyEdge.
 *   <li> <tt>E_FAIL</tt> if an error occurs.
 * </ul>
 */
ExportedByPolyMeshTools HRESULT CATPolyDefaultGetPolyEdge (const CATIPolySurfaceVertexLine& iPolyCurve, const CATPolyEdge*& oPolyEdge);


/**
 * Computes the bounding sphere of a CATIPolyCurve.
 * @param iPosMatrix
 *   An optional transformation to apply to the vertex positions.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if the bounding volume is successfully computed.
 *   <li> <tt>S_FALSE</tt> if the bounding volume is not computed.
 *   <li> <tt>E_FAIL</tt> if an error occurs.
 * </ul>
 */
ExportedByPolyMeshTools HRESULT CATPolyDefaultComputeBoundingSphere (const CATIPolyCurve& iPolyCurve, CATPolyBoundingSphere& ioBoundingSphere,
                                                                     const CATMathTransformation* iPosMatrix);

/**
 * Computes the AABB of a CATIPolyCurve.
 * @param iPosMatrix
 *   An optional transformation to apply to the vertex positions.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if the bounding volume is successfully computed.
 *   <li> <tt>S_FALSE</tt> if the bounding volume is not computed.
 *   <li> <tt>E_FAIL</tt> if an error occurs.
 * </ul>
 */
ExportedByPolyMeshTools HRESULT CATPolyDefaultComputeAABB (const CATIPolyCurve& iPolyCurve,  CATPolyAABB& ioAABB,
                                                           const CATMathTransformation* iPosMatrix);

/**
 * Computes the OBB of a CATIPolyCurve.
 * @param iPosMatrix
 *   An optional transformation to apply to the vertex positions.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if the bounding volume is successfully computed.
 *   <li> <tt>S_FALSE</tt> if the bounding volume is not computed.
 *   <li> <tt>E_FAIL</tt> if an error occurs.
 * </ul>
 */
ExportedByPolyMeshTools HRESULT CATPolyDefaultComputeOBB (const CATIPolyCurve& iPolyCurve, CATPolyOBB& ioOBB,
                                                          const CATMathTransformation* iPosMatrix);

/**
 * Computes the AABB and OBB of a CATIPolyCurve.
 * @param iPosMatrix
 *   An optional transformation to apply to the vertex positions.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if the bounding volume is successfully computed.
 *   <li> <tt>S_FALSE</tt> if the bounding volume is not computed.
 *   <li> <tt>E_FAIL</tt> if an error occurs.
 * </ul>
 */
ExportedByPolyMeshTools HRESULT CATPolyDefaultComputeAABBAndOBB (const CATIPolyCurve& iPolyCurve, CATPolyAABB& ioAABB, CATPolyOBB& ioOBB,
                                                                 const CATMathTransformation* iPosMatrix);

#endif
