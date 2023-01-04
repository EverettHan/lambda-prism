#include "CATIPGMDistanceToolImplDefine.h"

// ---------- CATEnhancedDistanceTool

CATLONG32 CATCGM_ITF_IMPL_CLASS::ValidateInitSide(
    CATCurve *iCurve,
    CATCrvParam &iCrvParam,
    CATSurface *iSurface,
    CATSurParam &iSurParam,
    double iRadiusValue,
    double *iTangent3D,
    double *oProduct)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.ValidateInitSide(
    iCurve,
    iCrvParam,
    iSurface,
    iSurParam,
    iRadiusValue,
    iTangent3D,
    oProduct);
}

CATLONG32 CATCGM_ITF_IMPL_CLASS::ProjectOnOriginalSurface(
    CATCurve *iCurve,
    CATCrvParam &iParam,
    CATSurface *&oOriginalSurface,
    CATPCurve *&oOriginalPCurve,
    CATCrvParam &oParam,
    CATSurParam &oCorrespondingParam)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.ProjectOnOriginalSurface(
    iCurve,
    iParam,
    oOriginalSurface,
    oOriginalPCurve,
    oParam,
    oCorrespondingParam);
}

CATEdgeCurve *CATCGM_ITF_IMPL_CLASS::GetMaps2DCurve(CATCurve *iCurve, CATCrvParam &iCrvParam)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetMaps2DCurve(iCurve, iCrvParam);
}

void CATCGM_ITF_IMPL_CLASS::GetNewSmoothing(CATLONG32 &oSmooth)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.GetNewSmoothing(oSmooth);
}

