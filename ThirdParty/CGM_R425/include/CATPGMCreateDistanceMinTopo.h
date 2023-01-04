#ifndef CATPGMCreateDistanceMinTopo_h_
#define CATPGMCreateDistanceMinTopo_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATSkillValue.h"

class CATBody;
class CATCell;
class CATIPGMDistanceMinBodyBody;
class CATDomain;
class CATGeoFactory;
class CATTopData;

/** 
 * @deprecated V5R14
 * This API has been deprecated. 
 * Please use the new API instead:
 *   CATICGMDistanceBodyBody (created using CATCGMCreateDistanceBodyBodyOp)
 * Use the signature with CATBody. 
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDistanceMinBodyBody *CATPGMCreateDistanceMinTopo(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATCell *iCell1,
  CATCell *iCell2,
  CATSkillValue iMode = BASIC);

/**
 * @nodoc
 * This API has been deprecated. 
 * Please use the new API instead:
 *   CATICGMDistanceBodyBody (created using CATCGMCreateDistanceBodyBodyOp)
 * Creates an operator for computing the minimum distance between two CATCell.
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDistanceMinBodyBody *CATPGMCreateDistanceMinTopo(
  CATGeoFactory *iFactory,
  CATCell *iCell1,
  CATCell *iCell2,
  CATSkillValue iMode = BASIC);

/** 
 * @deprecated V5R14
 * This API has been deprecated. 
 * Please use the new API instead:
 *   CATICGMDistanceBodyBody (created using CATCGMCreateDistanceBodyBodyOp)
 * Use the signature with CATBody. 
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDistanceMinBodyBody *CATPGMCreateDistanceMinTopo(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATDomain *iDomain1,
  CATDomain *iDomain2,
  CATSkillValue iMode = BASIC);

/**
 * @nodoc
 * This API has been deprecated. 
 * Please use the new API instead:
 *   CATICGMDistanceBodyBody (created using CATCGMCreateDistanceBodyBodyOp)
 * Creates an operator for computing the minimum distance between two CATDomain.
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDistanceMinBodyBody *CATPGMCreateDistanceMinTopo(
  CATGeoFactory *iFactory,
  CATDomain *iDomain1,
  CATDomain *iDomain2,
  CATSkillValue iMode = BASIC);

/**
 * This API has been deprecated. 
 * Please use the new API instead:
 *   CATICGMDistanceBodyBody (created using CATCGMCreateDistanceBodyBodyOp)
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
 * The pointer to the created operator. To be released with the <tt>Release</tt> method
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDistanceMinBodyBody *CATPGMCreateDistanceMinTopo(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBody1,
  CATBody *iBody2,
  CATSkillValue iMode = BASIC);

/** @nodoc
 * This API has been deprecated. 
 * Please use the new API instead:
 *   CATICGMDistanceBodyBody (created using CATCGMCreateDistanceBodyBodyOp)
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDistanceMinBodyBody *CATPGMCreateDistanceMinTopo(
  CATGeoFactory *iFactory,
  CATBody *iBody1,
  CATBody *iBody2,
  CATSkillValue iMode = BASIC);

#endif /* CATPGMCreateDistanceMinTopo_h_ */
