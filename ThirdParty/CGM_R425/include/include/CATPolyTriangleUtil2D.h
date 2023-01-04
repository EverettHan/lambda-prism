// COPYRIGHT DASSAULT SYSTEMES 2004, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyTriangleUtil2D.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// Oct 2004 Creation: NDO
//===================================================================
#ifndef CATPolyTriangleUtil2D_h
#define CATPolyTriangleUtil2D_h

#include "PolyMathUtils.h"

class CATMathPoint2D;


class ExportedByPolyMathUtils CATPolyTriangleUtil2D
{

public :

  /**
  * Computes the bar lengths and the height of the triangle represented by the points A, B and C.
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
  * @return
  *   The index of the vertex dropped to the base to calculate the height: 0, 1 or 2 for A, B or C respectively.
  */
  static int GetBarLengthsAndHeight (const CATMathPoint2D & A,
                                     const CATMathPoint2D & B,
                                     const CATMathPoint2D & C,
                                     double & oLength0,
                                     double & oLength1,
                                     double & oLength2,
                                     double & oHeight);

 /**
  * Computes the cosine of the angles at vertex A, B and C.
  * @param A
  *   The first point.
  * @param B
  *   The second point.
  * @param C
  *   The third point.
  * @param oCosA
  *   The cosine of the angle A.
  * @param  oCosB
  *   The cosine of the angle B.
  * @param oCosC
  *   The cosine of the angle C
  * Note: for degenerated triangle, at least two vertices are same, all three angles
  *       are consided have 0 degree.
  */
  static void GetTriangleAngleCosines (const CATMathPoint2D & A,
                                       const CATMathPoint2D & B,
                                       const CATMathPoint2D & C,
                                       double & oCosA,
                                       double & oCosB,
                                       double & oCosC);

};

#endif
