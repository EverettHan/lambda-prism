#include "CATICGMVirtualImplDefine.h"

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

short CATCGM_ITF_IMPL_CLASS::GetSide()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetSide();
}

