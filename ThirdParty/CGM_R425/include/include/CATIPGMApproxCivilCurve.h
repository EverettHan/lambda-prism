#ifndef CATIPGMApproxCivilCurve_h_
#define CATIPGMApproxCivilCurve_h_

// COPYRIGHT DASSAULT SYSTEMES 2017

// Bass class
#include "CATIPGMGeoOperator.h"

// ExportedBy
#include "CATGMModelInterfaces.h"

// Civil
#include "CATCivilCurveDef.h"
#include "CATCivilCurveEvaluator.h"

class CAT2DCurveEvaluator;
class CATCivilCurveParam;

class CATCurve;
class CATGeoFactory;
class CATMathPoint2D;
class CATMathVector2D;
class CATSoftwareConfiguration;
class CATSurface;
class CATTolerance;
class CATMathPoint;
class CATMathVector;
class CATMathPlane;
class CATMathInterval;

// Temp
#include "CATCivilCurveArchiTEMP.h"

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMApproxCivilCurve;

// ============================================================================================================================= //
//                                                           OPERATOR                                                            //
// ============================================================================================================================= //
class ExportedByCATGMModelInterfaces CATIPGMApproxCivilCurve: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMApproxCivilCurve();

  //-----------------------------------------------------------------------------
  // Output Interface (Get)
  //-----------------------------------------------------------------------------
  /**
   * @return
   * <br>E_FAIL  If there was an operator issue during the computation.
   * <br>S_FALSE If the operator did not succeed because of the inputs & option given
   *             are not consistent (ex: the evaluator is not a civil curve).
   * <br>S_OK    If the operator has not encountered any issue.
   */
  virtual HRESULT GetRunStatus() = 0;

  /**
    * @return
    * TRUE If the solution is a point, FALSE if it is a curve.
    */
  virtual HRESULT IsAPoint(CATBoolean &iIsAPoint) const = 0;

  /**
   *  Retrieve the point in UV space where the civil curve start.
   */
  virtual HRESULT GetPoint(CATMathPoint2D &oPoint) const = 0;

  /**
   * @param oCurve
   * The curve representing (can be exact or an approximation) of the civil curve.
   * <br>The object life of the object retrieved has to be handle by the caller.
   */
  virtual HRESULT GetCurve(CATCurve *&oCurve) const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMApproxCivilCurve(); // -> delete can't be called
};

// ============================================================================================================================= //
//                                                        CREATE OPERATOR                                                        //
// ============================================================================================================================= //
/**
* Create an operator which computes approximation of a civil curve defined by a 2D curve evaluator inside its current limits.
* @param iCivilCurveEvalutor
* The civil curve evaluator. A civil curve evaluator can be created from the methods contained in this file.
* @param iSurface
* The surface support of the civil curve.
*/
ExportedByCATGMModelInterfaces CATIPGMApproxCivilCurve *CATPGMCreateApproxCivilCurve(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATCivilCurveEvaluator *iCivilCurveEvaluator,
  CATSurface *iSurface);

/** **deprecated**
* Create an operator which computes approximation of a civil curve defined by a 2D curve evaluator inside its current limits.
* @param iCivilCurveEvalutor
* The civil curve evaluator. A civil curve evaluator can be created from the methods contained in this file.
* @param iSurface
* The surface support of the civil curve.
*/
ExportedByCATGMModelInterfaces CATIPGMApproxCivilCurve *CATPGMCreateApproxCivilCurve(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  const CAT2DCurveEvaluator *iCivilCurveEvaluator,
  CATSurface *iSurface);

// ============================================================================================================================= //
//                                                       CREATE CIVIL CURVE                                                      //
// ============================================================================================================================= //

// --------------------------------------------------------------------------------------------------------------------------------
// Line - Params
// --------------------------------------------------------------------------------------------------------------------------------
/** 
* Create a 2D curve evaluator which eval the required civil curve defined through two parameters at least.
* <br> If more than two parameters are given, the operator checks the consistency of the result with them.
* @param iPt
* The point where the curve starts
* @param iDir
* The tangent where the curve starts
* @param iDirOrtho
* The orthogonal direction of iDir. It represents the direction of the curve center of curvature.
* @param oCivilEvaluator
* The 2D curve evaluator of the civil curve and its related data
* The memory has to be handle by the caller, no delete are performed in this method.
* @param iCurveType
* The type of civil curve.
* @param iA2
* The parameter a²
* <br> It belongs in [0, +Infinite[
* @param iRadius
* The radius at the curve end extremity.
* <br> It belongs in ]0, +Infinite[
* @param iLength
* The length of the curve
* <br> It belongs in[0, +Infinite[
* @param iAngle
* The final angle of the curve
* <br> It is the angle between the curve end extremity normal and the orthogonal direction.
* <br> It belongs in [0, +Infinite[
* @param iShifting
* The shifting of the curve.
* <br>It represents the min distance between the circle of the curve end extremity with the line defined by the point and direction given.
* <br> It belongs in [0, 0.1957*Length] and [0, sqrt(iA2*pi)/2.0[
* @param iAccurate (only for parabola f degree 3, default FALSE)
* If TRUE, the returned curve evaluator represents a curve with the exact provided length and final radius.
* <br> If FALSE, the returned curve evaluator might represent an approximation of the exact curve.
* <br> The FALSE mode is based on the civil standard where efficient approximation are made. This only impact the parabola of degree 3 so far.
* @return
* <br>E_NOTIMPL If not implemented for the asked curve type.
* <br>E_FAIL  If there was an operator issue during the computation.
* <br>S_FALSE If the operator did not succeed because of the inputs & option given
*             are not consistent.
* <br>S_OK    If the operator has not encountered any issue.
*/
ExportedByCATGMModelInterfaces HRESULT CATPGMCreateCivilCurveEvaluator( const CATTolerance               & iTolerance        ,
                                                                              CATSoftwareConfiguration   * iConfig           ,
                                                                        const CATMathPoint2D             & iPt               ,
                                                                        const CATMathVector2D            & iDir              ,
                                                                        const CATMathVector2D            & iDirOrtho         ,
                                                                        const CATCivilCurveType            iCurveType        ,
                                                                              CATCivilCurveEvaluator   * & oCivilEvaluator   ,
                                                                        const double                     * iA2        = NULL ,
                                                                        const double                     * iLength    = NULL ,
                                                                        const double                     * iRadius    = NULL ,
                                                                        const double                     * iAngle     = NULL ,
                                                                        const double                     * iShifting  = NULL ,
                                                                        const CATBoolean                   iAccurate  = FALSE);

// --------------------------------------------------------------------------------------------------------------------------------
// Line - Params (input LENGTH & RADIUS)
// --------------------------------------------------------------------------------------------------------------------------------
/** 
* Create a 2D curve evaluator which eval the civil curve defined by its final radius and whole length.
* @param iPt
* The point where the civil curve start
* @param iDir
* The tangent where the civil curve start
* @param iDirOrtho
* The orthogonal direction of iDir. It represents the direction of the civil curve center of curvature.
* @param iRadius
* The radius of the civil curve end extremity.
* <br> It belongs in ]0, +Infinite[
* @param iLength
* The length of the civil curve
* <br> It belongs in[0, +Infinite[
* <br> The final angle shouldn't be above 2PI. In civil context, the final angle equals L/2R.
* @param iAccurate
* If TRUE, the returned curve evaluator represents a curve with the exact provided length and final radius.
* <br> If FALSE, the returned curve evaluator might represent an approximation of the exact curve.
* <br> The FALSE mode is based on the civil standard where efficient approximation are made. This only impact the parabola of degree 3 so far.
* @param iCurveType
* The type of civil curve.
* @param oCivilEvaluator
* The 2D curve evaluator of the civil curve and its related data
* The memory has to be handle by the caller, no delete are performed in this method.
* @return
* <br>E_NOTIMPL If not implemented for the asked curve type.
* <br>E_FAIL  If there was an operator issue during the computation.
* <br>S_FALSE If the operator did not succeed because of the inputs & option given
*             are not consistent (ex: the parabole2D civil curve can't be create from this constructor)
* <br>S_OK    If the operator has not encountered any issue.
*/
ExportedByCATGMModelInterfaces HRESULT CATPGMCreateCivilCurveEvaluator(const CATTolerance              & iTolerance ,
                                                                             CATSoftwareConfiguration *  iConfig    ,
                                                                       const CATMathPoint2D            & iPt        ,
                                                                       const CATMathVector2D           & iDir       ,
                                                                       const CATMathVector2D           & iDirOrtho  ,
                                                                       const double                      iLength    ,
                                                                       const double                      iRadius    ,
                                                                       const CATCivilCurveType           iCurveType ,
                                                                       const CATBoolean                  iAccurate  ,
                                                                             CATCivilCurveEvaluator   *& oCivilEvaluator );


// --------------------------------------------------------------------------------------------------------------------------------
// Line - Circle
// --------------------------------------------------------------------------------------------------------------------------------
/** Line-Circle Evaluator
* Create a 2D curve evaluator which eval the civil curve defined in between a line and a circle in 2D (the surface UV-Space).
* @param iLineOrigin
* A point on the line.
* @param iLineDir
* The direction of the line. The direction determines the direction of the civil curve.
* @param iCircleCenter
* The center of the circle.
* @param iCircleRadius
* The radius of the circle.
* @param iCurveType
* The type of civil curve.
* @param iAccurate (only for parabola of degree 3 so far)
* If TRUE, the returned curve evaluator represents a curve with the exact provided length and final radius.
* <br> If FALSE, the returned curve evaluator might represent an approximation of the exact curve.
* <br> The FALSE mode is based on the civil standard where efficient approximation are made. This only impact the parabola of degree 3 so far.
* @param oCharactPt
* The curve point at 0. It is a characteristic point (inflexion, summit, ...) Useful to retrieve if the curve is reduced to a point.
* @param oLength
* The length of the curve created.
* @param oA 
* The scaling coefficient of the created curve.
* @param oCivilEvaluator
* The 2D curve evaluator of the civil curve and its related data
* The memory has to be handle by the caller, no delete are performed in this method.
* @return
* <br>E_NOTIMPL If not implemented for the asked curve type.
* <br>E_FAIL  If there was an operator issue during the computation.
* <br>S_FALSE If the operator did not succeed because of the inputs & option given
*             are not consistent.
* <br>S_OK    If the operator has not encountered any issue.
*/
ExportedByCATGMModelInterfaces HRESULT CATPGMCreateCivilCurveEvaluator (const CATTolerance              & iTolerance   ,
                                                                              CATSoftwareConfiguration *  iConfig      ,
                                                                        const CATMathPoint2D            & iLineOrigin  ,
                                                                        const CATMathVector2D           & iLineDir     ,
                                                                        const CATMathPoint2D            & iCircleCenter,
                                                                        const double                      iCircleRadius,
                                                                        const CATCivilCurveType           iCurveType   ,
                                                                        const CATBoolean                  iAccurate    ,
                                                                              CATMathPoint2D            & oCharactPt   ,
                                                                              double                    & oLength      ,
                                                                              double                    & oA           ,
                                                                              CATCivilCurveEvaluator   *& oCivilEvaluator   );


// --------------------------------------------------------------------------------------
// Circle - Params
// --------------------------------------------------------------------------------------
ExportedByCATGMModelInterfaces HRESULT CATPGMCreateCivilCurveEvaluator(const CATTolerance                          & iTolerance,
                                                                             CATSoftwareConfiguration             *  iConfig,
                                                                       const CATMathPoint2D                        & iCircleCenter,
                                                                       const double                                  iCircleRadius,
                                                                       const CATCivilInput_ClockOrientation          iCircleOrientation,
                                                                       const CATMathPoint2D                        & iCircleStartPoint,
                                                                       const CATCivilCurveType                       iCurveType,
                                                                       const CATCivilCurveParam                    & iParam1,
                                                                       const CATCivilCurveParam                    & iParam2,
                                                                       const CATCivilCurve_CircleCircleTransition    iTransitionTypeCSC,
                                                                             CATCivilCurveEvaluator               *& oCivilEvaluator);

// --------------------------------------------------------------------------------------
// Circle - Params (end at a line ==> R2 is infinite)
// --------------------------------------------------------------------------------------
ExportedByCATGMModelInterfaces HRESULT CATPGMCreateCivilCurveEvaluator(const CATTolerance                    & iTolerance,
                                                                             CATSoftwareConfiguration       *  iConfig,
                                                                       const CATMathPoint2D                  & iCircleCenter,
                                                                       const double                            iCircleRadius,
                                                                       const CATCivilInput_ClockOrientation    iCircleOrientation,
                                                                       const CATMathPoint2D                  & iCircleStartPoint,
                                                                       const CATCivilCurveType                 iCurveType,
                                                                       const CATCivilCurveParam              & iParam1,
                                                                             CATCivilCurveEvaluator         *& oCivilEvaluator);

// --------------------------------------------------------------------------------------
// Sprial - Params
// --------------------------------------------------------------------------------------
ExportedByCATGMModelInterfaces HRESULT CATPGMCreateCivilCurveEvaluator(const CATTolerance                          & iTolerance,
                                                                             CATSoftwareConfiguration             *  iConfig,
                                                                       const CATCivilCurveEvaluator               *  iCivilEvaluator,
                                                                       const CATCivilCurveType                       iCurveType,
                                                                       const CATCivilCurveParam                    & iParam1,
                                                                       const CATCivilCurveParam                    & iParam2,
                                                                       const CATCivilCurve_CircleCircleTransition    iTransitionTypeCSC,
                                                                             CATCivilCurveEvaluator               *& oCivilEvaluator);

// --------------------------------------------------------------------------------------
// Sprial - Params (end with a line ==> R2 = infinite)
// --------------------------------------------------------------------------------------
ExportedByCATGMModelInterfaces HRESULT CATPGMCreateCivilCurveEvaluator(const CATTolerance              & iTolerance,
                                                                             CATSoftwareConfiguration *  iConfig,
                                                                       const CATCivilCurveEvaluator   *  iCivilEvaluator,
                                                                       const CATCivilCurveType           iCurveType,
                                                                       const CATCivilCurveParam        & iParam1,
                                                                             CATCivilCurveEvaluator   *& oCivilEvaluator);

// --------------------------------------------------------------------------------------------------------------------------------
// Circle - Circle (with init)
// --------------------------------------------------------------------------------------------------------------------------------
/**  Circle-Circle Evaluator
* Create a 2D curve evaluator which eval the civil curve defined in between two oriented circles in 2D (the surface UV-Space).
* We assume that the path goes from the first one to the second.
* @param iCircleCenter1
* The center of the first circle.
* @param iCircleRadius1
* The radius of the first circle.
* @param iCircleOrientation1
* The clockwise or anti-clockwise orientation of the first circle (direction of course).
* @param iCircleCenter2
* The center of the second circle.
* @param iCircleRadius2
* The radius of the second circle.
* @param iCurveType
* The type of civil curve.
* @param iAccurate (only for parabola of degree 3 so far)
* If TRUE, the returned curve evaluator represents a curve with the exact provided length and final radius.
* <br> If FALSE, the returned curve evaluator might represent an approximation of the exact curve.
* <br> The FALSE mode is based on the civil standard where efficient approximation are made. This only impact the parabola of degree 3 so far.
* @param oCharactPt
* The curve point at 0. It is a characteristic point (inflexion, summit, ...) Useful to retrieve if the curve is reduced to a point.
* @param oParamInterval
* The curvilinear abscissa interval of the curve parameter 
* @param oA
* The scale coefficient of the curve.
* @param oCivilEvaluator
* The 2D curve evaluator of the civil curve and its related data
* The memory has to be handle by the caller, no delete are performed in this method.
* @return
* <br>E_NOTIMPL If not implemented for the asked curve type.
* <br>E_FAIL  If there was an operator issue during the computation.
* <br>S_FALSE If the operator did not succeed because of the inputs & option given
*             are not consistent.
* <br>S_OK    If the operator has not encountered any issue.
*/
ExportedByCATGMModelInterfaces HRESULT CATPGMCreateCivilCurveEvaluator (const CATTolerance                           & iTolerance          ,
                                                                              CATSoftwareConfiguration             *   iConfig             ,
                                                                        const CATMathPoint2D                         & iCircleCenter1      ,
                                                                        const double                                   iCircleRadius1      ,
                                                                        const CATCivilInput_ClockOrientation           iCircleOrientation1 ,
                                                                        const CATMathPoint2D                         & iCircleCenter2      ,
                                                                        const double                                   iCircleRadius2      ,
                                                                        const CATCivilCurveType                        iCurveType          ,
                                                                        const CATCivilCurveEvaluator               *   iInitEvaluator      ,
                                                                        const CATBoolean                               iAccurate           ,
                                                                              CATMathPoint2D                         & oCharactPt          ,
                                                                              CATMathInterval                        & oParamInterval      ,
                                                                              double                                 & oA                  ,
                                                                              CATCivilCurveEvaluator               * & oCivilEvaluator     );

// --------------------------------------------------------------------------------------------------------------------------------
// Circle - Circle (no init)
//  DEPRECATED - please use the "with init" version
// --------------------------------------------------------------------------------------------------------------------------------
/**  Circle-Circle Evaluator (deprecated - please use the "with init" version)
* Create a 2D curve evaluator which eval the civil curve defined in between two oriented circles in 2D (the surface UV-Space).
* We assume that the path goes from the first one to the second.
* @param iCircleCenter1
* The center of the first circle.
* @param iCircleRadius1
* The radius of the first circle.
* @param iCircleOrientation1
* The clockwise or anti-clockwise orientation of the first circle (direction of course).
* @param iCircleCenter2
* The center of the second circle.
* @param iCircleRadius2
* The radius of the second circle.
* @param iCurveType
* The type of civil curve.
* @param iInitEvaluator
* The evaluator to use as an init (can be NULL)
* @param iAccurate (only for parabola of degree 3 so far)
* If TRUE, the returned curve evaluator represents a curve with the exact provided length and final radius.
* <br> If FALSE, the returned curve evaluator might represent an approximation of the exact curve.
* <br> The FALSE mode is based on the civil standard where efficient approximation are made. This only impact the parabola of degree 3 so far.
* @param oCharactPt
* The curve point at 0. It is a characteristic point (inflexion, summit, ...) Useful to retrieve if the curve is reduced to a point.
* @param oParamInterval
* The curvilinear abscissa interval of the curve parameter 
* @param oA
* The scale coefficient of the curve.
* @param oCivilEvaluator
* The 2D curve evaluator of the civil curve and its related data
* The memory has to be handle by the caller, no delete are performed in this method.
* @return
* <br>E_NOTIMPL If not implemented for the asked curve type.
* <br>E_FAIL  If there was an operator issue during the computation.
* <br>S_FALSE If the operator did not succeed because of the inputs & option given
*             are not consistent.
* <br>S_OK    If the operator has not encountered any issue.
*/
ExportedByCATGMModelInterfaces HRESULT CATPGMCreateCivilCurveEvaluator (const CATTolerance                    & iTolerance          ,
                                                                              CATSoftwareConfiguration       *  iConfig             ,
                                                                        const CATMathPoint2D                  & iCircleCenter1      ,
                                                                        const double                            iCircleRadius1      ,
                                                                        const CATCivilInput_ClockOrientation    iCircleOrientation1 ,
                                                                        const CATMathPoint2D                  & iCircleCenter2      ,
                                                                        const double                            iCircleRadius2      ,
                                                                        const CATCivilCurveType                 iCurveType          ,
                                                                        const CATBoolean                        iAccurate           ,
                                                                              CATMathPoint2D                  & oCharactPt          ,
                                                                              CATMathInterval                 & oParamInterval      ,
                                                                              double                          & oA                  ,
                                                                              CATCivilCurveEvaluator         *& oCivilEvaluator     );

// --------------------------------------------------------------------------------------------------------------------------------
// Circle - Circle (fixed length)
//   iLength is the length between the two circles
//  DEPRECATED - please use the "circle + params" version with LENGTH and RADIUS
// --------------------------------------------------------------------------------------------------------------------------------
/**  Circle-Circle Evaluator with unknown second circle position
* Create a 2D curve evaluator which eval the curve defined in between two oriented circles in 2D (the surface UV-Space).
* We assume that the path goes from the first one to the second.
* The second circle radius only is known and the curve length is constrained.
* We assume that the path goes from the first one to the second.
* @param iCircleCenter1
* The center of the first circle.
* @param iCircleRadius1
* The radius of the first circle.
* @param iCircleOrientation1
* The clockwise or anti-clockwise orientation of the first circle (direction of course).
* @param iStartPointOnCircle1
* The point on first circle where the curve starts
* @param iCircleRadius2
* The radius of the second circle.
* @param iTransitionType
* The transition type in betwen the two circles (OVE or REVERSE)
* @param iLength
* The length of the curve imposed in between the two circles.
* @param iCurveType
* The type of civil curve.
* @param iAccurate (only for parabola of degree 3 so far)
* If TRUE, the returned curve evaluator represents a curve with the exact provided length and final radius.
* <br> If FALSE, the returned curve evaluator might represent an approximation of the exact curve.
* <br> The FALSE mode is based on the civil standard where efficient approximation are made. This only impact the parabola of degree 3 so far.
* @param oCharactPt
* The curve point at 0. It is a characteristic point (inflexion, summit, ...) Useful to retrieve if the curve is reduced to a point.
* @param oParamInterval
* The curvilinear abscissa interval of the curve parameter 
* @param oA
* The scale coefficient of the curve.
* @param oCivilEvaluator
* The 2D curve evaluator of the civil curve and its related data
* The memory has to be handle by the caller, no delete are performed in this method.
* @return
* <br>E_NOTIMPL If not implemented for the asked curve type.
* <br>E_FAIL  If there was an operator issue during the computation.
* <br>S_FALSE If the operator did not succeed because of the inputs & option given
*             are not consistent.
* <br>S_OK    If the operator has not encountered any issue.
*/
ExportedByCATGMModelInterfaces HRESULT CATPGMCreateCivilCurveEvaluator( const CATTolerance                          & iTolerance          ,
                                                                              CATSoftwareConfiguration             *  iConfig             ,
                                                                        const CATMathPoint2D                        & iCircleCenter1      ,
                                                                        const double                                  iCircleRadius1      ,
                                                                        const CATCivilInput_ClockOrientation          iCircleOrientation1 ,
                                                                        const CATMathPoint2D                        & iStartPointOnCircle1,
                                                                        const double                                  iCircleRadius2      ,
                                                                        const CATCivilCurve_CircleCircleTransition    iTransitionType     ,
                                                                        const double                                  iLength             ,
                                                                        const CATCivilCurveType                       iCurveType          ,
                                                                        const CATBoolean                              iAccurate           ,
                                                                              CATMathPoint2D                        & oCharactPt          ,
                                                                              CATMathInterval                       & oParamInterval      ,
                                                                              double                                & oA                  ,
                                                                              CATCivilCurveEvaluator               *& oCivilEvaluator     );

#ifdef Q48_Civil_Keep_FixedParameterCSC
/**  Circle-Circle Evaluator with unknown second circle position (generalisation of the fixed-length API above)
* Create a 2D curve evaluator which eval the curve defined in between two oriented circles in 2D (the surface UV-Space).
* We assume that the path goes from the first one to the second.
* The second circle radius only is known and the curve length / flatness is constrained.
* @param iCircleCenter1
* The center of the first circle.
* @param iCircleRadius1
* The radius of the first circle.
* @param iCircleOrientation1
* The clockwise or anti-clockwise orientation of the first circle (direction of course).
* @param iStartPointOnCircle1
* The point on first circle where the curve starts
* @param iCircleRadius2
* The radius of the second circle.
* @param iTransitionType
* The transition type in betwen the two circles (OVE or REVERSE)
* @param iCivilParameterType
* The civil curve parameter (currently only FLATNESS is accepted)
* @param iCivilParameterValue
* The civil curve parameter value
* @param iCurveType
* The type of civil curve.
* @param oCharactPt
* The curve point at 0. It is a characteristic point (inflexion, summit, ...) Useful to retrieve if the curve is reduced to a point.
* @param oParamInterval
* The curvilinear abscissa interval of the curve parameter 
* @param oA
* The scale coefficient of the curve.
* @param oCivilEvaluator
* The 2D curve evaluator of the civil curve and its related data
* The memory has to be handle by the caller, no delete are performed in this method.
* @param iAccurate (only for parabola of degree 3 so far)
* If TRUE, the returned curve evaluator represents a curve with the exact provided length and final radius.
* <br> If FALSE, the returned curve evaluator might represent an approximation of the exact curve.
* <br> The FALSE mode is based on the civil standard where efficient approximation are made. This only impact the parabola of degree 3 so far.
* @return
* <br>E_NOTIMPL If not implemented for the asked curve type.
* <br>E_FAIL  If there was an operator issue during the computation.
* <br>S_FALSE If the operator did not succeed because of the inputs & option given
*             are not consistent.
* <br>S_OK    If the operator has not encountered any issue.
*/
ExportedByCATGMModelInterfaces HRESULT CATPGMCreateCivilCurveEvaluator(const CATTolerance                                   & iTolerance          ,
                                                                             CATSoftwareConfiguration                       * iConfig             ,
                                                                       const CATMathPoint2D                                 & iCircleCenter1      ,
                                                                       const double                                           iCircleRadius1      ,
                                                                       const CATCivilInput_ClockOrientation                   iCircleOrientation1 ,
                                                                       const CATMathPoint2D                                 & iStartPointOnCircle1,
                                                                       const double                                           iCircleRadius2      ,
                                                                       const CATCivilCurve_CircleCircleTransition             iTransitionType     ,
                                                                       const CATCivilCurveDef::ParamType                      iCivilParameterType ,
                                                                       const double                                           iCivilParameterValue,
                                                                       const CATCivilCurveType                                iCurveType          ,
                                                                             CATMathPoint2D                                 & oCharactPt          ,
                                                                             CATMathInterval                                & oParamInterval      ,
                                                                             double                                         & oA                  ,
                                                                             CATCivilCurveEvaluator                        *& oCivilEvaluator     ,
                                                                       const CATBoolean                                       iAccurate = FALSE   );
#endif // Q48_Civil_Keep_FixedParameterCSC

#ifdef Q48_Civil_KeepOldCreate_PtPtDir
/** Pt-Dir-Pt Evaluator
* Create a 2D curve evaluator which eval a civil curve defined by the two extremities points and initial tangent.
* @param iStartPoint
* The start extremity of the curve.
* @param iStartTangent
* The start extremity tangent of the curve.
* @param iEndPoint
* The end extremity of the curve.
* @param iCurveType
* The type of civil curve.
* @param iAccurate (only for parabola of degree 3 so far)
* If TRUE, the returned curve evaluator represents a curve with the exact provided length and final radius.
* <br> If FALSE, the returned curve evaluator might represent an approximation of the exact curve.
* <br> The FALSE mode is based on the civil standard where efficient approximation are made. This only impact the parabola of degree 3 so far.
* @param oCharactPt
* The curve point at 0. It is a characteristic point (inflexion, summit, ...) Useful to retrieve if the curve is reduced to a point.
* @param oLength
* The length of the curve created.
* @param oA
* The scale factor of the curve.
* @param oCivilEvaluator
* The 2D curve evaluator of the civil curve and its related data
* The memory has to be handle by the caller, no delete are performed in this method.
* @return
* <br>E_NOTIMPL If not implemented for the asked curve type.
* <br>E_FAIL  If there was an operator issue during the computation.
* <br>S_FALSE If the operator did not succeed because of the inputs & option given
*             are not consistent.
* <br>S_OK    If the operator has not encountered any issue.
*/
ExportedByCATGMModelInterfaces HRESULT CATPGMCreateCivilCurveEvaluator(const CATTolerance             & iTolerance          ,
                                                                             CATSoftwareConfiguration * iConfig             ,
                                                                       const CATMathPoint2D           & iStartPoint         ,
                                                                       const CATMathVector2D          & iStartTangent       ,
                                                                       const CATMathPoint2D           & iEndPoint           ,
                                                                       const CATCivilCurveType          iCurveType          ,
                                                                       const CATBoolean                 iAccurate           ,
                                                                             CATMathPoint2D           & oCharactPt          ,
                                                                             double                   & oLength             ,
                                                                             double                   & oA                  ,
                                                                             CATCivilCurveEvaluator * & oCivilEvaluator     );
#endif //Q48_Civil_KeepOldCreate_PtPtDir

/** 
* Create a 2D curve evaluator which eval the civil curve defined by its final radius and whole length.
* @param iPt
* The point where the civil curve end
* @param iDir
* The tangent where the civil curve end
* @param iDirOrtho
* The orthogonal direction of iDir. It represents the direction of the civil curve center of curvature.
* @param iRadius
* The radius of the civil curve end extremity.
* <br> It belongs in ]0, +Infinite[
* @param iLength
* The length of the civil curve
* <br> It belongs in[0, +Infinite[
* <br> The final angle shouldn't be above 2PI. In civil context, the final angle equals L/2R.
* @param iAccurate
* If TRUE, the returned curve evaluator represents a curve with the exact provided length and final radius.
* <br> If FALSE, the returned curve evaluator might represent an approximation of the exact curve.
* <br> The FALSE mode is based on the civil standard where efficient approximation are made. This only impact the parabola of degree 3 so far.
* @param iCurveType
* The type of civil curve.
* @param oCivilEvaluator
* The 2D curve evaluator of the civil curve and its related data
* The memory has to be handle by the caller, no delete are performed in this method.
* @return
* <br>E_FAIL  If there was an operator issue during the computation.
* <br>S_FALSE If the operator did not succeed because of the inputs & option given
*             are not consistent (ex: the parabole2D civil curve can't be create from this constructor)
* <br>S_OK    If the operator has not encountered any issue.
*/
ExportedByCATGMModelInterfaces HRESULT CATPGMCreateCivilCurveEvaluatorFromEnd(
  const CATTolerance &iTolerance,
  CATSoftwareConfiguration *iConfig,
  const CATMathPoint2D &iPt,
  const CATMathVector2D &iDir,
  const CATMathVector2D &iDirOrtho,
  const double iLength,
  const double iRadius,
  const CATCivilCurveType iCurveType,
  const CATBoolean iAccurate,
  CATCivilCurveEvaluator *&oCivilEvaluator);

/**
* Create a 2D Curve evaluator representing a PARABOLA OF DEGREE 2 defined by the provided parameters.
* @param iApex
* The parabola apex
* @param iDir
* The parabola axis (tangent to the apex)
* @param iFocalDist
* The parabola focal distance. It is equals to twice the distance between the apex and its focus.
* @param oEvaluator
* The 2D curve evaluator of the parabola.
* @return
* <br>E_FAIL  If there was an operator issue during the computation.
* <br>S_FALSE If the operator did not succeed because of the inputs & option given
*             are not consistent.
* <br>S_OK    If the operator has not encountered any issue.
*/
ExportedByCATGMModelInterfaces HRESULT CATPGMCreateCivilCurveEvaluator(
  const CATTolerance &iTolerance,
  CATSoftwareConfiguration *iConfig,
  const CATMathPoint2D &iApex,
  const CATMathVector2D &iDir,
  const double iFocalDist,
  CAT2DCurveEvaluator *&oEvaluator);

/**
* Create a 2D Curve evaluator in the plane on which is lying the CATENARY defined by the provided parameters.
* A catenary is the curve that an idealized hanging chain assumes under its own weight when supported only at its ends.
* @param iStartPoint
* The first extremity where the chain is hanged.
* @param iEndPoint
* The second extremity where the chain is hanged.
* @param iLength 
* The length of the chain.
* @param iAxis
* The axis of the catenary. In physics, it is equal to the direction of the gravity
* @param oPlane
* The plane on which is lying the catenary.
* @param oEvaluator
* The 2D curve evaluator in the plane oPlane  of the catenary.
* @return
* <br>E_FAIL  If there was an operator issue during the computation.
* <br>S_FALSE If the operator did not succeed because of the inputs & option given
*             are not consistent.
* <br>S_OK    If the operator has not encountered any issue.
*/
ExportedByCATGMModelInterfaces HRESULT CATPGMCreateCivilCurveEvaluator(
  const CATTolerance &iTolerance,
  CATSoftwareConfiguration *iConfig,
  const CATMathPoint &iStartPoint,
  const CATMathPoint &iEndPoint,
  const double iLength,
  const CATMathVector &iAxis,
  CATMathPlane &oPlane,
  CAT2DCurveEvaluator *&oEvaluator);

#endif /* CATIPGMApproxCivilCurve_h_ */
