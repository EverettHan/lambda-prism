// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATFilletTwist:
//  This is a function used to check if a FilletSurface is twisted or not
//  at a point 
//  can be used in constant, variable or tri-tangent fillet 
// 
//=============================================================================
// Usage notes:
//
//=============================================================================
// fev. 99                 
// 31/07/2013  Added software configuration to CATFilletTwistFindDiagnosticAtPoint (Sur/Sur)   XMH
// 21/01/2015  Use a Tab of index "iIndex12CA" to contain index1,index2,indexC,indexA          JSX
// 30/04/2020  Create class with static methods, rather than a bunch of global functions
//             & add FindCurvaturesAtPoint                                                     SMT1
// 19/11/2021  Move file from private interface                                                LJL2
//=============================================================================
#ifndef CATFilletTwist_h
#define CATFilletTwist_h

#include "ConnectInt.h"
#include "CATMathDef.h"
#include "CATMathSetOfPointsND.h"
#include "CATMathSetOfLongs.h"

class CATCurve;
class CATSurface;
class CATSoftwareConfiguration;


class CATFilletTwistUtil
{
    public:
// -----------------------------------------------------------------------------
// Input Variables 
// --------------- 
//    iPoints SetOfPointsND (dimension 14, 15 or 18), iTangents and iParameters
//    index1 = index of the coordinates of point 3D on first support    : P1
//    index2 = ....................................... second ......    : P2
//    indexC = .................................. center of the fillet  : C
//    indexA = ........ the angle between CP1 and CP2
// 
// Output Variables
// ----------------
// oPositions = SetOfPointsND in dimension 2
// coordinates of point No i : 0 -> Start Parameter of Twist No i
//                             1 -> End Parameter of Twist No i
//
// oDescriptions = SetOfLongs 
// element No i = Type of Twist No i
// types are CATFilletTwistOnLimit, CATFilletTwistOnSupport1, CATFilletTwistOnSupport2,
// CATFilletTwistInside.
//
// If theres no twist oPosition = 0, oDescriptions = 0 
//
// Returned value is 0 if no twist detected 1 if twists are detected
// -------------------------------------------------------------------------------

 ExportedByConnectInt static CATBoolean CATFilletTwist(const CATMathSetOfPointsND      & iPoints,
                                                       const CATMathSetOfPointsND      & iTangents,
                                                       const CATMathSetOfPointsND      & iParameters,
                                                       const int                         iIndex12CA[4],
                                                             CATMathSetOfPointsND     *& Positions,
                                                             CATMathSetOfLongs        *& Index,
                                                             CATMathSetOfLongs        *& Descriptions,
                                                             CATLONG32                 & oNbInsertedPts,
                                                       const double                      iResolution,
                                                             CATSoftwareConfiguration  * iConfig,
                                                       const CATTolerance              & iTolObject);


// ---------------------------------------------------------------------------------
// function to test if at one point, there is a twist or not
// ---------------------------------------------------------------------------------

ExportedByConnectInt static CATLONG32 CATFilletTwistCheckAtPoint(const double                   * PointND,
                                                                 const double                   * TangentND,
                                                                 const int                        index12CA[4], 
                                                                       short                    & ioTestSign,
                                                                 const double                     iResolution,
                                                                       CATSoftwareConfiguration * iConfig,
                                                                 const CATTolerance             & iTolObject);

ExportedByConnectInt static CATBoolean CATFilletTwistEvalAtPoint(const double                   * PointND,
                                                                 const double                   * TangentND,
                                                                 const int                        index12CA[4], 
                                                                 const double                     iResolution,
                                                                       double                   & oValue1,
                                                                       double                   & oValue2,
                                                                       CATBoolean               & oIsCurvatureInside,
                                                                       double                   & oValueInside,
                                                                       CATSoftwareConfiguration * iConfig,
                                                                  const CATTolerance            & iTolObject); 

// ---------------------------------------------------------------------------------
// function to find at one twisted point which support causes a twist
// ---------------------------------------------------------------------------------
// en un point ou on a deja detecte un twist sur une des deux traces 
// on analyse les courbures normales des supports pour determiner la
// cause du twist
//
// arguments d'entree
//--------------------
// iPoint : tableau de 4 doubles u1, v1, u2, v2
// iTangent : tableau de 4 doubles du1, dv1, du2, dv2 

ExportedByConnectInt static void CATFilletTwistFindCurvaturesAtPoint(const double                   * iPoint,
                                                                     const double                   * iTangent,
                                                                     const int                        iIndex12CA[4],
                                                                     const CATSurface               * iSurf1,
                                                                     const CATSurface               * iSurf2,
                                                                     const CATLONG32                  iOrientation1,
                                                                     const CATLONG32                  iOrientation2,
                                                                           CATSoftwareConfiguration * iConfig,
                                                                           CATBoolean               & ioDiag1,
                                                                           double                   & iuCurv1,
                                                                           CATBoolean               & ioDiag2,
                                                                           double                   & iuCurv2);

ExportedByConnectInt static CATLONG32 CATFilletTwistFindDiagnosticAtPoint(const double                   * iPoint,
                                                                          const double                   * iTangent,
                                                                          const int                        iIndex12CA[4],
                                                                          const CATSurface               * iSurf1,
                                                                          const CATSurface               * iSurf2,
                                                                          const CATLONG32                  iOrientation1,
                                                                          const CATLONG32                  iOrientation2,
                                                                                CATSoftwareConfiguration * iConfig);

// idem mais pour un fillet courbe surface
// arguments d'entree
//--------------------
// iPoint : tableau de 3 doubles w, u, v
// iTangent : tableau de 4 doubles dw, du, dv 

ExportedByConnectInt static CATLONG32 CATFilletTwistFindDiagnosticAtPoint(const double     * iPoint,
                                                                          const double     * iTangent,
                                                                          const int          iIndex12CA[4],
                                                                          const CATCurve   * iCurve1,
                                                                          const CATSurface * iSurf2,
                                                                          const CATLONG32    iOrientation2,
                                                                          const double       iRadius);

// idem mais pour un fillet courbe courbe
// arguments d'entree
//--------------------
// iPoint : tableau de 3 doubles w1, w2, x, y, z (point centre)
// iTangent : tableau de 4 doubles dw1, dw2, dx, dy, dz 

ExportedByConnectInt static CATLONG32 CATFilletTwistFindDiagnosticAtPoint(const double   * iPoint,
                                                                          const double   * iTangent,
                                                                          const int        iIndex12CA[4],
                                                                          const CATCurve * iCurve1,
                                                                          const CATCurve * iCurve2,
                                                                          const double     iRadius);
};

#endif


