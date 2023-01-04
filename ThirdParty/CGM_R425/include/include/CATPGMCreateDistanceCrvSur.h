#ifndef CATPGMCreateDistanceCrvSur_h_
#define CATPGMCreateDistanceCrvSur_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATDistanceType.h"
#include "CATSkillValue.h"

class CATCurve;
class CATIPGMDistanceCrvSur;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATSurface;

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMDistanceCrvSur *CATPGMCreateDistance(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATCurve *iCurve,
  CATSurface *iSurface,
  CATDistanceType iDistanceType = CATAbsoluteMinDist,
  CATSkillValue mode = BASIC);

#endif /* CATPGMCreateDistanceCrvSur_h_ */
