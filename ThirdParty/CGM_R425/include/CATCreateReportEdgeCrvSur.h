#ifndef CATCreateReportEdgeCrvSur_h
#define CATCreateReportEdgeCrvSur_h

// COPYRIGHT DASSAULT SYSTEMES  1999

#include "Y300IINT.h"

class CATReportEdgeCrvSur;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATEdgeCurve;
class CATPointOnEdgeCurve;
class CATPCurve;
class CATSurface;
class CATPointOnEdgeCurve;
class CATSurParam;

ExportedByY300IINT
CATReportEdgeCrvSur * CATCreateReportCrvSur (CATGeoFactory *iFactory,
            CATSoftwareConfiguration * iConfig,
					  CATEdgeCurve * iECrv,
					  const CATPointOnEdgeCurve * iPOECStart,
					  const CATPointOnEdgeCurve * iPOECEnd,
					  CATPCurve * iPCrv0,
					  CATPCurve * iPCrv1,
					  CATSurface * iSurf,
					  CATPointOnEdgeCurve * ioPOEC0,
					  CATSurParam & iSurParam0,
            const double iTolerance);
#endif




