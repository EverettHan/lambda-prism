#ifndef CreateDistanceMinPtCrv_H
#define CreateDistanceMinPtCrv_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @level Protected
 * @usage U1
 */ 

#include "Y300IINT.h"
#include "CATSkillValue.h"

class CATGeoFactory;
class CATCurve;
class CATDistanceMinPtCrv;
class CATPoint;
class CATMathPoint;
class CATMathNurbsMultiForm;
/**
* @deprecated V5R13 CATCreateDistanceMin
*/
ExportedByY300IINT CATDistanceMinPtCrv * CreateDistanceMin(CATGeoFactory * iWhere,
							   CATPoint * iPt,
							   CATCurve * iCrv,
							   CATSkillValue iMode=BASIC);

/**
* @deprecated V5R13 CATCreateDistanceMin
*/
ExportedByY300IINT CATDistanceMinPtCrv * CreateDistanceMin(CATGeoFactory * iWhere,
							   const CATMathPoint & iPt,
							   CATCurve * iCrv,
							   CATSkillValue iMode=BASIC);

/**
* @nodoc
*/
ExportedByY300IINT CATDistanceMinPtCrv * CreateDistanceMin(CATGeoFactory * iWhere,
							   const CATMathPoint & iPt,
							   CATMathNurbsMultiForm * iCrv,
							   CATSkillValue iMode=BASIC);

/**
 * @nodoc
 */
ExportedByY300IINT void Remove(CATDistanceMinPtCrv * iOperatorToRemove);


#endif
