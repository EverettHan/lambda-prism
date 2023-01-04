// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CreateCurveAffineSupport :
// creation of a CATCurveAffineSupport operator
//=============================================================================
//
// Usage Notes:
//
//=============================================================================
// Jan.  99 Creation                                     X. Gourdon
//=============================================================================

#ifndef CreateCurveAffineSupport_H
#define CreateCurveAffineSupport_H

#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CATMathDef.h"

class CATGeoFactory;
class CATPoint;
class CATCurve;
class CATCurveAffineSupport;

/**
* @deprecated V5R13 CATCreateAffineSupport
*/
ExportedByY300IINT CATCurveAffineSupport * CreateCurveAffineSupport(CATGeoFactory * iWhere,
                                                                    CATCurve * iCurve, 
                                                                    CATSkillValue iMode = BASIC); 
/**
* @deprecated V5R13 CATCreateAffineSupport
*/
ExportedByY300IINT CATCurveAffineSupport * CreateCurveAffineSupport(CATGeoFactory * iWhere,
                                                                    CATCurve ** iCurves,
                                                                    const CATLONG32 iNbCurves,
                                                                    CATSkillValue iMode = BASIC); 


ExportedByY300IINT void Remove(CATCurveAffineSupport *iOperatorToRemove);

#endif
