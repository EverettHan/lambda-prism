#ifndef CATIPGMComputeCivilTransitionCurves_h_
#define CATIPGMComputeCivilTransitionCurves_h_

// COPYRIGHT DASSAULT SYSTEMES 2018

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"
#include "CATCivilCurveDef.h"

class CATCivilCurveEvaluator;
class CAT2DCurveEvaluator;
class CATPGMCivilTransitionInfo;
class CATGeoFactory;
class CATMathCurve;
class CATMathPoint2D;
class CATMathVector2D;
class CATSoftwareConfiguration;

// Temp
#include "CATCivilCurveArchiTEMP.h"

//#ifdef Q48_Civil_KeepDeprecatedTSCST
//extern ExportedByCATGMModelInterfaces IID IID_CATIPGMComputeCivilTransitionCurves;
//
//// ============================================================================================================================= //
////                                                           OPERATOR                                                            //
//// ============================================================================================================================= //
//class ExportedByCATGMModelInterfaces CATIPGMComputeCivilTransitionCurves: public CATIPGMGeoOperator
//{
//public:
//  /**
//   * Constructor
//   */
//  CATIPGMComputeCivilTransitionCurves();
//
//  //-----------------------------------------------------------------------------
//  // Options Interface (Set)
//  //-----------------------------------------------------------------------------
//  virtual HRESULT Set(const CATCivilCurveType iCurveType) = 0;
//
//  //-----------------------------------------------------------------------------
//  // Output Interface (Get)
//  //-----------------------------------------------------------------------------
//  /**
//   * @return
//   * <br>E_FAIL  If there was an operator issue during the computation.
//   * <br>S_FALSE If the operator did not succeed because of the inputs & option given
//   *             are not consistent (ex: the evaluator is not a civil curve).
//   * <br>S_OK    If the operator has not encountered any issue.
//   */
//  virtual HRESULT GetRunStatus() const = 0;
//
//  /**
//   * Does the computed composition is self intersecting
//   */
//  virtual CATBoolean IsSelfIntersecting() const = 0;
//
//  /**
//  * Initializes the iterator for accessing the civil curve evaluator.
//  */
//  virtual void BeginCivilCurve() const = 0;
//
//  /**
//  * Sets the iterator to point at the next civil curve evaluator.
//  * @return
//  * TRUE if there is data,
//  * FALSE if the end of the data has been reached.
//  */
//  virtual CATBoolean NextCivilCurve() const = 0;
//
//  /**
//   * @param oCurveEvaluator
//   * The curve evaluator of the current civil curve.
//   * <br>The object life of the object retrieved has to be handle by the caller. Use delete.
//   */
//  virtual HRESULT GetCivilCurve(CATCivilCurveEvaluator *&oCurveEvaluator) const = 0;
//
//  /**
//   * @param oOrientation
//   * The orientation of this current civil curve parametrisation compared to the previous adjacent transition geometry.
//   * <br> TRUE means direct, FALSE indirect.
//   */
//  virtual HRESULT GetCivilCurveOrientation(CATBoolean &oOrientation) const = 0;
//
//  /**
//   * @param oStartPoint
//   * The common point between PreviousTransitionGeometry and the current civil curve.
//   * @param oEndPoint
//   * The common point between NextTransitionGeometry and the current civil curve.
//   */
//  virtual HRESULT GetCivilCurveExtremities(
//    CATMathPoint2D &oStartPoint,
//    CATMathPoint2D &oEndPoint) const = 0;
//
//  /**
//   * Does the end extremity of the current civil curve is confused with
//   * the next civil curve start extremity.
//   * @return
//   * TRUE if confused, FALSE otherwise.
//   */
//  virtual CATBoolean IsEndExtremityConfusedWithNext() const = 0;
//
//  /**
//   * @param oTransitionGeometry
//   * The transition geometry before this current civil curve.
//   * @param oIdFromInput
//   *  >=0 if the geometry was provided as input, equals -1 otherwise. Filled if the pointer is not null.
//   * @Param iHandleMemory
//   * Set to TRUE if the user wants the handle the deletion of the CATCivilCurveEvaluator object, FALSE if the operator does it.
//   * @return
//   * <br>E_FAIL  If there was an issue during the extraction.
//   * <br>S_OK    If the extraction has not encountered any issue.
//   */
//  virtual HRESULT GetPreviousTransitionGeometry(
//    const CATCivilCurveEvaluator *&oTransitionGeometry,
//    CATLONG32 *oIdFromInput = NULL,
//    CATBoolean iHandleMemory = FALSE) const = 0;
//
//  /**
//   * @param oTransitionGeometry
//   * The transition geometry after this current civil curve.
//   * @param oIdFromInput
//   *  >=0 if the geometry was provided as input, equals -1 otherwise. Filled if the pointer is not null.
//   * @Param iHandleMemory
//   * Set to TRUE if the user wants the handle the deletion of the CATCivilCurveEvaluator object, FALSE if the operator does it.
//   * @return
//   * <br>E_FAIL  If there was an issue during the extraction.
//   * <br>S_OK    If the extraction has not encountered any issue.
//   */
//  virtual HRESULT GetNextTransitionGeometry(
//    const CATCivilCurveEvaluator *&oTransitionGeometry,
//    CATLONG32 *oIdFromInput = NULL,
//    CATBoolean iHandleMemory = FALSE) const = 0;
//
//protected:
//  /**
//   * Destructor
//   */
//  virtual ~CATIPGMComputeCivilTransitionCurves(); // -> delete can't be called
//};
//#endif // Q48_Civil_KeepDeprecatedTSCST

// ============================================================================================================================= //
//                                                          DIRECT FUNCTION                                                      //
// ============================================================================================================================= //
/**
* Line-Civil-Circle-Civil-Line
*/
// --------------------------------------------------------------------------------------------------
//   Q48 21/12/21: This is called (through the interface) by:
//      - CATCDSGMInfra/CDSCurve.m/src/CATCSTransitionCurve2DImp.cpp
//      - CATCivilEngAlignmentModeler/CATCivilEngAlignmentModeler.m/src/CATECegAlignmentSketch.cpp
//      - SketcherModeler/CATSkmWireframe.m/src/CATSkmRestrictedServices.cpp
// --------------------------------------------------------------------------------------------------
ExportedByCATGMModelInterfaces HRESULT CATPGMComputeCivilTransitionCurvesInformation(
        CATGeoFactory             * iFactory,
        CATSoftwareConfiguration  * iConfig,
  const CATMathPoint2D            & iPtLine1,
  const CATMathVector2D           & iDirLine1,
  const CATMathVector2D           & iDirOrtho1,
  const CATMathPoint2D            & iPtLine2,
  const CATMathVector2D           & iDirLine2,
  const CATMathVector2D           & iDirOrtho2,
  const CATPGMCivilTransitionInfo * iTransitionInfo,
  const CATCivilCurveType           iCurveType,
        CATMathPoint2D            & oCivilOnLine1,
        CATMathPoint2D            & oCenterCircle,
        CATMathPoint2D            & oCivilOnLine2,
        CATBoolean                & oSelfIntersection,
        CATBoolean                & oEndPointsConfused,
  const CATBoolean                  iReverse = FALSE);

/**
* Line-Civil-Line
*/
// --------------------------------------------------------------------------------------------------
//   Q48 21/12/21: This is called (through the interface) by:
//      - CATCivilEngAlignmentModeler/CATCivilEngAlignmentModeler.m/src/CATECegAlignmentSketch.cpp
// --------------------------------------------------------------------------------------------------
ExportedByCATGMModelInterfaces HRESULT CATPGMComputeCivilTransitionCurvesInformation(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  const CATMathPoint2D &iPtLine1,
  const CATMathVector2D &iDirLine1,
  const CATMathVector2D &iDirOrtho1,
  const CATMathPoint2D &iPtLine2,
  const CATMathVector2D &iDirLine2,
  const CATMathVector2D &iDirOrtho2,
  const CATPGMCivilTransitionInfo *iTransitionInfo,
  const CATCivilCurveType iCurveType,
  CATMathPoint2D &oCivilOnLine1,
  CAT2DCurveEvaluator *&oCivilCurve,
  CATMathPoint2D &oCivilOnLine2);
#endif /* CATIPGMComputeCivilTransitionCurves_h_ */
