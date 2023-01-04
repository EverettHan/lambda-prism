#include "CATICGMOperatorImplDefine.h"

// ---------- CATTopOperator

CATBody *CATCGM_ITF_IMPL_CLASS::GetResult()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return ((CATTopOperator &)HandledObject).GetResult(); // OVERRIDEN IN CATTopSewSkin
}

CATBody *CATCGM_ITF_IMPL_CLASS::GetResult(CATCGMJournalList *iJournal)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return ((CATTopOperator &)HandledObject).GetResult(iJournal); // OVERRIDEN IN CATRecomposeShells
}

#ifndef CATCGM_ITF_OverrideTopOperatorFreezeMode // CATHybOperator overrides these methods with another signature...

void CATCGM_ITF_IMPL_CLASS::SetFreezeMode(CATBodyFreezeMode iOnOrOff)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.SetFreezeMode(iOnOrOff);
}

CATBodyFreezeMode CATCGM_ITF_IMPL_CLASS::GetFreezeMode() const
{
  const CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetFreezeMode();
}

#endif /* CATCGM_ITF_OverrideTopOperatorFreezeMode */

CATCGMJournalList *CATCGM_ITF_IMPL_CLASS::GetJournal()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetJournal();
}

void CATCGM_ITF_IMPL_CLASS::GetInputObjectsForJournal(
    CATBoolean &oSucceeded,
    CATLISTP(CATICGMObject) &oObjects,
    CATTopCheckJournalType iCopy_Or_Not,
    CATGeometricType iTypeOfObjects)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.GetInputObjectsForJournal(
    oSucceeded,
    oObjects,
    iCopy_Or_Not,
    iTypeOfObjects);
}

void CATCGM_ITF_IMPL_CLASS::SetFailsafeMode(CATBoolean iFailsafeMode)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.SetFailsafeMode(iFailsafeMode);
}

CATBoolean CATCGM_ITF_IMPL_CLASS::GetFailsafeMode()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetFailsafeMode();
}

void CATCGM_ITF_IMPL_CLASS::GetFailsafeDiagnosis(
    CATLISTP(CATCGMDiagnosis) &oFailsafeDiagnosis)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.GetFailsafeDiagnosis(
    oFailsafeDiagnosis);
}

