#ifndef CATPGMCreateDistanceMaxTopo_h_
#define CATPGMCreateDistanceMaxTopo_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"

class CATBody;
class CATIPGMDistanceMaxBodyBody;
class CATGeoFactory;
class CATTopData;



/**
 * Creates an operator for computing the maximum normal distance from body1 to body2.
 * The input surfaces (or volume) must be G1 continuous.
 * You must SetInitializationPoints, this set of MathPoint is approximated, as computed on the tesselation of the two surfaces,
 * then reconverged on the exact geometries.
 * If reconvergence on exact geometries fails, we keep the approximate distance but computed on the exact geometries.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. The journal inside <tt>iData</tt> 
 * is not filled. 
 * @param iBody1
 * The pointer to the first body.
 * @param iBody2
 * The pointer to the second body.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDistanceMaxBodyBody *CATPGMCreateDistanceMaxTopo(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBody1,
  CATBody *iBody2);

#endif /* CATPGMCreateDistanceMaxTopo_h_ */
