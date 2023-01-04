#ifndef CreateInclusionPtCrv_H
#define CreateInclusionPtCrv_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @level Protected
 * @usage U1
 */ 

#include "Y300IINT.h"

#include "CATSkillValue.h"

class CATGeoFactory;
class CATPoint;
class CATMathPoint;
class CATEdgeCurve;
class CATCurve;
class CATCrvLimits;
class CATInclusionPtCrv;

/**
 * @deprecated V5R13 CATCreateInclusion
 */
ExportedByY300IINT CATInclusionPtCrv * CreateInclusion(CATGeoFactory * iWhere,
                                                       const CATPoint * iPoint,
                                                       const CATCurve * iCrv, 
                                                       const double iTol,
                                                       CATSkillValue iMode=BASIC);

/**
 * @deprecated V5R13 CATCreateinclusion
 */
ExportedByY300IINT CATInclusionPtCrv * CreateInclusion(CATGeoFactory * iWhere,
                                                       const CATMathPoint & iPoint,
                                                       const CATEdgeCurve * iECrv,
                                                       const CATCurve * iCrv, 
                                                       const double iTol,
                                                       CATSkillValue iMode=BASIC);

/**
 * @nodoc
 * Removes a CATInclusionPtCrv operator from memory.
 */
ExportedByY300IINT void Remove(CATInclusionPtCrv * iOperatorToRemove);


#endif
