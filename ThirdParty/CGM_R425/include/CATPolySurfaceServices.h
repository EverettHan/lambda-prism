// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolySurfaceServices.h
//
//===================================================================
// January 2011  Creation: NDO
//===================================================================
#ifndef CATPolySurfaceServices_H
#define CATPolySurfaceServices_H

#include "PolyhedralUtilities.h"
#include "CATErrorDef.h"
#include "CATPolyCurveList.h"
#include "CATBoolean.h"

/** @file 
 * Global services about CATIPolySurface.
 *
 * @see CATPolyServices.h
 * @see CATPolyCGMServices.h
*/

class CATIPolySurface;
class CATIPolyMesh;
class CATIPolySurfaceDisabler;
class CATIPolyMeshDisabler;
class CATIPolySurfaceIterator;
class CATIPolyVertexFloatPositionConstLayer;
class CATIPolyVertexFloatNormalConstLayer;
class CATIPolySurfaceVertexTextureCoordConstLayer;
class CATIPolySurfaceDataConstLayers;
class CATIPolySurfaceFacetIterator;

class CATPolyMathSurface;
class CATPolyMathSurfaceSupport;
class CATPolyBoundingSphere;
class CATPolyAABB;
class CATPolyOBB;
class CATPolyFace;

class CATMathTransformation;
class CATMathPoint;
class CATMathVector;
class CATMathBox;


namespace Poly
{
  /** @name CATIPolySurface Services: Queries
   *
   * CATPolySurfaceServices.h
   * @{ */

  /**
   * Returns true if the surface has a float vertex position layer.
   */
  ExportedByPolyhedralUtilities bool HasFloatVertexPositionLayer (const CATIPolySurface& S);

  /**
   * Returns true if the surface has a vertex normal layer.
   * @param oUniqueNormal
   *   An optional output argument set to true if the normal is unique for the whole surface.
   */
  ExportedByPolyhedralUtilities bool HasVertexNormalLayer (const CATIPolySurface& S, bool* oUniqueNormal = 0);

  /** @} */
};


/** @name Surface Supports
    @{ */

/**
 * Returns a CATPolyMathSurface that is associated to the support (either explicitely or implicitely).
 * @param iPolySurface
 *   The input surface.
 * @param oSurface
 *   The object returned must be released by the caller.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if a CATPolyMathSurface is returned.
 *   <li> <tt>S_FALSE</tt> if there is no CATPolyMathSurface.
 *   <li> <tt>E_FAIL</tt> or another error code if an error occurs.
 * </ul>
 */
ExportedByPolyhedralUtilities HRESULT CATPolyGetMathSurface (const CATIPolySurface& iPolySurface, CATPolyMathSurface*& oSurface);


/**
 * Returns a support of the CATIPolySurface defined as a CATPolyMathSurfaceSupport.
 * If the support is natively a CATPolyMathSurfaceSupport, then the method just returns this support.
 * For any other support, the method converts it to a CATPolyMathSurfaceSupport.
 * The returned support must be released by the caller.
 * @param iPolySurface
 *   The input surface.
 * @param oMathSurfaceSupport
 *   The math surface support.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if a CATPolyMathSurfaceSupport is returned.
 *   <li> <tt>S_FALSE</tt> if the support cannot be converted to a CATPolyMathSurfaceSupport.
 *   <li> <tt>E_FAIL</tt> or another error code if any error occurs.
 * </ul>
 */
ExportedByPolyhedralUtilities HRESULT CATPolyGetMathSurfaceSupport (const CATIPolySurface& iPolySurface, 
                                                                    CATPolyMathSurfaceSupport*& oMathSurfaceSupport);

/**
 * Queries if a CATIPolySurface has a planar support.
 * @param iPolySurface
 *   The input surface.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if the CATIPolySurface is planar.
 *   <li> <tt>S_FALSE</tt> if the CATIPolySurface is not planar.
 *   <li> <tt>E_FAIL</tt> or any other error code if an error occurs.
 * </ul>
 */
ExportedByPolyhedralUtilities HRESULT CATPolyIsPlanar (const CATIPolySurface& iPolySurface);

/** @} */


/** @name Bounding Volumes
    @{ */

namespace Poly
{

  /**
   * Computes the bounding box of a CATIPolySurface instance.
   * @param iPolySurface
   *   The input CATIPolySurface.
   * @param ioBox
   *   The computed bounding box.
   * @param iPosMatrix
   *   An optional transformation applied to the points.
   * @return
   *   S_OK for a successful call
   *   S_FALSE if the bounding box has not been computed.
   *   E_FAIL if an error occurs during the computation.
   */
  ExportedByPolyhedralUtilities HRESULT ComputeBoundingBox (const CATIPolySurface& iPolySurface,
    CATMathBox& ioBox,
    const CATMathTransformation* iPosMatrix = 0);

}

/**
 * Returns a bounding sphere of the CATIPolySurface instance.
 * @param iPolySurface
 *   The input surface.
 * @param ioBoundingSphere
 *   The bounding sphere that will be set by a successful call.
 * @param iPosMatrix
 *   An optional transformation defining the position of the surface.
 * @return
 *   S_OK for a successful call
 *   S_FALSE if the bounding sphere has not been set.
 *   E_FAIL if an error occurs during the computation.
 */
ExportedByPolyhedralUtilities HRESULT CATPolyGetBoundingSphere (const CATIPolySurface& iPolySurface,
                                                                CATPolyBoundingSphere& ioBoundingSphere,
                                                                const CATMathTransformation* iPosMatrix = 0);

/**
 * Returns an AABB of the CATIPolySurface instance.
 * @param iPolySurface
 *   The input surface.
 * @param ioAABB
 *   The AABB that will be set by a successful call.
 * @param iPosMatrix
 *   An optional transformation defining the position of the surface.
 * @return
 *   S_OK for a successful call
 *   S_FALSE if the AABB has not been set.
 *   E_FAIL if an error occurs during the computation.
 */
ExportedByPolyhedralUtilities HRESULT CATPolyGetAABB (const CATIPolySurface& iPolySurface,
                                                      CATPolyAABB& ioAABB,
                                                      const CATMathTransformation* iPosMatrix = 0);

/**
 * Returns an OBB of the CATIPolySurface instance.
 * @param iPolySurface
 *   The input surface.
 * @param ioBB
 *   The OBB that will be set by a successful call.
 * @param iPosMatrix
 *   An optional transformation defining the position of the surface.
 * @return
 *   S_OK for a successful call
 *   S_FALSE if the OBB has not been set.
 *   E_FAIL if an error occurs during the computation.
 */
ExportedByPolyhedralUtilities HRESULT CATPolyGetOBB (const CATIPolySurface& iPolySurface,
                                                     CATPolyOBB& ioOBB,
                                                     const CATMathTransformation* iPosMatrix = 0);

/**
 * Returns an AABB and an OBB of the CATIPolySurface instance.
 * @param iPolySurface
 *   The input surface.
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
ExportedByPolyhedralUtilities HRESULT CATPolyGetAABBAndOBB (const CATIPolySurface& iPolySurface,
                                                            CATPolyAABB& ioAABB, CATPolyOBB& ioOBB,
                                                            const CATMathTransformation* iPosMatrix = 0);

/** @} */


/** @name Miscellaneous Services
    @{ */

/**
 * Fetches the coordinates of one vertex belonging to the surface.
 * @param[out] oPoint
 *   Coordinates of a vertex belonging to the surface.
 * @return 
 * <ul>
 *   <li> <tt>S_OK</tt> if the vertex coordinates has been successfully set.
 *   <li> <tt>S_FALSE</tt> If the surface doesn't contain any points.
 *   <li> <tt>E_INVALIDARG</tt> If the surface type is not supported, E_FAIL if something really serious happened..
 * </ul>
 */
ExportedByPolyhedralUtilities HRESULT CATPolyGetPointOnSurface (const CATIPolySurface& iPolySurface, CATMathPoint& oPoint);

/**
 * Retrieves the CGM ID of a CATIPolySurface.
 * @param iPolySurface
 *   The input surface.
 * @param oID
 *   The returned ID of the surface.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if the ID is set,
 *   <li> <tt>S_FALSE</tt> if the surface does not have an ID, or
 *   <li> <tt>E_FAIL</tt> or another error code if an error occurs.
 * </ul>
 */
ExportedByPolyhedralUtilities HRESULT CATPolyGetID (const CATIPolySurface& iPolySurface, unsigned int& oID);


/**
 * Returns <tt>TRUE</tt> if the CATIPolySurface shares its data with another CATIPolySurface.
 * @param iPolySurface1
 *   The first CATIPolySurface.
 * @param iPolySurface2
 *   The second CATIPolySurface.
 */
ExportedByPolyhedralUtilities CATBoolean CATPolyShareDataWith (const CATIPolySurface& iPolySurface1, const CATIPolySurface& iPolySurface2);

/**
 * Retrieves the vertex range of a CATIPolySurface.
 * @param iPolySurface
 *   The input surface.
 * @param oMinimum
 *   The output minimum index of a vertex.
 * @param oMaximum
 *   The output maximum index of a vertex.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if the vertex range is set.
 *   <li> <tt>S_FALSE</tt> if there is no vertex range (surface without any vertex.)
 *   <li> <tt>E_FAIL</tt> or another error code if an error occurs.
 * </ul>
 */
ExportedByPolyhedralUtilities HRESULT CATPolyGetVertexRange (const CATIPolySurface& iPolySurface, int& oMinimum, int& oMaximum);

/**
 * Returns
 * <ul>
 *   <li> <tt>S_OK</tt> if the CATIPolySurface has compact vertex range (with the first vertex index equal to 1).
 *                       The method also returns <tt>S_OK</tt> if the surface has not vertex.
 *   <li> <tt>S_FALSE</tt> otherwise.
 * </ul>
 */
ExportedByPolyhedralUtilities HRESULT CATPolyHasCompactVertexRange (const CATIPolySurface& iPolySurface);

/**
 * Retrieves the facet range of a CATIPolySurface.
 * @param iPolySurface
 *   The input surface.
 * @param oMinimum
 *   The output minimum index of a facet.
 * @param oMaximum
 *   The output maximum index of a facet.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if the facet range is set.
 *   <li> <tt>S_FALSE</tt> if there is no facet range (surface without any facet.)
 *   <li> <tt>E_FAIL</tt> or another error code if an error occurs.
 * </ul>
 */
ExportedByPolyhedralUtilities HRESULT CATPolyGetFacetRange (const CATIPolySurface& iPolySurface, int& oMinimum, int& oMaximum);

/**
 * Returns
 * <ul>
 *   <li> <tt>S_OK</tt> if the CATIPolySurface has compact facet range (with the first facet index equal to 1);
 *                       The method also returns <tt>S_OK</tt> if the surface has not facet.
 *   <li> <tt>S_FALSE</tt> otherwise.
 * </ul>
 */
ExportedByPolyhedralUtilities HRESULT CATPolyHasCompactFacetRange (const CATIPolySurface& iPolySurface);

/**
 * Returns the size in bytes of the CATIPolySurface and its layers.
 * The size of the objects it depends on is not included.
 * @param iPolySurface
 *   The input surface.
 */
ExportedByPolyhedralUtilities unsigned int CATPolySizeOf (const CATIPolySurface& iPolySurface);

/** @} */


/** @name Vertex Layer Services
    @{ */

/**
 * Returns the vertex position layer if one is available in floating-point precision. 
 * @param iPolySurface
 *   The input surface.
 * @param oLayer
 *   The returned layer.  The returned layer must be released (ref-counted.)
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if a layer is successfully returned.
 *   <li> <tt>S_FALSE</tt> if a layer is not available.
 *   <li> <tt>E_FAIL</tt> if an error occurs.
 * </ul>
 */
ExportedByPolyhedralUtilities HRESULT CATPolyGetVertexPositionLayer (const CATIPolySurface& iPolySurface, CATIPolyVertexFloatPositionConstLayer*& oLayer);


/**
 * Returns the normal position layer if one is available in floating point precision. 
 * @param iPolySurface
 *   The input surface.
 * @param oLayer
 *   The layer that is returned.  The returned layer must be released (ref-counted.)
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if a layer is successfully returned.
 *   <li> <tt>S_FALSE</tt> if a layer is not available.
 *   <li> <tt>E_FAIL</tt> if an error occurs.
 * </ul>
 */
ExportedByPolyhedralUtilities HRESULT CATPolyGetVertexNormalLayer (const CATIPolySurface& iPolySurface, CATIPolyVertexFloatNormalConstLayer*& oLayer);

/**
 * Adds a Normal layer to an editable mesh.
 * @param iPolySurface
 *   The input CATIPolySurface.
 * @return
 *   <ul>
 *     <li> <tt>S_OK</tt> The layer successfully added.
 *     <li> <tt>S_FALSE</tt> The layer already existed.
 *     <li> <tt>E_FAIL</tt> The input poly surface is not editable.
 *     <li> <tt>E_OUTOFMEMORY</tt> The world is on the verge of apocalypse.
 *   </ul>
 */
ExportedByPolyhedralUtilities HRESULT CATPolyAddVertexNormalLayer (CATIPolySurface& iPolySurface);

/** @} */


/** @name CATPolyBody Services
    @{ */

/**
 * Returns the parent CATPolyFace if this CATIPolySurface belongs to a CATPolyBody.
 * @param iPolySurface
 *   The input surface.
 * @param oPolyFace
 *   The output face to which the CATIPolySurface is attached.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if a CATPolyFace is successfully returned.
 *   <li> <tt>S_FALSE</tt> if the CATIPolySurface is not attached to any CATPolyFace.
 *   <li> <tt>E_FAIL</tt> if an error occurs.
 * </ul>
 */
ExportedByPolyhedralUtilities HRESULT CATPolyGetPolyFace (const CATIPolySurface& iPolySurface, const CATPolyFace*& oPolyFace);

/** @} */


/** @name Reserved Services (for surfaces that are dynamically refinable)
    @{ */

/**
 * @nodoc
 */
ExportedByPolyhedralUtilities HRESULT CATPolyGetBaseSurfaceAndCurves (const CATIPolySurface& iPolySurface, CATIPolySurface*& oBaseSurface, CATPolyCurveList* ioBaseCurves = 0);

/**
 * Returns the status of the CATIPolySurface data.
 * If the data of the CATIPolySurface are readily available in memory for usage
 * the method returns <tt>S_FALSE</tt>. Otherwise, the method returns <tt>S_OK</tt>
 * and push the facet data to the refinement engine (for example GPGPU engine) for later use.
 * When finished working with the data or to cancel a request made, a call to 
 * ReleaseSurface () must be made.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> If the surface could be pushed to the refinement engine.
 *   <li> <tt>S_FALSE</tt> If the facet data are readily available.
 *   <li> <tt>E_FAIL</tt> If an error occurs.
 * </ul>
 */
ExportedByPolyhedralUtilities HRESULT CATPolyPushSurfaceForRefinement (const CATIPolySurface& iPolySurface);

/**
 * Releases the facet data after a call to PushSurfaceForRefinement () has been made.
 * This informs the CATIPolySurface that its facet data no longer need to stay in memory.
 */
ExportedByPolyhedralUtilities HRESULT CATPolyReleaseSurfaceFromRefinementEngine (const CATIPolySurface& iPolySurface);

/** @} */


/** @name Reserved Services (others)
    @{ */

/**
 * @nodoc
 */
ExportedByPolyhedralUtilities HRESULT CATPolyCompressMesh (const CATIPolySurface& iPolySurface, void *& oCompressedForm);

/** @} */


namespace Poly
{

  /** @name Layer Services: CATIPolySurface
   *
   * CATPolySurfaceServices.h
   * @{ */

  /**
   * Returns an instance of CATIPolySurfaceDisabler constructed from the data layers associated to
   * a CATIPolySurface.  When a layer does not support a specific surface editing operation, then
   * a call made to the disabler returns true.  The operation should not be performed on the
   * CATIPolySurface otherwise data layers may become invalid.
   * @param iPolySurface
   *   The input CATIPolySurface.
   * @param oDisabler
   *   The disabler that makes the editing query to all disablers from the data layers (when available.)
   *   This output instance should be deleted.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if a disabler is returned.
   *   <li> <tt>S_FALSE</tt> if no disabler is available.
   * </ul>
  */
  ExportedByPolyhedralUtilities HRESULT GetDisablerFromDataLayers (const CATIPolySurface& iPolySurface, CATIPolySurfaceDisabler*& oDisabler);

  /** @} */

};


#ifndef DOXYGEN_SHOULD_SKIP_THIS

/**
* @nodoc
*/
ExportedByPolyhedralUtilities HRESULT CATPolyOBBSplit (const CATIPolySurface& iPolySurface,
                                                       const CATPolyOBB & iSurfaceOBB, int iMinNbTriangles,
                                                       CATIPolySurfaceIterator *& oSplittedSurfaces);

#endif

#endif // !CATPolySurfaceServices_H
