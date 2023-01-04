#ifndef CATPGMCreateDistanceSurSur_h_
#define CATPGMCreateDistanceSurSur_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATDistanceType.h"
#include "CATSkillValue.h"

class CATCurve;
class CATIPGMDistanceSurSur;
class CATGeoFactory;
class CATSurface;

/**
* @deprecated V5R13 CATPGMCreateDistance
* @return [out, IUnknown#Release]
*/
ExportedByCATGMModelInterfaces CATIPGMDistanceSurSur *CATPGMCreateDistance(
  CATGeoFactory *iFactory,
  CATSurface *iSur1,
  CATSurface *iSur2,
  CATDistanceType iDistanceType = CATAbsoluteMinDist,
  CATSkillValue mode = BASIC);

#endif /* CATPGMCreateDistanceSurSur_h_ */
