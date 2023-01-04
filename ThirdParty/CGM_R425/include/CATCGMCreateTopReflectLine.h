#ifndef CATCGMCreateTopReflectLine_h_
#define CATCGMCreateTopReflectLine_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATMathConstant.h"

class CATBody;
class CATCGMJournalList;
class CATGeoFactory;
class CATMathVector;
class CATTopData;
class CATICGMTopReflectLine;

/** 
 * Creates the operator to compute the CONICAL reflect lines on a skin body.
 * Conical reflect line definition<br>:
 * If a skin S, an origin point O and an angle alpha are given,
 * the conical reflect line is the set of points P on the skin S for which 
 * the angle between the normal to S in P and the vector OP is equal to alpha.
 * @param iFactory
 * The pointer to the geometry factory.
 * @param iInputSkin
 * The pointer to the skin body on which the reflect lines are computed.
 * @param iOriginPoint
 * The pointer to the point body
 * @param iAngle
 * The angle between the shell normal and <tt>iDirection</tt> at the points
 * of the reflect lines.
 * @param iData
 * Data for this current operation. 
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMTopReflectLine *CATCGMCreateTopReflectLine(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iInputSkin,
  CATBody *iOriginPoint,
  CATAngle iAngle);

/** 
 * Creates the operator to compute the CYLINDRICAL reflect lines on a skin body.
 * Cylindrical reflect line definition: <br>
 * If a skin S, a direction D and an angle alpha are given,
 * the cylindrical reflect line is the set of points P from the skin S for which
 * the angle between the normal to S in P and direction D is equal to alpha.
 * @param iFactory
 * The pointer to the geometry factory.
 * @param iInputSkin
 * The pointer to the skin body on which the reflect lines are computed.
 * @param iDirection
 * The view direction.
 * @param iAngle
 * The angle between the shell normal and <tt>iDirection</tt> at the points
 * of the reflect lines.
 * @param iData
 * Data for this current operation. 
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMTopReflectLine *CATCGMCreateTopReflectLine(
  CATGeoFactory *iFactory,
  CATBody *iInputSkin,
  CATMathVector &iDirection,
  CATAngle iAngle,
  CATTopData *iData);

#endif /* CATCGMCreateTopReflectLine_h_ */
