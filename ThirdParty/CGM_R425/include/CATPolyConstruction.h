// COPYRIGHT DASSAULT SYSTEMES 2004, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyConstruction.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// Aug 2004 Creation: NDO
//===================================================================
#ifndef CATPolyConstruction_h
#define CATPolyConstruction_h

#include "PolyMathArithmetic.h"
#include "CATErrorDef.h"  // For the definition of HRESULT.

class CATMathPoint2D;
class CATMathPoint;
class CATMathVector;
class CATMathPlane;
class CATMathBox;

class CATPolyExactArithmetic;

class ExportedByPolyMathArithmetic CATPolyConstruction
{

public :

  /**
  * Constructs the intersection between two line segments each defined by two points.
  * This method assumes that the intersection between the two segments exists and that
  * the intersection is a point.  The result is guaranteed to be on the segments
  * (within a small tolerance) and within their bounding boxes when successfully constructed.
  * Be aware the method is not symetrical.
  * @param iSeg0Point0
  *   The first vertex of the first line segment.
  * @param iSeg0Point1
  *   The second vertex of the first line segment.
  * @param iSeg1Point0
  *   The first vertex of the second line segment.
  * @param iSeg1Point1
  *   The second vertex of the second line segment.
  * @param oIntersectionPoint
  *   The intersection point when the method successfully computes it.
  * @return 
  *   S_OK if the method computes the point successfully.
  *   E_FAIL otherwise.
  */
  static HRESULT ConstructIntersection (const CATMathPoint& iSeg0Point0,
                                        const CATMathPoint& iSeg0Point1,
                                        const CATMathPoint& iSeg1Point0,
                                        const CATMathPoint& iSeg1Point1,
                                        CATMathPoint& oIntersectionPoint);

  /**
  * Constructs the intersection between two 2D line segments each defined by two points.
  * This method assumes that the intersection between the two segments exists and that
  * the intersection is a point.  The result is guaranteed to be the best double
  * approximation of exact intersection.
  * @param iSeg0Point0
  *   The first vertex of the first line segment.
  * @param iSeg0Point1
  *   The second vertex of the first line segment.
  * @param iSeg1Point0
  *   The first vertex of the second line segment.
  * @param iSeg1Point1
  *   The second vertex of the second line segment.
  * @param oIntersectionPoint
  *   The intersection point when the method successfully computes it.
  * @return 
  *   S_OK if the method computes the point successfully.
  *   E_FAIL otherwise.
  */
  static HRESULT ConstructExactIntersection2D (const CATMathPoint2D& iSeg0Point0,
                                               const CATMathPoint2D& iSeg0Point1,
                                               const CATMathPoint2D& iSeg1Point0,
                                               const CATMathPoint2D& iSeg1Point1,
                                               CATMathPoint2D& oIntersectionPoint);

  /**
  * Constructs the intersection between a line segment defined by two points and a triangle defined by three 
  * points.  This method assumes that the intersection between the segment and the triangle exists and that
  * the intersection is a point.  The result is guaranteed to be on the triangle and on the line segment
  * (within a small tolerance) and within their bounding boxes when successfully constructed.
  * @param iSegPoint0
  *   The first vertex of the line segment.
  * @param iSegPoint1
  *   The second vertex of the line segment.
  * @param iTriPoint0
  *   The first vertex of the triangle.
  * @param iTriPoint1
  *   The second vertex of the triangle.
  * @param iTriPoint2
  *   The third vertex of the triangle.
  * @param oIntersectionPoint
  *   The intersection point when the method successfully computes it.
  * @return 
  *   S_OK if the method computes the point successfully.
  *   E_FAIL otherwise.
  */
  static HRESULT ConstructIntersection (const CATMathPoint& iSegPoint0,
                                        const CATMathPoint& iSegPoint1,
                                        const CATMathPoint& iTriPoint0,
                                        const CATMathPoint& iTriPoint1,
                                        const CATMathPoint& iTriPoint2,
                                        CATMathPoint& oIntersectionPoint);

  /**
  * Constructs the intersection between a line segment defined by two points and a plane.
  * This method assumes that the intersection is a point.  The result is guaranteed to be 
  * on the line segment and the plane (within a small tolerance) and with the bounding box
  * of the line segment.
  */
  static HRESULT ConstructIntersection (const CATMathPoint& iSegPoint0,  // A
                                        const CATMathPoint& iSegPoint1,  // B
                                        const CATMathPlane& iPlane,
                                        CATMathPoint& oIntersectionPoint);

  /**
  * Projects a (constructed) point onto the bounding box when the point is outside the bounding box.
  */
  static void ProjectToBoundingBox (const CATMathBox& iBox, CATMathPoint& ioPoint);

  /**
   * Computes the squared distance and projection of a point on a line segment
   *   @param A
   *     The first point of the line segment.
   *   @param B
   *     The second point of the line segment.
   *   @param C
   *     The point to project on the line segment.
   *   @param P
   *     The projection of C on the line segment.
   *   @return
   *     The squared distance from P to C.
   */
  static double ProjectOnSegment (const double A[2], 
                                  const double B[2], 
                                  const double C[2], 
                                  double P[2]);

  static double ProjectOnSegment (const CATMathPoint2D& A, 
                                  const CATMathPoint2D& B, 
                                  const CATMathPoint2D& C, 
                                  CATMathPoint2D& P);

  /**
   * Computes the squared distance between A and B.
   */
  static double SquaredNorm (const double A[2], const double B[2]);

  static double SquaredNorm (const CATMathPoint2D& A, const CATMathPoint2D& B);

  /**
  * Computes the signed area of the 2D triangle ABC.
  * The returned area is null if and only if the triangle is degenerate.
  * It is positive if A, B, C appear in counterclockwise order and negative otherwise.
  */
  static double ComputeArea(const CATPolyExactArithmetic& iArithmetic, const CATMathPoint2D& A, const CATMathPoint2D& B, const CATMathPoint2D& C);

  /**
  * Computes the normal of the triangle ABC. This is more accurate, but more expensive, than a simple cross product.
  * Specifically, the sign (+, - or 0) of each coordinate of the normal is guaranteed to be accurate.
  * The normal is not normalized, its norm is equal to the AREA of the triangle ABC.
  * As a consequence, bar underflow, the computed area will not be null unless the triangle is degenerate.
  */
  static CATMathVector ComputeNormal(const CATPolyExactArithmetic& iArithmetic, const CATMathPoint& A, const CATMathPoint& B, const CATMathPoint& C);

  /**
  * Computes the signed volume of the tetrahedron ABCD.
  * The volume will be zero if and only if the tetrahedron is degenerate.
  * It is otherwise positive if D is on the positive side of the triangle ABC (considering right-handed orientation).
  * It is negative if D is on the negative side of ABC.
  */
  static double ComputeVolume(const CATPolyExactArithmetic& iArithmetic, const CATMathPoint& A, const CATMathPoint& B, const CATMathPoint& C, const CATMathPoint& D);
};

#endif
