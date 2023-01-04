// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CreateConfusionPtOnPCrvPtOnPCrv :
// 2d confusion of two points on the same pcurve
//
//=============================================================================
//
// Usage Notes:
//
//=============================================================================
// Aug. 97    Creation                         X. Gourdon
// Dec. 97    Documentation                    C. Keribin
//=============================================================================

#ifndef CreateConfusionPtOnPCrvPtOnPCrv_H
#define CreateConfusionPtOnPCrvPtOnPCrv_H

#include "Y300IINT.h"

#include "CATSkillValue.h"

class CATConfusionPtOnPCrvPtOnPCrv;
class CATGeoFactory;
class CATPointOnCurve;
class CATPointOnEdgeCurve;
class CATPCurve;

/**
* @deprecated V5R13 CATCreateConfusionOnSurface
*/
ExportedByY300IINT CATConfusionPtOnPCrvPtOnPCrv* 
CreateConfusionOnSurface(CATGeoFactory * iWhere,
             const CATPointOnCurve *iPoint1,
			 const CATPointOnCurve *iPoint2,
			 double iTol,
			 CATSkillValue iMode=BASIC );

/**
* @deprecated V5R13 CATCreateConfusionOnSurface
*/
ExportedByY300IINT CATConfusionPtOnPCrvPtOnPCrv* 
CreateConfusionOnSurface(CATGeoFactory * iWhere,
             const CATPointOnEdgeCurve *iPoint1,
			 const CATPointOnEdgeCurve *iPoint2,
             const CATPCurve * iPCrv,
			 double iTol,
			 CATSkillValue iMode=BASIC );

/**
 * Removes a CATConfusionPtOnPCrvPtOnPCrv operator from memory.
 */  
ExportedByY300IINT void Remove(CATConfusionPtOnPCrvPtOnPCrv * iConfusionOperator);

#endif



