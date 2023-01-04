// COPYRIGHT DASSAULT SYSTEMES 2014, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMeshServices.h
//
//===================================================================
// February 2014  Creation: NDO
//===================================================================
#ifndef CATPolyMeshServices_H
#define CATPolyMeshServices_H

#include "PolyhedralUtilities.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"

/** @file 
 * Global services about CATIPolyMesh.
 *
 * @see CATPolySurfaceServices.h
 * @see CATPolySurfaceBarServices.h
*/

class CATIPolyMesh;
class CATIPolySurfaceVertexFacetNeighborhood;
class CATIPolySurfaceVertexCellConstLayer;
class CATIPolySurfaceVertexPositionConstLayer;
class CATIPolySurfaceVertexNormalConstLayer;
class CATPolyMeshPointDef;
class CATMathPoint;
class CATMathVector;


/** @name Triangle Queries
    @{ */

/**
 * Given three vertices of a CATIPolyMesh returns a triangle referencing these three vertices.
 * @param iPolyMesh
 *   The input mesh.
 * @param iVertexNeighborhood
 *   The input vertex facet neighborhood to accelerate the query.
 * @param v0, v1, v2
 *   The three input vertices.
 * @param t
 *   The output triangle defined by these three vertices.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if a triangle referencing the three input vertices is returned.
 *   <li> <tt>S_FALSE</tt> if no triangle is referencing the three input vertices.
 *   <li> <tt>E_FAIL</tt> if an error occurs.
 * </ul>
 */
ExportedByPolyhedralUtilities HRESULT CATPolyGetTriangle (const CATIPolyMesh& iPolyMesh, const CATIPolySurfaceVertexFacetNeighborhood& iVertexNeighborhood,
                                                          const int v0, const int v1, const int v2, int& t);

/** @} */


/** @name Vertex Queries
    @{ */

/**
 * Given two triangles from a mesh or distinct meshes, counts the number of vertices shared by the two triangles.
 * @param iMesh0
 *   The mesh to which Triangle t0 belongs.
 * @param t0
 *   The first triangle.
 * @param iMesh1
 *   The mesh to which Triangle t1 belongs.
 * @param t1
 *   The second triangle.
 * @param iCellLayer0
 *   An optional surface vertex cell layer for Mesh 0.
 * @param iCellLayer1
 *   An optional surface vertex cell layer for Mesh 1.
 * @return
 *   The number of shared vertices.
 */
ExportedByPolyhedralUtilities unsigned int CATPolyCountSharedVertices (const CATIPolyMesh& iMesh0, const int t0,
                                                                       const CATIPolyMesh& iMesh1, const int t1,
                                                                       const CATIPolySurfaceVertexCellConstLayer* iCellLayer0 = 0, 
                                                                       const CATIPolySurfaceVertexCellConstLayer* iCellLayer1 = 0);

/**
 * Computes the position of a mesh point.
 * @param iPositionLayer
 *   The position layer of the mesh.
 * @param iMeshPoint
 *   The definition of the mesh-point.
 * @param oPosition
 *   The computed position of the mesh-point.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if the position has been successfully computed.
 *   <li> <tt>E_FAIL</tt> if an error occurs.
 * </ul>
 */
ExportedByPolyhedralUtilities HRESULT CATPolyComputePosition (const CATIPolySurfaceVertexPositionConstLayer& iPositionLayer,
                                                              const CATPolyMeshPointDef& iMeshPoint,
                                                              CATMathPoint& oPosition);

/**
 * Computes the normal of a mesh point.
 * @param iNormalLayer
 *   The normal layer of the mesh.
 * @param iMeshPoint
 *   The definition of the mesh-point.
 * @param oNormal
 *   The computed normal of the mesh-point.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if the normal has been successfully computed.
 *   <li> <tt>E_FAIL</tt> if an error occurs.
 * </ul>
 */
ExportedByPolyhedralUtilities HRESULT CATPolyComputeNormal (const CATIPolySurfaceVertexNormalConstLayer& iNormalLayer,
                                                            const CATPolyMeshPointDef& iMeshPoint,
                                                            CATMathVector& oNormal);

/**
 * Computes the normal at a vertex of a mesh given a position layer and a neighborhood.
 * This method does compute the normal from the triangles adjacent to the vertex.
 * @param iPositionLayer
 *   The position layer of the mesh.
 * @param iVertexNeighborhood
 *   The vertex-nighborhood layer of the mesh.
 * @param v
 *   The index of the vertex.
 * @param oNormal
 *   The computed normal at the mesh-vertex.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if the normal has been successfully computed.
 *   <li> <tt>S_FALSE</tt> if a normal cannot be computed at the vertex (no adjacent triangles.)
 *   <li> <tt>E_FAIL</tt> if an error occurs.
 * </ul>
 */
//ExportedByPolyhedralUtilities HRESULT CATPolyComputeNormal (const CATIPolyMesh& mesh,
                                                            //const CATIPolySurfaceVertexPositionConstLayer& iPositionLayer,
                                                            //const CATIPolySurfaceVertexFacetNeighborhood& iVertexNeighborhood,
                                                            //const int v,
                                                            //CATMathVector& oNormal);

/** @} */

#endif // !CATPolyMeshServices_H
