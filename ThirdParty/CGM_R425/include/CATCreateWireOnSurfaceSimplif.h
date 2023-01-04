#ifndef CATCreateWireOnSurfaceSimplif_h
#define CATCreateWireOnSurfaceSimplif_h

#include "Y300IINT.h"
#include "CATGeoOperator.h"

class CATWireOnSurfaceSimplif;
class CATGeoFactory;
class CATEdgeCurve;
class CATPCurve;
class CATPointOnEdgeCurve;
class CATSurface;
class CATCrvParam;
class CATSoftwareConfiguration;
class CATSurLimits;

ExportedByY300IINT
CATWireOnSurfaceSimplif * CATCreateWireOnSurfaceSimplif(CATGeoFactory * iFactory,
                            CATSoftwareConfiguration * iConfig,
                             const CATLONG32 iNbCrv,
                             CATEdgeCurve ** iTabECrv,
                             CATPCurve ** iTabPCrv,
                             CATPointOnEdgeCurve ** iStartPOEC,
                             CATPointOnEdgeCurve ** iEndPOEC,
                             CATSurface * iSurface,
                             const CATSurLimits & iSurLim);

#endif




