#ifndef CATPGMCreateExtruder_h_
#define CATPGMCreateExtruder_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"

class CATPGMExtruder;
class CATGeoFactory;
class CATMathAxis;
class CATMathPoint;
class CATSoftwareConfiguration;

ExportedByCATGMOperatorsInterfaces CATPGMExtruder *CATPGMCreateExtruderByCircle(
  CATGeoFactory *iWhere,
  const CATMathAxis &iRef,
  CATSoftwareConfiguration *iSoftwareConfiguration);

ExportedByCATGMOperatorsInterfaces CATPGMExtruder *CATPGMCreateExtruderByLine(
  CATGeoFactory *iWhere,
  const CATMathPoint &iRef,
  CATSoftwareConfiguration *iSoftwareConfiguration);

#endif /* CATPGMCreateExtruder_h_ */
