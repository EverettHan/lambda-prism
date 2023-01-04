#ifndef CATIPGMDistanceMaxBodyBody_h_
#define CATIPGMDistanceMaxBodyBody_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATMathPoint;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMDistanceMaxBodyBody;

// COPYRIGHT DASSAULT SYSTEMES  2004
/**
 * Creates an operator for computing the maximum normal distance from body1 to body2.
 * The input surfaces (or volume) must be G1 continuous.
 * You must SetInitializationPoints, this set of MathPoint is approximated, as computed on the tesselation of the two surfaces,
 * then reconverged on the exact geometries.
 * If reconvergence on exact geometries fails, we keep the approximate distance but computed on the exact geometries.
 * To use the operator:
 * <ul><li>Create it with the <tt>CATPGMCreateDistanceMaxTopo</tt> global function,
 * <li>Set parameters to tune its use,
 * <li>Run the operator ,
 * <li>Retrieve the results with the <tt>Get</tt> methods, 
 * <li>Release the operator with the <tt>Release</tt> method after use.
 * </ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMDistanceMaxBodyBody: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMDistanceMaxBodyBody();

  //-----------------------------------------------------------------------------
  //  Settings
  //-----------------------------------------------------------------------------
  virtual void SetInitializationPoints(
    const CATMathPoint &iPoint1,
    const CATMathPoint &iPoint2) = 0;

  //-------------------------------------------------------------------------
  // Result Access
  //-------------------------------------------------------------------------
  /**
	* Returns the computed maximum distance between the two bodies.
	* @return
	* The maximum distance. If the distance could not be computed, returns <tt>-1</tt>.
	*/
  virtual double GetDistance() = 0;

  /**
	* Returns the points realizing the maximum distance .
	* @param oPoint1
	* The CATMathPoint to the point on the first body.
	* @param oPoint2
	* The CATMathPoint to the point on the second body.
	*/
  virtual void GetMathPoints(CATMathPoint &oPoint1, CATMathPoint &oPoint2) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMDistanceMaxBodyBody(); // -> delete can't be called
};

#endif /* CATIPGMDistanceMaxBodyBody_h_ */
