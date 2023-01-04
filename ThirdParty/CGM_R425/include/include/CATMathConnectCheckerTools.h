//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2005
//=============================================================================
//
// CATMathConnectCheckerTools:
//  Basic tools for local analysis of a curve or a surface with mathematical
//  inputs:
//
//    - Normalization of a vector
//    - Frenet basis computation
//    - Curve curvature and curvature first derivative
//      (d/ds, with s = arc length)
//    - Radius of curvature vector first derivative (d/ds, with s = arc length)
//    - Normal to a surface with first derivatives inputs
//    - Surface's normal curvature and normal curvature first derivative
//      (d/ds, with s = arc length)
//    - Projection of a 3D direction on surface's tangent plane 
//
//=============================================================================
// Oct   05 CQI Creation                                                    CQI
// 19/06/08 NLD XScale. reperage par CATHardTol()
// 01/07/08 MWE ajout d'un argument a CurveCurvatureFirstDeriv
// 09/10/08 NLD XScale. suppression des dangereuses valeurs par defaut des tolerances
//              CurveCurvature() et NormalToCurve() recoivent iSqScale
//              2eme signature pour CurveCurvature() pour les appelants voulant
//              les tolerances standard
//              idem pour CurveCurvatureFirstDeriv() et ComputeFrenetBasis()
// 06/03/17 NLD XScale: documentation des usages recomnmandes des tolerances
//=============================================================================

#ifndef CATMathConnectCheckerTools_H
#define CATMathConnectCheckerTools_H

#include "CATTolerance.h"
#include "YN000ANL.h"

#include "CATMathLimits.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATTrackNSTOL.h" // pour CATHardTol

// G-continuity orders (dedicated to CATMathCurveGData and CATMathSurfaceGData)
// *** TO BE MOVED ***
#define G0Continuity 1
#define G1Continuity 2
#define G2Continuity 4
#define G3Continuity 8

// Suggested tolerances for standard factory scale
//
// iTol2 = Tol * Tol, where Tol = 1.e-9 ( = null vector tolerance )
//
// iCRBmin = 1.e-7 = minimum curvature used as a treshold
//
// iCRBmax = 1.e+7 = maximum curvature used as a treshold
//
// iNumTol = CATGetDefaultTolerance().EpsgForRelativeTest() = numerical tolerance

// ------------------------------------------------------------------------------------
//
// GENERIC TOOLS
//
// ------------------------------------------------------------------------------------

// Normalize
//
// Performs the normalization of ioVect 3D vector.
// Returns 0 if ||ioVect||^2 <= iTol2, 1 if it succeeded to normalize.
// N.B XScale: iTol2 must behave like square norm of ioVect        NLD060317
ExportedByYN000ANL int Normalize(CATMathVector & ioVect ,
                                 double          iTol2  ); /*= CATHardTol(1.e-18)*/

// Factorial
//
// Compute N!
ExportedByYN000ANL int Factorial(int iN);

// ------------------------------------------------------------------------------------
//
// CURVE DEDICATED TOOLS
//
// ------------------------------------------------------------------------------------

// ComputeFrenetBasis
//
// Inputs:
//
// iFirstDeriv = first non null derivative (at iTol2 square tol) that defines curve's tangent
//
// iSecDeriv = first non null and non colinear to iFirstDeriv derivative
//
// Outputs:
//
// Frenet basis (oT,oN), where:
// oT = Tangent to curve
// oN = Normal to curve
//
//
// Returns 0 if iFirstDeriv is singular at iTol2, or iSecDeriv is singular at iTol2 OR is colinear
// to iFirstDeriv. Returns 1 if it succeeded.
//
// N.B XScale: iTol2 must be scale independant.                    NLD060317
ExportedByYN000ANL int ComputeFrenetBasis(CATMathVector & iFirstDeriv,
                                          CATMathVector & iSecDeriv  ,
                                          double          iScale     ,
                                          CATMathVector & oT         ,
                                          CATMathVector & oN         );

ExportedByYN000ANL int ComputeFrenetBasis(CATMathVector & iFirstDeriv,
                                          CATMathVector & iSecDeriv  ,
                                          CATMathVector & oT         ,
                                          CATMathVector & oN         ,
                                          double          iTol2      , /*= CATHardTol(1.e-18)*/
                                          double          iSqScale   );/*= CATGetDefaultTolerance().GetSquareScale()*/

// CurveCurvature
//
// Inputs:
//
// Computes the curvature of a curve thanks to its first and second regular derivatives
// (iFirstDeriv and iSecDeriv - see ComputeFrenetBasis):
//
// ip = min{ p in N : d(p)Curve/dt^p != 0 }, e.g. 1 for regular cases
// iq = min{ q in N : d(q)Curve/dt^q != lambda * d(ip)Curve/dt^ip, lambda in R }, e.g. 2 for regular cases
//
// Output:
//
// oCurvature = curve's curvature
//
// Returns 1 if computation is OK, 0 otherwise
//
ExportedByYN000ANL int CurveCurvature(CATMathVector & iFirstDeriv,
                                      CATMathVector & iSecDeriv  , 
                                      int             ip         ,
                                      int             iq         ,
                                      double          iScale     ,
                                      double        & oCurvature );

// N.B XScale: iTol2 must be scale independant.                    NLD060317
ExportedByYN000ANL int CurveCurvature(CATMathVector & iFirstDeriv,
                                      CATMathVector & iSecDeriv  ,
                                      double        & oCurvature ,
                                      int             ip         ,  /* = 1*/
                                      int             iq         ,  /* = 2*/
                                      double          iTol2      ,  /* = CATHardTol(1.e-18)*/
                                      double          iSqScale   ,
                                      double          iCRBmin    ,  /* = CATHardTol(1.e-7)*/
                                      double          iCRBmax    ); /* = CATHardTol(1.e+7)*/

// CurveCurvatureFirstDeriv
//
// Inputs:
//
// iFirstDeriv = curve first derivative associated to its parameter t = C'(t)
//
// iSecDeriv   = curve second derivative associated to its parameter t = C''(t)
//
// iThirdDeriv = curve third derivative associated to its parameter t = C'''(t)
//
// iCurvature  = non signed curve's curvature = k (must be positive)
//
// Output:
//
// odCurvature = dk / ds = curve's curvature first derivative associated to arc length s.
//                         odCurvature could be used for G3-computation on plane curves (null torsion)
//
// Returns 1 if computation is OK, 0 otherwise
//
// N.B XScale: iTol2 must be scale independant.                    NLD060317
// N.B XScale: iCRBmin must behave like power -1 of factory scale. NLD060317
ExportedByYN000ANL int CurveCurvatureFirstDeriv(CATMathVector & iFirstDeriv,
                                                CATMathVector & iSecDeriv  ,
                                                CATMathVector & iThirdDeriv,
                                                double          iCurvature ,
                                                double        & odCurvature,
                                                double          iTol2      ,  /*= CATHardTol(1.e-18)*/
                                                double          iNumTol    ,  /*= CATGetDefaultTolerance().EpsgForRelativeTest()*/
                                                double          iCRBmin    ,  /*= CATHardTol(1.e-7)*/
                                                double          iResol     ); /*= CATGetDefaultTolerance().ResolutionForLengthTest()*/

ExportedByYN000ANL int CurveCurvatureFirstDeriv(CATMathVector & iFirstDeriv,
                                                CATMathVector & iSecDeriv  ,
                                                CATMathVector & iThirdDeriv,
                                                double          iCurvature ,
                                                double          iScale     ,
                                                double        & odCurvature) ;

// CurveRadiusOfCurvatureFirstDeriv
//
// Inputs:
//
// iT          = curve's Frenet tangent
//
// iN          = curve's Frenet normal
//
// iB          = curve's Frenet binormal ( e.g iB = iT ^ iN )
//
// iCurvature  = curve's curvature = k
//
// idCurvature = dk / ds = curve's curvature first derivative associated to arc length s
//
// iTorsion    = curve's torsion
//
//
// Output:
//
// odRds       = dR / ds = curve's radius of curvature vector first derivative associated to arc length s
//                         normalized, and expressed in canonical basis
//
ExportedByYN000ANL void CurveRadiusOfCurvatureFirstDeriv(CATMathVector & iT         ,
                                                         CATMathVector & iN         ,
                                                         CATMathVector & iB         ,
                                                         double          iCurvature ,
                                                         double          idCurvature,
                                                         double          iTorsion   ,
                                                         CATMathVector & odRds      ,
                                                         double          iNumTol    ); /*= CATGetDefaultTolerance().EpsgForRelativeTest()*/

// ------------------------------------------------------------------------------------
//
// SURFACE DEDICATED TOOLS
//
// ------------------------------------------------------------------------------------

// NormalToSurface
//
// Computes the first order normal to a surface, re-oriented with iOrientation (give +1 if it does not import).
//
// Inputs:
//
// iDU = dS(u,v) / du
//
// iDV = dS(u,v) / dv
//
// iOrientation used to re-orient normal (give +1 if unknown)
//
// Output:
//
// oNormal = normalized normal vector to surface
//
// Returns 0 if oNormal is singular (square norm tested at iTol2), 1 otherwise.
//
// N.B XScale: iTol2 must be scale independant.                    NLD060317
ExportedByYN000ANL int NormalToSurface(CATMathVector & iDU         ,
                                       CATMathVector & iDV         ,
                                       int             iOrientation,
                                       CATMathVector & oNormal     ,
                                       double          iTol2       = CATHardTol(1.e-18)
                                      );

// ComputeUVFirstDerivFromDir
//
// Computes the 2D coordinates of the projection of a 3D vector iDir on a surface. 
//
// Inputs:
//
// iDU  = dS(u,v) / du
//
// iDV  = dS(u,v) / dv
//
// iDir = input 3D vector
//
// Outputs:
//
// odu, odv   = 2D coordinates in UV-domain
//
// oE, oF, oG = surface's first fundamental form (optionnal)
//
ExportedByYN000ANL int ComputeUVFirstDerivFromDir(const CATMathVector & iDU ,
                                                  const CATMathVector & iDV ,
                                                  const CATMathVector & iDir,
                                                        double        & odu ,
                                                        double        & odv ,
                                                        double        * oE  = 0,
                                                        double        * oF  = 0,
                                                        double        * oG  = 0);

// ComputeCurvatureAlongDirection
//
// Compute the normal curvature of a surface along UV-direction (idu,idv).
//
// Inputs:
//
// iE, iF, iG = surface's first fundamental form
//
// iL, iM, iN = surface's second fundamental form
//
// idu, idv   = 2D direction in UV-domain
//
// Output:
//
// oK = normal curvature of the surface along (idu,idv) direction
//
ExportedByYN000ANL void ComputeCurvatureAlongDirection(const double   iE ,
                                                       const double   iF ,
                                                       const double   iG ,
                                                       const double   iL ,
                                                       const double   iM ,
                                                       const double   iN ,
                                                       const double   idu,
                                                       const double   idv,
                                                             double & oK );

// ComputeUVFirstAndSecDerivFromDir
//
// Computes the 2D coordinates and first derivative coordinates of the projection of a 3D vector iDir on a surface. 
//
// Inputs:
//
// iDU, iDV, iDU2, iDUDV, iDV2 = surface's first and second derivatives
//
// iDir                        = input 3D vector
//
// Outputs:
//
// odu, odv   = 2D coordinates in UV-domain
//
// od2u, od2v = 2D coordinates first derivative in UV-domain
//
// oE, oF, oG = surface's first fundamental form (optionnal)
//
ExportedByYN000ANL int ComputeUVFirstAndSecDerivFromDir(const CATMathVector & iDU  ,
                                                        const CATMathVector & iDV  ,
                                                        const CATMathVector & iDU2 ,
                                                        const CATMathVector & iDUDV,
                                                        const CATMathVector & iDV2 ,
                                                        const CATMathVector & iDir ,
                                                              double        & odu  ,
                                                              double        & odv  ,
                                                              double        & od2u ,
                                                              double        & od2v ,
                                                              double        * oE   = 0,
                                                              double        * oF   = 0,
                                                              double        * oG   = 0);

// ComputeCurvatureAlongDirection
//
// Compute the normal curvature and its first derivative of a surface along UV-direction (du,dv).
//
// Inputs:
//
// iE, iF, iG                 = surface's first  fundamental form
//
// iL, iM, iN                 = surface's second fundamental form
//
// iDU3, iDU2DV, iDUDV2, iDV2 = surface's third derivatives
//
// iNormal                    = surface's normal
//
// idu, idv                   = 2D direction in UV-domain
//
// id2u, id2v                 = 2D direction first derivatives in UV-domain
//
// Outputs:
//
// oK  = normal curvature of the surface along (idu,idv) direction
//
// oDK = d(oK)/ds = normal curvature first derivative associated to arc length s
//
ExportedByYN000ANL void ComputeCurvatureAlongDirection(const double          iE     ,
                                                       const double          iF     ,
                                                       const double          iG     ,
                                                       const double          iL     ,
                                                       const double          iM     ,
                                                       const double          iN     ,
                                                       const CATMathVector & iDU3   ,
                                                       const CATMathVector & iDU2DV ,
                                                       const CATMathVector & iDUDV2 ,
                                                       const CATMathVector & iDV3   ,
                                                       const CATMathVector & iNormal,
                                                       const double          idu    ,
                                                       const double          idv    ,
                                                       const double          id2u   ,
                                                       const double          id2v   ,
                                                             double        & oK     ,
                                                             double        & oDK    );






#endif

