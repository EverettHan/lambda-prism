// COPYRIGHT DASSAULT SYSTEMES 2003-2013, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyTriangleUtil.h
//
//===================================================================
// Sep 2003 Creation: dhp
//===================================================================
#ifndef CATPolyTriangleUtil_h
#define CATPolyTriangleUtil_h

#include "PolyMathUtils.h"
#include "CATBoolean.h"
#include "CATPolyTriangleServices.h"
#include "CATPolyGeoServices.h"

class CATMathPoint;
class CATMathPoint2D;
class CATMathVector;
class CATMathSetOfPoints;


/**
* Services for triangles.
* @see CATPolyTriangleServices
*/
class ExportedByPolyMathUtils CATPolyTriangleUtil
{

public :

  /**
  * Computes the bar lengths and the height and cosines of the triangle represented by the points A, B and C.
  * @param A
  *   The first point.
  * @param B
  *   The second point.
  * @param C
  *   The third point.
  * @param oLength0
  *   The length of the AB bar.
  * @param oLength1
  *   The length of the BC bar.
  * @param oLength2
  *   The length of the CA bar.
  * @param oHeight
  *   The height of the triangle (smallest height.)
  * @param oCosine0
  *   The cosine of the angle at A.
  * @param oCosine1
  *   The cosine of the angle at B.
  * @param oCosine2
  *   The cosine of the angle at C.
  * @return
  *   The index of the vertex dropped to the base to calculate the height: 0, 1 or 2 for A, B or C respectively.
  */
  static int GetBarLengthsAndHeightAndCosines (const CATMathPoint & A,
                                               const CATMathPoint & B,
                                               const CATMathPoint & C,
                                               double & oLength0,
                                               double & oLength1,
                                               double & oLength2,
                                               double & oHeight,
                                               double & oCosine0,
                                               double & oCosine1,
                                               double & oCosine2);

  /**
   * @see CATPolyComputeTriangleArea
   */
  static double GetTriangleArea (const CATMathPoint& A, const CATMathPoint& B, const CATMathPoint& C)
    {return CATPolyComputeTriangleArea (A, B, C);}

  /**
  * Computes the area of a polygon. It's assume that the points are
  * planar and that they represent a simple polygon (one with no
  * self-intersections).
  * @param points
  *   The points in the polygon.
  * @return
  *   The area of the polygon.
  */
  static double GetPolygonArea (const CATMathSetOfPoints & points);

  /**
  * Computes the edge lengths of the triangle represented by the points
  * <tt>iPoint0</tt>,<tt>iPoint1</tt>, and <tt>iPoint2</tt>.
  * @param iPoint0
  *   The location of the first vertex.
  * @param iPoint1
  *   The location of the second vertex.
  * @param iPoint2
  *   The location of the third vertex.
  * @param oLength0
  *   The length of the edge from <tt>iPoint0</tt> to <tt>iPoint1</tt>.
  * @param oLength1
  *   The length of the edge from <tt>iPoint1</tt> to <tt>iPoint2</tt>.
  * @param oLength2
  *   The length of the edge from <tt>iPoint2</tt> to <tt>iPoint0</tt>.
  */
  static void GetTriangleEdgeLengths (const CATMathPoint & iPoint0,
                                      const CATMathPoint & iPoint1,
                                      const CATMathPoint & iPoint2,
                                      double & oLength0,
                                      double & oLength1,
                                      double & oLength2);

  /**
  * Computes the cosines of the angles of the triangle represented by the points
  * <tt>iPoint0</tt>,<tt>iPoint1</tt>, and <tt>iPoint2</tt>.
  * @param iPoint0
  *   The location of the first vertex.
  * @param iPoint1
  *   The location of the second vertex.
  * @param iPoint2
  *   The location of the third vertex.
  * @param oCosine0
  *   The cosine of the angle formed by the edges sharing <tt>iPoint0</tt>.
  * @param oCosine1
  *   The cosine of the angle formed by the edges sharing <tt>iPoint1</tt>.
  * @param oCosine2
  *   The cosine of the angle formed by the edges sharing <tt>iPoint2</tt>.
  */
  static void GetTriangleAngleCosines (const CATMathPoint & iPoint0,
                                       const CATMathPoint & iPoint1,
                                       const CATMathPoint & iPoint2,
                                       double & oCosine0,
                                       double & oCosine1,
                                       double & oCosine2);

  /**
  * Computes the angles of the triangle represented by the points
  * <tt>iPoint0</tt>,<tt>iPoint1</tt>, and <tt>iPoint2</tt>.
  * @param iPoint0
  *   The location of the first vertex.
  * @param iPoint1
  *   The location of the second vertex.
  * @param iPoint2
  *   The location of the third vertex.
  * @param oAngle0
  *   The angle formed by the edges sharing <tt>iPoint0</tt>.
  * @param oAngle1
  *   The angle formed by the edges sharing <tt>iPoint1</tt>.
  * @param oAngle2
  *   The angle formed by the edges sharing <tt>iPoint2</tt>.
  */
  static void GetTriangleAngles (const CATMathPoint & iPoint0,
                                 const CATMathPoint & iPoint1,
                                 const CATMathPoint & iPoint2,
                                 double & oAngle0,
                                 double & oAngle1,
                                 double & oAngle2);

  /**
  * Computes the edge lengths and the cosines of the angles of the triangle
  * represented by the points <tt>iPoint0</tt>,<tt>iPoint1</tt>,
  * and <tt>iPoint2</tt>.
  * @param iPoint0
  *   The location of the first vertex.
  * @param iPoint1
  *   The location of the second vertex.
  * @param iPoint2
  *   The location of the third vertex.
  * @param oLength0
  *   The length of the edge from <tt>iPoint0</tt> to <tt>iPoint1</tt>.
  * @param oLength1
  *   The length of the edge from <tt>iPoint1</tt> to <tt>iPoint2</tt>.
  * @param oLength2
  *   The length of the edge from <tt>iPoint2</tt> to <tt>iPoint0</tt>.
  * @param oCosine0
  *   The cosine of the angle formed by the edges sharing <tt>iPoint0</tt>.
  * @param oCosine1
  *   The cosine of the angle formed by the edges sharing <tt>iPoint1</tt>.
  * @param oCosine2
  *   The cosine of the angle formed by the edges sharing <tt>iPoint2</tt>.
  */
  static void GetTriangleEdgeLengthsAngleCosines (const CATMathPoint & iPoint0,
                                                  const CATMathPoint & iPoint1,
                                                  const CATMathPoint & iPoint2,
                                                  double & oLength0,
                                                  double & oLength1,
                                                  double & oLength2,
                                                  double & oCosine0,
                                                  double & oCosine1,
                                                  double & oCosine2);

  /**
  * Computes the edge lengths and the angles of the triangle
  * represented by the points <tt>iPoint0</tt>,<tt>iPoint1</tt>,
  * and <tt>iPoint2</tt>.
  * @param iPoint0
  *   The location of the first vertex.
  * @param iPoint1
  *   The location of the second vertex.
  * @param iPoint2
  *   The location of the third vertex.
  * @param oLength0
  *   The length of the edge from <tt>iPoint0</tt> to <tt>iPoint1</tt>.
  * @param oLength1
  *   The length of the edge from <tt>iPoint1</tt> to <tt>iPoint2</tt>.
  * @param oLength2
  *   The length of the edge from <tt>iPoint2</tt> to <tt>iPoint0</tt>.
  * @param oAngle0
  *   The angle formed by the edges sharing <tt>iPoint0</tt>.
  * @param oAngle1
  *   The angle formed by the edges sharing <tt>iPoint1</tt>.
  * @param oAngle2
  *   The angle formed by the edges sharing <tt>iPoint2</tt>.
  */
  static void GetTriangleEdgeLengthsAngles (const CATMathPoint & iPoint0,
                                            const CATMathPoint & iPoint1,
                                            const CATMathPoint & iPoint2,
                                            double & oLength0,
                                            double & oLength1,
                                            double & oLength2,
                                            double & oAngle0,
                                            double & oAngle1,
                                            double & oAngle2);

  static double GetDihedralAngle (const CATMathPoint & iTri0Point0,
                                  const CATMathPoint & iTri0Point1,
                                  const CATMathPoint & iTri0Point2,
                                  const CATMathPoint & iTri1Point0,
                                  const CATMathPoint & iTri1Point1,
                                  const CATMathPoint & iTri1Point2);

public:

  /**
  * Compare the orientation of the normals of two coplanar triangles.
  * @param iTri0Point0
  *   The first vertex of Triangle 0.
  * @param iTri0Point1
  *   The second vertex of Triangle 0.
  * @param iTri0Point2
  *   The third vertex of Triangle 0.
  * @param iTri1Point0
  *   The first vertex of Triangle 1.
  * @param iTri1Point1
  *   The second vertex of Triangle 1.
  * @param iTri1Point2
  *   The third vertex of Triangle 1.
  * @return
  *   +1: if the normals are in the same direction.
  *   -1: if the normals are in the opposite direction.
  */
  static int CompareTriangleNormals (const CATMathPoint & iTri0Point0,
                                     const CATMathPoint & iTri0Point1,
                                     const CATMathPoint & iTri0Point2,
                                     const CATMathPoint & iTri1Point0,
                                     const CATMathPoint & iTri1Point1,
                                     const CATMathPoint & iTri1Point2);

  /**
  * Compare the orientation of the triangle defined by the three points to the direction of a main axis.
  * @param dir
  *   -3: -z
  *   -2: -y
  *   -1: -x 
  *   +1: +x
  *   +2: +y
  *   +3: +z
  * @return
  *   +1: the normal to the triangle has the same general direction as the axis.
  *    0: the normal to the triangle is orthogonal to the axis.
  *   -1: the normal to the triangle has the opposite direction to the axis.
  */
  static int CompareOrientationToDirection (const CATMathPoint& A,
                                            const CATMathPoint& B,
                                            const CATMathPoint& C,
                                            const int dir);

public:

  /**
   * @see CATPolyGetMainAxisDirection
   */
  static int GetProjectionDirTo2D (const CATMathVector& N) {return CATPolyGetMainAxisDirection (N);}

  /**
   * @see CATPolyGetMainTriangleDirection
   */
  static int GetProjectionDirTo2D (const CATMathPoint& A, const CATMathPoint& B, const CATMathPoint& C)
    {return CATPolyGetMainTriangleDirection (A, B, C);}

  /**
  * Project a point to 2D along one of the cartesian direction.
  * @param iPoint
  *   The input point.
  * @param dir
  *   The direction (see ProjectTriangleTo2D)
  * @param oPoint
  *   The output point.
  */
  static void ProjectPointTo2D (const CATMathPoint & iPoint, const int dir, CATMathPoint2D & oPoint)
    {CATPolyProjectOntoCartesianPlane (dir, iPoint, oPoint);}

  /**
  * Project a triangle to a 2D cartesian plane along the main direction of its normal vector.
  * This is equivalent to dropping one of the 3D point coordinates.  The method returns the 
  * direction along which the triangle was projected.
  * @param iPoint0
  *   The first vertex.
  * @param iPoint1
  *   The second vertex.
  * @param iPoint2
  *   The third vertex.
  * @param oPoint0
  *   The first vertex of the projected triangle.
  * @param oPoint1
  *   The second vertex of the projected triangle.
  * @param oPoint2
  *   The third vertex of the projected triangle.
  * @return
  *   The direction along which the triangle was projected:
  *   -3: (X,Y,Z) ==> (Y,X)
  *   -2: (X,Y,Z) ==> (X,Z)
  *   -1: (X,Y,Z) ==> (Z,Y)
  *    0: The projection failed (degenerate triangle.)
  *   +1: (X,Y,Z) ==> (Y,Z)
  *   +2: (X,Y,Z) ==> (Z,X)
  *   +3: (X,Y,Z) ==> (X,Y)
  */
  static int ProjectTriangleTo2D (const CATMathPoint & iPoint0,
                                  const CATMathPoint & iPoint1,
                                  const CATMathPoint & iPoint2,
                                  CATMathPoint2D & oPoint0,
                                  CATMathPoint2D & oPoint1,
                                  CATMathPoint2D & oPoint2);

};

#endif
