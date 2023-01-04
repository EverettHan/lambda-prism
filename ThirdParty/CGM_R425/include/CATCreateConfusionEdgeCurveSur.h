#ifndef CATCreateConfusionEdgeCurveSur_H
#define CATCreateConfusionEdgeCurveSur_H

#include "Y300IINT.h"

class CATConfusionEdgeCurveSur;
class CATGeoFactory;
class CATCurve;
class CATEdgeCurve;
class CATPointOnEdgeCurve;
class CATSurface;
class CATSurParam;
class CATSoftwareConfiguration;
class CATSurLimits;

ExportedByY300IINT
CATConfusionEdgeCurveSur * CATCreateConfusionEdgeCurveSur(CATGeoFactory * iFactory,
                           CATSoftwareConfiguration * iConfig,
                           CATEdgeCurve * iECrv, 
                           CATPointOnEdgeCurve * iStartPOEC,
                           CATPointOnEdgeCurve * iEndPOEC,
                           CATCurve * iPCrv0,
                           CATCurve * iPCrv1,
                           CATSurface * iSurface,
                           CATSurLimits & iSurLimits,
                           CATSurParam * iSurParamStart[2],
                           CATSurParam * iSurParamEnd[2]);

#endif




