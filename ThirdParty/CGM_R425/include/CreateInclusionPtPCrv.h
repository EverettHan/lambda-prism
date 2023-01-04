#ifndef CreateInclusionPtPCrv_H
#define CreateInclusionPtPCrv_H

// COPYRIGHT DASSAULT SYSTEMES  1999

#include "Y300IINT.h"

#include "CATSkillValue.h"

class CATGeoFactory;
class CATSurParam;
class CATEdgeCurve;
class CATPCurve;
class CATCrvLimits;
class CATInclusionPtPCrv;

/**
* @deprecated V5R13 CATCreateInclusion
*/
ExportedByY300IINT CATInclusionPtPCrv * CreateInclusion(CATGeoFactory * iWhere,
							const CATSurParam & iPt,
							const CATEdgeCurve * iECrv,
                                                        const CATPCurve * iPCrv,
							const double iTol,
							CATSkillValue mode=BASIC);
/**
* @deprecated V5R13 CATCreateInclusion
*/
ExportedByY300IINT CATInclusionPtPCrv * CreateInclusion(CATGeoFactory * iWhere,
							const CATSurParam & iPt,
							const CATPCurve * iPCrv, 
							const double iTol,
							CATSkillValue iMode=BASIC);
/**
 * Removes a CATInclusionPtPCrv operator from memory.
 */
ExportedByY300IINT void Remove(CATInclusionPtPCrv * iOperatorToRemove);


#endif

