//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2017
//=============================================================================
// Methods to create civil curve evaluator
//=============================================================================
// 23/02/17 F1Z : Creation
// 30/07/18 KJD : new API CATCreateCatenaryEvaluator (2D evaluator for the Catenaries)
// 26/07/19 F4E : CATCreateClothoideCurveEvaluator() :
//                propagation of the add in CATClothoideEvaluator of a new input parameter
// 17/04/20 F4E : Migration CAT2DCurveEvaluator -> CATCivilCurveEvaluator (except for catenary and parabola2)
// 29/05/20 F4E : Propagate change in CATPGMCreateCivilCurveEvaluator API
// DD/MM/YY
//=============================================================================

#ifndef CATCreateCivilCurveEvaluator_H
#define CATCreateCivilCurveEvaluator_H

// ExportedBy
#include "GeoAdvCurves.h"

// Special API
#include "CATSysErrorDef.h"
#include "CATBoolean.h"

// GMModelInterfaces
#include "CATCivilCurveDef.h"
class CATCivilCurveParam;
class CAT2DCurveEvaluator;
class CATCivilCurveEvaluator;

class CATTolerance;
class CATSoftwareConfiguration;

class CATMathPoint;
class CATMathPoint2D;
class CATMathVector;
class CATMathVector2D;
class CATMathPlane;
class CATMathInterval;

// Temp
#include "CATCivilCurveArchiTEMP.h"

#ifndef NULL
#define NULL 0
#endif

// --------------------------------------------------------------------------------------------------------------------------------
// Line - Params
// --------------------------------------------------------------------------------------------------------------------------------
ExportedByGeoAdvCurves HRESULT CATCreateCivilCurveEvaluator( const CATTolerance               & iTolerance        ,
                                                                   CATSoftwareConfiguration   * iConfig           ,
                                                             const CATMathPoint2D             & iPt               ,
                                                             const CATMathVector2D            & iDir              ,
                                                             const CATMathVector2D            & iDirOrtho         ,
                                                             const CATCivilCurveType            iCurveType        ,
                                                                   CATCivilCurveEvaluator    *& oCivilEvaluator   ,
                                                             const double                     * iA2        = NULL ,
                                                             const double                     * iL         = NULL ,
                                                             const double                     * iR         = NULL ,
                                                             const double                     * iAngle     = NULL ,
                                                             const double                     * iShifting  = NULL ,
                                                             const CATBoolean                   iAccurate  = FALSE);

// --------------------------------------------------------------------------------------------------------------------------------
// Line - Params (input LENGTH & RADIUS)
// --------------------------------------------------------------------------------------------------------------------------------
ExportedByGeoAdvCurves HRESULT CATCreateCivilCurveEvaluator(const CATTolerance               & iTolerance ,
                                                                  CATSoftwareConfiguration *   iConfig    ,
                                                            const CATMathPoint2D             & iPt        ,
                                                            const CATMathVector2D            & iDir       ,
                                                            const CATMathVector2D            & iDirOrtho  ,
                                                            const double                       iL         ,
                                                            const double                       iR         ,
                                                            const CATCivilCurveType            iCurveType ,
                                                                  CATCivilCurveEvaluator    *& oCivilEvaluator,
                                                            const CATBoolean                   iAccurate = FALSE);

// --------------------------------------------------------------------------------------------------------------------------------
// Line - Circle
// --------------------------------------------------------------------------------------------------------------------------------
ExportedByGeoAdvCurves HRESULT CATCreateCivilCurveEvaluator (const CATTolerance               & iTolerance   ,
                                                                   CATSoftwareConfiguration *   iConfig      ,
                                                             const CATMathPoint2D             & iLineOrigin  ,
                                                             const CATMathVector2D            & iLineDir     ,
                                                             const CATMathPoint2D             & iCircleCenter,
                                                                   double                       iCircleRadius,
                                                             const CATCivilCurveType            iCurveType   ,
                                                                   CATMathPoint2D             & oCharactPt   ,
                                                                   double                     & oL           ,
                                                                   double                     & oA           ,
                                                                   CATCivilCurveEvaluator    *& oCivilEvaluator,
                                                             const CATBoolean                   iAccurate = FALSE);

// --------------------------------------------------------------------------------------
// Circle - Params
// --------------------------------------------------------------------------------------
ExportedByGeoAdvCurves HRESULT CATCreateCivilCurveEvaluator(const CATTolerance                          & iTolerance,
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
// Circle - Params (end with a line ==> R2 = infinite)
// --------------------------------------------------------------------------------------
ExportedByGeoAdvCurves HRESULT CATCreateCivilCurveEvaluator(const CATTolerance                    & iTolerance,
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
ExportedByGeoAdvCurves HRESULT CATCreateCivilCurveEvaluator(const CATTolerance                          & iTolerance,
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
ExportedByGeoAdvCurves HRESULT CATCreateCivilCurveEvaluator(const CATTolerance              & iTolerance,
                                                                  CATSoftwareConfiguration *  iConfig,
                                                            const CATCivilCurveEvaluator   *  iCivilEvaluator,
                                                            const CATCivilCurveType           iCurveType,
                                                            const CATCivilCurveParam        & iParam1,
                                                                  CATCivilCurveEvaluator   *& oCivilEvaluator);

// --------------------------------------------------------------------------------------------------------------------------------
// Circle - Circle (with init)
// --------------------------------------------------------------------------------------------------------------------------------
ExportedByGeoAdvCurves HRESULT CATCreateCivilCurveEvaluator (const CATTolerance                    & iTolerance          ,
                                                                   CATSoftwareConfiguration       *  iConfig             ,
                                                             const CATMathPoint2D                  & iCircleCenter1      ,
                                                             const double                            iCircleRadius1      ,
                                                             const CATCivilInput_ClockOrientation    iCircleOrientation1 ,
                                                             const CATMathPoint2D                  & iCircleCenter2      ,
                                                             const double                            iCircleRadius2      ,
                                                             const CATCivilCurveType                 iCurveType          ,
                                                             const CATCivilCurveEvaluator         *  iInitEvaluator      ,
                                                                   CATMathPoint2D                  & oCharactPt          ,
                                                                   CATMathInterval                 & oParamInterval      ,
                                                                   double                          & oA                  ,
                                                                   CATCivilCurveEvaluator         *& oCivilEvaluator     ,
                                                             const CATBoolean                        iAccurate = FALSE   );

// --------------------------------------------------------------------------------------------------------------------------------
// Circle - Circle (no init)
//  DEPRECATED - please use the "with init" version
// --------------------------------------------------------------------------------------------------------------------------------
ExportedByGeoAdvCurves HRESULT CATCreateCivilCurveEvaluator (const CATTolerance                           & iTolerance          ,
                                                                   CATSoftwareConfiguration             *   iConfig             ,
                                                             const CATMathPoint2D                         & iCircleCenter1      ,
                                                             const double                                   iCircleRadius1      ,
                                                             const CATCivilInput_ClockOrientation           iCircleOrientation1 ,
                                                             const CATMathPoint2D                         & iCircleCenter2      ,
                                                             const double                                   iCircleRadius2      ,
                                                             const CATCivilCurveType                        iCurveType          ,
                                                                   CATMathPoint2D                         & oCharactPt          ,
                                                                   CATMathInterval                        & oParamInterval      ,
                                                                   double                                 & oA                  ,
                                                                   CATCivilCurveEvaluator                *& oCivilEvaluator     ,
                                                             const CATBoolean                               iAccurate = FALSE   );

// --------------------------------------------------------------------------------------------------------------------------------
// Circle - Circle (fixed length)
//   iLength is the length between the two circles
//  DEPRECATED - please use the "circle + params" version with LENGTH and RADIUS
// --------------------------------------------------------------------------------------------------------------------------------
ExportedByGeoAdvCurves HRESULT CATCreateCivilCurveEvaluator( const CATTolerance                                   & iTolerance          ,
                                                                   CATSoftwareConfiguration                       * iConfig             ,
                                                             const CATMathPoint2D                                 & iCircleCenter1      ,
                                                             const double                                           iCircleRadius1      ,
                                                             const CATCivilInput_ClockOrientation                   iCircleOrientation1 ,
                                                             const CATMathPoint2D                                 & iStartPointOnCircle1,
                                                             const double                                           iCircleRadius2      ,
                                                             const CATCivilCurve_CircleCircleTransition             iTransitionType     ,
                                                             const double                                           iLength             ,
                                                             const CATCivilCurveType                                iCurveType          ,
                                                                   CATMathPoint2D                                 & oCharactPt          ,
                                                                   CATMathInterval                                & oParamInterval      ,
                                                                   double                                         & oA                  ,
                                                                   CATCivilCurveEvaluator                        *& oCivilEvaluator     ,
                                                             const CATBoolean                                       iAccurate = FALSE   );

#ifdef Q48_Civil_Keep_FixedParameterCSC
ExportedByGeoAdvCurves HRESULT CATCreateCivilCurveEvaluator( const CATTolerance                                   & iTolerance          ,
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
* @param oCharactPt
* The curve point at 0. It is a characteristic point (inflexion, summit, ...) Useful to retrieve if the curve is reduced to a point.
* @param oL
* The curvilinear absica at curve extremity
* @param oA
* The scale factor of the curve.
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
ExportedByGeoAdvCurves HRESULT CATCreateCivilCurveEvaluator(const CATTolerance             & iTolerance          ,
                                                                  CATSoftwareConfiguration * iConfig             ,
                                                            const CATMathPoint2D           & iStartPoint         ,
                                                            const CATMathVector2D          & iStartTangent       ,
                                                            const CATMathPoint2D           & iEndPoint           ,
                                                            const CATCivilCurveType          iCurveType          ,
                                                                  CATMathPoint2D           & oCharactPt          ,
                                                                  double                   & oL                  ,
                                                                  double                   & oA                  ,
                                                                  CATCivilCurveEvaluator  *& oCivilEvaluator     ,
                                                            const CATBoolean                 iAccurate = FALSE   );
#endif // Q48_Civil_KeepOldCreate_PtPtDir

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
* @param iCurveType
* The type of civil curve.
* @param oCivilEvaluator
* The 2D curve evaluator of the civil curve and its related data
* The memory has to be handle by the caller, no delete are performed in this method.
* @param iAccurate (only for parabola f degree 3, default FALSE)
* If TRUE, the returned curve evaluator represents a curve with the exact provided length and final radius.
* <br> If FALSE, the returned curve evaluator might represent an approximation of the exact curve.
* <br> The FALSE mode is based on the civil standard where efficient approximation are made. This only impact the parabola of degree 3 so far.
* @return
* <br>E_FAIL  If there was an operator issue during the computation.
* <br>S_FALSE If the operator did not succeed because of the inputs & option given
*             are not consistent (ex: the parabole2D civil curve can't be create from this constructor)
* <br>S_OK    If the operator has not encountered any issue.
*/
ExportedByGeoAdvCurves HRESULT CATCreateCivilCurveEvaluatorFromEnd(const CATTolerance               & iTolerance ,
                                                                         CATSoftwareConfiguration *   iConfig    ,
                                                                   const CATMathPoint2D             & iPtEnd     ,
                                                                   const CATMathVector2D            & iDir       ,
                                                                   const CATMathVector2D            & iDirOrtho  ,
                                                                   const double                       iLength    ,
                                                                   const double                       iRadius    ,
                                                                   const CATCivilCurveType            iCurveType ,
                                                                         CATCivilCurveEvaluator    *& oEvaluator ,
                                                                   const CATBoolean                   iAccurate = FALSE);

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
ExportedByGeoAdvCurves HRESULT CATCreateCivilCurveEvaluator(const CATTolerance           & iTolerance ,
                                                              CATSoftwareConfiguration   * iConfig    ,
                                                        const CATMathPoint2D             & iApex      ,
                                                        const CATMathVector2D            & iDir       ,
                                                        const double                       iFocalDist ,
                                                              CAT2DCurveEvaluator      * & oEvaluator );

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
ExportedByGeoAdvCurves HRESULT CATCreateCivilCurveEvaluator(const CATTolerance               & iTolerance ,
                                                                  CATSoftwareConfiguration *   iConfig    ,
                                                            const CATMathPoint               & iStartPoint,
                                                            const CATMathPoint               & iEndPoint  ,
                                                            const double                       iLength    ,
                                                            const CATMathVector              & iAxis      ,
                                                                  CATMathPlane               & oPlane     ,
                                                                  CAT2DCurveEvaluator      * & oEvaluator );




#endif

