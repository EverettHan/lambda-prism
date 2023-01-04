#ifndef CATIPGMCrvFittingToNurbsCrv_h_
#define CATIPGMCrvFittingToNurbsCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @level Protected
 * @usage U3
 */

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMVirtual.h"
#include "CATDataType.h"
#include "CATSkillValue.h"
#include "CATFreeFormDef.h"

class CATCrvLimits;
class CATCrvParam;
class CATFrFNurbsMultiForm;
class CATNurbsCurve;
class CATPNurbs;
class CATSoftwareConfiguration;
class CATGeoFactory;
class CATCurve;
class CATKnotVector;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMCrvFittingToNurbsCrv;

/**
 * Class defining a geometric operator that computes a (possibly approximated) NURBS representation of a CATCurve.
 * <br>If a curve has no corresponding NURBS representation, the operator uses a fitting operation to
 * compute the best approximating NURBS representation. Hence, a maximum deviation must be given as input of 
 * the operator. 
 * <ul>
 * <li>An input CATNurbsCurve or CATPNurbs is directly output: 
 * the <tt>GetResult</tt> method outputs the same pointer.
 * <li>By default, a CATPCurve is retrieved as a CATPNurbs. To force the creation of the corresponding CATNurbsCurve,
 * use the @href CATIPGMCrvFittingToNurbsCrv#Set3DCurveCreation method.
 * <li>Some canonic curves/pcurves will be transformed into rational 
 * CATNurbsCurve/CATPNurbs. However, setting <tt>iRationalAllowed = 0</tt> at the operator creation 
 * or using the @href CATIPGMCrvFittingToNurbsCrv#SetRationalAllowed method, 
 * will force the fitting into a non rational curve (default is <tt>iRationalAllowed = 1</tt>).
 * <li>The CATEdgeCurve is converted according to the types of its inside curves.
 * </ul>
 * The CATIPGMCrvFittingToNurbsCrv operator follows the global frame of the geometric operators: 
 *<ul>
 * <li>A CATIPGMCrvFittingToNurbsCrv operator is created with the <tt>CATPGMCreateCrvFittingToNurbsCrv</tt> global function 
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
class ExportedByCATGMOperatorsInterfaces CATIPGMCrvFittingToNurbsCrv: public CATIPGMVirtual
{
public:
  /**
   * Constructor
   */
  CATIPGMCrvFittingToNurbsCrv();

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
   * @nodoc
   * @deprecated
   * DO NOT USE -- USE MAX DEGREE
   * @param iDegree
   * The degree value. 
   */
  virtual void SetDegree(CATLONG32 iDegree) = 0;

  /**
   * @nodoc
   * @deprecated
   * DO NOT USE -- SPECIFY LIMITS IN CONSTRUCTOR
   * Defines the maximum limits to take into account on the input curve.
   * <br>To call in <tt>ADVANCED</tt> mode before the <tt>Run</tt> method.
   * @param iMaxLimits
   * The maximum limits.
   */
  virtual void SetMaxLimits(const CATCrvLimits &iMaxLimits) = 0;

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
   * @nodoc
   * Defines the maximum deviation between the input curve and the result curve.
   * <br>To call in <tt>ADVANCED</tt> mode before the <tt>Run</tt> method.
   * @param iMaxDeviation
   * The maximum deviation value.
   */
  virtual void SetMaxDeviation(double iMaxDeviation) = 0;

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

  /** @nodoc 
   * Operator does not try to do an exact conversion but calls directly fitting operation 
   * to compute the best approximating NURBS representation.
   */
  virtual void ForceFitting() = 0;

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

  //
  // ............................................
  //  --> MultiForm Results (2D or 3D MultiForm) 
  // ............................................
  /** 
 * @nodoc
 *  Getting the CATFrFNurbsMultiForm result (with Active Split inside 
 *  curve (to convert) limits.
 */
  virtual CATFrFNurbsMultiForm *GetNurbsMultiForm() = 0;

  /** @nodoc 
   *  Getting the CATFrFNurbsMultiForm result without using curve limits. 
   */
  virtual CATFrFNurbsMultiForm *GetUntrimmedNurbsMultiForm() = 0;

  /**
	* @nodoc
    * Sets the continuity constraint at the extremities of the curve.
    * @param iSideContinuity
    * The continuity constraint.
	* <tt>CATFrFTangentCont</tt> : Tangent continuity. 
    * <tt>CATFrFCurvatureCont</tt> : Curvature continuity.
	*/
  virtual void SetSideContinuity(CATFrFContinuity iSideContinuity) = 0;

  /** @nodoc 
   * For debug purpose.
   * @param iPrint
   * <tt>0</tt> : No traces. 
   * <tt>1</tt> : dumps results in output traces.
   */
  virtual int CheckResult(int iPrint = 0) = 0;

  /** @nodoc 
   * Different computation and smoothing methods.
   * @param iKindOfFit
   * The computation method.
   * <tt>0</tt> : V5 smoothing.
   * <tt>1</tt> : V4 smoothing.
   * <tt>4</tt> : default.
   * <tt>5</tt> 
   * <tt>6</tt>  
   */
  virtual void SetKindOfFit(int iKindOfFit) = 0;

  /** @nodoc 
   * Do not use (same as ImposeSameParametrization())
   */
  virtual void ImposeSameParametrization(CATCrvLimits *NewLimits) = 0;

  /** @nodoc 
   * Same as SetMaxDegree but does not minimize the number of arcs.
   * @param iMaxDegree
   * The degree maximum value. 
   */
  virtual void SetMaxDegreeForExactTransformation(
    CATLONG32 iMaxDegreeForExactTransformation) = 0;

  /** @nodoc 
   * Set type of internal continuity.
   * @param iInternalContinuity
   * <tt>1</tt> : tangent continuity.
   * <tt>2</tt> : curvature continuity (default)
   */
  virtual void SetInternalContinuity(int iInternalContinuity) = 0;

  /**
   *@nodoc
   * Concerns deviation calculation method in the cas of 2D result.
   */
  virtual void SetDeviationComputationIn3D() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMCrvFittingToNurbsCrv(); // -> delete can't be called
};

/**
 * @deprecated V5R21 CATPGMCreateCrvFittingToNurbsCrv(CATGeoFactory  *, CATSoftwareConfiguration * ,
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
 * @see CATIPGMCrvFittingToNurbsCrv
 */
ExportedByCATGMOperatorsInterfaces CATIPGMCrvFittingToNurbsCrv *CATPGMCreateCrvFittingToNurbsCrv(
  CATGeoFactory *iFactory,
  const CATCurve *iCurve,
  const CATCrvLimits &iLimits,
  double iMaxDeviation,
  CATLONG32 iRationalAllowed = 1,
  CATSkillValue iMode = BASIC);

/**
 * @nodoc
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
 * @see CATIPGMCrvFittingToNurbsCrv
 */
ExportedByCATGMOperatorsInterfaces CATIPGMCrvFittingToNurbsCrv *CATPGMCreateCrvFittingToNurbsCrv(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iSoftwareConfiguration,
  const CATCurve *iCurve,
  const CATCrvLimits &iLimits,
  double iMaxDeviation,
  CATLONG32 iRationalAllowed = 1,
  CATSkillValue iMode = BASIC);

#endif /* CATIPGMCrvFittingToNurbsCrv_h_ */
