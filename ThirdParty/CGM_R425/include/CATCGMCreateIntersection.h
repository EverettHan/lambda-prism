#ifndef CATCGMCreateIntersection_h_
#define CATCGMCreateIntersection_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMModelInterfaces.h"
#include "CATSkillValue.h"

class CATCartesianPoint;
class CATCurve;
class CATGeoFactory;
class CATICGMIntersectionCrvCrv;
class CATICGMIntersectionCrvSur;
class CATICGMIntersectionSurSur;
//class CATICGMIntersectionTriSur;
class CATPCurve;
class CATPlane;
class CATPointOnCurve;
class CATPointOnSurface;
class CATSoftwareConfiguration;
class CATSurface;

/**
 * Creates an operator intersecting two surfaces.
 * @param iWhere
 * The pointer to the factory of the geometry.
 * @param iConfig
 * The pointer to configuration defining the level of code to replay.
 * @param iSurface1
 * The pointer to the first surface.
 * @param iSurface2
 * The pointer to the second surface.
 * @param iMode
 * The mode of use.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation.
 *     <dt><tt>ADVANCED</tt> <dd>Use the <tt>Run</tt> method to compute the operation.</dl>
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATICGMIntersectionSurSur *CATCGMCreateIntersection(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *iConfig,
  CATSurface *iSurface1,
  CATSurface *iSurface2,
  CATSkillValue iMode = BASIC);

/**
 * Creates an operator intersecting a curve and a surface.
 * @param iWhere
 * The pointer to the factory of the geometry. 
 * @param iConfig
 * The pointer to configuration defining the level of code to replay.
 * @param iCurve 
 * The pointer to the curve.
 * @param iSurface
 * The pointer to the surface.
 * @param iMode
 * The mode of use.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation.
 *     <dt><tt>ADVANCED</tt> <dd>Use the <tt>Run</tt> method to compute the operation.</dl>
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATICGMIntersectionCrvSur *CATCGMCreateIntersection(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *iConfig,
  CATCurve *iCurve,
  CATSurface *iSurface,
  CATSkillValue iMode = BASIC);

/**
 * Creates an operator intersecting two curves.
 * @param iWhere
 * The pointer to the factory of the geometry. 
 * @param iConfig
 * The pointer to configuration defining the level of code to replay.
 * @param iCurve1
 * The pointer to the first curve.
 * @param iCurve2
 * The pointer to the second curve.
 * @param iMode
 * The mode of use.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation.
 *     <dt><tt>ADVANCED</tt> <dd>Use the <tt>Run</tt> method to compute the operation.</dl>
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATICGMIntersectionCrvCrv *CATCGMCreateIntersection(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *iConfig,
  CATCurve *iCurve1,
  CATCurve *iCurve2,
  CATSkillValue iMode = BASIC);

#endif /* CATCGMCreateIntersection_h_ */

