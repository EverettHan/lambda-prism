// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyPointSegmentIntersector2D.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
// February 2010  Creation: ndo
//===================================================================
#ifndef CATPolyPointSegmentIntersector2D_H
#define CATPolyPointSegmentIntersector2D_H

#include "PolyMathIntersectors.h"
#include "CATPolyIntersection.h"
#include "CATErrorDef.h"

class CATPolyExactArithmetic;
class CATMathPoint2D;


/**
 * This intersector tests whether a point lies on a segment or not.
 */
class ExportedByPolyMathIntersectors CATPolyPointSegmentIntersector2D
{

public:

  inline CATPolyPointSegmentIntersector2D (const CATPolyExactArithmetic& iExactArithmetic);
  inline ~CATPolyPointSegmentIntersector2D () {}

  enum IntersectionPoint
  {
    eNoPoint,
    eStartPoint,
    eSegmentPoint,
    eEndPoint
  };

  /**
  * Test whether a segment, AB and a point C intersects.
  * @param A
  *   The start point of the segment.
  * @param B
  *   The end point of the segment.
  * @param C
  *   The point to be tested against the segment.
  * @param oSegmentPoint
  *   An optional argument to recover the position of the intersection point w.r.t. the segment.
  * @return
  *   S_OK if there is an intersection.
  *   S_FALSE if there is no intersection.
  *   E_FAIL if there is an error.
  */
  HRESULT Intersect (const CATMathPoint2D& A, const CATMathPoint2D& B, 
                     const CATMathPoint2D& C,
                     CATPolyIntersection::Type& oIntersectionType, CATPolyIntersection::Error& oError,
                     int* oSegmentPoint = 0);

private:

  const CATPolyExactArithmetic& _ExactArithmetic;

};


inline CATPolyPointSegmentIntersector2D::CATPolyPointSegmentIntersector2D (const CATPolyExactArithmetic& iExactArithmetic) :
  _ExactArithmetic (iExactArithmetic)
{
}

#endif

