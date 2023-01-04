#ifndef CATCreateIntersectionSurSurGen_h
#define CATCreateIntersectionSurSurGen_h

#include "Y300IINT.h"

class CATIntersectionSurSurGen;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATSurface;

ExportedByY300IINT
CATIntersectionSurSurGen * CATCreateIntersectionSurSurGen(CATGeoFactory * iFactory, 
                                     CATSoftwareConfiguration * iConfig,
                                     CATSurface * iSurface1, CATSurface * iSurface2);

#endif





