#ifndef CATPGMCreateBreakCurve_h_
#define CATPGMCreateBreakCurve_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATDataType.h"
#include "CATSkillValue.h"

class CATBreakCurve;
class CATGeoFactory;
class CATNurbsCurve;
class CATPointOnCurve;

//
ExportedByCATGMOperatorsInterfaces CATBreakCurve *CATPGMCreateBreakCurve(
  CATGeoFactory *iFactory,
  CATPointOnCurve *iPtBreak,
  CATSkillValue iMode = BASIC);

/**
 * Ascending compatibility for client frameworks. This inline function must be deleted once clients call
 * CATPGMCreateBreakCurve.
 */
inline CATBreakCurve *CreateBreakCurve(
  CATGeoFactory *iFactory,
  CATPointOnCurve *iPtBreak,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateBreakCurve(iFactory, iPtBreak, iMode);
}

ExportedByCATGMOperatorsInterfaces CATBreakCurve *CATPGMCreateBreakCurve(
  CATGeoFactory *iFactory,
  CATNurbsCurve *iCrvToBreak,
  CATLONG32 iKnotRank,
  CATSkillValue iMode = BASIC);

/**
 * Ascending compatibility for client frameworks. This inline function must be deleted once clients call
 * CATPGMCreateBreakCurve.
 */
inline CATBreakCurve *CreateBreakCurve(
  CATGeoFactory *iFactory,
  CATNurbsCurve *iCrvToBreak,
  CATLONG32 iKnotRank,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateBreakCurve(iFactory, iCrvToBreak, iKnotRank, iMode);
}

//
ExportedByCATGMOperatorsInterfaces
void Remove( CATBreakCurve *&iBreakCurve );

#endif /* CATPGMCreateBreakCurve_h_ */
