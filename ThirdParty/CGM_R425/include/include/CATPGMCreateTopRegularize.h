#ifndef CATPGMCreateTopRegularize_h_
#define CATPGMCreateTopRegularize_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"

class CATIPGMHybRegularize;
class CATGeoFactory;
class CATTopData;
class CATBody;

// COPYRIGHT DASSAULT SYSTEMES  2000
/**
* Constructs a hybrid operator to regularize body.
* <br> The regularization consists in the suppression of too small
* volumes / faces / edges (which size is less than a tolerance).
* @param iFactory
* The pointer to the factory of the geometry.
* @param iData
* A pointer to the topological data.
* @param iBodyToRegularize
* The pointer to the body to process.
* @Use the SetTolerance() method to modify tolerance.
* @Use the GetResult() method to get result.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMHybRegularize *CATPGMCreateTopRegularize(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBodyToRegularize);

#endif /* CATPGMCreateTopRegularize_h_ */
