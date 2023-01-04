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

#ifndef CreateHomotopy3Sur_H
#define CreateHomotopy3Sur_H

#include "Y300IINT.h"
#include "CATSkillValue.h"

class CATGeoFactory;
class CATSurface;
class CATOffsetSurface;
class CATHomotopy3Sur;
class CATInitialPoint3Sur;
class CATSoftwareConfiguration;
/**
* @deprecated V5R13 CATCreateHomotopy3Sur
*/
ExportedByY300IINT CATHomotopy3Sur * CreateHomotopy3Sur(CATGeoFactory * iFactory,
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

ExportedByY300IINT void Remove(CATHomotopy3Sur *lyingon);


#endif
