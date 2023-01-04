#ifndef CATPGMCreateTopProjectSimplif_h_
#define CATPGMCreateTopProjectSimplif_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"

class CATIPGMHybProject;
class CATGeoFactory;
class CATTopData;
class CATBody;
class CATMathDirection;

// COPYRIGHT DASSAULT SYSTEMES  2005
/** @nodoc
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMHybProject *CATPGMCreateTopProjectSimplif(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBodyToProject,
  CATBody *iBodySupport,
  CATMathDirection *iDirection = (CATMathDirection*)0);

#endif /* CATPGMCreateTopProjectSimplif_h_ */
