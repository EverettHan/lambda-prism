#ifndef CATIPGMApproxClothoide_h_
#define CATIPGMApproxClothoide_h_

// COPYRIGHT DASSAULT SYSTEMES 2015

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"

class CAT2DCurveEvaluator;
class CATCurve;
class CATGeoFactory;
class CATMathPoint2D;
class CATMathVector2D;
class CATMathInterval;
class CATPCircle;
class CATPLine;
class CATSoftwareConfiguration;
class CATSurface;

// Temp
#include "CATCivilCurveArchiTEMP.h"

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMApproxClothoide;


/**
 * Defines curve orientation when needed as input (e.g. for clothoid creation in between two circles)
 */
enum CATApproxClothoide_ClockOrientation {CATApproxClothoide_CLOCKWISE, CATApproxClothoide_ANTI_CLOCKWISE};


/**
* Defines the transition type in between two circles
*/
enum CATApproxClothoide_CircleCircleTransition {CATApproxClothoide_OVE, CATApproxClothoide_REVERSE};

//===================================================================
class ExportedByCATGMModelInterfaces CATIPGMApproxClothoide: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMApproxClothoide();

#ifndef Q48_RemoveAngleOptions
  //-----------------------------------------------------------------------------
  // Options Interface (Set)
  //-----------------------------------------------------------------------------
  /**
   * Set the domain in which the clothoide angle must lay.
   * <br> Currently, the operator is optimized for an angle between [0, 2PI]
   * and does not try to find solution for an angle>4PI.
   * @param iMinAngle
   * The minimum angle the clothoide can have.
   * @param iMaxAngle
   * The Maximum angle the clothoide can have.
   */
  virtual void SetAngleDomain(double iMinAngle, double iMaxAngle) = 0;

  /**
    * Set the algorithm behavior in case two clothoids
    * can be defined with the input parameters and other options given.
    * <br> Note this only occurs when the shifting and the length are given.
    */
  virtual void SetAngleToKeep(CATBoolean iSmallerAngle) = 0;
#endif // Q48_RemoveAngleOptions

  //-----------------------------------------------------------------------------
  // Output Interface (Get)
  //-----------------------------------------------------------------------------
  /**
   * @return
   * <br>E_FAIL  If there was an operator issue during the computation.
   * <br>S_FALSE If the operator did not succeed because of the inputs & option given
   *             are not consistent (out of domain or does not described a clothoide respecting the options).
   * <br>S_OK    If the operator has not encountered any issue.
   */
  virtual HRESULT GetRunStatus() = 0;

  /**
    * @return
    * TRUE If the solution is a point, FALSE if it is a curve.
    */
  virtual HRESULT IsAPoint(CATBoolean &iIsAPoint) = 0;

  /**
   *  Retrieve the point in UV space where the clothoide start.
   */
  virtual HRESULT GetPoint(CATMathPoint2D &oPoint) = 0;

  /**
   * @param oCurve
   * The curve approximating the clothoïde.
   * <br>The object life of the object retrieved has to be handle by the caller.
   */
  virtual HRESULT GetCurve(CATCurve *&oCurve) = 0;

  /**
    * Retrieve the clothoide properties of the curve computed.
    */
  virtual HRESULT GetClothoideProperties(
    double *oA2 = NULL,
    double *oLength = NULL,
    double *oRadius = NULL,
    double *oAngle = NULL,
    double *oShifting = NULL) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMApproxClothoide(); // -> delete can't be called
};

// ============================================================================================================================= //
//                                                            CREATE                                                             //
// ============================================================================================================================= //

/* deprecated */ // use CATPGMCreateApproxCivilCurve with suitable CATCreateCivilCurveEvaluator
/**
* Create an operator which computes approximation of a clothoïde defined through two parameters at least.
* <br> If more than two clothoide parameters are given, the operator checks the consistency of the result with them.
* @param iPt
* The point where the clothoïde start
* @param iDir
* The tangent where the clothoïde start
* @param iDirOrtho
* The orthogonal direction of iDir. It represents the direction of the clothoïde center of curvature.
* @param iSurface
* The surface support of the clothoide.
* @param iA2
* The clothoïde parameter a²
* <br> It belongs in [0, +Infinite[
* @param iRadius
* The radius of the clothoïde end extremity.
* <br> It belongs in ]0, +Infinite[
* @param iLength
* The length of the clothoïde
* <br> It belongs in[0, +Infinite[
* @param iAngle
* The final angle of the clothoïde
* <br> It is the angle between the clothoïde end extremity normal and
* the orthogonal direction.
* <br> For instance, angle=2PI will leads to a clothoide that makes a complete turn.
* <br> It belongs in [0, +Infinite[
* @param iShifting
* The shifting of the clothoïde.
* <br>It represents the min distance between
* the circle of the clothoïde end extremity with the
* line defined by the point and direction given.
* <br> It belongs in [0, 0.1957*Length] and [0, sqrt(iA2*pi)/2.0[
* @return [out, IUnknown#Release]
*/
ExportedByCATGMModelInterfaces CATIPGMApproxClothoide *CATPGMCreateApproxClothoide(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  const CATMathPoint2D &iPt,
  const CATMathVector2D &iDir,
  const CATMathVector2D &iDirOrtho,
  CATSurface *iSurface,
  const double *iA2 = NULL,
  const double *iLength = NULL,
  const double *iRadius = NULL,
  const double *iAngle = NULL,
  const double *iShifting = NULL);

/* deprecated */ // use CATPGMCreateApproxCivilCurve with suitable CATCreateCivilCurveEvaluator
/**
* Create an operator which computes approximation of a clothoïde defined by a line and a circle in 2D (the surface UV-Space).
* @param iLineOrigin
* A point on the line.
* @param iLineDir
* The direction of the line. The direction determines the direction of the clothoide.
* @param iCircleCenter
* The center of the circle.
* @param iCircleRadius
* The radius of the circle.
* @param iSurface
* The surface support of the clothoide.
* @return [out, IUnknown#Release]
*/
ExportedByCATGMModelInterfaces CATIPGMApproxClothoide *CATPGMCreateApproxClothoide(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  const CATMathPoint2D &iLineOrigin,
  const CATMathVector2D &iLineDir,
  const CATMathPoint2D &iCircleCenter,
  double iCircleRadius,
  CATSurface *iSurface);

#ifdef CIVIL_CURVE_OLD
/**
* Create an operator which computes approximation of a clothoïde defined by a PLine and a Pcircle.
* <br> The object limits are not taken into account.
* <br> The surface support will be the PLine support.
* @param iInverse
* Inverses the direction of the PLine for the computation (the PLine remains unchanged).
* @return [out, IUnknown#Release]
*/
ExportedByCATGMModelInterfaces CATIPGMApproxClothoide *CATPGMCreateApproxClothoide(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  const CATPLine *iPLine,
  const CATPCircle *iPCircle,
  CATBoolean iInverse = FALSE);
#endif //CIVIL_CURVE_OLD

/* deprecated */ // use CATPGMCreateApproxCivilCurve with suitable CATCreateCivilCurveEvaluator
/**
* Create an operator which computes approximation of a clothoïde defined in between two oriented circles in 2D (the surface UV-Space).
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
* @param iSurface
* The surface support of the clothoide.
* @return [out, IUnknown#Release]
*/
ExportedByCATGMModelInterfaces CATIPGMApproxClothoide *CATPGMCreateApproxClothoide(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  const CATMathPoint2D &iCircleCenter1,
  const double iCircleRadius1,
  const CATApproxClothoide_ClockOrientation iCircleOrientation1,
  const CATMathPoint2D &iCircleCenter2,
  const double iCircleRadius2,
  CATSurface *iSurface);

/* deprecated */ // use CATPGMCreateApproxCivilCurve with suitable CATCreateCivilCurveEvaluator
/**
* Create an operator which computes approximation of a clothoïde defined by the two extremities points and initial tangent.
* <br> The surface support will be the PLine support.
* @param iStartPoint
* The start extremity of the clothoïd.
* @param iStartTangent
* The start extremity tangent of the clothoïd.
* @param iEndPoint
* The end extremity of the clothoïd.
* @param iSurface
* The surface support of the clothoide.
* @return [out, IUnknown#Release]
*/
ExportedByCATGMModelInterfaces CATIPGMApproxClothoide *CATPGMCreateApproxClothoide(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  const CATMathPoint2D &iStartPoint,
  const CATMathVector2D &iStartTangent,
  const CATMathPoint2D &iEndPoint,
  CATSurface *iSurface);

// ============================================================================================================================= //
//                                                            METHODS                                                            //
// ============================================================================================================================= //

/**
* Computes the two clothoids parameters from a Line-Clotho-Circle-Clotho-Line configuration.
* <br/>
* This method can return self intersecting solution. To avoid self-intersecting solution,
* one must check the sum of the two clothoids final angle is lower than the angle between the two orthogonal directions.
* <br/>
* The solution returned will always be the one going toward the line intersection.
* @param iPtLine1
* A point of the first line.
* @param iDirLine1
* The direction of the first line. The sign is not used.
* @param iDirOrtho1
* The orthogonal direction of iDirLine1. It represents the direction of the first clothoïde center of curvature.
* @param iPtLine2
* A point of the second line.
* @param iDirLine2
* The direction of the second line. The sign is not used.
* @param iDirOrtho2
* The orthogonal direction of iDirLine2. It represents the direction of the second clothoïde center of curvature.
* @param iLengthClotho1
* The length of the first clothoid
* @param iLengthClotho2
* The length of the second clothoid
* @param iRadius
* The radius of the circle arc between the two clothoids.
* @param oClotho1OnLine1
* The starting point of the first clothoid on the first line.
* @param oCenterCircle
* The position of the center of the circle between the two clothoids.
* @param oClotho2OnLine2
* The starting point of the second clothoid on the second line.
* @param oSelfIntersection
* Equals TRUE if the solution is self-intersecting, FALSE otherwise.
* @param oEndPointsConfused
* Equals TRUE if the arc between the two clothoids is smaller than the resolution, FALSE otherwise.
* @return 
* <br>E_FAIL  If there was an issue during the computation.
* <br>S_FALSE If the operator did not succeed because of the inputs & option given
*             are not consistent (ex: the final angle is too high, the clothoid length under the resolution)
* <br>S_OK    If the operator has not encountered any issue.
*/
ExportedByCATGMModelInterfaces HRESULT CATPGMComputeParamClothoide(
  CATSoftwareConfiguration *iConfig,
  const CATTolerance &iTol,
  const CATMathPoint2D &iPtLine1,
  const CATMathVector2D &iDirLine1,
  const CATMathVector2D &iDirOrtho1,
  const CATMathPoint2D &iPtLine2,
  const CATMathVector2D &iDirLine2,
  const CATMathVector2D &iDirOrtho2,
  const double iLengthClotho1,
  const double iLengthClotho2,
  const double iRadius,
  CATMathPoint2D &oClotho1OnLine1,
  CATMathPoint2D &oCenterCircle,
  CATMathPoint2D &oClotho2OnLine2,
  CATBoolean &oSelfIntersection,
  CATBoolean &oEndPointsConfused);

/**
* Computes the two clothoids parameters from a Circle-Clotho-Line-Clotho-Circle configuration.
* @param iCircleCenter1
* The center of the first circle
* @param iCircleRadius1
* The radius of the first circle
* @param iLineLeftFromCircle1
* The position of the intermediare line from Circle1
* @param iCircleCenter2
* The center of the second circle
* @param iCircleRadius2
* The radius of the second circle
* @param iLineLeftFromCircle2
* The position of the intermediare line from Circle2
* @param iLengthClotho1
* The length of the clothoid starting from the first circle
* @param iLengthClotho2
* The length of the clothoid starting from the second circle
* @param oClotho1OnLine
* The starting point of the first clothoid on the intermediate line.
* @param oClotho2OnLine
* The starting point of the second clothoid on the intermediate line.
* @param oDirClotho1
* The starting direction of the first clothoid
* @param oDirClotho2
* The starting direction of the second clothoid
* @return 
* <br>E_FAIL  If there was an issue during the computation.
* <br>S_FALSE If the operator did not succeed because of the inputs & option given
*             are not consistent (ex: the final angle is too high, the clothoid length under the resolution)
* <br>S_OK    If the operator has not encountered any issue.
*/
ExportedByCATGMModelInterfaces HRESULT CATPGMComputeParamClothoide(
  CATSoftwareConfiguration *iConfig,
  const CATTolerance &iTol,
  const CATMathPoint2D &iCircleCenter1,
  const double iCircleRadius1,
  const CATBoolean iLineLeftFromCircle1,
  const CATMathPoint2D &iCircleCenter2,
  const double iCircleRadius2,
  const CATBoolean iLineLeftFromCircle2,
  const double iLengthClotho1,
  const double iLengthClotho2,
  CATMathPoint2D &oClotho1OnLine,
  CATMathPoint2D &oClotho2OnLine,
  CATMathVector2D &oDirClotho1,
  CATMathVector2D &oDirClotho2);

#endif /* CATIPGMApproxClothoide_h_ */
