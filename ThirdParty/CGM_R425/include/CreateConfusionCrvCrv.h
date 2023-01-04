#ifndef CreateConfusionCrvCrv_H
#define CreateConfusionCrvCrv_H

// COPYRIGHT DASSAULT SYSTEMES  1999

#include "Y300IINT.h"
#include "CATSkillValue.h"
class CATConfusionCrvCrv;
class CATGeoFactory;
class CATPointOnCurve;
class CATPointOnEdgeCurve;
class CATCurve;
/**
* @deprecated V5R13 CATCreateConfusion
*/
ExportedByY300IINT CATConfusionCrvCrv * 
CreateConfusion(CATGeoFactory * iWhere,
        const CATPointOnCurve *iStartPtOnCrv1, 
		const CATPointOnCurve *iEndPtOnCrv1,
		const CATPointOnCurve *iStartPtOnCrv2,
		const CATPointOnCurve *iEndPtOnCrv2,
		const double & iTol,
		CATSkillValue iMode=BASIC);

/**
* @deprecated V5R13 CATCreateConfusion
*/
ExportedByY300IINT CATConfusionCrvCrv * 
CreateConfusion(CATGeoFactory * iWhere,
        const CATPointOnEdgeCurve *iStartPtOnECrv1, 
		const CATPointOnEdgeCurve *iEndPtOnECrv1,
        const CATCurve * iCrv1,
		const CATPointOnEdgeCurve *iStartPtOnECrv2,
		const CATPointOnEdgeCurve *iEndPtOnECrv2,
        const CATCurve * iCrv2,
		const double & iTol,
		CATSkillValue iMode=BASIC);


/**
 * @nodoc
 * Removes a CATConfusionCrvCrv operator from memory.
 */
ExportedByY300IINT void Remove(CATConfusionCrvCrv * iConfusionOperator);


#endif

