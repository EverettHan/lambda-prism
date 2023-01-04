// COPYRIGHT DASSAULT SYSTEMES 2003, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyTopoUtil.h
//
//===================================================================
// Sep 2003 Creation: dhp
//===================================================================
#ifndef CATPolyTopoUtil_h
#define CATPolyTopoUtil_h

#include "PolyhedralUtilities.h"
#include "CATErrorDef.h"     // HRESULT definition
#include "CATBoolean.h"
#include "CATListOfInt.h"

class CATIPolyMesh;
class CATIPolySurfaceVertexFacetNeighborhood;


class ExportedByPolyhedralUtilities CATPolyTopoUtil 
{
public :

  /**
   * Constructor.
   */
	CATPolyTopoUtil (const CATIPolyMesh * polyMesh);

  /**
   * Destructor.
   */
	~CATPolyTopoUtil (void);

  /**
   * Tests if the bars (bar0V0, bar0V1) and (bar1V0, bar1V1)
   * are the same bar.
   * @param iBar0Vertex0
   *   The first vertex of the first bar.
   * @param iBar0Vertex1
   *   The second vertex of the first bar.
   * @param iBar1Vertex0
   *   The first vertex of the second bar.
   * @param iBar1Vertex1
   *   The second vertex of the second bar.
   * @return
   *   TRUE if the bars are the same and FALSE otherwise.
   */
  inline static CATBoolean BarEqual (const int iBar0Vertex0, const int iBar0Vertex1,
                                     const int iBar1Vertex0, const int iBar1Vertex1);

  /** 
   * Given three vertices, check whether they define a valid triangle of the mesh.
   * A valid triangle cannot have two of its vertices identical.
   * If the three vertices define a valid triangle, the method returns TRUE and the
   * triangle.  The returned triangle is not necessarily oriented in the same direction as 
   * the direction defined by (iIdxVertex0, iIdxVertex1, iIdxVertex2).
   */
  CATBoolean IsTriangleValid (const int iIdxVertex0, const int iIdxVertex1, const int iIdxVertex2,
                              int& oTriangle) const;

  /** 
   * Given two bars (iIdxVertex00, iIdxVertex01) and (iIdxVertex10, iIdxVertex11), 
   * check whether they define a valid triangle of the mesh.
   * A valid triangle cannot have two of its vertices identical.
   * If the two bars define a valid triangle, the method returns TRUE and the
   * triangle. Two of the bar vertices must be equal.
   */
  CATBoolean IsTriangleValid (const int iIdxVertex00, const int iIdxVertex01,
                              const int iIdxVertex10, const int iIdxVertex11,
                              int& oTriangle) const;

  /**
   * Tests if a vertex is a vertex of the triangle.
   * @param iIdxTriangle
   *   The index of the triangle.
   * @param iIdxVertex
   *   The index of the vertex.
   * @return
   *   TRUE if the vertex is a vertex of the triangle and FALSE otherwise.
   */
  CATBoolean IsAVertexOfTriangle (const int iIdxTriangle,
                                  const int iIdxVertex) const;


  /**
   * Tests if the two triangles are neighbors (they share a bar).
   * @param iIdxTriangle0
   *   The first triangle.
   * @param iIdxTriangle1
   *   The second triangle.
   * @return
   *   TRUE if the triangles are neighbors and FALSE otherwise.
   */
  CATBoolean IsATriangleNeighborOfTriangle (const int iIdxTriangle0,
                                            const int iIdxTriangle1) const;

  /**
   * Tests if a bar (given by its vertices) is contained in the triangle.
   * @param iIdxTriangle
   *   The index of the triangle.
   * @param iIdxVertex1
   *   The index of the first vertex of the bar.
   * @param iIdxVertex2
   *   The index of the second vertex of the bar.
   * @return
   *   TRUE if the bar is in the triangle and FALSE otherwise.
   */
  CATBoolean IsABarOfTriangle (const int iIdxTriangle,
                               const int iIdxVertex1,
                               const int iIdxVertex2) const;

  /**
   * Given a vertex, returns the next vertex of the triangle.
   * @param iIdxTriangle
   *   The index of the triangle.
   * @param iIdxVertex
   *   The index of the vertex.
   * @return
   *   The index of the next vertex.
   */
  HRESULT GetNextVertex (const int iIdxTriangle,
                         const int iIdxVertex,
                         int & nextVertex) const;

  /**
   * Given a vertex, returns the previous vertex of the triangle.
   * @param iIdxTriangle
   *   The index of the triangle.
   * @param iIdxVertex
   *   The index of the vertex.
   * @return
   *   The index of the previous vertex.
   */
  HRESULT GetPreviousVertex (const int iIdxTriangle,
                             const int iIdxVertex,
                             int & prevVertex) const;

  /**
   * Returns the vertex in the triangle opposite to the bar defined by the two vertices.
   * @param iIdxTriangle
   *   The index of the triangle.
   * @param iIdxVertex1
   *   The index of the first vertex of the bar.
   * @param iIdxVertex2
   *   The index of the second vertex of the bar.
   * @return
   *   The index of the vertex opposite the bar.
   *   Returns zero if the triangle is not valid or the specified vertices are not in the triangle.
   */
  HRESULT GetOppositeVertex (const int iIdxTriangle,
                             const int iIdxVertex1,
                             const int iIdxVertex2,
                             int & oppVertex) const;

  /**
   * Returns the vertices of a bar opposite to the specified vertex.
   * @param iIdxTriangle
   *   The index of the triangle.
   * @param iIdxVertex
   *   The index of a vertex in the triangle.
   * @param oIdxVertex1
   *   The index of the first vertex of the opposite bar.
   * @param oIdxVertex2
   *   The index of the second vertex of the opposite bar.
   * @return
   *   S_OK if the method runs successfully and E_FAIL otherwise.
   */
  HRESULT GetOppositeBar (const int  iIdxTriangle,
                          const int  iIdxVertex,
                          int       &oIdxVertex1,
                          int       &oIdxVertex2) const;

  /**
   * Given a triangle <tt>iIdxTriangle</tt> and a bar of the triangle <tt>(iIdxVertex1, iIdxVertex2)</tt>
   * get the third vertex <tt>iIdxVertex3</tt> and the triangle opposite the bar <tt>(iIdxVertex1, iIdxVertex3)</tt>.
   * This method gets the next triangle in the fan around <tt>iIdxVertex1</tt> and across the other bar
   * containing <tt>iIdxVertex1</tt>.
   * It can be called iteratively to fetch triangles and vertices around a vertex.
   * @param iIdxVertex1
   * The index of the vertex around which the search is performed.
   * It is the starting point of the input and output bars.
   * @param iIdxVertex2
   * The index of the vertex defining the ending point of the input bar.
   * When the method runs successfully, it is set to the ending point of the output bar.
   * @param iIdxTriangle
   * The index of the triangle.
   * If the method runs successfully, it is set to the next triangle in the fan.
   * @return
   * <tt>S_OK</tt> if the method runs successfully and the parameters are updated.
   * <tt>E_FAIL</tt> otherwise.
   *
   *           2       2       2
   *           +-------+-------+              For instance, a call to
   *          / \     / \     / \               GetNextVertexAndTriangle (vertex1, vertex2, triangle) ;
   *         /   \   /   \   /   \            with   
   *       2/     \b/     \c/     \2            vertex1 = a, vertex2 = b, triangle = T1,
   *       +-------+-------+-------+          results in:
   *      / \     / \ T1  / \     / \           vertex1 = a, vertex2 = c, triangle = T2.
   *     /   \   /   \   /   \   /   \
   *   2/     \g/ T6  \a/  T2 \d/     \2
   *   +-------+-------+-------+-------+
   *    \     / \ T5  / \  T3 / \     /
   *     \   /   \   /   \   /   \   /
   *      \2/     \f/ T4  \e/     \2/
   *       +-------+-------+-------+
   *        \     / \     / \     /
   *         \   /   \   /   \   /
   *          \2/     \2/     \2/
   *           +-------+-------+
   */
  HRESULT GetNextVertexAndTriangle (const int  iCenterVertex1,
                                    int       &ioIdxVertex2,
                                    int       &ioIdxTriangle) const;

  /**
   * Retrieves the vertices of a bar of the triangle.
   * @param iIdxTriangle
   *   The index of the triangle whose bar vertices are desired.
   *   <b>Legal values</b>: 1 to the number of triangles, inclusive.
   * @param iBarIndex
   *   The bar index in the triangle.
   *   <b>Legal values</b>: 0, 1, or 2.
   * @param oIdxVertex0
   *   The first vertex of the bar.
   * @param oIdxVertex1
   *   The second vertex of the bar.
   * @return
   *   S_OK if the method runs successfully and E_FAIL otherwise.
   */
  HRESULT GetVerticesFromBarIndex (const int iIdxTriangle,
                                   const int iBarIndex,
                                   int & oIdxVertex0,
                                   int & oIdxVertex1) const;

  /**
   * Retrieves the bar index in a given triangle.
   * @param iIdxTriangle
   *   The index of the triangle.
   *   <b>Legal values</b>: 1 to the number of triangles, inclusive.
   * @param iIdxVertex0
   *   The first vertex of the bar.
   * @param iIdxVertex1
   *   The second vertex of the bar.
   * @param oBarIndex
   *   The bar index in the triangle.
   *   <b>Legal values</b>: 0, 1, or 2.
   * @return
   *   S_OK if the method runs successfully and E_FAIL otherwise.
   */
  HRESULT GetBarIndex (const int iIdxTriangle,
                       const int iIdxVertex0,
                       const int iIdxVertex1,
                       int& oBarIndex) const;

  /**
   * Returns the index of a vertex in the triangle.
   * @param iIdxTriangle.
   *   The index of the triangle.
   *   <b>Legal values</b>: 1 to the number of triangles, inclusive.
   * @param iIdxVertex
   *   The index of the vertex.
   * @param oVertexIndex
   *   The vertex index (0, 1, or 2) in the triangle.
   * @return
   *   S_OK if the method runs successfully and E_FAIL otherwise.
   */
  HRESULT GetVertexIndex (const int iIdxTriangle,
                          const int iIdxVertex,
                          int & oVertexIndex) const;

  /**
   * Returns the orientation of a bar in a triangle.
   * @param iIdxTriangle
   *   The index of the triangle to which the bar belongs.
   * @param iIdxVertex0
   *   The first vertex of the bar.
   * @param iIdxVertex1
   *   The second vertex of the bar.
   * @param oBarOrientation
   *    +1 if the bar (iIdxVertex0, iIdxVertex1) is a positive bar of the triangle;
   *    -1 if the bar (iIdxVertex0, iIdxVertex1) is a negative bar of the triangle; 
   *     0 if it's not a bar.
   * @return 
   *   S_OK if the method runs successfully and E_FAIL otherwise.
   */
  HRESULT GetBarOrientation (const int iIdxTriangle,
                             const int iIdxVertex0, 
                             const int iIdxVertex1,
                             int & oBarOrientation) const;

  /**
   * Tests if a vertex is on a hole.
   * @param iIdxVertex
   *   The index of the vertex.
   * @return
   *   TRUE if the vertex is on a hole. This will the case if the vertex
   *   is shared by a bar which itself is referenced by only one triangle.
   *   FALSE otherwise.
   */
  //CATBoolean IsHoleVertex (const int iIdxVertex) const;

  /**
   * Tests if an bar is on a hole.
   * @param iIdxVertex0
   *   The index of the first vertex of the bar.
   * @param iIdxVertex1
   *   The index of the second vertex of the bar.
   * @return
   *   TRUE if the bar is on a hole and FALSE otherwise..
   */
  //CATBoolean IsHoleBar (const int iIdxVertex0,
                        //const int iIdxVertex1) const;

  /**
   * Given a free bar defined by (iIdxVertex0, iIdxVertex1), 
   * returns the vertex along the same hole that is a neighbor of iIdxVertex0
   * and different from iIdxVertex1.
   * @param iIdxVertex0
   *   The first vertex of the bar.
   * @param iIdxVertex1
   *   The second vertex of the bar.
   * @param nextVertex
   *   The neighbor of iIdxVertex0 along the same hole.
   * @return
   *   Return E_FAIL if no such vertex can be found.
   */
  HRESULT GetNextHoleVertex (const int iIdxVertex0,
                             const int iIdxVertex1,
                             int & nextVertex) const;

  /**
   * Gets the next bar along the hole from a bar in a triangle.  The given bar must be 
   * a hole bar of the triangle.
   * Returns <tt>S_OK<\tt> if the method runs successfully and <tt>E_FAIL<\tt> otherwise.
   * @param iIdxTriangle
   *   The index of the triangle to which the current bar belongs.  This triangle
   *   number is updated to point to the next triangle along the hole if the method
   *   runs successfully.
   * @param iIdxVertex0
   *   The index of the start vertex of the bar.  This vertex number is updated to 
   *   point to the start vertex of the next bar along the hole (that is iIdxVertex1).
   * @param iIdxVertex1
   *   The index of the end vertex of the bar.  This vertex number is updated to 
   *   point to the end vertex of the next bar along the hole.
   * @return
   *    <tt>S_OK<\tt> if the method runs succesfully and <tt>E_FAIL<\tt> otherwise.
   */
  HRESULT GetNextHoleBar (int & iIdxTriangle, 
                          int & iIdxVertex0,
                          int & iIdxVertex1) const;

  /**
   * Returns the bars (if any) of the triangle that lie on a hole.
   * @param iIdxTriangle
   *   The index of the triangle.
   * @param oIdxVertices
   *   The indices of the bar vertices that lie on a hole.
   *   Each bar is defined by a pair of vertices:
   *   (vrtx[0], vrtx[1]), (vrtx[2], vrtx[3]) and (vrtx[4], vrtx[5]).
   *   This array fills in in the order in which free bars are found.
   *   That is if only one hole is found then only (vrtx[0], vrtx[1]) is 
   *   defined.  The other vertices will be set to 0.
   * @param oNbBars
   *   The number of free bars.
   * @return 
   *   S_OK if the method runs successfully and E_FAIL otherwise.
   */
  HRESULT GetHoleBarsFromTriangle (const int iIdxTriangle, 
                                   int oIdxVertices[6],
                                   int & oNbBars) const;

  /**
   * Given a vertex on a hole, the method returns the two vertex neighbors that lie 
   * also on a hole.
   * @param iIdxVertex
   *   The index of a hole vertex.
   * @param oIdxVertex0
   *   One neighbor of the vertex.
   * @param oIdxVertex1
   *   A second neighbor of the vertex.
   * @return 
   *   S_OK if the method runs successfully and E_FAIL otherwise.
   */
  HRESULT GetHoleVertexNeighbors (const int iIdxVertex,
                                  int & oIdxVertex0,
                                  int & oIdxVertex1) const;

  /**
   * Checks whether two vertices belong to the same triangle.
   * @param vertex0
   *   The index of the first vertex.
   * @param vertex1
   *   The index of the second vertex.
   * @return
   *   The triangle number if they belong to the same triangle and 0 otherwise.
   */
  HRESULT CheckSameTriangleVertexVertex (const int vertex0, const int vertex1,
                                         int & returnTriangle);

  /**
   * Checks whether a vertex and a bar belongs to the same triangle.
   * @param vertex
   *   The index of the vertex.
   * @param barVertex0
   *   The index of the first vertex of the bar.
   * @param barVertex1
   *   The index of the second vertex of the bar.
   * @return
   *   The triangle number if they belong to the same triangle and 0 otherwise.
   */
  HRESULT CheckSameTriangleVertexBar (const int vertex,
                                      const int barVertex0, const int barVertex1,
                                      int & returnTriangle);

  /**
   * Checks whether a vertex belong to a triangle.
   * @param vertex
   *   The index of the vertex.
   * @param triangle
   *   The index of the triangle.
   * @return
   *   The triangle number if the vertex belongs to the triangle and 0 otherwise.
   */
  HRESULT CheckSameTriangleVertexTriangle (const int vertex, const int triangle, int & returnTriangle);

  /**
   * Checks whether two bars belong to the same triangle.
   * @param bar0Vertex0
   *   The index of the first vertex of the first bar.
   * @param bar0Vertex1
   *   The index of the second vertex of the first bar.
   * @param bar1Vertex0
   *   The index of the first vertex of the second bar.
   * @param bar1Vertex1
   *   The index of the second vertex of the second bar.
   * @return
   *   The triangle number if they belong to the same triangle and 0 otherwise.
   */
  HRESULT CheckSameTriangleBarBar (const int bar0Vertex0,
                                   const int bar0Vertex1,
                                   const int bar1Vertex0,
                                   const int bar1Vertex1,
                                   int & returnTriangle);

  /**
   * Checks whether a bar belongs to a triangle.
   * @param barVertex0
   *   The index of the first vertex of the bar.
   * @param barVertex1
   *   The index of the second vertex of the bar.
   * @param triangle
   *   The index of the triangle.
   * @return
   *   The triangle number if the bar belongs to the triangle and 0 otherwise.
   */
  HRESULT CheckSameTriangleBarTriangle (const int barVertex0, const int barVertex1,
                                        const int triangle,
                                        int & returnTriangle);

private :

  const CATIPolyMesh* _PolyMesh;
  CATIPolySurfaceVertexFacetNeighborhood* _Neighborhood;

};


inline CATBoolean CATPolyTopoUtil::BarEqual (const int bar0V0, const int bar0V1,
                                             const int bar1V0, const int bar1V1)
{
  return ((bar0V0 == bar1V0 && bar0V1 == bar1V1) || (bar0V0 == bar1V1 && bar0V1 == bar1V0)) ? TRUE : FALSE;
}


#endif

