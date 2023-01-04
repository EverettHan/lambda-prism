#ifndef __CATCreateSewSkin_h__ 
#define __CATCreateSewSkin_h__ 

// COPYRIGHT DASSAULT SYSTEMES  2003

/**
 * @level Protected
 * @usage U1
 */

#include "ExportedByCATTopologicalObjects.h"

class CATTopSewSkin;
class CATGeoFactory;
class CATTopData;
class CATBody;


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
 * @return
 * The pointer to the created operator. To delete with the usual C++ <tt>delete</tt> operator after use.
 */

ExportedByCATTopologicalObjects CATTopSewSkin *
CATCreateSewSkin(CATGeoFactory * iFactory,
                 CATTopData    * iTopData,
                 CATBody       * iTrimmingBody,
                 CATBody       * iSkinBody);

#endif






