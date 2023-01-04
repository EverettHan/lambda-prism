#ifndef CATInclusionPtPCrv_H
#define CATInclusionPtPCrv_H

// COPYRIGHT DASSAULT SYSTEMES  1999

#include "CreateInclusionPtPCrv.h"
#include "CATCreateInclusionPtPCrv.h"
#include "CATCGMOperator.h"

#include "CATMathDef.h"
#include "CATIntersectionPCrvPCrvSign.h"

class CATPointOnCurve;
class CATPointOnEdgeCurve;
class CATCrvParam;
/**
 * Class defining the operator for testing the inclusion of a point
 * in a PCurve.
 *<br>The inclusion is tested within a given tolerance. The operator gets all
 * the points closed enough (at the tolerance) to the curve, spaced 
 * each other by a curvilinear distance at least equal to <tt>2*Tol</tt>.
 * This operator is optimized for low values of <tt>Tol</tt>. Notice that
 * the inclusion operator is not symmetrical. It also differs from the
 * CATDistanceMinPtCrv operator, that only outputs one point realizing
 * the minimum distance without tolerance.
 *<ul>
 *<li>The CATInclusionPtPCrv operator is created with the @href CreateInclusionMinPtPCrv method.
 * It is is not streamable. 
 *<li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed at the operator creation. 
 * In case of <tt>ADVANCED</tt>
 * mode, options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. The advanced mode also allows you to
 * run the same operator with different limitations of the curve.
 *<li>In both cases, the result is accessed with a specific interator.
 *<li> The operator is removed from the memory with the <tt>Remove</tt> method.
 *</ul>
 */
class CATInclusionPtPCrv : public CATCGMOperator
{
  CATCGMVirtualDeclareClass(CATInclusionPtPCrv);
 public:
/**
 * Destructor.
 */  
  virtual ~CATInclusionPtPCrv();
  CATInclusionPtPCrv(CATGeoFactory * factory);
  
/**
 * The 3D tolerance used to decide the inclusion.
 * @param i3DTolerance
 * The tolerance.
 */

  virtual void Set3DTolerance(const double i3DTolerance) = 0;

/**
 * The SurParam to be included.
 * @param iSurParam
 * The SurParam.
 */

  virtual void SetParam(const CATSurParam & iSurParam) = 0;

/**
 * Returns the number of points resulting of <tt>this</tt> CATInclusionPtCrv operator.
 * @return
 * The number of solutions.
 */
  virtual CATLONG32 GetNumberOfPoints() const = 0;
  
  // Iterators
/**
 * Initializes the iterator of the resulting points of a 
 * CATInclusionPtPCrv operator.
 *<br>By default, the initialization is performed once the operator has been
 * calculated, and is therefore only used to read the solutions again.
 */
  virtual void BeginningPoint() = 0;

/**
 * Skips to the next solution point of <tt>this</tt> CATInclusionPtPCrv operator.
 *<br>After <tt>BeginningPoint</tt>, it skips to the first point. The points are
 * spaced each other by a curvilinear length at least equal to <tt>2*Tol</tt>.
 * @return
 * The existence a the next solution.
 * <br><b>Legal values</b>:
 *<dl><dt><tt>TRUE</tt> <dd>if there is a solution point
 *    <dt><tt>FALSE</tt> <dd>no more solution point.</dl>
 */
  virtual CATBoolean NextPoint() = 0;

  // Methods which can be used after each NextPoint() call
/**
 * Returns the next solution point of <tt>this</tt> CATInclusionPtPCrv operator.
 * <br>To use if the input curve is an edge curve.
 * @return
 * The pointer to the created point on edge curve. A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 */
  virtual CATPointOnEdgeCurve * GetPointOnEdgeCurve() const = 0;

/**
 * Returns the next solution point of <tt>this</tt> CATInclusionPtPCrv operator.
 * @return
 * The pointer to the created point on curve. A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 */
  virtual CATPointOnCurve * GetPointOnCurve() const = 0;

/**
 * Retrieves the parameter of the next solution point of <tt>this</tt> CATInclusionPtCrv operator.
 * @param ioParam
 * The parameter.
 */
  virtual void GetCurveParam(CATCrvParam & oParam) const = 0;

/**
 * Returns the distance of a solution point and the curve.
 * @return
 * The distance.
 */
  virtual double GetDistance() const = 0;

/**
 * Returns the position of the point on the CATPCurve.
 *@return
 * <dl><dt><tt>CATPositionOnCurveBegin</tt><dd>the point is located at the 
 * begining of the CATPCurve.
 *    <dt><tt>CATPositionOnCurveEnd</tt><dd>the point is located at the 
 * end of the CATPCurve.
 *    <dt><tt>CATPositionOnCurveInterior</tt><dd>the point is located inside
 *CATPCurve (without its limits points).
 *    <dt><tt>CATPositionOnCurveUnknown</tt><dd>the point is not located on the
 *CATPCurve.</dl>
 */
  virtual CATPointPositionOnCurve GetPointPositionOnCurve() const = 0;

/**
 * Returns the relative position of the point and the CATPCurve on the
 * CATSurface.
 *@return
 *<dl><dt><tt>CATPtPcrvSignaturePositive</tt><dd>
 *    <dt><tt>CATPtPcrvSignatureNegative</tt><dd>
 *    <dt><tt>CATPtPcrvSignatureClose</tt><dd>
 *    <dt><tt>CATPositionOnCurveUnknown</tt><dd></dl>
 */
  virtual CATPtPCrvSignature GetSignature() const = 0;

/**
 * Modifies the curve limitations to take into account (<tt>ADVANCED</tt> mode).
 *<br> It does not change the current CATCurve 
 * limitations. The proposed limitations have to be included into the
 * current limitations.
 * @param iNewLimits
 * The new limitations to take into account.
 */
  virtual void SetLimits(const CATCrvLimits & iNewLimits) = 0;
  
/**
 * @nodoc
 * Do not use.
 */
  virtual double GetTolerance() const = 0;

};

#endif
