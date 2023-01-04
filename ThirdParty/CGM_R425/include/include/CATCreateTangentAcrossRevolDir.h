// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CreateTangentAcrossRevolDir:
// creation of an operator that computes all the tangents of a curve 
// perpendicular to a revolution direction
//
//=============================================================================

#ifndef CATCreateTangentAcrossRevolDir_h 
#define CATCreateTangentAcrossRevolDir_h 

#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CATMathDef.h"
#include "CATMathDirection.h"
#include "CreateTangentAcrossRevolDir.h"

class CATExtractTangentAcrossRevolDir;
class CATGeoFactory ;
class CATCurve ;
class CATPointOnCurve;
class CATSoftwareConfiguration;

ExportedByY300IINT CATExtractTangentAcrossRevolDir *
                     CATCreateTangentAcrossRevolDir (CATGeoFactory    *Factory,
                        CATSoftwareConfiguration  *iConfig,
                        CATCurve                  *Curve,
                        CATMathPoint              &Origin,
                        CATMathDirection          &Direction,
                        CATPointOnCurve           *StartPoc,
                        CATPointOnCurve           *EndPoc,
                        CATSkillValue              iMode=BASIC);


#endif


