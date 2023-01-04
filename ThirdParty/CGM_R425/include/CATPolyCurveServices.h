// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyCurveServices.h
//
//===================================================================
// January 2011  Creation: NDO
//===================================================================
#ifndef CATPolyCurveServices_H
#define CATPolyCurveServices_H

#include "PolyhedralUtilities.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"

/** @file
 * Global services about CATIPolyCurve.
 *
 * @see CATPolyServices.h
 * @see CATPolyCGMServices.h
*/

class CATIPolyCurve;
class CATPolyMathCurve;
class CATPolyBoundingSphere;
class CATPolyAABB;
class CATPolyOBB;
class CATIPolyVertexFloatPositionConstLayer;

class CATMathTransformation;
class CATMathPoint;
class CATMathVector;
class CATMathBox;


namespace Poly
{
  /** @name CATIPolyCurve Services: Queries
   *
   * CATPolyCurveServices.h
   * @{ */

   /**
    * Returns true if the surface has a float vertex position layer.
    */
  ExportedByPolyhedralUtilities bool HasFloatVertexPositionLayer (const CATIPolyCurve& C);

  /**
   * Returns true if the curve has a vertex tangent layer.
   */
  ExportedByPolyhedralUtilities bool HasVertexTangentLayer (const CATIPolyCurve& C);

  /** @} */
};


/** @name Curve Supports
    @{ */

    /**
     * Returns a CATPolyMathCurve that is associated to the support (either directly or indirectly).
     * @param iPolyCurve
     *   The curve.
     * @param oCurve
     *   The object returned MUST be deleted by the caller.
     * @return
     * <ul>
     *   <tt>S_OK</tt> if a CATPolyMathCurve is returned.
     *   <tt>S_FALSE</tt> if there is no CATPolyMathCurve.
     *   <tt>E_FAIL</tt> or another error code if an error occurs.
     * </ul>
     */
ExportedByPolyhedralUtilities HRESULT CATPolyGetMathCurve (const CATIPolyCurve& iPolyCurve, CATPolyMathCurve*& oCurve);

/** @} */


/** @name Bounding Volumes
    @{ */


namespace Poly
{

  /**
   * Computes the bounding box of a CATIPolyCurve instance.
   * @param iPolyCurve
   *   The input CATIPolyCurve.
   * @param ioBox
   *   The computed bounding box.
   * @param iPosMatrix
   *   An optional transformation applied to the points.
   * @return
   *   S_OK for a successful call
   *   S_FALSE if the bounding box has not been computed.
   *   E_FAIL if an error occurs during the computation.
   */
  ExportedByPolyhedralUtilities HRESULT ComputeBoundingBox (const CATIPolyCurve& iPolyCurve,
    CATMathBox& ioBox,
    const CATMathTransformation* iPosMatrix = 0);

}


    /**
     * Returns a bounding sphere of the CATIPolyCurve instance.
     * @param iPolyCurve
     *   The input curve.
     * @param ioBoundingSphere
     *   The bounding sphere that will be set by a successful call.
     * @param iPosMatrix
     *   An optional transformation defining the position of the surface.
     * @return
     *   S_OK for a successful call
     *   S_FALSE if the bounding sphere has not been set.
     *   E_FAIL if an error occurs during the computation.
     */
ExportedByPolyhedralUtilities HRESULT CATPolyGetBoundingSphere (const CATIPolyCurve& iPolyCurve,
  CATPolyBoundingSphere& ioBoundingSphere,
  const CATMathTransformation* iPosMatrix = 0);

/**
 * Returns an AABB of the CATIPolyCurve instance.
 * @param iPolyCurve
 *   The input curve.
 * @param ioAABB
 *   The AABB that will be set by a successful call.
 * @param iPosMatrix
 *   An optional transformation defining the position of the surface.
 * @return
 *   S_OK for a successful call
 *   S_FALSE if the AABB has not been set.
 *   E_FAIL if an error occurs during the computation.
 */
ExportedByPolyhedralUtilities HRESULT CATPolyGetAABB (const CATIPolyCurve& iPolyCurve,
  CATPolyAABB& ioAABB,
  const CATMathTransformation* iPosMatrix = 0);

/**
 * Returns an OBB of the CATIPolyCurve instance.
 * @param iPolyCurve
 *   The input curve.
 * @param ioBB
 *   The OBB that will be set by a successful call.
 * @param iPosMatrix
 *   An optional transformation defining the position of the surface.
 * @return
 *   S_OK for a successful call
 *   S_FALSE if the OBB has not been set.
 *   E_FAIL if an error occurs during the computation.
 */
ExportedByPolyhedralUtilities HRESULT CATPolyGetOBB (const CATIPolyCurve& iPolyCurve,
  CATPolyOBB& ioOBB,
  const CATMathTransformation* iPosMatrix = 0);

/**
 * Returns an AABB and an OBB of the CATIPolyCurve instance.
 * @param iPolyCurve
 *   The input curve.
 * @param ioAABB
 *   The AABB that will be set by a successful call.
 * @param ioBB
 *   The OBB that will be set by a successful call.
 * @param iPosMatrix
 *   An optional transformation defining the position of the surface.
 * @return
 *   S_OK for a successful call
 *   S_FALSE if the AABB and OBB have not been set.
 *   E_FAIL if an error occurs during the computation.
 */
ExportedByPolyhedralUtilities HRESULT CATPolyGetAABBAndOBB (const CATIPolyCurve& iPolyCurve,
  CATPolyAABB& ioAABB, CATPolyOBB& ioOBB,
  const CATMathTransformation* iPosMatrix = 0);

/** @} */


/** @name Miscellaneous Services
    @{ */

    /**
     * Retrieves the CGM ID of a CATIPolyCurve.
     * @param iPolyCurve
     *   The input curve.
     * @param oID
     *   The returned ID of the curve.
     * @return
     * <ul>
     *   <li> <tt>S_OK</tt> if the ID is set,
     *   <li> <tt>S_FALSE</tt> if the curve does not have an ID, or
     *   <li> <tt>E_FAIL</tt> or another error code if an error occurs.
     * </ul>
     */
ExportedByPolyhedralUtilities HRESULT CATPolyGetID (const CATIPolyCurve& iPolyCurve, unsigned int& oID);

/**
 * Returns the size in bytes of the CATIPolyCurve and its layers.
 * The size of the dependent objects is not included.
 * @param iPolyCurve
 *   The input curve.
 */
ExportedByPolyhedralUtilities unsigned int CATPolySizeOf (const CATIPolyCurve& iPolyCurve);

/**
 * Returns <tt>TRUE</tt> if the CATIPolyCurve shares its data with another CATIPolyCurve.
 * @param iPolyCurve1
 *   The first CATIPolyCurve.
 * @param iPolyCurve2
 *   The second CATIPolyCurve.
 */
ExportedByPolyhedralUtilities CATBoolean CATPolyShareDataWith (const CATIPolyCurve& iPolyCurve1, const CATIPolyCurve& iPolyCurve2);

/** @} */


/** @name Vertex Layer Services
    @{ */

    /**
     * Returns the vertex position layer if one is available in floating-point precision.
     * @param iPolyCurve
     *   The input curve.
     * @param oLayer
     *   The returned layer.  The returned layer must be released (ref-counted.)
     * @return
     * <ul>
     *   <li> <tt>S_OK</tt> if a layer is successfully returned.
     *   <li> <tt>S_FALSE</tt> if a layer is not available.
     *   <li> <tt>E_FAIL</tt> if an error occurs.
     * </ul>
     */
ExportedByPolyhedralUtilities HRESULT CATPolyGetVertexPositionLayer (const CATIPolyCurve& iPolyCurve, CATIPolyVertexFloatPositionConstLayer*& oLayer);

/** @} */


/** @name Services for curves that are dynamically refinable.
    @{ */

    /**
     * @nodoc
     */
ExportedByPolyhedralUtilities HRESULT CATPolyGetBaseCurve (const CATIPolyCurve& iPolyCurve, CATIPolyCurve*& oBaseCurve);

/** @} */

#endif // !CATPolyCurveServices_H
