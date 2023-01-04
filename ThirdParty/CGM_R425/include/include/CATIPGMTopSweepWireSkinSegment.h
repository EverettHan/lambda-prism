#ifndef CATPGMTopSweepWireSkinSegment_h_
#define CATPGMTopSweepWireSkinSegment_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopSweepWireSkin.h"

#define CATIPGMTopSweepWireSkinSegment CATIPGMTopSweepWireSkin

/**
* @level Protected
* @usage U1
*/
/**
 * Constructs an operator that creates a segment sweep
 * between a skin body and a wire body.
 */
/**
 * Creates a CATTopSweepWireSkinSegment operator.
 * @param iFactory
 * The pointer to the geometry factory that creates the result bodies.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iSupportShell
 * The pointer to the skin body.
 * @param iGuide
 * The pointer to the wire body.
 * @param iSpine
 * The pointer to the spine body. Each segment section is in the plane normal to this spine curve.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 * operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopSweepWireSkinSegment *CATPGMCreateTopSweepWireSkinSegment(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iSupportShell,
  CATBody *iGuide,
  CATBody *iSpine);

#endif /* CATPGMTopSweepWireSkinSegment_h_ */
