#ifndef CATICGMCreateConfusionPtOnSurPtOnSur_h_
#define CATICGMCreateConfusionPtOnSurPtOnSur_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMModelInterfaces.h"
#include "CATSkillValue.h"

class CATICGMConfusionPtOnSurPtOnSur;
class CATGeoFactory;
class CATPointOnSurface;
class CATSoftwareConfiguration;
class CATSurParam;
class CATSurface;

/**
 * Creates an operator for testing the overlap of two CATPointOnSurfaces,
 * with respect to the Geodesical length between the points.
 * @param iFactory
 * The pointer to the factory of the points.
 * @param iPoint1
 * The parameter of the first point.
 * @param iPoint2
 * The parameter of the second point.
 * @param iSurface
 * The pointer to the surface on which the points are lying on.
 * @param iTol
 * The distance for deciding the overlap.
 * @param iMode
 * <dl><dt><tt>BASIC</tt> <dd>the operation is performed at the operator creation
 *     <dt><tt>ADVANCED</tt><dd>otherwise (not implemented yet)</dl>
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATICGMConfusionPtOnSurPtOnSur *CATCGMCreateConfusion(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  const CATSurParam &iParam1,
  const CATSurParam &iParam2,
  const CATSurface *iSurface,
  const double iTol,
  CATSkillValue iMode = BASIC);

/**
 * Creates an operator for testing the overlap of two CATPointOnSurfaces,
 * with respect to the geodesical length between the points.
 *<br>The two points belong to the same CATSurface.
 * @param iFactory
 * The pointer to the factory of the points.
 * @param iPoint1
 * The pointer to the first point.
 * @param iPoint2
 * The pointer to the second point.
 * @param iTol
 * The distance for deciding the overlap.
 * @param iMode
 * <dl><dt><tt>BASIC</tt> <dd>the operation is performed at the operator creation
 *     <dt><tt>ADVANCED</tt><dd>otherwise (not implemented yet)</dl>
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATICGMConfusionPtOnSurPtOnSur *CATCGMCreateConfusion(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  const CATPointOnSurface *iPoint1,
  const CATPointOnSurface *iPoint2,
  const double iTol,
  CATSkillValue iMode = BASIC);

#endif /* CATICGMCreateConfusionPtOnSurPtOnSur_h_ */
