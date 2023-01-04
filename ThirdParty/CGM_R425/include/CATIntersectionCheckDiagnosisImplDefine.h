#include "CATCheckDiagnosisImplDefine.h"

// ---------- CATIntersectionCheckDiagnosis

CATCheckDiagnosisLocation CATCGM_DIAG_IMPL_CLASS::GetCheckDiagnosisLocation() const
{
  return _EmbeddedObject.GetCheckDiagnosisLocation();
}

const char *CATCGM_DIAG_IMPL_CLASS::GetCheckDiagnosisLocationAsString() const
{
  return _EmbeddedObject.GetCheckDiagnosisLocationAsString();
}

void CATCGM_DIAG_IMPL_CLASS::GetIntersectedDomains(
    CATDomain *&oFirstDomain,
    CATDomain *&oSecondDomain) const
{
  _EmbeddedObject.GetIntersectedDomains(
    oFirstDomain,
    oSecondDomain);
}

void CATCGM_DIAG_IMPL_CLASS::GetIntersectedCells(
    CATCell *&oFirstCell,
    CATCell *&oSecondCell) const
{
  _EmbeddedObject.GetIntersectedCells(
    oFirstCell,
    oSecondCell);
}
