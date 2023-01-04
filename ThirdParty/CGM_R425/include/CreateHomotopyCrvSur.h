/* -*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CreateHomotopyCrvSur :
// creation of an operator of homotopy for a curve and a surface
// ( two tangent surfaces and a third one ) 
//
//=============================================================================
//
// Usage Notes:
//
//=============================================================================
// Aug. 97    Creation                         J. Peter
//=============================================================================

#ifndef CreateHomotopyCrvSur_H
#define CreateHomotopyCrvSur_H

#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CATDataType.h"

class CATGeoFactory;
class CATSurface;
class CATOffsetSurface;
class CATEdgeCurve;
class CATPCurve;
class CATHomotopyCrvSur;
class CATInitialPointCrvSur;
class CATSoftwareConfiguration;
/**
* @deprecated V5R13 CATCreateHomotopyCrvSur
*/
ExportedByY300IINT CATHomotopyCrvSur * CreateHomotopyCrvSur(CATGeoFactory * iFactory,
                                                            CATSoftwareConfiguration * iConfig,
                                                            CATSurface * iSurface,
                                                            const double iRSurInitial,
                                                            const double iRSurOffset,
                                                            CATEdgeCurve * iEdgeCurve,
                                                            CATSurface * iSupport1,
                                                            CATSurface * iSupport2,
                                                            const CATLONG32 iSignOffsetSur1,
                                                            const CATLONG32 iSignOffsetSur2,
                                                            const double iREdgeInitial,
                                                            const double iREdgeOffset, 
                                                            CATInitialPointCrvSur * iInit,
                                                            CATSkillValue iMode = BASIC); 


ExportedByY300IINT void Remove(CATHomotopyCrvSur *lyingon);


#endif
