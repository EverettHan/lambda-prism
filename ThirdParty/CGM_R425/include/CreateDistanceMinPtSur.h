#ifndef CreateDistanceMinPtSur_H
#define CreateDistanceMinPtSur_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @level Protected
 * @usage U1
 */ 

#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CATMathDef.h"

class CATGeoFactory;
class CATPoint;
class CATSurface;
class CATDistanceMinPtSur;
class CATMathPoint;

/**
* @deprecated V5R13 CATCreateDistanceMin
*/
ExportedByY300IINT CATDistanceMinPtSur * CreateDistanceMin(CATGeoFactory * iWhere,
								const CATPoint * iPt, 
								const CATSurface *iSur,
                                      CATBoolean iSearchOnBoundary = TRUE,
								CATSkillValue iMode = BASIC); 
/**
* @deprecated V5R13 CATCreateDistanceMin
*/
ExportedByY300IINT CATDistanceMinPtSur * CreateDistanceMin(CATGeoFactory * iWhere,
                                                           const CATMathPoint & iPt, 
                                                           const CATSurface *iSur,
                                                           CATBoolean iSearchOnBoundary = TRUE,
                                                           CATSkillValue iMode = BASIC); 

/**
 * @nodoc
 */
ExportedByY300IINT void Remove(CATDistanceMinPtSur *iOperatorToRemove);

#endif
