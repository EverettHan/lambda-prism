// COPYRIGHT DASSAULT SYSTEMES 2005, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyTriangleRectangleIntersector.h
// Header definition of CATPolyTriangleRectangleIntersector
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// December 2005  Creation: ndo
//===================================================================
#ifndef CATPolyTriangleRectangleIntersector_H
#define CATPolyTriangleRectangleIntersector_H

#include "PolyMathIntersectors.h"

class CATMathPoint;
class CATPolyExactArithmetic;


/**
 * This class tests whether a triangle intersects a rectangle. 
 * It uses exact predicates and returns an integer describing the type of the intersection.
 * This implementation does not calculate a symbolic description of the intersections.
 * The triangle and rectangle are assumed to be non-degenerate.
 */
class ExportedByPolyMathIntersectors CATPolyTriangleRectangleIntersector
{

public:

  /**
   * Standard constructors and destructors.
   */
  CATPolyTriangleRectangleIntersector (CATPolyExactArithmetic* iExactArithmetic);
  ~CATPolyTriangleRectangleIntersector ();

  /**
  * Test whether a triangle intersects a rectangle.  The method returns an enum
  * that describes the type of the intersection (see CATPolyIntersection::IntersectionType.)
  * The positions of the three (respectively, four) points defining the triangle (rectangle)
  * with respect to the rectangle (triangle) are optional arguments.
  * @param iTriangle
  *    The three vertices defining the triangle.
  * @param iRectangle
  *    The four vertices defining the rectangle.  The four vertices must be coplanar.
  *    They must define a valid rectangle.
  * @param ioTrianglePositions
  *    The positions of the three points from the triangle w.r.t. the rectangle (optional):
  *      -1: below the rectangle.
  *       0: on the rectangle.
  *      +1: above the rectangle.
  *      +2: not calculated; to be calculated by the method if needed.
  * @param ioRectanglePositions
  *    The positions of the four points from the rectangle w.r.t. the triangle (optional):
  *      -1: below the triangle.
  *       0: on the triangle.
  *      +1: above the triangle.
  *      +2: not calculated; to be calculated by the method if needed.
  * @return
  *    An integer describing the type of the intersection between the triangle and the rectangle.
  *    See CATPolyIntersection::IntersectionType.
  */
  int Intersect (const CATMathPoint* iTriangle, const CATMathPoint* iRectangle,
                 int* ioTrianglePositions = 0, int* ioRectanglePositions = 0);

private:

  void InitTPositions (const CATMathPoint* T, const CATMathPoint* R, int* oPosTR); 
  void InitRPositions (const CATMathPoint* T, const CATMathPoint* R, int* oPosRT);

  int IntersectionTest (const CATMathPoint* T, const CATMathPoint* R, const int* iPosTR, const int* iPosRT);

  CATPolyExactArithmetic* _ExactArithmetic;

};

#endif
