#ifndef CATPGMTopCreateRibbonHomotopy_h_
#define CATPGMTopCreateRibbonHomotopy_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATTopDefine.h"

class CATBody;
class CATIPGMConnectTool;
class CATEdge;
class CATGeoFactory;
class CATMathPoint;
class CATTopData;
class CATIPGMTopRibbonHomotopy;
class CATIPGMConnectTool;
class CATFace;
class CATMathDirection;

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopRibbonHomotopy *CATPGMTopCreateRibbonHomotopy(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody,
  CATEdge *iEdge,
  const CATMathPoint &iPoint,
  CATIPGMConnectTool *iProfilePtr);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopRibbonHomotopy *CATPGMTopCreateRibbonHomotopy(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody,
  CATFace *iLeftFace,
  CATFace *iRightFace,
  CATFace *iCentreFace,
  const CATOrientation *iOri,
  const CATMathDirection &iDir,
  const CATMathPoint &iPoint,
  CATIPGMConnectTool *iProfilePtr);

#endif /* CATPGMTopCreateRibbonHomotopy_h_ */
