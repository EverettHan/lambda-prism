#ifndef CATCreateContextualSurfaceExtrapol_h
#define CATCreateContextualSurfaceExtrapol_h 

#include "Y300IINT.h"
class CATContextualSurfaceExtrapol;
class CATGeoFactory;
class CATSoftwareConfiguration;

ExportedByY300IINT
CATContextualSurfaceExtrapol * CATCreateContextualSurfaceExtrapol(CATGeoFactory * iFactory,
    CATSoftwareConfiguration * iConfig); 

#endif



