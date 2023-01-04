#include "CATIPGMVirtualImplDefine.h"

// ---------- CATCGMAttribute

int CATCGM_ITF_IMPL_CLASS::IsPersistent()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.IsPersistent();
}

const CATCGMAttrId *CATCGM_ITF_IMPL_CLASS::GetCGMAttrId() const
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetCGMAttrId();
}

int CATCGM_ITF_IMPL_CLASS::IsATypeOf(const CATCGMAttrId *iId)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.IsATypeOf(iId);
}

CATULONG32 CATCGM_ITF_IMPL_CLASS::AddAttrRef()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.AddAttrRef();
}

CATULONG32 CATCGM_ITF_IMPL_CLASS::ReleaseAttrRef()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.ReleaseAttrRef();
}

CATULONG32 CATCGM_ITF_IMPL_CLASS::GetNbAttrRef() const
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetNbAttrRef();
}

void CATCGM_ITF_IMPL_CLASS::Dump(CATCGMOutput &os)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.Dump(os);
}

short CATCGM_ITF_IMPL_CLASS::IsDirty()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.IsDirty();
}

const CATCGMAttributeDef *CATCGM_ITF_IMPL_CLASS::GetAttributeDef() const
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetAttributeDef();
}

void CATCGM_ITF_IMPL_CLASS::PutObject(CATICGMObject *iToPoint)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.PutObject(iToPoint);
}

