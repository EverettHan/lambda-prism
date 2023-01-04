// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CreateTangentLinePCrvPCrv :
// creation of an operator of TangentLine between two PCurves
//
//=============================================================================

#ifndef CATCreateTangentLinePCrvPCrv_h 
#define CATCreateTangentLinePCrvPCrv_h 

#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CATMathDef.h"
#include "CreateTangentLinePCrvPCrv.h"

class CATTangentLinePCrvPCrv ;
class CATGeoFactory ;
class CATPCurve ;
class CATSoftwareConfiguration;

ExportedByY300IINT CATTangentLinePCrvPCrv *
CATCreateTangentLinePCrvPCrv (CATGeoFactory *Factory,
                              CATSoftwareConfiguration *Config,
                              CATPCurve     *PCurve1, 
                              CATPCurve     *PCurve2, 
                              CATSkillValue iMode=BASIC,
                              short         iVerificationMode=1);


#endif


