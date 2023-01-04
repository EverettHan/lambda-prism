#include "CATCheckDiagnosisImplDeclare.h"

  // ---------- CATIntersectionCheckDiagnosis

  virtual CATCheckDiagnosisLocation GetCheckDiagnosisLocation() const;

  virtual const char *GetCheckDiagnosisLocationAsString() const;

  virtual void GetIntersectedDomains(
    CATDomain *&oFirstDomain,
    CATDomain *&oSecondDomain) const;

  virtual void GetIntersectedCells(
    CATCell *&oFirstCell,
    CATCell *&oSecondCell) const;
