// COPYRIGHT DASSAULT SYSTEMES 2014, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyGeoServices.h
//
//===================================================================
// June 2014 Creation: ndo
//===================================================================
#ifndef CATPolyGeoServices_h
#define CATPolyGeoServices_h

#include "PolyMathUtils.h"
#include "CATErrorDef.h"
#include "CATPolyGeoServices2D.h"
#include "CATMathPoint.h"

class CATMathVector;
class CATMathBox;
class CATMathPoint2D;
class CATMathBox2D;
class CATPolyExactArithmetic;


/** @file
* Geometric services about points.
*
* List of services:
* <ul>
*   <li> Lexicographical comparison between points.
*   <li> Test of inclusion of a point inside a two-dimensional polygon.
*   <li> Computation of cartesian directions of a vector, segment and triangle and cartesian projections.
*  </ul>
*/


namespace Poly
{

  /** @name Point Services
   *
   * CATPolyGeoServices.h
   * @{ */

  /**
   * Returns true if the points are equal and false otherwise.
   */
  inline bool Equal (const CATMathPoint& A, const CATMathPoint& B);

  /**
  * Compares two points lexicographically according to the values of their x, y and z coordinates.
  * The method compares the x-coordinates of the two points;
  * if the x-coordinates are equal, then it compares the y-coordinates and if the y-coordinates are equal, then it compares the z-coordinates.
  * @param A
  *   The first point.
  * @param B
  *   The second point.
  * @return
  *   <ul>
  *     <li> +1 if xA > xB or (xA = xB and yA > yB) or (xA = xB and yA = yB and zA > zB)   (A is right of B)
  *     <li> 0 if xA = xB and yA = yB and zA = zB                                          (A is equal to B)
  *     <li> -1 if xA < xB or (xA = xB and yA < yB) or (xA = xB and yA = yB and zA < zB)   (A is left of B)
  *   </ul>
  */
  ExportedByPolyMathUtils int CompareLeftRight (const CATMathPoint& A, const CATMathPoint& B);

  /**
  * Compares two points lexicographically according to the values of their z, y and x coordinates.
  * The method compares the z-coordinates of the two points;
  * if the z-coordinates are equal, then it compares the y-coordinates and if the y-coordinates are equal, then it compares the x-coordinates.
  * @param A
  *   The first point.
  * @param B
  *   The second point.
  * @return
  *   <ul>
  *     <li> +1 if zA > zB or (zA = zB and yA > yB) or (zA = zB and yA = yB and xA > xB)   (A is above of B)
  *     <li> 0 if xA = xB and yA = yB and zA = zB                                          (A is equal to B)
  *     <li> -1 if zA < zB or (zA = zB and yA < yB) or (zA = zB and yA = yB and xA < xB)   (A is below of B)
  *   </ul>
  */
  ExportedByPolyMathUtils int CompareBelowAbove (const CATMathPoint& A, const CATMathPoint& B);

/** @} */

};


namespace Poly
{

/** @name Barycentric Coordinates
@{ */


  /**
   * Normalizes a vector regardless of the value of its norm.
   * If its norm is equal to 0, then the method returns <tt>S_FALSE</tt>
   * Otherwise, it returns <tt>S_OK</tt>.
   */
  ExportedByPolyMathUtils HRESULT Normalize (CATMathVector& N);

  /**
   * Applies the barycentric coordinates to three normals to compute the new normal.
   * Thr output normal is normalized.
   */
  ExportedByPolyMathUtils HRESULT ApplyBaryCoordinatesAndNormalize (const CATMathVector & Na, const CATMathVector & Nb, const CATMathVector & Nc,
    double u, double v, double w, CATMathVector & oN);

  /**
   * Applies the barycentric coordinates to two normals to compute the new normal.
   * Thr output normal is normalized.
   */
  ExportedByPolyMathUtils HRESULT ApplyBaryCoordinatesAndNormalize (const CATMathVector & Na, const CATMathVector & Nb,
    double u, double v, CATMathVector & oN);

/** @} */

}


/** @name Cartesian Directions
@{ */

/**
* Returns the main axis direction of the vector.
* @return
* <ul>
*   <li> -3: -z
*   <li> -2: -y
*   <li> -1: -x
*   <li>  0: Null Vector
*   <li> +1: +x
*   <li> +2: +y
*   <li> +3: +z
* </ul>
*/
ExportedByPolyMathUtils int CATPolyGetMainAxisDirection (const CATMathVector& N);


/**
* Returns the main axis direction of the segment (A, B).
* @return
* <ul>
*   <li> -3: -z
*   <li> -2: -y
*   <li> -1: -x
*   <li>  0: Null Vector
*   <li> +1: +x
*   <li> +2: +y
*   <li> +3: +z
* </ul>
*/
ExportedByPolyMathUtils int CATPolyGetMainSegmentDirection (const CATMathPoint& A, const CATMathPoint& B);


/**
* Returns the main axis direction of the normal to the triangle (A, B, C).
* @return
* <ul>
*   <li> -3: -z
*   <li> -2: -y
*   <li> -1: -x
*   <li>  0: Null Vector
*   <li> +1: +x
*   <li> +2: +y
*   <li> +3: +z
* </ul>
*/
ExportedByPolyMathUtils int CATPolyGetMainTriangleDirection (const CATMathPoint& A, const CATMathPoint& B, const CATMathPoint& C);


/**
* Projects a point onto a cartesian plane.
* @param dir
*   The direction of the projection.
*   @see CATPolyGetMainAxisDirection
*   @see CATPolyGetMainTriangleDirection
* @param A
*   The input point.
* @param P
*   The output point (projection of A).
*/
ExportedByPolyMathUtils HRESULT CATPolyProjectOntoCartesianPlane (const int dir, const CATMathPoint& A, CATMathPoint2D& P);


/**
* Projects a point onto the axis.
* If the direction has negative sign, then the sign of the returned coordinate changes.
* @param P
*   The input point.
* @param dir
*   The direction of the projection.
*   @see CATPolyGetMainAxisDirection
* @return
*   A coordinate of the point with an eventual change of sign.
*/
ExportedByPolyMathUtils double CATPolyProjectOnAxis (const CATMathPoint& P, const int dir);

/** @} */


/** @name Bounding Box
@{ */

/**
* Returns the maximum coordinate in absolute value of the bounding box.
*/
ExportedByPolyMathUtils HRESULT CATPolyGetMaximumCoordinate (const CATMathBox2D& iMBox, double& oMaxCoordinate);

/**
* Returns the maximum coordinate in absolute value of the bounding box.
*/
ExportedByPolyMathUtils HRESULT CATPolyGetMaximumCoordinate (const CATMathBox& iMBox, double& oMaxCoordinate);

/** @} */


/** @name Barycentric Coordinates
@{ */

/**
* Computes the barycentric coordinates (signed values) of a point <tt>P</tt> with respect
* to the segment <tt>(A, B)</tt>.
* The point <tt>P</tt> should lie on the line <tt> (A, B) </tt>.
*
* @param A
*   The first input point.
* @param B
*   The second input point.
* @param P
*  The input point whose barycentric coordinates are computed.
* @param u
*   The output barycentric coordinate with respect to A.
* @param v
*   The output barycentric coordinate with respect to B.
* @param oDistanceAB
*   Optionally, the computed distance between A and B.
* @return
* <ul>
*   <li> <tt>S_OK</tt> if the barycentric coordinates are successfully computed.
*   <li> <tt>E_FAIL</tt> if an error occurs (triangle of null area.)
* </ul>
*/
ExportedByPolyMathUtils HRESULT CATPolyComputeBarycentricCoordinates (const CATMathPoint& A, const CATMathPoint& B,
  const CATMathPoint& P,
  double& u, double& v,
  double* oDistanceAB = 0);

/**
* Computes the barycentric coordinates (signed values) of a point <tt>P</tt> with respect
* to the triangle <tt>(A, B, C)</tt>.
* The point <tt>P</tt> should lie on the plane <tt> (A, B, C) </tt>.
*
* @param A
*   The first input point.
* @param B
*   The second input point.
* @param C
*   The third input point.
* @param P
*  The input point whose barycentric coordinates are computed.
* @param u
*   The output barycentric coordinate with respect to A.
* @param v
*   The output barycentric coordinate with respect to B.
* @param w
*   The output barycentric coordinate with respect to C.
* @param oAreaABC
*   Optionally, the computed area of the triangle <tt>(A, B, C)</tt>.
* @return
* <ul>
*   <li> <tt>S_OK</tt> if the barycentric coordinates are successfully computed.
*   <li> <tt>E_FAIL</tt> if an error occurs (triangle of null area.)
* </ul>
*/
ExportedByPolyMathUtils HRESULT CATPolyComputeBarycentricCoordinates (const CATMathPoint& A, const CATMathPoint& B, const CATMathPoint& C,
  const CATMathPoint& P,
  double& u, double& v, double& w,
  double* oAreaABC = 0);

/** @} */


/** @name Other Geometrical Services
@{ */

/**
* Tests if a point is inside, on or outside a polygon.
* The polygon is defined by a sequence of points forming a loop.
* A segment is automatically added between the last and first point of the sequence to close the loop.
* @param iPoints
*   The sequence of points.
* @param nbPoints
*   The number of points in the sequence.
* @param iPointToTest
*   The point to be tested.
* @param iExactArithmetic
*   An instance of exact arithmetic for the geometric tests.
* @param oSegment
*   An optional output parameter specifying the segment on which the point lies.
*   If s is equal as *oSegment, then the segment is defined by the pair of points: (s, s+1).
*   The last segment is defined by the pair of points: (s, 0).
* @return
* <ul>
*   <li> -1: The point is outside the polygon..
*   <li>  0: The point is on the polygon.
*   <li> +1: The point is inside the polygon.
* </ul>
*
* @see CATPolyPointInPolygonOper2D
*/
ExportedByPolyMathUtils int CATPolyIsInsidePolygon (const CATMathPoint2D iPoints[], const int nbPoints,
  const CATMathPoint2D& iPointToTest,
  const CATPolyExactArithmetic& iExactArithmetic,
  int* oSegment = 0);

/** @} */


namespace Poly
{

  /** @name Triangle Services
  * Overlapping triangles
  *
  * CATPolyGeoServices.h
  * @{ */

  /** Tests two triangles for an overlap.
  * An overlap is defined when there is at least three distinct contact points
  * (vertex-triangle or bar-bar within tolerance) between the two triangles.
  * @param P
  *   Three points defining the first triangle.
  * @param Q
  *   Three points defining the second triangle.
  * @param iTolerance
  *   The maximum acceptable distance for contact between the triangles.
  *   Contact points cannot be defined if their distance is greater than this tolerance.
  * @param oOrientation
  *   Relative orientation of the triangles:
  *   * -1 if the triangle normals are opposite;
  *   * +1 if the triangle normals have same orientation; or,
  *   *  0 if the triangles are nearly perpendicular
  *        (say with an angle between the normals in the 85-95 degree-range.)
  * @param iSymetricResult
  *   * If set to TRUE (default value), the result is symetric and tries to project the first triangle onto the second
  *     then the second on the first.
  *   * If set to FALSE check only the projection of the first triangle onto the second.
  * @return
  *   * S_OK if the triangles overlap;
  *   * S_FALSE otherwise.
  */
  ExportedByPolyMathUtils HRESULT AreTrianglesOverlapping (const CATMathPoint P[3], const CATMathPoint Q[3], const double iTolerance,
    const double iReclassificationTol, int & oOrientation, unsigned int * oLinkRegistry = NULL);


  /**
   * Test if the projected part of one triangle on the other one is under the provided tolerance.
   * It can be seen as a relaxed version of AreTrianglesOverlapping method since it'll allow non symetrical result.
   */
ExportedByPolyMathUtils HRESULT AreTrianglesPartiallyConfused (const CATMathPoint P[3], const CATMathPoint Q[3], const double iTolerance,
                                                               const double iReclassificationTol);
  /** @} */

};

inline bool Poly::Equal (const CATMathPoint& A, const CATMathPoint& B)
{
  return A.GetX () == B.GetX () && A.GetY () == B.GetY () && A.GetZ () == B.GetZ ();
}

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/**
* @see Poly::AreTrianglesOverlapping
* The Links Registry is an integer that stores all possible links with
* others patches for this patch, according to bars that were
* projected during the detection and overlaying bars couples. There
* are 15 possible bar-triangle and bar-bar links, each encoded by a
* bit. Bar-bar links imply the two bars can be overlaid.
*  1: bar 1 - triangle
*  2: bar 2 - triangle
*  3: bar 3 - triangle
*  4: triangle - bar 1
*  5: triangle - bar 2
*  6: triangle - bar 3
*  7: bar 1 - bar 1
*  8: bar 1 - bar 2
*  9: bar 1 - bar 3
* 10: bar 2 - bar 1
* 11: bar 2 - bar 2
* 12: bar 2 - bar 3
* 13: bar 3 - bar 1
* 14: bar 3 - bar 2
* 15: bar 3 - bar 3
*/
inline HRESULT PatchTriangleTriangle (const CATMathPoint iTriangle1[3], const CATMathPoint iTriangle2[3], const double iTolerance, const double iReclassificationTol, int & oOrientation, unsigned int * oLinkRegistry = NULL)
{
  return Poly::AreTrianglesOverlapping (iTriangle1, iTriangle2, iTolerance, iReclassificationTol, oOrientation, oLinkRegistry);
}

inline int CATPolyCompareLeftRight (const CATMathPoint& A, const CATMathPoint& B)
{
  return Poly::CompareLeftRight (A, B);
}

inline int CATPolyCompareBelowAbove (const CATMathPoint& A, const CATMathPoint& B)
{
  return Poly::CompareBelowAbove (A, B);
}

inline int CATPolyCompareLeftRight (const CATMathPoint2D& A, const CATMathPoint2D& B)
{
  return Poly::CompareLeftRight (A, B);
}

inline int CATPolyCompareBelowAbove (const CATMathPoint2D& A, const CATMathPoint2D& B)
{
  return Poly::CompareBelowAbove (A, B);
}

inline HRESULT CATPolyDoNormalize (CATMathVector& N)
{
  return Poly::Normalize (N);
}

#endif

#endif
