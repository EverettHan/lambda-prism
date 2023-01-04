// COPYRIGHT DASSAULT SYSTEMES 2003, ALL RIGHTS RESERVED.
//=============================================================================
//
// CATPolyBody
//
//=============================================================================
// 2016-02-03   NDO: AddRef and Release become const methods as they should be.
// 2011-05-04   NDO: Activation AddRef/Release R21 and R212.
// 2009-04-01   NDO: Revisited
// 2007-01-02   BPG: Raise
// 2003-03-20   FDS: New
//=============================================================================
#pragma once

#include "PolyMODEL.h"
#include "CATPolyDart.h"
#include "CATPolyDartList.h"
#include "CATPolyVertexList.h"
#include "CATPolyEdgeList.h"
#include "CATPolyFaceList.h"
#include "CATPolyVolumeList.h"
#include "CATPolyMicroTopologyFwd.h"
#include "CATPolyMacroTopologyFwd.h"
#include "CATErrorDef.h"
#include "CATIAV5Level.h"

class CATMathBox;
class CATIPolyBodyAttributes;
class CATPolyBodyNativeAttributes;
class CATMutex;


#ifndef DOXYGEN_SHOULD_SKIP_THIS
namespace Poly 
{
  ExportedByPolyMODEL CATPolyBody* NewEditableBody (const CATPolyBody& iPolyBody);
}
#endif


/**
 * Definition of a polyhedral body.
 * 
 * A CATPolyBody represents a cellular model whose cells refer to discrete geometry, namely,
 * meshes and discrete curves (polylines.)  A polyhedral body has a unique implementation (no interface).
 * 
 * The cells of the CATPolyBody, vertices, edges and faces are defined by the classes:
 * <ul>
 *   <li> CATPolyVertex
 *   <li> CATPolyEdge
 *   <li> CATPolyFace
 * </ul>
 * They all derive from CATPolyCell.
 *
 * To scan the cells from the body, several iterators are defined:
 * <ul>
 *   <li> CATPolyBodyVertexIterator
 *   <li> CATPolyBodyEdgeIterator
 *   <li> CATPolyBodyFaceIterator
 * </ul>
 * Other iterators are defined to navigate through the neighborhoods from a cell.
 *
 * The faces may refer to various types of meshes (heterogeneous model): triangles, quads, polygonal, procedural meshes.
 */
class ExportedByPolyMODEL CATPolyBody
{

public:

/** @name Life Cycle
  @{ */

  /**
   * Creates a new instance of a CATPolyBody. 
   * Instances are ref-counted.  Use the Release () method when done with this CATPolyBody; 
   *
   * @param iWithDefaultAttributes.
   *   If set to true, default attributes (see CATPolyBodyDefaultAttributes) will be added to the CATPolyBody instance.
   *   By default, the CATPolyBody is created without attributes; you must assign it to an instance of CATIPolyBodyAttributes 
   *   to specify the characteristics of the data contained in this body (see the method AbsorbAttributes ()).
   *   The attributes are required by some operators and for streaming.
   * @return
   *   A new CATPolyBody (with or without default attributes depending on the value of the input flag).
   */
  static CATPolyBody* New (bool iWithDefaultAttributes = false);

  /**
   * Creates a native CATPolyBody.
   * A native CATPolyBody refers to polyhedral surfaces, curves and points exclusive to the PolyhedralObjects framework.
   * It cannot refer to any polyhedral objects implemented in another framework.
   * Native polyhedral objects include:
   *   * Surfaces
   *       * CATPolyMeshImpl
   *       * CATPolyCompactMesh
   *       * CATPolyCompactMeshConst
   *       * CATPolyEditableMesh (if the parent mesh is native)
   *       * CATPolySubMesh (if the parent mesh is native)
   *       * CATPolyProxyMesh (if the parent mesh is native)
   *   * Curves
   *       * CATPolyLine
   *       * CATPolyLineConst
   *       * CATPolyMeshCurve
   *       * CATPolyMeshCurveConst
   *       * CATPolySurfaceVertexLine
   *       * CATPolyCompactSurfaceVertexLine
   *       * CATPolyCompactSurfaceVertexLineConst
   *       * CATPolyEditableCurve (if the parent curve is native)
   *       * CATPolyEditableSurfaceVertexLine (if the parent curve is native)
   *   * Points
   *       * CATPolyPoint
   *       * CATPolyPointConst
   *       * CATPolyMeshPoint
   *       * CATPolyMeshPointConst
   *       * CATPolyCurveVertex
   *       * CATPolyCurveVertexConst
   *       * CATPolySurfaceVertex
   *       * CATPolySurfaceVertexConst
   *
   * A native CATPolyBody instance is associated to (and only to) a CATPolyBodyNativeAttributes instance.
   *
   * @return
   *   A native CATPolyBody.
   *   The instance must be released.
   */
  static CATPolyBody* NewNative (bool iWithVolumes = false);

  /**
   * Returns true if the CATPolyBody is native.
   */
  inline bool IsNative () const;

  /**
   * Returns true if the CATPolyBody can accept volume cells.
   */
  inline bool WithVolumes () const;

  /**
   * Absorbs a new set of attributes.
   * After a successful call, the input attributes are owned by this instance;
   * The attributes should no longer be deleted or assigned to another CATPolyBody.
   *
   * The instance of attributes cannot be changed once set.
   */
  HRESULT AbsorbAttributes (CATIPolyBodyAttributes* iAttributes);

  /**
  * Reference counting.
  * Increments the reference counter.
  */
  void AddRef () const;

  /**
  * Reference counting.
  * Decrements the reference counter.  When the counter reaches 0, the instance is deleted.
  */
  void Release () const;

/** @} */

public:

/** @name Vertex
    @{ */

  /** 
   * Given a CATIPolyPoint, P, creates a new vertex in the CATPolyBody.
   * A CATPolyVertex is associated to at least one CATIPolyPoint.
   * @param P 
   *   The point that is associated to the vertex.
   * @return 
   *   A new vertex when succeeding and 0 on failure (e.g. not enough memory). 
   */
  inline CATPolyVertex* MakeVertex (CATIPolyPoint& P);

  /**
   * Creates a new vertex in the CATPolyBody out of a pseudo-manifold vertex.
   * This new CATPolyVertex will have one and only one 12-orbit or 123-orbit (only one pseudo-manifold vertex).
   * Be aware that the origin vertex to which iPMV belongs is not deleted.
   * @param iPMV
   *   The input pseudo manifold vertex.
   * @return
   *   The new vertex constructed from this input pseudo-manifold vertex.
   */
  inline CATPolyVertex* MakeVertex (const CATPolyPseudoManifoldVertex& iPMV);

  /** 
   * Removes and deletes a vertex. 
   * The vertex can no longer be incident to any edge of face to be removed.
   * See FaceRemoveVertex () to remove the incidence between a face and a vertex.
   * If the vertex is the start or end vertex of a CATPolyEdge, then the method fails.
   * The edges incident to the vertex should be deleted first.
   * @param V
   *   The vertex to be deleted.
   * @return 
   *   On success, returns S_OK and otherwise, an error.
  */
  inline HRESULT DeleteVertex (CATPolyVertex*& V);

public:

  /**
   * Adds another CATIPolyPoint to an existing CATPolyVertex.
   * The CATIPolyPoint could be a CATIPolyCurveVertex or a CATIPolySurfaceVertex.
   * @param V
   *   The input CATPolyVertex.
   * @param P
   *   The point added to the CATPolyVertex.
   * @return
   *   On success, returns S_OK and otherwise, an error.
   */
  inline HRESULT VertexAddPoint (CATPolyVertex& V, CATIPolyPoint& P);

public:

  /**
   * Returns the number of CATPolyVertex in the CATPolyBody.
   * @return
   *   The number of vertex cells.
   */
  inline unsigned int GetNbVertices () const;

  /** 
   * Returns a CATPolyVertex.
   * @return 
   *   Returns the CATPolyVertex of index v with v ranging from 1 to GetNbVertices () included. 
   */
  inline CATPolyVertex* GetVertex (int v) const;

/** @} */


public:

/** @name Edge
    @{ */

  /** 
   * Given a CATIPolyCurve, C, and two CATPolyVertex, V0 and V1, defining the extremities
   * creates a new edge in the CATPolyBody.
   * A CATPolyEdge is associated to at least one CATIPolyCurve.
   * @param V0 
   *   The start vertex of the edge.
   * @param V1 
   *   The end vertex of the edge.
   * @param C 
   *   The curve that is associated to the edge.
   *
   * @return 
   *   The new edge.
   */
  inline CATPolyEdge* MakeEdge (CATPolyVertex& V0, CATPolyVertex& V1, CATIPolyCurve& C);

  /**
   * Creates an edge joined at a vertex (edge closing on a vertex).
   * The curve C must be open.  (Position of first vertex matches position of end vertex.)
   */
  inline CATPolyEdge* MakeEdge (CATPolyVertex& V, CATIPolyCurve& C);

  /**
   * Creates an edge from a curve that is closed.
   */
  inline CATPolyEdge* MakeEdge (CATIPolyCurve& C);

  /**
   * Given a CATIPolyCurve, C, and two CATPolyVertex defining the end and the start, StartVertex and EndVertex,
   * creates a new edge.
   * @param StartVertex 
   *   The start vertex of the edge.
   * @param PreviousEdge
   *   If different from the NULL pointer, the edge to which the new edge will be linked at StartVertex.
   * @param EndVertex 
   *   The end vertex of the edge.
   * @param NextEdge
   *   If different from the NULL pointer, the edge to which the new edge will be linked at EndVertex.
   * @return 
   *   A new edge when succeeding and 0 on failure (e.g. not enough memory). 
   */
  inline CATPolyEdge* MakeEdge (CATPolyVertex& StartVertex, CATPolyEdge* PreviousEdge,
                                CATPolyVertex& EndVertex, CATPolyEdge* NextEdge,
                                CATIPolyCurve& C);

  /**
   * Creates a new edge in the CATPolyBody out of a manifold edge.
   * This new CATPolyEdge will have one and only one 02-orbit or 023-orbit (only one manifold edge).
   * Be aware that the origin edge to which iME belongs is not deleted.
   * @param iME
   *   The input manifold edge.
   * @return
   *   The new edge constructed from this input manifold edge.
   */
  inline CATPolyEdge* MakeEdge (const CATPolyManifoldEdge& iME);

  /**
   * Removes and deletes an edge. 
   * To be removed, the edge cannot be incident to any face.
   * See FaceRemoveEdge () to remove the incidence between a face and an edge.
   * @param E
   *   The edge to be deleted.
   * @return 
   *   On success, returns S_OK and otherwise, an error.
  */
  inline HRESULT DeleteEdge (CATPolyEdge*& E);

  /**
   * Add a face adjacency information around an edge.
   * Both faces must have no adjacency information yet, otherwise the operation does nothing.
   * @param face0
   *   the first face
   * @param face1
   *   the second face
   * @param edge
   *   the edge to add the adjacency
   * @return
   *   On success, returns S_OK, S_FALSE if the adjacency couldn't be performed, E_FAIL otherwise.
  */
  inline HRESULT AddFacesAdjacency (CATPolyFace& face0,
    CATPolyFace& face1,
    CATPolyEdge& edge);

public:

  /**
   * Returns the number of CATPolyEdge in the CATPolyBody.
   * @return
   *   The number of edge cells.
   */
  inline unsigned int GetNbEdges () const;

  /** 
   * Returns a CATPolyEdge.
   * @return 
   *   Returns the CATPolyEdge of index e with e ranging from 1 to GetNbEdges () included. 
   */
  inline CATPolyEdge* GetEdge (int e) const;

/** @} */


public:

/** @name Face
    @{ */

  /** 
   * Given a CATIPolySurface, S, creates a new face in the CATPolyBody.
   * A CATPolyFace is associated to one and only one CATIPolySurface.
   * @param p 
   *   The surface that is associated to the vertex.
   * @return 
   *   A new face when succeeding and 0 on failure (e.g. not enough memory). 
   */
  CATPolyFace* MakeFace (CATIPolySurface& S);

  /** 
   * Removes and deletes a face.  
   *
   * The suppression of a face does not get rid of vertices and edges supported by the
   * CATIPolySurface associated to the face.  These must be detached explicitely.  For instance, 
   * assume that CATPolyFace, F, is incident to a CATPolyEdge, E.  This edge, E, references a
   * CATIPolyCurve, C, that references the CATIPolySurface, S.  Before suppression of F, the 
   * surface S is referenced by F and C.  Suppression of F removes its reference to S but not 
   * that of the curve C.  The surface S is not deleted because there remains at least one reference.
   * 
   * @param F
   *   The face to be deleted.
   * @return 
   *   On success, returns S_OK and otherwise, an error.
  */
  inline HRESULT DeleteFace (CATPolyFace*& F);

public:

  /**
   * Given a CATIPolySurfaceVertex, P, (a CATIPolyPoint referencing a vertex of a CATIPolySurface),
   * creates a new vertex.  This new vertex is incident to the CATPolyFace.
   * (To remove and delete the CATPolyVertex, use DeleteVertex ().)
   * @param F
   *   The CATPolyFace to which the new vertex is incident.
   * @param P
   *   The CATIPolySurface vertex associated to the new vertex.
   * @return 
   *   A new vertex when succeeding and 0 on failure (e.g. not enough memory). 
   *   The method will fail if F and P refers to different CATIPolySurface's.
   */
  inline CATPolyVertex* MakeFaceVertex (CATPolyFace& F, CATIPolySurfaceVertex& P);

  /**
   * Removes the incidence between a CATPolyFace, F, and a CATPolyVertex, V
   * and deletes the vertex.  The vertex should not be incident to any other face.
   * This method is equivalent to a FaceRemoveVertex () followed by a DeleteVertex ().
   * @return
   *   On success, returns S_OK and otherwise, an error.
   */
  HRESULT DeleteFaceVertex (CATPolyFace& F, CATPolyVertex*& V, CATIPolySurfaceVertex& P);

  /**
   * Given a CATIPolySurfaceVertexLine, SVL, and two CATPolyVertex defining the end and the start, StartVertex and EndVertex,
   * creates a new edge. The new edge is incident to the CATPolyFace.
   * (To remove and delete the CATPolyEdge, use DeleteEdge ().)
   * @param F
   *   The CATPolyFace to which the new edge is incident.
   * @param StartVertex 
   *   The start vertex of the edge.
   * @param EndVertex 
   *   The end vertex of the edge.
   * @param SVL 
   *   The CATIPolySurface curve that is associated to the edge.
   * @return 
   *   A new edge when succeeding and 0 on failure (e.g. not enough memory). 
   *   The method will fail if F and C refers to different CATIPolySurface's.
   */
  inline CATPolyEdge* MakeFaceEdge (CATPolyFace& F,
    CATPolyVertex& StartVertex, CATPolyVertex& EndVertex, CATIPolySurfaceVertexLine& SVL);

  /**
   * Given a CATIPolySurfaceVertexLine, SVL, and two CATPolyVertex defining the end and the start, StartVertex and EndVertex,
   * creates a new edge. The new edge is incident to the CATPolyFace.
   * (To remove and delete the CATPolyEdge, use DeleteEdge ().)
   * @param F
   *   The CATPolyFace to which the new edge is incident.
   * @param StartVertex 
   *   The start vertex of the edge.
   * @param PreviousEdge
   *   If different from the NULL pointer, the edge to which the new edge will be linked at StartVertex.
   * @param EndVertex 
   *   The end vertex of the edge.
   * @param NextEdge
   *   If different from the NULL pointer, the edge to which the new edge will be linked at EndVertex.
   * @param SVL 
   *   The CATIPolySurface curve that is associated to the edge.
   * @return 
   *   A new edge when succeeding and 0 on failure (e.g. not enough memory). 
   *   The method will fail if F and C refers to different CATIPolySurface's.
   */
  inline CATPolyEdge* MakeFaceEdge (CATPolyFace& F,
    CATPolyVertex& StartVertex, CATPolyEdge* PreviousEdge,
    CATPolyVertex& EndVertex, CATPolyEdge* NextEdge,
    CATIPolySurfaceVertexLine& SVL);

  /**
   * Removes the incidence between a CATPolyFace, F, and a CATPolyEdge, E
   * and deletes the edge.  The edge should not be incident to any other face.
   * This method is equivalent to a FaceRemoveEdge () followed by a DeleteEdge ().
   * @return
   *   On success, returns S_OK and otherwise, an error.
   */
  HRESULT DeleteFaceEdge (CATPolyFace& F, CATPolyEdge*& E, CATIPolySurfaceVertexLine& SVL);

public:

  /**
   * Adds an incidence between a CATPolyFace, F, and a CATPolyVertex, V, using
   * the CATIPolySurfaceVertex, P as micro-topology.  The point, P must lie on the same 
   * CATIPolySurface as the surface associated to F.
   * @return
   *   On success, returns S_OK and otherwise, an error.
   */
  inline HRESULT FaceAddVertex (CATPolyFace& F, CATPolyVertex& V, CATIPolySurfaceVertex& P);

  /**
   * Removes the incidence between a CATPolyFace, F, and a CATPolyVertex, V.
   * The face must be incident to the vertex otherwise the method will fail.
   * The method does not delete the vertex.
   * @return
   *   On success, returns S_OK and otherwise, an error.
   */
  inline HRESULT FaceRemoveVertex (CATPolyFace& F, CATPolyVertex& V, CATIPolySurfaceVertex& P);

public:

  /**
   * Adds an incidence between a CATPolyFace, F, and a CATPolyEdge, E, using
   * the CATIPolySurfaceVertexLine, SVL, as micro-topology.  The curve, SVL, must lie on the same 
   * CATIPolySurface as the surface associated to F.
   * @param F
   *   The CATPolyFace to which the edge becomes incident.
   * @param E
   *   The CATPolyEdge that becomes incident to the face.
   * @param SVL
   *   The curve added to the edge definition.  This curve is defined as a sequence of vertices on the CATIPolySurface.
   * @return
   *   On success, returns <tt>S_OK</tt> and otherwise, an error.
   */
  inline HRESULT FaceAddEdge (CATPolyFace& F, CATPolyEdge& E, CATIPolySurfaceVertexLine& SVL);

  /**
   * Adds an incidence between a CATPolyFace, F, and a CATPolyEdge, E, using
   * the CATIPolySurfaceVertexLine, SVL, as micro-topology.  The curve, SVL, must lie on the same 
   * CATIPolySurface as the surface associated to F.
   *
   * This method will fail in the creation of non-manifold edges.  See method below for the creation
   * of non-manifold edges.
   *
   * @param F
   *   The CATPolyFace to which the edge becomes incident.
   * @param iPreviousEdge
   *   If different from the NULL pointer, the edge to which the edge <tt>E</tt> will be linked at its start vertex.
   *   This previous edge must be incident to the face <tt>F</tt>
   * @param E
   *   The CATPolyEdge that becomes incident to the face.
   * @param iNextEdge
   *   If different from the NULL pointer, the edge to which the edge <tt>E</tt> will be linked at its end vertex.
   *   This next edge must be incident to the face <tt>F</tt>
   * @param SVL
   *   The curve added to the edge definition.  This curve is defined as sequence of vertices on the CATIPolySurface.
   * @return
   *   On success, returns <tt>S_OK</tt> and otherwise, an error.
   */
  inline HRESULT FaceAddEdge (CATPolyFace& F,
    CATPolyEdge* iPreviousEdge, CATPolyEdge& E, CATPolyEdge* iNextEdge,
    CATIPolySurfaceVertexLine& SVL);

  /**
   * Adds an incidence between a CATPolyFace, F, and a CATPolyEdge, E, using
   * the CATIPolySurfaceVertexLine, SVL, as micro-topology.  The curve, SVL, must lie on the same
   * CATIPolySurface as the surface associated to F.
   *
   * Calling this method may result in the creation of non-manifold edges.  A manifold edge can be incident
   * to two faces at most.
   *
   * @param F
   *   The CATPolyFace to which the edge becomes incident.
   * @param iPreviousEdge
   *   If different from the NULL pointer, the edge to which the edge <tt>E</tt> will be linked at its start vertex.
   *   This previous edge must be incident to the face <tt>F</tt>
   * @param E
   *   The CATPolyEdge that becomes incident to the face.
   * @param iNextEdge
   *   If different from the NULL pointer, the edge to which the edge <tt>E</tt> will be linked at its end vertex.
   *   This next edge must be incident to the face <tt>F</tt>
   * @param SVL
   *   The curve added to the edge definition.  This curve is defined as sequence of vertices on the CATIPolySurface.
   * @param iAdjacentFace
   *   The face becoming adjacent via a manifold-edge.  Without an adjacent face specified, this method will result in
   *   the creation of a new manifold-edge bound to the input edge. 
   * @return
   *   On success, returns <tt>S_OK</tt> and otherwise, an error.
   */
  inline HRESULT FaceAddEdge (CATPolyFace& F,
    CATPolyEdge* iPreviousEdge, CATPolyEdge& E, CATPolyEdge* iNextEdge,
    CATIPolySurfaceVertexLine& SVL, CATPolyFace* iAdjacentFace);

  /**
   * Removes the incidence between a CATPolyFace, F, and a CATPolyEdge, E.
   * The face must be incident to the edge otherwise the method will fail.
   * The method does not delete the edge.
   * @return
   *   On success, returns S_OK and otherwise, an error.
   */
  inline HRESULT FaceRemoveEdge (CATPolyFace& F, CATPolyEdge& E, CATIPolySurfaceVertexLine& SVL);

public:

  /**
   * Returns the number of CATPolyFace in the CATPolyBody.
   * @return
   *   The number of face cells.
   */
  inline unsigned int GetNbFaces () const;

  /** 
   * Returns a CATPolyFace.
   * @return 
   *   Returns the CATPolyFace of index f with f ranging from 1 to GetNbFaces () included. 
   */
  inline CATPolyFace* GetFace (int f) const;

/** @} */

public:

/** @name Volume
    @{ */

  CATPolyVolume* MakeVolume ();

  /**
   * @param orientation
   *   +1: Face has positive orientation in volume.
   *    0: Case of a full face
   *   -1: Face has negative orientation in volume.
   */
  HRESULT VolumeAddFace (CATPolyVolume& iVolume, CATPolyFace& iFace, int orientation);

  /**
   * Returns the number of CATPolyVolume in the CATPolyBody.
   * @return
   *   The number of volume cells.
   */
  inline unsigned int GetNbVolumes () const;

  /**
   * Returns a CATPolyVolume.
   * @return
   *   Returns the CATPolyVolume of index v with v ranging from 1 to GetNbVolumes () included.
   */
  inline CATPolyVolume* GetVolume (int v) const;

/** @} */

public:

/** @name Topological Edition
    @{ */

  /**
   * Merge two vertices (V0 absorb V1)
   * If it exist, the edge between the two vertices will be removed
   * V1 is not removed but will no longer be incident
   * to any cell and should be deleted explicitely
   * @param V0
   *   The target vertex 
   * @param V1
   *   The vertex absorbed by V0
   */
  HRESULT MergeVertices (CATPolyVertex *& V0, CATPolyVertex *& V1);

  /**
   * Collapses an edge into a vertex (start or end vertex of the edge.)
   * The edge is deleted during the collapse.  
   * The other vertex is not deleted; however it will no longer be incident 
   * to any cell and should be deleted explicitely.
   * @param V
   *   The target vertex which must be incident to the edge.
   * @param E
   *   The edge to collapse.
   */
  HRESULT CollapseEdge (CATPolyVertex* V, CATPolyEdge*& E);

  /**
   * Collapses a face onto an incident edge.
   * The face should have at most two incident edge.
   * The other edge, if it exist, is not deleted; however it will no longer be incident
   * to any cell and should be deleted explicitely.
   * If no edge to keep is provided, the face must not have any incident edge (return E_FAIL in this case).
   * 
   * The face is deleted during the collapse.
   * @param E
   *   The target edge which must be incident to the face.
   * @param F
   *   The face to collapse.
   */
  inline HRESULT CollapseFace (CATPolyEdge* E, CATPolyFace*& F);

  /**
   * Splits an edge given a curve vertex.
   * @param E
   *   The input edge which will be split.  
   *   This edge is deleted during the split.
   * @param cv
   *   The curve vertex where the edge will be split.
   * @param V
   *   The output vertex created during the split.
   * @param E1
   *   The first half of the edge created during the split.
   * @param E2
   *   The second half of the edge created during the split.
   */
  inline HRESULT SplitEdge (CATPolyEdge*& E, int cv, CATPolyVertex*& V, CATPolyEdge*& E1, CATPolyEdge*& E2);

  /**
   * Substitutes a surface-vertex line from an edge by another.
   */
  inline HRESULT Substitute (CATPolyFace& F, CATPolyEdge& E, CATIPolySurfaceVertexLine& svlOut, CATIPolySurfaceVertexLine& svlIn);

/** @} */


public:

/** @name Attributes
    @{ */

  /**
   * Returns the attributes of the CATPolyBody.
   * The object returned is owned by the CATPolyBody and should not be deleted.
   */
  inline const CATIPolyBodyAttributes* GetAttributes () const;

  /**
   * Returns the attributes of the CATPolyBody.
   * The object returned is owned by the CATPolyBody and should not be deleted.
   */
  inline CATIPolyBodyAttributes* GetAttributes ();

  /**
   * Returns the native CATPolyBody attributes if it is native.
   * Otherwise returns 0.
   */
  const CATPolyBodyNativeAttributes* GetNativeAttributes () const;

  /**
   * Returns the native CATPolyBody attributes if it is native.
   * Otherwise returns 0.
   */
  CATPolyBodyNativeAttributes* GetNativeAttributes ();

  /**
   * Returns the number of cells in the CATPolyBody.
   */
  inline unsigned int GetNbCells () const;

  /**
   * Returns the size in bytes of the CATPolyBody.
   * The size includes the size of all polyhedral objects and cache currently in memory and 
   * on which the CATPolyBody depends.  It does not however include the size of the external (non-polyhedral) objects 
   * such as for instance a CATRep or a CATBody associated to the CATPolyBody.
   */
  unsigned int SizeOf () const;

/** @} */

#ifndef DOXYGEN_SHOULD_SKIP_THIS

private:

  CATPolyDartList _Darts;
  CATPolyVertexList _Vertices;
  CATPolyEdgeList _Edges;
  CATPolyFaceList _Faces;
  CATPolyVolumeList* _Volumes;

  CATIPolyBodyAttributes* _Attributes;

private:

  unsigned int _NextCellTag;
  mutable unsigned int _Ref;

  static CATMutex& GetRefCountedMutex ();

  template<class DART> friend class CATPolyBodyDartIterator;
  friend class CATPolyBodyHelpers;
  friend class CATPolyCellOrbitComputer;
  friend class CATPolyBodyTopologyStreamer;
  friend class CATPolyBodyTopologyUnstreamer;
  friend CATPolyBody* Poly::NewEditableBody (const CATPolyBody& iPolyBody);

public:

  /**
   * @nodoc
   * To create an instance of a CATPolyBody, use CATPolyBody::New ().
   */
  CATPolyBody ();  // Should be private.

  /**
   * @nodoc
   */
  HRESULT GetAttributes (CATIPolyBodyAttributes*& oAttributes) const;

private:

  CATPolyBody (bool iWithVolumes);
  ~CATPolyBody (); // DO NOT VIRTUALIZE

  inline unsigned int GetCellTag () const;  // Reserved for CATPolyBodyTopologyStreamer.
  inline void SetCellTag (unsigned int tag);  // Reserved for CATPolyBodyTopologyUnstreamer.

  template<class DART>
  DART* NewDart ();

  template<class DART>
  DART* NewDart (CATIPolyPoint& p);

  template<class DART>
  HRESULT DeleteDart (DART*& ioDart);

  template<class DART>
  CATPolyVertex* MakeVertexP (CATIPolyPoint& P);

  template<class DART>
  CATPolyVertex* MakeVertexP (const CATPolyPseudoManifoldVertex& iPMV);

  // Removes the pseudo-manifold vertex and deletes its dart.
  template<class DART>
  HRESULT DeletePseudoManifoldVertex (CATPolyVertex& V, DART*& d);

  template<class DART>
  HRESULT DeleteVertexP (CATPolyVertex*& V);

  template<class DART>
  HRESULT VertexAddPointP (CATPolyVertex& V, CATIPolyPoint& P);

  template<class DART>
  CATPolyEdge* MakeEdgeP (CATPolyVertex& V0, CATPolyVertex& V1, CATIPolyCurve& C);

  template<class DART>
  CATPolyEdge* MakeEdgeP (CATPolyVertex& V, CATIPolyCurve& C);

  template<class DART>
  CATPolyEdge* MakeEdgeP (CATIPolyCurve& C);

  template<class DART>
  CATPolyEdge* MakeEdgeP (CATPolyVertex& StartVertex, CATPolyEdge* PreviousEdge,
    CATPolyVertex& EndVertex, CATPolyEdge* NextEdge,
    CATIPolyCurve& C);

  template<class DART>
  CATPolyEdge* MakeEdgeP (const CATPolyManifoldEdge& iME);

  template<class DART>
  CATPolyEdge* MakeEdgeP (CATIPolyCurve& C, DART& D0, DART& D1);

  // Removes the manifold edge and deletes its darts.
  template<class DART>
  HRESULT DeleteManifoldEdge (CATPolyEdge& E, DART*& d0, DART*& d1);

  template<class DART>
  HRESULT DeleteEdgeP (CATPolyEdge*& E);

  template<class DART>
  HRESULT FaceAddEdgeP (CATPolyFace& F,
                        CATPolyEdge* iPreviousEdge, CATPolyEdge& E, CATPolyEdge* iNextEdge,
                        CATIPolySurfaceVertexLine& SVL, CATPolyFace** iAdjacentFace);

  template<class DART>
  HRESULT FaceAddEdgeP (CATPolyFace& F,
                        CATPolyEdge* iPreviousEdge, CATPolyEdge& E, CATPolyEdge* iNextEdge,
                        CATPolyVertex * v0, CATPolyVertex * v1,
                        CATIPolySurfaceVertexLine& SVL, CATPolyFace** iAdjacentFace);

  template<class DART>
  HRESULT FaceAddEdgeP (CATPolyFace& F, CATPolyEdge& E, CATIPolySurfaceVertexLine& SVL, DART& D0, DART& D1,
                        bool addOrbit01, CATPolyFace** iAdjacentFace = 0);

  template<class DART>
  HRESULT FaceRemoveEdgeP (CATPolyFace& F, CATPolyEdge& E, DART*& d0, DART*& d1,
                           CATPolyPseudoManifoldVertex& PMV0, CATPolyPseudoManifoldVertex& PMV1);

  template<class DART>
  HRESULT DeleteFaceP (CATPolyFace*& F);

  template<class DART>
  CATPolyVertex* MakeFaceVertexP (CATPolyFace& F, CATIPolySurfaceVertex& P);

  template<class DART>
  CATPolyEdge* MakeFaceEdgeP (CATPolyFace& F,
    CATPolyVertex& StartVertex, CATPolyVertex& EndVertex, CATIPolySurfaceVertexLine& SVL);

  template<class DART>
  CATPolyEdge* MakeFaceEdgeP (CATPolyFace& F,
    CATPolyVertex& StartVertex, CATPolyEdge* PreviousEdge,
    CATPolyVertex& EndVertex, CATPolyEdge* NextEdge,
    CATIPolySurfaceVertexLine& SVL);

  template<class DART>
  HRESULT FaceAddVertexP (CATPolyFace& F, CATPolyVertex& V, CATIPolySurfaceVertex& P);

  // Buggy version.
  template<class DART>
  HRESULT FaceAddVertexV1 (CATPolyFace& F, CATPolyVertex& V, CATIPolySurfaceVertex& P);

  // Correct version.
  template<class DART>
  HRESULT FaceAddVertexV2 (CATPolyFace& F, CATPolyVertex& V, CATIPolySurfaceVertex& P);

  template<class DART>
  HRESULT FaceRemoveVertexP (CATPolyFace& F, CATPolyVertex& V, CATIPolySurfaceVertex& P);

  // To be replaced by FaceAddEdgeV2.
  template<class DART>
  HRESULT FaceAddEdgeV1 (CATPolyFace& F, CATPolyEdge& E, CATIPolySurfaceVertexLine& SVL);

  template<class DART>
  HRESULT FaceAddEdgeV2 (CATPolyFace& F, CATPolyEdge& E, CATIPolySurfaceVertexLine& SVL, CATPolyVolume* VLM);

  template<class DART>
  HRESULT FaceRemoveEdgeP (CATPolyFace& F, CATPolyEdge& E, CATIPolySurfaceVertexLine& SVL);

  HRESULT VolumeAddFaceOrbit (CATPolyVolume& iVolume, CATPolyFaceOrbit& iOrbit, int orientation);

  HRESULT VolumeSewFaceOrbit (CATPolyVolume& iVolume, CATPolyFaceOrbit& iOrbit, int orientation);

  template<class DART>
  HRESULT FindFaceOrbitsP ();

  inline HRESULT FindFaceOrbits ();

  template<class DART>
  HRESULT CollapseFaceP (CATPolyEdge* E, CATPolyFace*& F);

  template<class DART>
  HRESULT MergeGeometry (CATPolyVertex& V0, CATPolyVertex& V1);

  template<class DART>
  HRESULT AddFacesAdjacencyP (CATPolyFace& face0,
    CATPolyFace& face1,
    CATPolyEdge& edge);

  template<class DART>
  HRESULT MergeVerticesP (CATPolyVertex *& V0, CATPolyVertex *& V1, CATPolyEdge *& E);

  template<class DART>
  HRESULT SplitEdgeP (CATPolyEdge*& E, int cv, CATPolyVertex*& V, CATPolyEdge*& E1, CATPolyEdge*& E2);

  template<class DART>
  HRESULT SubstituteP (CATPolyFace& F, CATPolyEdge& E, CATIPolySurfaceVertexLine& svlOut, CATIPolySurfaceVertexLine& svlIn);

#endif

};

inline unsigned int CATPolyBody::GetCellTag () const
{
  return _NextCellTag;
}

inline void CATPolyBody::SetCellTag (unsigned int tag)
{
  _NextCellTag = tag;
}

inline bool CATPolyBody::IsNative () const
{
  return GetNativeAttributes () != 0;
}

inline bool CATPolyBody::WithVolumes () const
{
  return _Volumes != 0;
}

inline const CATIPolyBodyAttributes* CATPolyBody::GetAttributes () const
{
  return _Attributes;
}

inline CATIPolyBodyAttributes* CATPolyBody::GetAttributes ()
{
  return _Attributes;
}

inline unsigned int CATPolyBody::GetNbVertices () const
{
  return _Vertices.Size ();
}

inline unsigned int CATPolyBody::GetNbEdges () const
{
  return _Edges.Size ();
}

inline unsigned int CATPolyBody::GetNbFaces () const
{
  return _Faces.Size ();
}

inline unsigned int CATPolyBody::GetNbVolumes () const
{
  return _Volumes ? _Volumes->Size () : 0;
}

inline unsigned int CATPolyBody::GetNbCells () const
{
  return GetNbVertices () + GetNbEdges () + GetNbFaces () + GetNbVolumes ();
}

inline CATPolyVertex* CATPolyBody::GetVertex (int v) const
{
  return v <= _Vertices.Size () ? _Vertices[v] : 0;
}

inline CATPolyEdge* CATPolyBody::GetEdge (int e) const
{
  return e <= _Edges.Size () ? _Edges[e] : 0;
}

inline CATPolyFace* CATPolyBody::GetFace (int f) const
{
  return f <= _Faces.Size () ? _Faces[f] : 0;
}

inline CATPolyVolume* CATPolyBody::GetVolume (int v) const
{
  return _Volumes && v <= _Volumes->Size () ? (*_Volumes)[v] : 0;
}

inline CATPolyVertex* CATPolyBody::MakeVertex (CATIPolyPoint& P)
{
  return !WithVolumes () ? MakeVertexP<CATPolyDart2> (P) : MakeVertexP<CATPolyDart3> (P);
}

inline CATPolyVertex* CATPolyBody::MakeVertex (const CATPolyPseudoManifoldVertex& iPMV)
{
  return !WithVolumes () ? MakeVertexP<CATPolyDart2> (iPMV) : MakeVertexP<CATPolyDart3> (iPMV);
}

inline HRESULT CATPolyBody::DeleteVertex (CATPolyVertex*& V)
{
  return !WithVolumes () ? DeleteVertexP<CATPolyDart2> (V) : DeleteVertexP<CATPolyDart3> (V);
}

inline HRESULT CATPolyBody::VertexAddPoint (CATPolyVertex& V, CATIPolyPoint& P)
{
  return !WithVolumes () ? VertexAddPointP<CATPolyDart2> (V, P) : VertexAddPointP<CATPolyDart3> (V, P);
}

inline CATPolyEdge* CATPolyBody::MakeEdge (CATPolyVertex& V0, CATPolyVertex& V1, CATIPolyCurve& C)
{
  return !WithVolumes () ? MakeEdgeP<CATPolyDart2> (V0, V1, C) : MakeEdgeP<CATPolyDart3> (V0, V1, C);
}

inline CATPolyEdge* CATPolyBody::MakeEdge (CATPolyVertex& V, CATIPolyCurve& C)
{
  return !WithVolumes () ? MakeEdgeP<CATPolyDart2> (V, C) : MakeEdgeP<CATPolyDart3> (V, C);
}

inline CATPolyEdge* CATPolyBody::MakeEdge (CATIPolyCurve& C)
{
  return !WithVolumes () ? MakeEdgeP<CATPolyDart2> (C) : MakeEdgeP<CATPolyDart3> (C);
}

inline CATPolyEdge* CATPolyBody::MakeEdge (CATPolyVertex& StartVertex, CATPolyEdge* PreviousEdge,
  CATPolyVertex& EndVertex, CATPolyEdge* NextEdge,
  CATIPolyCurve& C)
{
  return !WithVolumes () ? MakeEdgeP<CATPolyDart2> (StartVertex, PreviousEdge, EndVertex, NextEdge, C) : 
                           MakeEdgeP<CATPolyDart3> (StartVertex, PreviousEdge, EndVertex, NextEdge, C);
}

inline CATPolyEdge* CATPolyBody::MakeEdge (const CATPolyManifoldEdge& iME)
{
  return !WithVolumes () ? MakeEdgeP<CATPolyDart2> (iME) : MakeEdgeP<CATPolyDart3> (iME);
}

inline HRESULT CATPolyBody::DeleteEdge (CATPolyEdge*& E)
{
  return !WithVolumes () ? DeleteEdgeP<CATPolyDart2> (E) : DeleteEdgeP<CATPolyDart3> (E);
}

inline HRESULT CATPolyBody::DeleteFace (CATPolyFace*& F)
{
  return !WithVolumes () ? DeleteFaceP<CATPolyDart2> (F) : DeleteFaceP<CATPolyDart3> (F);
}

inline CATPolyVertex* CATPolyBody::MakeFaceVertex (CATPolyFace& F, CATIPolySurfaceVertex& P)
{
  return !WithVolumes () ? MakeFaceVertexP<CATPolyDart2> (F, P) : MakeFaceVertexP<CATPolyDart3> (F, P);
}

inline CATPolyEdge* CATPolyBody::MakeFaceEdge (CATPolyFace& F,
  CATPolyVertex& StartVertex, CATPolyVertex& EndVertex, CATIPolySurfaceVertexLine& SVL)
{
  return !WithVolumes () ? 
    MakeFaceEdgeP<CATPolyDart2> (F, StartVertex, EndVertex, SVL) : MakeFaceEdgeP<CATPolyDart3> (F, StartVertex, EndVertex, SVL);
}

CATPolyEdge* CATPolyBody::MakeFaceEdge (CATPolyFace& F,
  CATPolyVertex& StartVertex, CATPolyEdge* PreviousEdge,
  CATPolyVertex& EndVertex, CATPolyEdge* NextEdge,
  CATIPolySurfaceVertexLine& SVL)
{
  return !WithVolumes () ?
    MakeFaceEdgeP<CATPolyDart2> (F, StartVertex, PreviousEdge, EndVertex, NextEdge, SVL) : 
    MakeFaceEdgeP<CATPolyDart3> (F, StartVertex, PreviousEdge, EndVertex, NextEdge, SVL);
}

inline HRESULT CATPolyBody::FaceAddVertex (CATPolyFace& F, CATPolyVertex& V, CATIPolySurfaceVertex& P)
{
  return !WithVolumes () ? FaceAddVertexP<CATPolyDart2> (F, V, P) : FaceAddVertexP<CATPolyDart3> (F, V, P);
}

inline HRESULT CATPolyBody::FaceRemoveVertex (CATPolyFace& F, CATPolyVertex& V, CATIPolySurfaceVertex& P)
{
  return !WithVolumes () ? FaceRemoveVertexP<CATPolyDart2> (F, V, P) : FaceRemoveVertexP<CATPolyDart3> (F, V, P);
}

inline HRESULT CATPolyBody::FaceAddEdge (CATPolyFace& F, CATPolyEdge& E, CATIPolySurfaceVertexLine& SVL)
{
  return !WithVolumes () ? 
    FaceAddEdgeV1<CATPolyDart2> (F, E, SVL) : 
    FaceAddEdgeV1<CATPolyDart3> (F, E, SVL);
}

inline HRESULT CATPolyBody::FaceAddEdge (CATPolyFace& F,
  CATPolyEdge* iPreviousEdge, CATPolyEdge& E, CATPolyEdge* iNextEdge,
  CATIPolySurfaceVertexLine& SVL)
{
  return !WithVolumes () ?
    FaceAddEdgeP<CATPolyDart2> (F, iPreviousEdge, E, iNextEdge, SVL, 0) :
    FaceAddEdgeP<CATPolyDart3> (F, iPreviousEdge, E, iNextEdge, SVL, 0);
}

inline HRESULT CATPolyBody::FaceAddEdge (CATPolyFace& F,
  CATPolyEdge* iPreviousEdge, CATPolyEdge& E, CATPolyEdge* iNextEdge,
  CATIPolySurfaceVertexLine& SVL, CATPolyFace* iAdjacentFace)
{
  return !WithVolumes () ?
    FaceAddEdgeP<CATPolyDart2> (F, iPreviousEdge, E, iNextEdge, SVL, &iAdjacentFace) :
    FaceAddEdgeP<CATPolyDart3> (F, iPreviousEdge, E, iNextEdge, SVL, &iAdjacentFace);
}

inline HRESULT CATPolyBody::FaceRemoveEdge (CATPolyFace& F, CATPolyEdge& E, CATIPolySurfaceVertexLine& SVL)
{
  return !WithVolumes () ?
    FaceRemoveEdgeP<CATPolyDart2> (F, E, SVL) :
    FaceRemoveEdgeP<CATPolyDart3> (F, E, SVL);
}

inline HRESULT CATPolyBody::FindFaceOrbits ()
{
  return !WithVolumes () ? 
    FindFaceOrbitsP<CATPolyDart2> () : 
    FindFaceOrbitsP<CATPolyDart3> ();
}

inline HRESULT CATPolyBody::CollapseFace (CATPolyEdge* E, CATPolyFace*& F)
{
  return !WithVolumes () ? 
    CollapseFaceP<CATPolyDart2> (E, F) : 
    CollapseFaceP<CATPolyDart3> (E, F);
}

inline HRESULT CATPolyBody::SplitEdge (CATPolyEdge*& E, int cv, CATPolyVertex*& V, CATPolyEdge*& E1, CATPolyEdge*& E2)
{
  return !WithVolumes () ? 
    SplitEdgeP<CATPolyDart2> (E, cv, V, E1, E2) : 
    SplitEdgeP<CATPolyDart3> (E, cv, V, E1, E2);
}

inline HRESULT CATPolyBody::Substitute (CATPolyFace& F, CATPolyEdge& E, CATIPolySurfaceVertexLine& svlOut, CATIPolySurfaceVertexLine& svlIn)
{
  return !WithVolumes () ? 
    SubstituteP<CATPolyDart2> (F, E, svlOut, svlIn) : 
    SubstituteP<CATPolyDart3> (F, E, svlOut, svlIn);
}

inline HRESULT CATPolyBody::AddFacesAdjacency (CATPolyFace& face0,
  CATPolyFace& face1,
  CATPolyEdge& edge)
{
  return !WithVolumes () ? 
    AddFacesAdjacencyP<CATPolyDart2> (face0, face1, edge) : 
    AddFacesAdjacencyP<CATPolyDart3> (face0, face1, edge);
}
