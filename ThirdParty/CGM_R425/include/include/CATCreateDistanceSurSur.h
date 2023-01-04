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
#ifndef CATCreateDistanceSurSur_h
#define CATCreateDistanceSurSur_h

#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CATDistanceType.h"

class CATGeoFactory;
class CATCurve;
class CATSurface;
class CATDistanceSurSur;
class CATSoftwareConfiguration;

// Creates an operator for computing the distance between two CATCurves.
ExportedByY300IINT CATDistanceSurSur * CATCreateDistance(CATGeoFactory * iFactory, 
                                                         CATSoftwareConfiguration *Config,
                                                         CATSurface * iSur1,
                                                         CATSurface * iSur2,
                                                         CATDistanceType iDistanceType =CATAbsoluteMinDist,
                                                         CATSkillValue mode = BASIC);

#endif
