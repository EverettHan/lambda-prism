#ifndef CATCreateCheckCurve_H
#define CATCreateCheckCurve_H

#include "Y300IINT.h"

class CATCheckCurve;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATCurve;

ExportedByY300IINT
CATCheckCurve * CATCreateCheckCurve(CATGeoFactory *iFactory,
                                    CATSoftwareConfiguration * iConfig,
                                    CATCurve  *iCurve);

#endif


