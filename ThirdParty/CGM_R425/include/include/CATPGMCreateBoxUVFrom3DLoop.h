#ifndef CATPGMCreateBoxUVFrom3DLoop_h_
#define CATPGMCreateBoxUVFrom3DLoop_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"

class CATIPGMBoxUVFrom3DLoop;
class CATFrFNurbsBipar;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATSurface;



/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMBoxUVFrom3DLoop *CATPGMCreateBoxUVFrom3DLoop(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATFrFNurbsBipar *iSurface);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMBoxUVFrom3DLoop *CATPGMCreateBoxUVFrom3DLoop(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATSurface *iSurface);

#endif /* CATPGMCreateBoxUVFrom3DLoop_h_ */
