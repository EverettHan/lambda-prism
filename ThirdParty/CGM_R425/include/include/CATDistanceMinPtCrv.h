#ifndef CATDistanceMinPtCrv_H
#define CATDistanceMinPtCrv_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @level Protected
 * @usage U1
 */ 

#include "CATCreateDistanceMinPtCrv.h"
#include "CreateDistanceMinPtCrv.h"
#include "CATMathDef.h"
#include "CATCGMOperator.h"
#include "Y30A3HGG.h"
#include "CATCrvParam.h"

class CATPointOnCurve;
class CATCurve;
class CATCrvLimits;
class CATMathPoint;

/**
 * Class defining the operator of the minimum distance between
 * a point and a curve.
 *<ul>
 *<li>The CATDistanceMinPtCrv operator is created with the <tt>CreateDistanceMin</tt> method  and 
 * directly <tt>delete</tt>d with the usual C++ delete operator.
 * It is is not streamable. 
 *<li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed at the operator creation. 
 * In case of <tt>ADVANCED</tt>
 * mode, options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. The advanced mode also allows you to
 * run the same operator with different points.
 *<li>In both cases, the result is accessed with specific methods.
 *</ul>
 */
class ExportedByY30A3HGG CATDistanceMinPtCrv : public CATCGMOperator
{

  CATCGMVirtualDeclareClass(CATDistanceMinPtCrv);
public:
/**
 * Destructor.
 */ 
  virtual ~CATDistanceMinPtCrv() ;
/**
 * @nodoc
 * Use the <tt>CreateDistanceMin</tt> global method.
 */ 
  CATDistanceMinPtCrv(CATGeoFactory * factory) ;
  
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
 * Creates a CATPointCnCurve realizing the minimum distance.
 *<br>Note that only one point is proposed, even multiple solutions exist.
 * @return
 * The pointer to the created point. A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 */
  virtual CATPointOnCurve * GetPointOnCurve() const = 0;

/**
 * @nodoc
 *  Returns the point on the CATMathNurbsMultiForm that realizes
 *  the minimum distance
 */
  virtual double GetPointOnMultiForm() const =0;

/**
 * Defines the new domain of the curve to take into account for <tt>this</tt> operator in 
 * <tt>ADVANCED</tt> mode.
 * @param iLimits
 * The new limitations on the curve.
 */
  virtual void SetLimits(const CATCrvLimits & iLimits) = 0;

/**
 * Sets the new point from which the main distance with the curve is computed.
 * @param iPoint
 * The new point.
 */
  virtual void SetPoint(const CATMathPoint & iPoint) =0;

/**
 * @nodoc
 * Defines the maximum value of the minimum distance (<tt>ADVANCED</tt> mode). 
 * @param iMaxDistance
 * The maximum value of minimum distance.
 */
  virtual void SetMaximumValue(double & iMaxDistance) =0;

  
/**
 * @nodoc
 * Sets a new point and an initialization
 * (<tt>ADVANCED</tt> mode).
 *<br>This is usefull for computing the distance to a new point near a another one, whose CATCrvParam
 * solution is already known. 
 * @param iNewPoint
 * The new point to take into account. 
 * @param iInit
 * The parameter of a point close from the solution.
  */

  virtual void SetPointAndInit(const CATMathPoint & iNewPoint, const CATCrvParam & iInit) =0;
//#ifdef CATIAV5R14
  /**
   * @nodoc
   * method to call to know if a solution exists or not
   */
	virtual CATBoolean IsSolution() const = 0;
//#endif
};

#endif
