#ifndef CATIPGMConfusionCrvCrv_h_
#define CATIPGMConfusionCrvCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"

class CATMathSetOfPointsND;
class CATCurve;
class CATEdgeCurve;
class CATCrvParam;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMConfusionCrvCrv;

/**
 * Class defining the operator testing the overlap of two CATCurves.
 *<br>Two curves are overlapping within a given tolerance if their
 * Haussdorf distance <tt>dH</tt> is less than this tolerance.<br>
 * <pre>
 * dH= MAX [ Max{Point1 in Curve1}Min{Point2 in Curve2} distance(Point1,Point2),
 *           Max{Point2 in Curve2}Min{Point1 in Curve1} distance(Point1,Point2) ]</pre>
 *<ul>
 *<li>The CATConfusionOperator is created with the @href CATPGMCreateConfusionCrvCrv method and 
 * directly released with the <tt>Release</tt> method. It is not streamable. 
 *<li>The operation is automatically done at the operator creation. 
 *<li>The result is accessed with <tt>GetConfusion</tt> method.
 *</ul>
 */
class ExportedByCATGMModelInterfaces CATIPGMConfusionCrvCrv: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMConfusionCrvCrv();

  /**
 * Returns the result of <tt>this</tt> CATIPGMConfusionCrvCrv operator.
 * Check before that the extremities of the curves are overlapping within 
 * the given tolerance.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl>
 * <dt><tt>TRUE</tt> <dd> if the Haussdorf distance between the two CATCurves
 * is less than the tolerance given at the operator creation.
 *    <dt><tt>FALSE</tt> <dd> otherwise.  </dl> 
 */
  virtual CATBoolean GetConfusion() const = 0;

  /**
	 * @nodoc
   * If launched before the run method, this method enable oParamMapping to be
   * filled with a mapping from one curve to another. More precisely, 
   * oParamMapping is 2-dimensional and will contain value (w0,w1) such
   * that w0 and w1 are corresponding parameters on the confusion.
   */
  virtual void FillParamMapping(CATMathSetOfPointsND &oParamMapping) = 0;

  /**
   * Returns the approximate value of the gap between the curves, if there are overlapping.
   * @return
	 * The gap.
   */
  virtual double GetMaxGap() const = 0;

  /** @nodoc */
  virtual CATBoolean TryLinearConfusion(double iTolerance = 0.) = 0;

  /**
  * Returns 1 is a confusion exists, independantly of the length of the curves
  */
  virtual CATBoolean GetTotalConfusion() const = 0;

  /**
  * Reset Options and result as in constructor
  */
  virtual void ResetResult() = 0;

  virtual void ResetOptions() = 0;

  /*
   * @nodoc
   */
  virtual void SetReduceStep() = 0;

  /**
   * For local use only
   * Propagate the confusion. Returns 2 if a total confusion occurs,
   * 0 if no confusion occurs, 1 if an inclusion occurs.
   * ow1 and ow2 contains the global parameters of the end of the state of the propagation
   */
  virtual CATLONG32 PropagateConfusion(
    double &ow1,
    double &ow2,
    CATBoolean iFromMiddle = FALSE) = 0;

  /*
   * @nodoc
   */
  virtual void SetDetectInvalidPcurve() = 0;

  /*
  * @nodoc
  */
  virtual void SetOnlyPropagation() = 0;

  /*
  * @nodoc
  */
  virtual void SetNonVerificationTest() = 0;

  /*
  * @nodoc
  */
  virtual void SetNonExtremityTest() = 0;

  /*
  * Setting  parameters  without  changing  the  surface
  */
  virtual void SetParameters(
    const CATCrvParam &iStartParam1,
    const CATCrvParam &iEndParam1,
    const CATCrvParam &iStartParam2,
    const CATCrvParam &iEndParam2) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMConfusionCrvCrv(); // -> delete can't be called
};

ExportedByCATGMModelInterfaces void CATPGMMapOnECrv(
  CATMathSetOfPointsND *ioParamMap,
  const CATCurve *iPCrv1,
  const CATEdgeCurve *iECrv1,
  const CATCurve *iPCrv2,
  const CATEdgeCurve *iECrv2);

#endif /* CATIPGMConfusionCrvCrv_h_ */
