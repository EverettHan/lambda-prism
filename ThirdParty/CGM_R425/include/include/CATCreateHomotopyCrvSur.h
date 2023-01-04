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

#ifndef CATreateHomotopyCrvSur_H
#define CATCreateHomotopyCrvSur_H

#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CreateHomotopyCrvSur.h"

class CATGeoFactory;
class CATSurface;
class CATOffsetSurface;
class CATEdgeCurve;
class CATPCurve;
class CATHomotopyCrvSur;
class CATInitialPointCrvSur;
class CATSoftwareConfiguration;
class CATCrvParam;

ExportedByY300IINT CATHomotopyCrvSur * CATCreateHomotopyCrvSur(CATGeoFactory * iFactory,
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

// Creates an HomotopyCrvSur operator dedicated to extrapolation of a curve (not necesseraly a CATPCurve)
// up to a target plane
//
// INPUT
//
// iExtrapolDirection == -1 extrapolation is at the left
// iExtrapolDirection ==  1 extrapolation is at the right
// iExtrapolDirection ==  0 extrapolation is at the left or right
// see CATExtrapolCurve for more details
//
// OUTPUT. To get results use the following methods :
// 
// CATHomotopyDiag GetHomotopyDiag() : - CATHomotopyOK if succeeded
//                                     - CATHomotopyStop if extrapolation did not reached target plane
//                                     - CATHomotopyDegenerateSystem if reached point is singular (ie.
//                                       tangent to curve is orthogonal to plane).
//
// If not OK (Diag != 0), test diag thanks to & operator : ex. if(Diag & CATHomotopyStop)
//
// CATCrvParam  GetCrvParam()        : returns the CrvParam on EC solution. If CATHomotopyOK, it corresponds
//                                     to the CrvParam which performs intersection between curve and target plane.
//
// double GetRadiusEdgeStop()        : returns the maximum offset radius reached.
// 
//
ExportedByY300IINT CATHomotopyCrvSur * CATCreateHomotopyCrvSur(CATGeoFactory            * iFactory,
                                                               CATSoftwareConfiguration * iConfig,
                                                               CATSurface               * iPlane,
                                                               CATEdgeCurve             * iEdgeCurve,
                                                               const CATCrvParam        & iCrvInit,
                                                               const short                iExtrapolDirection,
                                                               CATSkillValue              iMode = BASIC);


#endif
