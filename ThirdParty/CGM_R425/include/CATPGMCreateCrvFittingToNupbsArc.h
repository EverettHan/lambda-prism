#ifndef CATPGMCreateCrvFittingToNupbsArc_h_
#define CATPGMCreateCrvFittingToNupbsArc_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATDataType.h"
#include "CATSkillValue.h"

class CATCrvFittingToNupbsArc;
class CATCrvLimits;
class CATCurve;
class CATGeoFactory;
class CATNurbsCurve;
class CATPNurbs;
class CATSoftwareConfiguration;

ExportedByCATGMOperatorsInterfaces CATCrvFittingToNupbsArc *CATPGMCreateCrvFittingToNupbsArc(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  const CATCurve *iCrvToConvert,
  const CATCrvLimits *iCrvLim,
  const CATLONG32 &iDimension,
  const double &iToler,
  const CATLONG32 &iMaxDegree,
  CATSkillValue iMode = BASIC);

// DEPRECATED
ExportedByCATGMOperatorsInterfaces CATCrvFittingToNupbsArc *CATPGMCreateCrvFittingToNupbsArc(
  CATGeoFactory *iFactory,
  const CATCurve *iCrvToConvert,
  const CATCrvLimits *iCrvLim,
  const CATLONG32 &iDimension,
  const double &iToler,
  const CATLONG32 &iMaxDegree,
  CATSkillValue iMode = BASIC);

/**
 * Ascending compatibility for client frameworks. This inline function must be deleted once clients call
 * CATPGMCreateCrvFittingToNupbsArc.
 */
inline CATCrvFittingToNupbsArc *CreateCrvFittingToNupbsArc(
  CATGeoFactory *iFactory,
  const CATCurve *iCrvToConvert,
  const CATCrvLimits *iCrvLim,
  const CATLONG32 &iDimension,
  const double &iToler,
  const CATLONG32 &iMaxDegree,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateCrvFittingToNupbsArc(iFactory, iCrvToConvert, iCrvLim, iDimension, iToler, iMaxDegree, iMode);
}

//
ExportedByCATGMOperatorsInterfaces
void Remove( CATCrvFittingToNupbsArc *&iCrvFittingToNupbsArc );

#endif /* CATPGMCreateCrvFittingToNupbsArc_h_ */
