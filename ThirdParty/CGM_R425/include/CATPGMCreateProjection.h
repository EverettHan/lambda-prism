#ifndef CATIPGMCreateProjection_h_
#define CATIPGMCreateProjection_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATCollec.h"
#include "CATDataType.h"
#include "CATSkillValue.h"

class CATCrvLimits;
class CATCurve;
class CATGeoFactory;
class CATIPGMListOfProjectionCrvSur;
class CATMathDirection;
class CATMathPoint;
class CATPoint;
class CATIPGMProjectionCrvSur;
class CATIPGMProjectionPtCrv;
class CATIPGMProjectionPtSur;
class CATSoftwareConfiguration;
class CATSurLimits;
class CATSurface;
class CATLISTP(CATSurface);
class CATLISTP(CATCurve);

/**
 * @level Protected
 * @usage U1
 */

/**
 * @deprecated V5R11
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMListOfProjectionCrvSur *CATPGMCreateProjection(
  CATGeoFactory *iWhere,
  const CATLISTP(CATCurve) *iCrvList,
  const CATLISTP(CATSurface) *iSurList,
  CATLONG32 iNPatchU,
  CATLONG32 iNPatchV,
  const CATMathDirection *iDirection = (const CATMathDirection*)0,
  CATSkillValue iMode = BASIC);

/**
 * @deprecated V5R13 CATPGMCreateProjection
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMProjectionCrvSur *CATPGMCreateProjection(
  CATGeoFactory *iWhere,

  const CATCurve *iCurve,
  const CATCrvLimits *iCrvLim,
  const CATSurface *iSurface,
  const CATSurLimits *iSurLim,
  const CATMathDirection *iDirection = (const CATMathDirection*)0,
  CATSkillValue iMode = BASIC);

/**
 * @deprecated V5R13 CATPGMCreateProjection
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMProjectionPtCrv *CATPGMCreateProjection(
  CATGeoFactory *iWhere,
  const CATPoint *iPoint,
  const CATCurve *iCurve,
  const CATMathDirection *iDirection = (const CATMathDirection*)0,
  CATSkillValue iMode = BASIC);

/**
 * @deprecated V5R13 CATPGMCreateProjection
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMProjectionPtSur *CATPGMCreateProjection(
  CATGeoFactory *iWhere,
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
ExportedByCATGMModelInterfaces CATIPGMProjectionPtCrv *CATPGMCreateProjection(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *iConfig,
  const CATPoint *iPoint,
  const CATCurve *iCurve,
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
ExportedByCATGMModelInterfaces CATIPGMProjectionPtSur *CATPGMCreateProjection(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *iConfig,
  const CATPoint *iPoint,
  const CATSurface *iSurface,
  const CATMathDirection *iDirection = (const CATMathDirection*)0,
  CATSkillValue iMode = BASIC);

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
ExportedByCATGMModelInterfaces CATIPGMProjectionCrvSur *CATPGMCreateProjection(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *iConfig,
  const CATCurve *iCurve,
  const CATCrvLimits *iCrvLim,
  const CATSurface *iSurface,
  const CATSurLimits *iSurLim,
  const CATMathDirection *iDirection = (const CATMathDirection*)0,
  CATSkillValue iMode = BASIC);

/**
 * @nodoc
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMListOfProjectionCrvSur *CATPGMCreateProjection(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *iConfig,
  const CATLISTP(CATCurve) *iCrvList,
  const CATLISTP(CATSurface) *iSurList,
  CATLONG32 iNPatchU,
  CATLONG32 iNPatchV,
  const CATMathDirection *iDirection = (const CATMathDirection*)0,
  CATSkillValue iMode = BASIC);

/**
 * @nodoc
 * Simpler/cleaner signature for CATProjectionPtCrv creation:
 * a CATMathPoint is passed instead of a CATPoint, CATCrvLimits must be specified,
 * BASIC mode isn't available.
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMProjectionPtCrv *CATPGMCreateProjection(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  const CATMathPoint &iPoint,
  const CATCurve *iCurve,
  const CATCrvLimits &iLimits,
  const CATMathDirection *iDirection = (const CATMathDirection*)0);


#endif /* CATIPGMCreateProjection_h_ */
