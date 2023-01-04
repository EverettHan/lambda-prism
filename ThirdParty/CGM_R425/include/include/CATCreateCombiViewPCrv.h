#ifndef CATCreateCombiViewPCrv_H
#define CATCreateCombiViewPCrv_H

#include "Y300IINT.h"
#include "CATSkillValue.h"

class CATCombiViewPCrv;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATGeometry;
class CATPlane;


ExportedByY300IINT
CATCombiViewPCrv * CATCreateCombiViewPCrv(CATGeoFactory * iFactory,
                                       CATSoftwareConfiguration * iConfig,
                                       CATGeometry * iGeometry1,
                                       CATGeometry * iGeometry2,
                                       CATPlane * iSupport1,
                                       CATPlane * iSupport2,
                                       CATPlane * iResultSupport,
                                       CATSkillValue iMode = BASIC);


#endif
