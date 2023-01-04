#ifndef CATICGMDistanceMinCrvCrv_h_
#define CATICGMDistanceMinCrvCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATICGMGeoOperator.h"

class CATCrvParam;
class CATCurve;
class CATPointOnCurve;
class CATCrvLimits;

extern ExportedByCATGMModelInterfaces IID IID_CATICGMDistanceMinCrvCrv;

/**
 * Class defining the operator of the minimum distance between
 * two curves.
 *<ul>
 *<li>The CATICGMDistanceMinCrvCrv operator is created with the <tt>CATCGMCreateDistanceMin</tt> method  and 
 * directly released with the <tt>Release</tt> method.
 * It is is not streamable. 
 *<li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed at the operator creation. 
 * In case of <tt>ADVANCED</tt>
 * mode, the user can precise options with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method.
 *<li>In both cases, the result is accessed with specific methods.
 *</ul>
 */
class ExportedByCATGMModelInterfaces CATICGMDistanceMinCrvCrv: public CATICGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATICGMDistanceMinCrvCrv();

  /**
 * Defines the curve domain to take into account for <tt>this</tt> operator in case of 
 * <tt>ADVANCED</tt> mode.
 * @param iCrvLim1
 * The limitations on the first curve.
 * @param iCrvLim2
 * The limitations on the second curve.
 */
  virtual void SetLimits(
    const CATCrvLimits &iCrvLim1,
    const CATCrvLimits &iCrvLim2) = 0;

  /**
 * Returns the minimum distance between two CATCurves.
 * @return
 * The minimum distance.
 */
  virtual double GetDistance() const = 0;

  /**
 * Creates a CATPointOnCurve realizing the minimum distance 
 * between two CATCurves.
 * <br>Note that only one point is proposed, even multiple solutions exist.
 * @param iCurve
 * The pointer to the curve on which the point is created.
 * @return
 * The pointer to the created point. A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 */
  virtual CATPointOnCurve *GetPointOnCurve(CATCurve *iCurve) const = 0;

  /**
 * Returns a parameter on a given curve realizing the minimum distance 
 * between the two input CATCurves.
 * <br>Note that only one point is proposed, even multiple solutions exist.
 * @param iCurve
 * The pointer to the curve on which the parameter is retrieved.
 * @param ioParam
 * The parameter value of the point realizing the minimum distance on <tt>iCurve</tt>.
 */
  virtual void GetCurveParam(CATCurve *iCurve, CATCrvParam &ioParam) const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMDistanceMinCrvCrv(); // -> delete can't be called
};

#endif /* CATICGMDistanceMinCrvCrv_h_ */
