// COPYRIGHT DASSAULT SYSTEMES 1998
#ifndef CATCREATEDistanceCrvSur_h
#define CATCREATEDistanceCrvSur_h

#include "Y300IINT.h"

#include "CATSkillValue.h"
#include "CATDistanceType.h"

class CATGeoFactory ;
class CATCurve;
class CATSurface;
class CATDistanceCrvSur;
class CATSoftwareConfiguration;


ExportedByY300IINT  CATDistanceCrvSur * CATCreateDistance(CATGeoFactory *iFactory,
                                                          CATSoftwareConfiguration *iConfig,
                                 CATCurve *iCurve, 
                                 CATSurface *iSurface,
                                 CATDistanceType iDistanceType = CATAbsoluteMinDist,
                                 CATSkillValue mode = BASIC);


#endif
