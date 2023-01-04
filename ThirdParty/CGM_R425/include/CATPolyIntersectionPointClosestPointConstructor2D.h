// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyIntersectionPointClosestPointConstructor2D.h
//
//===================================================================
// June 2008  Creation: ndo
//===================================================================
#ifndef CATPolyIntersectionPointClosestPointConstructor2D_H
#define CATPolyIntersectionPointClosestPointConstructor2D_H

#include "PolyMathIntersectors.h"
#include "CATPolyIntersectionPointConstructor2D.h"
#include "CATErrorDef.h"

class CATMathPoint2D;


/**
 * Implements a constructor of an intersection point between two intersecting segments.
 * 
 * This constructor chooses the extremity of the segment which is the closest to the
 * other segment.  If the distance of this extremity to the segment is greater than the
 * tolerance then the method fails. 
 * 
 * The returned intersection point is one of the four input points.
 */
class ExportedByPolyMathIntersectors CATPolyIntersectionPointClosestPointConstructor2D : public CATPolyIntersectionPointConstructor2D
{

public:

  /**
   * 
   */
  inline CATPolyIntersectionPointClosestPointConstructor2D (const double iTolerance);

  virtual ~CATPolyIntersectionPointClosestPointConstructor2D () {}

  /**
   * Implements CATPolyIntersectionPointConstructor2D::Compute.
   */
  HRESULT Compute (const CATMathPoint2D& A, const CATMathPoint2D& B,   // Define Segment AB.
                   const CATMathPoint2D& C, const CATMathPoint2D& D,   // Define Segment CD.
                   CATMathPoint2D& oIntersectionPoint) const;

public:

  /**
   * Returns the index and the square of the distance of the closest extremity to the other segment.
   * @param oDistance2
   *   The square of the distance of the extremity to the segment.
   * <ul>
   *   <li> 1: The start point of Segment 0: A.
   *   <li> 2: The end point of Segment 0: B.
   *   <li> 3: The start point of Segment 1: C.
   *   <li> 4: The end point of Segment 1: D.
   * </ul>
   */
  static int FindClosestExtremity (const CATMathPoint2D& A, const CATMathPoint2D& B, 
                                   const CATMathPoint2D& C, const CATMathPoint2D& D,
                                   double& oDistance2);

private:

  const double _Tolerance;

};

inline CATPolyIntersectionPointClosestPointConstructor2D::CATPolyIntersectionPointClosestPointConstructor2D (const double iTolerance) :
  _Tolerance (iTolerance)
{
}


#endif
