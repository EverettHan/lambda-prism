#ifndef CATCreateBoxUVFrom3DLoop_H
#define CATCreateBoxUVFrom3DLoop_H

#include "Y300IINT.h"
class CATBoxUVFrom3DLoop;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATSurface;
class CATFrFNurbsBipar;

ExportedByY300IINT
CATBoxUVFrom3DLoop * CATCreateBoxUVFrom3DLoop(CATGeoFactory * iFactory,
                                              CATSoftwareConfiguration * iConfig,
                                              CATSurface * iSurface);


ExportedByY300IINT
CATBoxUVFrom3DLoop * CATCreateBoxUVFrom3DLoop(CATGeoFactory * iFactory,
                                              CATSoftwareConfiguration * iConfig,
                                              CATFrFNurbsBipar * iSurface);

#endif


