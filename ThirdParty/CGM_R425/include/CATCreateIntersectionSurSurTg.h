#ifndef CATCreateIntersectionSurSurTg_H
#define CATCreateIntersectionSurSurTg_H

#include "Y300IINT.h"

class CATIntersectionSurSurTg;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATSurface;
class CATPCurve;
class CATSurLimits;
class CATCrvLimits;

ExportedByY300IINT CATIntersectionSurSurTg * CATCreateIntersectionSurSurTg(CATGeoFactory * iFactory,
    CATSoftwareConfiguration * iConfig,
    CATSurface * iSurface1, 
    CATSurface * iSurface2,
    CATPCurve * iPCrv1,
    CATPCurve * iPCrv2,
    const CATSurLimits & iSurLimits1, 
    const CATSurLimits & iSurLimits2,
    const CATCrvLimits & iCrvLimits1,
    const CATCrvLimits & iCrvLimits2,
    short iOriPC2vsPC1);


#endif


