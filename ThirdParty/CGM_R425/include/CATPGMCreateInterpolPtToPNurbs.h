#ifndef CATPGMCreateInterpolPtToPNurbs_h_
#define CATPGMCreateInterpolPtToPNurbs_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATDataType.h"
#include "CATSkillValue.h"

class CATGeoFactory;
class CATInterpolPtToPNurbs;
class CATMathPointsND;
class CATMathSetOfPointsND;
class CATNurbsCurve;
class CATSurface;

ExportedByCATGMOperatorsInterfaces CATInterpolPtToPNurbs *CATPGMCreateInterpolPtToPNurbs(
  CATGeoFactory *iFactory,
  const CATMathSetOfPointsND *iPoints,
  const CATLONG32 &nvar0,
  const CATLONG32 &nvar1,
  const CATLONG32 &nvar2,
  CATSurface *iSupport,
  CATSkillValue iMode = BASIC);

/**
 * Ascending compatibility for client frameworks. This inline function must be deleted once clients call
 * CATPGMCreateInterpolPtToPNurbs.
 */
inline CATInterpolPtToPNurbs *CreateInterpolPtToPNurbs(
  CATGeoFactory *iFactory,
  const CATMathSetOfPointsND *iPoints,
  const CATLONG32 &nvar0,
  const CATLONG32 &nvar1,
  const CATLONG32 &nvar2,
  CATSurface *iSupport,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateInterpolPtToPNurbs(iFactory, iPoints, nvar0, nvar1, nvar2, iSupport, iMode);
}

ExportedByCATGMOperatorsInterfaces
void Remove( CATInterpolPtToPNurbs *&iCATInterpolPtToPNurbs );

#endif /* CATPGMCreateInterpolPtToPNurbs_h_ */
