#ifndef CATPGMCreateSurTo2DCompositionMapping_h_
#define CATPGMCreateSurTo2DCompositionMapping_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"

class CATGeoFactory;
class CATMathFunctionXY;
class CATIPGMSurTo2DGlobalCompositionMapping;
class CATIPGMSurTo2DGlobalMapping;



/**
* @deprecated V5R13 CATPGMCreateCompositionMapping
* @return [out, IUnknown#Release]
*/
ExportedByCATGMModelInterfaces CATIPGMSurTo2DGlobalCompositionMapping *CATPGMCreateCompositionMapping(
  CATGeoFactory *iFactory,
  CATIPGMSurTo2DGlobalMapping *iGlobalMapping,
  const CATMathFunctionXY *iNewX,
  const CATMathFunctionXY *iNewY,
  const CATMathFunctionXY *iOldX,
  const CATMathFunctionXY *iOldY);

#endif /* CATPGMCreateSurTo2DCompositionMapping_h_ */
