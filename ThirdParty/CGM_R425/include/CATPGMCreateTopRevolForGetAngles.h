#ifndef CATPGMCreateTopRevolForGetAngles_h_
#define CATPGMCreateTopRevolForGetAngles_h_

// COPYRIGHT DASSAULT SYSTEMES 2015

#include "CATGMOperatorsInterfaces.h"

class CATGeoFactory;
class CATTopData;
class CATBody;
class CATMathAxis;
typedef double CATAngle;
class CATIPGMTopRevol;

/**
 * @nodoc
 * @return [out, IUnknown#Release]
*/

ExportedByCATGMOperatorsInterfaces CATIPGMTopRevol *CATPGMCreateTopRevolForGetAngles(
  CATGeoFactory *iGeoFactory,
  CATTopData *iData,
  CATBody *iProfBody,
  CATMathAxis *iAxis,
  CATAngle iStartAngle,
  CATAngle iEndAngle);

#endif /* CATPGMCreateTopRevolForGetAngles_h_ */
