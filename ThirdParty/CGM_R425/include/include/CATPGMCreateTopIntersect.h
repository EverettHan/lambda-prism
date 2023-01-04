#ifndef CATPGMCreateTopIntersect_h_
#define CATPGMCreateTopIntersect_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"

class CATIPGMHybIntersect;
class CATGeoFactory;
class CATTopData;
class CATBody;

/**
* @level Protected
* @usage U1
*/
/**
* Constructs an operator that intersects two bodies.
* <br>The bodies to intersect can contain several domains.
* @param iFactory
* The pointer to the factory of the geometry.
* @param iData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
* is <tt>NULL</tt>, it is not filled. 
* @param iBody1ToIntersect
* The pointer to the first body to intersect. It can contain several 
* domains. In this case, the operator only processes the domains of highest dimension.
* @param iBody2ToIntersect
* The pointer to the second body to intersect. It can contain several 
* domains. In this case, the operator only processes the domains of highest dimension.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMHybIntersect *CATPGMCreateTopIntersect(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBody1ToIntersect,
  CATBody *iBody2ToIntersect);

#endif /* CATPGMCreateTopIntersect_h_ */
