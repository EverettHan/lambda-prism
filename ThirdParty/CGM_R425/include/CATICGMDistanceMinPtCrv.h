#ifndef CATICGMDistanceMinPtCrv_h_
#define CATICGMDistanceMinPtCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATICGMOperator.h"

class CATCrvLimits;
class CATCurve;
class CATMathPoint;
class CATPointOnCurve;
class CATCrvParam;

extern ExportedByCATGMModelInterfaces IID IID_CATICGMDistanceMinPtCrv;

/**
 * Class defining the operator of the minimum distance between
 * a point and a curve.
 * <ul>
 *<li>The CATICGMDistanceMinPtCrv operator is created with the <tt>CATCGMCreateDistanceMin</tt> method  and 
 * directly released with the <tt>Release</tt> method.
 * It is is not streamable. 
 * <li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed at the operator creation. 
 * In case of <tt>ADVANCED</tt>
 * mode, options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. The advanced mode also allows you to
 * run the same operator with different points.
 * <li>In both cases, the result is accessed with specific methods.
 * </ul>
 */
class ExportedByCATGMModelInterfaces CATICGMDistanceMinPtCrv: public CATICGMOperator
{
public:
  /**
   * Constructor
   */
  CATICGMDistanceMinPtCrv();

  //-----------------------------------------------------------------------
  //- Public Interface Methods
  //-----------------------------------------------------------------------
  /**
 * Returns the minimum distance between a curve and a point.
 * @return
 * The distance.
 */
  virtual double GetDistance() const = 0;

  /**
 * Returns the global parameter of the point realizing the minimum
 * distance.
 *<br>Note that only one point is proposed, even multiple solutions exist.
 * @return
 * The parameter on the curve.
 */
  virtual CATCrvParam GetCrvParam() const = 0;

  /**
 * Creates a CATPointOnCurve realizing the minimum distance.
 *<br>Note that only one point is proposed, even multiple solutions exist.
 * @return
 * The pointer to the created point. A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 */
  virtual CATPointOnCurve *GetPointOnCurve() const = 0;

  /**
 * Defines the new domain of the curve to take into account for <tt>this</tt> operator in 
 * <tt>ADVANCED</tt> mode.
 * @param iLimits
 * The new limitations on the curve.
 */
  virtual void SetLimits(const CATCrvLimits &iLimits) = 0;

  /**
 * Sets the new point from which the main distance with the curve is computed.
 * @param iPoint
 * The new point.
 */
  virtual void SetPoint(const CATMathPoint &iPoint) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMDistanceMinPtCrv(); // -> delete can't be called
};

#endif /* CATICGMDistanceMinPtCrv_h_ */
