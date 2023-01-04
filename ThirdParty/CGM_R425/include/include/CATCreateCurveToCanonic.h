#ifndef CATCreateCurveToCanonic_H
#define CATCreateCurveToCanonic_H 

#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CATSurface.h"
#include "CATGeoOpTimer.h"

class CATCurveToCanonic;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATEdgeCurve;
class CATPointOnEdgeCurve;
class CATCurve;
class CATCrvLimits;
class CATCrvParam;

// If iSupport is specified, iSupport should be a support of one of the representant
// of iEdgeCurve
// Note : iSupport should be a plane if specified
ExportedByY300IINT 
CATCurveToCanonic * CATCreateCurveToCanonic(CATGeoFactory * iFactory,
                                         CATSoftwareConfiguration * iConfig,
                                         CATEdgeCurve * iEdgeCurveToCanonic,
                                         CATPointOnEdgeCurve * iStartPOEC,
                                         CATPointOnEdgeCurve * iEndPOEC,
                                         CATSurface * iSupport=0,
                                         CATSkillValue iMode = BASIC);

// If iSupport is specified, iCurveToCanonic should be a pcurve on iSupport
// Note : iSupport should be a plane if specified
ExportedByY300IINT 
CATCurveToCanonic * CATCreateCurveToCanonic(CATGeoFactory * iFactory,
                                         CATSoftwareConfiguration * iConfig,
                                         CATCurve * iCurveToCanonic,
                                         CATCrvLimits & iLimits,
                                         CATSurface * iSupport=0,
                                         CATSkillValue iMode = BASIC);



ExportedByY300IINT
CATCurveToCanonic * CATCreateCurveToCanonic(CATGeoFactory * iFactory,
                                            CATSoftwareConfiguration * iConfig,
                                            const CATLONG32 iNbCrv,
                                            CATCurve ** iTabCrv,
                                            CATCrvParam * iStartParam,
                                            CATCrvParam * iEndParam,
                                            CATSurface * iSupport=0);

#endif


