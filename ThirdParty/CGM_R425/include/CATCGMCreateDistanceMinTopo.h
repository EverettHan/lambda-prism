#ifndef CATCGMCreateDistanceMinTopo_h_
#define CATCGMCreateDistanceMinTopo_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATSkillValue.h"

class CATBody;
class CATCell;
class CATICGMDistanceMinBodyBody;
class CATDomain;
class CATGeoFactory;
class CATTopData;

/**
 * @nodoc
 * @deprecated V5R27-R419 CATCGMCreateDistanceBodyBodyOp
 * This API has been deprecated. 
 * Please use the new API instead:
 *   CATICGMDistanceBodyBody (created using CATCGMCreateDistanceBodyBodyOp)
 *
 * Creates an operator for computing the minimum distance between two CATBody.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. The journal inside <tt>iData</tt> 
 * is not filled. 
 * @param iBody1
 * The pointer to the first body.
 * @param iBody2
 * The pointer to the second body.
 * @param iMode
 * The mode of use.
 * <br><b>Legal values</b>: 
 *<dl><dt><tt>BASIC</tt></dt><dd> for triggering the computation at the operator creation
 *<dt><tt>ADVANCED</tt></dt><dd> for delaying the computation after the operator creation. Meanwhile,
 * parameters can be set to tune the operator.</dl>
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method.
 */
ExportedByCATGMOperatorsInterfaces CATICGMDistanceMinBodyBody *CATCGMCreateDistanceMinTopo(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBody1,
  CATBody *iBody2,
  CATSkillValue iMode = BASIC);

#endif /* CATCGMCreateDistanceMinTopo_h_ */
