#ifndef CATPGMCreateCrvParametricExtend_h_
#define CATPGMCreateCrvParametricExtend_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATSkillValue.h"

class CATCrvParam;
class CATCrvParametricExtend;
class CATNurbsCurve;
class CATSoftwareConfiguration;

ExportedByCATGMOperatorsInterfaces CATCrvParametricExtend *CATPGMCreateCrvParametricExtend(
  CATSoftwareConfiguration *iSoft,
  CATNurbsCurve *iNurbsCrv,
  const CATCrvParam &iCrvParam,
  const double &iExtendRatio,
  CATSkillValue iMode = BASIC);

/**
 * Ascending compatibility for client frameworks. This inline function must be deleted once clients call
 * CATPGMCreateCrvParametricExtend.
 */
inline CATCrvParametricExtend *CreateCrvParametricExtend(
  CATSoftwareConfiguration *iSoft,
  CATNurbsCurve *iNurbsCrv,
  const CATCrvParam &iCrvParam,
  const double &iExtendRatio,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateCrvParametricExtend(iSoft, iNurbsCrv, iCrvParam, iExtendRatio, iMode);
}

//DO NOT USE ANYMORE. USE PREVIOUS CREATE INSTEAD.
ExportedByCATGMOperatorsInterfaces CATCrvParametricExtend *CATPGMCreateCrvParametricExtend(
  CATNurbsCurve *iNurbsCrv,
  const CATCrvParam &iCrvParam,
  const double &iExtendRatio,
  CATSkillValue iMode = BASIC);

/**
 * Ascending compatibility for client frameworks. This inline function must be deleted once clients call
 * CATPGMCreateCrvParametricExtend.
 */
inline CATCrvParametricExtend *CreateCrvParametricExtend(
  CATNurbsCurve *iNurbsCrv,
  const CATCrvParam &iCrvParam,
  const double &iExtendRatio,
  CATSkillValue iMode = BASIC)
{
  return CATPGMCreateCrvParametricExtend(iNurbsCrv, iCrvParam, iExtendRatio, iMode);
}

//
ExportedByCATGMOperatorsInterfaces
void Remove( CATCrvParametricExtend *&iCrvParametricExtend );

#endif /* CATPGMCreateCrvParametricExtend_h_ */
