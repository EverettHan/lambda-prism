#ifndef CATCreateOrientationLoop_H
#define CATCreateOrientationLoop_H

#include "Y300IINT.h"
#include "CATMathDef.h"

class CATOrientationLoop;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATPCurve;
class CATCrvParam;

ExportedByY300IINT
CATOrientationLoop * CATCreateOrientationLoop(CATGeoFactory * iFactory,
         CATSoftwareConfiguration * iConfig,
		     const CATLONG32 iNbPCrv,
		     const CATPCurve ** iPCrv,
		     const CATCrvParam * iStartParam,
		     const CATCrvParam * iEndParam);

#endif





