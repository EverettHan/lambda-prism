#ifndef CATCreateTryConfusionCrvCrv_H
#define CATCreateTryConfusionCrvCrv_H

#include "Y300IINT.h"

class CATGeoFactory;
class CATCurve;
class CATEdgeCurve;
class CATSoftwareConfiguration;
class CATCrvLimits;
class CATTryConfusionCrvCrv;

ExportedByY300IINT CATTryConfusionCrvCrv * CATCreateTryConfusionCrvCrv(CATGeoFactory * iWhere,
      CATSoftwareConfiguration * iConfig,
			CATCurve * iCrv1,
			const CATCrvLimits & iLimits1,
			CATCurve * iCrv2,
			const CATCrvLimits & iLimits2,
			const double iTolerance);

#endif





