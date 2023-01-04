#ifndef CATIPGMCreateRecomposeShells_h_
#define CATIPGMCreateRecomposeShells_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"

class CATBody;
class CATGeoFactory;
class CATIPGMRecomposeShells;
class CATTopData;

/**
 * Creates a CATRecomposeShells operator.
 * @param iFactory
 * The pointer to the geometry factory.
 * @param iData
 * The pointer to the data defining the configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 * @param iBodyToRecompose
 * The pointer to the body to be recomposed.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 * @see CATRecomposeShells
 */
ExportedByCATGMOperatorsInterfaces CATIPGMRecomposeShells *CATPGMCreateRecomposeShells(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBodyToRecompose);

#endif /* CATIPGMCreateRecomposeShells_h_ */
