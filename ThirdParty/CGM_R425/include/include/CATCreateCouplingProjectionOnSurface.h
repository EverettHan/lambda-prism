#ifndef CATCreateCouplingProjectionOnSurface_H
#define CATCreateCouplingProjectionOnSurface_H

#include "Y300IINT.h"
#include "CATCouplingProjectionOnSurface.h"
class CATCouplingProjectionOnSurface;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATEdgeCurve;
class CATPointOnEdgeCurve;
class CATSurface;
class CATSurParam;
class CATPCurve;
class CATMathDirection;




ExportedByY300IINT
CATCouplingProjectionOnSurface * CATCreateCouplingProjectionOnSurface(CATGeoFactory * iFactory,
                                 CATSoftwareConfiguration * iConfig,
                                 CATEdgeCurve * iECrvFirst,
                                 const CATPointOnEdgeCurve * iPOEC_ECrv_First,
                                 CATEdgeCurve * iECrvSecond,
                                 const CATPointOnEdgeCurve * iPOEC_ECrv_Second,
                                 CATSurface * iSurface,
                                 CATSurParam * iParam_First,
                                 CATSurParam * iParam_Second,
                                 CATMathDirection  *iDirection = 0);
ExportedByY300IINT
CATCouplingProjectionOnSurface * CATCreateCouplingProjectionOnSurface(CATGeoFactory * iFactory,
                                 CATSoftwareConfiguration * iConfig,
                                 CATEdgeCurve * iECrvFirst,
                                 const CATPointOnEdgeCurve * iPOEC_ECrv_First,
                                 CATEdgeCurve * iECrvSecond,
                                 const CATPointOnEdgeCurve * iPOEC_ECrv_Second,
                                 CATEdgeCurve * iECrvBord,
                                 CATPointOnEdgeCurve * iPOEC_Proj_First,
                                 CATPCurve * iBord1,
                                 CATPointOnEdgeCurve * iPOEC_Proj_Second,
                                 CATPCurve * iBord2,
                                 CATGeoContinuity   iSharpness,
                                 CATMathDirection  *iDirection = 0);


#endif




