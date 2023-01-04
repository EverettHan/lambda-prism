#ifndef CATIPGMInclusionPtCrv_h_
#define CATIPGMInclusionPtCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMOperator.h"
#include "CATMathPoint.h"
#include "CATIntersectionPCrvPCrvSign.h"

class CATCrvParam;
class CATPointOnCurve;
class CATPointOnEdgeCurve;
class CATCrvLimits;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMInclusionPtCrv;

/**
 * Class defining the operator for testing the inclusion of a point
 * in a curve.
 *<br>The inclusion is tested within a given tolerance. The operator gets all
 * the points closed enough (at the tolerance) to the curve, spaced 
 * each other by a curvilinear distance at least equal to <tt>2*Tol</tt>.
 * This operator is optimized for low values of <tt>Tol</tt>. It differs from the
 * CATIPGMDistanceMinPtCrv operator, that only outputs one point realizing
 * the minimum distance without tolerance.
 *<ul>
 *<li>The CATIPGMInclusionPtCrv operator is created with the <tt>CATPGMCreateInclusion</tt> method and 
 * directly released with the <tt>Release</tt> method.
 * It is is not streamable. 
 *<li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed at the operator creation. 
 * In case of <tt>ADVANCED</tt>
 * mode, options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. The advanced mode also allows you to
 * run the same operator with different limitations of the curve.
 *<li>In both cases, the result is accessed with a specific interator.
 *</ul>
 */
class ExportedByCATGMModelInterfaces CATIPGMInclusionPtCrv: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMInclusionPtCrv();

  /**
 * Returns the number of resulting points of <tt>this</tt> CATIPGMInclusionPtCrv operator.
 * @return
 * The number of solutions.
 */
  virtual CATLONG32 GetNumberOfPoints() const = 0;

  // Iterators
  /**
 * Initializes the iterator of the resulting points of <tt>this</tt> 
 * CATIPGMInclusionPtCrv operator.
 *<br>By default, the initialization is performed once the operator runs, and
 * this is therefore only used to read the solutions again.
 */
  virtual void BeginningPoint() = 0;

  /**
 * Skips to the next solution point of <tt>this</tt> CATIPGMInclusionPtCrv operator.
 *<br>After <tt>BeginningPoint</tt>, it skips to the first point. The points are
 * spaced each other by a curvilinear length at least equal to <tt>2*Tol</tt>.
 * @return
 * The existence of the next solution.
 * <br><b>Legal values</b>:
 *<dl><dt><tt>TRUE</tt> <dd>if there is a solution point
 *    <dt><tt>FALSE</tt> <dd>no more solution point.</dl>
 */
  virtual CATBoolean NextPoint() = 0;

  // Methods which can be used after each NextPoint() call
  /**
 * @nodoc
 * Creates the next solution point of <tt>this</tt> CATIPGMInclusionPtCrv operator.
 * <br>To use if the input curve is an edge curve.
 * @return
 * The pointer to the created point on edge curve. A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 */
  virtual CATPointOnEdgeCurve *GetPointOnEdgeCurve() const = 0;

  /**
 * Creates the next solution point of <tt>this</tt> CATIPGMInclusionPtCrv operator.
 * @return
 * The pointer to the created point on curve. A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 */
  virtual CATPointOnCurve *GetPointOnCurve() const = 0;

  /**
 * Retrieves the parameter of the next solution point of <tt>this</tt> CATIPGMInclusionPtCrv operator.
 * @param ioParam
 * The parameter.
 */
  virtual void GetCurveParam(CATCrvParam &ioParam) const = 0;

  /**
 * Returns the distance of a solution point and the curve.
 * @return
 * The distance.
 */
  virtual double GetDistance() const = 0;

  /**
 * Modifies the curve domain to take into account (<tt>ADVANCED</tt> mode).
 *<br> It does not change the current CATCurve 
 * limitations. The proposed limitations have to be included into the
 * current limitations.
 * @param iNewLimits
 * The new limitations to take into account.
 */
  virtual void SetLimits(const CATCrvLimits &iNewLimits) = 0;

  /**
 * @nodoc
 * Defines the new point to test (<tt>ADVANCED</tt> mode).
 * <br>After this method, use again the <tt>Run</tt> method, and retrieve the result with the <tt>GetXxx</tt> methods.
 * @param iPoint
 * The new point.
 */
  virtual void SetPoint(CATMathPoint &iPoint) = 0;

  /**
 * @nodoc
 * Do not use.
 */
  virtual CATPointPositionOnCurve GetPointPositionOnCurve() const = 0;

  /**
 * @nodoc
 * Do not use.
 */
  virtual double GetTolerance() const = 0;

  /**
 * @nodoc
 * Do not use.
 */
  virtual void SetTolerance(double iNewTolerance) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMInclusionPtCrv(); // -> delete can't be called
};

#endif /* CATIPGMInclusionPtCrv_h_ */
