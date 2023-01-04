#ifndef CATGeometryUtilities_H
#define CATGeometryUtilities_H

// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CATGeometryUtilities: header providing global methods on CATGeometry
//
//=============================================================================
//
// Usage notes:
//
//=============================================================================
// 06/05/16 R1Y Added ComputeGenericFilletAngleDataAtPoint() (moved from
//              CATRollingBlendSurfaceImplementation).
//=============================================================================

#include "YP00IMPL.h"
#include "CATCGMOutput.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"

#include "CATBoolean.h"
#include "CATCollec.h"

class CATMathBox;
class CATMathAdvancedBox;
class CATCurve;
class CATCrvParam;
class CATSurLimits;
class CATSurface;
class CATMathTransformation;
class CATMathTransformation2D;
class CATSurParam;
class CATMathFunctionX;
class CATMathFunctionXY;
class CATTolerance;

// Returns a CATMathBox surrounding a portion of CATSurface, with regards to
// the provided CATSurlimits.
void ExportedByYP00IMPL ComputeSurfaceBox(const CATSurface*    iSurface, 
                                          const CATSurLimits & iLimits, 
                                                CATMathBox   & oBox);

// Generic Methods for 2D transformations
// Returns TRUE  if the transformation is the Identity
// Returns FALSE if the transformation must be applied
// Throws an exception if the Transformation is not a similitude
// Computes the root square of the determinant and the determinant sign.
ExportedByYP00IMPL CATBoolean IsIdentity2D(const CATMathTransformation2D & iTransfo2D ,
                                                 CATLONG32                 iCheckForSimilitude = 1, 
                                                 double                  * oRatio              = 0, 
                                                 CATLONG32               * oOrientationChange  = 0,
                                                 CATBoolean                iInfnity            = FALSE);

// iSurf1 and iSurf2 must belong to a common equivalence class under the relation
// "A is an offset surface of B" closed by reflectivity, symmetry and transitivity.
// Then this function returns in oParam2 the parametre on iSurf2 corresponding to
// iParam1 on iSurf1.
void ExportedByYP00IMPL GetEquivalentOffsetParam(const CATSurface  * iSurf1,
                                                 const CATSurParam & iParam1,
                                                 const CATSurface  * iSurf2,
                                                       CATSurParam & oParam2);

// Eval3DOn2DCurve - ajout PRG - 17/04/02
// return a non null value if a problem occurs during the evaluation
CATLONG32 ExportedByYP00IMPL Eval3DOn2DCurve(double              paramCrv,
                                             CATMathFunctionX  * U,
                                             CATMathFunctionX  * V,
                                             CATLONG32           iLevelEval, // 0 point, 1 up to first derivative, 2 up to second derivative
                                             CATMathFunctionXY * supportX,
                                             CATMathFunctionXY * supportY,
                                             CATMathFunctionXY * supportZ,
                                             CATMathPoint      & Pt,
                                             CATMathVector     & D1,
                                             CATMathVector     & D2);

//Method for Comparison for Curve Params:
//Comparison of Params first and if it fails, the check 3d distance between them
// if iTolerance is NULL then factory resolution is used
CATBoolean ExportedByYP00IMPL CompareCrvParams(CATCurve     * iCurve1,
                                               CATCurve     * iCurve2,
                                               CATCrvParam  & iParam1,
                                               CATCrvParam  & iParam2,
                                               double       * iTolerance = NULL,
                                               CATCGMOutput * os         = NULL);

//Method for Comparison for Curve Params(double):First Conversion to CATCrvParam type
//and then Comparison of Params  and if it fails, the check 3d distance between them
// if iTolerance is NULL then factory resolution is used
CATBoolean ExportedByYP00IMPL CompareCrvParams(CATCurve     * iCurve1,
                                               CATCurve     * iCurve2,
                                               double         iParam1,
                                               double         iParam2,
                                               double       * iTolerance = NULL,
                                               CATCGMOutput * os         = NULL);

//Method for Comparison for Surface Params:
//Comparison of Params first and if it fails, the check 3d distance between them
//if iTolerance is NULL then factory resolution is used
CATBoolean ExportedByYP00IMPL CompareSurParams(CATSurface  * iSurface1,
                                               CATSurface  * iSurface2,
                                               CATSurParam  & iParam1,
                                               CATSurParam  & iParam2, 
                                               double       * iTolerance = NULL,
                                               CATCGMOutput * os         = NULL);

//Method for Comparison for Surface Params(double):First Conversion to CATSurParam type:
//and then Comparison of Params  and if it fails, the check 3d distance between them
//if iTolerance is NULL then factory resolution is used
CATBoolean ExportedByYP00IMPL CompareSurParams(CATSurface   * iSurface1,
                                               CATSurface   * iSurface2,
                                               double         iParam1_1,
                                               double         iParam1_2,
                                               double         iParam2_1,
                                               double         iParam2_2,
                                               double       * iTolerance = NULL,
                                               CATCGMOutput * os         = NULL);

// Methods for ConeCGM to test values near to zero - one for "relative" tests and one for "length" tests.
// These are placed here in GeometricObject, so they are accessible to GeometricOperators in order to
// avoid re-implementing the test.
CATBoolean ExportedByYP00IMPL IsConeZero_Scale0(const double         iRadius,
                                                const CATTolerance & iTolObject);
CATBoolean ExportedByYP00IMPL IsConeZero_Scale1(const double         iRadius,
                                                const CATTolerance & iTolObject);

// XScale a CATMathTransformation parameter of an odt
CATBoolean ExportedByYP00IMPL CATXScale(      CATMathTransformation & ioTransfo,
                                        const double                  iScaleFactor);

// Function to calculate the angle for a generic fillet, together with the first and second derivatives.
void ExportedByYP00IMPL ComputeGenericFilletAngleDataAtPoint(const double         iRadius,
                                                             const double         iOrientation,
                                                             const CATLONG32      iNullAngle,
                                                             const CATTolerance & iTolObject,
                                                             const CATLONG32      iIndexTrace1,
                                                             const CATLONG32      iIndexTrace2,
                                                             const CATLONG32      iIndexCentre,
                                                             const CATLONG32      iIndexAngle,
                                                                   double       * ioP,
                                                                   double       * ioT,
                                                                   double       * ioC);

#endif
