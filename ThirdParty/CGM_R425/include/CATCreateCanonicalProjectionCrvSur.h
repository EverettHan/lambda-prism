#ifndef CATCreateCanonicalProjectionCrvSur_H
#define CATCreateCanonicalProjectionCrvSur_H

#include "Y300IINT.h"
#include "CATMathDef.h"

class CATCanonicalProjectionCrvSur;
class CATGeoFactory;
class CATCurve;
class CATSurface;
class CATPCurve;
class CATMathPlane;
class CATSoftwareConfiguration;


ExportedByY300IINT
CATCanonicalProjectionCrvSur * CATCreateCanonicalProjection(CATGeoFactory * iFactory,
                                                            CATSoftwareConfiguration * iConfig,
                                                            CATCurve * iCurve,
                                                            CATSurface * iSurface);


ExportedByY300IINT
CATCanonicalProjectionCrvSur * CATCreateCanonicalProjection(CATGeoFactory * iFactory,
                                                            CATSoftwareConfiguration * iConfig,
                                                            CATCurve * iCurve,
                                                            const CATMathPlane & iMathSupport);
#endif








