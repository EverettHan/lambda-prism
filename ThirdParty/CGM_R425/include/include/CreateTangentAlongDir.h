// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CreateTangentAlongDir:
// creation of an operator that computes all the tangents of a curve 
// parallel to a direction
//
//=============================================================================

#ifndef CreateTangentAlongDir_h 
#define CreateTangentAlongDir_h 

#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CATMathDef.h"
#include "CATMathDirection.h"

class CATExtractTangentAlongDir;
class CATGeoFactory ;
class CATCurve ;
class CATPointOnCurve;
/**
* @deprecated V5R13 CATCreateTangentAlongDir 
*/
ExportedByY300IINT CATExtractTangentAlongDir *
                     CreateTangentAlongDir (CATGeoFactory    *Factory,
					    CATCurve         *Curve,
					    CATMathDirection &Direction,
					    CATPointOnCurve  *StartPoc,
					    CATPointOnCurve  *EndPoc,
					    CATSkillValue iMode=BASIC);

ExportedByY300IINT void Remove (CATExtractTangentAlongDir *&iOperatorToRemove) ;

#endif


