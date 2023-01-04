#ifndef CATIPGMEdgeCurveComputation_h_
#define CATIPGMEdgeCurveComputation_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMOperator.h"

class CATCrvLimits;
class CATCrvParam;
class CATEdgeCurve;
class CATMapX;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMEdgeCurveComputation;

//#endif
/**
 * Class defining the operator to create the edge curve representing two curves.
 * <br>This operator first checks that the two curves can be merged. You must use it as soon as the mapping
 * between the parameterizations of the two initial curves is not linear.
 *<ul>
 *<li>The CATIPGMEdgeCurveComputation operator is created with the <tt>CATPGMCreateEdgeCurveComputation</tt> method and 
 * directly released with the <tt>Release</tt> method.
 * It is is not streamable. 
 *<li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed at the operator creation. 
 * In case of <tt>ADVANCED</tt>
 * mode, options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. 
 *<li>In both cases, the result is accessed with the <tt>GetEdgeCurve</tt> method.
 *</ul>
 */
class ExportedByCATGMModelInterfaces CATIPGMEdgeCurveComputation: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMEdgeCurveComputation();

  /**
 * Returns the created edge curve. 
 * @return 
 * The pointer to the created edge curve, <tt>NULL</tt> if the initial curves cannot be merged.
 */
  virtual CATEdgeCurve *GetEdgeCurve() const = 0;

  /**
 * Defines the domains of the curves to take into account (<tt>ADVANCED mode</tt>).
 * <br>This method allows you to specify working params for mergeability computation.
 * <br>The relative sense (start-end of each curve) is specified.
 * <br>It has no effect on the relative orientation of input curves within the edge curve.
 * @param iStartParam1
 * The parameter of the first limitation of the first curve.
 * @param iEndParam1
 * The parameter of the end limitation of the first curve.
 * @param iStartParam2
 * The parameter of the first limitation of the second curve. 
 * @param iEndParam2
 * The parameter of the end limitation of the second curve.
 */
  virtual void SetParams(
    const CATCrvParam &iStartParam1,
    const CATCrvParam &iEndParam1,
    const CATCrvParam &iStartParam2,
    const CATCrvParam &iEndParam2) = 0;

  /**
 * Defines the domains of the curves to take into account (<tt>ADVANCED mode</tt>).
 * <br>The relative sense (start-end of each curve) is not specified.
 * @param iLimits1
 * The limitations of the first curve.
 * @param iLimits2
 * The limitations of the second curve.
 */
  virtual void SetLimits(
    const CATCrvLimits &iLimits1,
    const CATCrvLimits &iLimits2) = 0;

  /**
 * Defines the maximum gap between the initial curves above which the edge curve cannot be created
 *(<tt>ADVANCED mode</tt>).
 * @param iMaxGap
 * The maximum gap value. By default, a large gap is allowed.
 */
  virtual void SetMaxGap(const double iMaxGap) = 0;

  /**
  * @nodoc 
  * Precises which EdgeCurve of  the PCurve to compute.
	*/
  virtual void SetEdgeCurve(CATEdgeCurve *iECrv1, CATEdgeCurve *iECrv2) = 0;

  /**
  * @nodoc 
  * Detected Invalid EdgeCurve.
	*/
  virtual void SetDetectInvalidMergedCurve() = 0;

  //#ifdef CATIAV5R14
  /**
  * @nodoc 
	*/
  virtual void SetNoCreateMergedCurve() = 0;

  /**
  * @nodoc 
	*/
  virtual CATBoolean IsMergedCurveComputed(double &oGap) = 0;

  /**
  * @nodoc 
	*/
  virtual void SetNonExtremityTest() = 0;

  /**
  * @nodoc 
	*/
  virtual CATMapX *GetMapX() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMEdgeCurveComputation(); // -> delete can't be called
};

#endif /* CATIPGMEdgeCurveComputation_h_ */
