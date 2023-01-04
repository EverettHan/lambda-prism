#ifndef CATICGMInterproxSur_h_
#define CATICGMInterproxSur_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMVirtual.h"

class CATFrFNurbsMultiForm;
class CATMathSetOfVectors;
class CATNurbsSurface;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMInterproxSur;

/**
 * Class representing the geometric operator that deforms surfaces on a set of points.
 * <br>Several parameters define this operator:
 * <ul><li>The tension parameter strengthens the shape: a higher tension gives a flatter shape.
 * <li>The curvature (or smoothness) parameter regularizes the surface curvature: 
 * a higher curvature coefficient gives a smoother surface.
 * </ul>
 * This operator projects the set of points on the surfaces and use a least squares method to deform the surfaces. 
 * <br>To use it in <tt>BASIC</tt> mode:
 * <ul><li>Create it with the <tt>CATCGMCreateInterproxSur</tt> global method. The run is automatically done and the
 * input surfaces are directly deformed.
 * <li>Release the operator with the <tt>Release</tt> method after use.
 * </ul>
 * <br>To use it in <tt>ADVANCED</tt> mode:
 * <ul><li>Create it with the <tt>CATCGMCreateInterproxSur</tt> global method.
 * <li>Change the smoothness or tension parameters with the <tt>SetXxx</tt> methods.
 * <li>Run it. This step directly deforms the input surfaces, it is the reason why there is no <tt>GetResult</tt>
 * method. You can <tt>Run</tt> again the operator with different parameters, 
 * allowing you to iterate on the deformation.
 * <li>Release the operator with the <tt>Release</tt> method after use.
 * </ul>
 */
class ExportedByCATGMOperatorsInterfaces CATICGMInterproxSur: public CATICGMVirtual
{
public:
  /**
   * Constructor
   */
  CATICGMInterproxSur();

  /**
 * Runs <tt>this</tt> operator (<tt>ADVANCED</tt> mode).
 * <br>The input surfaces are directly modified
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

  /**
 * Defines the continuity constraints.
 * @param iImposition
 * The array [4*Nbsur] defining the type of constraints at each extremities of the deformed surface.
 * The array is filled as follows, for the input surfaces from <tt>0 <= i < Nbsur</tt>:
 * <ul>
 * <li><tt>iImposition[0+4*i]</tt> for the iso-parametric boundary <tt>v=0</tt> of the <tt>i-</tt>th surface.
 * <li><tt>iImposition[1+4*i]</tt> for the iso-parametric boundary <tt>u=0</tt> of the <tt>i-</tt>th surface.
 * <li><tt>iImposition[2+4*i]</tt> for the iso-parametric boundary <tt>v=vmax</tt> of the <tt>i-</tt>th surface.
 * <li><tt>iImposition[3+4*i]</tt> for the iso-parametric boundary <tt>u=umax</tt> of the <tt>i-</tt>th surface.
 * </ul>
 * <br><b>Legal values</b>: <tt>0</tt> for a free boundary,
 * <tt>1</tt> for a C0 continuity with the input surface, 
 * <tt>2</tt> for a C1 continuity, <tt>3</tt> for a C2 continuity.
 */
  virtual void SetContinuity(const int *iImposition) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMInterproxSur(); // -> delete can't be called
};

#endif /* CATICGMInterproxSur_h_ */
