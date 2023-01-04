// COPYRIGHT DASSAULT SYSTEMES 2006, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyTriangleSegmentIntersector2D.h
//
//===================================================================
// November 2006 Creation: ndo
//===================================================================
#ifndef CATPolyTriangleSegmentIntersector2D_H
#define CATPolyTriangleSegmentIntersector2D_H

#include "PolyMathIntersectors.h"
#include "CATPolyIntersection.h"
#include "CATPolyIntersectionPoint.h"

class CATMathPoint2D;
class CATPolyExactArithmetic;


/**
 * This class tests whether a triangle and a segment intersect.
 * If they intersect, it computes a symbolic description of their intersections.
 * This intersector computes the intersections between a triangle and a segment in the plane.
 * The intersection could be a point or a segment.
 */
class ExportedByPolyMathIntersectors CATPolyTriangleSegmentIntersector2D
{

public:

  CATPolyTriangleSegmentIntersector2D (const CATPolyExactArithmetic& iExactArithmetic);

  ~CATPolyTriangleSegmentIntersector2D ();

public:

  /**
  * Test whether a triangle and a segment intersect or not.  The method returns an enum
  * that describes the type of the intersection (see CATPolyIntersection::IntersectionType.)
  * If there is an intersection, a symbolic description of the intersection
  * can be obtained with the GetIntersectionPoint () method.
  *   @param A
  *      The first point of the triangle.
  *   @param B
  *      The second point of the triangle.
  *   @param C
  *      The third point of the triangle.
  *   @param iSegPoint0
  *      The first extremity of the segment.
  *   @param iSegPoint1
  *      The second extremity of the segment.
  *   @return
  *      An integer describing the type of the intersection between the segment and the triangle.
  *      See CATPolyIntersection::IntersectionType.
  */
  int Intersect (const CATMathPoint2D& A, const CATMathPoint2D& B, const CATMathPoint2D& C,
                 const CATMathPoint2D& iSegPoint0, const CATMathPoint2D& iSegPoint1);

  /**
  * Returns a description of the intersection between the two triangles after a call to the Intersect ()
  * method. The intersection is either a point or a line segment which are defined respectively 
  * by one or two intersection points. If another call to Intersect () is made after calling this method,
  * the data become invalid.
  *   @param oNbPoints
  *      An output integer giving the number of points defining the intersection.
  *   @return
  *      A pointer to the intersection points defining the intersection.
  */
  const CATPolyIntersectionPoint* GetIntersectionPoints (int& oNbPoints) const;

private:

  const CATPolyExactArithmetic& _ExactArithmetic;

  // Symbolic description of the intersection points.
  // An intersection point is defined symbolically by the intersection of two entities
  // (a vertex, a bar or a triangle) from the triangle and the segment.
  // When the intersection is on a bar, it excludes the vertices from this bar; otherwise, it would
  // be on a vertex.  When the intersection is on a triangle, it excludes the bars and vertices from
  // this triangle; otherwise, it would be on a bar or a vertex.
  // An index identifies the vertex or the bar of the triangle.
  // Given a triangle (A, B, C), the indices of the vertices A, B, C are 0, 1 and 2 respectively and
  // the indices of the bars AB, BC, CA are 0, 1 and 2 respectively.

  int _NbPoints;
  int _Orientation;  // Orientation of the triangle.
  CATPolyIntersectionPoint _Point[2];

  void UpdateTrianglePoints (const int det[3], unsigned int idx[3]);
  void UpdatePointDefinitionP (unsigned int idx[3]);
  void UpdatePointDefinitionTP (unsigned int idx[3]);

};

#endif
