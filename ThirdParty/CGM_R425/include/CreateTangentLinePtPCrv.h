// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CreateTangentLinePtPCrv :
// creation of an operator that computes all the Points passing by a SurParam
// tangent of a PCurve.
//
//=============================================================================

#ifndef CREATETANGENTLINEPTPCRV_H 
#define CREATETANGENTLINEPTPCRV_H 

#include "Y300IINT.h"
#include "CATSkillValue.h"

class CATTangentLinePtPCrv ;
class CATGeoFactory ;
class CATPCurve ;
class CATPointOnSurface ;

/**
* @deprecated V5R13 CATCreateTangentLinePtPCrv
*/
ExportedByY300IINT CATTangentLinePtPCrv *CreateTangentLinePtPCrv (
							  CATGeoFactory       *iFactory,
							  CATPointOnSurface   *iPoint, 
							  CATPCurve           *iPCurve, 
							  CATSkillValue       iMode = BASIC,
							  short               VerificationMode = 1
							  ) ;


ExportedByY300IINT void Remove (CATTangentLinePtPCrv *&iOperatorToRemove) ;

#endif


