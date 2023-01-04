#ifndef CATPGMCreateCornerPCrvPCrv_h_
#define CATPGMCreateCornerPCrvPCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATMathDef.h"
#include "CATSkillValue.h"

class CATIPGMCornerPCrvPCrv;
class CATGeoFactory;
class CATPCurve;
class CATPointOnSurface;
class CATSoftwareConfiguration;

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMCornerPCrvPCrv *CATPGMCreateCornerPCrvPCrv(
  CATGeoFactory *Factory,
  CATSoftwareConfiguration *iConfig,
  CATPCurve *PCurve1,
  int Sign1,
  CATPCurve *PCurve2,
  int Sign2,
  CATPositiveLength &Radius,
  CATSkillValue iMode = BASIC);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMCornerPCrvPCrv *CATPGMCreateCornerPCrvPCrv(
  CATGeoFactory *Factory,
  CATSoftwareConfiguration *iConfig,
  CATPCurve *PCurve1,
  CATPCurve *PCurve2,
  CATPointOnSurface *PPoint,
  CATPositiveLength &Radius,
  CATSkillValue iMode = BASIC);

#endif /* CATPGMCreateCornerPCrvPCrv_h_ */
