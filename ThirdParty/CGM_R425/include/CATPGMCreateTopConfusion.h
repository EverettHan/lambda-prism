#ifndef CATPGMCreateTopConfusion_h_
#define CATPGMCreateTopConfusion_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"

class CATGeoFactory;
class CATTopData;
class CATBody;
class CATIPGMHybConfusion;

// COPYRIGHT DASSAULT SYSTEMES  2000
//========================================================================
// 
//  Confusion Operator Body onto Body : 
// 
//========================================================================
/**
* Constructs an operator that analyze FULL confusion between Bodies.
* <br>This operator allows to check 
* <ul><li>a shell on a shell or a volume
* </ul>
* The candidate body and the support body can contain several domains.
* </ul>
* @param iFactory
* A pointer to the factory of the resulting body.
* @param iData
* A pointer to the topological data.
* @param iBodyCandidate
* A pointer to the body to check confusion on iBodySupport. 
* @param iBodySupport
* A pointer to the support body.
* @return [out, IUnknown#Release]
*/
ExportedByCATGMOperatorsInterfaces CATIPGMHybConfusion *CATPGMCreateTopConfusion(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBodyCandidate,
  CATBody *iBodySupport);

#endif /* CATPGMCreateTopConfusion_h_ */
