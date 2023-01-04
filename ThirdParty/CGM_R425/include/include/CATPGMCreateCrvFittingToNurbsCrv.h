#ifndef CATPGMCreateCrvFittingToNurbsCrv_h_
#define CATPGMCreateCrvFittingToNurbsCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATDataType.h"
#include "CATSkillValue.h"

class CATIPGMCrvFittingToNurbsCrv;
class CATGeoFactory;
class CATCurve;

//DO NOT USE -- USE CATPGMCreateCrvFittingToNurbsCrv
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMCrvFittingToNurbsCrv *CATPGMCreateCrvFittingToNurbsCrv(
  CATGeoFactory *iFactory,
  const CATCurve &iCurve,
  double iMaxDeviation,
  CATLONG32 iRationalAllowed = 1,
  CATSkillValue iMode = BASIC);

#endif /* CATPGMCreateCrvFittingToNurbsCrv_h_ */
