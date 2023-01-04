// COPYRIGHT DASSAULT SYSTEMES 2004, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyTriangleIntersector2D.h
//
//===================================================================
// Apr 2004 Creation: rxu/ndo
//===================================================================
#ifndef CATPolyTriangleIntersector2D_H
#define CATPolyTriangleIntersector2D_H

#include "PolyMathIntersectors.h"
#include "CATPolyIntersectionPoint.h"
#include "CATBoolean.h"

class CATMathPoint2D;
class CATPolyExactArithmetic;


enum PositionOnEdge {
  START,
  INTERIOR,
  END,
  EXTERIOR,
  COLINEAR
};


struct Local2DIntersectionPoint
{
  int _EdgeOfTriangle[2];
  PositionOnEdge _PositionOnEdgeOfTriangle[2];
  int _TriangleOfEnteringEdge;  // 0 if 0 entering 1, 1 if 1 is entering 0
  int _NextTriangle;
  int _NextEdge;
};


/**
* Operator that finds out if two coplanar triangles intersect.
* If the triangles intersect, it computes a symbolic description of the intersection
* (point, segment or polygon.)
*/
class ExportedByPolyMathIntersectors CATPolyTriangleIntersector2D
{

public:

  CATPolyTriangleIntersector2D(const CATPolyExactArithmetic& iExactArithmetic);
  ~CATPolyTriangleIntersector2D();

public:

  /** @name Options
  @{ */

  /**
  * Sets an option to compute an estimation of the barycentric coordinates of intersection points;
  */
  void ComputeBarycentricCoordinates() { _ComputeBarycentricCoordinates = true; }

  /**
  * Check if barycentric coordinates are estimated or not.
  */
  bool DoesComputeBarycentricCoordinates() { return _ComputeBarycentricCoordinates; }

  /** @} */

public:

  /** @name Intersect Methods
  @{ */

  /**
  * Tests whether two coplanar triangles intersect or not.
  * The method returns an enum that describes the type of the intersection.
  * (see CATPolyIntersection.)
  * If there is an intersection between the two triangles, a symbolic description of the intersection
  * can be obtained with the GetIntersectionPoint () method.
  *   @param iTriangle1
  *      A pointer to an array of three points defining Triangle 1.
  *   @param iTriangle2
  *      A pointer to an array of three points defining Triangle 2.
  *   @return
  *      An integer describing the type of the intersection between the triangles.
  *      See CATPolyTriangleIntersector::IntersectionType.
  */
  int Intersect(const CATMathPoint2D P[3], const CATMathPoint2D Q[3]);

  /**
  * Test whether two triangles defined by three coplanar points intersect or not.  The method returns an enum
  * that describes the type of the intersection (see CATPolyTriangleIntersector::IntersectionType.)
  * If there is an intersection between the two triangles, a symbolic description of the intersection
  * can be obtained with the GetIntersectionPoint () method.
  *   @param A
  *      The first point of Triangle 1.
  *   @param B
  *      The second point of Triangle 1.
  *   @param C
  *      The third point of Triangle 1.
  *   @param D
  *      The first point of Triangle 2.
  *   @param E
  *      The second point of Triangle 2.
  *   @param F
  *      The third point of Triangle 2.
  *   @return
  *      An integer describing the type of the intersection between the triangles.
  *      See CATPolyTriangleIntersector::IntersectionType.
  */
  int Intersect(const CATMathPoint2D& A, const CATMathPoint2D& B, const CATMathPoint2D& C, const CATMathPoint2D& D, const CATMathPoint2D& E, const CATMathPoint2D& F);

  // More efficient (and correct) method in convergence.
  // Do not use.
  int IntersectInConvergence(const CATMathPoint2D P[3], const CATMathPoint2D Q[3]);

  /** @} */

public:

  /** @name Results
  @{ */

  /**
  * Returns a description of the intersection between the two triangles after a call to the Intersect ()
  * method. The intersection is either a point, a line segment or a polygon which are defined respectively
  * by one, two or more intersection points.  When the intersection is a polygon, it has the same orientation
  * as the first triangle (CCW?).  Another call to Intersect () invalidates the result of the previous call.
  *   @param oNbPoints
  *      An output integer giving the number of points defining the intersection.
  *   @return
  *      A pointer to the intersection points defining the intersection.
  */
  inline const CATPolyIntersectionPoint* GetIntersectionPoints(int& oNbPoints) const;

  /**
  * Returns <tt>TRUE</tt> if the orientation of the two triangles are the same.
  */
  inline CATBoolean HaveSameOrientation() const;

  /**
  * @see HaveSameOrientation
  */
  inline CATBoolean IsOrientationOfTrianglesTheSame() const;

  /** @} */

private:

  const CATPolyExactArithmetic& _ExactArithmetic;
  bool _ComputeBarycentricCoordinates;

  // Symbolic description of the intersection points.
  // An intersection point is defined symbolically by the intersection of two triangle entities
  // (a vertex, a bar or a triangle) from Triangle 1 and Triangle 2.
  // For instance, a vertex from Triangle 1 on a bar from Triangle 2; or an intersection point 
  // could be defined as the intersection between Triangle 1 and a bar of Triangle 2.  
  // When the intersection is on a bar, it excludes the vertices from this bar; otherwise, it would
  // When the intersection is on a bar, it excludes the vertices from this bar; otherwise, it would
  // be on a vertex.  When the intersection is on a triangle, it excludes the bars and vertices from
  // this triangle; otherwise, it would be on a bar or a vertex.
  // An index identifies the vertex or the bar of the triangle.
  // Given a triangle (A, B, C), the indices of the vertices A, B, C are 0, 1 and 2 respectively and
  // the indices of the bars AB, BC, CA are 0, 1 and 2 respectively.

  int _NbPoints;
  CATPolyIntersectionPoint _Point[6];
  int _OrientTriangle[2];  // The orientations of Triangle 0 and 1.

private:

  CATBoolean IsSamePoint(CATPolyIntersectionPoint &P1, CATPolyIntersectionPoint &P2);

  int IntersectDefault(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[2][3][3]);

private:

  /**
  * Reverse permutation of the intersection points of index greater of equal to s
  * for Triangle t by an index of p.
  */
  void ReversePermuteOfPoints(unsigned int t, unsigned int s, unsigned int p);

  void ReverseNoncyclicPermuteOfPoints(unsigned int t);

private:

  /** @name Methods adding intersection points.
  @{ */

  void AddVertexVertex(unsigned int vi, unsigned int vj);
  void AddVertexBar(unsigned int v, unsigned int b);
  void AddVertexTriangle(unsigned int v);
  void AddBarVertex(unsigned int b, unsigned int v);
  void AddBarBar(unsigned int bi, unsigned int bj);
  void AddTriangleVertex(unsigned int v);

  /** @} */

private:

  /** @name Methods finding out if the two triangles are intersecting.
  @{ */

  int IntersectCCW(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int IntersectR1(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int IntersectR2(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  void ComputeBarycentricCoordinates(const CATMathPoint2D* pts[2], unsigned int idx[][3]);

  /** @} */

private:

  int FindNext(int idx, int det[2][3][3]);
  void ReverseIntersectionOrder();

  /** @name Methods computing the symbolic description of the intersection between the two triangles.
  @{ */

  int ComputeR0(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeR0Q2(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeR0B2(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeR0R0(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeR0R1(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeR0R1R2(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeR0R2R3(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  //

  int ComputeQ2(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeQ2Q0(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeQ2Q1(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeQ2B0(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeQ2B1(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeQ2B2(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeQ2R0(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeQ2R1(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeQ2R2(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeQ2R3(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeQ2R4(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeQ2R5(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeQ2R6(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeR2_Case4(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  // Common part between Q2B2 and Q2R0
  int CommonQ2B2andQ2R0(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeB2(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeB2Q0(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeB2Q1(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeB2Q2(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeB2B0(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeB2B1(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeB2B2(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeB2R0(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeB2R1(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeB2R2(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeB2R3(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeB2R4(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeB2R5(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeB2R1R2(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeB2R2R3(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeB2R5R6(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeB2R1R4(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);

  int ComputeB2R4R5(const CATMathPoint2D P[3], const CATMathPoint2D Q[3], unsigned int idx[][3], int det[][3][3]);
  /** @} */

};

inline const CATPolyIntersectionPoint* CATPolyTriangleIntersector2D::GetIntersectionPoints(int& oNbPoints) const
{
  oNbPoints = _NbPoints;
  return _NbPoints ? _Point : 0;
}

inline CATBoolean CATPolyTriangleIntersector2D::HaveSameOrientation() const
{
  return _OrientTriangle[0] * _OrientTriangle[1] > 0;
}

inline CATBoolean CATPolyTriangleIntersector2D::IsOrientationOfTrianglesTheSame() const
{
  return HaveSameOrientation();
}

#endif
