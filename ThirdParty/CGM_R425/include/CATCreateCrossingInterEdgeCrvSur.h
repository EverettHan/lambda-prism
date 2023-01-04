#ifndef CATCreateCrossingInterEdgeCrvSur_H
#define CATCreateCrossingInterEdgeCrvSur_H

#include "Y300IINT.h"

class CATCrossingInterEdgeCrvSur;
class CATGeoFactory;
class CATCurve;
class CATPCurve;
class CATEdgeCurve;
class CATPointOnEdgeCurve;
class CATSurface;
class CATSoftwareConfiguration;
class CATSurLimits;


ExportedByY300IINT
CATCrossingInterEdgeCrvSur * CATCreateCrossingInterEdgeCrvSur(CATGeoFactory * iFactory,
                             CATSoftwareConfiguration * iConfig,
                             CATEdgeCurve * iECrv, 
                             CATPointOnEdgeCurve * iStartPOEC,
                             CATPointOnEdgeCurve * iEndPOEC,
                             CATSurface * iSurface,
                             CATSurLimits & iSurLimits);

#endif




