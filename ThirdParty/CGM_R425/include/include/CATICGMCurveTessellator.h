#ifndef CATICGMCurveTessellator_h_
#define CATICGMCurveTessellator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATSoftwareConfiguration.h"
#include "CATICGMVirtual.h"
#include "CATDataType.h"
#include "CATMathConstant.h"

class CATCrvLimits;
class CATCurve;
class CATMathSetOfPointsND;

extern ExportedByCATGMModelInterfaces IID IID_CATICGMCurveTessellator;

/**
 * Class defining a tessellation operator on curves.
 * <br> This operator computes a discretized geometry on the curves as bars.
 * The extremities of the bars are called points. Three parameters tune the tessellation result:
 * <dl>
 * <dt> Sag </dt><dd> Defines the maximum distance between a bar and the object to tessellate
 * <dt> Step </dt><dd> Defines the maximum length of a bar. If not defined, the step is infinite 
 * (this parameter is unused)
 * <dt> Angle </dt><dd> Defines the maximum angle between the normals at each bar end. 
 * </dl>
 * The tessellation operator follows the scheme of all CGM operator:
 * <ul>
 * <li> Create an operator instance by using <tt>CATCGMCreateCurveTessellator</tt>
 * <li> Run,
 * <li> Optionally, adds other curves to tessellate in the same operation,
 * <li> Recover the results into arrays that are allocated by the operator,
 * <li> Delete the operator instance. The deletion of the operator leads to the deletion
 * of the arrays of results.
 * </ul>
 */
class ExportedByCATGMModelInterfaces CATICGMCurveTessellator: public CATICGMVirtual
{
public:
  /**
   * Constructor
   */
  CATICGMCurveTessellator();

  /**
   * Adds an other curve to <tt>this</tt> CATICGMCurveTessellator.
   * @param iCurve
   * The other curve to tessellate in the same operation.
   * @param iCurveLimits
   * The part of the curve to take into account.
   */
  virtual void AddCurve(CATCurve *iCurve, const CATCrvLimits &iCurveLimits) = 0;

  /**
   * Defines a finite step for <tt>this</tt> CATICGMCurveTessellator.
   * @param iStep
   * The Step value.
   */
  virtual void SetStep(double iStep) = 0;

  /**
   * Runs <tt>this</tt> CATICGMCurveTessellator.
   */
  virtual void Run() = 0;

  /**
   * Retrieves the results associated with a curve.
   * @param iCurve
   * A curve among the input curves.
   * @param oMathPoints
   * A CATMathSetOfPointsND pointer. This set contains the points (as 3 Cartesian coordinates)
   * of the resulting tessellation.
   * @param oCrvParams
   * A CATMathSetOfPointsND pointer. This set contains the points (as a CATCrvParam on the
   * underlying edge curve)
   * of the resulting tessellation.
   */
  virtual void GetCurve(
    CATCurve *iCurve,
    CATMathSetOfPointsND **oMathPoints,
    CATMathSetOfPointsND **oCrvParams) = 0;

  /**
   * Retrieves the results (in doubles) associated with a curve.
   * @param iCurve
   * A curve among the input curves.
   * @param ioNumberOfPoints
   * The number of points of the resulting tessellation.
   * @param oPointData
   * The array of the resulting points. This array is allocated by the <tt>GetCurve</tt>
   * method. The j-th coordinate of the i-th point is
   * <tt>oPointData[3*(i-1)+j-1]</tt>. 
   */
  virtual void GetCurve(CATCurve *iCurve, CATLONG32 &ioNumberOfPoints, double **oPointData) = 0;

  /**
   * Retrieves the results (in floats) associated with a curve.
   * @param iCurve
   * A curve among the input curves.
   * @param ioNumberOfPoints
   * The number of points of the resulting tessellation.
   * @param oPointData
   * The array of the resulting points. This array is allocated by the <tt>GetCurve</tt>
   * method. The j-th coordinate of the i-th point is
   * <tt>oPointData[3*(i-1)+j-1]</tt>. 
   */
  virtual void GetCurve(CATCurve *iCurve, CATLONG32 &ioNumberOfPoints, float **oPointData) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMCurveTessellator(); // -> delete can't be called
};

/**
  * Constructs a CATICGMCurveTessellator with an infinite step.
  * @param iSag
  * The Sag value.
  * @param iAngle
  * The Angle value.
  * @return [out, IUnknown#Release]
  */
ExportedByCATGMModelInterfaces CATICGMCurveTessellator *CATCGMCreateCurveTessellator(
  double iSag,
  double iAngle = CATPI*.25);

/**
  * Constructs a CATICGMCurveTessellator with an infinite step.
  * @param iSoftwareConfiguration
  * The software configuration.
  * @param iSag
  * The Sag value.
  * @param iAngle
  * The Angle value.
  * @return [out, IUnknown#Release]
  */
ExportedByCATGMModelInterfaces CATICGMCurveTessellator* CATCGMCreateCurveTessellator(
    CATSoftwareConfiguration * iSoftwareConfiguration,
    double iSag,
    double iAngle = CATPI * .25);

#endif /* CATICGMCurveTessellator_h_ */
