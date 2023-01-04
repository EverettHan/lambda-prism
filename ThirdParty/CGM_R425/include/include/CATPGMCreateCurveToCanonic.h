#ifndef CATPGMCreateCurveToCanonic_h_
#define CATPGMCreateCurveToCanonic_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATDataType.h"
#include "CATSkillValue.h"

class CATCrvLimits;
class CATCrvParam;
class CATCurve;
class CATIPGMCurveToCanonic;
class CATEdgeCurve;
class CATGeoFactory;
class CATPointOnEdgeCurve;
class CATSoftwareConfiguration;
class CATSurface;

// If iSupport is specified, iSupport should be a support of one of the representant
// of iEdgeCurve
// Note : iSupport should be a plane if specified
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMCurveToCanonic *CATPGMCreateCurveToCanonic(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATEdgeCurve *iEdgeCurveToCanonic,
  CATPointOnEdgeCurve *iStartPOEC,
  CATPointOnEdgeCurve *iEndPOEC,
  CATSurface *iSupport = 0,
  CATSkillValue iMode = BASIC);

// If iSupport is specified, iCurveToCanonic should be a pcurve on iSupport
// Note : iSupport should be a plane if specified
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMCurveToCanonic *CATPGMCreateCurveToCanonic(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATCurve *iCurveToCanonic,
  CATCrvLimits &iLimits,
  CATSurface *iSupport = 0,
  CATSkillValue iMode = BASIC);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMCurveToCanonic *CATPGMCreateCurveToCanonic(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  const CATLONG32 iNbCrv,
  CATCurve **iTabCrv,
  CATCrvParam *iStartParam,
  CATCrvParam *iEndParam,
  CATSurface *iSupport = 0);

#endif /* CATPGMCreateCurveToCanonic_h_ */
