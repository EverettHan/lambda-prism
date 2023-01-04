#ifndef CATCreateAutoIntersectionPCrv_H
#define CATCreateAutoIntersectionPCrv_H

#include "Y30UIUTI.h"
class CATAutoIntersectionPCrv;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATPCurve;
class CATCrvLimits;

ExportedByY30UIUTI
CATAutoIntersectionPCrv * CATCreateAutoIntersectionPCrv(CATGeoFactory *iFactory,CATSoftwareConfiguration * iConfig,
    CATPCurve * iPCrv, CATCrvLimits &iCrvLimits);

#endif



