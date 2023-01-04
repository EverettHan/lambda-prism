// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyServices.h
//
//===================================================================
// May  2011  Creation: NDO
// June 2014  Modification JXO: Geometric diagnosis
// March 2018 Modification JXO: SetPointType, SetWireType, SetSkinType, SetSolidType
//===================================================================
#pragma once

#include "PolyBodyTools.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"

#include "CATPolyStreamOptions.h"
#include "CATPolyDeprecated.h"
#include "CATMathStreamVersionDef.h"

#include "CATPolyMacroTopologyFwd.h"

class CATIPolyObject;
class CATIPolyPoint;
class CATIPolyCurve;
class CATIPolySurface;
class CATIPolySurfaceVertex;

class CATPolyStreamRecord;
class CATPolyUnstreamRecord;
class CATUnicodeString;
class CATMapOfPtrToInt;


/** @file 
 * Global services about CATPolyBody.
 *
 * @see CATPolyServices.h for services about CATIPolyPoint, CATIPolyCurve and CATIPolySurface.
 * @see CATPolyCGMServices.h for additional CGM services about CATIPolyPoint, CATIPolyCurve and CATIPolySurface.
 * @see CATPolyVisServices.h for additional visualization services.
 */

class CATPolyBodyDiagnosis;
class CATPolyBodyGeoDiagnosis;
class CATIPolyPrimitiveSupport;
class CATPolyBoundingSphere;

class CATMathBox;
class CATMathTransformation;
class CATTolerance;


namespace Poly
{
  /** @name Topology Services
   *
   * CATPolyBodyServices.h
   * @{ */

  /**
   * Returns the CATPolyEdge incident to a CATPolyVertex, CATPolyEdge and CATPolyFace.
   * There can be at most one incident CATPolyEdge.
   * @return
   *   The incident CATPolyEdge or 0 if there is none.
   */
  ExportedByPolyBodyTools CATPolyEdge* GetIncidentEdge (const CATPolyVertex* iVertex, const CATPolyEdge* iEdge, const CATPolyFace* iFace);

  /**
   * Returns the CATPolyFace incident to a a CATPolyEdge, CATPolyFace and CATPolyVolume.
   * There can be at most one incident CATPolyFace.
   * It returns null if the edge has no adjacent face.
   * @return
   *   The incident CATPolyFace or 0 if there is none.
   */
  ExportedByPolyBodyTools CATPolyFace* GetIncidentFace (const CATPolyEdge* iEdge, const CATPolyFace* iFace, const CATPolyVolume* iVolume);

  /**
   * Returns the adjacent face to a face across an edge.
   * Note that an edge can be incident to several faces.
   * The adjacent face may not be unique.
   * It returns null if the edge has no other incident face.
   * @return
   *   The adjacent face or null.
   */
  ExportedByPolyBodyTools CATPolyFace* GetAdjacentFace (const CATPolyEdge* E, const CATPolyFace* F);

  /**
   * Returns the adjacent volume to a volume across a face.
   * A face is incident to at most two volumes.
   * There cannot be more than one adjacent volume.
   * It returns null if the face has no other incident volume.
   * @return
   *   The adjacent face or null.
   */
  ExportedByPolyBodyTools CATPolyVolume* GetAdjacentVolume (const CATPolyFace* F, const CATPolyVolume* VLM);

  /**
   * Returns the CATPolyVertex and its CATIPolySurfaceVertex uniquely associated to a CATPolyFaceOrbit.
   */
  ExportedByPolyBodyTools CATPolyVertex* GetVertex (CATPolyFaceOrbit& orbit, CATIPolySurfaceVertex*& iSV);

  /** @} */

};


/** @name Topology Services
    @{ */

/**
 * Returns an adjacent face to the edge if any.
 * @return
 *   The adjacent CATPolyFace or 0 if there is none.
 */
ExportedByPolyBodyTools CATPolyFace* CATPolyGetAdjacentFace (CATPolyEdge* iEdge);

/**
 * Returns the CATIPolyCurve that is shared by the CATPolyEdge and the CATPolyFace.
 * The returned instance should not be released.
 */
ExportedByPolyBodyTools CATIPolyCurve* CATPolyGetCurve (CATPolyEdge* iEdge, CATPolyFace* iFace);

/**
 * Returns the CATIPolyPoint that is shared by the CATPolyVertex and the CATPolyFace.
 * The returned instance should not be released.
 */
ExportedByPolyBodyTools CATIPolyPoint* CATPolyGetPoint (CATPolyVertex* iVertex, CATPolyFace* iFace);

/**
 * Returns the CATIPolyObject that is shared by the CATPolyCell and the CATPolyFace.
 * The returned instance should not be released.
 */
ExportedByPolyBodyTools CATIPolyObject* CATPolyGetPolyObject (CATPolyCell* iCell, CATPolyFace* iFace);

/**
 * Returns a CATIPolyCurve associated to a CATPolyEdge.
 * The returned instance should not be released.
 */
ExportedByPolyBodyTools CATIPolyCurve* CATPolyGetACurve (const CATPolyEdge* iEdge);

/**
* Returns a CATIPolyPoint associated to a CATPolyVertex.
* The returned instance should not be released.
*/
ExportedByPolyBodyTools CATIPolyPoint* CATPolyGetAPoint (const CATPolyVertex* iVertex);

/**
 * Given two CATPolyCell, returns the CATPolyEdge that is adjacent to both cells.
 * This CATPolyEdge may not be unique for two CATPolyVertex.
 * @return
 *   The CATPolyEdge shared by the two input cells.
 */
ExportedByPolyBodyTools const CATPolyEdge* CATPolyGetCommonEdge (const CATPolyCell* iCell0, const CATPolyCell* iCell1);

/** @} */


/** @name Diagnosis
    @{ */

/**
 * Returns the status about the validity of the CATPolyBody. 
 * @return
 *   <ul>
 *     <li> <tt>S_OK</tt> if the CATPolyBody is valid;
 *     <li> <tt>S_FALSE</tt> if the CATPolyBody is invalid;
 *     <li> <tt>E_FAIL</tt> if a serious error is detected (corrupted CATPolyBody) and the tests
 *          could not be completed.
 *   </ul>
 * See CATPolyBodyDiagnosis if the CATPolyBody is invalid for further information about 
 * the errors.
 */
ExportedByPolyBodyTools HRESULT CATPolyIsValid (const CATPolyBody& iPolyBody);

/**
 * Returns the status about the watertightness of the CATPolyBody. 
 * @return
 *   <ul>
 *     <li> <tt>S_OK</tt> if the CATPolyBody is topologically watertight;
 *     <li> <tt>S_FALSE</tt> if the CATPolyBody is open;
 *     <li> <tt>E_FAIL</tt> if a serious error is detected (corrupted CATPolyBody) and the tests
 *          could not be completed.
 *   </ul>
 */
ExportedByPolyBodyTools HRESULT CATPolyIsTopologicallyWatertight(const CATPolyBody& iPolyBody);

/**
 * Returns the status about the geometric watertightness of the CATPolyBody. 
 * @return
 *   <ul>
 *     <li> <tt>S_OK</tt> if the CATPolyBody is geometrically watertight;
 *     <li> <tt>S_FALSE</tt> if the CATPolyBody is open;
 *     <li> <tt>E_FAIL</tt> if a serious error is detected (corrupted CATPolyBody) and the tests
 *          could not be completed.
 *   </ul>
 */
ExportedByPolyBodyTools HRESULT CATPolyIsGeometricallyWatertight(const CATPolyBody& iPolyBody);

/**
 * Returns the CATPolyBodyDiagnosis from a CATPolyBody if available.
 * The object returned should not be deleted by the caller.
 * @param iPolyBody
 *   The input CATPolyBody.
 * @return
 *   The diagnosis of the CATPolyBody.
 */
ExportedByPolyBodyTools CATPolyBodyDiagnosis* CATPolyGetDiagnosis (const CATPolyBody& iPolyBody);

/**
 * Returns the geometric diagnosis from a CATPolyBody if available.
 * The diagnosis has to be filled with a CATPolyBodyGeoChecker, or by calling CATPolyIsGeoValid.
 * The object returned should not be deleted by the caller.
 * @param iPolyBody
 *   The input CATPolyBody.
 * @return
 *   The geometric diagnosis of the CATPolyBody.
 */
ExportedByPolyBodyTools CATPolyBodyGeoDiagnosis* CATPolyGetGeoDiagnosis (const CATPolyBody& iPolyBody);

/** @} */


/** @name Bounding Volumes
    @{ */

namespace Poly
{

  /**
   * Computes the bounding box of a CATPolyBody instance.
   * @param iPolyBody
   *   The input CATPolyBody.
   * @param ioBox
   *   The computed bounding box.
   * @param iPosMatrix
   *   An optional transformation applied to the points.
   * @return
   *   S_OK for a successful call
   *   S_FALSE if the bounding box has not been computed.
   *   E_FAIL if an error occurs during the computation.
   */
  ExportedByPolyBodyTools HRESULT ComputeBoundingBox (const CATPolyBody& iPolyBody,
    CATMathBox& ioBox,
    const CATMathTransformation* iPosMatrix = 0);

}


/**
 * Returns a bounding sphere of the CATPolyBody instance.
 * @param iPolyBody
 *   The input CATPolyBody.
 * @param ioBoundingSphere
 *   The bounding sphere that will be set by a successful call.
 * @param iPosMatrix
 *   An optional transformation defining the position of the CATPolyBody.
 * @return
 *   S_OK for a successful call
 *   S_FALSE if the bounding sphere has not been set.
 *   E_FAIL if an error occurs during the computation.
 */
//ExportedByPolyBodyTools HRESULT CATPolyGetBoundingSphere (const CATPolyBody& iPolyBody,
                                                          //CATPolyBoundingSphere& ioBoundingSphere,
                                                          //const CATMathTransformation* iPosMatrix = 0);

/** @} */


/** @name Miscellaneous Services
    @{ */

/**
 * Retrieves the CGM ID of a CATPolyBody.
 * @param iPolyBody
 *   The input CATPolyBody.
 * @param oID
 *   The returned ID of the CATPolyBody.
 * @return
 *   S_OK if the ID is set,
 *   S_FALSE if the body does not have an ID, or
 *   E_FAIL or another error code if an error occurs.
 */
ExportedByPolyBodyTools HRESULT CATPolyGetID (const CATPolyBody& iPolyBody, unsigned int& oID);

/**
 * Retrieves the sag of a CATPolyBody.
 * @param iPolyBody
 *   The input CATPolyBody.
 * @param oSag
 *   The returned sag of the CATPolyBody.
 * @return
 *   S_OK if the sag is set,
 *   S_FALSE if the body does not have a sag, or
 *   E_FAIL or another error code if an error occurs.
 */
ExportedByPolyBodyTools HRESULT CATPolyGetSag (const CATPolyBody& iPolyBody, double& oSag);

/**
 * Retrieves the CATTolerance of a CATPolyBody.
 * The CATTolerance provides a set of tolerance values for geometric tests.
 * For instance, the distance from a point to the surface of a CATPolyBody can be compared to a length epsilon 
 * to check whether the point is on the surface or not.
 * Some tolerances like length tolerances depend on the scale of the model.
 * The instance returned cannot be deleted by the caller.
 * @param iPolyBody
 *   The input CATPolyBody.
 * @param oTolerance
 *   The returned CATTolerance associated to the CATPolyBody.
 * @return
 *   S_OK if the CATTolerance is set,
 *   S_FALSE if the body does not have a CATTolerance, or
 *   E_FAIL or another error code if an error occurs.
 */
ExportedByPolyBodyTools HRESULT CATPolyGetTolerance (const CATPolyBody& iPolyBody, const CATTolerance*& oTolerance);

/**
 * Retrieves the underlying primitive support associated to a CATPolyBody, if any.
 * @param oSupport
 *   The support.  The returned support must be released (ref-counted.)
 * <ul>
 *   <li> <tt>S_OK</tt> if a support is successfully returned.
 *   <li> <tt>S_FALSE</tt> if a support is not available.
 *   <li> <tt>E_FAIL</tt> if an error occurs.
 * </ul>
 */
ExportedByPolyBodyTools HRESULT CATPolyGetSupport (const CATPolyBody& iPolyBody, CATIPolyPrimitiveSupport*& oSupport);

/**
 * Query about a solid body.
 * A CATPolyBody is a solid body if all the cells define the boundary of a solid.
 * A solid body refers exclusively to domains of dimension 3.
 * Note: this service only reads the attributes, it does not actually check the body.
 * <ul>
 *   <li> <tt>S_OK</tt> is a solid body.
 *   <li> <tt>S_FALSE</tt> is not a solid body.
 *   <li> <tt>E_FAIL</tt> for any error.
 * </ul>
 */
ExportedByPolyBodyTools HRESULT CATPolyIsSolidBody (const CATPolyBody& iPolyBody);

/**
 * Query about a skin body.
 * A skin body refers exclusively to domains of dimension 2.
 * Note: this service only reads the attributes, it does not actually check the body.
 * <ul>
 *   <li> <tt>S_OK</tt> is a skin body.
 *   <li> <tt>S_FALSE</tt> is not a skin body.
 *   <li> <tt>E_FAIL</tt> for any error.
 * </ul>
 */
ExportedByPolyBodyTools HRESULT CATPolyIsSkinBody (const CATPolyBody& iPolyBody);

/**
 * Query about a wire body.
 * A wire body refers exclusively to domains of dimension 1.
 * Note: this service only reads the attributes, it does not actually check the body.
 * <ul>
 *   <li> <tt>S_OK</tt> is a wire body.
 *   <li> <tt>S_FALSE</tt> is not a wire body.
 *   <li> <tt>E_FAIL</tt> for any error.
 * </ul>
 */
ExportedByPolyBodyTools HRESULT CATPolyIsWireBody (const CATPolyBody& iPolyBody);

/**
* Query about a point body.
* A point body refers exclusively to domains of dimension 0.
* Note: this service only reads the attributes, it does not actually check the body.
* <ul>
*   <li> <tt>S_OK</tt> is a point body.
*   <li> <tt>S_FALSE</tt> is not a point body.
*   <li> <tt>E_FAIL</tt> for any error.
* </ul>
*/
ExportedByPolyBodyTools HRESULT CATPolyIsPointBody (const CATPolyBody& iPolyBody);

/** @} */


namespace Poly
{
  /** @name Size Services
   *
   * CATPolyBodyServices.h
   * @{ */

  /**
   * Returns the total number of facets in a CATPolyBody.
   * @param iPolyBody
   *   The input CATPolyBody.
   * @return
   *   The count of all facets from all CATIPolySurface.
   */
  ExportedByPolyBodyTools unsigned int GetNbFacets (const CATPolyBody& iPolyBody);

  /**
   * Returns the total number of surface-vertices in a CATPolyBody.
   * @param iPolyBody
   *   The input CATPolyBody.
   * @return
   *   The count of all surface-vertices from all CATIPolySurface.
   */
  ExportedByPolyBodyTools unsigned int GetNbSurfaceVertices (const CATPolyBody& iPolyBody);

  /**
   * Returns the total number of edge-segments in a CATPolyBody.
   * (Edge-segments or bars may be shared by several curves.)
   * @param iPolyBody
   *   The input CATPolyBody.
   * @return
   *   The count of all edge-segments from the sample curves from the edges of the CATPolyBody.
   */
  ExportedByPolyBodyTools unsigned int GetNbEdgeSegments (const CATPolyBody& iPolyBody);

  /**
   * Returns the number of curve-vertices in each curve incident to a CATPolyEdge.
   * @param iPolyBody
   *   The input CATPolyBody.
   * @return
   *   The number of curve-vertices.
   */
  ExportedByPolyBodyTools unsigned int GetNbCurveVertices (const CATPolyEdge& Edge);

  /** @} */

};


namespace Poly
{
  /** @name CATPolyBody Services
   *
   * CATPolyBodyServices.h
   * @{ */

  /**
   * Returns the valence of a CATPolyVertex or equivalently the number of edges.
   */
  ExportedByPolyBodyTools unsigned int GetValence (const CATPolyVertex& V);

  /**
   * Customization of the face-add vertex for some import operators.
   * Before calling the CATPolyBody::FaceAddVertex, this method checks 
   * a surface-vertex does not already refer to a CATPolyVertex.
   * It does not call CATPolyBody::FaceAddVertex if there is a reference to a vertex.
   * If the reference matches the input vertex, it just returns; if it does not match it fails.
   */
  ExportedByPolyBodyTools HRESULT CustomFaceAddVertex (CATPolyBody& B, CATPolyFace& F, const int sv, CATPolyVertex& V);

 /** @} */

};


namespace Poly
{
  /** @name CATPolyBody Services
   *
   * CATPolyBody services to map the cell to an increasing id. <br/>
   * It can be useful to use array instead of map for highly-called methods.
   *
   * The map becomes invalid when the CATPolyBody topology changes.
   *
   * CATPolyBodyServices.h
   * @{ */

   /**
    * Maps the vertex to their integer position in the CATPolyBodyVertexIterator (starting from 1).
    * @param iPolyBody
    *   The input CATPolyBody.
    * @param oVertexToId
    *   A map from the CATPolyBody vertices to an integer index.
    */
  ExportedByPolyBodyTools HRESULT CreateVertexToIteratorId (const CATPolyBody& iPolyBody,
                                                            CATMapOfPtrToInt& oVertexToId);

  /**
   * Maps the edge to their integer position in the CATPolyBodyEdgeIterator (starting from 1).
   * @param iPolyBody
  *   The input CATPolyBody.
  * @param oEdgeToId
  *   A map from the CATPolyBody edges to an integer index.
  */
  ExportedByPolyBodyTools HRESULT CreateEdgeToIteratorId (const CATPolyBody& iPolyBody,
                                                          CATMapOfPtrToInt& oEdgeToId);

  /**
   * Maps the face to their integer position in the CATPolyBodyFaceIterator (starting from 1).
   * @param iPolyBody
   *   The input CATPolyBody.
   * @param oFaceToId
   *   A map from the CATPolyBody faces to an integer index.
   */
  ExportedByPolyBodyTools HRESULT CreateFaceToIteratorId (const CATPolyBody& iPolyBody,
                                                          CATMapOfPtrToInt& oFaceToId);

};


namespace Poly
{
 /** @name CATPolyBody Services
  *
  * CATPolyBodyServices.h
  * @{ */

 /** 
  * Sets the point flag on the CATPolyBody (domains of dimension 0)
  * @return 
  *         S_FALSE if the attributes cannot be changed on the CATPolyBody.
  */
ExportedByPolyBodyTools HRESULT SetPointType(CATPolyBody& iPolyBody);

 /** 
  * Sets the wire flag on the CATPolyBody (domains of dimension 1)
  * @return 
  *         S_FALSE if the attributes cannot be changed on the CATPolyBody.
  */
ExportedByPolyBodyTools HRESULT SetWireType (CATPolyBody& iPolyBody);

 /** 
  * Sets the skin flag on the CATPolyBody (domains of dimension 2)
  * @return 
  *         S_FALSE if the attributes cannot be changed on the CATPolyBody.
  */
ExportedByPolyBodyTools HRESULT SetSkinType (CATPolyBody& iPolyBody);

 /** 
  * Sets the solid flag on the CATPolyBody (domains of dimension 3)
  * @return 
  *         S_FALSE if the attributes cannot be changed on the CATPolyBody.
  */
ExportedByPolyBodyTools HRESULT SetSolidType (CATPolyBody& iPolyBody);

/**
 * Returns:
 *   * +1 if the shell is the outer shell of a volume;
 *   *  0 if the shell is the inner shell of a volume;
 *   * -1 if the state of the shell is unknown.
 */
ExportedByPolyBodyTools int IsOuterShell (const CATPolyVolumeShell* iShell);

/** 
 * Returns whether the body contains at least one cell (be vertex, edge or face)
 */
ExportedByPolyBodyTools CATBoolean IsEmpty(CATPolyBody * iPolyBody);

/** 
 * Returns whether the body contains at least one free edge (not attached to any face)
 */
ExportedByPolyBodyTools CATBoolean DoesContainWire(CATPolyBody * iPolyBody);

/** 
 * Returns whether the body contains at least one free vertex (not attached to any edge nor face)
 */
ExportedByPolyBodyTools CATBoolean DoesContainPoint(CATPolyBody * iPolyBody);

/** 
 * Does nothing if some edges point to the vertex.
 * Detaches the vertex from the faces then deletes it.
 * iVertexToDelete is no more valid after this operation.
 * @return S_OK if the vertex was successfully removed.
 */
ExportedByPolyBodyTools HRESULT DeleteVertex(CATPolyBody & ioBody, CATPolyVertex *& iVertexToDelete);

/** 
 * Detaches the edge from the faces then deletes it.
 * iEdgeToDelete is no more valid after this operation.
 * @return S_OK if the edge was successfully removed.
 */
ExportedByPolyBodyTools HRESULT DeleteEdge(CATPolyBody & ioBody, CATPolyEdge *& iEdgeToDelete);

/** 
 * Detaches the edges and the vertices from the face then deletes the face.
 * iFaceToDelete is no more valid after this operation.
 * @return S_OK if the face was successfully removed.
 */
ExportedByPolyBodyTools HRESULT DeleteFace(CATPolyBody & ioBody, CATPolyFace *& iFaceToDelete);

/** 
 * Calls any of DeleteVertex, DeleteEdge or DeleteFace.
 * @return S_OK if the cell was successfully removed.
 */
ExportedByPolyBodyTools HRESULT DeleteCell(CATPolyBody & ioBody, CATPolyCell *& iCellToDelete);



/** @} */

};


#ifndef DOXYGEN_SHOULD_SKIP_THIS

/** @name Streaming Services
    @{ */

    /**
     * @see Poly::IsStreamable
     * CATPolyStreamServices.h
     */
ExportedByPolyBodyTools HRESULT CATPolyIsStreamable (const CATPolyBody& iPolyBody, const CATMathStream& iStream);

/**
 * @see Poly::Stream
 * CATPolyStreamServices.h
 */
ExportedByPolyBodyTools HRESULT CATPolyStreamPolyBody (const CATUnicodeString& iFileName,
  const CATPolyBody& iPolyBody, const CATMathTransformation* iPosMatrix,
  CATBoolean iPolyhedralObjectsMode,  // By default: FALSE.
  const unsigned int iLayerFilter = CATPolyStreamOptions::eAllLayers |
  CATPolyStreamOptions::eEnableStreamOfBadBody,
  CATPolyStreamRecord* ioStreamRecords = 0);

/**
 * @see Poly::Stream
 * CATPolyStreamServices.h
 */
ExportedByPolyBodyTools HRESULT CATPolyStreamPolyBody (CATMathStream& str,
  const CATPolyBody& iPolyBody, const CATMathTransformation* iPosMatrix,
  CATBoolean iPolyhedralObjectsMode,  // By default: FALSE.
  const unsigned int iLayerFilter = CATPolyStreamOptions::eAllLayers |
  CATPolyStreamOptions::eEnableStreamOfBadBody,
  CATPolyStreamRecord* ioStreamRecords = 0);

/**
 * @see Poly::Stream
 * CATPolyStreamServices.h
 */
ExportedByPolyBodyTools HRESULT CATPolyStreamPolyBody (char*& oBuffer, size_t& oNbBytes,
  const CATPolyBody& iPolyBody, const CATMathTransformation* iPosMatrix,
  CATBoolean iPolyhedralObjectsMode,  // By default: FALSE.
  const unsigned int iLayerFilter = CATPolyStreamOptions::eAllLayers |
  CATPolyStreamOptions::eEnableStreamOfBadBody,
  CATPolyStreamRecord* ioStreamRecords = 0);

/**
 * @see Poly::Stream
 * CATPolyStreamServices.h
 */
ExportedByPolyBodyTools HRESULT CATPolyStreamPolyBody (const CATUnicodeString& iFileName,
  const CATPolyBody& iPolyBody,
  CATBoolean iPolyhedralObjectsMode = FALSE,
  const unsigned int iLayerFilter = CATPolyStreamOptions::eAllLayers |
  CATPolyStreamOptions::eEnableStreamOfBadBody,
  CATPolyStreamRecord* ioStreamRecords = 0);

/**
 * @see Poly::Stream
 * CATPolyStreamServices.h
 */
ExportedByPolyBodyTools HRESULT CATPolyStreamPolyBody (CATMathStream& str,
  const CATPolyBody& iPolyBody,
  CATBoolean iPolyhedralObjectsMode = FALSE,
  const unsigned int iLayerFilter = CATPolyStreamOptions::eAllLayers |
  CATPolyStreamOptions::eEnableStreamOfBadBody,
  CATPolyStreamRecord* ioStreamRecords = 0);

/**
 * @see Poly::Unstream
 * CATPolyStreamServices.h
 */
ExportedByPolyBodyTools HRESULT CATPolyUnstreamPolyBody (const CATUnicodeString& iFileName,
  CATPolyBody*& oPolyBody, CATMathTransformation*& oPosMatrix,
  const unsigned int iLayerFilter = CATPolyStreamOptions::eAllLayers,
  CATPolyUnstreamRecord* ioUnstreamRecords = 0);

/**
 * @see Poly::Unstream
 * CATPolyStreamServices.h
 */
ExportedByPolyBodyTools HRESULT CATPolyUnstreamPolyBody (CATMathStream& str,
  CATPolyBody*& oPolyBody, CATMathTransformation*& oPosMatrix,
  const unsigned int iLayerFilter = CATPolyStreamOptions::eAllLayers,
  CATPolyUnstreamRecord* ioUnstreamRecords = 0);

/**
 * @see Poly::Unstream
 * CATPolyStreamServices.h
 */
ExportedByPolyBodyTools HRESULT CATPolyUnstreamPolyBody (const char* iBuffer, const size_t iNbBytes,
  CATPolyBody*& oPolyBody, CATMathTransformation*& oPosMatrix,
  const unsigned int iLayerFilter = CATPolyStreamOptions::eAllLayers,
  CATPolyUnstreamRecord* ioUnstreamRecords = 0);

/**
 * @see Poly::Unstream
 * CATPolyStreamServices.h
 */
ExportedByPolyBodyTools HRESULT CATPolyUnstreamPolyBody (const CATUnicodeString& iFileName,
  CATPolyBody*& oPolyBody,
  const unsigned int iLayerFilter = CATPolyStreamOptions::eAllLayers,
  CATPolyUnstreamRecord* ioUnstreamRecords = 0);

/**
 * @see Poly::Unstream
 * CATPolyStreamServices.h
 */
ExportedByPolyBodyTools HRESULT CATPolyUnstreamPolyBody (CATMathStream& str,
  CATPolyBody*& oPolyBody,
  const unsigned int iLayerFilter = CATPolyStreamOptions::eAllLayers,
  CATPolyUnstreamRecord* ioUnstreamRecords = 0);

/** @} */

/**
 * @nodoc
 */
POLY_DEPRECATED ("Use CATPolyEdge::HasIncidentFaces ();",
ExportedByPolyBodyTools HRESULT CATPolyIsEdgeAdjacentToAnyFace (CATPolyEdge* iEdge));

/**
 * @nodoc
 */
POLY_DEPRECATED ("Use Poly::GetIncidentEdge ()",
ExportedByPolyBodyTools CATPolyEdge* CATPolyGetAdjacentEdge (const CATPolyVertex* iVertex, const CATPolyEdge* iEdge, const CATPolyFace* iFace);)

/**
 * @nodoc
 */
POLY_DEPRECATED ("Use CATPolyBody::NewNative ();",
ExportedByPolyBodyTools CATPolyBody* CATPolyCreatePolyBodyForNativePolyhedralObjects ();)


inline HRESULT CATPolyGetNbFacets (const CATPolyBody& iPolyBody, int& oNbFacets)
{
  oNbFacets = Poly::GetNbFacets (iPolyBody);
  return S_OK;
}

inline HRESULT CATPolyGetNbSurfaceVertices (const CATPolyBody& iPolyBody, int& oNbSurfaceVertices)
{
  oNbSurfaceVertices = Poly::GetNbSurfaceVertices (iPolyBody);
  return S_OK;
}

inline HRESULT CATPolyGetNbEdgeSegments (const CATPolyBody& iPolyBody, int& oNbEdgeSegments)
{
  oNbEdgeSegments = Poly::GetNbEdgeSegments (iPolyBody);
  return S_OK;
}

ExportedByPolyBodyTools HRESULT CATPolyGetBoundingBox (const CATPolyBody& iPolyBody,
  CATMathBox& ioBox,
  const CATMathTransformation* iPosMatrix = 0);


#endif
