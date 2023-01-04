#ifndef CATPGMCreateCircularBody_h_
#define CATPGMCreateCircularBody_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"

class CATBody;
class CATCurve;
class CATGeoFactory;
class CATPlane;
class CATTopData;
class CATMathPoint;

/**
 * @nodoc
 */
ExportedByCATGMOperatorsInterfaces CATBody *CATPGMCreateCircularBody(
  CATGeoFactory *iFactory,
  CATMathPoint &iCentre,
  CATPlane *iPlane,
  double iRadius,
  CATTopData *iTopData);

#endif /* CATPGMCreateCircularBody_h_ */
