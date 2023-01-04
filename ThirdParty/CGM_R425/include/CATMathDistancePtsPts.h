//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  1999
// CATMathDistancePtsPts
//=============================================================================
#ifndef CATMathDistancePtsPts_H
#define CATMathDistancePtsPts_H

#include "CATMathematics.h"
class CATMathPoint;

/**
 * Returns the distance between two arrays of CATMathPoint.
 * @param iPoint1[]
 *   The first array of CATMathPoint to which the distance is computed.
 * @param iNbPt1
 *   The number of points of the first array.
 * @param iPoint2[]
 *   The second array of CATMathPoint to which the distance is computed.
 * @param iNbPt2
 *   The number of points of the second array.
 * @param oIndex1
 *   The index of the closest point in the <tt>iPoint1[]</tt> array.
 * @param oIndex2
 *   The index of the closest point in the <tt>iPoint2[]</tt> array.
 */

 double    ExportedByCATMathematics CATMathDistancePtsPts
      (const CATMathPoint iPoint1[], const CATLONG32 iNbPt1,
       const CATMathPoint iPoint2[], const CATLONG32 iNbPt2,
       CATLONG32 & oIndex1, CATLONG32 & oIndex2);

#endif
