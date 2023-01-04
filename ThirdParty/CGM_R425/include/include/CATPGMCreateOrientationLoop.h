#ifndef CATPGMCreateOrientationLoop_h_
#define CATPGMCreateOrientationLoop_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATDataType.h"

class CATCrvParam;
class CATGeoFactory;
class CATIPGMOrientationLoop;
class CATPCurve;
class CATSoftwareConfiguration;

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMOrientationLoop *CATPGMCreateOrientationLoop(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  const CATLONG32 iNbPCrv,
  const CATPCurve **iPCrv,
  const CATCrvParam *iStartParam,
  const CATCrvParam *iEndParam);

#endif /* CATPGMCreateOrientationLoop_h_ */
