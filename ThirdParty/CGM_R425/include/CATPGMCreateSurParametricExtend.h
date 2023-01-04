#ifndef CATPGMCreateSurParametricExtend_h_
#define CATPGMCreateSurParametricExtend_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATSkillValue.h"

class CATNurbsSurface;
class CATSoftwareConfiguration;
class CATSurParam;
class CATSurParametricExtend;

ExportedByCATGMOperatorsInterfaces CATSurParametricExtend *CATPGMCreateSurParametricExtend(
  CATSoftwareConfiguration *iSoft,
  CATNurbsSurface *iNurbsSur,
  const CATSurParam &iSurParam,
  const double &iExtendRatio,
  CATSkillValue iMode = BASIC);

/**
 * Ascending compatibility for client frameworks. This inline function must be deleted once clients call
 * CATPGMCreateSurParametricExtend.
 */
inline CATSurParametricExtend *CreateSurParametricExtend(
  CATSoftwareConfiguration *iSoft,
  CATNurbsSurface *iNurbsSur,
  const CATSurParam &iSurParam,
  const double &iExtendRatio,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateSurParametricExtend(iSoft, iNurbsSur, iSurParam, iExtendRatio, iMode);
}

//DO NOT USE ANYMORE. USE PREVIOUS CREATE INSTEAD.
ExportedByCATGMOperatorsInterfaces CATSurParametricExtend *CATPGMCreateSurParametricExtend(
  CATNurbsSurface *iNurbsSur,
  const CATSurParam &iSurParam,
  const double &iExtendRatio,
  CATSkillValue iMode = BASIC);

/**
 * Ascending compatibility for client frameworks. This inline function must be deleted once clients call
 * CATPGMCreateSurParametricExtend.
 */
inline CATSurParametricExtend *CreateSurParametricExtend(
  CATNurbsSurface *iNurbsSur,
  const CATSurParam &iSurParam,
  const double &iExtendRatio,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateSurParametricExtend(iNurbsSur, iSurParam, iExtendRatio, iMode);
}

//
ExportedByCATGMOperatorsInterfaces
void Remove( CATSurParametricExtend *&iSurParametricExtend );

#endif /* CATPGMCreateSurParametricExtend_h_ */
