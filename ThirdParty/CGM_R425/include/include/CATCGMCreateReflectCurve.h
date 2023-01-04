#ifndef CATICGMCreateReflectCurve_h_
#define CATICGMCreateReflectCurve_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMModelInterfaces.h"
#include "CATMathConstant.h"
#include "CATSkillValue.h"

class CATCurve;
class CATGeoFactory;
class CATPCurve;
class CATICGMReflectCurve;
class CATSoftwareConfiguration;
class CATSurface;
class CATMathDirection;

/**
 * Creates an operator for the computation of the reflect curves.
 * <br>The reflect curves are the set of points of a surface such that the surface normal 
 * at these points and a direction defines a constant angle.
 * @param iWhere
 * The pointer to the factory of the geometry.
 * @param iSur
 * The pointer to the surface on which the curves are computed.
 * @param iDir
 * The direction.
 * @param iAngle
 * The constant angle between the surface normal at a point of the reflect curve 
 * and the direction <tt>iDir</tt>.
 * @param iMode
 * The mode of use.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation (only available).
 *     <dt><tt>ADVANCED</tt>  <dd>Use the <tt>Run</tt> method to computes the operation (not implemented yet).</dl>
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATICGMReflectCurve *CATCGMCreateReflectCurve(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATSurface *iSur,
  CATMathDirection &iDir,
  CATAngle iAngle = 0.,
  CATSkillValue mode = BASIC);

#endif /* CATICGMCreateReflectCurve_h_ */
