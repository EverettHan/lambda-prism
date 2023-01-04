#ifndef CATPGMCreateTopExtrapolWireOpe_h_
#define CATPGMCreateTopExtrapolWireOpe_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATCollec.h"

#ifndef NULL
#define NULL 0
#endif

class CATIPGMTopExtrapolWireOpe;
class CATGeoFactory;
class CATTopData;
class CATBody;

/**
 * @level Protected
 * @usage U1
 */
/**
* Creates a topological operator that extrapolates a wire.
* <br>It allows you to extrapolate a wire
* <ul><li>in tangency mode
* <li> or in curvature mode
* <li> on a support or not.
* <li> from a given length or up to an other wire or a shell.
* </ul>
* @param iFactory
* The pointer to the geometry factory.
* @param iData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
* is <tt>NULL</tt>, it is not filled. 
* @param iBodyWire
* The pointer to the wire to extrapolate.
* @param iBodyShell
* The pointer to the body support on which the wire must be extrapolated. If <tt>NULL</tt>, the result won't have any support.
* @return [out, IUnknown#Release]
* The pointer to the created operator. 
* To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopExtrapolWireOpe *CATPGMCreateTopExtrapolWireOpe(
  CATGeoFactory *iFacto,
  CATTopData *iData,
  CATBody *iBodyWire,
  CATBody *iBodyShell = NULL);

#endif /* CATPGMCreateTopExtrapolWireOpe_h_ */
