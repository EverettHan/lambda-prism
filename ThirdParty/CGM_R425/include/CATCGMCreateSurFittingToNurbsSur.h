#ifndef CATCGMCreateSurFittingToNurbsSur_h_
#define CATCGMCreateSurFittingToNurbsSur_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATDataType.h"
#include "CATSkillValue.h"

class CATICGMSurFittingToNurbsSur;
class CATGeoFactory;
class CATSurface;

//DO NOT USE -- USE CATCGMCreateSurFittingToNurbsSur
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATICGMSurFittingToNurbsSur *CATCGMCreateSurFittingToNurbsSur(
  CATGeoFactory *iFactory,
  const CATSurface &iSurface,
  double iMaxDeviation,
  CATLONG32 iRationalAllowed = 1,
  CATSkillValue iMode = BASIC);

#endif /* CATCGMCreateSurFittingToNurbsSur_h_ */
