#ifndef CATPGMCreateTopProjectTrapError_h_
#define CATPGMCreateTopProjectTrapError_h_

// COPYRIGHT DASSAULT SYSTEMES 2009

#include "CATGMOperatorsInterfaces.h"

class CATIPGMHybProject;
class CATGeoFactory;
class CATTopData;
class CATBody;
class CATMathDirection;

/**
* no doc DAIMLER Chrysler issue Only
*/
ExportedByCATGMOperatorsInterfaces CATIPGMHybProject *CATPGMCreateTopProjectTrapError(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBodyToProject,
  CATBody *iBodySupport,
  CATMathDirection *iDirection = (CATMathDirection*)0);

#endif /* CATPGMCreateTopProjectTrapError_h_ */
