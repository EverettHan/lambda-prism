//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 2006
//==============================================================================================================
// File: CATICldPolygon.h
//==============================================================================================================
// Creation: JLH - 30-Jun-2006
//==============================================================================================================

#ifndef CATICldPolygon_h
#define CATICldPolygon_h

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATICldCell.h"

#include "CATBooleanDef.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATICldPolygon ;
#else
extern "C" const IID IID_CATICldPolygon ;
#endif

/**
 * Interface for the entity <tt>CATICldPolygon</tt>.<br>
 * The <tt>CATICldPolygon</tt> corresponds to the tessellation of a cloud of points.<br>
 * @see CATICldGenEntity, CATICldCell
 */
class ExportedByCATGMGeometricInterfaces CATICldPolygon : public CATICldCell
{
  CATDeclareInterface ;
public:

  /**
   * Returns the number of triangles.
   *
   * @return
   * The number of triangles.
   */
  virtual int GetNbTriangles() const = 0 ;

  /**
   * Adds a triangle given by the indices of its vertices.
   *
   * @param iNoVertices
   * The vertices indices of the triangle to add.
   * They should be in the range [1,GetNbPoints()]
   *
   * @return
   * If positive, the index of the added triangle (the first is equal to 1).
   * If null or negative, the triangle was not added.
   */
  virtual int AddTriangle (const int iNoVertices[3]) = 0 ;

  /**
   * Removes the iNoTriangle'th triangle.
   * CAUTION: The subsequent calls of the method GetTriangle will return null numbers for the vertices
   * and neighbouring triangles.
   *
   * @param iNoTriangle
   * The index of the triangle to remove.
   * It should be in the range [1,GetNbTriangles()]
   */
  virtual void RemoveTriangle (const int iNoTriangle) = 0 ;

  /**
   * Updates the vertices of the iNoTriangle'th triangle.
   * This method consists of removing the given triangle and adds a new one in place.
   *
   * @param iNoTriangle
   * The index of the triangle to update.
   * It should be in the range [1,GetNbTriangles()].
   *
   * @param iNoVertices
   * The new vertices indices of the triangle to update.
   * They should be in the range [1,GetNbPoints()]
   */
  virtual void UpdateTriangle (const int iNoTriangle,
                               const int iNoVertices[3]) = 0 ;

  /**
   * Tests if the iNoTriangle'th triangle is valid ie is not removed or each of its vertices indices is not null.
   *
   * @param iNoTriangle
   * The index of the triangle to check.
   * It should be in the range [1,GetNbTriangles()].
   *
   * @return
   * TRUE if the triangle is valid, FALSE otherwise.
   */
  virtual CATBoolean IsTriangleValid (const int iNoTriangle) const = 0 ;

  /**
   * Returns the vertices, the neighbouring triangles and the orientation of the iNoTriangle'th triangle.
   *
   * @param iNoTriangle
   * The index of the triangle.
   * It should be in the range [1,GetNbTriangles()].
   *
   * @param oNoVertices
   * The indices of the vertices defining the triangle.
   * They are in the range [1,GetNbPoints()]
   * CAUTION: If one of oNoVertices is null means that the triangle is not valid (removed).
   *
   * @param oNoConnexes
   * The indices of the connected triangles.
   * They are in the range [1,GetNbTriangles()]
   * The connectivity between triangles is computed by the EndOfCreation or EndOfModification methods thanks
   * to the vertices indices.
   * The coding is as shown hereafter:
   *  o  oNoConnexes[0] gives the neighbouring triangle index along the edge (oNoVertices[0],oNoVertices[1])
   *  o  oNoConnexes[1] .................................................... (oNoVertices[1],oNoVertices[2])
   *  o  oNoConnexes[2] .................................................... (oNoVertices[2],oNoVertices[0])
   *  o  If oNoConnexes[i] equals to 0, there is no neighbouring triangle ie. it is a free edge.
   *
   * @param oDirect
   * TRUE, if the triangle is oriented as the majority, FALSE, otherwise.
   * This flag is computed by the EndOfCreation or EndOfModification methods:
   *  o  The first valid triangle is considered as direct.
   *  o  The valid connected triangles are oriented by propagation, in relation to the first valid triangle.
   *  o  At the end, the population in the majority is considered as direct and so defines the global orientation
   *     of the whole mesh.
   *  o  CAUTION: If the mesh is not orientable, this flag could be not significant.
   */
  virtual void GetTriangle (const int   iNoTriangle,
                            int         oNoVertices[3],
                            int         oNoConnexes[3],
                            CATBoolean &oDirect) const = 0 ;

  /**
   * Returns the fact that the mesh could be assumed as a manifold surface,
   * ie each edge is shared by no more than two triangles.
   * This fact is determined by the EndOfCreation or EndOfModification methods.
   *
   * @return
   * TRUE, if the mesh is a manifold surface, FALSE otherwise.
   */
  virtual CATBoolean IsManifold() const = 0 ;

  /**
   * Returns the fact that the mesh could be assumed as an orientable surface.
   * This fact is determined by the EndOfCreation or EndOfModification methods.
   *
   * @return
   * TRUE, if the mesh is an orientable surface, FALSE otherwise.
   */
  virtual CATBoolean IsOrientable() const = 0 ;

  /**
   * Returns the fact that the mesh could be assumed as a closed surface.
   * This fact is determined by the EndOfCreation or EndOfModification methods.
   *
   * @return
   * TRUE, if the mesh is a closed surface, FALSE otherwise.
   */
  virtual CATBoolean IsClosed() const = 0 ;

} ;

CATDeclareHandler (CATICldPolygon, CATICldCell) ;

#endif
