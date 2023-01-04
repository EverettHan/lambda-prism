#include "CATIPGMVirtualImplDeclare.h"

  // ---------- CATTopOperator

  virtual CATCGMJournalList *GetJournal() const;

  virtual void ReadInputBodies(
    CATLISTP(CATBody) &oListOfCopyInputBodies,
    CATLISTP(CATBody) &oListOfNoCopyInputBodies);

  virtual HRESULT Run();

  virtual CATBody *GetLiveResult() const;

