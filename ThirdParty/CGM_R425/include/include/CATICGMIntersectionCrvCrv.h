#ifndef CATICGMIntersectionCrvCrv_h_
#define CATICGMIntersectionCrvCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATICGMOperator.h"
#include "CATDataType.h"
#include "CATBoolean.h"

class CATCartesianPoint;
class CATCrvLimits;
class CATCrvParam;
class CATCurve;
class CATEdgeCurve;
class CATGeoFactory;
class CATPointOnCurve;
class CATPointOnEdgeCurve;

extern ExportedByCATGMModelInterfaces IID IID_CATICGMIntersectionCrvCrv;

/**
 * Class defining the operator of the intersection of two curves.
 * <br>The operator outputs the isolated solutions (points) and the
 * overlapping solutions (curves).
 * <ul>
 * <li>The CATICGMIntersectionCrvCrv operator is created with the <tt>CATCGMCreateIntersection</tt> method and 
 * directly released with the <tt>Release</tt> method.
 * It is is not streamable. 
 * <li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed at the operator creation. 
 * In case of <tt>ADVANCED</tt>
 * mode, options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. The advanced mode also allows you to
 * run the same operator with different curves.
 * <li>In both cases, the result is accessed with two specific interators, one for the solution points,
 * the other for the solution curves.
 * </ul>
 */
class ExportedByCATGMModelInterfaces CATICGMIntersectionCrvCrv: public CATICGMOperator
{
public:
  /**
   * Constructor
   */
  CATICGMIntersectionCrvCrv();

  /**
 * Returns the number of isolated resulting points of <tt>this</tt> CATICGMIntersectionCrvCrv operator.
 * @return
 * The number of isolated points.
 */
  virtual CATLONG32 GetNumberOfPoints() const = 0;

  /**
 * Initializes the iterator of the resulting points.
 *<br>By default, the initialization is performed once the operator runs, 
 * and this is therefore only used to read the solutions again.
 */
  virtual void BeginningPoint() = 0;

  /**
 * Skips to the next solution point of <tt>this</tt> CATICGMIntersectionCrvCrv operator.
 *<br>After <tt>BeginningPoint</tt>, it skips to the first point. 
 * @return
 * The existence of the next solution.
 * <br><b>Legal values</b>:
 *<dl><dt><tt>TRUE</tt> <dd>if there is a solution point
 *    <dt><tt>FALSE</tt> <dd>no more solution point.</dl>
 */
  virtual CATBoolean NextPoint() = 0;

  /**
 * Creates the next solution point of <tt>this</tt> CATICGMIntersectionCrvCrv operator.
 * @return
 * The pointer to the created point. A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 */
  virtual CATCartesianPoint *GetCartesianPoint() = 0;

  /**
 * Creates the next solution point on curve of <tt>this</tt> CATICGMIntersectionCrvCrv operator.
 * @param iCurve
 * The pointer to the first or second curve which are intersected.
 * @param iIndex
 * Internal use.
 * @return
 * The pointer to the created point on curve. A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 */
  virtual CATPointOnCurve *GetPointOnCurve(
    CATCurve *iCurve,
    const CATLONG32 iIndex = 0) const = 0;

  /**
 * Retrieves the parameter of the next solution point of <tt>this</tt> CATICGMIntersectionCrvCrv operator.
 * @param iCurve
 * The pointer to the first or second curve which are intersected. 
 * @param ioCrvParam
 * The parameter.
 * @param iIndex
 * Internal use.
 */
  virtual void GetCurveParam(
    CATCurve *iCurve,
    CATCrvParam &ioCrvParam,
    const CATLONG32 iIndex = 0) const = 0;

  /**
 * Returns the number of solution curves of <tt>this</tt> CATICGMIntersectionCrvCrv operator.
 * @return
 * The number of resulting curves.
 */
  virtual CATLONG32 GetNumberOfCurves() const = 0;

  /**
 * Initializes the iterator of the solution curves.
 * <br>By default, the initialization is performed once the operator runs, 
 * and this is therefore only used to read the solutions again.
 */
  virtual void BeginningCurve() = 0;

  /**
 * Skips to the next solution curve of <tt>this</tt> CATICGMIntersectionCrvCrv operator.
 * <br>After <tt>BeginningCurve</tt>, it skips to the first curve. 
 * @return
 * The existence of the next solution.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>TRUE</tt> <dd>if there is a solution curve
 *    <dt><tt>FALSE</tt> <dd>no more solution curve.</dl>
 */
  virtual CATBoolean NextCurve() = 0;

  /**
 * Returns the domain of the next solution curve of <tt>this</tt> CATICGMIntersectionCrvCrv operator.
 * @param iCurve
 * The first or the second operand of the operator, on which the domain is output.
 * @param ioLimits
 * The domain of the solution curve.
 */
  virtual void GetCurveLimits(CATCurve *iCurve, CATCrvLimits &ioLimits) const = 0;

  /**
 * Creates the next solution curve of <tt>this</tt> CATICGMIntersectionCrvCrv operator as an edge curve.
 * <br>The edge curve is composed of parts of each inital curve. 
 * @param oStart
 * The pointer to the created point representing the first extremity of the solution curve.
 * A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 * @param oEnd
 * The pointer to the created point representing the last extremity of the solution curve.
 * A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 * @return
 * The pointer to the created edge curve, <tt>NULL</tt> if it cannot be created.
 * A new curve is created each time this method is called.
 * If you do not want to keep the created curve, use the @href CATICGMContainer#Remove method.
 * and the POEC extremities oStart and oEnd on this edgecurve.
 */
  virtual CATEdgeCurve *GetEdgeCurve(
    CATPointOnEdgeCurve *&oStart,
    CATPointOnEdgeCurve *&oEnd) const = 0;

  /**
 * Defines the intersection with another second curve (<tt>ADVANCED</tt> mode).
 * @param iNewSecondCurve
 * The pointer to the new second curve.
 */
  virtual void SetCurve(CATCurve *iNewSecondCurve) = 0;

  /**
 * Modifies the curve domain to take into account for <tt>this</tt>
 * CATICGMIntersectionCrvCrv operator (<tt>ADVANCED</tt> mode).
 * <br> It does not change the current curve limitations.
 * @param iLimitsForCurve1
 * The pointer to the new domain of the first curve. If <tt>NULL</tt>, the current limitation of the first
 * curve is used.
 * @param iLimitsForCurve2
 * The pointer to the new domain of the second curve. If <tt>NULL</tt>, the current limitation of the second
 * curve is used.
 */
  virtual void UseLimits(
    CATCrvLimits *iLimitsForCurve1,
    CATCrvLimits *iLimitsForCurve2) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMIntersectionCrvCrv(); // -> delete can't be called
};

#endif /* CATICGMIntersectionCrvCrv_h_ */
