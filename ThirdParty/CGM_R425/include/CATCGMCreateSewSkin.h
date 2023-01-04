#ifndef CATICGMCreateSewSkin_h_
#define CATICGMCreateSewSkin_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"

class CATBody;
class CATGeoFactory;
class CATTopData;
class CATICGMTopSewSkin;

/**
 * Creates a CATICGMTopSewSkin operator.
 * @param iFactory
 * The pointer to the geometry factory. 
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iTrimmingBody
 * The input body.
 * @param iSkinBody
 * The skin body to be sewn onto the input body. 
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMTopSewSkin *CATCGMCreateSewSkin(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iTrimmingBody,
  CATBody *iSkinBody);

#endif /* CATICGMCreateSewSkin_h_ */
