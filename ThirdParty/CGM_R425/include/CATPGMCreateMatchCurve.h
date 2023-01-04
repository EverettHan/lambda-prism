#ifndef CATPGMCreateMatchCurve_h_
#define CATPGMCreateMatchCurve_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATSkillValue.h"

class CATCrvParam;
class CATCurve;
class CATGeoFactory;
class CATMatchCurve;
class CATPoint;
class CATPointOnCurve;
class CATSoftwareConfiguration;

// DO NOT USE
ExportedByCATGMOperatorsInterfaces CATMatchCurve *CATPGMCreateMatchCurve(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration* iSoftwareConfiguration,
  const CATPointOnCurve *iLimitPoint,
  const CATCurve *iCrvMatched,
  const CATCurve *iCrvRef,
  const CATCrvParam &iParamPtRef,
  CATSkillValue iMode = BASIC);

// DO NOT USE
// DEPRECATED
ExportedByCATGMOperatorsInterfaces CATMatchCurve *CATPGMCreateMatchCurve(
  CATGeoFactory *iFactory,
  const CATPointOnCurve *iLimitPoint,
  const CATCurve *iCrvMatched,
  const CATCurve *iCrvRef,
  const CATCrvParam &iParamPtRef,
  CATSkillValue iMode = BASIC);

/**
 * Ascending compatibility for client frameworks. This inline function must be deleted once clients call
 * CATPGMCreateMatchCurve.
 */
// DO NOT USE
inline CATMatchCurve *CreateMatchCurve(
  CATGeoFactory *iFactory,
  const CATPointOnCurve *iLimitPoint,
  const CATCurve *iCrvMatched,
  const CATCurve *iCrvRef,
  const CATCrvParam &iParamPtRef,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateMatchCurve(iFactory, iLimitPoint, iCrvMatched, iCrvRef, iParamPtRef, iMode);
}

ExportedByCATGMOperatorsInterfaces CATMatchCurve *CATPGMCreateMatchCurve(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration* iSoftwareConfiguration,
  const CATPointOnCurve *iLimitPoint,
  const CATCurve *iCrvMatched,
  CATPoint *iRefPoint,
  CATSkillValue iMode = BASIC);

ExportedByCATGMOperatorsInterfaces CATMatchCurve *CATPGMCreateMatchCurve(
  CATGeoFactory *iFactory,
  const CATPointOnCurve *iLimitPoint,
  const CATCurve *iCrvMatched,
  CATPoint *iRefPoint,
  CATSkillValue iMode = BASIC);

/**
 * Ascending compatibility for client frameworks. This inline function must be deleted once clients call
 * CATPGMCreateMatchCurve.
 */
inline CATMatchCurve *CreateMatchCurve(
  CATGeoFactory *iFactory,
  const CATPointOnCurve *iLimitPoint,
  const CATCurve *iCrvMatched,
  CATPoint *iRefPoint,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateMatchCurve(iFactory, iLimitPoint, iCrvMatched, iRefPoint, iMode);
}

ExportedByCATGMOperatorsInterfaces
void Remove( CATMatchCurve *&iMatchCurve );

#endif /* CATPGMCreateMatchCurve_h_ */
