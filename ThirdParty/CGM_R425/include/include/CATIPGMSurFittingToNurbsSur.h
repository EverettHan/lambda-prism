#ifndef CATIPGMSurFittingToNurbsSur_h_
#define CATIPGMSurFittingToNurbsSur_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMVirtual.h"
#include "CATDataType.h"
#include "CATBoolean.h"
#include "CATSkillValue.h"

class CATFrFNurbsBipar;
class CATNurbsSurface;
class CATSoftwareConfiguration;
class CATSurParam;
class CATSurLimits;
class CATGeoFactory;
class CATSurface;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMSurFittingToNurbsSur;

/**
 * Class defining a geometric operator that computes a (possibly approximated) NURBS representation of a CATSurface.
 * <br>If a surface has no corresponding NURBS representation, the operator uses a fitting operation to
 * compute the best approximating NURBS representation. Hence, a maximum deviation must be given as input of 
 * the operator. 
 * <ul>
 * <li>An input CATNurbsSurface is directly output: 
 * the <tt>GetResult</tt> method outputs the same pointer.
 * <li>Some canonic surfaces will be transformed into rational 
 * CATNurbsSurface. However, setting <tt>iRationalAllowed = 0</tt> at the operator creation 
 * or using the @href CATIPGMCrvFittingToNurbsCrv#SetRationalAllowed method, 
 * will force the fitting into a non rational surface (default is <tt>iRationalAllowed = 1</tt>).
 * </ul>
 * The CATIPGMSurFittingToNurbsSur operator follows the global frame of the geometric operators: 
 *<ul>
 * <li>A CATIPGMSurFittingToNurbsSur operator is created with the <tt>CATPGMCreateSurFittingToNurbsSur</tt> global function 
 * and must be directly released with the <tt>Release</tt> method after use.
 * It is is not streamable. 
 *<li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed at the operator creation. 
 * In case of <tt>ADVANCED</tt>
 * mode, options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. 
 *<li>In both cases, the result is accessed with the <tt>Getxxx</tt> methods. 
 * If a surface does not need to be converted because it already is of the required type, the same pointer 
 * is returned. In this case, using the @href CATICGMContainer#Remove method on the result surface
 * will remove the input surface, because they are the same.
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMSurFittingToNurbsSur: public CATIPGMVirtual
{
public:
  /**
   * Constructor
   */
  CATIPGMSurFittingToNurbsSur();

  /** 
   * Runs <tt>this</tt> operator.
   * <br>To call in <tt>ADVANCED</tt> mode. 
   */
  virtual void Run() = 0;

  /**
   * Defines whether the result NURBS representation can be rational.
   * <br>To call in <tt>ADVANCED</tt> mode before the <tt>Run</tt> method.
   * @param iAllowRational
   * <tt>1</tt> if the result surface can be rational (default value when the method is not called), 
   * <tt>0</tt> if the result surface must not be rational.
   */
  virtual void SetRationalAllowed(CATLONG32 iAllowRational) = 0;

  /**
   * Declares that the result surface must have the same parameterization than the input surface to fit.
   * <br>To call in <tt>ADVANCED</tt> mode before the <tt>Run</tt> method.
   */
  virtual void ImposeSameParametrization() = 0;

  /**
   * Declares that the result NURBS must not be periodic.
   * <br>To call in <tt>ADVANCED</tt> mode before the <tt>Run</tt> method.
   */
  virtual void ForbidPeriodicity() = 0;

  /**
   * @nodoc
   * Defines the maximum limits to take into account on the input surface.
   * <br>To call in <tt>ADVANCED</tt> mode before the <tt>Run</tt> method.
   * @param iMaxLimits
   * The maximum limits.
   */
  virtual void SetMaxLimits(const CATSurLimits *iLimitsToFit) = 0;

  /** 
 * @nodoc 
 * Do not use. Use the SetMaxLimits
 */
  virtual void SetLimitsToFit(CATSurLimits *iLimitsToFit) = 0;

  /**
   * @nodoc
   * Defines the maximum deviation between the input surface and the result surface.
   * <br>To call in <tt>ADVANCED</tt> mode before the <tt>Run</tt> method.
   * @param iMaxDeviation
   * The maximum deviation value.
   */
  virtual void SetMaxDeviation(double iMaxDeviation) = 0;

  /**
   * Defines the minimal length of an internal arc of the result surface.
   * <br>To call in <tt>ADVANCED</tt> mode before the <tt>Run</tt> method.
   * @param iInternalMinLength
   * The minimum length value.
   */
  virtual void SetInternalMinLength(double iInternalMinLength) = 0;

  /**
   * Forces the computation of an approximation even if the input surface already match the fitting criteria.
   * <br>To call in <tt>ADVANCED</tt> mode before the <tt>Run</tt> method.
   */
  virtual void ForceFitting() = 0;

  /**
   * Defines the maximum degree of the result NURBS representation in the first direction of the surface.
   * <br>To call in <tt>ADVANCED</tt> mode before the <tt>Run</tt> method.
   * @param iMaxDegree
   * The degree maximum value. 
   */
  virtual void SetMaxDegreeU(CATLONG32 iMaxDegree) = 0;

  /**
   * Defines the maximum number of arcs of the result NURBS representation in the first direction of the surface. 
   * <br>To call in <tt>ADVANCED</tt> mode before the <tt>Run</tt> method.
   * @param iMaxArcs
   * The maximum number of arcs. If <tt>SetMaxDegreeU</tt> and <tt>SetMaxArcsV</tt> are both used, 
   * the operator tries to get as few arcs as possible, even with a larger number of arcs with
   * <tt>iMaxDegree</tt>.
   */
  virtual void SetMaxSegmentsU(CATLONG32 iMaxArcs) = 0;

  /**
   * Defines the maximum degree of the result NURBS representation in the second direction of the surface.
   * <br>To call in <tt>ADVANCED</tt> mode before the <tt>Run</tt> method.
   * @param iMaxDegree
   * The degree maximum value. 
   */
  virtual void SetMaxDegreeV(CATLONG32 iMaxDegree) = 0;

  /**
   * Defines the maximum number of arcs of the result NURBS representation in the second direction of the surface. 
   * <br>To call in <tt>ADVANCED</tt> mode before the <tt>Run</tt> method.
   * @param iMaxArcs
   * The maximum number of arcs. If <tt>SetMaxDegreeV</tt> and <tt>SetMaxArcsV</tt> are both used, 
   * the operator tries to get as few arcs as possible, even with a larger number of arcs with
   * <tt>iMaxDegree</tt>.
   */
  virtual void SetMaxSegmentsV(CATLONG32 iMaxArcs) = 0;

  /**
  * Returns the maximum deviation computed for the result surface.
  * <br> To call after the operator ran.
  * @return
  * The maximum deviation value.
  */
  virtual double GetMaxDeviation() = 0;

  /**
   * Returns whether the transformation between the input and output surfaces is exact.
   * <br> To call after the operator ran.
   * @return
   * <tt>1</tt> if the transformation is exact, <tt>0</tt> otherwise.
   */
  virtual CATLONG32 IsExactTransformation() = 0;

  /**
  * Maps a parameter on the initial surface to the corresponding parameter on the computed NURBS representation.
  * <br> To call after the operator ran.
  * @param iParamOnSurface
  * The parameter on the initial surface.
  * @return
  * The parameter on the computed NURBS representation.
  */
  virtual CATSurParam ComputeNewParameter(const CATSurParam &iParamOnSurface) = 0;

  //
  // ................................
  //  --> Result (Nurbs Surfaces) 
  // ................................
  /**
 * Returns the result CATNurbsSurface.
 * @return
 * The pointer to the created CATNurbsSurface. Use the @href CATICGMContainer#Remove if you do not want
 * to keep it in the geometric factory.
 */
  virtual CATNurbsSurface *GetNurbsSurface() = 0;

  //
  // ............................................
  //  --> Bipar Result 
  // ............................................
  /** @nodoc */
  virtual CATFrFNurbsBipar *GetNurbsBipar() = 0;

  /** @nodoc */
  virtual void SetMaxDegreeForExactTransformation(
    CATLONG32 iMaxDegreeForExactTransformation) = 0;

  /** @nodoc */
  virtual void SetInternalContinuity(int iInternalContinuity) = 0;

  /** @nodoc */
  virtual void SetKindOfFit(int iKindOfFit) = 0;

  /** @nodoc */
  virtual int CheckResult(int iPrint = 0) = 0;

  /** 
 * Returns a diagnosis about the fitting process.
 * <br>To call after the <tt>Run</tt> method.
 *@return
 *1 if a correct result could not be computed because it would have produced small patches
 *0 otherwise
 */
  virtual CATLONG32 GetDiagnosis() = 0;

  /**
 * @nodoc
 * By Default: either no desextrapolation or complete desextrapolation (original state restored).
 * If this method is called: allow to remove only one or several patches;
 */
  virtual void AllowPartialDesextrapolation() = 0;

  /**
 * Specifies a continuity constraint along the borders of the surface.
 * <ul>
 * <li> 0 for C0 (default)
 * <li> 1 for C1
 * <li> 2 for C2
 * </ul>
 * @param iSideContinuityU
 * The continuity along U. 
 * @param iSideContinuityV
 * The continuity along V. 
 */
  virtual void SetSideContinuity(int iSideContinuityU, int iSideContinuityV) = 0;

  /** @nodoc */
  virtual void SetTrimOption(CATBoolean iTrimToLimits) = 0;

  /**
 *@nodoc
 *Set the maximum useful deviation.
 *Must be greater than the tolerance.
 *If during the approximation algorithm, we realize that it is not possible to find a result
 *achieving a deviation smaller than iMaxUsefulDeviation while complying with the specifications
 *(max degrees, max arcs, ...), then the algorithm is stopped and the current result is 
 *returned, without exhausting the maximum number of arcs.
 *The purpose of this option is to avoid CATLONG32 CPU time while trying to approximate invalid or
 *too complex surfaces when we know that the result will be useless anyway.
 *
 *Default: -1. (inactive)
 */
  virtual void SetMaxUsefulDeviation(double iMaxUsefulDeviation) = 0;

  /**
 * @nodoc
*/
  virtual void SetOriginalLimitsMode() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMSurFittingToNurbsSur(); // -> delete can't be called
};

/**
 * @deprecated V5R21 CATPGMCreateSurFittingToNurbsSur(CATGeoFactory  *, CATSoftwareConfiguration * ,
 * Creates the geometric operator that computes a (possibly approximated) NURBS representation of a CATSurface.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iSurface
 * The pointer to the surface to convert.
 * @param iLimits
 * The limits defining the portion of the input surface to be converted into a NURBS. These limits are
 * not necessarily the maximum limits.
 * @param iMaxDeviation
 * The maximum deviation between the input and result surfaces.
 * @param iRationalAllowed
 * <tt>1</tt> if the result surface can be rational, 
 * <tt>0</tt> if the result surface must not be rational.
 * @param iMode
 * The mode of use.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 * @see CATIPGMSurFittingToNurbsSur
 */
ExportedByCATGMOperatorsInterfaces CATIPGMSurFittingToNurbsSur *CATPGMCreateSurFittingToNurbsSur(
  CATGeoFactory *iFactory,
  const CATSurface *iSurface,
  const CATSurLimits &iLimits,
  double iMaxDeviation,
  CATLONG32 iRationalAllowed = 1,
  CATSkillValue iMode = BASIC);

/**
 * Creates the geometric operator that computes a (possibly approximated) NURBS representation of a CATSurface.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iSoftwareConfiguration
 * The pointer to the software configuration
 * @param iSurface
 * The pointer to the surface to convert.
 * @param iLimits
 * The maximum limits to take into account on the input surface.
 * @param iMaxDeviation
 * The maximum deviation between the input and result surfaces.
 * If less than the resolution, quality of result is not guarenteed.
 * @param iRationalAllowed
 * <tt>1</tt> if the result surface can be rational, 
 * <tt>0</tt> if the result surface must not be rational.
 * @param iMode
 * The mode of use.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 * @see CATIPGMSurFittingToNurbsSur
 */
ExportedByCATGMOperatorsInterfaces CATIPGMSurFittingToNurbsSur *CATPGMCreateSurFittingToNurbsSur(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iSoftwareConfiguration,
  const CATSurface *iSurface,
  const CATSurLimits &iLimits,
  double iMaxDeviation,
  CATLONG32 iRationalAllowed = 1,
  CATSkillValue iMode = BASIC);

#endif /* CATIPGMSurFittingToNurbsSur_h_ */
