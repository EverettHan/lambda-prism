#ifndef CATPGMCreateBlendCurve_h_
#define CATPGMCreateBlendCurve_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATSkillValue.h"

class CATBlendCurve;
class CATCrvParam;
class CATCurve;
class CATGeoFactory;

ExportedByCATGMOperatorsInterfaces CATBlendCurve *CATPGMCreateBlendCurve(
  CATGeoFactory *iFactory,
  const CATCurve *iCurve1,
  const CATCrvParam &iCrvParam1,
  const CATCurve *iCurve2,
  const CATCrvParam &iCrvParam2,
  CATSkillValue iMode = BASIC);

/**
 * Ascending compatibility for client frameworks. This inline function must be deleted once clients call
 * CATPGMCreateBlendCurve.
 */
inline CATBlendCurve *CreateBlendCurve(
  CATGeoFactory *iFactory,
  const CATCurve *iCurve1,
  const CATCrvParam &iCrvParam1,
  const CATCurve *iCurve2,
  const CATCrvParam &iCrvParam2,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateBlendCurve(iFactory, iCurve1, iCrvParam1, iCurve2, iCrvParam2, iMode);
}

ExportedByCATGMOperatorsInterfaces
void Remove( CATBlendCurve *&iBlendCurve );

#endif /* CATPGMCreateBlendCurve_h_ */
