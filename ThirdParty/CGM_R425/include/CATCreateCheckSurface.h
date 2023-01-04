#ifndef CATCreateCheckSurface_H
#define CATCreateCheckSurface_H

#include "Y300IINT.h"

class CATCheckSurface;
class CATGeoFactory;
class CATSurface;
class CATSoftwareConfiguration;

ExportedByY300IINT
CATCheckSurface * CATCreateCheckSurface(CATGeoFactory *iFactory,
                                        CATSoftwareConfiguration * iConfig,
                                        CATSurface  *iSurface);

#endif



