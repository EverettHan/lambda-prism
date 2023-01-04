#ifndef CATCreateIntersectionEdgeCrvSur_h
#define CATCreateIntersectionEdgeCrvSur_h

// COPYRIGHT DASSAULT SYSTEMES  1999

#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CATDataType.h"

class CATGeoFactory;
class CATIntersectionEdgeCrvSur;
class CATEdgeCurve;
class CATSurface;
class CATPointOnEdgeCurve;
class CATCurve;
class CATSoftwareConfiguration;

ExportedByY300IINT
CATIntersectionEdgeCrvSur * CATCreateIntersection (CATGeoFactory *iFactory,
                                                   CATSoftwareConfiguration * iConfig,
				                                           CATEdgeCurve *iECrv,
						                                       const CATCurve ** iTabCrv,
						                                       const CATLONG32 iNbCrv,
                                                   CATSurface *iSurface,
				                                           CATSkillValue  mode);


ExportedByY300IINT
CATIntersectionEdgeCrvSur * CATCreateIntersection (CATGeoFactory *iFactory,
                                                   CATSoftwareConfiguration * iConfig,
                                                   CATEdgeCurve *iECrv,
                                                   const CATPointOnEdgeCurve * iPOECStart,
                                                   const CATPointOnEdgeCurve * iPOECEnd,
                                                   const CATCurve ** iTabCrv,
                                                   const CATLONG32 iNbCrv,
                                                   CATSurface *iSurface,
                                                   CATSkillValue  mode);
#endif



