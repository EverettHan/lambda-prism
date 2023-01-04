#ifndef CreateInclusionPtSur_H
#define CreateInclusionPtSur_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @level Protected
 * @usage U1
 */ 

#include "Y300IINT.h"
#include "CATMathDef.h"
#include "CATSkillValue.h"

class CATGeoFactory;
class CATPoint;
class CATSurface;
class CATInclusionPtSur;
class CATMathPoint;

/**
 * @deprecated V5R13 CATCreateinclusion
 */
ExportedByY300IINT CATInclusionPtSur * CreateInclusion(CATGeoFactory * iFactory,
						       const CATPoint * iPt, 
						       const CATSurface *iSur, 
						       const double & iTol,
                                                       const CATBoolean iSearchOnBoundary = TRUE,
                                                       CATSkillValue iMode = BASIC);
/**
 * @deprecated V5R13 CATCreateinclusion
 */
ExportedByY300IINT CATInclusionPtSur * CreateInclusion(CATGeoFactory * iFactory,
						       const CATMathPoint & iPt, 
						       const CATSurface *Sur, 
						       const double & iTol,
                                                       const CATBoolean iSearchOnBoundary = TRUE,
                                                       CATSkillValue iMode = BASIC);
/**
 * @nodoc
 * Removes a CATInclusionPtSur operator from memory.
 */
ExportedByY300IINT void Remove(CATInclusionPtSur *iOperatorToRemove);


#endif




