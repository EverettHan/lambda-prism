#ifndef CATCreateContinuousBySamePCrv_H 
#define CATCreateContinuousBySamePCrv_H

#include "Y300IINT.h"

class CATGeoFactory;
class CATContinuousBySamePCrv;
class CATSoftwareConfiguration;
class CATEdgeCurve;
class CATPointOnEdgeCurve;

ExportedByY300IINT 
CATContinuousBySamePCrv * CATCreateContinuousBySamePCrv (CATGeoFactory * iFactory,
                           CATSoftwareConfiguration * iConfig,
                           CATEdgeCurve * iECrv1,
                           CATEdgeCurve * iECrv2,
                           CATPointOnEdgeCurve * PointOnECrv1,
                           CATPointOnEdgeCurve * PointOnECrv2);
                          

#endif






