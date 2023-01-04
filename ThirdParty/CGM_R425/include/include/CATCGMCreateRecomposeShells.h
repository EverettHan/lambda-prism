#ifndef CATICGMCreateRecomposeShells_h_
#define CATICGMCreateRecomposeShells_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMVirtual.h"

class CATBody;
class CATGeoFactory;
class CATICGMRecomposeShells;
class CATTopData;

/**
 * Creates a CATICGMRecomposeShells operator.
 * @param iFactory
 * The pointer to the geometry factory.
 * @param iData
 * The pointer to the data defining the configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 * @param iBodyToRecompose
 * The pointer to the body to be recomposed.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 * @see CATICGMRecomposeShells
 */
ExportedByCATGMOperatorsInterfaces CATICGMRecomposeShells *CATCGMCreateRecomposeShells(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBodyToRecompose);

#endif /* CATICGMCreateRecomposeShells_h_ */
