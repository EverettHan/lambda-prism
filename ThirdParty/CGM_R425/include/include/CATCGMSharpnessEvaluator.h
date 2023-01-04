/* -*-c++-*- */
#ifndef CATCGMSharpnessEvaluator_h
#define CATCGMSharpnessEvaluator_h
//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2001
//-----------------------------------------------------------------------------
// On isole l'evaluation geometrique de la vivicite
//-----------------------------------------------------------------------------

#include "CATBoolean.h"
#include "CATMathConstant.h"
#include "CATTopDefine.h"
#include "CATSoftwareConfiguration.h"
#include "GeoTopo.h"
#include "CATCrvParam.h"
#include "CATMathInline.h"
#include "CATCGMSharpnessEvaluation.h"

class CATPointOnEdgeCurve;
class CATEdgeCurve;
class CATPCurve;
class CATSurface;
class CATCrvParam;
 



/**
 * Generic sharpness evaluator about GeometricObjects/PublicInterfaces/CATGeoDef.h
 * <ul>
 * <li>continuity : CATSharp/CATSmooth
 * <li>convexity  : CATUnknownConvexity and (if Sharp) CATConvex/CATConcave/CATRazorBlade/ 
 * </ul>
 */ 
class  ExportedByGeoTopo CATCGMSharpnessEvaluator
{
public:

/**
 * CreateSharpnessEvaluator .
 *     create appropriate evaluator.
 * @param iType
 *    Kind of evaluator which implements the calculus.
 * @param iSoftConfig
 *    For smart management of evolution made by a level comparison.
 * @param iMinSharpAngle
 *    Angle for Sharp/Smooth continuity
 *    GMModelInterfaces/PublicInterfaces/CATTopDefine.h CATTopSharpAngle  0.0087266463 radian 
 * @param iPOECCrvParams[2]
 *    Delimitation of the EdgeCurve (equivalents to CrvLimits).
 * @param iEdgeCurveOrientation
 *    Orientation of EdgeCurve needed for convexity calculus.
 * @param ipEdgeCurve
 *    The EdgeCurve containing .
 * @param ippPCurves[2]
 *    The two PCurve to be considered .
 * @param iFirstFaceIsLeft
 *    for convexity calculus : Orientation of matter (Shell orientation) .
 * @param iFaceMatterSides[2]
 *    for convexity calculus : Orientation of matter (Face's orientation ) .
 * @param iFaceOrientations[2]
 *    for convexity calculus : Orientation of matter (Surface orientation Face's ) .
 * @param ippSurfaces[2]
 *    Surface of PCurves (redondant) .
 * @param iComputeConvexity
 *    for convexity calculus : Determines if calculus is required .
 * @param iForceGeometricEvaluation
 *    Argument Dedicated to CatCGMSharpnessPrototype .
 */
  static CATCGMSharpnessEvaluator  *       CreateSharpnessEvaluator(CATCGMSharpnessEvaluation    iType,
                                                                   CATSoftwareConfiguration   * iSoftConfig,
                                                                   CATAngle                     iMinSharpAngle,
                                                                   CATPointOnEdgeCurve        * Poec[2],
                                                                   CATCrvParam                  iPOECCrvParams[2],
                                                                   CATOrientation               iEdgeCurveOrientation,
                                                                   CATEdgeCurve*                ipEdgeCurve,
                                                                   CATPCurve*                   ippPCurves[2],
                                                                   CATBoolean                   iFirstFaceIsLeft,
                                                                   CATSide                      iFaceMatterSides[2],
                                                                   CATOrientation               iFaceOrientations[2],
                                                                   CATSurface*                  ippSurfaces[2],
                                                                   CATBoolean                   iComputeConvexity,
                                                                   CATBoolean                   iForceGeometricEvaluation) ;

/**
 * Runs <tt>this</tt> operator.
 */
  virtual void Run() = 0;

  /**
 * Access to resulting sharpness.
 *     return 1 if Okay, return 0 if no result can be computed.
 */
  INLINE CATBoolean GetSharpness(CATTopSharpness& oSharpness);


    /** @nodoc  */
  virtual ~CATCGMSharpnessEvaluator();

protected :


  INLINE CATCGMSharpnessEvaluator(CATCGMSharpnessEvaluation    iType,
                                  CATSoftwareConfiguration   * iSoftConfig,
                                  CATAngle                     iMinSharpAngle,
                                  CATPointOnEdgeCurve        * Poec[2],
                                  CATCrvParam                  iPOECCrvParams[2],
                                  CATOrientation               iEdgeCurveOrientation,
                                  CATEdgeCurve*                ipEdgeCurve,
                                  CATPCurve*                   ippPCurves[2],
                                  CATBoolean                   iFirstFaceIsLeft,
                                  CATSide                      iFaceMatterSides[2],
                                  CATOrientation               iFaceOrientations[2],
                                  CATSurface*                  ippSurfaces[2],
                                  CATBoolean                   iComputeConvexity,
                                  CATBoolean                   iForceGeometricEvaluation) ;


  CATCGMSharpnessEvaluation    _Type;

  CATBoolean                   _HasRun;
  CATBoolean                   _HasResult;
  CATTopSharpness              _Result;

  CATSoftwareConfiguration   * _SoftConfig;
  CATAngle                     _MinSharpAngle;
  CATPointOnEdgeCurve        * _Poec[2];

  CATCrvParam                  _POECCrvParams[2];
  CATOrientation               _EdgeCurveOrientation;
  CATEdgeCurve*                _pEdgeCurve;
  CATPCurve*                   _ppPCurves[2];
  CATBoolean                   _FirstFaceIsLeft;
  CATSide                      _FaceMatterSides[2];
  CATOrientation               _FaceOrientations[2];
  CATSurface*                  _ppSurfaces[2];
  CATBoolean                   _ComputeConvexity;
  CATBoolean                   _ForceGeometricEvaluation;


};

INLINE CATCGMSharpnessEvaluator::CATCGMSharpnessEvaluator(CATCGMSharpnessEvaluation    iType,
                                                          CATSoftwareConfiguration   * iSoftConfig,
                                                          CATAngle                     iMinSharpAngle,
                                                          CATPointOnEdgeCurve        * Poec[2],
                                                          CATCrvParam                  iPOECCrvParams[2],
                                                          CATOrientation               iEdgeCurveOrientation,
                                                          CATEdgeCurve*                ipEdgeCurve,
                                                          CATPCurve*                   ippPCurves[2],
                                                          CATBoolean                   iFirstFaceIsLeft,
                                                          CATSide                      iFaceMatterSides[2],
                                                          CATOrientation               iFaceOrientations[2],
                                                          CATSurface*                  ippSurfaces[2],
                                                          CATBoolean                   iComputeConvexity,
                                                          CATBoolean                   iForceGeometricEvaluation) 
:_Type(iType)
,_HasRun(FALSE)
,_HasResult(FALSE)
,_SoftConfig(iSoftConfig)
,_MinSharpAngle(iMinSharpAngle)
,_EdgeCurveOrientation(iEdgeCurveOrientation)
,_pEdgeCurve(ipEdgeCurve)
,_FirstFaceIsLeft(iFirstFaceIsLeft)
,_ComputeConvexity(iComputeConvexity)
,_ForceGeometricEvaluation(iForceGeometricEvaluation)
{
  _Result._GeoContinuity = CATUnknownContinuity;
  _Result._Convexity     = CATUnknownConvexity;
  _Poec[0]      = Poec[0];
  _Poec[1]      = Poec[1];
  _POECCrvParams[0]      = iPOECCrvParams[0];
  _POECCrvParams[1]      = iPOECCrvParams[1];
  _ppPCurves[0]          = ippPCurves[0];
  _ppPCurves[1]          = ippPCurves[1];
  _FaceMatterSides[0]    = iFaceMatterSides[0];
  _FaceMatterSides[1]    = iFaceMatterSides[1];
  _FaceOrientations[0]   = iFaceOrientations[0];
  _FaceOrientations[1]   = iFaceOrientations[1];
  _ppSurfaces[0]         = ippSurfaces[0];
  _ppSurfaces[1]         = ippSurfaces[1];
}

 CATBoolean CATCGMSharpnessEvaluator::GetSharpness(CATTopSharpness& oSharpness)
 {
   if ( _HasRun && _HasResult ) { oSharpness = _Result; return TRUE; }
   return FALSE;
 }


#endif
