//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 1999
//==============================================================================================================
// CATCldPolygon
//==============================================================================================================
// 07-Feb-2013 - JLH - Add an argument to GetPolyMesh to get iterators working only on the active vertices and
//                     triangles.
// 01-Sep-2009 - DNR - Add a method GetPolyMesh to delete the QueryInterface to get a CATIPolyMesh from a
//                     CATCldPolygon.
// ??-Oct-1999 - JLH - Creation
// 24-03-2014 CGMOFF+CGMPRJ
//==============================================================================================================

#ifndef CATCldPolygon_H
#define CATCldPolygon_H

/**
 * @CAA2Level L0
 * @CAA2Usage U0
 */ 

#include "CATCldUniCell.h"

#include "CATListOfCATCldCells.h"
#include "CATListOfInt.h"
#include "CATMathPoint.h"
#include "CATIACGMLevel.h"

class CATCldSetOfScans ;
class CATIPolyMesh ;

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATCldPolygon ;
#else
extern "C" const IID IID_CATCldPolygon ;
#endif

/**
 * Interface for the CloudEditor entity <tt>CATCldPolygon</tt>.<br>
 * The <tt>CATCldPolygon</tt> corresponds to the tessellation of a cloud of points.<br>
 * @see CATCldGenEntity, CATCldCell, CATCldUniCell
 */
class ExportedByCATGMGeometricInterfaces CATCldPolygon : public CATCldUniCell
{
  CATDeclareInterface ;

public:

//==============================================================================================================
// Specific points management for the CATCldPolygon.
//==============================================================================================================

  /**
   * Computes the normal to a point given by its relative indice in the <tt>CATCldPolygon</tt>.<br>
   * The normal is the normalized sum of the normals of each triangle having the given point as vertex.<br>
   * The normal of a triangle <tt>(V1,V2,V3)</tt> is the cross product "<tt>(V1V2)^(V1V3)</tt>".<br>
   * @param iNormalize
   * If <tt>TRUE</tt>, the normal of a triangle is normalized before being summed.<br>
   * <b>NB:</b> If this method is called several times consecutively, it is advised to call it
   * under the optimization context <tt>(OptimizeBegin,OptimizeEnd)</tt>.
   */
  virtual void ComputeVertexNormal (const int        iNoVertex,
                                    float            oNormal[3],
                                    const CATBoolean iNormalize = FALSE) const = 0 ;

  /**
   * Computes the normal to a point given by its relative indice in the <tt>CATCldPolygon</tt>.<br>
   * The normal is the normalized sum of the normals of each triangle having the given point as vertex.<br>
   * The normal of a triangle <tt>(V1,V2,V3)</tt> is the cross product "<tt>(V1V2)^(V1V3)</tt>".<br>
   * @param iNormalize
   * If <tt>TRUE</tt>, the normal of a triangle is normalized before being summed.<br>
   * <b>NB:</b> If this method is called several times consecutively, it is advised to call it
   * under the optimization context <tt>(OptimizeBegin,OptimizeEnd)</tt>.
   */
  virtual void ComputeVertexNormal (const int        iNoVertex,
                                    double           oNormal[3],
                                    const CATBoolean iNormalize = FALSE) const = 0 ;

  /**
   * Is the point given by its indice relative to the <tt>CATCldPolygon</tt> a vertex<br>
   * ie is it belonging to a triangle ?
   */
  virtual CATBoolean IsAVertex (const int iNoPoint) const = 0 ;

  /**
   * Gets the number of points which are vertices.
   */
  virtual int GetNbVertices () const = 0 ;

  /**
   * Gets the relative indices of the vertices.<br>
   * <b>CAUTION:</b> if <tt>ioNoVertices</tt> is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method if it is not <tt>NULL</tt> in case of no vertices.
   */
  virtual void GetVertices (int  &oNbVertices,
                            int* &ioNoVertices) const = 0 ;

//==============================================================================================================
// Triangles management.
//==============================================================================================================

  /**
   * Returns the fact that the <tt>CATCldPolygon</tt> could be assumed as a manifold surface,<br>
   * ie each edge is shared by no more than two triangles.<br>
   * This fact is determined by the <tt>EndOfModification</tt> method.
   */
  virtual CATBoolean IsManifold () const = 0 ;

  /**
   * Returns the fact that the <tt>CATCldPolygon</tt> could be assumed as an orientable surface.<br>
   * This fact is determined by the <tt>EndOfModification</tt> method.
   */
  virtual CATBoolean IsOrientable () const = 0 ;

  /**
   * Returns the fact that the <tt>CATCldPolygon</tt> could be assumed as a closed surface.<br>
   * This fact is determined by the <tt>EndOfModification</tt> method.
   */
  virtual CATBoolean IsClosed () const = 0 ;

  /**
   * Adds a triangle given by the relative indices of its vertices.
   */
  virtual void AddTriangle (const int iNoVertices[3]) = 0 ;

  /**
   * Adds several triangles given by the relative indices of their vertices.<br>
   * The <tt>ITri</tt>'th triangle is described by :<br>
   * <tt><ul>
   * <li>iNoVertices[3*ITri+0]
   * <li>iNoVertices[3*ITri+1]
   * <li>iNoVertices[3*ITri+2]
   * </ul></tt>
   */
  virtual void AddTriangles (const int  iNbTriangles,
                             const int* iNoVertices) = 0 ;

  /**
   * Adds several triangles given by the coordinates of their vertices.<br>
   * The <tt>ITri</tt>'th triangle is described by :
   * <tt><ul>
   * <li>iNoVertices[3*ITri+0]
   * <li>iNoVertices[3*ITri+1]
   * <li>iNoVertices[3*ITri+2]
   * </ul></tt>
   * Let be <tt>IVtx</tt> a relative vertex number such for instance
   * <tt>IVtx = iNoVertices[3*ITri+0]</tt>,
   * the coordinates of this vertex will be described by :
   * <tt><ul>
   * <li>iCoords[3*IVtx+0]
   * <li>iCoords[3*IVtx+1]
   * <li>iCoords[3*IVtx+2]
   * </ul></tt>
   */
  virtual void AddTriangles (const int    iNbVertices,
                             const float* iCoords,
                             const int    iNbTriangles,
                             const int*   iNoVertices) = 0 ;

  /**
   * Adds several triangles given by the coordinates of their vertices.<br>
   * The <tt>ITri</tt>'th triangle is described by :
   * <tt><ul>
   * <li>iNoVertices[3*ITri+0]
   * <li>iNoVertices[3*ITri+1]
   * <li>iNoVertices[3*ITri+2]
   * </ul></tt>
   * Let be <tt>IVtx</tt> a relative vertex number such for instance
   * <tt>IVtx = iNoVertices[3*ITri+0]</tt>,
   * the coordinates of this vertex will be described by :
   * <tt><ul>
   * <li>iCoords[3*IVtx+0]
   * <li>iCoords[3*IVtx+1]
   * <li>iCoords[3*IVtx+2]
   * </ul></tt>
   */
  virtual void AddTriangles (const int     iNbVertices,
                             const double* iCoords,
                             const int     iNbTriangles,
                             const int*    iNoVertices) = 0 ;

  /**
   * Adds several triangles given by the indexes in the <tt>CATCldSetOfPoints</tt> of their vertices.<br>
   * The <tt>ITri</tt>'th triangle is described by :
   * <tt><ul>
   * <li>iNoVertices[3*ITri+0]
   * <li>iNoVertices[3*ITri+1]
   * <li>iNoVertices[3*ITri+2]
   * </ul></tt>
   * Let be <tt>IVtx</tt> a relative vertex number such for instance
   * <tt>IVtx = iNoVertices[3*ITri+0]</tt>, the index of this vertex is <tt>iIndexes[IVtx]</tt>.<br>
   * <b>CAUTION:</b> It is assumed that there is not duplicated index in the array <tt>iIndexes</tt>.
   */
  virtual void AddTriangles (const int  iNbVertices,
                             const int* iIndexes,
                             const int  iNbTriangles,
                             const int* iNoVertices) = 0 ;

  /**
   * Adds a triangle given by the relative indices of its vertices and returns its indice.
   */
  virtual void AddTriangleNum (const int  iNoVertices[3],
                               int       &oNoTriangle) = 0 ;

  /**
   * Adds several triangles given by the relative indices of their vertices and returns their indices.<br>
   * The <tt>ITri</tt>'th triangle is described by :<br>
   * <tt><ul>
   * <li>iNoVertices[3*ITri+0]
   * <li>iNoVertices[3*ITri+1]
   * <li>iNoVertices[3*ITri+2]
   * </ul></tt>
   * <b>CAUTION:</b> If <tt>ioNoTriangles</tt> is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and its size must be at least <tt>iNbTriangles</tt>.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method.<br>
   */
  virtual void AddTrianglesNum (const int   iNbTriangles,
                                const int*  iNoVertices,
                                int*       &ioNoTriangles) = 0 ;

  /**
   * Adds several triangles given by the coordinates of their vertices and returns their indices.<br>
   * The <tt>ITri</tt>'th triangle is described by :
   * <tt><ul>
   * <li>iNoVertices[3*ITri+0]
   * <li>iNoVertices[3*ITri+1]
   * <li>iNoVertices[3*ITri+2]
   * </ul></tt>
   * Let be <tt>IVtx</tt> a relative vertex number such for instance
   * <tt>IVtx = iNoVertices[3*ITri+0]</tt>,
   * the coordinates of this vertex will be described by :
   * <tt><ul>
   * <li>iCoords[3*IVtx+0]
   * <li>iCoords[3*IVtx+1]
   * <li>iCoords[3*IVtx+2]
   * </ul></tt>
   * <b>CAUTION:</b> If <tt>ioNoTriangles</tt> is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and its size must be at least <tt>iNbTriangles</tt>.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method.<br>
   */
  virtual void AddTrianglesNum (const int     iNbVertices,
                                const float*  iCoords,
                                const int     iNbTriangles,
                                const int*    iNoVertices,
                                int*         &ioNoTriangles) = 0 ;

  /**
   * Adds several triangles given by the coordinates of their vertices and returns their indices.<br>
   * The <tt>ITri</tt>'th triangle is described by :
   * <tt><ul>
   * <li>iNoVertices[3*ITri+0]
   * <li>iNoVertices[3*ITri+1]
   * <li>iNoVertices[3*ITri+2]
   * </ul></tt>
   * Let be <tt>IVtx</tt> a relative vertex number such for instance
   * <tt>IVtx = iNoVertices[3*ITri+0]</tt>,
   * the coordinates of this vertex will be described by :
   * <tt><ul>
   * <li>iCoords[3*IVtx+0]
   * <li>iCoords[3*IVtx+1]
   * <li>iCoords[3*IVtx+2]
   * </ul></tt>
   * <b>CAUTION:</b> If <tt>ioNoTriangles</tt> is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and its size must be at least <tt>iNbTriangles</tt>.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method.<br>
   */
  virtual void AddTrianglesNum (const int      iNbVertices,
                                const double*  iCoords,
                                const int      iNbTriangles,
                                const int*     iNoVertices,
                                int*          &ioNoTriangles) = 0 ;

  /**
   * Adds several triangles given by the indexes in the <tt>CATCldSetOfPoints</tt> of their vertices and returns their indices.<br>
   * The <tt>ITri</tt>'th triangle is described by :
   * <tt><ul>
   * <li>iNoVertices[3*ITri+0]
   * <li>iNoVertices[3*ITri+1]
   * <li>iNoVertices[3*ITri+2]
   * </ul></tt>
   * Let be <tt>IVtx</tt> a relative vertex number such for instance
   * <tt>IVtx = iNoVertices[3*ITri+0]</tt>, the index of this vertex is <tt>iIndexes[IVtx]</tt>.<br>
   * <b>CAUTION 1:</b> It is assumed that there is not duplicated index in the array <tt>iIndexes</tt>.
   * <b>CAUTION 2:</b> If <tt>ioNoTriangles</tt> is <tt>NULL</tt>, its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and its size must be at least <tt>iNbTriangles</tt>.<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method.<br>
   */
  virtual void AddTrianglesNum (const int   iNbVertices,
                                const int*  iIndexes,
                                const int   iNbTriangles,
                                const int*  iNoVertices,
                                int*       &ioNoTriangles) = 0 ;

  /**
   * Removes the <tt>iNoTriangle</tt>'th triangle.<br>
   * <b>CAUTION:</b> The subsequent calls of the method <tt>GetTriangle</tt> will return
   * null numbers for the vertices and neighbouring triangles.
   */
  virtual void RemoveTriangle (const int iNoTriangle) = 0 ;

  /**
   * Updates the vertices of the <tt>iNoTriangle</tt>'th triangle.<br>
   * This method consists of removing the given triangle and add a new one in place.
   */
  virtual void UpdateTriangle (const int iNoTriangle, const int iNoVertices[3]) = 0 ;

  /**
   * Removes a vertex given by its relative indice in the <tt>CATCldPolygon</tt>.<br>
   * That means removes all the triangles having this vertex.<br>
   * <b>CAUTION:</b> the point is not removed (ie it could be used after) unlike
   * the <tt>RemovePoint</tt> method.<br>
   * <b>NB:</b> If this method is called several times consecutively, it is advised to call it
   * under the optimization context <tt>(OptimizeBegin,OptimizeEnd)</tt>.
   */
  virtual void RemoveVertex (const int iNoVertex) = 0 ;

  /**
   * Tests if the <tt>iNoTriangle</tt>'th triangle in the <tt>CATCldPolygon</tt> is valid,
   * ie is not removed or each of its vertices indices is not null.
   */
  virtual CATBoolean IsTriangleValid (const int iNoTriangle) const = 0 ;

  /**
   * Tests if the <tt>iNoTriangle</tt>'th triangle in the <tt>CATCldPolygon</tt> is active,
   * ie each of its vertices is active.
   */
  virtual CATBoolean IsTriangleActive (const int iNoTriangle) const = 0 ;

  /**
   * Returns the number of triangles.<br>
   * @param iAllTriangles
   * If <tt>TRUE</tt>,  the removed triangles are taken account.<br>
   * If <tt>FALSE</tt>, they are not.
   */
  virtual int GetNbTriangles (const CATBoolean iAllTriangles = TRUE) const = 0 ;

  /**
   * Returns the vertices and the orientation of the <tt>iNoTriangle</tt>'th triangle.<br>
   * The <tt>oDirect</tt> flag is computed by the <tt>EndOfCreation</tt> or <tt>EndOfModification</tt> methods.<br>
   * <ul>
   * <li>The first valid triangle is considered as direct and defines the global
   * orientation for the whole <tt>CATCldPolygon</tt>.
   * <li>The other valid triangles are oriented in regards on the first valid triangle.
   * <li><b>CAUTION:</b> If the <tt>CATCldPolygon</tt> is not orientable, this flag could be not significant.
   * </ul>
   */
  virtual void GetTriangle (const int   iNoTriangle,
                            int         oNoVertices[3],
                            CATBoolean &oDirect) const = 0 ;

  /**
   * Returns the vertices and the neighbouring triangles of the <tt>iNoTriangle</tt>'th triangle.<br>
   * <ul>
   * <li><tt>oNoConnexes[0]</tt> gives the neighbouring triangle number
   * along the edge <tt>(oNoVertices[0],oNoVertices[1])</tt>
   * <li><tt>oNoConnexes[1]</tt> gives the neighbouring triangle number
   * along the edge <tt>(oNoVertices[1],oNoVertices[2])</tt>
   * <li><tt>oNoConnexes[2]</tt> gives the neighbouring triangle number
   * along the edge <tt>(oNoVertices[2],oNoVertices[0])</tt>
   * </ul>
   * If <tt>oNoConnexes[i]</tt> equals to 0, there is no neighbouring triangle.<br>
   * <b>CAUTION:</b> <tt>oNoVertices[0]</tt> equals 0 means that the triangle was removed.
   */
  virtual void GetTriangle (const int iNoTriangle,
                            int       oNoVertices[3],
                            int       oNoConnexes[3]) const = 0 ;

  /**
   * Returns the vertices, the neighbouring triangles and the orientation of the <tt>iNoTriangle</tt>'th triangle.<br>
   * <ul>
   * <li><tt>oNoConnexes[0]</tt> gives the neighbouring triangle number
   * along the edge <tt>(oNoVertices[0],oNoVertices[1])</tt>
   * <li><tt>oNoConnexes[1]</tt> gives the neighbouring triangle number
   * along the edge <tt>(oNoVertices[1],oNoVertices[2])</tt>
   * <li><tt>oNoConnexes[2]</tt> gives the neighbouring triangle number
   * along the edge <tt>(oNoVertices[2],oNoVertices[0])</tt>
   * </ul>
   * If <tt>oNoConnexes[i]</tt> equals to 0, there is no neighbouring triangle.<br>
   * <b>CAUTION:</b> <tt>oNoVertices[0]</tt> equals 0 means that the triangle was removed.<br>
   * The <tt>oDirect</tt> flag is computed by the <tt>EndOfCreation</tt> or <tt>EndOfModification</tt> methods.<br>
   * <ul>
   * <li>The first valid triangle is considered as direct and defines the global
   * orientation for the whole <tt>CATCldPolygon</tt>.
   * <li>The other valid triangles are oriented in regards on the first valid triangle.
   * <li><b>CAUTION:</b> If the <tt>CATCldPolygon</tt> is not orientable, this flag could be not significant.
   * </ul>
   */
  virtual void GetTriangle (const int   iNoTriangle,
                            int         oNoVertices[3],
                            int         oNoConnexes[3],
                            CATBoolean &oDirect) const = 0 ;

  /**
   * Returns the whole description of the polygon (the removed triangles are not taken account).<br>
   * The <tt>ITri</tt>'th triangle is described by :
   * <tt><ul>
   * <li>iNoVertices[3*ITri+0]
   * <li>iNoVertices[3*ITri+1]
   * <li>iNoVertices[3*ITri+2]
   * </ul></tt>
   * Let be <tt>IVtx</tt> a relative vertex number such for instance
   * <tt>IVtx = iNoVertices[3*ITri+0]</tt>, the index of this vertex is <tt>iIndexes[IVtx]</tt>.<br>
   * <b>CAUTION:</b> if <tt>ioIndexes</tt> (resp. <tt>ioNoVertices</tt>) is <tt>NULL</tt>,
   * its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and
   * its size must be greater than the expected <tt>oNbVertices</tt>
   * (resp. <tt>3*oNbTriangles, 3*oNbTriangles</tt>).<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method
   * if it is not <tt>NULL</tt> in case of no vertices r triangles.<br>
   */
  virtual void GetTriangles (int              &oNbVertices,
                             int*             &ioIndexes,
                             int              &oNbTriangles,
                             int*             &ioNoVertices,
                             const CATBoolean  iOnlyActive = FALSE) const = 0 ;

  /**
   * Returns the whole description of the polygon (the removed triangles are not taken account).<br>
   * The <tt>ITri</tt>'th triangle is described by :
   * <tt><ul>
   * <li>iNoVertices[3*ITri+0]
   * <li>iNoVertices[3*ITri+1]
   * <li>iNoVertices[3*ITri+2]
   * </ul></tt>
   * Its neighbouring triangles will be found in :
   * <tt><ul>
   * <li>iNoConnexes[3*ITri+0]
   * <li>iNoConnexes[3*ITri+1]
   * <li>iNoConnexes[3*ITri+2]
   * </ul></tt>
   * If <tt>oNoConnexes[i]</tt> equals to -1, there is no neighbouring triangle.
   * Let be <tt>IVtx</tt> a relative vertex number such for instance
   * <tt>IVtx = iNoVertices[3*ITri+0]</tt>, the index of this vertex is <tt>iIndexes[IVtx]</tt>.<br>
   * <b>CAUTION:</b> if <tt>ioIndexes</tt> (resp. <tt>ioNoVertices, ioNoConnexes</tt>) is <tt>NULL</tt>,
   * its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and
   * its size must be greater than the expected <tt>oNbVertices</tt>
   * (resp. <tt>3*oNbTriangles, 3*oNbTriangles</tt>).<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method
   * if it is not <tt>NULL</tt> in case of no vertices r triangles.<br>
   */
  virtual void GetTriangles (int              &oNbVertices,
                             int*             &ioIndexes,
                             int              &oNbTriangles,
                             int*             &ioNoVertices,
                             int*             &ioNoConnexes,
                             const CATBoolean  iOnlyActive = FALSE) const = 0 ;

  /**
   * Returns a description of the polygon (the removed triangles are not taken account).<br>
   * The <tt>ITri</tt>'th triangle is described by :
   * <tt><ul>
   * <li>iNoVertices[3*ITri+0]
   * <li>iNoVertices[3*ITri+1]
   * <li>iNoVertices[3*ITri+2]
   * </ul></tt>
   * Let be <tt>IVtx</tt> a relative vertex number such for instance
   * <tt>IVtx = iNoVertices[3*ITri+0]</tt>, the coordinates of this vertex
   * will be found in :
   * <tt><ul>
   * <li>ioCoords[3*IVtx+0]
   * <li>ioCoords[3*IVtx+1]
   * <li>ioCoords[3*IVtx+2]
   * </ul></tt>
   * <b>CAUTION:</b> if <tt>ioCoords</tt> (resp. <tt>ioNoVertices</tt>) is <tt>NULL</tt>,
   * its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and
   * its size must be greater than the expected <tt>3*oNbVertices</tt>
   * (resp. <tt>3*oNbTriangles</tt>).<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method
   * if it is not <tt>NULL</tt> in case of no vertices r triangles.<br>
   */
  virtual void GetTriangles (int              &oNbVertices,
                             float*           &ioCoords,
                             int              &oNbTriangles,
                             int*             &ioNoVertices,
                             const CATBoolean  iOnlyActive = FALSE) const = 0 ;

  /**
   * Returns a description of the polygon (the removed triangles are not taken account).<br>
   * The <tt>ITri</tt>'th triangle is described by :
   * <tt><ul>
   * <li>iNoVertices[3*ITri+0]
   * <li>iNoVertices[3*ITri+1]
   * <li>iNoVertices[3*ITri+2]
   * </ul></tt>
   * Let be <tt>IVtx</tt> a relative vertex number such for instance
   * <tt>IVtx = iNoVertices[3*ITri+0]</tt>, the coordinates of this vertex
   * will be found in :
   * <tt><ul>
   * <li>ioCoords[3*IVtx+0]
   * <li>ioCoords[3*IVtx+1]
   * <li>ioCoords[3*IVtx+2]
   * </ul></tt>
   * <b>CAUTION:</b> if <tt>ioCoords</tt> (resp. <tt>ioNoVertices</tt>) is <tt>NULL</tt>,
   * its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and
   * its size must be greater than the expected <tt>3*oNbVertices</tt>
   * (resp. <tt>3*oNbTriangles</tt>).<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method
   * if it is not <tt>NULL</tt> in case of no vertices or triangles.<br>
   */
  virtual void GetTriangles (int              &oNbVertices,
                             double*          &ioCoords,
                             int              &oNbTriangles,
                             int*             &ioNoVertices,
                             const CATBoolean  iOnlyActive = FALSE) const = 0 ;

  /**
   * Returns the whole description of the polygon (the removed triangles are not taken account).<br>
   * The <tt>ITri</tt>'th triangle is described by :
   * <tt><ul>
   * <li>iNoVertices[3*ITri+0]
   * <li>iNoVertices[3*ITri+1]
   * <li>iNoVertices[3*ITri+2]
   * </ul></tt>
   * Let be <tt>IVtx</tt> a relative vertex number such for instance
   * <tt>IVtx = iNoVertices[3*ITri+0]</tt>, the coordinates of this vertex
   * will be found in :
   * <tt><ul>
   * <li>ioCoords[3*IVtx+0]
   * <li>ioCoords[3*IVtx+1]
   * <li>ioCoords[3*IVtx+2]
   * </ul></tt>
   * and the coordinates of the associated normal in :
   * <tt><ul>
   * <li>ioNormals[3*IVtx+0]
   * <li>ioNormals[3*IVtx+1]
   * <li>ioNormals[3*IVtx+2]
   * </ul></tt>
   * <b>CAUTION:</b> if <tt>ioCoords</tt> (resp. <tt>ioNormals, ioNoVertices</tt>) is <tt>NULL</tt>,
   * its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and
   * its size must be greater than the expected <tt>3*oNbVertices</tt>
   * (resp. <tt>3*oNbVertices, 3*oNbTriangles, 3*oNbTriangles</tt>).<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method
   * if it is not <tt>NULL</tt> in case of no vertices r triangles.<br>
   * @param iNormalize
   * If <tt>TRUE</tt>, the normal of a triangle is normalized before being summed.
   */
  virtual void GetTriangles (int              &oNbVertices,
                             float*           &ioCoords,
                             float*           &ioNormals,
                             int              &oNbTriangles,
                             int*             &ioNoVertices,
                             const CATBoolean  iOnlyActive = FALSE,
                             const CATBoolean  iNormalize = FALSE) const = 0 ;

  /**
   * Returns the whole description of the polygon (the removed triangles are not taken account).<br>
   * The <tt>ITri</tt>'th triangle is described by :
   * <tt><ul>
   * <li>iNoVertices[3*ITri+0]
   * <li>iNoVertices[3*ITri+1]
   * <li>iNoVertices[3*ITri+2]
   * </ul></tt>
   * Let be <tt>IVtx</tt> a relative vertex number such for instance
   * <tt>IVtx = iNoVertices[3*ITri+0]</tt>, the coordinates of this vertex
   * will be found in :
   * <tt><ul>
   * <li>ioCoords[3*IVtx+0]
   * <li>ioCoords[3*IVtx+1]
   * <li>ioCoords[3*IVtx+2]
   * </ul></tt>
   * and the coordinates of the associated normal in :
   * <tt><ul>
   * <li>ioNormals[3*IVtx+0]
   * <li>ioNormals[3*IVtx+1]
   * <li>ioNormals[3*IVtx+2]
   * </ul></tt>
   * <b>CAUTION:</b> if <tt>ioCoords</tt> (resp. <tt>ioNormals, ioNoVertices</tt>) is <tt>NULL</tt>,
   * its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and
   * its size must be greater than the expected <tt>3*oNbVertices</tt>
   * (resp. <tt>3*oNbVertices, 3*oNbTriangles, 3*oNbTriangles</tt>).<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method
   * if it is not <tt>NULL</tt> in case of no vertices r triangles.<br>
   * @param iNormalize
   * If <tt>TRUE</tt>, the normal of a triangle is normalized before being summed.
   */
  virtual void GetTriangles (int              &oNbVertices,
                             double*          &ioCoords,
                             double*          &ioNormals,
                             int              &oNbTriangles,
                             int*             &ioNoVertices,
                             const CATBoolean  iOnlyActive = FALSE,
                             const CATBoolean  iNormalize = FALSE) const = 0 ;

  /**
   * Returns the whole description of the polygon (the removed triangles are not taken account).<br>
   * The <tt>ITri</tt>'th triangle is described by :
   * <tt><ul>
   * <li>iNoVertices[3*ITri+0]
   * <li>iNoVertices[3*ITri+1]
   * <li>iNoVertices[3*ITri+2]
   * </ul></tt>
   * Its neighbouring triangles will be found in :
   * <tt><ul>
   * <li>iNoConnexes[3*ITri+0]
   * <li>iNoConnexes[3*ITri+1]
   * <li>iNoConnexes[3*ITri+2]
   * </ul></tt>
   * If <tt>oNoConnexes[i]</tt> equals to -1, there is no neighbouring triangle.
   * Let be <tt>IVtx</tt> a relative vertex number such for instance
   * <tt>IVtx = iNoVertices[3*ITri+0]</tt>, the coordinates of this vertex
   * will be found in :
   * <tt><ul>
   * <li>ioCoords[3*IVtx+0]
   * <li>ioCoords[3*IVtx+1]
   * <li>ioCoords[3*IVtx+2]
   * </ul></tt>
   * and the coordinates of the associated normal in :
   * <tt><ul>
   * <li>ioNormals[3*IVtx+0]
   * <li>ioNormals[3*IVtx+1]
   * <li>ioNormals[3*IVtx+2]
   * </ul></tt>
   * <b>CAUTION:</b> if <tt>ioCoords</tt> (resp. <tt>ioNormals, ioNoVertices, ioNoConnexes</tt>) is <tt>NULL</tt>,
   * its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and
   * its size must be greater than the expected <tt>3*oNbVertices</tt>
   * (resp. <tt>3*oNbVertices, 3*oNbTriangles, 3*oNbTriangles</tt>).<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method
   * if it is not <tt>NULL</tt> in case of no vertices r triangles.<br>
   * @param iNormalize
   * If <tt>TRUE</tt>, the normal of a triangle is normalized before being summed.
   */
  virtual void GetTriangles (int              &oNbVertices,
                             float*           &ioCoords,
                             float*           &ioNormals,
                             int              &oNbTriangles,
                             int*             &ioNoVertices,
                             int*             &ioNoConnexes,
                             const CATBoolean  iOnlyActive = FALSE,
                             const CATBoolean  iNormalize = FALSE) const = 0 ;

  /**
   * Returns the whole description of the polygon (the removed triangles are not taken account).<br>
   * The <tt>ITri</tt>'th triangle is described by :
   * <tt><ul>
   * <li>iNoVertices[3*ITri+0]
   * <li>iNoVertices[3*ITri+1]
   * <li>iNoVertices[3*ITri+2]
   * </ul></tt>
   * Its neighbouring triangles will be found in :
   * <tt><ul>
   * <li>iNoConnexes[3*ITri+0]
   * <li>iNoConnexes[3*ITri+1]
   * <li>iNoConnexes[3*ITri+2]
   * </ul></tt>
   * If <tt>oNoConnexes[i]</tt> equals to -1, there is no neighbouring triangle.
   * Let be <tt>IVtx</tt> a relative vertex number such for instance
   * <tt>IVtx = iNoVertices[3*ITri+0]</tt>, the coordinates of this vertex
   * will be found in :
   * <tt><ul>
   * <li>ioCoords[3*IVtx+0]
   * <li>ioCoords[3*IVtx+1]
   * <li>ioCoords[3*IVtx+2]
   * </ul></tt>
   * and the coordinates of the associated normal in :
   * <tt><ul>
   * <li>ioNormals[3*IVtx+0]
   * <li>ioNormals[3*IVtx+1]
   * <li>ioNormals[3*IVtx+2]
   * </ul></tt>
   * <b>CAUTION:</b> if <tt>ioCoords</tt> (resp. <tt>ioNormals, ioNoVertices, ioNoConnexes</tt>) is <tt>NULL</tt>,
   * its allocation is done by the method.<br>
   * Otherwise it has to be done by the calling method and
   * its size must be greater than the expected <tt>3*oNbVertices</tt>
   * (resp. <tt>3*oNbVertices, 3*oNbTriangles, 3*oNbTriangles</tt>).<br>
   * But its release <b>HAS TO BE DONE</b> by the calling method
   * if it is not <tt>NULL</tt> in case of no vertices r triangles.<br>
   * @param iNormalize
   * If <tt>TRUE</tt>, the normal of a triangle is normalized before being summed.
   */
  virtual void GetTriangles (int              &oNbVertices,
                             double*          &ioCoords,
                             double*          &ioNormals,
                             int              &oNbTriangles,
                             int*             &ioNoVertices,
                             int*             &ioNoConnexes,
                             const CATBoolean  iOnlyActive = FALSE,
                             const CATBoolean  iNormalize = FALSE) const = 0 ;

  /**
   * Returns the triangles having the given point as vertex.<br>
   * <b>CAUTION:</b> The list will be cleared by the method before use.<br>
   * <b>NB:</b> If this method is called several times consecutively, it is advised to call it
   * under the optimization context <tt>(OptimizeBegin,OptimizeEnd)</tt>.
   */
  virtual void GetNeighbours (const int     iNoVertex,
                              CATListOfInt &ioNoTriangles) const = 0 ;

  /**
   * Returns the neighbour vertices at a given level for a vertex given by its relative indice.
   * <pre>
   *           2       2       2
   *           +-------+-------+              On this tesselation, the levels are shown
   *          / \     / \     / \             in regards on the central vertex (level 0).
   *         /   \   /   \   /   \
   *       2/     \1/     \1/     \2
   *       +-------+-------+-------+
   *      / \     / \     / \     / \
   *     /   \   /   \   /   \   /   \
   *   2/     \1/     \0/     \1/     \2
   *   +-------+-------+-------+-------+
   *    \     / \     / \     / \     /
   *     \   /   \   /   \   /   \   /
   *      \2/     \1/     \1/     \2/
   *       +-------+-------+-------+
   *        \     / \     / \     /
   *         \   /   \   /   \   /
   *          \2/     \2/     \2/
   *           +-------+-------+
   * </pre>
   * @param iNoVertex
   * The relative indice of the vertex that we want the neighbours.
   * @param iLevel
   * The wanted level.
   * @param ioLevels
   * Array of the levels offsets.<br>
   * If <tt>NULL</tt>, the array is allocated by the method and HAS TO RELEASED by the caller.<br>
   * It size has to be greater or equal to <tt>1+iLevel+1</tt>.<br>
   * The vertices of the <tt>I</tt>'th level (<tt>I in [0,iLevel]</tt>) will be found between
   * <tt>ioNoVertices[ioLevels[I]]</tt> and <tt>ioNoVertices[ioLevels[I+1]-1]</tt>.
   * @param ioNoVertices
   * List of the neighbour vertices indices.<br>
   * <b>CAUTION:</b> The list will be cleaned at the beginning of the treatment.
   * @return
   * <tt>TRUE</tt>, if the computation has succeeded. <tt>FALSE</tt>, otherwise.<br>
   * <b>NB:</b> If this method is called several times consecutively, it is advised to call it
   * under the optimization context <tt>(OptimizeBegin,OptimizeEnd)</tt>.
   */

  virtual CATBoolean GetNeighbours (const int     iNoVertex,
                                    const int     iLevel,
                                    int*         &ioLevels,
                                    CATListOfInt &ioNoVertices) const = 0 ;

  /**
   * Returns the two triangles sharing the edge defined by the two points given
   * their relative indices in the <tt>CATCldPolygon</tt>.<br>
   * If <tt>iNoTriangle1</tt> and <tt>iNoTriangle2</tt> equal to 0, that means
   * there is no triangle having this edge.<br>
   * If only <tt>iNoTriangle2</tt> equals to 0, that means the edge belongs to
   * only one triangle (ie it is a free edge).<br>
   * <b>NB:</b> If this method is called several times consecutively, it is advised to call it
   * under the optimization context <tt>(OptimizeBegin,OptimizeEnd)</tt>.<br>
   * <b>CAUTION:</b> In case of a non-manifold polygon, the returned triangles
   * are the first having the given edge. So it is advised to call the hereafter method.
   */
  virtual void GetNeighbours (const int  iNoVertex1,
                              const int  iNoVertex2,
                              int       &oNoTriangle1,
                              int       &oNoTriangle2) const = 0 ;

  /**
   * Returns all the triangles sharing the edge defined by the two points given
   * their relative indices in the <tt>CATCldPolygon</tt>.<br>
   * <b>NB:</b> If this method is called several times consecutively, it is advised to call it
   * under the optimization context <tt>(OptimizeBegin,OptimizeEnd)</tt>.<br>
   * <b>CAUTION:</b> The list <tt>ioNoTriangles</tt> will be cleaned before any treatment.
   */
  virtual void GetNeighbours (const int     iNoVertex1,
                              const int     iNoVertex2,
                              CATListOfInt &ioNoTriangles) const = 0 ;

  /**
   * Returns the connected triangle to the given triangle along the given edge.<br>
   * @return
   * <ul>
   * <li><tt>-1</tt>: if the given edge does not belong to the given triangle.
   * <li><tt> 0</tt>: if the given edge is a free edge.
   * <li>The indice of the connected triangle.
   * </ul>
   */
  virtual int GetNeighbour (const int iNoTriangle,
                            const int iNoVertex1,
                            const int iNoVertex2) const = 0 ;

  /**
   * Flips the edge between two triangles.<br>
   * Let be two triangles T1 (n1,n2,n3) and T2 (n4,n2,n1),
   * they will be replaced by the triangles T'1 (n1,n4,n3) and T'2 (n4,n2,n3).
   * <pre>
   *   n4-----n2     n4-----n2
   *   |     /|      |\     |
   *   | T2 / |      | \ T2'|
   *   |   /  |      |  \   |
   *   |  /   | ==>  |   \  |
   *   | / T1 |      |T1' \ |
   *   |/     |      |     \|
   *   n1-----n3     n1-----n3
   * </pre>
   */
  virtual void FlipEdge (const int iNoVertex1,
                         const int iNoVertex2) = 0 ;

  /**
   * Computes the normal of a triangle.<br>
   * The normal of a triangle <tt>(V1,V2,V3)</tt> is the cross product "<tt>(V1V2)^(V1V3)</tt>".<br>
   * @param iNormalize
   * If <tt>TRUE</tt>, the normal is normalized.
   */
  virtual void ComputeTriangleNormal (const int        iNoTriangle,
                                      float            oNormal[3],
                                      const CATBoolean iNormalize = FALSE) const = 0 ;

  /**
   * Computes the normal of a triangle.<br>
   * The normal of a triangle <tt>(V1,V2,V3)</tt> is the cross product "<tt>(V1V2)^(V1V3)</tt>".<br>
   * @param iNormalize
   * If <tt>TRUE</tt>, the normal is normalized.
   */
  virtual void ComputeTriangleNormal (const int        iNoTriangle,
                                      double           oNormal[3],
                                      const CATBoolean iNormalize = FALSE) const = 0 ;

  /**
   * Extracts a minimal sub-polygon composed of the given triangles.<br>
   * It shares the same <tt>CATCldSetOfPoints</tt>.
   */
  virtual CATCldPolygon* ExtractSubPolygon (const int  iNbTriangles,
                                            const int* iNoTriangles) const = 0 ;

  /**
   * Returns the free edges of the <tt>CATCldPolygon</tt> as a <tt>CATCldSetOfScans</tt>.
   */
  virtual CATCldSetOfScans* FreeEdges () const = 0 ;

  /**
   * Returns the free edges of the <tt>CATCldPolygon</tt>.<br>
   * @param oNbEdges.
   * The number of free edges.
   * @param oNoVertices.
   * The free edges described by the relative indices of their vertices.<br>
   * The <tt>i</tt>'th edge (<tt>i</tt> in the range <tt>[0,oNbEdges-1]</tt>) is defined
   * by <tt>(oNoVertices[2*i],oNoVertices[2*i+1])</tt>.<br>
   * <b>CAUTION:</b> If <tt>oNoVertices</tt> is not null, it is desallocated by the method before any treatment.
   * @param iOnlyActive
   * If <tt>TRUE</tt>, the research will be done only on the active triangles.
   * @return
   * <tt>TRUE</tt>, if there are free edges. <tt>FALSE</tt>, otherwise.<br>
   */

  virtual CATBoolean GetFreeEdges (int              &oNbEdges,
                                   int*             &oNoVertices,
                                   const CATBoolean  iOnlyActive = FALSE) const = 0 ;

  /**
   * Returns the non-manifold edges of the <tt>CATCldPolygon</tt>.<br>
   * An edge is said non-manifold if it is shared by more than two triangles.
   * @param oNbEdges.
   * The number of non-manifold edges.
   * @param oNoVertices.
   * The non-manifold edges described by the relative indices of their vertices.<br>
   * The <tt>i</tt>'th edge (<tt>i</tt> in the range <tt>[0,oNbEdges-1]</tt>) is defined
   * by <tt>(oNoVertices[2*i],oNoVertices[2*i+1])</tt>.<br>
   * <b>CAUTION:</b> If <tt>oNoVertices</tt> is not null, it is desallocated by the method before any treatment.
   * @param iOnlyActive
   * If <tt>TRUE</tt>, the research will be done only on the active triangles.
   * @return
   * <tt>TRUE</tt>, if there are non-manifold edges. <tt>FALSE</tt>, otherwise.<br>
   */

  virtual CATBoolean GetNonManifoldEdges (int              &oNbEdges,
                                          int*             &oNoVertices,
                                          const CATBoolean  iOnlyActive = FALSE) const = 0 ;

//==============================================================================================================
// Triangles attributes management in a CATCldPolygon.
//==============================================================================================================

  /**
   * Returns the attribute associated to the <tt>iNoTriangle</tt>'th triangle.<br>
   * <tt>CAUTION:</tt> Returns a <tt>NULL</tt> pointer if the attributes is not set.
   */
  virtual CATCldAttribute* GetTriangleAttribute (const int iNoTriangle) const = 0 ;

  /**
   * Associates the given attribute to the <tt>iNoTriangle</tt>'th triangle.
   */
  virtual void SetTriangleAttribute (const int              iNoTriangle,
                                     const CATCldAttribute* iAttribute) = 0 ;

//==============================================================================================================
// Specific algorithms on a CATCldPolygon.
//==============================================================================================================

  /**
   * Returns the normal projection of a given point.
   * @param iPoint
   * A point.
   * @param oType
   * The type of the projection :
   * <ul>
   * <li><tt> 0</tt>: On a vertex.
   * <li><tt> 1</tt>: On an edge.
   * <li><tt> 2</tt>: On a triangle.
   * <li><tt>-1</tt>: If no result.
   * </ul>
   * @param oNum1
   * <ul>
   * <li>If <tt>"oType == 0"</tt>, the vertex relative indice.
   * <li>If <tt>"oType == 1"</tt>, the relative indice of the first vertex of the edge.
   * <li>If <tt>"oType == 2"</tt>, the triangle indice.
   * </ul>
   * @param oNum2
   * If <tt>"oType == 1"</tt>, the relative indice of the second vertex of the edge.
   * @param iTolerance
   * The tolerance defining the confusion with a vertex or an edge.
   * @return
   * The point projection.
   */

  virtual CATMathPoint NormalProjection (const CATMathPoint &iPoint,
                                         int                &oType,
                                         int                &oNum1,
                                         int                &oNum2,
                                         const double        iTolerance = 0.) const = 0 ;

  /**
   * Splits the <tt>CATCldPolygon</tt> in connected components.
   * @param ioSubPolygons.
   * The connected sub-polygons.<br>
   * <b>CAUTION:</b> The list <tt>ioSubPolygons</tt> is cleaned by the method before any treatment.
   */

  virtual void SplitInConnectedZones (CATLISTP(CATCldCell) &ioSubPolygons) const = 0 ;

  /**
   * Re-orientates the valid triangles of the <tt>CATCldPolygon</tt> computed as indirect.<br>
   * If the <tt>CATCldPolygon</tt> is not orientable, the result is not garanted.<br>
   * <b>CAUTION:</b> The call of this method does not need a recall of <tt>EndOfCreation</tt>
   * or <tt>EndOfModification</tt> methods.
   */

  virtual void ReOrientate () = 0 ;


  /**
   * Returns a CATIPolyMesh adapter to the CATCldPolygon.  The instance returned must be released
   * by the caller.
   * @param oMesh
   *   A CATIPolyMesh interface to the instance constructed.  It must be released by the caller.
   * @param iOnlyActive
   *   If TRUE, the different iterators associated to the returned CATIPolyMesh will considerate
   *   only the active vertices and triangles
   * @return
   *   TRUE if it constructs successfully a CATIPolyMesh object.
   */
  virtual CATBoolean GetPolyMesh (CATIPolyMesh*& oMesh, const CATBoolean iOnlyActive = FALSE) = 0;


} ;

CATDeclareHandler (CATCldPolygon, CATCldUniCell) ;

#endif
