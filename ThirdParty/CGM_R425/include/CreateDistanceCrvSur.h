// COPYRIGHT DASSAULT SYSTEMES 1998
#ifndef CREATEDistanceCrvSur_h
#define CREATEDistanceCrvSur_h

#include "Y300IINT.h"

#include "CATSkillValue.h"
#include "CATDistanceType.h"

class CATGeoFactory ;
class CATCurve;
class CATSurface;
class CATDistanceCrvSur;

/**
* @deprecated V5R13 CATCreateDistance
*/
ExportedByY300IINT  CATDistanceCrvSur * CreateDistance(CATGeoFactory *iFactory,
                                 CATCurve *iCurve, 
                                 CATSurface *iSurface,
                                 CATDistanceType iDistanceType = CATAbsoluteMinDist,
                                 CATSkillValue mode = BASIC);

ExportedByY300IINT void Remove(CATDistanceCrvSur *iOperatorToRemove);

#endif
