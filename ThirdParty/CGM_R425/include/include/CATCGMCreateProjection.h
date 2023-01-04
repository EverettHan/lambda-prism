#ifndef CATICGMCreateProjection_h_
#define CATICGMCreateProjection_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMModelInterfaces.h"
#include "CATSkillValue.h"

class CATCrvLimits;
class CATCurve;
class CATGeoFactory;
//class CATICGMListOfProjectionCrvSur;
class CATMathDirection;
class CATMathPoint;
class CATPoint;
class CATICGMProjectionCrvSur;
class CATICGMProjectionPtCrv;
class CATICGMProjectionPtSur;
class CATSoftwareConfiguration;
class CATSurLimits;
class CATSurface;

/**
 * Creates an operator for projecting a CATCurve onto a CATSurface.
 *<br>The projection is orthogonal or along a direction.
 * @param iWhere
 * The pointer to the factory of the geometry. 
 * @param iCurve
 * The pointer to the curve to project.
 * @param iCrvLim
 * The pointer to the domain limiting the curve. This does not change the current limitations of the curve.
 * @param iSurface
 * The pointer to the surface on which the point is projected.
 * @param iSurLim
 * The pointer to the domain limiting the surface. This does not change the current limitations of the surface.
 * @param iDirection
 * The pointer to the direction along which the point is projected, <tt>0</tt> for a normal projection.
 * @param iMode
 * <dl><dt><tt>BASIC</tt> <dd>the operation is performed at the operator creation
 *     <dt><tt>ADVANCED</tt><dd>otherwise </dl>
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATICGMProjectionCrvSur *CATCGMCreateProjection(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *iConfig,
  const CATCurve *iCurve,
  const CATCrvLimits *iCrvLim,
  const CATSurface *iSurface,
  const CATSurLimits *iSurLim,
  const CATMathDirection *iDirection = (const CATMathDirection*)0,
  CATSkillValue iMode = BASIC);

/**
 * Creates an operator for projecting a CATPoint onto a CATSurface.
 *<br>The projection is orthogonal or along a direction.
 *  @param iWhere
 * The pointer to the factory of the geometry. 
 * @param iPoint
 * The pointer to the point to project.
 * @param iSurface
 * The pointer to the surface on which the point is projected.
 * @param iDirection
 * The pointer to the direction along which the point is projected, <tt>0</tt> for a normal projection.
 * @param iMode
 * <dl><dt><tt>BASIC</tt> <dd>the operation is performed at the operator creation
 *     <dt><tt>ADVANCED</tt><dd>otherwise </dl>
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATICGMProjectionPtSur *CATCGMCreateProjection(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *iConfig,
  const CATPoint *iPoint,
  const CATSurface *iSurface,
  const CATMathDirection *iDirection = (const CATMathDirection*)0,
  CATSkillValue iMode = BASIC);

/**
 * Creates an operator for projecting a CATPoint onto a CATCurve.
 *<br>The projection is orthogonal or along a direction.
 *  @param iWhere
 * The pointer to the factory of the geometry. 
 * @param iPoint
 * The pointer to the point to project.
 * @param iCurve
 * The pointer to the curve on which the point is projected.
 * @param iDirection
 * The pointer to the direction along which the point is projected, <tt>0</tt> for a normal projection.
 * @param iMode
 * <dl><dt><tt>BASIC</tt> <dd>the operation is performed at the operator creation
 *     <dt><tt>ADVANCED</tt><dd>otherwise </dl>
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATICGMProjectionPtCrv *CATCGMCreateProjection(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *iConfig,
  const CATPoint *iPoint,
  const CATCurve *iCurve,
  const CATMathDirection *iDirection = (const CATMathDirection*)0,
  CATSkillValue iMode = BASIC);

#endif /* CATICGMCreateProjection_h_ */
