#ifndef CreateConfusionPtOnCrvPtOnCrv_H
#define CreateConfusionPtOnCrvPtOnCrv_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @level Protected
 * @usage U1
 */ 

#include "Y300IINT.h"
#include "CATSkillValue.h"
class CATConfusionPtOnCrvPtOnCrv;
class CATGeoFactory;
class CATPointOnCurve;
class CATPointOnEdgeCurve;
class CATCurve;
class CATCrvParam;


/**
* @deprecated V5R13 CATCreateConfusion
*/
ExportedByY300IINT CATConfusionPtOnCrvPtOnCrv * 
CreateConfusion(CATGeoFactory * iWhere,
		const CATPointOnCurve * iPoint1,
		const CATPointOnCurve * iPoint2, 
		const double & iTol,
		CATSkillValue iMode=BASIC);
                                
/**
* @deprecated V5R13 CATCreateConfusion
*/
ExportedByY300IINT CATConfusionPtOnCrvPtOnCrv* 
CreateConfusion(CATGeoFactory * iFactory,
		const CATPointOnEdgeCurve * iPECrv1,
		const CATPointOnEdgeCurve * iPECrv2,
		const CATCurve * iCrv,
		double iTol,
		CATSkillValue iMode=BASIC);

/**
* @deprecated V5R13 CATCreateConfusion
*/
ExportedByY300IINT CATConfusionPtOnCrvPtOnCrv * 
CreateConfusion(CATGeoFactory * iFactory,
		const CATCrvParam & iParam1,
		const CATCrvParam & iParam2,
		const CATCurve * iCrv,		
		const double & tol,
		CATSkillValue iMode=BASIC);

/**
 * @nodoc
 * Removes a CATConfusionPtOnCrvPtOnCrv operator from memory.
 */   
ExportedByY300IINT void Remove(CATConfusionPtOnCrvPtOnCrv * iConfusionOperator);


#endif

