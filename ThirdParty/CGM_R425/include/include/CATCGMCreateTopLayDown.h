#ifndef CATCGMCreateTopLayDown_h_
#define CATCGMCreateTopLayDown_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"

class CATBody;
class CATGeoFactory;
class CATICGMLayDownOperator;
class CATTopData;

/**
* Constructs an operator that  projects a body onto another one referred to as the support
* and returns a solution.
* @param iFactory
* The pointer to the factory of the geometry.
* @param iData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
* is <tt>NULL</tt>, it is not filled. 
* @param iBodyToLayDown
* The pointer to the body to be projected. 
* @param iBodySupport
* The support.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMLayDownOperator *CATCGMCreateTopLayDown(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBodyToLayDown,
  CATBody *iBodySupport);

#endif /* CATCGMCreateTopLayDown_h_ */
