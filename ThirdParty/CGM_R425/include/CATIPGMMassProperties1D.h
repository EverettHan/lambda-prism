#ifndef CATIPGMMassProperties1D_h_
#define CATIPGMMassProperties1D_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMDynMassProperties1D.h"
#include "CATMath3x3Matrix.h"

class CATCrvParam;
class CATMathFunctionX;
class CATMathInterval;
class CATSoftwareConfiguration;
class CATMathPoint;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMMassProperties1D;

/**
* Class allowing to perform a global analysis on a CATCurve.
*<br>This class is not streamable. It performs conversions from curve parameter
* to length and the converse. The conversion can be time consuming, and the precision is
* the factory resolution.
*/
class ExportedByCATGMModelInterfaces CATIPGMMassProperties1D: public CATIPGMDynMassProperties1D
{
public:
  /**
   * Constructor
   */
  CATIPGMMassProperties1D();

  /**
	* Set the operator in a mode where, in the GetParamFromLength method,
	* it estimates the solution before starting the computation.
	* Better and quicker results, but the modification of comportment may
	* affect sensitive algorithms.
	*/
  virtual void SetEstimateInit(const CATBoolean &iEstimate = TRUE) = 0;

  /**
   * Set the absolute length and cog error the computation can make.
   * @param iPrecision
   * The absolute error.
   */
  virtual void SetPrecision(double iPrecision) = 0;

  /**
    * Set the relative inertia error the computation can make.
    * <br> The inertia can no be computed with an absolute error for performance purpose.
    * @param iPrecision
    * The relative error.
    */
  virtual void SetRelativePrecision(double iPrecision) = 0;

  /**
   * Set the new origin for the computation.
   * @param iOrigin
   * The origin. For instance, the COG computed will be relatively to this point.
   */
  virtual void SetOrigin(const CATMathPoint &iOrigin) = 0;

  //-----------------------------------------------------------------------------
  // Options (Get)
  //-----------------------------------------------------------------------------
  /**
	* Returns the parameter of the point at a given length (on the curve)
	* to another point.
	* @param iParam
	* The parameter of the point from which the distance is computed.
	* @param iLength
	* The length on the curve.
	* @return
	* The parameter of the point at <tt>iLength</tt> from <tt>iParam</tt>.
	*/
  virtual CATCrvParam GetParamFromLength(
    const CATCrvParam &iParam,
    const CATLength &iLength) const = 0;

  /**
	* Returns the length between two points of a curve.
	* @param iParam1
	* The parameter of the first point on the curve.
	* @param iParam2
	* The parameter of the second point on the curve.
	* @return
   * The length on the curve between the two points. (algebraic length: may be negative)
	*/
  virtual CATLength GetLengthFromParams(
    const CATCrvParam &iParam1,
    const CATCrvParam &iParam2) const = 0;

  /**
	* Returns the length between two points of a curve with a relative precision 
   * of 1%. (NOT GUARANTEED AT ALL) (NLD210109. Garanti comme du Gourdon: parfois c'est bon)
	* @param iParam1
	* The parameter of the first point on the curve.
	* @param iParam2
	* The parameter of the second point on the curve.
	* @return
   * The length on the curve between the two points. (algebraic length: may be negative)
	*/
  virtual CATLength GetRoughLengthFromParams(
    const CATCrvParam &iParam1,
    const CATCrvParam &iParam2) const = 0;

  /**
	* Returns the total length of the curve.
	* @return
	* The length.
	*/
  virtual CATPositiveLength GetLength() const = 0;

  /**
   * Returns the center of gravity of the curve limited to the given parameters.
   * @return
   * The center of gravity (relatively to the origin setted).
   */
  virtual CATMathPoint GetCenterOfGravity(
    const CATCrvParam &iParam1,
    const CATCrvParam &iParam2) const = 0;

  /**
   * Returns the inertia matrix of the curve limited to the given parameters.
   * @return
   * The inertia matrix (relatively to the origin setted).
   */
  virtual CATMath3x3Matrix GetInertiaMatrix(
    const CATCrvParam &iParam1,
    const CATCrvParam &iParam2) const = 0;

  /**
   * Compute the mass properties informations of the curve limited to the given parameters.
   * <br> The mass properties are computed from the origin point setted to this operator.
   * @param oLength
   * The length.
   * @param oCOG
   * The center of gravity (relatively to the origin setted).
   * @param oInertia
   * The inertia matrix (relatively to the origin setted).
   * @return
   * TRUE if no issue with the computation, FALSE otherwise.
   */
  virtual CATBoolean GetMassProperties(
    const CATCrvParam &iParam1,
    const CATCrvParam &iParam2,
    double *oLength = NULL,
    CATMathPoint *oCOG = NULL,
    CATMath3x3Matrix *Inertia = NULL) const = 0;

  /**
   * Compute the mass properties informations of the curve limited to the given parameters.
   * <br> The mass properties are computed from the origin point setted to this operator.
   * <br> The retrived mass properties are not normalized.
   * @param oLength
   * The length.
   * @param oCOG
    * The true center of gravity = (oCOG[0],oCOG[1],oCOG[2])/oCOG[3], oCOG[3] is the length computed with the COG, so oCOG[3] might != oLength=GetLength();
   * @param oInertia
   * Ixx=oInertia[0], Iyy=oInertia[1], Izz=oInertia[2], Iyz=oInertia[3] , Izx=oInertia[4], Ixy=oInertia[5]
   * @return
   * TRUE if no issue with the computation, FALSE otherwise.
   */
  virtual CATBoolean GetMassPropertiesNotNormalized(
    const CATCrvParam &iParam1,
    const CATCrvParam &iParam2,
    double *oLength = NULL,
    double *oCOG = NULL,
    double *oInertia = NULL) const = 0;

  /**
   * @nodoc
   * NLD190109 returns 1 if identical parameters, considering null length tolerance given.
   * Computation is fast when tolerance si reasonable (not too high, not too small, for example
   * near factory resolution, and rough length computation precise enough). Otherwise
   * exact length computation is done.
   */
  virtual int IdenticalParams(
    const CATCrvParam &iParam1,
    const CATCrvParam &iParam2,
    double iTolForNullLength) const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMMassProperties1D(); // -> delete can't be called
};

/**
* Creates a global analyzer on a CATCurve.
* @param iCurveToAnalyse
* The pointer to the curve to analyze.
* @return [out, IUnknown#Release]
*/
ExportedByCATGMModelInterfaces CATIPGMMassProperties1D *CATPGMCreateMassProperties1D(
  CATSoftwareConfiguration *iSoftwareConfiguration,
  const CATCurve *iCurveToAnalyse);

//DEPRECATED -- DO NOT USE -- WILL DISAPPEAR SOON
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMMassProperties1D *CATPGMCreateMassProperties1D(const CATCurve *iCurveToAnalyse);

#endif /* CATIPGMMassProperties1D_h_ */
