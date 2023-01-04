#include "CATIPGMVirtualImplDefine.h"

// ---------- CATDistanceTool

short CATCGM_ITF_IMPL_CLASS::GetType() const
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetType();
}

CATCompositeLaw *CATCGM_ITF_IMPL_CLASS::GetCompositeLaw()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetCompositeLaw();
}

CATCompositeLaw *CATCGM_ITF_IMPL_CLASS::GetLaw()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetLaw();
}

short CATCGM_ITF_IMPL_CLASS::GetSide()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetSide();
}

void CATCGM_ITF_IMPL_CLASS::SetSide(short iSide)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.SetSide(iSide);
}

