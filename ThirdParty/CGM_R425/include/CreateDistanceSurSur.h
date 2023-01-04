// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CreateDistanceSurSur :
// creation of an operator of distance beetween two surfaces
//
//=============================================================================
//
// Usage Notes:
//
//=============================================================================
// Jan. 98    Creation                         Migration CXR1 - CXR2
//=============================================================================
#ifndef CreateDistanceSurSur_h
#define CreateDistanceSurSur_h

#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CATDistanceType.h"

class CATGeoFactory;
class CATCurve;
class CATSurface;
class CATDistanceSurSur;

/**
* @deprecated V5R13 CATCreateDistance
*/
ExportedByY300IINT CATDistanceSurSur * CreateDistance(CATGeoFactory * iFactory, 
                                                            CATSurface * iSur1,
                                                            CATSurface * iSur2,
                                                            CATDistanceType iDistanceType =CATAbsoluteMinDist,
                                                            CATSkillValue mode = BASIC);
// Removes a CATDistanceSurSur operator from memory.
ExportedByY300IINT void Remove(CATDistanceSurSur *iOperatorToRemove);
#endif
