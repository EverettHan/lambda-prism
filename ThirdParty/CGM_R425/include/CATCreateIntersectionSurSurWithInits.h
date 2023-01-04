#ifndef CATIntersectionSurSurWithInits_h
#define CATIntersectionSurSurWithInits_h

#include "Y300IINT.h"

class CATIntersectionSurSurWithInits;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATSurface;

ExportedByY300IINT CATIntersectionSurSurWithInits * CATCreateIntersectionSurSurWithInits(CATGeoFactory * factory,
    CATSoftwareConfiguration * iConfig,CATSurface *iSurface1,CATSurface *iSurface2);


#endif


