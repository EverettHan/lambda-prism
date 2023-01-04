#ifndef CATCGMCreateTopDisconnect_h_
#define CATCGMCreateTopDisconnect_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"

class CATICGMHybDisconnect;
class CATGeoFactory;
class CATTopData;
class CATBody;

/**
 * Creates the operator to insert vertices in a wire or skin body, or to
 * insert edges in a skin body.
 * @param iFactory
 * The pointer to the geometry factory.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 *  @param iBodyToDisconnect
 * The pointer to the body in which cells are inserted.
 * @param iDisconnectingBody
 * The pointer to the body containing the cells to insert.
 * @param iCuttingBody
 * The pointer to the resulting body of the operation of projection of <tt>iDisconnectingBody</tt>
 * onto <tt>iBodyToDisconnect</tt>.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMHybDisconnect *CATCGMCreateTopDisconnect(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBodyToDisconnect,
  CATBody *iDisconnectingBody,
  CATBody *iCuttingBody);

#endif /* CATCGMCreateTopDisconnect_h_ */
