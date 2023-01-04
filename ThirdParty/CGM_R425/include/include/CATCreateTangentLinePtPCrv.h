// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CreateTangentLinePtPCrv :
// creation of an operator that computes all the Points passing by a SurParam
// tangent of a PCurve.
//
//=============================================================================

#ifndef CATCREATETANGENTLINEPTPCRV_H 
#define CATCREATETANGENTLINEPTPCRV_H 

#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CreateTangentLinePtPCrv.h"

class CATTangentLinePtPCrv ;
class CATGeoFactory ;
class CATPCurve ;
class CATPointOnSurface ;
class CATSoftwareConfiguration;


ExportedByY300IINT CATTangentLinePtPCrv *CATCreateTangentLinePtPCrv (
                                                                     CATGeoFactory       *iFactory,
                                                                     CATSoftwareConfiguration *Config,
                                                                     CATPointOnSurface   *iPoint, 
                                                                     CATPCurve           *iPCurve, 
                                                                     CATSkillValue       iMode = BASIC,
                                                                     short               VerificationMode = 1
                                                                     ) ;


#endif


