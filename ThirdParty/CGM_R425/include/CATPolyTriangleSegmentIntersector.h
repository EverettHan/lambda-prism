// COPYRIGHT DASSAULT SYSTEMES 2006, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyTriangleSegmentIntersector.h
// Header definition of CATPolyTriangleSegmentIntersector
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// November 2006  Creation: ndo
//===================================================================
#ifndef CATPolyTriangleSegmentIntersector_H
#define CATPolyTriangleSegmentIntersector_H

#include "PolyMathIntersectors.h"
#include "CATPolyIntersectionPoint.h"
#include "CATPolyIntersection.h"
#include "CATBoolean.h"

class CATMathPoint;
class CATPolyExactArithmetic;
class CATPolyTriangleSegmentIntersector2D;


/**
 * Describe your class here.
 * <p> This class tests whether a segment and a triangle intersect. </br>
 *     If they intersect, it computes a symbolic description of the intersection. </br>
 */
class ExportedByPolyMathIntersectors CATPolyTriangleSegmentIntersector
{

public:

  // Standard constructors and destructors
  // -------------------------------------
  CATPolyTriangleSegmentIntersector (const CATPolyExactArithmetic& iExactArithmetic);
  ~CATPolyTriangleSegmentIntersector ();

  /** 
  * Set an option to ignore triangle and segment that are coplanar.  
  * If this option is turned on, then the Intersect () method will return an error when
  * the operands are coplanar instead of finding their intersections.  
  */
  void IgnoreCoplanarTriangleAndSegment ();

  /**
  * Test whether a segment and a triangle intersect or not.  The method returns an enum
  * that describes the type of the intersection (see CATPolyIntersection::IntersectionType.)
  * If there is an intersection between the entities, a symbolic description of the intersection
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
  *      An integer describing the type of the intersection between the segment and triangle.
  *      See CATPolyIntersection::IntersectionType.
  */
  int Intersect (const CATMathPoint& A, const CATMathPoint& B, const CATMathPoint& C,
                 const CATMathPoint& iSegPoint0, const CATMathPoint& iSegPoint1);

  /**
  * Returns a description of the intersection between the segment and the triangle after a call to the 
  * Intersect () method. The intersection is either a point or a line segment which are defined respectively 
  * by one or two intersection points. If another call to Intersect () is made after calling this method,
  * the data become invalid.
  *  *
  *   @param oNbPoints
  *      An output integer giving the number of points defining the intersection.
  *   @return
  *      A pointer to the intersection points defining the intersection.
  */
  const CATPolyIntersectionPoint* GetIntersectionPoints (int& oNbPoints) const;

  /**
  * Returns TRUE if the segment and the triangle are coplanar and FALSE otherwise.
  *   @return
  *     TRUE if the segment and the triangle are coplanar and FALSE otherwise.
  */
  CATBoolean AreTriangleAndSegmentCoplanar () const;

private:

  void ComputeTriangleType (const int side0, const int side1, const int side2);
  void ComputeSegmentType (const int pos0, const int pos1);

  int IntersectCoplanarTriangleAndSegment (const CATMathPoint& A, const CATMathPoint& B, const CATMathPoint& C,
                                           const CATMathPoint& iSegPoint0, const CATMathPoint& iSegPoint1) ;

  const CATPolyExactArithmetic& _ExactArithmetic;
  CATPolyTriangleSegmentIntersector2D* _PlanarIntersector;

  // Symbolic description of the intersection points.
  // An intersection point is defined symbolically by the intersection of the segment with a triangle
  // entity: (a vertex, a bar or a triangle). When the intersection is on a bar, it excludes the vertices 
  // from this bar; otherwise, it would be on a vertex.  When the intersection is on a triangle, it excludes 
  // the bars and vertices from this triangle; otherwise, it would be on a bar or a vertex.
  // An index identifies the vertex or the bar of the triangle.
  // Given a triangle (A, B, C), the indices of the vertices A, B, C are 0, 1 and 2 respectively and
  // the indices of the bars AB, BC, CA are 0, 1 and 2 respectively.
  // 
  // An intersection points refer to two entities, in this instance: a triangle and a segment.
  // The information for the triangle is associated to the index 0.
  // The information for the segment is associated to the index 1.

  int _NbPoints;
  CATPolyIntersectionPoint _Point;

};

#endif
