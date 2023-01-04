#ifndef CATPGMCreateSurfaceToCanonic_h_
#define CATPGMCreateSurfaceToCanonic_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATCollec.h"
#include "CATSkillValue.h"

class CATGeoFactory;
class CATSoftwareConfiguration;
class CATSurface;
class CATIPGMSurfaceToCanonic;
class CATLISTP(CATSurface);

// Do not use this one....
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMSurfaceToCanonic *CATPGMCreateSurfaceToCanonic(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATLISTP(CATSurface) *iSurList,
  double iTolApprox,
  CATSkillValue iMode = BASIC);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMSurfaceToCanonic *CATPGMCreateSurfaceToCanonic(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATSurface *iSurface,
  double iTolApprox,
  CATSkillValue iMode = BASIC);

#endif /* CATPGMCreateSurfaceToCanonic_h_ */
