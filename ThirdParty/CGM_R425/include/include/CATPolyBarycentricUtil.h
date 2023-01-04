// COPYRIGHT Dassault Systemes 2003, all rights reserved.
//===================================================================
//
// CATPolyBarycentricUtil.h
// Header definition of CATPolyBarycentricUtil.
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
//  oct 2003 Creation: dhp
//===================================================================
#ifndef CATPolyBarycentricUtil_h
#define CATPolyBarycentricUtil_h

#include "PolyMathUtils.h"
#include "CATBoolean.h"

class CATMathPoint;
class CATMathVector;

/**
* Class used to compute the barycentric coordinates of a point
* with respect to a triangle.
*/

class ExportedByPolyMathUtils CATPolyBarycentricUtil
{

public :

  /**
  * Default constructor.
  */
  CATPolyBarycentricUtil (void);

  /**
  * Destructor.
  */
  ~CATPolyBarycentricUtil (void);

  /**
  * Computes the barycentric coordinates (signed values) of a point <tt>p</tt> with respect
  * to the line segment defined by <tt>(a, b)</tt>.  This method assumes the points <tt> (a, b, p) </tt>
  * are colinear (no check).
  * @param a
  *   The first point of the line segment.
  * @param b
  *   The second point of the line segment.
  * @param p
  *   The point whose barycentric coordinates are computed.
  * @param u
  *   The first barycentric coordinate of the point.
  * @param v
  *   The second barycentric coordinate of the point.
  * @return
  *   TRUE if the barycentric calculation is successful (distance between a and b differs from 0) and 
  *   FALSE otherwise.
  */
  static CATBoolean GetCoords (
    const CATMathPoint& a,
    const CATMathPoint& b,
    const CATMathPoint& p,
    double& u,
    double& v);

  /**
  * Computes the barycentric coordinates (signed values) of a point <tt>p</tt> with respect
  * to the line segment defined by <tt>(a, b)</tt>.  This method assumes the points <tt> (a, b, p) </tt>
  * are colinear (no check).
  * @param a
  *   The first point of the line segment.
  * @param b
  *   The second point of the line segment.
  * @param p
  *   The point whose barycentric coordinates are computed.
  * @param u
  *   The first barycentric coordinate of the point.
  * @param v
  *   The second barycentric coordinate of the point.
  * @param distanceAB
  *   The distance between the two points a and b.
  * @return
  *   TRUE if the barycentric calculation is successful (distance between a and b differs from 0) and 
  *   FALSE otherwise.
  */
  static CATBoolean GetCoords (
    const CATMathPoint& a,
    const CATMathPoint& b,
    const CATMathPoint& p,
    double& u,
    double& v,
    double& distanceAB);

  /**
  * Computes the barycentric coordinates (signed values) of a point <tt>p</tt> with respect
  * to the triangle defined by <tt>(a, b, c)</tt>.  This method assumes the points <tt> (a, b, c, p) </tt>
  * are coplanar (no check).
  * @param a
  *   The first vertex of the triangle.
  * @param b
  *   The second vertex of the triangle.
  * @param c
  *   The third vertex of the triangle.
  * @param p
  *   The point whose barycentric coordinates are computed.
  * @param u
  *   The first barycentric coordinate of the point.
  * @param v
  *   The second barycentric coordinate of the point.
  * @param w
  *   The third barycentric coordinate of the point.
  * @return
  *   TRUE if the barycentric calculation is successful (area of triangle differs from 0) and FALSE otherwise.
  */
  static CATBoolean GetCoords (
    const CATMathPoint& a,
    const CATMathPoint& b,
    const CATMathPoint& c,
    const CATMathPoint& p,
    double& u,
    double& v,
    double& w);

  /**
  * Computes the barycentric coordinates (signed values) of a point <tt>p</tt> with respect
  * to the triangle defined by <tt>(a, b, c)</tt>.  This method assumes the points <tt> (a, b, c, p) </tt>
  * are coplanar (no check).
  * @param a
  *   The first vertex of the triangle.
  * @param b
  *   The second vertex of the triangle.
  * @param c
  *   The third vertex of the triangle.
  * @param p
  *   The point whose barycentric coordinates are computed.
  * @param u
  *   The first barycentric coordinate of the point.
  * @param v
  *   The second barycentric coordinate of the point.
  * @param w
  *   The third barycentric coordinate of the point.
  * @param areaABC
  *   The area of the triangle (a, b, c).
  * @return
  *   TRUE if the barycentric calculation is successful (area of triangle differs from 0) and FALSE otherwise.
  */
  static CATBoolean GetCoords (
    const CATMathPoint& a,
    const CATMathPoint& b,
    const CATMathPoint& c,
    const CATMathPoint& p,
    double& u,
    double& v,
    double& w,
    double& areaABC);

  /**
  * Computes the barycentric coordinates (signed values) of a point <tt>p</tt> with respect
  * to the triangle defined by <tt>(a, b, c)</tt>.  This method assumes the points <tt> (a, b, c, p) </tt>
  * are coplanar (no check).
  * @param a
  *   The first vertex of the triangle.
  * @param b
  *   The second vertex of the triangle.
  * @param c
  *   The third vertex of the triangle.
  * @param p
  *   The point whose barycentric coordinates are computed.
  * @param oBary
  *   The barycentric coordinate of the point with respect to the triangle (a, b, c).
  * @return
  *   TRUE if the barycentric calculation is successful (area of triangle differs from 0) and FALSE otherwise.
  */
  static CATBoolean GetCoords (
    const CATMathPoint& a,
    const CATMathPoint& b,
    const CATMathPoint& c,
    const CATMathPoint& p,
    CATMathPoint& oBary);

};

#endif
