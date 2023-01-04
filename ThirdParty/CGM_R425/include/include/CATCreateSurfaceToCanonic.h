#ifndef CATCreateSurfaceToCanonic_h
#define CATCreateSurfaceToCanonic_h

// COPYRIGHT DASSAULT SYSTEMES  1999

#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CATListOfCATSurfaces.h"
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATSurface;
class CATSurfaceToCanonic;

ExportedByY300IINT
CATSurfaceToCanonic * CATCreateSurfaceToCanonic(CATGeoFactory * iFactory,
                                                CATSoftwareConfiguration * iConfig,
                                                CATSurface * iSurface,
                                                double iTolApprox,
                                                CATSkillValue iMode=BASIC);
// Do not use this one....
ExportedByY300IINT
CATSurfaceToCanonic * CATCreateSurfaceToCanonic(CATGeoFactory * iFactory,
                                                CATSoftwareConfiguration * iConfig,
                                                CATLISTP(CATSurface)* iSurList,
                                                double iTolApprox,
                                                CATSkillValue iMode=BASIC);
#endif



