// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CreateTangentAcrossRevolDir:
// creation of an operator that computes all the tangents of a curve 
// perpendicular to a revolution direction
//
//=============================================================================

#ifndef CreateTangentAcrossRevolDir_h 
#define CreateTangentAcrossRevolDir_h 

#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CATMathDef.h"
#include "CATMathDirection.h"

class CATExtractTangentAcrossRevolDir;
class CATGeoFactory ;
class CATCurve ;
class CATPointOnCurve;
class CATSoftwareConfiguration;
/**
* @deprecated V5R13 CATCreateTangentAcrossRevolDir 
*/
ExportedByY300IINT CATExtractTangentAcrossRevolDir *
                     CreateTangentAcrossRevolDir (CATGeoFactory    *Factory,
                        CATSoftwareConfiguration  *iConfig,
                        CATCurve                  *Curve,
                        CATMathPoint              &Origin,
                        CATMathDirection          &Direction,
                        CATPointOnCurve           *StartPoc,
                        CATPointOnCurve           *EndPoc,
                        CATSkillValue              iMode=BASIC);

ExportedByY300IINT void Remove (CATExtractTangentAcrossRevolDir *&iOperatorToRemove) ;

#endif


