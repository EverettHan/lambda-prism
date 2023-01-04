#ifndef CATPGMCreateSplitShellByWiresBasicExtrapol_h_
#define CATPGMCreateSplitShellByWiresBasicExtrapol_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATCollec.h"

class CATBody;
class CATGeoFactory;
class CATTopData;
class CATLISTP(CATBody);
class CATIPGMTopSplitShellByWires;

/**
 * Creates a CATIPGMTopSplitShellByWires operator.
 * @param iFactory
 * The pointer to the geometry factory. 
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iSplittingBodies
 * A list of bodies containing only one wire.
 * @param iSkinBody
 * The skin body to be split by iSplittingBodies. 
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopSplitShellByWires *CATPGMCreateSplitShellByWiresBasicExtrapol(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATLISTP(CATBody) *iSplittingBodies,
  CATBody *iSkinBody);

#endif /* CATPGMCreateSplitShellByWiresBasicExtrapol_h_ */
