#ifndef CATIPGMLiss_h_
#define CATIPGMLiss_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMVirtual.h"
#include "CATDataType.h"

class CATMathSetOfPointsND;
class CATNurbsCurve;
class CATPNurbs;
class CATFrFNurbsMultiForm;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMLiss;

/**
 * @level Protected
 * @usage U1
 */
/**
 * Class defining a geometric operator that smoothes a set of points to create a curve.
 * <br>The CATIPGMLiss operator follows the global frame of the geometric operators: 
 *<ul>
 * <li>A CATIPGMLiss operator is created with the <tt>CATPGMCreateLiss</tt> global method 
 * and must be
 * directly released with the <tt>Release</tt> method after use.
 * It is is not streamable. 
 *<li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed at the operator creation. 
 * In case of <tt>ADVANCED</tt>
 * mode, options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. 
 *<li>In both cases, the result is accessed with the <tt>Getxxx</tt> methods. 
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMLiss: public CATIPGMVirtual
{
public:
  /**
   * Constructor
   */
  CATIPGMLiss();

  /**
 * Runs <tt>this</tt> operator (<tt>ADVANCED</tt> mode).
 */
  virtual void Run() = 0;

  /**
 * Sets the arcs limits at the constrained points (<tt>ADVANCED</tt> mode).
 * <br>The constraints points are defined by the <tt>SetSoftContinuity</tt> method.
 */
  virtual void SetTwinOption() = 0;

  /**
 * Defines the continuity constraints on given points (<tt>ADVANCED</tt> mode).
 * @param iNbOfRanks
 * The number of constrained points.
 * @param iRanks
 * The array of the ranks (beginning at 1) of the constrained points.
 * @param iContinuityOrder
 * The array of the corresponding continuity constraints.
 * <br><b>Legal values</b>:
 * <tt>0</tt> for a C0 continuity, <tt>1</tt> for a C1 continuity, 
 * <tt>2</tt> for a C2 continuity. 
 */
  virtual void SetSoftContinuity(
    CATLONG32 &iNbOfRanks,
    CATLONG32 *iRanks,
    CATLONG32 *iContinuityOrder) = 0;

  /**
 * Defines the degree of the resulting curve (<tt>ADVANCED</tt> mode).
 * @param iDegree
 * The degree value.
 */
  virtual void SetDegree(CATLONG32 &iDegree) = 0;

  /**
 * Defines the parameters corresponding to each point of the initial set of points (<tt>ADVANCED</tt> mode).
 * @param iParameter
 * The array of the parameter values that correspond on the smoothed curve to
 * each point of the input set.
 */
  virtual void SetImposedParametrization(double *iParameter) = 0;

  /**
 * @nodoc
 */
  virtual void AddForm(CATMathSetOfPointsND *Pts, CATLONG32 &ityp) = 0;

  /**
 * Defines a new set of points to be taken into account (<tt>ADVANCED</tt> mode).
 * @param iPts
 * The pointer to the new set of points. 
 */
  virtual void UpdateForm(CATMathSetOfPointsND *iPts) = 0;

  /**
 * @nodoc
 */
  virtual void KeepTangentsNorms() = 0;

  /**
 * Defines the maximum number of arcs of the created curve (<tt>ADVANCED</tt> mode).
 * @param iMaxNumber
 * The maximum number of arcs of the created curve
 */
  virtual void SetMaxNumberOfArcs(CATLONG32 iMaxNumber) = 0;

  /**
 * Returns the created smoothed curve.
 * @return
 * The pointer to the created smoothed curve. If you do not want to keep it, use
 * the @href CATICGMContainer#Remove method.
 */
  virtual CATNurbsCurve *GetResult() = 0;

  /**
 * Returns the created smoothed Pcurve.
 * @return
 * The pointer to the created smoothed Pcurve. If you do not want to keep it, use
 * the @href CATICGMContainer#Remove method.
 */
  virtual CATPNurbs *GetPResult() = 0;

  /**
	 * @nodoc
	 */
  virtual CATFrFNurbsMultiForm *GetMultiForm() = 0;

  /**
	 * @nodoc
	 */
  virtual CATFrFNurbsMultiForm *GetInterpolForm() = 0;

  /**
	 * Returns the maximum deviation between a point and the smoothed curve.
	 * @return
	 * The maximum deviation value.
	 */
  virtual double GetMaxDeviation() = 0;

  /**
	 * Returns the parameters associated to each point .
	 * @return
	 * The parameters.
	 */
  virtual double *GetParameters() = 0;

  /**
	 * @nodoc
	 */
  virtual void SetSmoothingFactor(double iSmoothingFactor) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMLiss(); // -> delete can't be called
};

#endif /* CATIPGMLiss_h_ */
