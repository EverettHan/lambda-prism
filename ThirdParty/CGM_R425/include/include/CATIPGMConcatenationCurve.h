#ifndef CATIPGMConcatenationCurve_h_
#define CATIPGMConcatenationCurve_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMOperator.h"
#include "CATListOfInt.h"

class CATCurve;
class CATGEoFactory;
class CATSurface;
class CATLISTP(CATCrvLimits);
class CATLISTP(CATCurve);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMConcatenationCurve;

//-----------------------------------------------------------------------------
/**
 * Class representing the geometric operator to concatenate a list of curves.
 * <br>The junction between two initial curves must be C2 continuous. If not, the operator tries
 * to deform the curves in order to make them C2. If the deformation is not inside a given
 * tolerance (by default the factory resolution), these curves are not modified.
 *<br>
 * The CATIPGMConcatenationCurve operator follows the global frame of the geometric operators. 
 *<ul>
 * <li>A CATIPGMConcatenationCurve operator is created with the <tt>CATPGMCreateConcatenationCurve</tt> global method:
 * It must be directly released with the <tt>Release</tt> method after use. It is not streamable. 
 *<li>Options can be precised (such as the limits of the input curves) with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. 
 *<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
 * to keep the resulting curve, use the @href CATICGMContainer#Remove method to remove it from the 
 * geometry factory.
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMConcatenationCurve: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMConcatenationCurve();

  /**
   * Defines the maximum deformation to make the curves being C2 continuous.
   * @param iTol
   * The tolerance value.
   */
  virtual void SetTolerance(double iTol) = 0;

  /**
  * Defines the underlying surface on which the curves must be concatened.
  * @param iSurface
  * The pointer to the surface.
  * @return
  * Not null in case of error.
  */
  virtual void SetSurface(CATSurface *iSurface) = 0;

  /**
   * Runs <tt>this</tt> operator.
   */
  virtual int Run() = 0;

  /**
   * Returns the curve resulting of the concatenation of the input curves.
   * @param ioListOfConcatCurve
   * The pointer to the list of concatenated curves. If you do not want 
   * to keep the resulting curve, use the @href CATICGMContainer#Remove method to remove it from the 
   * geometric factory.
   * @param ioListOfCrvLimits
   * The pointer to the list of limits of concatenated curves.
   * @param ioListOrient
   * The list of orientation of concatenated curves.
   * <br><b>Legal values</b>:
   * <tt>1</tt> for the same orientation than the list, <tt>-1</tt> for the opposite orientation.
   * @param ioListModified
   * <br><b>Legal values</b>:
   * <tt>0</tt> the curve is not concatenated, <tt>1</tt> the curve is not concatenated.
	 * @param ioListOfCurveRef
   * <br><b>Legal values</b>: 
   * <tt>0</tt> the curve is not concatenated, <tt>n</tt> the curve is a part of the <tt>ioListOfConcatCurve[n]<tt> curve.
	 *
	*/
  virtual void GetResult(
    CATLISTP(CATCurve) &ioListOfConcatCurve,
    CATLISTP(CATCrvLimits) &ioListOfCrvLimits,
    CATListOfInt &ioListOrient,
    CATListOfInt &ioListModified,
    CATListOfInt &ioListOfCurveRef) = 0;

  /**
	* Allows you to access the maximum deformation resulting from the concatenation.
	* This deformation is the sum of the C0 concatenation, of the optimisation of the deformation
  * due to the optimisation of the continuities. 
  * This is an evaluation of the max-distance on the control points, what means, it is an upper
  * bound of the exact max-distance (Hausdorf's distance). They should have a similar size.
	*/
  virtual void GetDeformation(double &oDeformation) = 0;

  /**
	* impose to concatenate the list of input curves into one curve.
	* The default mode is the concatenation into several curves according to the tolerance
	*/
  virtual void SetOneCurveConcatenationMode(CATLONG32 iMode = 1) = 0;

  /**
	* Allows you to access the minimum deformation to concatenate the wire into one curve.
  * This method has to be called after the Run() and is valid only with one curve concatenation.
  * 
	*/
  virtual void GetThresholdValue(double &oThreshold) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMConcatenationCurve(); // -> delete can't be called
};

/**
 * Creates the operator to concatenate a list of curves.
 * @param iFactory
 * The pointer to the geometry factory.
 * @param iSoftwareConfiguration
 * The pointer to software configuration.
 * @param iListOfCurve
 * The pointer to the list of curve to concatenate.
 * @param iListOfLimits
 * The pointer to the list of limits to take into account.
 * @param iListOfOrient
 * The pointer to the list of relative orientation to use.
 * The relative orientation of the curve with regards to the orientation of the list of curve.
 * <br><b>Legal values</b>:
 * <tt>1</tt> for the same orientation, <tt>-1</tt> for the opposite orientation.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMConcatenationCurve *CATPGMCreateConcatenationCurve(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iSoftwareConfiguration,
  const CATLISTP(CATCurve) &iListOfCurve,
  const CATLISTP(CATCrvLimits) &iListOfLimits,
  const CATListOfInt & iListOfOrient);

/**
 * @nodoc
 */
ExportedByCATGMOperatorsInterfaces CATIPGMConcatenationCurve *CATPGMCreateConcatenationCurve(
  CATGeoFactory *iFactory,
  const CATLISTP(CATCurve) &iListOfCurve,
  const CATLISTP(CATCrvLimits) &iListOfLimits,
  const CATListOfInt & iListOfOrient);

#endif /* CATIPGMConcatenationCurve_h_ */
