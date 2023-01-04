#ifndef CATIPGMTopLineOperator_h_
#define CATIPGMTopLineOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopCurveOperator.h"
#include "CATMathDef.h"

class CATMathVector;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopLineOperator;

/**
* Class defining a topological operator that builds a line body.
* <br> The definition of the line can be:
* <ul><li> passing by two points,
* <li> passing by a point and with a given direction,
* <li> tangent to a wire at a given point,
* <li> angled to the tangent to a wire at a given point, round the shell normal at this point 
* <li> normal to a shell at a point.
*</ul>
*<br> This operator follows the general scheme of the topological operators.
* For a basic use, use the functions <tt>CATCreateTopLineXXX</tt>
* that directly returns a line body.
* If you need to tune specific parameters, use the advanced scheme:
*<ul>
*<li> Create the operator with one of the functions <tt>CATCreateTopLineOperatorXXX</tt>
*<li> Set parameters: for example, use the </tt>SetFirstLimit</tt>
* </tt>SetSecondLimit</tt> methods to tune the line limits
*<li> Run
*<li> Get the resulting body 
*<li> Release the operator with the <tt>Release</tt> method.
*</ul>
*<br>The created body can be removed from the factory with the 
* @href CATICGMContainer#Remove method as any CATICGMObject.
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMTopLineOperator: public CATIPGMTopCurveOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopLineOperator();

  /** 
  * Defines the first limitation of the Line Body.
  * @param iFirstLength
  * The length from the origin of the line to define the first limitation.
  */
  virtual void SetFirstLimit(double iFirstLength) = 0;

  /** 
  * Defines the second limitation of the Line Body.
  * @param iSecondLength
  * The length from the origin of the line to define the second limitation.
  */
  virtual void SetSecondLimit(double iSecondLength) = 0;

  /**
 * Reads the first limitation, set for <tt>this</tt> CATIPGMTopLineOperator.
 * @param ioFirstLength
 * The length from the origin of the line to define the first limitation.
 */
  virtual void GetFirstLimit(double &ioFirstLength) = 0;

  /**
 * Reads the second limitation, set for <tt>this</tt> CATIPGMTopLineOperator.
 * @param ioSecondLength
 * The length from the origin of the line to define the second limitation.
 */
  virtual void GetSecondLimit(double &ioSecondLength) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopLineOperator(); // -> delete can't be called
};

/**
* Creates a topological line operator that builds
* a line passing through two points.
* @param iFactory
* The factory that creates the resulting body.
* @param iTopData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
* is <tt>NULL</tt>, it is not filled. 
* @param iOriginPoint
* The pointer to the point body, origin of the line. This body must only contain one point (vertex).
* @param iSecondPoint
* A pointer to the second point body, defining the line. This body must only contain one point (vertex).
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopLineOperator *CATPGMCreateTopLineOperatorFromPoints(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iOriginPoint,
  CATBody *iSecondPoint);

/**
* Creates a topological line operator that builds
* a line passing through a point and with a given direction.
* @param iFactory
* The factory that creates the resulting body.
* @param iTopData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
* is <tt>NULL</tt>, it is not filled. 
* @param iOriginPoint
* A pointer to the point body, origin of the line.  This body must only contain one point (vertex).
* @param iDirection
* The vector defining the line direction.
* @param iLength
* The length of the line from the origin point.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopLineOperator *CATPGMCreateTopLineOperatorFromDirection(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iOriginPoint,
  const CATMathVector &iDirection,
  double iLength);

/**
* Creates a topological line operator that builds
* a line tangent to a wire at a given point on the wire.
* @param iFactory
* The factory that creates the resulting body.
* @param iTopData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
* is <tt>NULL</tt>, it is not filled. 
* @param iOriginPoint
* The pointer to the point body, origin of the line.  This body must only contain one point (vertex).
* @param iWire
* The pointer to the wire body which geometrically contains the origin point. This body must only contain one wire.
* @param iLength
* The length of the line from the origin point.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopLineOperator *CATPGMCreateTopLineOperatorTangentToWire(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iOriginPoint,
  CATBody *iCurve,
  double iLength);

/**
* Creates a topological line operator that builds
* a line angled to the tangent to the wire at the origin point,
* and lying in the plane tangent to the shell at the origin point.
* <br>In other words:
* <ul>
*   <li>consider T as the tangent to the wire at the origin point P,
*   <li>build the result line by rotation of T of a given angle round the
*     normal to the shell at P.
* </ul>
* @param iFactory
* The factory that creates the resulting body.
* @param iTopData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
* is <tt>NULL</tt>, it is not filled. 
* @param iOriginPoint
* The pointer to the point body, origin of the line. This body must only contain one point (vertex).
* @param iCurve
* The pointer to the wire which contains the origin point. It must be included in the shell. 
* @param iShellOfCurve
* The pointer to the shell which contains the origin point and the wire. 
* @param iLength
* The length of the line from the origin point.
* @param iAngle
* The angle in radian of the rotation around the normal of the shell at the origin point.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopLineOperator *CATPGMCreateTopLineOperatorAngledTangentToWire(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iOriginPoint,
  CATBody *iCurve,
  CATBody *iShellOfCurve,
  double iLength,
  CATAngle iAngle);

/**
* Creates a topological line operator  that builds
* a line normal to a shell at a point.
* @param iFactory
* The factory that creates the resulting body.
* @param iTopData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
* is <tt>NULL</tt>, it is not filled. 
* @param iOriginPoint
* The pointer to the point body, origin of the line. This body must only contain one point (vertex).
* @param iShellOfPoint
* The pointer to the shell containing the origin point. 
* @param iLength
* The length of the line from the origin point.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopLineOperator *CATPGMCreateTopLineOperatorNormalToShell(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iOriginPoint,
  CATBody *iShellOfPoint,
  double iLength);

/**
* Create an infinite line passing through a point in a given direction.
* @param iFactory
* The factory that creates the resulting body.
* @param iOriginPoint
* The point body origin of the line.
* @param iDirection
* The vector giving the line direction.
* @param iIsSemiInfinite
* Yes if the line is only infinite in the given direction
* and No if the line is infinite on the both side.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
//===================================================================
ExportedByCATGMOperatorsInterfaces CATIPGMTopLineOperator *CATPGMCreateTopLineInfiniteOperatorFromDirection(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iOriginPoint,
  const CATMathVector &iDirection,
  CATBoolean iIsSemiInfinite);

#endif /* CATIPGMTopLineOperator_h_ */
