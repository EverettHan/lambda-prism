#ifndef CATICGMCrvFittingToNurbsCrv_h_
#define CATICGMCrvFittingToNurbsCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMVirtual.h"
#include "CATDataType.h"
#include "CATSkillValue.h"

class CATCrvLimits;
class CATCrvParam;
class CATFrFNurbsMultiForm;
class CATNurbsCurve;
class CATPNurbs;
class CATSoftwareConfiguration;
class CATGeoFactory;
class CATCurve;
class CATKnotVector;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMCrvFittingToNurbsCrv;

/**
 * Class defining a geometric operator that computes a (possibly approximated) NURBS representation of a CATCurve.
 * <br>If a curve has no corresponding NURBS representation, the operator uses a fitting operation to
 * compute the best approximating NURBS representation. Hence, a maximum deviation must be given as input of 
 * the operator. 
 * <ul>
 * <li>An input CATNurbsCurve or CATPNurbs is directly output: 
 * the <tt>GetResult</tt> method outputs the same pointer.
 * <li>By default, a CATPCurve is retrieved as a CATPNurbs. To force the creation of the corresponding CATNurbsCurve,
 * use the @href CATICGMCrvFittingToNurbsCrv#Set3DCurveCreation method.
 * <li>Some canonic curves/pcurves will be transformed into rational 
 * CATNurbsCurve/CATPNurbs. However, setting <tt>iRationalAllowed = 0</tt> at the operator creation 
 * or using the @href CATICGMCrvFittingToNurbsCrv#SetRationalAllowed method, 
 * will force the fitting into a non rational curve (default is <tt>iRationalAllowed = 1</tt>).
 * <li>The CATEdgeCurve is converted according to the types of its inside curves.
 * </ul>
 * The CATICGMCrvFittingToNurbsCrv operator follows the global frame of the geometric operators: 
 *<ul>
 * <li>A CATICGMCrvFittingToNurbsCrv operator is created with the <tt>CATCGMCreateCrvFittingToNurbsCrv</tt> global function 
 * and must be directly released with the <tt>Release</tt> method after use.
 * It is is not streamable. 
 *<li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed at the operator creation. 
 * In case of <tt>ADVANCED</tt>
 * mode, options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. 
 *<li>In both cases, the result is accessed with the <tt>Getxxx</tt> methods. 
 * If a curve does not need to be converted because it already is of the required type, the same pointer 
 * is returned. In this case, using the @href CATICGMContainer#Remove method on the result curve
 * will remove the input curve, because they are the same.
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATICGMCrvFittingToNurbsCrv: public CATICGMVirtual
{
public:
  /**
   * Constructor
   */
  CATICGMCrvFittingToNurbsCrv();

  /** 
   * Runs <tt>this</tt> operator.
   * <br>To call in <tt>ADVANCED</tt> mode. 
   */
  virtual void Run() = 0;

  /**
   * Imposes the conversion of a CATPCurve in a (3D) CATNurbsCurve.
   * <br>To call in <tt>ADVANCED</tt> mode before the <tt>Run</tt> method.
   * <br>By default (if this method is not called), a CATPCurve is transformed into a CATPNurbs.
   */
  virtual void Set3DCurveCreation() = 0;

  /**
   * Defines whether the result NURBS representation can be rational.
   * <br>To call in <tt>ADVANCED</tt> mode before the <tt>Run</tt> method.
   * @param iAllowRational
   * <tt>1</tt> if the result curve can be rational (default value when the method is not called), 
   * <tt>0</tt> if the result curve must not be rational.
   */
  virtual void SetRationalAllowed(CATLONG32 iAllowRational) = 0;

  /**
   * Declares that the result NURBS must not be periodic.
   * <br>To call in <tt>ADVANCED</tt> mode before the <tt>Run</tt> method.
   */
  virtual void ForbidPeriodicity() = 0;

  /**
   * Declares that the result curve must have the same parameterization than the input curve to fit.
   * <br>To call in <tt>ADVANCED</tt> mode before the <tt>Run</tt> method.
   */
  virtual void ImposeSameParametrization() = 0;

  /**
   * Defines the minimal length of an internal arc of the result curve.
   * <br>To call in <tt>ADVANCED</tt> mode before the <tt>Run</tt> method.
   * @param iInternalMinLength
   * The minimum length value.
   */
  virtual void SetInternalMinLength(double iInternalMinLength) = 0;

  /**
   * Defines the maximum degree of the result NURBS representation.
   * <br>To call in <tt>ADVANCED</tt> mode before the <tt>Run</tt> method.
   * @param iMaxDegree
   * The degree maximum value. 
   */
  virtual void SetMaxDegree(CATLONG32 iMaxDegree) = 0;

  /**
   * Defines the maximum number of arcs of the result curve. 
   * <br>To call in <tt>ADVANCED</tt> mode before the <tt>Run</tt> method.
   * @param iMaxArcs
   * The maximum number of arcs. If <tt>SetMaxDegree</tt> and <tt>SetMaxArcs</tt> are both used, 
   * the operator tries to get as few arcs as possible, even with a larger number of arcs with
   * <tt>MaxDegree</tt>.
   */
  virtual void SetMaxArcs(CATLONG32 iMaxArcs) = 0;

  /**
   * Defines the knot vector to be used for the conversion. 
   * @param iKnotVector
   * The knot vector.
   */
  virtual void ImposeKnotVector(const CATKnotVector *iKnotVector) = 0;

  /**
  * Returns the maximum deviation computed for the result curve.
  * <br> To call after the operator ran.
  * @return
  * The maximum deviation value.
  */
  virtual double GetMaxDeviation() = 0;

  /**
   * Returns whether the transformation between the input and output curves is exact.
   * <br> To call after the operator ran.
   * @return
   * <tt>1</tt> if the transformation is exact, <tt>0</tt> otherwise.
   */
  virtual CATLONG32 IsExactTransformation() = 0;

  /**
  * Maps a parameter on the initial curve to the corresponding parameter on the computed NURBS representation.
  * <br> To call after the operator ran.
  * @param iParamOnCurve
  * The parameter on the initial curve.
  * @return
  * The parameter on the computed NURBS representation.
  */
  virtual CATCrvParam ComputeNewParameter(const CATCrvParam &iParamOnCurve) = 0;

  // ................................
  //  --> 2D Results (PNurbs) 
  // ................................
  /**
 * Returns the result CATPNurbs.
 * @return
 * The pointer to the created CATPNurbs. Use the @href CATICGMContainer#Remove if you do not want
 * to keep it in the geometric factory.
 */
  virtual CATPNurbs *GetPNurbs() = 0;

  //
  // ................................
  //  --> 3D Results (Nurbs curves) 
  // ................................
  /**
 * Returns the result CATNurbsCurve.
 * @return
 * The pointer to the created CATNurbsCurve. Use the @href CATICGMContainer#Remove if you do not want
 * to keep it in the geometric factory.
 */
  virtual CATNurbsCurve *GetNurbsCurve() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMCrvFittingToNurbsCrv(); // -> delete can't be called
};

/**
 * @nodoc
 * @deprecated V5R21 CATCGMCreateCrvFittingToNurbsCrv(CATGeoFactory  *, CATSoftwareConfiguration * ,
 * Creates the geometric operator that computes a (possibly approximated) NURBS representation of a CATCurve.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iCurve
 * The pointer to the curve to convert.
 * @param iLimits
 * The maximum limits to take into account on the input curve.
 * @param iMaxDeviation
 * The maximum deviation between the input and result curves.
 * @param iRationalAllowed
 * <tt>1</tt> if the result curve can be rational, 
 * <tt>0</tt> if the result curve must not be rational.
 * @param iMode
 * The mode of use.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 * @see CATICGMCrvFittingToNurbsCrv
 */
ExportedByCATGMOperatorsInterfaces CATICGMCrvFittingToNurbsCrv *CATCGMCreateCrvFittingToNurbsCrv(
  CATGeoFactory *iFactory,
  const CATCurve *iCurve,
  const CATCrvLimits &iLimits,
  double iMaxDeviation,
  CATLONG32 iRationalAllowed = 1,
  CATSkillValue iMode = BASIC);

/**
 * Creates the geometric operator that computes a (possibly approximated) NURBS representation of a CATCurve.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iSoftwareConfiguration
 * The pointer to the software configuration
 * @param iCurve
 * The pointer to the curve to convert.
 * The curve's length must be bigger than the maximum deviation.
 * @param iLimits
 * The maximum limits to take into account on the input curve.
 * @param iMaxDeviation
 * The maximum deviation between the input and result curves.
 * @param iRationalAllowed
 * <tt>1</tt> if the result curve can be rational, 
 * <tt>0</tt> if the result curve must not be rational.
 * @param iMode
 * The mode of use.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 * @see CATICGMCrvFittingToNurbsCrv
 */
ExportedByCATGMOperatorsInterfaces CATICGMCrvFittingToNurbsCrv *CATCGMCreateCrvFittingToNurbsCrv(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iSoftwareConfiguration,
  const CATCurve *iCurve,
  const CATCrvLimits &iLimits,
  double iMaxDeviation,
  CATLONG32 iRationalAllowed = 1,
  CATSkillValue iMode = BASIC);

#endif /* CATICGMCrvFittingToNurbsCrv_h_ */
