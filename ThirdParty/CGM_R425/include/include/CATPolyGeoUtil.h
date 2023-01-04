// COPYRIGHT DASSAULT SYSTEMES 2003, all rights reserved
//===================================================================
//
// CATPolyGeoUtil.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// Oct 2008 RAQ Changement signature de GetVertexNormal
// Sep 2003 Creation: dhp/ndo
//===================================================================
#ifndef CATPolyGeoUtil_h
#define CATPolyGeoUtil_h

#include "PolyhedralUtilities.h"
#include "CATErrorDef.h"     // HRESULT definition
#include "CATBoolean.h"
#include "CATListOfInt.h"

class CATIPolyMesh;
class CATIPolySurfaceVertexPositionConstLayer;
class CATMathVector;
class CATMathPlane;
class CATMathBox;


class ExportedByPolyhedralUtilities CATPolyGeoUtil
{

public :

  /**
  * Constructor.
  */
	CATPolyGeoUtil (const CATIPolyMesh * polyMesh);

  /**
  * Destructor.
  */
	~CATPolyGeoUtil (void);

  /**
   * Calculates the maximum coordinate in absolute value of the bounding box of the mesh.
   */
  HRESULT GetMaximumVertexCoordinate (double& oMaxCoordinate) const;

  
  /**
   * Calculates the normalized normal at a given vertex.
   *
   * @param iIdxVertex
   * The vertex index in the CATIPolyMesh
   * @param oNormal
   * The computed normal
   * @iNormalize
   * If TRUE the normal is the normalized sum over the adjacent triangles of the normalized normals, else it is
   * the normalized sum of the adjacent triangles normals.
   **/
  HRESULT GetVertexNormal(const int iIdxVertex,
                          CATMathVector& oNormal,
                          const CATBoolean iNormalize = FALSE) const;

  HRESULT GetBarNormal (const int iIdxVertex0,
                        const int iIdxVertex1,
                        CATMathVector & oNormal) const;

  HRESULT GetTriangleNormal (const int iIdxTriangle,
                             CATMathVector & oNormal,
                             double * iToleranceOnNorm = 0) const; // default tolerance is 1e-15

  HRESULT GetTrianglePlane (const int iIdxTriangle,
                            CATMathPlane & oPlane) const;

  /**
   * Calculates the normalized normal at a given vertex.
   *
   * @param iIdxTriangle
   * The triangle index in the CATIPolyMesh
   * @param oNormal
   * The computed area of the triangle
   **/
  HRESULT GetTriangleArea (const int iIdxTriangle,
                           double & oArea) const;

  /**
   * Computes and returns the length of the bar defined by two vertices. 
   * The two vertices must define a valid bar.
   * @param iIdxVertex0
   *   The index of the first vertex of the bar.
   * @param iIdxVertex1
   *   The index of the second vertex of the bar.
   * @param oLength
   *   The distance between the two vertices.
   * @return 
   *   S_OK if the method runs successfully and E_FAIL otherwise.
   */
  HRESULT GetBarLength (const int iIdxVertex0,
                        const int iIdxVertex1,
                        double & oLength) const;

  /**
   * Finds the index of the bar of maximum length in a triangle.
   * @param iIdxTriangle
   *   The triangle.
   *   <b>Legal values</b>: 1 to the number of triangles, inclusive.
   * @param oBarIndex
   *   The index of the bar with maximum length (0, 1 or 2.)
   * @return
   *   S_OK if the method runs successfully and E_FAIL otherwise.
   */
  HRESULT GetMaximumBar (const int iIdxTriangle,
                         int & oBarIndex) const;

  /**
   * Finds the index of the bar of minimum length in a triangle.
   * @param iIdxTriangle
   *   The triangle.
   *   <b>Legal values</b>: 1 to the number of triangles, inclusive.
   * @param oBarIndex
   *   The index of the bar with minimum length (0, 1 or 2.)
   * @return
   *   S_OK if the method runs successfully and E_FAIL otherwise.
   */
  HRESULT GetMinimumBar (const int iIdxTriangle,
                         int & oBarIndex) const;

  /**
   * Tests if the two vertices forms the bar of maximum length in the triangle.
   * @param iIdxTriangle
   *   The triangle.
   *   <b>Legal values</b>: 1 to the number of triangles, inclusive.
   * @param iIdxVertex0
   *   The index of the first vertex of the bar.
   * @param iIdxVertex1
   *   The index of the second vertex of the bar.
   * @return
   *   TRUE if the vertices forms the bar of maximum length in the triangle
   *   and FALSE otherwise.
   */
  CATBoolean IsMaximumBar (const int iIdxTriangle,
                           const int iIdxVertex0,
                           const int iIdxVertex1) const;

  /**
  * Returns the angles associated with each vertex in the triangle.
  * @param triangle
  *   The triangle whose angles are desired.
  * @param angle0
  *   The angle associated with the first vertex.
  * @param angle1
  *   The angle associated with the second vertex.
  * @param angle2
  *   The angle associated with the third vertex.
  */

  HRESULT GetAngles (const int triangle,
                     double & angle0, double & angle1, double & angle2);

  HRESULT GetAngleCosines (const int triangle,
                           double & cosine0, double & cosine1, double & cosine2);

  /**
  * Returns the angles associated with each vertex in the triangle
  * in sorted order from largest to smallest.
  * @param triangle
  *   The triangle whose angles are desired.
  * @param angle0
  *   The largest angle.
  * @param angle1
  *   The second largest angle.
  * @param angle2
  *   The smallest angle.
  */

  HRESULT GetSortedAngles (const int triangle, 
                           double & angle0, double & angle1, double & angle2);

  /**
  * Returns the angles associated with each vertex in the triangle
  * in sorted order from largest to smallest. It also returns
  * the vertex indices associated with each angle (from 0 to 2,
  * inclusive).
  * @param triangle
  *   The triangle whose angles are desired.
  * @param angle0
  *   The largest angle.
  * @param angle1
  *   The second largest angle.
  * @param angle2
  *   The smallest angle.
  * @param vertexIndex0
  *   The vertex index (0 to 2) of the vertex with the largest angle.
  * @param vertexIndex1
  *   The vertex index (0 to 2) of the vertex with the second largest angle.
  * @param vertexIndex2
  *   The vertex index (0 to 2) of the vertex with the smallest angle.
  */

  HRESULT GetSortedAngles (const int triangle,
                           double & angle0, double & angle1, double & angle2,
                           int & vertexIndex0, int & vertexIndex1, int & vertexIndex2);

  /**
  * Returns the smallest angle in the triangle.
  * @param triangle
  *   The triangle whose smallest angle is desired.
  * @param vertexIndex
  *   The index of the vertex (0 to 2, inclusive) with the
  *   smallest associated angle.
  * @param angle
  *   The value of the smallest angle.
  */

  HRESULT GetMinimumAngle (const int triangle,
                           int & vertexIndex,
                           double & angle);

  /**
  * Returns the largest angle in the triangle.
  * @param triangle
  *   The triangle whose largest angle is desired.
  * @param vertexIndex
  *   The index of the vertex (0 to 2, inclusive) with the
  *   largest associated angle.
  * @param angle
  *   The value of the largest angle.
  */

  HRESULT GetMaximumAngle (const int triangle,
                           int & vertexIndex,
                           double & angle);

  HRESULT GetBox (const CATListOfInt & vertices,
                  const CATBoolean clearBox,
                  CATMathBox & box);

private :

  const CATIPolyMesh* _PolyMesh;
  CATIPolySurfaceVertexPositionConstLayer* _VertexCoords;

};

#endif

