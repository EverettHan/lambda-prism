// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CreateCornerPtPCrv :
// creation of an operator of corner between a Point On Surface and a PCurve.
//
//=============================================================================

#ifndef CATCREATECORNERPTPCRV_H 
#define CATCREATECORNERPTPCRV_H 

#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CATMathDef.h"

class CATCornerPtPCrv ;
class CATGeoFactory ;
class CATPCurve ;
class CATPointOnSurface ;
class CATSoftwareConfiguration;

ExportedByY300IINT CATCornerPtPCrv *CATCreateCornerPtPCrv (
							  CATGeoFactory       *Factory,
                CATSoftwareConfiguration *iConfig,
							  CATPointOnSurface   *Point, 
							  CATPCurve           *PCurve, 
							  CATPointOnSurface   *IndPoint, 
							  CATPositiveLength   &Radius,
							  CATSkillValue       iMode = BASIC
							  ) ;

ExportedByY300IINT CATCornerPtPCrv *CATCreateCornerPtPCrv (
							CATGeoFactory       *Factory,
              CATSoftwareConfiguration *iConfig,
							CATPointOnSurface   *Point, 
							CATPCurve           *PCurve,
							int                 Sign,
							CATPositiveLength   &Radius,
							CATSkillValue       iMode = BASIC
							) ;

ExportedByY300IINT void Remove (CATCornerPtPCrv *iOperatorToRemove) ;

#endif


