#ifndef CreateConfusionPtOnSurPtOnSur_H
#define CreateConfusionPtOnSurPtOnSur_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @level Protected
 * @usage U1
 */ 

#include "Y300IINT.h"

#include "CATSkillValue.h"

class CATConfusionPtOnSurPtOnSur;
class CATGeoFactory;
class CATPointOnSurface;
class CATSurParam;
class CATSurface;

/**
* @deprecated V5R13 CATCreateConfusion
*/
ExportedByY300IINT CATConfusionPtOnSurPtOnSur * 
CreateConfusion(CATGeoFactory * iFactory,
		const CATPointOnSurface * iPoint1,
		const CATPointOnSurface * iPoint2, 
		const double iTol,
		CATSkillValue iMode=BASIC);


/**
* @deprecated V5R13 CATCreateConfusion
*/
ExportedByY300IINT CATConfusionPtOnSurPtOnSur * 
CreateConfusion(CATGeoFactory * iFactory,
		const CATSurParam & iParam1,
		const CATSurParam & iParam2,
		const CATSurface * iSurface,
		const double iTol,
		CATSkillValue iMode=BASIC);
                     
  /**
	* @nodoc
 * Removes a CATConfusionPtOnSurPtOnSur operator from memory.
 */                                      
ExportedByY300IINT void Remove(CATConfusionPtOnSurPtOnSur * iConfusionOperator);


#endif

