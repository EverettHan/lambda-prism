/* -*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CreateHomotopy3Sur :
// creation of an operator of homotopy of three non tangent surfaces 
//
//=============================================================================
//
// Usage Notes:
//
//=============================================================================
// Aug. 97    Creation                         J. Peter
//=============================================================================

#ifndef CATCreateHomotopy3Sur_H
#define CATCreateHomotopy3Sur_H

#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CreateHomotopy3Sur.h"

class CATGeoFactory;
class CATSurface;
class CATOffsetSurface;
class CATHomotopy3Sur;
class CATInitialPoint3Sur;
class CATSoftwareConfiguration;

ExportedByY300IINT CATHomotopy3Sur * CATCreateHomotopy3Sur(CATGeoFactory * iFactory,
                                                        CATSoftwareConfiguration * iConfig,
                                                        CATSurface * iSur1, 
                                                        const double iR1Initial, 
                                                        const double iR1Offset,
                                                        CATSurface * iSur2, 
                                                        const double iR2Initial, 
                                                        const double iR2Offset,
                                                        CATSurface * iSur3, 
                                                        const double iR3Initial, 
                                                        const double iR3Offset,
                                                        CATInitialPoint3Sur * iInit,
                                                        CATSkillValue iMode = BASIC); 


#endif
