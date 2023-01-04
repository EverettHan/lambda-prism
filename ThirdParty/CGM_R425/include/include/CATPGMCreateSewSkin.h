#ifndef CATIPGMCreateSewSkin_h_
#define CATIPGMCreateSewSkin_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"

class CATBody;
class CATGeoFactory;
class CATTopData;
class CATIPGMTopSewSkin;

/**
 * Creates a CATTopSewSkin operator.
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
ExportedByCATGMOperatorsInterfaces CATIPGMTopSewSkin *CATPGMCreateSewSkin(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iTrimmingBody,
  CATBody *iSkinBody);

#endif /* CATIPGMCreateSewSkin_h_ */
