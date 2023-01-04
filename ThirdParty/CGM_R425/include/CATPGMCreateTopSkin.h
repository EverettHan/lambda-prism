#ifndef CATPGMCreateTopSkin_h_
#define CATPGMCreateTopSkin_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "IUnknown.h"
#include "CATCollec.h"

#ifndef NULL
#define NULL 0
#endif

class CATPlane;
class CATTopData;
class CATIPGMTopSkin;
class CATGeoFactory;
class CATPCurve;
class CATCrvLimits;
class CATBody;
class CATSurface;
class CATMathBox;

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopSkin *CATPGMCreateTopOldSkin(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATSurface *iSurface,
  int iNbPcurves,
  CATPCurve **iPcurves,
  CATCrvLimits *iLims,
  CATBody *TargetBody = NULL);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopSkin *CATPGMCreateTopOldSkin(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATSurface *iSurface,
  int iNbPcurves,
  CATPCurve **iPcurves,
  CATBody *TargetBody = NULL);

// to keep
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopSkin *CATPGMCreateTopOldSkin(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATPlane *plane,
  CATMathBox &iBox,
  CATBody *TargetBody = NULL);

// to delete
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopSkin *CATPGMCreateTopSkin(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATPlane *plane,
  CATMathBox &iBox);

#endif /* CATPGMCreateTopSkin_h_ */
