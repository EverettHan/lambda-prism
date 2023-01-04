#include "CATIPGMAttributeImplDefine.h"

// ---------- CATCGMStreamAttribute

void CATCGM_ITF_IMPL_CLASS::Stream(CATCGMStream &ioStream) const
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.Stream(ioStream);
}

void CATCGM_ITF_IMPL_CLASS::UnStream(CATCGMStream &ioStr)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.UnStream(ioStr);
}

void CATCGM_ITF_IMPL_CLASS::AddLink(CATICGMObject *iObject)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.AddLink(iObject);
}

void CATCGM_ITF_IMPL_CLASS::RemoveLink(CATICGMObject *iObject)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.RemoveLink(iObject);
}

void CATCGM_ITF_IMPL_CLASS::SetLinks(const CATLISTP(CATICGMObject) &iObjects)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.SetLinks(iObjects);
}

void CATCGM_ITF_IMPL_CLASS::GetLinks(CATLISTP(CATICGMObject) &ioLinkedObjects)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.GetLinks(ioLinkedObjects);
}

CATBoolean CATCGM_ITF_IMPL_CLASS::IsStreamable(
    const CATCGMStreamVersion iTargetVersion,
    CATBoolean &ioReversible) const
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.IsStreamable(
    iTargetVersion,
    ioReversible);
}

void CATCGM_ITF_IMPL_CLASS::SetMustStreamForStreamCompact(int iMustStreamForStreamCompact)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.SetMustStreamForStreamCompact(iMustStreamForStreamCompact);
}

int CATCGM_ITF_IMPL_CLASS::MustStreamForStreamCompact() const
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.MustStreamForStreamCompact();
}

