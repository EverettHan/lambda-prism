// COPYRIGHT DASSAULT SYSTEMES 2009, ALL RIGHTS RESERVED.
//===================================================================
//
// CATIPolySurfaceConstTools.h
//
//===================================================================
//
// October 2009  Creation: NDO
//===================================================================
#ifndef CATIPolySurfaceConstTools_H
#define CATIPolySurfaceConstTools_H

#include "PolyhedralModel.h"
#include "CATErrorDef.h" 
#include "CATBoolean.h"
#include "CATPolyCurveList.h"

class CATIPolySurface;
class CATPolyMathSurface;
class CATPolyMathSurfaceSupport;
class CATPolyBoundingSphere;
class CATPolyAABB;
class CATPolyOBB;
class CATMathTransformation;
class CATIPolySurfaceIterator;
class CATIPolyVertexFloatPositionConstLayer;
class CATIPolyVertexFloatNormalConstLayer;
class CATIPolySurfaceFacetIterator;
class CATIPolySurfaceVertexCellConstLayer;
class CATPolyFace;

class CATMathPoint;
class CATMathVector;


/**
 * The use of polyhedral tools (this class) is reserved exclusively to polyhedral frameworks.
 * Do not use anywhere else.
 * Use instead the global functions and services that are defined in CATPolyServices.h.
 * 
 * @see CATPolyServices.h
 */
class ExportedByPolyhedralModel CATIPolySurfaceConstTools
{

public:

  virtual ~CATIPolySurfaceConstTools () {}

public:

  //
  // GEOMETRY TOOLS - SURFACE SUPPORT
  //

  /**
   * Returns a CATPolyMathSurface that is associated to the support (either explicitely or implicitely).
   * @param oSurface
   *   The object returned must be released by the caller.
   * @return
   * <ul>
   *   <tt>S_OK</tt> if a CATPolyMathSurface is returned.
   *   <tt>S_FALSE</tt> if there is no CATPolyMathSurface available from this instance.
   *   <tt>E_FAIL</tt> or another error code if any error occurs.
   * </ul>
   */
  virtual HRESULT GetMathSurface (const CATIPolySurface& iPolySurface, CATPolyMathSurface*& oSurface) const = 0;

  /**
   * Returns a support of the CATIPolySurface defined as a CATPolyMathSurfaceSupport.
   * If the support is natively a CATPolyMathSurfaceSupport, then the method just returns this support.
   * For any other support, the method converts it to a CATPolyMathSurfaceSupport.
   * The returned support must be released by the caller.
   * @param oMathSurfaceSupport
   *   The math surface support.
   * @return
   * <ul>
   *   <tt>S_OK</tt> if a CATPolyMathSurfaceSupport is returned.
   *   <tt>S_FALSE</tt> if the support cannot be converted to a CATPolyMathSurfaceSupport.
   *   <tt>E_FAIL</tt> or another error code if any error occurs.
   * </ul>
   */
  virtual HRESULT GetMathSurfaceSupport (const CATIPolySurface& iPolySurface, CATPolyMathSurfaceSupport*& oMathSurfaceSupport) const = 0;

  /**
   * Returns <tt>S_OK</tt> is the surface is planar and <tt>S_FALSE</tt> if it is not.
   */
  virtual HRESULT IsPlanar (const CATIPolySurface& iPolySurface) const = 0;

public:

  //
  // GEOMETRY TOOLS - BOUNDING VOLUME TOOLS
  //

  /**
   * Returns a bounding sphere of the CATIPolySurface instance.
   * @param ioBoundingSphere
   *   The bounding sphere that will be set by a successful call.
   * @param iPosMatrix
   *   An optional transformation defining the position of the surface.
   * @return
   *   S_OK for a successful call
   *   S_FALSE if the bounding sphere has not been set.
   *   E_FAIL if an error occurs during the computation.
   */
  virtual HRESULT GetBoundingSphere (const CATIPolySurface& iPolySurface, CATPolyBoundingSphere& ioBoundingSphere,
                                     const CATMathTransformation* iPosMatrix = 0) const = 0;

  /**
   * Returns an AABB of the CATIPolySurface instance.
   * @param ioAABB
   *   The AABB that will be set by a successful call.
   * @param iPosMatrix
   *   An optional transformation defining the position of the surface.
   * @return
   *   S_OK for a successful call
   *   S_FALSE if the AABB has not been set.
   *   E_FAIL if an error occurs during the computation.
   */
  virtual HRESULT GetAABB (const CATIPolySurface& iPolySurface, CATPolyAABB& ioAABB,
                           const CATMathTransformation* iPosMatrix = 0) const = 0;

  /**
   * Returns an OBB of the CATIPolySurface instance.
   * @param ioBB
   *   The OBB that will be set by a successful call.
   * @param iPosMatrix
   *   An optional transformation defining the position of the surface.
   * @return
   *   S_OK for a successful call
   *   S_FALSE if the OBB has not been set.
   *   E_FAIL if an error occurs during the computation.
   */
  virtual HRESULT GetOBB (const CATIPolySurface& iPolySurface, CATPolyOBB& ioOBB,
                          const CATMathTransformation* iPosMatrix = 0) const = 0;

  /**
   * Returns an AABB and an OBB of the CATIPolySurface instance.
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
  virtual HRESULT GetAABBAndOBB (const CATIPolySurface& iPolySurface, CATPolyAABB& ioAABB, CATPolyOBB& ioOBB,
                                 const CATMathTransformation* iPosMatrix = 0) const = 0;

  /**
   * Splits the surface into several sub surfaces. The created subSurfaces
   * define a partition of the splited surface. The decompostion requires
   * the OBB of the surface. If not already computed, you might use the above
   * GetOBB method.
   * @param iSurfaceOBB OBB of the surface. As usual the tighter the OBB, the better
   *                   the result.
   * @param iMinNbTriangles Number of triangles below which the surface shouldn't be splited.
   * @param oSplitSurfaces resulting subsurfaces, must be deleted afterwards.
   * @return S_OK if the split was successfull, E_INVALIDARG if the surface kind
   *         does not allow split, S_FALSE if the surface kind is OK but the algorithm
   *         did not manage to split it, E_FAIL if something wrong and unexpected happened.
   */
  virtual HRESULT OBBSplit (const CATIPolySurface& iPolySurface, const CATPolyOBB & iSurfaceOBB, int iMinNbTriangles,
                            CATIPolySurfaceIterator *& oSplitSurfaces) const = 0;

public:

  //
  // GEOMETRY TOOLS - OTHER TOOLS
  //

  /**
   * Fetches the coordinates of one vertex belonging to the surface.
   * @param[out] oCoords
   *   Coordinates of a vertex belonging to the surface.
   * @return 
   * <ul>
   *   <li> <tt>S_OK</tt> if the vertex coordinates has been successfully set.
   *   <li> <tt>S_FALSE</tt> If the surface doesn't contain any points.
   *   <li> <tt>E_INVALIDARG</tt> If the surface type is not supported, E_FAIL if something really serious happened..
   * </ul>
   */
  virtual HRESULT GetPointOnMesh (const CATIPolySurface& iPolySurface, CATMathPoint& oCoords) const = 0;

public:

  //
  // MISCELLANEOUS TOOLS
  //

  /**
   * Returns the ID or CGM ID associated to the surface if available.
   */
  virtual HRESULT GetID (const CATIPolySurface& iPolySurface, unsigned int& oID) const = 0;

  /**
   * Returns the size in bytes of the CATIPolySurface and its layers.
   * The size of the dependent objects is not included.
   */
  virtual unsigned int SizeOf (const CATIPolySurface& iPolySurface) const = 0;

  /**
   * Returns <tt>TRUE</tt> if the CATIPolySurface shares its data with another CATIPolySurface.
   */
  virtual CATBoolean ShareDataWith (const CATIPolySurface& iPolySurface, const CATIPolySurface& iWithPolySurface) const = 0;

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
  virtual HRESULT PushSurfaceForRefinement (const CATIPolySurface& iPolySurface) const = 0;

  /**
   * Releases the facet data after a call to PushSurfaceForRefinement () has been made.
   * This informs the CATIPolySurface that its facet data no longer need to stay in memory.
   */
  virtual HRESULT ReleaseSurfaceFromRefinementEngine (const CATIPolySurface& iPolySurface) const = 0;

  /**
   * Creates a compressed form of this surface.
   * @param oCompressedForm 
   *   Opaque pointer containing the compressed data (or set to NULL if something went wrong.)
   *   (Must be deleted.)
   * @return 
   * <ul>
   *   <li> <tt>S_OK</tt> if the surface has been successfully compressed, 
   *   <li> <tt>E_INVALIDARG</tt> if the surface type is not compressible, <tt>E_FAIL</tt> if something else went wrong.
   * </ul>
   */
  virtual HRESULT CompressMesh (const CATIPolySurface& iPolySurface, void *& oCompressedForm) const = 0;

public:

  //
  // VERTEX TOOLS
  //

  /**
   * Returns the range of the vertex indices.
   */
  virtual HRESULT GetVertexRange (const CATIPolySurface& iPolySurface, int& oMinimum, int& oMaximum) const = 0;

  virtual bool UseTriangleVertexRatherThanSurfaceVertexIterator () const { return false; }

  //
  // VERTEX LAYER TOOLS
  //

  /**
   * Returns the surface vertex position layer if available in float precision.
   * The returned layer must be released.
   */
  virtual HRESULT GetVertexPositionLayer (const CATIPolySurface& iPolySurface, CATIPolyVertexFloatPositionConstLayer*& oLayer) const = 0;

  /**
   * Returns the surface vertex normal layer if available in float precision.
   * The returned layer must be released.
   */
  virtual HRESULT GetVertexNormalLayer (const CATIPolySurface& iPolySurface, CATIPolyVertexFloatNormalConstLayer*& oLayer) const = 0;

public:

  //
  // FACET TOOLS
  //

  /**
   * Returns the range of the vertex indices.
   */
  virtual HRESULT GetFacetRange (const CATIPolySurface& iPolySurface, int& oMinimum, int& oMaximum) const = 0;

public:

  //
  // LINKS TO THE TOPOLOGY OF A PARENT BODY
  //

  /**
   * Makes a CATIPolySurfaceVertexCellConstLayer given CATIPolySurface and a CATPolyFace.
   * The cell layer may be cast as a CATIPolySurfaceVertexCellLayer if applicable for an editable CATIPolySurface.
   * @param iPolySurface
   *   The input CATIPolySurface.
   * @param iPolyFace
   *   The input CATPolyFace.
   * @return
   *   <ul>
   *     <li> <tt>S_OK</tt> A new surface vertex cell layer is returned.
   *     <li> <tt>S_FALSE</tt> No surface vertex cell layer is returned.
   *     <li> <tt>E_FAIL</tt> An error occured.
   *   </ul>
   * @see CATIPolySurfaceVertexCellLayer
   * @see CATIPolySurfaceVertexCellConstLayer
   */
  virtual HRESULT MakeVertexCellLayer (const CATIPolySurface& iPolySurface, CATPolyFace& iPolyFace,
                                       CATIPolySurfaceVertexCellConstLayer*& oCellLayer) const = 0;

/**
 * Returns the parent CATPolyFace if this CATIPolySurface belongs to a CATPolyBody.
 * @param oPolyFace
 *   The output face to which the CATIPolySurface is attached.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if a CATPolyFace is successfully returned.
 *   <li> <tt>S_FALSE</tt> if the CATIPolySurface is not attached to any CATPolyFace.
 *   <li> <tt>E_FAIL</tt> if an error occurs.
 * </ul>
 */
  virtual HRESULT GetPolyFace (const CATIPolySurface& iPolySurface, const CATPolyFace*& oPolyFace) const = 0;

public:

  //
  // TOOLS FOR SURFACES THAT ARE DYNAMICALLY REFINABLE
  // 

  /**
   * Returns the base surface and its bounding curves.
   * This method is for a refinement engine that can compute efficiently these data from the base surface and curves.
   * @param oBaseSurface
   *   The returned base surface (also called mesh 0).  The returned instance must be released.
   * @param ioBaseCurves
   *   If this pointer is different from 0, then the base curves bounding the base surface will be appended 
   *   to this list.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> If a base mesh and optionally curves are returned.
   *   <li> <tt>S_FALSE</tt> If there is no base mesh (and base curves) associated to this CATIPolySurface.
   *   <li> <tt>E_FAIL</tt> If an error occurs.
   *  </ul>
   */
  virtual HRESULT GetBaseSurfaceAndCurves (const CATIPolySurface& iPolySurface, CATIPolySurface*& oBaseSurface, CATPolyCurveList* ioBaseCurves = 0) const = 0;

protected:

  CATIPolySurfaceConstTools () {}

};

#endif // !CATIPolySurfaceConstTools_H
