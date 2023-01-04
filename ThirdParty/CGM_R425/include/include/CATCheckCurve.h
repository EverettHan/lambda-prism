// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
// Jun 99 Creation                       XGN
// Jan 04 Versionning de l'operateur     EAB
//
//=============================================================================
// Usage notes:
//  This operator is used to check the internal validity (ERROR and WARNINGS) of the curve on a given CrvLimits:
//  
//  I - Length
//   1/ The curve is not too short (length > resolution) ERROR
//   2/ each arc of the curve is not too short (length > resolution) WARNING
//
//  II - Parametrization
//
//   1/ The curve must be of class C2 (not G2) ERROR
//   2/ The tangent of the curve must nether vanish (norm > resolution in 3D) ERROR
//      even at the extremities
//   3/ The mean parametrization must be "close" to curvilign (ratio between 0.1 and 10.)  WARNING
//       If too much difference between maximum and minimum distortion :  ERROR
//   4/ The radius of curvature must be bigger than the resolution at each point  ERROR 
//   5/ The norm of the tangent must be consistent with estimated curve length/deltaparam WARNING
//         ( ratio between (.83 and 1.22) for PSpline)
//         ( ratio between (.1 and 2.) for all other curves )
//
//  III - Canonical curves
//
//   1/ To avoid numerical cancellations, the definition point of the canonical curves 
//      must be in the geometric infinity ERROR
//      (examples : center of circle, of ellipse, vertex of parabola, ...)
//
//   2/ A canonical curve must not be non degenerated.ERROR
//      (examples : an ellipse with minor radius < _resolution looks like a line, so
//       it is not authorized; a too sharp parabola is not authorized, etc...)
//   
//  IV - Beziers-like curves
//
//   The distance between two distinct control points must be > resolution.
//
//  V - EdgeCurves
//
//   When the SetEdgeCurveLimits method has been specified, verify recursively 
//   that the curves inside the MergedCurve are close.
//
//=============================================================================
#ifndef CATCheckCurve_H
#define CATCheckCurve_H

#include "Y30UIUTI.h"

#include "CATCGMOperator.h"

#include "CATCrvLimits.h"
#include "CATCrvParam.h"
#include "CATSurface.h"
#include "CATMathDef.h"
#include "CATCreateCheckCurve.h"

class CATGeoFactory;
class CATCurve;
class CATPointOnEdgeCurve;
class CATError;
class CATCGMOutput;
class CATSoftwareConfiguration;

class ExportedByY30UIUTI CATCheckCurve : public CATCGMOperator
{
public:
   //-----------------------------------------------------------------------
   //- Object management
   //-----------------------------------------------------------------------

   CATCheckCurve (CATGeoFactory *iFactory,CATSoftwareConfiguration * iConfig, CATCurve  *iCurve);	

   ~CATCheckCurve ();

   //-----------------------------------------------------------------------
   //- Settings methods
   //-----------------------------------------------------------------------

   void SetLimits(const CATCrvLimits & iLimits);
   void SetEdgeCurveLimits(const CATPointOnEdgeCurve * iPOECStart,
                           const CATPointOnEdgeCurve * iPOECEnd);
   
   void SetCheckEdgeGap(CATBoolean iSetCheckGap = TRUE);
   
   //-----------------------------------------------------------------------
   //- Get methods
   //-----------------------------------------------------------------------

   // Array of errors pointers is returned (0 is no error found)
   // This array (and contained errors) must be deleted by the caller.
   CATError ** GetCheckResult(CATLONG32 & oNbErrors);
   CATLONG32 GetNumberOfErrors();
   CATLONG32 GetNumberOfWarnings();
   //
   // Return a Diagnostic for TangentDesign only for IntCurve.
   // 0 is No Tangent
   // 1 Is Tangent and the supports of Two Pcurve of intCurve is returned
   // If oCheckGap = 1 MaxGap of IntCurve > Resolution(10e-3)
   // If oCheckGap = 2 MaxGap of IntCurve > 0.1*Resolution (10e-4)
   // else oCheckGap = 0
   int GetTangentDiagnostic (int* oCheckGap, CATSurface ** oSupport1=0, CATSurface ** oSupport2=0);
   //
   // Return a Diagnostic for TangentDesign only for IntCurve and oCheckGap = 0.
   // Perfos (Not calculate a MaxGap of IntCurve)
   // 
   void  setOnlyTangentDiagnostic ();
   //-----------------------------------------------------------------------
   //- Running the operator
   //-----------------------------------------------------------------------

   int Run();

   //-----------------------------------------------------------------------
   //- For internal use only : Write in the console the detected errors when
   //  encountered during the Run()
   //-----------------------------------------------------------------------
   void SetConsoleOutput();
   void SetOutput(CATCGMOutput & os);

   //-----------------------------------------------------------------------
   // Perform more check. Warning : this mode is expensive
   //-----------------------------------------------------------------------
   void SetAdvancedMode();

   //-----------------------------------------------------------------------
   // Check Only Errors (For Boolean Team == Healing)
   //-----------------------------------------------------------------------
   void SetOnlyErrors();

protected:
   void Initialize();

   void RunAdvanced();

   CATBoolean Sampling(CATLONG32 iSamplingCount, double *iFirstSquareNorm,
      double &iRoughLength, CATLONG32 iNoArc);


   // - I  - Length of curves
   // Data related to length of curve
   CATBoolean _CurveTooShort;
   // Length of arc
   CATBoolean _ArcTooShort;
   CATLONG32 _IndexArcTooShort;

   // - II - Parametrization
   // Data relative to null tangent
   CATBoolean _TangentNull;
   double _ParamOfTangent;
   // Data relative to non curvilign parametrization
   CATBoolean _BadIsoParametrization;
   CATLONG32 _IndexArcWithBadIsoParam;
   // Data relative to tangent norm consistency
   CATBoolean _BadTangentNorm;
   CATLONG32 _IndexArcWithBadTangentNorm;

   // - III - Canonical curves
   // Data relative to degenerate canonical curve
   CATBoolean _MaxGapDiagnostic;

   // - IV - EdgeCurves
   CATBoolean _EdgeCurveKO;
   CATError ** _TabErr;
   CATLONG32 _NbErr;

   // - V - Generic
   CATBoolean _ErrorOnCurve, _WarningOnCurve;

   CATCrvLimits _Limits;
   CATCurve * _Curve;
   const CATPointOnEdgeCurve * _POECStart, * _POECEnd;

   // - Internal data 
   CATBoolean _CGMOutput;
   CATCGMOutput * _os;

   // - Advanced mode
   CATBoolean _AdvancedMode;
   // - OnlyErrors  mode
   CATBoolean _OnlyErrors;

   
   CATBoolean _SetCheckGap;
   
   CATSoftwareConfiguration * _Config;
};

#endif
