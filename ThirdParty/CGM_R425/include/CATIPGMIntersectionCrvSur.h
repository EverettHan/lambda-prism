#ifndef CATIPGMIntersectionCrvSur_h_
#define CATIPGMIntersectionCrvSur_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @level Protected
 * @usage U3
 */

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"
#include "CATIntersectionSign.h"

class CATCartesianPoint;
class CATCrvLimits;
class CATCrvParam;
class CATCurve;
class CATEdgeCurve;
class CATGeoFactory;
class CATMathBox;
class CATMathSetOfPointsND;
class CATPCurve;
struct CATPipeData;
class CATPointOnCurve;
class CATPointOnSurface;
class CATSurLimits;
class CATSurParam;
class CATSurface;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMIntersectionCrvSur;

//#endif
/**
 * Class defining the operator of the intersection of a curve and a surface.
 *<br>The operator outputs the isolated solutions (points) and the
 * overlapping solutions (curves).
 *<ul>
 *<li>The CATIPGMIntersectionCrvSur operator is created with the <tt>CATPGMCreateIntersection</tt> method and 
 * directly released with the <tt>Release</tt> method.
 * It is is not streamable. 
 *<li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed at the operator creation. 
 * In case of <tt>ADVANCED</tt>
 * mode, options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. The advanced mode also allows you to
 * run the same operator with different curves or surfaces.
 *<li>In both cases, the result is accessed with two specific interators, one for the solution points,
 * the other for the solution curves.
 *</ul>
 */
class ExportedByCATGMModelInterfaces CATIPGMIntersectionCrvSur: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMIntersectionCrvSur();

  //
  //  Getting the isolated intersections between the curve and the surface
  //
  /**
 * Returns the number of isolated solution points of <tt>this</tt> CATIPGMIntersectionCrvSur operator.
 * @return
 * The number of isolated solution points.
 */
  virtual CATLONG32 GetNumberOfPoints() const = 0;

  /**
 * Initializes the iterator of the resulting points.
 *<br>By default, the initialization is performed once the operator runs, 
 * and this is therefore only used to read the solutions again.
 */
  virtual void BeginningPoint() = 0;

  /**
 * Skips to the next solution point of <tt>this</tt> CATIPGMIntersectionCrvSur operator.
 *<br>After <tt>BeginningPoint</tt>, it skips to the first point. 
 * @return
 * The existence of the next solution.
 * <br><b>Legal values</b>:
 *<dl><dt><tt>TRUE</tt> <dd>if there is a solution point
 *    <dt><tt>FALSE</tt> <dd>no more solution point.</dl>
 */
  virtual CATBoolean NextPoint() = 0;

  /**
 * Createss the next solution point of <tt>this</tt> CATIPGMIntersectionCrvSur operator.
 * @return
 * The pointer to the created point. A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 */
  virtual CATCartesianPoint *GetCartesianPoint() = 0;

  /**
 * Creates the next solution point on curve of <tt>this</tt> CATIPGMIntersectionCrvSur operator.
 * @return
 * The pointer to the created point on curve. A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 */
  virtual CATPointOnCurve *GetPointOnCurve() = 0;

  /**
 * Returns the parameter on the curve of the next solution point of <tt>this</tt> CATIPGMIntersectionCrvSur operator.
 * @return
 * The parameter.
 */
  virtual CATCrvParam GetCurveParam() const = 0;

  /**
 * Returns the next solution point on surface of <tt>this</tt> CATIPGMIntersectionCrvSur operator.
 * @return
 * The pointer to the created point on surface. A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 */
  virtual CATPointOnSurface *GetPointOnSurface() = 0;

  /**
 * Returns the parameter on the surface of the next solution point of <tt>this</tt> CATIPGMIntersectionCrvSur operator.
 * @return
 * The parameter.
 */
  virtual CATSurParam GetSurfaceParam() const = 0;

  /**
 * Returns the relative orientation of the curve tangent and the surface normal at the intersection point.
 *<dl><dt><tt>CATIntersectionSignNegative</tt><dd> The scalar product between the curve tangent at the intersection point, 
 * and the surface normal at the intersection point is negative. 
 *    <dt><tt>CATIntersectionSignPositive</tt><dd> The scalar product between the curve tangent at the intersection point, 
 * and the surface normal at the intersection point is positive. 
 *</dl>
 */
  virtual CATIntersectionSign GetSignatureOn() const = 0;

  //
  //  Getting the confusion solution
  //
  /**
 * Returns the number of solution curves of <tt>this</tt> CATIPGMIntersectionCrvSur operator.
 * @return
 * The number of solution curves.
 */
  virtual CATLONG32 GetNumberOfCurves() const = 0;

  /**
 * Initializes the iterator of the solution curves of <tt>this</tt> 
 * CATIPGMIntersectionCrvSur operator.
 *<br>By default, the initialization is performed once the operator runs, 
 * and this is therefore only used to read the solutions again.
 */
  virtual void BeginningCurve() = 0;

  /**
 * Skips to the next solution curve of <tt>this</tt> CATIPGMIntersectionCrvSur operator.
 *<br>After <tt>BeginningCurve</tt>, it skips to the first curve. 
 * @return
 * The existence of the next solution.
 * <br><b>Legal values</b>:
 *<dl><dt><tt>TRUE</tt> <dd>if there is a solution curve
 *    <dt><tt>FALSE</tt> <dd>no more solution curve.</dl>
 */
  virtual CATBoolean NextCurve() = 0;

  /**
 * Creates the next solution curve of <tt>this</tt> CATIPGMIntersectionCrvSur operator.
 * @return
 * The pointer to the created curve on surface. A new curve is created each time this method is called.
 * If you do not want to keep the created curve, use the @href CATICGMContainer#Remove method.
 */
  virtual CATPCurve *GetPCurve() = 0;

  /**
 *@nodoc
 * Returns the marching points of the next resulting PCurve of a
 * CATIPGMIntersectionCrvSur operator.
 *<br>Creates the object if necessary.
 */
  virtual CATMathSetOfPointsND *GetSetOfPoints() const = 0;

  /**
 * Creates the next solution curve as an edge curve.
 * @return
 * The pointer to the created edge curve, composed of a part of the initial curve, and the corresponding
 * part as a curve on the surface. 
 * A new curve is created each time this method is called.
 * If you do not want to keep the created curve, use the @href CATICGMContainer#Remove method.
 */
  virtual CATEdgeCurve *GetEdgeCurve() = 0;

  /**
 * Returns the domain of the next resulting curve of <tt>this</tt>
 * CATIPGMIntersectionCrvSur operator.
 * @return
 * The corresponding limitations.
 */
  virtual CATCrvLimits GetCurveBoundaries() const = 0;

  /**
 * @nodoc
 * Modifies the tolerance of points confusion for <tt>this</tt> CATIPGMIntersectionCrvSur operator.
 * (<tt>ADVANCED</tt> mode).
 */
  virtual void SetTolerance(const double tolerance) = 0;

  /**
 * Modifies the curve domain to take into account for <tt>this</tt> CATIPGMIntersectionCrvSur
 * operator (<tt>ADVANCED</tt> mode).
 *<br> It does not change the current curve 
 * limitations.  
 * @param iNewLimits
 * The new limitations of the curve.
 */
  virtual void SetLimits(const CATCrvLimits &iNewLimits) = 0;

  /**
 * Modifies the surface domain to take into account for <tt>this</tt> CATIPGMIntersectionCrvSur
 * operator (<tt>ADVANCED</tt> mode).
 *<br> It does not change the current surface 
 * limitations. 
 * @param iNewLimits
 * The new limitations of the surface.
 */
  virtual void SetLimits(const CATSurLimits &iNewLimits) = 0;

  /**
 * Defines the intersection with another curve (<tt>ADVANCED</tt> mode).
 * @param iNewCurve
 * The pointer to the new curve.
 */
  virtual void SetCurve(const CATCurve *iNewCurve) = 0;

  /**
 * Defines the intersection with another second surface (<tt>ADVANCED</tt> mode).
 * @param iNewSurface
 * The pointer to the new surface.
 */
  virtual void SetSurface(const CATSurface *iNewSurface) = 0;

  /**
 * @nodoc
 * Asks to the CATIPGMIntersectionCrvSur to get the solutions at the same geometric
 * 3D point and with different paramters.
 * Do not use.
 */
  virtual void SetEliminationOn() = 0;

  /**
 * @nodoc
 * Asks to the CATIPGMIntersectionCrvSur to get one of the solutions at 
 * the same geometrical location and with different parameters.
 * Do not use.
 */
  virtual void SetEliminationOff() = 0;

  /**
 * @nodoc
 * Asks CATIPGMIntersectionCrvSur to operate on the extremities of the operands.
 * (<tt>ADVANCED</tt> mode)
 */
  virtual void FindExtremitiesOn() = 0;

  /**
 * @nodoc
 * Asks CATIPGMIntersectionCrvSur not to operate on the extremities of the operands.
 * (<tt>ADVANCED</tt> mode)
 */
  virtual void FindExtremitiesOff() = 0;

  /**
 * @nodoc
 * Asks CATIPGMIntersectionCrvSur to operate inside the box limitations.
 * (<tt>ADVANCED</tt> mode)
 * All solutions are in the box, if there are any.
 * @param i3DBox
 * The 3D Box in which to operate.
 */
  virtual void SearchInBox(const CATMathBox &i3DBox) = 0;

  //#ifdef CATIAV5R14
  /**
    * @nodoc
	* Checks if a confusion exists between iCrvParam1 and iSurParam1 
	* and between iCrvParam2 and iSurParam2. 
	* <br>This method is called internally by operator when option has been set with 
	* SetTryOnlyConfusion method.
	* @param iCrvParam1
	* The first point parameter on curve.
	* @param iCrvParam2
	* The second point parameter on curve.
	* @param iSurParam1
	* The first point parameter on surface.
	* @param iSurParam2
	* The second parameter on surface.
    */
  virtual void TryOnlyConfusion(
    const CATCrvParam &iCrvParam1,
    const CATSurParam &iSurParam1,
    const CATCrvParam &iCrvParam2,
    const CATSurParam &iSurParam2) = 0;

  /**
    * @nodoc
	* Do not use.
    */
  virtual void SetConfusionBetweenZerosOff() = 0;

  /**
    * @nodoc
	* Authorize intersection with Surface Borders.
	* (<tt>ADVANCED</tt> mode)
	* <br>By default this option is unset for operator.
    * @param iBorderSolution
	* <br><b>Legal values</b>:
    * <dl><dt><tt>TRUE</tt></dt><dd> Intersection with borders allowed.
    *     <dt><tt>FALSE</tt></dt><dd> Intersection with border not allowed. </dl>
    */
  virtual void SetBorderSolutions(CATBoolean iBorderSolution = 1) = 0;

  /**
    * @nodoc
	* Remove points at confusion extremities.
	* (<tt>ADVANCED</tt> mode)
	* <br>By default this option is unset for operator.
    * @param iNoPointAtConfusionExtremity
	* <br><b>Legal values</b>:
    * <dl><dt><tt>TRUE</tt> </dt><dd> Remove points.
    *     <dt><tt>FALSE</tt></dt><dd> Don't remove points.</dl>
    */
  virtual void SetNoPointAtConfusionExtremity(
    CATBoolean iNoPointAtConfusionExtremity = 1) = 0;

  /**
    * @nodoc
	* Authorize mixed result in case of mixed solution.
	* <br>By default result is a point.
	* (<tt>ADVANCED</tt> mode)
    */
  virtual void SetMixedSolutionOfCrossingTreatment() = 0;

  /**
    * @nodoc
	* Disable use of "EasySolver" used for performance reasons on expensive surfaces.
	* (<tt>ADVANCED</tt> mode)
	* <br>By default, EasySolver is used.
    */
  virtual void SetExpensiveSurface() = 0;

  /**
    * @nodoc
	* Checks if a confusion was found in result.
    * @return
    * <br><b>Legal values</b>:
    * <dl><dt><tt>TRUE</tt></dt><dd>There is a confusion in result.
    *     <dt><tt>FALSE</tt</dt><dd>There isn't a confusion in result.</dl>
    */
  virtual CATBoolean IsMixedSolution() = 0;

  /**
    * @nodoc
	* Enables quick detection of non intersection in the case of a pipe.
	* (<tt>ADVANCED</tt> mode)
    * @param iPipeData
	* The PipeData of the surface to intersect.
    */
  virtual void SetPipeData(CATPipeData *iPipeData) = 0;

  /**
    * @nodoc
	* Specify inits in a CATMathSetOfPoints of dimension 3.
	* (<tt>ADVANCED</tt> mode)
    *  <br>These inits consists in all the inits of the following type :
	* <ul>
    * <li> Curve extremities which are admissible in the surface.
    * <li> Solution of the intersection between the curve and frontier of surfaces.
	* </ul>
    * If admissable inits have been set, operator does not look for other inits .
    * @param iInits
	* The set of admissable init points.
    */
  virtual void SetAdmissibleInits(const CATMathSetOfPointsND &iInits) = 0;

  /**
    * @nodoc
	* Checks if Curve result is linear.
	* <br>To be used within Curve iterator.
	* @return
    * <br><b>Legal values</b>:
    * <dl><dt><tt>TRUE</tt> </dt><dd>Curve is linear.
    *     <dt><tt>FALSE</tt></dt><dd>Curve isn't linear. </dl>
    */
  virtual CATBoolean IsLinearSol() const = 0;

  /**
    * @nodoc
	* Gets construction data of a PCurve result when the solution is quintic.
	* <br>To be used within Curve iterator.
	* @param oPointsForQuintic
	* @param oTangentsForQuintic
	* @param oSecondDerivForQuintic
    */
  virtual CATBoolean GetDataForQuintic(
    CATMathSetOfPointsND &oParamsForQuintic,
    CATMathSetOfPointsND &oPointsForQuintic,
    CATMathSetOfPointsND &oTangentsForQuintic,
    CATMathSetOfPointsND &oSecondDerivForQuintic) const = 0;

  /**
    * @nodoc
	* Get relative orientation of Curve result.
    * <br>To be used within Curve iterator.
	* @return
	* <br><b>Legal values</b>:
    * <dl><dt><tt>1</tt> </dt><dd>Same orientation as input Curve.
    *     <dt><tt>-1</tt></dt><dd>Opposite orientation from input Curve. </dl>
    */
  virtual CATLONG32 GetRelativeOrientation() const = 0;

  /**
    * @nodoc
	* Gets the domain of the Curve result. 
    * <br>To be used within Curve iterator.
    * @param oStartParam 
	* First limit.
    * @param oEndParam
	* End limit.
    */
  virtual void GetCurveBoundaries(
    CATCrvParam &oStartParam,
    CATCrvParam &oEndParam) const = 0;

  /**
    * @nodoc
	* Set try only confusion option in order to check if a confusion exists 
    * between iCrvParam1 and iSurParam1 and between iCrvParam2 and iSurParam2 
	* (<tt>ADVANCED</tt> mode).
	* <br>By default this option is unset for operator.
	* @param iCrvParam1
	* The first point parameter on curve.
	* @param iSurParam1
	* The first point parameter on surface.
	* @param iCrvParam2
	* The second point parameter on curve.
	* @param iSurParam2
	* The second point parameter on surface.
    * @param iConf
	* <br><b>Legal values</b>:
    * <dl><dt><tt>1</tt></dt><dd> Option is set.
    *     <dt><tt>0</tt></dt><dd> Option is unset.  </dl>
    */
  virtual void SetTryOnlyConfusion(
    const CATCrvParam &iCrvParam1,
    const CATSurParam &iSurParam1,
    const CATCrvParam &iCrvParam2,
    const CATSurParam &iSurParam2,
    CATBoolean iConf = 1) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMIntersectionCrvSur(); // -> delete can't be called
};

#endif /* CATIPGMIntersectionCrvSur_h_ */
