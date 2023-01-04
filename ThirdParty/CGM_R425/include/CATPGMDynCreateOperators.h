#ifndef CATPGMDynCreateOperators_h_
#define CATPGMDynCreateOperators_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATSkillValue.h"
#include "CATMathDef.h"

class CATIPGMCornerPCrvPCrv;
class CATCrvLimits;
class CATCurve;
class CATIPGMDistanceCrvSur;
class CATIPGMDistanceMinCrvCrv;
class CATIPGMDistanceMinPtCrv;
class CATIPGMDistanceMinPtSur;
class CATIPGMDistanceSurSur;
class CATIPGMExtractSameTangent;
class CATGeoFactory;
class CATIPGMIntersectionCrvCrv;
class CATIPGMIntersectionCrvSur;
class CATIPGMIntersectionSurSur;
class CATMathDirection;
class CATPCurve;
class CATPoint;
class CATPointOnSurface;
class CATIPGMProjectionCrvSur;
class CATIPGMProjectionPtCrv;
class CATIPGMProjectionPtSur;
class CATSurLimits;
class CATSurface;
class CATSoftwareConfiguration;

//------------------------------------------------------------------------------
// Distance Mins
//------------------------------------------------------------------------------
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMDistanceMinPtCrv *CATPGMDynCreateDistanceMin(
  CATGeoFactory *iFactory,
  CATPoint *iPt,
  CATCurve *iCrv,
  CATSkillValue iMode = BASIC);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMDistanceMinPtSur *CATPGMDynCreateDistanceMin(
  CATGeoFactory *iFactory,
  const CATPoint *Pt,
  const CATSurface *Sur,
  CATBoolean SearchOnBoundary = 1,
  CATSkillValue mode = BASIC);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMDistanceMinCrvCrv *CATPGMDynCreateDistanceMin(
  CATGeoFactory *iFactory,
  const CATCurve *iCrv1,
  const CATCurve *iCrv2,
  CATSkillValue mode = BASIC);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMDistanceCrvSur *CATPGMDynCreateDistanceMin(
  CATGeoFactory *iFactory,
  const CATCurve *iCurve,
  const CATSurface *iSurface,
  CATSkillValue mode = BASIC);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMDistanceSurSur *CATPGMDynCreateDistanceMin(
  CATGeoFactory *iFactory,
  const CATSurface *iSur1,
  const CATSurface *iSur2,
  CATSkillValue mode = BASIC);

//------------------------------------------------------------------------------
// Projections
//------------------------------------------------------------------------------
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMProjectionPtCrv *CATPGMDynCreateProjection(
  CATGeoFactory *iFactory,
  const CATPoint *iPoint,
  const CATCurve *iCurve,
  const CATMathDirection *iDirection = (const CATMathDirection*)0,
  CATSkillValue iMode = BASIC);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMProjectionPtSur *CATPGMDynCreateProjection(
  CATGeoFactory *iFactory,
  const CATPoint *iPoint,
  const CATSurface *iSurface,
  const CATMathDirection *iDirection = (const CATMathDirection*)0,
  CATSkillValue iMode = BASIC);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMProjectionCrvSur *CATPGMDynCreateProjection(
  CATGeoFactory *iFactory,
  const CATCurve *iCurve,
  const CATCrvLimits *iCrvLim,
  const CATSurface *iSurface,
  const CATSurLimits *iSurLim,
  const CATMathDirection *iDirection = (const CATMathDirection*)0,
  CATSkillValue iMode = BASIC);

//------------------------------------------------------------------------------
// Intersections
//------------------------------------------------------------------------------
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMIntersectionCrvCrv *CATPGMDynCreateIntersection(
  CATGeoFactory *iFactory,
  CATCurve *iCurve1,
  CATCurve *iCurve2,
  CATSkillValue mode = BASIC);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMIntersectionCrvSur *CATPGMDynCreateIntersection(
  CATGeoFactory *iFactory,
  CATCurve *iCurve,
  CATSurface *iSurface,
  CATSkillValue mode = BASIC);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMIntersectionSurSur *CATPGMDynCreateIntersection(
  CATGeoFactory *iFactory,
  CATSurface *iSurface1,
  CATSurface *iSurface2,
  CATSkillValue mode = BASIC);

//------------------------------------------------------------------------------
// CornerPCrvPCrv
//------------------------------------------------------------------------------
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMCornerPCrvPCrv *CATPGMDynCreateCornerPCrvPCrv(
  CATGeoFactory *iFactory,
  CATPCurve *PCurve1,
  CATPCurve *PCurve2,
  CATPointOnSurface *PPoint,
  CATPositiveLength &Radius,
  CATSkillValue imode);

//------------------------------------------------------------------------------
// ExtractSameTangent - for Drafting
//------------------------------------------------------------------------------
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMExtractSameTangent *CATPGMDynCreateExtractSameTangent(
  CATGeoFactory *iFactory,
  CATCurve *iCurve,
  CATMathDirection &iDirection,
  CATSkillValue iMode = BASIC,
  CATSoftwareConfiguration *iConfig = 0);

#endif /* CATPGMDynCreateOperators_h_ */
