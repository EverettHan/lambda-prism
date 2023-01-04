#ifndef CATDISTANCEMINCRVCRV_H
#define CATDISTANCEMINCRVCRV_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @level Protected
 * @usage U1
 */ 

#include "CATCreateDistanceMinCrvCrv.h"
#include "CreateDistanceMinCrvCrv.h"
#include "CATMathDef.h"
#include "CATCrvLimits.h"
#include "Y30C3XGG.h"
#include "CATGeoOperator.h"

class CATPointOnCurve;
class CATCurve;
class CATCrvParam;

/**
 * Class defining the operator of the minimum distance between
 * two curves.
 *<ul>
 *<li>The CATDistanceMinCrvCrv operator is created with the <tt>CreateDistanceMin</tt> method  and 
 * directly <tt>delete</tt>d with the usual C++ delete operator.
 * It is is not streamable. 
 *<li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed at the operator creation. 
 * In case of <tt>ADVANCED</tt>
 * mode, the user can precise options with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method.
 *<li>In both cases, the result is accessed with specific methods.
 *</ul>
 */
class ExportedByY30C3XGG CATDistanceMinCrvCrv : public CATGeoOperator
{

  CATCGMVirtualDeclareClass(CATDistanceMinCrvCrv);
public:
/**
 * Destructor.
 */
   virtual ~CATDistanceMinCrvCrv() ;
	/**
    * @nodoc
	* Use the <tt>CreateDistanceMin</tt> global method.
	*/
  CATDistanceMinCrvCrv(CATGeoFactory * factory) ;

/**
 * Defines the curve domain to take into account for <tt>this</tt> operator in case of 
 * <tt>ADVANCED</tt> mode.
 * @param iCrvLim1
 * The limitations on the first curve.
 * @param iCrvLim2
 * The limitations on the second curve.
 */
   virtual void SetLimits(const CATCrvLimits& iCrvLim1, const CATCrvLimits& iCrvLim2) = 0; 

/**
 * Returns the minimum distance between two CATCurves.
 * @return
 * The minimum distance.
 */
   virtual double GetDistance() const = 0;

/**
 * Creates a CATPointOnCurve realizing the minimum distance 
 * between two CATCurves.
 *<br>Note that only one point is proposed, even multiple solutions exist.
 * @param iCurve
 * The pointer to the curve on which the point is created.
 * @return
 * The pointer to the created point. A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 */
  virtual CATPointOnCurve * GetPointOnCurve( CATCurve *iCurve ) const = 0;

/**
 * Returns a parameter on a given curve realizing the minimum distance 
 * between the two input CATCurves.
 *<br>Note that only one point is proposed, even multiple solutions exist.
 * @param iCurve
 * The pointer to the curve on which the parameter is retrieved.
 * @param ioParam
 * The parameter value of the point realizing the minimum distance on <tt>iCurve</tt>.
 */
  virtual void GetCurveParam(CATCurve *iCurve, CATCrvParam & ioParam) const = 0;

/**
 * @nodoc
 * To increase performance, force the operator to find a minimal distance
 * lower than the specified one. If this is impossible no solution will be returned.
 * @param iMaxDistance
 * The maximum distance.
 */
  virtual void SetMaxDistance (double iMaxDistance) = 0;

/**
 * @nodoc
 * Return TRUE if the minimum distance between the two curves was lower (strictly at the
 * numerical precision) than the maximum distance given in SetMaxDistance.
 * Return FALSE otherwise : in this case, other result methods such as GetDistance,
 * GetPointOnCurve and GetCurveParam are not supposed to be called.
 */
  virtual CATBoolean MinDistanceFound () const = 0;

};

#include "CreateIntersection.h"
#endif
