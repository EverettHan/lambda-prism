//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 2014
//==============================================================================================================
// Usage notes:
//==============================================================================================================
// 2014-01-28 - T6L : Creation
//==============================================================================================================


#ifndef CATExpOrientationPredicates_H
#define CATExpOrientationPredicates_H

#include "CATExpEnums.h"


class CATExpPoint2D;


#if defined(__CATExpOrientationPredicates)
#define ExportedByCATExpOrientationPredicates DSYExport
#else
#define ExportedByCATExpOrientationPredicates DSYImport
#endif
#include "DSYExport.h"



/**
* @return CATExpPOSITIVE iff the angle between (center, pt1) and (center, pt2) is positive, CATExpNEGATIVE if negative,
*   and CATExpZERO if the three points are aligned.
*/
ExportedByCATExpOrientationPredicates CATExpSign_t CATExpOrientation
  (const CATExpPoint2D &center, const CATExpPoint2D &pt1, const CATExpPoint2D &pt2);


#endif 
