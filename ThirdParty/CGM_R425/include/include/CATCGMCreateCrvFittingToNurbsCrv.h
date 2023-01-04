#include "CATDataType.h"
#ifndef CATCGMCreateCrvFittingToNurbsCrv_h_
#define CATCGMCreateCrvFittingToNurbsCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATDataType.h"
#include "CATSkillValue.h"

class CATICGMCrvFittingToNurbsCrv;
class CATGeoFactory;
class CATCurve;

//DO NOT USE -- USE CATCGMCreateCrvFittingToNurbsCrv with CATTopData
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATICGMCrvFittingToNurbsCrv *CATCGMCreateCrvFittingToNurbsCrv(
  CATGeoFactory *iFactory,
  const CATCurve &iCurve,
  double iMaxDeviation,
  CATLONG32 iRationalAllowed = 1,
  CATSkillValue iMode = BASIC);

#endif /* CATCGMCreateCrvFittingToNurbsCrv_h_ */
