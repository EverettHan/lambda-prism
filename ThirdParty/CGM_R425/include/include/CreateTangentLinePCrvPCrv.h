// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CreateTangentLinePCrvPCrv :
// creation of an operator of TangentLine between two PCurves
//
//=============================================================================

#ifndef CreateTangentLinePCrvPCrv_h 
#define CreateTangentLinePCrvPCrv_h 

#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CATMathDef.h"

class CATTangentLinePCrvPCrv ;
class CATGeoFactory ;
class CATPCurve ;
/**
* @deprecated V5R13 CATCreateTangentLinePCrvPCrv
*/
/*
ExportedByY300IINT CATTangentLinePCrvPCrv *
                   CreateTangentLinePCrvPCrv (CATGeoFactory *Factory,
					      CATPCurve     *PCurve1, 
					      CATPCurve     *PCurve2, 
					      CATSkillValue iMode=BASIC,
					      short         iVerificationMode=1);
*/

ExportedByY300IINT void Remove (CATTangentLinePCrvPCrv *&iOperatorToRemove) ;

#endif


