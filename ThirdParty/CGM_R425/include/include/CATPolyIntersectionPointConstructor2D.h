// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyIntersectionPointConstructor2D.h
//
//===================================================================
// June 2008  Creation: ndo
//===================================================================
#ifndef CATPolyIntersectionPointConstructor2D_H
#define CATPolyIntersectionPointConstructor2D_H

#include "PolyMathIntersectors.h"
#include "CATErrorDef.h"

class CATMathPoint2D;


/**
 * Interface to a constructor of an intersection point between two segments.
 * The segments are defined by pairs of CATMathPoint2D.
 * There should be a point intersection between the two segments.  
 * The segments must not be colinear.
 */
class ExportedByPolyMathIntersectors CATPolyIntersectionPointConstructor2D
{

public:

  virtual ~CATPolyIntersectionPointConstructor2D () {}

public:

  /**
   * Constructs an intersection point between two segments: AB and CD.
   * There should be a point intersection between AB and CD.
   * @param A
   *   The start point of the first segment.
   * @param B
   *   The end point of the first segment.
   * @param C
   *   The start point of the second segment.
   * @param D
   *   The end point of the second segment.
   * @param oIntersectionPoint
   *   The constructed intersection point.
   * @return
   * <ul>
   *   <li> <tt>S_OK</tt> if the computation of the intersection point succeeds; and,
   *   <li> <tt>E_FAIL</tt> if the computation of the intersection point fails and a point cannot be computed.
   * </ul>
   */   
  virtual HRESULT Compute (const CATMathPoint2D& A, const CATMathPoint2D& B,   // Define Segment AB.
                           const CATMathPoint2D& C, const CATMathPoint2D& D,   // Define Segment CD.
                           CATMathPoint2D& oIntersectionPoint) const = 0;

};

#endif
