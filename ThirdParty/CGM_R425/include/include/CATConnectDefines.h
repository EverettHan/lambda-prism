//
// Copyright Dassault Systemes 1998-2009, all rights reserved
//
//=============================================================================
//
// CATConnectDefines :
//
//=============================================================================
// Usage notes:
//=============================================================================
// Jan. 1998     Creation                                       S. Royer
// Sep. 1998     CATConnectToolType                             P-A Lourme
// Oct. 1998     CATConnectTwistType                            P. Catel
// Jun. 2003     CATVariableFilletD1D2ToolType                  H. Leban
// Sep. 2009     CATConnectG2Section                            H. Leban
// May  2011     CATHoldCurveChamferA1ToolType                  UVC
// Oct  2011     CATHoldCurveChamferD2ToolType                  XMH
// June 2012     CATHoldCurveFilletToolType                     XMH
// June 2014     CATHoldCurveChamferGenericD2ToolType           R1Y
// June 2014     CATHoldCurveChamferApproxD2ToolType            R1Y
// Apr  2022     Connect Types [for CATConnectReportInit]		SME31
//=============================================================================
#ifndef CATConnectDefines_h
#define CATConnectDefines_h

#include "CATDataType.h"

#define CATConnectRegular           1
#define CATConnectDegenerated1      2
#define CATConnectDegenerated2      4
#define CATConnectCircle1           8
#define CATConnectCircle2          16
#define CATConnectBlockedSphere    32
#define CATConnectTriTangent       64
#define CATConnectCanonicalPlnCyl 128

#define CATConstantFilletToolType           1
#define CATVariableFilletToolType           2
#define CATChamferD1D2ToolType              3
#define CATChamferD1A1ToolType              4
//#define CATChamferD1A2ToolType            5
//#define CATChamferDD1ToolType             6
#define CATChamferDA1ToolType               7
#define CATEuclidianParallelToolType        8
#define CATEuclidianCornerToolType          9
#define CATCurveMappingOpeToolType         10
#define CATVariableCircleFilletToolType    11
#define CATParallelConnectToolType         12
#define CATSweepSegmentToolType            13
#define CATSweepCircleToolType             14
#define CATDraftBothSidesToolType          20
#define CATHoldCurveCircleFilletToolType   21 
#define CATFilletR1R2ToolType              22 
#define CATChordalFilletToolType           23 
#define CATVariableSweepCircleToolType     24
#define CATVariableChordalFilletToolType   25 
#define CATVariableFilletD1D2ToolType      26
#define CATTritangentFilletToolType        27
#define CATHoldCurveChamferA1ToolType      28
#define CATHoldCurveChamferD2ToolType      29  // From CatCGMStream_2014Fall onwards, this type is replaced with CATHoldCurveChamferGenericD2ToolType
#define CATHoldCurveFilletToolType         30
#define CATChamferApproxD1D2ToolType       31
#define CATHoldCurveChamferGenericD2ToolType 32
#define CATHoldCurveChamferApproxD2ToolType  33

typedef CATLONG32  CATConnectTwistType;

#define CATConnectNoTwist      0   // No Twist
#define CATConnectTwistSurf1   1   // Twist due to Support 1
#define CATConnectTwistSurf2   2   // Twist due to Support 2
#define CATConnectTwistInside  3   // Twist due to CenterCurve
#define CATConnectTwistFolding 4   // "Folding" Twist
#define CATConnectTwistUnknown 5   // Unknown 

//-----------------------------------------------------------------------------
// 
// Support ID : 
// 
//-----------------------------------------------------------------------------

#define CATConnectFirstSupport              0
#define CATConnectSecondSupport             1
#define CATConnectThirdSupport              2
#define CATConnectFourthSupport             3
#define CATConnectNoSupport                -1

//-----------------------------------------------------------------------------
// Diagnostic
//-----------------------------------------------------------------------------

#define CATConnectNoStop                              0
#define CATConnectStopByDomain                        1
//#define CATConnectStopByUserConstraintOnSurface1      2 // -> CATConnectStopByBumperOnEdge1SideIn
//#define CATConnectStopByUserConstraintOnSurface2      3 // -> CATConnectStopByBumperOnEdge1SideOut
#define CATConnectStopBySingularity                   4

// For DraftBothSides
// ******************
#define CATConnectStopByNullAngle                     5
#define CATConnectStopByCutOnMasterSupport            6
#define CATConnectStopByInfiniteLength                7
#define CATConnectStopByTwistConstraintOnSurface1     12
#define CATConnectStopByTwistConstraintOnSurface2     13
#define CATConnectStopByTwistConstraintOnBothSurfaces 14

// For RollingEdgeFillet and KeepKeepFillet (ConstantFilletCrvCrv)
// ***************************************************************
#define CATConnectStopByCutOnEdge1              8
#define CATConnectStopByCutOnEdge2              9
#define CATConnectExitOnEdge1SideIn             16
#define CATConnectExitOnEdge1SideOut            32
#define CATConnectExitOnEdge2SideIn             64
#define CATConnectExitOnEdge2SideOut            128

// For VariableFillet
// ******************
#define CATConnectStopByBlockedSphere           10

// For C1 Cut
#define CATConnectStopByCutOnC1                 200

// For Fillet Section
// ******************
#define CATConnectCircularSection               0
#define CATConnectConicalSection                1
#define CATConnectG2Section                     2


// For Connect Types [for CATConnectReportInit]
// ******************
#define CATConnectCrvSur                0
#define CATConnectSurSur                1


#endif
