#ifndef CATPGMCreateSurFittingToNurbsSur_h_
#define CATPGMCreateSurFittingToNurbsSur_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATDataType.h"
#include "CATSkillValue.h"

class CATIPGMSurFittingToNurbsSur;
class CATGeoFactory;
class CATSurface;

//DO NOT USE -- USE CATPGMCreateSurFittingToNurbsSur
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMSurFittingToNurbsSur *CATPGMCreateSurFittingToNurbsSur(
  CATGeoFactory *iFactory,
  const CATSurface &iSurface,
  double iMaxDeviation,
  CATLONG32 iRationalAllowed = 1,
  CATSkillValue iMode = BASIC);

#endif /* CATPGMCreateSurFittingToNurbsSur_h_ */
