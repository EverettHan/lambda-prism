// COPYRIGHT DASSAULT SYSTEMES 2013, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyDefaultMeshServices.h
//
//===================================================================
// September 2013  Creation: NDO
//===================================================================
#ifndef CATPolyDefaultMeshServices_H
#define CATPolyDefaultMeshServices_H

#include "PolyMeshTools.h"
#include "CATErrorDef.h"

#include "CATListOfInt.h"

/** @file 
 * Default services that can be applied to CATIPolyMesh.
 * These services are implemented in PolyhedralObjects.
 *
 * @see CATPolyDefaultSurfaceServices
 * @see CATPolyServices.h
*/

class CATIPolyMesh;
class CATIPolySurfaceVertexFacetNeighborhood;
class CATIPolySurfaceVertexPositionConstLayer;
class CATIPolyVertexPositionConstLayer;
class CATMathPoint;
class CATMathVector;
class CATPolyMeshPointDef;
class CATSetOfInt;

/**
 * Adds arrays of vertices and triangles to a CATIPolyMesh instance.
 * @param mesh
 *   The CATIPolyMesh instance.
 * @param iNbVertices
 *   The number of vertices to add.
 * @param iCoords
 *   The coordinates of the vertices to add (three coordinates per vertex.)
 *   The size of this buffer should be 3 x iNbVertices.
 * @param iNbTriangles
 *   The number of triangles to add.
 * @param iIdxVertices
 *   The indices of the vertices to add.
 *   The size of this buffer should be 3 x iNbTriangles.
 * @param iStride
 *   A stride of 1 (default) means the indices address vertices (needs to be x3 to address the coordinates in iCoords.)
 *   A stride of 3 means the indices in this array address directly the coordinates of the vertices of the triangles.
 */
ExportedByPolyMeshTools HRESULT CATPolyDefaultAddTriangles (CATIPolyMesh& mesh,
                                                            unsigned int iNbVertices, const double* iCoords, unsigned int iNbTriangles, const int* iIdxVertices,
                                                            unsigned int iStride = 1);


/**
 * Given a vertex and an iterator through all triangles adjacent to this vertex, checks whether the vertex is manifold.
 * This is a combinatorial check regardless of the triangle orientations.
 * @param mesh
 *   The input mesh.
 * @param v
 *   The index of the vertex to test.
 * @param triangles
 *   A list of triangles around the vertex v.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if the vertex is manifold.
 *   <li> <tt>S_FALSE</tt> if the vertex is non-manifold.
 *   <li> <tt>E_FAIL</tt> if an error occurs.
 * </ul>
 */
ExportedByPolyMeshTools HRESULT CATPolyDefaultIsVertexManifold (const CATIPolyMesh& mesh, const int v, const CATListOfInt& triangles);
//ExportedByPolyMeshTools HRESULT CATPolyDefaultIsVertexManifold (const CATIPolyMesh& mesh, const int v, CATPolyIndexIterator& triangles);


/**
 * Given a vertex and a surface vertex neighborhood of a triangular mesh, checks whether the vertex is on a boundary or not.
 * This is a combinatorial check regardless of the triangle orientations.
 * A vertex is on a boundary, if one of its adjacent bar is a boundary-bar.
 * @param mesh
 *   The input mesh.
 * @param iNeighborhood
 *   The surface vertex neighborhood.
 * @param v
 *   The index of the vertex to test.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if the vertex is on a boundary.
 *   <li> <tt>S_FALSE</tt> if the vertex is not on a boundary.
 *   <li> <tt>E_FAIL</tt> if an error occurs.
 * </ul>
 */
ExportedByPolyMeshTools HRESULT CATPolyDefaultIsBoundaryVertex (const CATIPolyMesh& mesh, const CATIPolySurfaceVertexFacetNeighborhood& iNeighborhood, const int v);


/**
 * Given a bar defined by two surface vertices and a surface vertex neighborhood of a triangular mesh, 
 * checks whether the bar is on a boundary or not.
 * This is a combinatorial check regardless of the triangle orientations.
 * @param mesh
 *   The input mesh.
 * @param iNeighborhood
 *   The surface vertex neighborhood.
 * @param v0
 *   The index of the start vertex of the bar.
 * @param v1
 *   The index of the end vertex of the bar.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if the bar is a boundary bar.
 *   <li> <tt>S_FALSE</tt> if the bar is not a boundary bar.
 *   <li> <tt>E_FAIL</tt> if an error occurs.
 * </ul>
 */
ExportedByPolyMeshTools HRESULT CATPolyDefaultIsBoundaryBar (const CATIPolyMesh& mesh, const CATIPolySurfaceVertexFacetNeighborhood& iNeighborhood, 
                                                             const int v0, const int v1);


/**
 * Fetches the coordinates of a vertex on a triangular mesh.
 * The point whose coordinates are returned is on the mesh (it cannot be
 * an isolated vertex.)
 * @param mesh
 *   The input mesh.
 * @param P
 *   The point whose coordinates are set with those of the vertex.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if the coordinates of a vertex are successfully set.
 *   <li> <tt>S_FALSE</tt> if the surface does not contain any vertex.
 *   <li> <tt>E_FAIL</tt> if an error occurs.
 * </ul>
 */
ExportedByPolyMeshTools HRESULT CATPolyDefaultGetPointOnMesh (const CATIPolyMesh& mesh, CATMathPoint& P);


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
// Should be migrated to CATPolyMeshServices.h.
ExportedByPolyMeshTools HRESULT CATPolyComputeNormal (const CATIPolyMesh& mesh,
                                                      const CATIPolySurfaceVertexPositionConstLayer& iPositionLayer,
                                                      const CATIPolySurfaceVertexFacetNeighborhood& iVertexNeighborhood,
                                                      const int v,
                                                      CATMathVector& oNormal);

/**
 * Computes the normal at a mesh-point of a mesh given a position layer and a neighborhood.
 * This method does compute the normal from the triangles adjacent to the vertices of the triangle (from the mesh-point)
 * @param iPositionLayer
 *   The position layer of the mesh.
 * @param iVertexNeighborhood
 *   The vertex-nighborhood layer of the mesh.
 * @param iMeshPoint
 *   The mesh point.
 * @param oNormal
 *   The computed normal at the mesh-point.
 * @return
 * <ul>
 *   <li> <tt>S_OK</tt> if the normal has been successfully computed.
 *   <li> <tt>S_FALSE</tt> if a normal cannot be computed at the vertex (no adjacent triangles.)
 *   <li> <tt>E_FAIL</tt> if an error occurs.
 * </ul>
 */
// Should be migrated to CATPolyMeshServices.h.
ExportedByPolyMeshTools HRESULT CATPolyComputeNormal (const CATIPolyMesh& mesh,
                                                      const CATIPolySurfaceVertexPositionConstLayer& iPositionLayer,
                                                      const CATIPolySurfaceVertexFacetNeighborhood& iVertexNeighborhood,
                                                      const CATPolyMeshPointDef& iMeshPoint,
                                                      CATMathVector& oNormal);

/**
 * @nodoc
 * Generic implementation with few optimization.
 * Support non manifold mesh compared to some of the CATIPolySurfaceVertexFacetNeighborhood implementation
 */
ExportedByPolyMeshTools HRESULT CATPolyMeshGetFacetNeighborsOfFacet(const CATIPolyMesh                           & iPolyMesh      ,
                                                                    const CATIPolySurfaceVertexFacetNeighborhood & iFacetNeighb   ,
                                                                    const int                                      iIdTriangle    ,
                                                                          CATListOfInt                           & oNeighb        ,
                                                                          CATSetOfInt                            & ioTamponSet    ,
                                                                          CATListOfInt                             ioTamponList[3]);


/**
 * @nodoc
 * Generic implementation (if idTriangle can't equal 0) with few optimization
 * Support non manifold bars
 */
ExportedByPolyMeshTools HRESULT CATPolyMeshGetFacetNeighborsOfBar(const CATIPolyMesh                           & iPolyMesh      ,
                                                                  const CATIPolySurfaceVertexFacetNeighborhood & iFacetNeighb   ,
                                                                  const int                                      iIdSV0         ,
                                                                  const int                                      iIdSV1         ,
                                                                        CATListOfInt                           & oNeighb        );

/**
 * Compute the area of a triangle
 */
ExportedByPolyMeshTools double CATPolyComputeTriangleArea(const int                                       iIdVertices[3],
                                                                CATIPolySurfaceVertexPositionConstLayer & iPosLayer     );

namespace Poly
{
  namespace ParentOrientation
  {
    enum 
    {
      eTriangleInverted = 1<<0,       /// The parent triangle are inverted
      eNormalVertexInverted = 1<<1,   /// The normal vertices are inverted
      eParentInverted = 0x3           /// Both parent triangle and normal vertices are inverted
    };
  };

  /**
   * Get the parent of a mesh (proxy, subMesh, editable, delta...)
   */
  ExportedByPolyMeshTools const CATIPolyMesh * GetParent(const CATIPolyMesh & iMesh);

  /**
  * true if the mesh is an editable mesh or not
  */
  ExportedByPolyMeshTools bool IsEditable(const CATIPolyMesh & iMesh);

  /**
   * true if the provided vertex index is comming from the parent
   * @oIdParent
   *  the real id of the parent. Might be different from iIdV.
   */
  ExportedByPolyMeshTools bool IsParentVertex(const CATIPolyMesh & iMesh, const int iIdV, int * oIdParent=NULL);

  /**
   * true if the provided vertex index is comming from the parent
   * @oIdParent
   *  the real id of the parent. Might be different from iIdV.
   */
  ExportedByPolyMeshTools bool IsParentTriangle(const CATIPolyMesh & iMesh, const int iIdT, int * oIdParent=NULL);

  /**
   * true if the parent triangles are flipped
   */
  ExportedByPolyMeshTools bool AreParentTrianglesFlipped(const CATIPolyMesh & iMesh);

  /**
   * true if the parent triangles are flipped
   */
  ExportedByPolyMeshTools bool AreParentVertexNormalFlipped(const CATIPolyMesh & iMesh);


  /**
   * Get the Origin parent of a delta mesh type (proxy, subMesh, editable, delta...)
   */
  ExportedByPolyMeshTools const CATIPolyMesh * GetOriginParent(const CATIPolyMesh & iMesh);

  /**
  * true if the origin parent is an editable mesh or not
  */
  ExportedByPolyMeshTools bool IsOriginEditable(const CATIPolyMesh & iMesh);

  /**
   * true if the origin parent is a persistent mesh of not (the path from iMesh is important - one persistent mesh leads to original persistency)
   */
  ExportedByPolyMeshTools bool IsOriginPersistent(const CATIPolyMesh& iMesh);

  /**
   * true if the provided vertex index is comming from the Origin parent
   * @oIdParent
   *  the real id of the parent. Might be different from iIdV.
   */
  ExportedByPolyMeshTools bool IsOriginParentVertex(const CATIPolyMesh & iMesh, const int iIdV, int * oIdParent=NULL);

  /**
  * true if the provided triangle index is comming from the Origin parent
  * @oIdParent
  *  the real id of the parent. Might be different from iIdV.
  */
  ExportedByPolyMeshTools bool IsOriginParentTriangle(const CATIPolyMesh & iMesh, const int iIdT, int * oIdParent = NULL);

  /**
 * true if the origin parent triangles are flipped
 */
  ExportedByPolyMeshTools bool AreOriginParentTrianglesFlipped(const CATIPolyMesh & iMesh);


  /**
   * true if the origin parent triangles are flipped
   */
  ExportedByPolyMeshTools bool AreOriginParentVertexNormalFlipped(const CATIPolyMesh & iMesh);

}



#endif
