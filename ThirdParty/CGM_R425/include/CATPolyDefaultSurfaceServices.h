// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyDefaultSurfaceServices.h
//
//===================================================================
// July 2011  Creation: NDO
//===================================================================
#pragma once

#include "PolyMeshImpl.h"
#include "CATErrorDef.h"

#include "CATPolySurfaceObserverList.h"
#include "Poly/Precision.h"

/** @file
 * Default services that can be applied to CATIPolySurface.
 * These services are implemented in PolyhedralObjects.
 *
 * @see CATPolyServices.h
*/

class CATPolyFace;
class CATIPolySurface;
class CATIPolyMesh;
class CATIPolySurfaceObserver;
class CATIPolyLayer;
class CATIPolySurfaceVertexPositionLayer;
class CATIPolySurfaceVertexTextureCoordLayer;
class CATPolySurfaceVertexTexCoordFloat1DLayer;
class CATPolySurfaceVertexTexCoordFloat2DLayer;
class CATIPolyTextureVertexCoords2DLayer;
class CATIPolySurfaceVertexNormalLayer;
class CATIPolySurfaceVertexUVLayer;
class CATIPolySurfaceVertexFloatsLayer;
class CATIPolySurfaceVertexDoublesLayer;
class CATIPolySurfaceVertexCellConstLayer;

class CATMathBox;
class CATPolyBoundingSphere;
class CATPolyAABB;
class CATPolyOBB;
class CATMathTransformation;


namespace Poly
{

  /** @name Creation of specific layers for CATIPolySurface objects
   *
   * CATPolyDefaultSurfaceServices.h
   * @{ */

  // CATIPolySurfaceVertexTextureCoordConstLayer::ClassID ()
  ExportedByPolyMeshImpl HRESULT AddNewLayer (CATIPolySurface& S, const CATUnicodeString& iIdentifier,
    unsigned int dim,
    CATIPolySurfaceVertexTextureCoordLayer*& oLayer);

  // CATPolySurfaceVertexTexCoordFloat1DLayer::ClassID ()
  ExportedByPolyMeshImpl HRESULT AddNewLayer (CATIPolySurface& S, const CATUnicodeString& iIdentifier,
    CATPolySurfaceVertexTexCoordFloat1DLayer*& oLayer);

  // CATPolySurfaceVertexTexCoordFloat2DLayer::ClassID ()
  ExportedByPolyMeshImpl HRESULT AddNewLayer (CATIPolySurface& S, const CATUnicodeString& iIdentifier,
    CATPolySurfaceVertexTexCoordFloat2DLayer*& oLayer);

  /**
   * Creates and adds a new texture-vertex layer instance to a CATIPolySurface.
   * Addition of the new layer to the CATIPolySurface will also register the layer-observer with the CATIPolySurface.
   * @param M
   *   The input CATIPolyMesh for which the new layer is created.
   * @param iIdentifier
   *   A string identifying the layer.
   * @param dim
   *   The dimension of the texture layer.
   * @param oLayer
   *   The layer that was added to the CATIPolySurface.
   *   The returned instance must be released (ref-counted.)
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if a layer is successfully added to the CATIPolySurface.
   *   <li> <tt>S_FALSE</tt> if the requested layer cannot be added to the CATIPolySurface.
   *   <li> <tt>E_FAIL</tt> if an error occurs.
   * </ul>
  */
  // CATIPolyTextureVertexCoords2DLayer::ClassID ()
  ExportedByPolyMeshImpl HRESULT AddNewLayer (CATIPolyMesh& M, const CATUnicodeString& iIdentifier,
    unsigned int dim,
    CATIPolyTextureVertexCoords2DLayer*& oLayer);

  /**
   * Creates and adds a new vertex uv-layer instance to a CATIPolySurface.
   * Addition of the new layer to the CATIPolySurface will also register the layer-observer with the CATIPolySurface.
   * @param S
   *   The input CATIPolySurface for which the new layer is created.
   * @param oLayer
   *   The layer that was added to the CATIPolySurface.
   *   The returned instance must be released (ref-counted.)
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if a layer is successfully added to the CATIPolySurface.
   *   <li> <tt>S_FALSE</tt> if the requested layer cannot be added to the CATIPolySurface.
   *   <li> <tt>E_FAIL</tt> if an error occurs.
   * </ul>
   */
  // CATIPolySurfaceVertexUVConstLayer::ClassID ()
  ExportedByPolyMeshImpl HRESULT AddNewLayer (CATIPolySurface& S, CATIPolySurfaceVertexUVLayer*& oLayer);

   /**
    * Creates and adds a new layer instance to a CATIPolySurface.
    * Addition of the new layer to the CATIPolySurface will also register the layer-observer with the CATIPolySurface.
    * @param S
    *   The input CATIPolySurface for which the new layer is created.
    * @param iIdentifier
    *   The string identifier of the layer.
    * @param oLayer
    *   The layer that was added to the CATIPolySurface.
    *   The returned instance must be released (ref-counted.)
    * @return
    * <ul>
    *   <li> <tt>S_OK</tt> if a layer is successfully added to the CATIPolySurface.
    *   <li> <tt>S_FALSE</tt> if the requested layer cannot be added to the CATIPolySurface.
    *   <li> <tt>E_FAIL</tt> if an error occurs.
    * </ul>
    */
   // CATIPolySurfaceVertexPositionConstLayer::ClassID ()
  ExportedByPolyMeshImpl HRESULT AddNewLayer (CATIPolySurface& S, const CATUnicodeString& iIdentifier,
    PolyPrecision iPrecision,
    CATIPolySurfaceVertexPositionLayer*& oLayer);

  /**
   * Creates and adds a new vertex normal-layer instance to a CATIPolySurface.
   * Addition of the new layer to the CATIPolySurface will also register the layer-observer with the CATIPolySurface.
   * 
   * NOTE: Currently, only one vertex normal-layer can be added to a CATIPolySurface.
   * If a surface vertex-normal layer already exists for this CATIPolySurface, no new layer is added.
   * In this case, the method returns S_FALSE and a null layer (no new layer added.)
   * 
   * @param S
   *   The input CATIPolySurface for which the new layer is created.
   * @param id
   *   The class id of the layer to add to the surface.
   * @param oLayer
   *   The layer that was added to the CATIPolySurface.
   *   The returned instance must be released (ref-counted.)
   * @param iUniqueNormal
   *   An optional flag to specify that the normals in the layer will be the same for all vertices.
   *   The implementation may be optimized when this flag is set to true.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if a layer is successfully added to the CATIPolySurface.
   *   <li> <tt>S_FALSE</tt> if the requested layer cannot be added to the CATIPolySurface.
   *   <li> <tt>E_FAIL</tt> if an error occurs.
   * </ul>
  */
  ExportedByPolyMeshImpl HRESULT AddNewLayer (CATIPolySurface& S, CATIPolySurfaceVertexNormalLayer*& oLayer,
    bool uniqueNormal = false);

  /**
   * Creates and adds a new layer instance to a CATIPolySurface.
   * Addition of the new layer to the CATIPolySurface will also register the layer-observer with the CATIPolySurface.
   * @param S
   *   The input CATIPolySurface for which the new layer is created.
   * @param id
   *   The class id of the layer to add to the surface.
   * @param oLayer
   *   The layer that was added to the CATIPolySurface.
   *   The returned instance must be released (ref-counted.)
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if a layer is successfully added to the CATIPolySurface.
   *   <li> <tt>S_FALSE</tt> if the requested layer cannot be added to the CATIPolySurface.
   *   <li> <tt>E_FAIL</tt> if an error occurs.
   * </ul>
   */

   // CATIPolySurfaceVertexFloatsLayer::ClassID ()
  ExportedByPolyMeshImpl HRESULT AddNewLayer (CATIPolySurface& S, const CATUnicodeString& iIdentifier, unsigned int dim,
    CATIPolySurfaceVertexFloatsLayer*& oLayer);

  // CATIPolySurfaceVertexDoublesLayer::ClassID ()
  ExportedByPolyMeshImpl HRESULT AddNewLayer (CATIPolySurface& S, const CATUnicodeString& iIdentifier, unsigned int dim,
    CATIPolySurfaceVertexDoublesLayer*& oLayer);

  ExportedByPolyMeshImpl bool HasPersistencyInformation (const CATIPolySurface& ioSurface);
  ExportedByPolyMeshImpl HRESULT SetPersistencyInformation (CATIPolySurface& ioSurface);
  ExportedByPolyMeshImpl HRESULT UnsetPersistencyInformation (CATIPolySurface& ioSurface);

  /** @} */

  /**
   * Finds a layer instance matching the input parameters from a CATIPolySurface.
   * @param S
   *   The input CATIPolySurface.
   * @param iIdentifier
   *   The identifier of the layer.
   * @param iPrecision
   *   The precision of the layer.
   * @param oLayer
   *   The layer found from the CATIPolySurface.
   *   The returned instance must be released (ref-counted.)
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if a layer is found.
   *   <li> <tt>S_FALSE</tt> if no layer is found.
   *   <li> <tt>E_FAIL</tt> if an error occurs.
   * </ul>
   */
   //ExportedByPolyMeshImpl HRESULT FindLayer (CATIPolySurface& S, const CATUnicodeString& iIdentifier,
     //Poly::Precision iPrecision,
     //CATIPolySurfaceVertexPositionLayer*& oLayer);
};


/**
 * Retrieves the vertex range of a CATIPolySurface.
 * (Default implementation.)
 * @param iPolySurface
 *   The input surface.
 * @param oMinimum
 *   The output minimum index of a vertex.
 * @param oMaximum
 *   The output maximum index of a vertex.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if the vertex range is set.
 *   <li> <tt>S_FALSE</tt> if there is no vertex range (surface without vertex.)
 *   <li> <tt>E_FAIL</tt> or another error code if an error occurs.
 * </ul>
 */
ExportedByPolyMeshImpl HRESULT CATPolyDefaultGetVertexRange (const CATIPolySurface& iPolySurface, int& oMinimum, int& oMaximum);

/**
 * Computes the bounding box of a CATIPolySurface.
 * @param iPosMatrix
 *   An optional transformation to apply to the vertex positions.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if the bounding box is successfully computed.
 *   <li> <tt>S_FALSE</tt> if the bounding box is not computed.
 *   <li> <tt>E_FAIL</tt> if an error occurs.
 * </ul>
 */
ExportedByPolyMeshImpl HRESULT CATPolyDefaultComputeBoundingBox (const CATIPolySurface& iPolySurface, CATMathBox& ioBBox,
  const CATMathTransformation* iPosMatrix);

/**
 * Computes the bounding sphere of a CATIPolySurface.
 * @param iPosMatrix
 *   An optional transformation to apply to the vertex positions.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if the bounding volume is successfully computed.
 *   <li> <tt>S_FALSE</tt> if the bounding volume is not computed.
 *   <li> <tt>E_FAIL</tt> if an error occurs.
 * </ul>
 */
ExportedByPolyMeshImpl HRESULT CATPolyDefaultComputeBoundingSphere (const CATIPolySurface& iPolySurface, CATPolyBoundingSphere& ioBoundingSphere,
  const CATMathTransformation* iPosMatrix);

/**
 * Computes the AABB of a CATIPolySurface.
 * @param iPosMatrix
 *   An optional transformation to apply to the vertex positions.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if the bounding volume is successfully computed.
 *   <li> <tt>S_FALSE</tt> if the bounding volume is not computed.
 *   <li> <tt>E_FAIL</tt> if an error occurs.
 * </ul>
 */
ExportedByPolyMeshImpl HRESULT CATPolyDefaultComputeAABB (const CATIPolySurface& iPolySurface, CATPolyAABB& ioAABB,
  const CATMathTransformation* iPosMatrix);

/**
 * Computes the OBB of a CATIPolySurface.
 * @param iPosMatrix
 *   An optional transformation to apply to the vertex positions.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if the bounding volume is successfully computed.
 *   <li> <tt>S_FALSE</tt> if the bounding volume is not computed.
 *   <li> <tt>E_FAIL</tt> if an error occurs.
 * </ul>
 */
ExportedByPolyMeshImpl HRESULT CATPolyDefaultComputeOBB (const CATIPolySurface& iPolySurface, CATPolyOBB& ioOBB,
  const CATMathTransformation* iPosMatrix);

/**
 * Computes the AABB and OBB of a CATIPolySurface.
 * @param iPosMatrix
 *   An optional transformation to apply to the vertex positions.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if the bounding volume is successfully computed.
 *   <li> <tt>S_FALSE</tt> if the bounding volume is not computed.
 *   <li> <tt>E_FAIL</tt> if an error occurs.
 * </ul>
 */
ExportedByPolyMeshImpl HRESULT CATPolyDefaultComputeAABBAndOBB (const CATIPolySurface& iPolySurface, CATPolyAABB& ioAABB, CATPolyOBB& ioOBB,
  const CATMathTransformation* iPosMatrix);

/**
 * Returns the CATPolyFace to which an observer may be associated.
 * @param iObserver
 *   An input CATIPolySurfaceObserver.
 * @return
 *   A pointer to an output CATPolyFace.
 */
ExportedByPolyMeshImpl CATPolyFace* CATPolyDefaultGetPolyFace (CATIPolySurfaceObserver& iObserver);

/**
 * Returns a CATPolyFace to which an observer from the input list is associated.
 * If there are several observers in the list referring to a CATPolyFace, then the
 * method returns the CATPolyFace from the first observer.
 * @param iPolySurfaceObservers
 *   An input observer list from a CATIPolySurface instance.
 * @return
 *   The output CATPolyFace from one of the observers.
 */
ExportedByPolyMeshImpl CATPolyFace* CATPolyDefaultGetPolyFace (const CATPolySurfaceObserverList& iPolySurfaceObservers);

/**
 * DO NOT USE.
 * Reserved service to get rid of once migration of
 * CATIPolySurface::GetVertexCellLayer to CATPolyFace::GetSurfaceVertexCellLayer is completed.
 * @see CATPolyFace
 * @return
 *  Do not release returned pointer.
 */
ExportedByPolyMeshImpl CATIPolySurfaceVertexCellConstLayer* CATPolyReservedGetVertexCellConstLayer (CATIPolySurfaceObserver& iObserver);

/**
 * DO NOT USE.
 * Reserved service to get rid of once migration of
 * CATIPolySurface::GetVertexCellLayer to CATPolyFace::GetSurfaceVertexCellLayer is completed.
 * @see CATPolyFace
 *
 * Returns a surface-vertex cell layer obtained from the input observer.
 * @param iObserver
 *   An input observer.
 * @param oLayer [out, IUnknown#Release]
 *   The output CATIPolySurfaceVertexCellConstLayer.  The instance must be released.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if a layer is returned.
 *   <li> <tt>S_FALSE</tt> if no layer is returned.
 *   <li> <tt>E_FAIL</tt> if an error occurs.
 * </ul>
 */
ExportedByPolyMeshImpl HRESULT CATPolyReservedGetVertexCellLayer (CATIPolySurfaceObserver& iObserver,
  CATIPolySurfaceVertexCellConstLayer*& oLayer);

/**
 * DO NOT USE.
 * Reserved service to get rid of once migration of
 * CATIPolySurface::GetVertexCellLayer to CATPolyFace::GetSurfaceVertexCellLayer is completed.
 * @see CATPolyFace
 *
 * Returns the first surface-vertex cell layer obtained from an observer in the list.
 * @param iPolySurfaceObservers
 *   An input observer list from a CATIPolySurface instance.
 * @param oLayer [out, IUnknown#Release]
 *   The output CATIPolySurfaceVertexCellConstLayer.  The instance must be released.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if a layer is returned.
 *   <li> <tt>S_FALSE</tt> if no layer is returned.
 *   <li> <tt>E_FAIL</tt> if an error occurs.
 * </ul>
 */
ExportedByPolyMeshImpl HRESULT CATPolyReservedGetVertexCellLayer (const CATPolySurfaceObserverList& iPolySurfaceObservers,
  CATIPolySurfaceVertexCellConstLayer*& oLayer);
