#include "CATIPGMVirtualImplDefine.h"
#include "CATIACGMLevel.h"
#include "CATExtTopOperator.h"

// ---------- CATTopOperator

CATCGMJournalList *CATCGM_ITF_IMPL_CLASS::GetJournal() const
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetJournal();
}

void CATCGM_ITF_IMPL_CLASS::ReadInputBodies(
    CATLISTP(CATBody) &oListOfCopyInputBodies,
    CATLISTP(CATBody) &oListOfNoCopyInputBodies)
{
  CATTopOperator &HandledObject = (CATTopOperator &)_InternalData.GetHandledObject();

#if (defined(CATIACGMV5R21) || defined(CATIAR210))
  HandledObject.ReadInputBodies(
    oListOfCopyInputBodies,
    oListOfNoCopyInputBodies);

#else
  CATExtTopOperator::CATTopOperator_ReadInputBodies(&HandledObject, oListOfCopyInputBodies, oListOfNoCopyInputBodies);
#endif
}

HRESULT CATCGM_ITF_IMPL_CLASS::Run()
{
  CATTopOperator &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HRESULT hr = S_OK;

  CATTry
  {
    HandledObject.Run();
  }
  CATCatch(CATError, error)
  {
    hr = error->GetReturnCode();
    error->CATSetLastError();
    error->Release();
  }
  CATEndTry;

  return hr;
}

CATBody *CATCGM_ITF_IMPL_CLASS::GetLiveResult() const
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetLiveResult();
}
