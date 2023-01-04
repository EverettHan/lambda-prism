#ifndef CATCreateCircleTriRelations_H
#define CATCreateCircleTriRelations_H

#include "Y300IINT.h"

class CATCircleTriRelations;
class CATCrvLimits;
class CATGeoFactory;
class CATSurface;
class CATSurLimits;
class CATMathInterval;
class CATSoftwareConfiguration;

ExportedByY300IINT
CATCircleTriRelations * CATCreateCircleTriRelations(CATGeoFactory *iFactory,
                                                    CATSoftwareConfiguration * iSoftwareConfiguration,
                                                    CATSurface * iSupport,
                                                    CATSurLimits &iCenterLimits,
                                                    CATMathInterval &iRadiusLimits);

#endif





