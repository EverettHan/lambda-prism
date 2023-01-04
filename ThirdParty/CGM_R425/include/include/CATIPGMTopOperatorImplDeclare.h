#include "CATIACGMLevel.h" // automatic treatment EB_2014_04_16
#include "CATIPGMOperatorImplDeclare.h"

  // ---------- CATTopOperator

  virtual CATBody *GetResult();

  virtual CATBody *GetResult(CATCGMJournalList *iJournal);

  virtual void SetFreezeMode(CATBodyFreezeMode iOnOrOff);

  virtual CATBodyFreezeMode GetFreezeMode() const;

  virtual CATCGMJournalList *GetJournal();

  virtual void GetInputObjectsForJournal(
    CATBoolean &oSucceeded,
    CATLISTP(CATICGMObject) &oObjects,
    CATTopCheckJournalType iCopy_Or_Not,
    CATGeometricType iTypeOfObjects);

/* Already declared in a parent class
#ifdef CATIACGMV5R21
  virtual void EnableInterrupt(CATCGMInterruptFunction ipInterruptFunction);
#endif
*/

  virtual CATBoolean HasConsistentResult(
    CATLONG32 &nberr,
    CATError **&Diagnostic) const;

  virtual void GetTopData(CATTopData &oTopData) const;

  virtual void SetSoftwareConfiguration(CATSoftwareConfiguration *iConfig);

/* Already defined in a parent class
  virtual CATSoftwareConfiguration *GetSoftwareConfiguration() const;
*/

  virtual CATTopOpInError *GetWarning();

  virtual void AppendWarning(CATCGMDiagnosis *iWarning);

  virtual void RemoveAllWarning();

  virtual int BasicCheckJournal(int iLevelOfCheck, CATCGMOutput *iForceDump);

  virtual CATBoolean GivesBodyAsResult() const;

  virtual CATBoolean GivesValidJournalAsResult(
    CATCGMJournalList **ioDuplicatedButExpectedValid) const;

  virtual CATExtTopOperator *GetTopExtensible(CATBoolean iRequired) const;

  virtual void CreateManifolds(
    CATLISTP(CATBody) &iListOfInputBodies,
    CATBody *iOutputBody,
    CATCGMJournalList *iTopOpJournal,
    CATCGMJournalList *ioManifoldBasedJournal);

  virtual HRESULT AppendDeclarativeManifoldAgent(CATDeclarativeManifoldAgent *&ioAgent);

  virtual CATBody *GetLiveResult();

  virtual CATBody *GetLiveResult(CATCGMJournalList *ioManifoldBasedJournal);

  virtual CATContextForFastRun *GetContextForFastRun(CATBoolean iGetOnly);

  virtual void EnableCellTracker(CATBoolean iEnable);
 
  virtual CATBoolean IsCellTrackerEnable();

  virtual CATCGMCellTracker *CreateCellTracker(); 

#if (defined(CATIACGMV5R21) || defined(CATIAR210))
  virtual void ReadInputBodies(
    CATLISTP(CATBody) &oListOfCopyInputBodies,
    CATLISTP(CATBody) &oListOfNoCopyInputBodies);
#endif

#ifdef CATIACGMV5R22

  virtual void SetVoBTool(CATCGMVoBTool *iTool);

  virtual void GetVoBResults(
    CATLISTP(CATCGMVoBResult) &iFailureResults,
    CATBoolean iBlock,
    CATBoolean &iCompletion);
#endif

#ifdef CATIACGMR215CAA
  virtual void SetDRepBehavior(CATPGMDRepBehavior *iDRepBehavior);

  virtual void SetFailsafeMode(CATBoolean iFailsafeMode);

  virtual CATBoolean GetFailsafeMode();

  virtual void GetFailsafeDiagnosis(
    CATLISTP(CATCGMDiagnosis) &oFailsafeDiagnosis);
#endif

