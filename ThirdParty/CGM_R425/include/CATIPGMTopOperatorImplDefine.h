#include "CATIACGMLevel.h" // automatic treatment EB_2014_04_16
#include "CATIPGMOperatorImplDefine.h"

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

/* Already declared in a parent class
#ifdef CATIACGMV5R21
void CATCGM_ITF_IMPL_CLASS::EnableInterrupt(CATCGMInterruptFunction ipInterruptFunction)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.EnableInterrupt(ipInterruptFunction);
}
#endif
*/

CATBoolean CATCGM_ITF_IMPL_CLASS::HasConsistentResult(
    CATLONG32 &nberr,
    CATError **&Diagnostic) const
{
  const CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.HasConsistentResult(
    nberr,
    Diagnostic);
}

void CATCGM_ITF_IMPL_CLASS::GetTopData(CATTopData &oTopData) const
{
  const CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.GetTopData(oTopData);
}

void CATCGM_ITF_IMPL_CLASS::SetSoftwareConfiguration(CATSoftwareConfiguration *iConfig)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.SetSoftwareConfiguration(iConfig);
}

/* Already defined in a parent class
CATSoftwareConfiguration *CATCGM_ITF_IMPL_CLASS::GetSoftwareConfiguration() const
{
  const CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetSoftwareConfiguration();
}
*/

CATTopOpInError *CATCGM_ITF_IMPL_CLASS::GetWarning()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetWarning();
}

void CATCGM_ITF_IMPL_CLASS::AppendWarning(CATCGMDiagnosis *iWarning)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.AppendWarning(iWarning);
}

void CATCGM_ITF_IMPL_CLASS::RemoveAllWarning()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.RemoveAllWarning();
}

int CATCGM_ITF_IMPL_CLASS::BasicCheckJournal(int iLevelOfCheck, CATCGMOutput *iForceDump)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.BasicCheckJournal(iLevelOfCheck, iForceDump);
}

CATBoolean CATCGM_ITF_IMPL_CLASS::GivesBodyAsResult() const
{
  const CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GivesBodyAsResult();
}

CATBoolean CATCGM_ITF_IMPL_CLASS::GivesValidJournalAsResult(
    CATCGMJournalList **ioDuplicatedButExpectedValid) const
{
  const CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GivesValidJournalAsResult(
    ioDuplicatedButExpectedValid);
}

CATExtTopOperator *CATCGM_ITF_IMPL_CLASS::GetTopExtensible(CATBoolean iRequired) const
{
  const CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetTopExtensible(iRequired);
}

void CATCGM_ITF_IMPL_CLASS::CreateManifolds(
    CATLISTP(CATBody) &iListOfInputBodies,
    CATBody *iOutputBody,
    CATCGMJournalList *iTopOpJournal,
    CATCGMJournalList *ioManifoldBasedJournal)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.CreateManifolds(
    iListOfInputBodies,
    iOutputBody,
    iTopOpJournal,
    ioManifoldBasedJournal);
}

HRESULT CATCGM_ITF_IMPL_CLASS::AppendDeclarativeManifoldAgent(CATDeclarativeManifoldAgent *&ioAgent)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.AppendDeclarativeManifoldAgent(ioAgent);
}

CATBody *CATCGM_ITF_IMPL_CLASS::GetLiveResult()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetLiveResult();
}

CATBody *CATCGM_ITF_IMPL_CLASS::GetLiveResult(CATCGMJournalList *ioManifoldBasedJournal)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetLiveResult(ioManifoldBasedJournal);
}

CATContextForFastRun *CATCGM_ITF_IMPL_CLASS::GetContextForFastRun(CATBoolean iGetOnly)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetContextForFastRun(iGetOnly);
}

void CATCGM_ITF_IMPL_CLASS::EnableCellTracker(CATBoolean iEnable)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.EnableCellTracker(iEnable);
}

CATBoolean CATCGM_ITF_IMPL_CLASS::IsCellTrackerEnable()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.IsCellTrackerEnable();
}

CATCGMCellTracker *CATCGM_ITF_IMPL_CLASS::CreateCellTracker()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.CreateCellTracker();
}

#if (defined(CATIACGMV5R21) || defined(CATIAR210))
void CATCGM_ITF_IMPL_CLASS::ReadInputBodies(
    CATLISTP(CATBody) &oListOfCopyInputBodies,
    CATLISTP(CATBody) &oListOfNoCopyInputBodies)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.ReadInputBodies(
    oListOfCopyInputBodies,
    oListOfNoCopyInputBodies);
}
#endif

void CATCGM_ITF_IMPL_CLASS::SetVoBTool(CATCGMVoBTool *iTool)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.SetVoBTool(iTool);
}

void CATCGM_ITF_IMPL_CLASS::GetVoBResults(
    CATLISTP(CATCGMVoBResult) &iFailureResults,
    CATBoolean iBlock,
    CATBoolean &iCompletion)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.GetVoBResults(
    iFailureResults,
    iBlock,
    iCompletion);
}

void CATCGM_ITF_IMPL_CLASS::SetDRepBehavior(CATPGMDRepBehavior *iDRepBehavior)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.SetDRepBehavior(iDRepBehavior);
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

