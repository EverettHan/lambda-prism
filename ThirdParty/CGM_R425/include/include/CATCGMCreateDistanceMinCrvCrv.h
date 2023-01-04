#ifndef CATICGMCreateDistanceMinCrvCrv_h_
#define CATICGMCreateDistanceMinCrvCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMModelInterfaces.h"
#include "CATICGMVirtual.h"
#include "CATSkillValue.h"

class CATCurve;
class CATICGMDistanceMinCrvCrv;
class CATGeoFactory;
class CATSoftwareConfiguration;

/**
 * Creates an operator for computing the minimum distance between two curves.
 * @param iWhere
 * The pointer to the factory of the curves. 
 * @param iConfig
 * The pointer to configuration defining the level of code to replay.
 * @param iCrv1
 * The pointer to the first curve.
 * @param iCrv2
 * The pointer to the second curve.
 * @param iMode
 * The mode of use.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation.
 *     <dt><tt>ADVANCED</tt> <dd>Use the <tt>Run</tt> method to compute the operation.</dl>
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATICGMDistanceMinCrvCrv *CATCGMCreateDistanceMin(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *iConfig,
  CATCurve *iCrv1,
  CATCurve *iCrv2,
  CATSkillValue iMode = BASIC);

#endif /* CATICGMCreateDistanceMinCrvCrv_h_ */
