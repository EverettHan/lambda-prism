#ifndef CATICGMInterproxCrv_h_
#define CATICGMInterproxCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMVirtual.h"

class CATMathSetOfVectors;
class CATNurbsCurve;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMInterproxCrv;

/**
 * Class representing the geometric operator that deforms curves on a set of points.
 * <br>Several parameters define this operator:
 * <ul><li>The tension parameter strengthens the shape: a higher tension gives a flatter shape.
 * <li>The curvature (or smoothness) parameter regularizes the curvature along the curve: 
 * a higher curvature coefficient gives a smoother curve.
 * </ul>
 * This operator projects the set of points on the curves and use a least squares method to deform the curves. 
 * <br>To use it in <tt>BASIC</tt> mode:
 * <ul><li>Create it with the <tt>CATCGMCreateInterproxCrv</tt> global method. The run is automatically done and the
 * input curves are directly deformed.
 * <li>Release the operator with the <tt>Release</tt> method after use after use.
 * </ul>
 * <br>To use it in <tt>ADVANCED</tt> mode:
 * <ul><li>Create it with the <tt>CATCGMCreateInterproxCrv</tt> global method.
 * <li>Change the smoothness or tension parameters with the <tt>SetXxx</tt> methods.
 * <li>Run it. This step directly deforms the input curves, it is the reason why there is no <tt>GetResult</tt>
 * method. You can <tt>Run</tt> again the operator with different parameters, 
 * allowing you to iterate on the deformation.
 * <li>Release the operator with the <tt>Release</tt> method after use.
 * </ul>
 */
class ExportedByCATGMOperatorsInterfaces CATICGMInterproxCrv: public CATICGMVirtual
{
public:
  /**
   * Constructor
   */
  CATICGMInterproxCrv();

  /**
 * Runs <tt>this</tt> operator (<tt>ADVANCED</tt> mode).
 * <br>The input curves are directly modified
 */
  virtual void Run() = 0;

  /**
 * Defines the tension parameter (<tt>ADVANCED</tt> mode).
 * @param iTension
 * The new value of the tension parameter.
 */
  virtual void SetTensionParameter(const double iTension) = 0;

  /**
 * Defines the smoothness parameter (<tt>ADVANCED</tt> mode).
 * @param iSmoothness
 * The new value of the smoothness parameter.
 */
  virtual void SetCurvatureParameter(const double iSmoothness) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMInterproxCrv(); // -> delete can't be called
};

#endif /* CATICGMInterproxCrv_h_ */
