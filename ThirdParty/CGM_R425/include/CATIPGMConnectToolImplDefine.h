#include "CATIPGMOperatorImplDefine.h"

// ---------- CATConnectTool

CATLONG32 CATCGM_ITF_IMPL_CLASS::GetType() const
{
  const CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetType();
}

void CATCGM_ITF_IMPL_CLASS::SetOriginCurveSupport(CATSurface *iSupp, CATLONG32 iOrient)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.SetOriginCurveSupport(iSupp, iOrient);
}

void CATCGM_ITF_IMPL_CLASS::GetOriginCurveSupport(CATSurface *&oSupp, CATLONG32 &oOrient)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.GetOriginCurveSupport(oSupp, oOrient);
}

CATGeoODTScaleManager *CATCGM_ITF_IMPL_CLASS::GetScaleManager() const
{
  const CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetScaleManager();
}

void CATCGM_ITF_IMPL_CLASS::SetScaleManager(CATGeoODTScaleManager *iScaleManager)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.SetScaleManager(iScaleManager);
}

CATLONG32 CATCGM_ITF_IMPL_CLASS::GetSectionType() const
{
  const CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetSectionType();
}

