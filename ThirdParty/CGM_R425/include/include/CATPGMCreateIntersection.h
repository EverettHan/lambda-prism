#ifndef CATPGMCreateIntersection_h_
#define CATPGMCreateIntersection_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @level Protected
 * @usage U1
 */

#include "CATGMModelInterfaces.h"
#include "CATSkillValue.h"
#include "CATBoolean.h"

class CATCartesianPoint;
class CATCurve;
class CATGeoFactory;
class CATIPGMIntersectionCrvCrv;
class CATIPGMIntersectionCrvSur;
class CATIPGMIntersectionSurSur;
class CATIPGMIntersectionTriSur;
class CATPCurve;
class CATPlane;
class CATPointOnCurve;
class CATPointOnSurface;
class CATSoftwareConfiguration;
class CATSurface;

// COPYRIGHT DASSAULT SYSTEMES 2002

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
 * <br><b>Warning</b><br>:
 * For performance reasons, the operator does not support having twice the same geometry in arguments.
 * @param iMode
 * The mode of use.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation.
 *     <dt><tt>ADVANCED</tt> <dd>Use the <tt>Run</tt> method to compute the operation.</dl>
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATIPGMIntersectionCrvCrv *CATPGMCreateIntersection(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *iConfig,
  CATCurve *iCurve1,
  CATCurve *iCurve2,
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
ExportedByCATGMModelInterfaces CATIPGMIntersectionCrvSur *CATPGMCreateIntersection(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *iConfig,
  CATCurve *iCurve,
  CATSurface *iSurface,
  CATSkillValue iMode = BASIC);

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
ExportedByCATGMModelInterfaces CATIPGMIntersectionSurSur *CATPGMCreateIntersection(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *iConfig,
  CATSurface *iSurface1,
  CATSurface *iSurface2,
  CATSkillValue iMode = BASIC);

/**
 * @nodoc
 * Like CreateIntersection but requires a CATSoftwareConfiguration.
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMIntersectionSurSur *CATPGMCreateIntersectionWithInits(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *iConfig,
  CATSurface *iSurface1,
  CATSurface *iSurface2,
  CATSkillValue iMode = BASIC);

/**
 * @nodoc
 * Like CreateIntersection but requires a CATSoftwareConfiguration.
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMIntersectionSurSur *CATPGMCreateIntersectionPlnSur(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *iConfig,
  CATPlane *iPlane,
  CATSurface *iSurface,
  CATSkillValue iMode);

/**
 * @nodoc
 * Like CreateIntersection but requires a CATSoftwareConfiguration.
 * @return [out, IUnknown#Release]
 */
// sdp 04avr03- j'ajoute l'argument CATSoftwareConfiguration malencontreusement omis
// a la creation de ce header. a priori sans consequence du point de vue CAA car
// c'est une fonction globale en nodoc
ExportedByCATGMModelInterfaces CATIPGMIntersectionTriSur *CATPGMCreateIntersectionTriSur(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *iConfig,
  CATSurface *iSurface1,
  CATSurface *iSurface2,
  CATSurface *iSurface3,
  CATSkillValue iMode = BASIC);

/**
* @deprecated V5R11 CATPGMCreateIntersection
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMIntersectionCrvCrv *CATPGMCreateIntersection(
  CATGeoFactory *iWhere,
  CATCurve *iCurve1,
  CATCurve *iCurve2,
  CATSkillValue iMode = BASIC);

/**
* @deprecated V5R11 CATPGMCreateIntersection
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMIntersectionCrvSur *CATPGMCreateIntersection(
  CATGeoFactory *iWhere,
  CATCurve *iCurve,
  CATSurface *iSurface,
  CATSkillValue iMode = BASIC);

/**
* @deprecated V5R11 CATPGMCreateIntersection
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMIntersectionSurSur *CATPGMCreateIntersection(
  CATGeoFactory *iWhere,
  CATSurface *iSurface1,
  CATSurface *iSurface2,
  CATSkillValue iMode = BASIC,
  CATBoolean iRelimitation = FALSE);

/**
 * @nodoc
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMIntersectionSurSur *CATPGMCreateIntersectionWithInits(
  CATGeoFactory *iWhere,
  CATSurface *iSurface1,
  CATSurface *iSurface2,
  CATSkillValue iMode = BASIC);

/**
 * @nodoc
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMIntersectionSurSur *CATPGMCreateIntersectionPlnSur(
  CATGeoFactory *iWhere,
  CATPlane *iPlane,
  CATSurface *iSurface,
  CATSkillValue iMode = BASIC);

/**
 * @nodoc
* Use now @href CATPGMCreateIntersection.
* @return [out, IUnknown#Release]
*/
ExportedByCATGMModelInterfaces CATIPGMIntersectionTriSur *CATPGMCreateIntersectionTriSur(
  CATGeoFactory *iWhere,
  CATSurface *iSurface1,
  CATSurface *iSurface2,
  CATSurface *iSurface3,
  CATSkillValue iMode = BASIC);

#endif /* CATPGMCreateIntersection_h_ */
