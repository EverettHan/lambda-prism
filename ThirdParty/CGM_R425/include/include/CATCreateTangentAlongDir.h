// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CreateTangentAlongDir:
// creation of an operator that computes all the tangents of a curve 
// parallel to a direction
//
//=============================================================================

#ifndef CATCreateTangentAlongDir_h 
#define CATCreateTangentAlongDir_h 

#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CATMathDef.h"
#include "CATMathDirection.h"
#include "CreateTangentAlongDir.h"

class CATExtractTangentAlongDir;
class CATGeoFactory ;
class CATCurve ;
class CATPointOnCurve;
class CATSoftwareConfiguration;

ExportedByY300IINT CATExtractTangentAlongDir *
CATCreateTangentAlongDir (CATGeoFactory    *Factory,
                          CATSoftwareConfiguration *Config,
                          CATCurve         *Curve,
                          CATMathDirection &Direction,
                          CATPointOnCurve  *StartPoc,
                          CATPointOnCurve  *EndPoc,
                          CATSkillValue iMode=BASIC);


#endif


