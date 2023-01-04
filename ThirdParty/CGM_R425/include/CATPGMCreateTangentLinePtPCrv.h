#ifndef CATPGMCreateTangentLinePtPCrv_h_
#define CATPGMCreateTangentLinePtPCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATSkillValue.h"

class CATGeoFactory;
class CATPCurve;
class CATPointOnSurface;
class CATSoftwareConfiguration;
class CATIPGMTangentLinePtPCrv;

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMTangentLinePtPCrv *CATPGMCreateTangentLinePtPCrv(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *Config,
  CATPointOnSurface *iPoint,
  CATPCurve *iPCurve,
  CATSkillValue iMode = BASIC,
  short VerificationMode = 1);

#endif /* CATPGMCreateTangentLinePtPCrv_h_ */
