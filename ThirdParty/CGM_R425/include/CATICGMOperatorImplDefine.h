#include "CATICGMVirtualImplDefine.h"

// ---------- CATCGMOperator

int CATCGM_ITF_IMPL_CLASS::Run()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.Run();
}

CATGeoFactory *CATCGM_ITF_IMPL_CLASS::GetFactory() const
{
  const CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return ((const CATCGMOperator &)HandledObject).GetFactory(); // OVERRIDEN IN CATSolidPrimitive
}

const CATString *CATCGM_ITF_IMPL_CLASS::GetOperatorId()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return ((CATCGMOperator &)HandledObject).GetOperatorId(); // OVERRIDEN IN CATLayDownOperatorImpl
}

void CATCGM_ITF_IMPL_CLASS::SetOperatorId(const CATString iOperatorName)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.SetOperatorId(iOperatorName);
}

