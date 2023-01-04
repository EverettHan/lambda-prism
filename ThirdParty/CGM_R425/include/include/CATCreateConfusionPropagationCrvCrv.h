#ifndef CATCreateConfusionPropagationCrvCrv_H
#define CATCreateConfusionPropagationCrvCrv_H

#include "Y300IINT.h"
class CATConfusionPropagationCrvCrv;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATPointOnEdgeCurve;
class CATCurve;
class CATCrvParam;


ExportedByY300IINT CATConfusionPropagationCrvCrv * 
CATCreateConfusionPropagation(CATGeoFactory * iFactory,
                           CATSoftwareConfiguration * iConfig,
                           const CATPointOnEdgeCurve *StartPtOnECrv1,
			                     const CATPointOnEdgeCurve *EndPtOnECrv1,
                           const CATCurve * Crv1,
			                     const CATPointOnEdgeCurve *StartPtOnECrv2,
			                     const CATPointOnEdgeCurve *EndPtOnECrv2,
                           const CATCurve * Crv2,
			                     double tol);

ExportedByY300IINT CATConfusionPropagationCrvCrv * 
CATCreateConfusionPropagation(CATGeoFactory * iFactory,
                                CATSoftwareConfiguration * iConfig,
                                const CATCrvParam & StartParam1,
                                const CATCrvParam & EndParam1,
                                const CATCurve * iCrv1,
                                const CATCrvParam & StartParam2,
                                const CATCrvParam & EndParam2,
                                const CATCurve * iCrv2,
                                const double iTol) ;


#endif



