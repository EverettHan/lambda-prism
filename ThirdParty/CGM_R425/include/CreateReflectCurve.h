#ifndef CreateReflectCurve_H
#define CreateReflectCurve_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @level Protected
 * @usage U1
 */ 

#include "Y300IINT.h"

#include "CATSkillValue.h"
#include "CATMathDirection.h"
#include "CATMathDef.h"
class CATReflectCurve;
class CATGeoFactory;
class CATCurve;
class CATPCurve;
class CATSurface;

/**
 * @deprecated V5R11 CATCreateReflectCurve
 */
ExportedByY300IINT CATReflectCurve * 
CreateReflectCurve(CATGeoFactory * iFactory,
		   CATSurface *iSur,
		   CATMathDirection &iDir,
		   CATAngle iAngle=0.,
		   CATSkillValue mode=BASIC);

/** @nodoc */                                     
ExportedByY300IINT void Remove(CATReflectCurve * iReflectCurve);


#endif

