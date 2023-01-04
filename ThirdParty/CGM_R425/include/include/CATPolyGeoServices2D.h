// COPYRIGHT DASSAULT SYSTEMES 2016, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyGeoServices2D.h
//
//===================================================================
// March 2016 Creation: ndo
//===================================================================
#ifndef CATPolyGeoServices2D_h
#define CATPolyGeoServices2D_h

#include "PolyMathUtils.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"

#include "CATMathPoint2D.h"


/** @file 
 * Various geometric services about points in the plane.
 * @see CATPolyGeoServices.h
 *
 * List of services:
 * <ul>
 *   <li> Lexicographical comparison between points.
 *   <li> Test of inclusion of a point inside a two-dimensional polygon.
 *  </ul>
 */


/**
 * Returns the cartesian direction (main axis) of the segment PQ.
 * @return
 * <ul>
 *   <li> -2: -y
 *   <li> -1: -x 
 *   <li>  0: Null Vector
 *   <li> +1: +x
 *   <li> +2: +y
 * </ul>
 */
ExportedByPolyMathUtils int CATPolyGetMainSegmentDirection (const CATMathPoint2D& P, const CATMathPoint2D& Q);


 /**
  * Projects a point onto the axis.
  * If the direction has negative sign, then the sign of the returned coordinate changes.
  * @param P
  *   The input point.
  * @param dir
  *   The direction of the projection.
  *   @see CATPolyGetMainSegmentDirection
  * @return
  *   A coordinate of the point with an eventual change of sign.
  */
ExportedByPolyMathUtils double CATPolyProjectOnAxis (const CATMathPoint2D& P, const int dir);


namespace Poly
{

  /** @name Point Services
   *
   * CATPolyGeoServices2D.h
   * @{ */

  /**
   * Returns true if the points are equal and false otherwise.
   */
  ExportedByPolyMathUtils inline bool Equal (const CATMathPoint2D& A, const CATMathPoint2D& B);

  /**
  * Compares the two points lexicographically according to the values of their x and y coordinates.
  * The method compares the x-coordinates of the two points;
  * if the x-coordinates are equal, then it compares the y-coordinates.
  * @return
  *   <ul>
  *     <li> +1 if xA > xB or (xA = xB and yA > yB)   (A is right of B)
  *     <li> 0 if xA = xB and yA = yB                 (A is equal to B)
  *     <li> -1 if xA < xB or (xA = xB and yA < yB)   (A is left of B)
  *   </ul>
  */
  ExportedByPolyMathUtils int CompareLeftRight (const CATMathPoint2D& A, const CATMathPoint2D& B);


  /**
  * Compares the y-coordinates of two points; if the y-coordinates are equal,
  * then compares the x-coordinates of the two points.
  * @param A
  *   The first point.
  * @param B
  *   The second point.
  * @return
  * <ul>
  *   <li> +1 if yA > yB or yA = yB and xA > xB     (A is above of B)
  *   <li>  0 if yA = yB and xA = xB                (A is equal to B)
  *   <li> -1 if yA < yB or yA = yB and xA < xB     (A is below of B)
  * </ul>
  */
  ExportedByPolyMathUtils int CompareBelowAbove (const CATMathPoint2D& A, const CATMathPoint2D& B);

/** @} */

};


namespace Poly
{

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
  *   The computed distance between A and B.
  * @return
  * <ul>
  *   <li> <tt>S_OK</tt> if the barycentric coordinates are successfully computed.
  *   <li> <tt>E_FAIL</tt> if an error occurs (distance between A and B is null.)
  * </ul>
  */
  ExportedByPolyMathUtils HRESULT ComputeBarycentricCoordinates (const CATMathPoint2D& A, const CATMathPoint2D& B,
                                                                 const CATMathPoint2D& P,
                                                                 double& u, double& v,
                                                                 double* oDistanceAB = 0);

/** @} */

};


inline bool Poly::Equal (const CATMathPoint2D& A, const CATMathPoint2D& B)
{
  return (A.GetX () == B.GetX () && A.GetY () == B.GetY ()) ? 1 : 0;
}

#endif
