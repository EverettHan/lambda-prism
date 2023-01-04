/* -*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CATHomotopyUtilities: header providing global methods for Homotopy
//
//=============================================================================
// Sept. 98 ILY Creation                           I. Levy
// 28/11/18 NLD Mise au propre: detabulation, smart indent
//              Documentation XScale
// 22/06/22 NLD CalculateCurvatureRadius() remplace CalculateCurvature()
//=============================================================================
// 
// Usage for CGM only 
//
//=============================================================================

#ifndef CATHomotopyUtilities_H
#define CATHomotopyUtilities_H

#include "Y30C3XGG.h"
#include "CATDataType.h"
#include "CATIsoParameter.h"
#include "CATSoftwareConfiguration.h"
#include "CATTolerance.h"

class CATMathTransformation1D;
class CATMathVector;
class CATMathDirection;
class CATSurface;
class CATCurve;
class CATSurParam;
class CATGeoFactory;
class CATSurLimits;
class CATMathFunctionXY;
class CATSubdivGridSurface;
class CATNurbsSurface;


//---------------------------------------------------------------------------
// CalculateCurvature: Calculate the curvature of a surface
//    at a given position
//---------------------------------------------------------------------------
// CAUTION: returns a curvature radius (and not a curvature)        NLD060622
//          CalculateCurvature() renamed CalculateCurvatureRadius() NLD220622
double ExportedByY30C3XGG
CalculateCurvatureRadius                    (      CATGeoFactory            * iFactory  ,
                                             const CATMathFunctionXY        * iFunctionX,
                                             const CATMathFunctionXY        * iFunctionY,
                                             const CATMathFunctionXY        * iFunctionZ,
                                                   CATMathVector            & iDu ,
                                                   CATMathVector            & iDv ,
                                                   CATMathVector            & iDu2,
                                                   CATMathVector            & iDuv,
                                                   CATMathVector            & iDv2,
                                             const CATSurface               * iSurface,
                                                   CATSurParam              & iSurParam,
                                                   int                        iIsPole,
                                                   CATSoftwareConfiguration * iConfig = NULL);


//---------------------------------------------------------------------------
// ComputeDerivatives
//---------------------------------------------------------------------------
void ExportedByY30C3XGG ComputeDerivatives(const double                  *  iGlobalParam,
                                           const CATMathFunctionXY       *  FunctionX,
                                           const CATMathFunctionXY       *  FunctionY,
                                           const CATMathFunctionXY       *  FunctionZ,
                                                 CATMathVector             &oDu,
                                                 CATMathVector             &oDv,
                                                 CATMathVector             &oDu2,
                                                 CATMathVector             &oDuDv,
                                                 CATMathVector             &oDv2,
                                                 CATSoftwareConfiguration * iConfig = NULL);

//---------------------------------------------------------------------------
// IsExtrapolable: returns 1 if Surface is extrapolable
//---------------------------------------------------------------------------
short ExportedByY30C3XGG IsExtrapolableSurface(const CATSurface               * iSurface,
                                                     CATSoftwareConfiguration * iConfig = NULL);

//---------------------------------------------------------------------------
// IsExtrapolable: returns 1 if Curve is extrapolable
//---------------------------------------------------------------------------
short ExportedByY30C3XGG IsExtrapolableCurve(const CATCurve                 * iCurve,
                                                   CATSoftwareConfiguration * iConfig = NULL);

//---------------------------------------------------------------------------
// SetInside: set iosys inside domain
// iTol should be non-scaled quantity.
//---------------------------------------------------------------------------
// XScale
// -----
// CAUTION: 
// as of Nov 28th 2018
// iTol in input of SetInside() (both methods) is internally used as a relative tolerance (not depending on factory scale)
// iTol in input of IsInside () is internally used as an absolute tolerance (depending on factory scale)
// This might be taken into account or fixed
// NLD281118
void ExportedByY30C3XGG SetInside(const CATLONG32                   iDimension,
                                  const double                   *  iDomain   ,
                                        double                   *  ioSolution,
                                  const CATTolerance              & nTol      ,
                                  const double                      iTol      = 0   );

void ExportedByY30C3XGG SetInside(const CATLONG32                   iDimension,
                                  const double                   *  iDomain   ,
                                        double                   *  ioSolution,
                                        CATSoftwareConfiguration *  iConfig   ,
                                  const CATTolerance              & nTol      ,
                                  const double                      iTol      = 0 );

short ExportedByY30C3XGG IsInside(const CATLONG32                   iDimension,
                                  const double                   *  iDomain   ,
                                        double                   *  ioSolution,
                                  const CATTolerance              & nTol,
                                  const double                      iTol   = 0 );

//---------------------------------------------------------------------------
// IsPoleSliding: returns 1 if the pole slides along normal
//---------------------------------------------------------------------------
CATLONG32 ExportedByY30C3XGG IsPoleSliding(const CATSurface               *  iSurface    ,
                                           const CATMathDirection          & iNormal     ,
                                           const CATSurParam               & iSurParam   ,
                                                 CATSoftwareConfiguration *  iConfig     = NULL);
//---------------------------------------------------------------------------
// HasPole : returns 1 if the surface has a pole
//           returns what parameter that corresponds to the degenerate Isopar
//---------------------------------------------------------------------------
short     ExportedByY30C3XGG CanonicalSurfaceHasAPole(const CATSurface               *  iSurface         ,
                                                            CATIsoParameter           & oDegenerateIsopar,
                                                            CATSoftwareConfiguration *  Config           );

//---------------------------------------------------------------------------
// AnalyseCurvature
// We suppose that iSurf0 and iSurf1 have the same tangent plane at 
// iPar0 and iPar1 (same 3D point)
//          returns 1 if iSurf0 et iSurf1 have the same curvature along 
//                    a few directions at the params iPar0 and iPar1 
//          returns 0 if not
//--------------------------------------------------------------------------- 
CATLONG32 ExportedByY30C3XGG  AnalyseCurvature(           CATSurface               *  iSurf0  ,
                                                          CATSurface               *  iSurf1  ,
                                                    const CATSurParam               & iPar0   ,
                                                    const CATSurParam               & iPar1   ,
                                                    const CATMathDirection          & iNormal0,
                                                    const CATMathDirection          & iNormal1,
                                                          CATSoftwareConfiguration *  iConfig = NULL);

void      ExportedByY30C3XGG FindUnderlyingNurbs   (const CATSurface               *  Surf,
                                                    const CATNurbsSurface          *& Nurbs1,
                                                    const CATNurbsSurface          *& Nurbs2);

void      ExportedByY30C3XGG FindUnderlyingSubdiv  (const CATSurface               *  Surf    ,
                                                    const CATSubdivGridSurface     *& oSubdiv1,
                                                    const CATSubdivGridSurface     *& oSubdiv2);

void      ExportedByY30C3XGG GetOriginalLimits      (const CATSubdivGridSurface    *  iSubdiv,
                                                           CATSurLimits             & oOriginalLimits);


#endif

