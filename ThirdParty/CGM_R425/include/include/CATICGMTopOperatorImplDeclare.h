#include "CATICGMOperatorImplDeclare.h"

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

  virtual void SetFailsafeMode(CATBoolean iFailsafeMode);
  
  virtual CATBoolean GetFailsafeMode();
  
  virtual void GetFailsafeDiagnosis(
    CATLISTP(CATCGMDiagnosis) &oFailsafeDiagnosis);

