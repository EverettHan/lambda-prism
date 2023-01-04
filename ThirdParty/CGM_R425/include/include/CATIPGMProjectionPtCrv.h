#ifndef CATIPGMProjectionPtCrv_h_
#define CATIPGMProjectionPtCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @level Protected
 * @usage U3
 */

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"

class CATCartesianPoint;
class CATCrvLimits;
class CATCrvParam;
class CATGeoFactory;
class CATMathPoint;
class CATPointOnCurve;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMProjectionPtCrv;

/**
 * Class defining the operator of projection of a CATPoint onto a
 * CATCurve.
 *<br> The projection can be orthogonal or directional.
 * The resulting objects are points.
 *<ul>
 *<li>The CATIPGMProjectionPtCrv operator is created with the <tt>CreateProjection</tt> method and 
 * directly released with the <tt>Release</tt> method.
 * It is is not streamable. 
 *<li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed at the operator creation. 
 * In case of <tt>ADVANCED</tt>
 * mode, options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. The advanced mode also allows you to
 * run the same operator with different points.
 *<li>In both cases, the result is accessed with a specific interator.
 *</ul>
 */
class ExportedByCATGMModelInterfaces CATIPGMProjectionPtCrv: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMProjectionPtCrv();

  /**
 * Returns the maximum orthogonal distance between the CATCurve and the 
 * CATPoint.
 * @return
 * The distance.
 */
  virtual double GetDistance() const = 0;

  /**
 * Returns the number of solution points of <tt>this</tt> CATIPGMProjectionPtCrv operator.
 * @return
 * The number of solution points.
 */
  virtual CATLONG32 GetNumberOfPoints() const = 0;

  /**
 * Initializes the iterator of the resulting points.
 *<br>By default, the initialization is performed once the operator runs, 
 * and this is therefore only used to read the solutions again.
 */
  virtual void BeginningPoint() = 0;

  /**
 * Skips to the next solution point of <tt>this</tt> CATIPGMProjectionPtCrv operator.
 *<br>After <tt>BeginningPoint</tt>, it skips to the first point. 
 * @return
 * The existence of the next solution.
 * <br><b>Legal values</b>:
 *<dl><dt><tt>TRUE</tt> <dd>if there is a solution point
 *    <dt><tt>FALSE</tt> <dd>no more solution point.</dl>
 */
  virtual CATBoolean NextPoint() = 0;

  /**
 * Creates the next solution point of <tt>this</tt> CATIPGMProjectionPtCrv operator.
 * @return
 * The pointer to the created point. A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 */
  virtual CATCartesianPoint *GetCartesianPoint() const = 0;

  /**
 * Creates the next solution as a point on curve of <tt>this</tt> CATIPGMProjectionPtCrv operator.
 * @return
 * The pointer to the created point on curve. A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 */
  virtual CATPointOnCurve *GetPointOnCurve() const = 0;

  /**
 * Returns the parameter on the curve of the next solution point of <tt>this</tt> CATIPGMProjectionPtCrv operator.
 * @return
 * The parameter.
 */
  virtual CATCrvParam GetParam() const = 0;

  /**
 * @nodoc
 * Returns the number of solution curves of <tt>this</tt> CATIPGMProjectionPtCrv operator.
 * @return
 * The number of solution curves.
 */
  virtual CATLONG32 GetNumberOfCurves() const = 0;

  /**
 * @nodoc
 * Initializes the iterator of the solution curves of <tt>this</tt> 
 * CATIPGMProjectionPtCrv operator.
 *<br>By default, the initialization is performed once the operator runs, 
 * and this is therefore only used to read the solutions again.
 */
  virtual void BeginningCurve() = 0;

  /**
 * @nodoc
 * Skips to the next solution curve of <tt>this</tt> CATIPGMProjectionPtCrv operator.
 *<br>After <tt>BeginningCurve</tt>, it skips to the first curve. 
 * @return
 * The existence of the next solution.
 * <br><b>Legal values</b>:
 *<dl><dt><tt>TRUE</tt> <dd>if there is a solution curve
 *    <dt><tt>FALSE</tt> <dd>no more solution curve.</dl>
 */
  virtual CATBoolean NextCurve() = 0;

  /**
 * @nodoc
 * Returns the limitations of the current resulting curve of <tt>this</tt> 
 * CATIPGMProjectionPtCrv operator.
 * @return
 * The domain of the solution curve.
 */
  virtual CATCrvLimits GetCurveLimits() const = 0;

  /**
 * Modifies the curve domain to take into account for <tt>this</tt> CATIPGMIntersectionCrvSur
 * operator (<tt>ADVANCED</tt> mode).
 *<br> It does not change the current curve 
 * limitations.  
 * @param iNewLimits
 * The new limitations of the curve.
 */
  virtual void SetLimits(const CATCrvLimits &iLimits) = 0;

  /**
 * Defines a new point to project (<tt>ADVANCED</tt> mode).
 * @param iPoint
 * The new point.
 */
  virtual void SetPoint(const CATMathPoint &iPoint) = 0;

  /**
 * @nodoc
 * Modifies the tolerance of points confusion of a CATIPGMIntersectionCrvSur operator.
 *<br>In case of <tt>ADVANCED</tt> mode.
 * Use after the <tt>Run</tt> method.
 */
  virtual void SetTolerance(const double tolerance) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMProjectionPtCrv(); // -> delete can't be called
};

#endif /* CATIPGMProjectionPtCrv_h_ */
