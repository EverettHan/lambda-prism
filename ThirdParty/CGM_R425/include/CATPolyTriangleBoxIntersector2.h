// COPYRIGHT DASSAULT SYSTEMES 2006, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyTriangleBoxIntersector2.h
// Header definition of CATPolyTriangleBoxIntersector2
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// January 2006  Creation: ndo
//===================================================================
#ifndef CATPolyTriangleBoxIntersector2_H
#define CATPolyTriangleBoxIntersector2_H

#include "PolyMathIntersectors.h"
#include "CATMathPoint.h"

class CATMathBox;
class CATPolyExactArithmetic;


/**
 * This class tests whether a triangle intersects a box. 
 * It uses exact predicates and returns an integer describing the type of the intersection.
 * This implementation does not calculate a symbolic description of the intersections.
 * The triangle and box are assumed to be non-degenerate.
 */
class ExportedByPolyMathIntersectors CATPolyTriangleBoxIntersector2
{

public:

  /**
   * Standard constructors and destructors.
   */
  CATPolyTriangleBoxIntersector2 (CATPolyExactArithmetic* iExactArithmetic);
  ~CATPolyTriangleBoxIntersector2 ();

  /**
  * Test whether a triangle intersects a box.  The method returns an enum
  * that describes the type of the intersection (see CATPolyIntersection::IntersectionType.)
  * The positions of the eight points defining the box
  * with respect to the triangle are optional arguments.
  * @param iTriangle
  *    An array of three vertices defining the triangle.
  * @param iBox
  *    The box.
  * @return
  *    An integer describing the type of the intersection between the triangle and the box.
  *    See CATPolyIntersection::IntersectionType.
  */

  int Intersect (const CATMathPoint* iTriangle, const CATMathBox& iBox);

private:

  void GetCornerPoint (const int iCorner, CATMathPoint& oPoint) const;

  int GetVertexPosition (const int iFace, const CATMathPoint& iPoint) const;
  unsigned int GetPlanePositions (const CATMathPoint& iPoint) const;

  void GetFaceCorners (const int iFace, CATMathPoint R[4]) const;
  void GetFaceCornerPositions (const int iFace, int oPos[4]) const;
  void SetFaceCornerPositions (const int iFace, const int iPos[4]);
  void GetTriangleVertexPositions (const int iFace, const CATMathPoint* T, int oPos[3]) const;

  int IntersectFaceTriangle (const int iFace, const CATMathPoint* T);

  CATPolyExactArithmetic* _ExactArithmetic;

  double _XMin;
  double _XMax;
  double _YMin;
  double _YMax;
  double _ZMin;
  double _ZMax;

  // Positions of the eight corners of the box w.r.t the plane of the triangle.
  //   -1: Below the plane of the triangle.
  //    0: On the plane of the triangle.
  //   +1: Above the plane of the triangle.
  //   +2: Not calculated.
  int _CornerPositions[8];

  CATMathPoint _R[4];
};

#endif
