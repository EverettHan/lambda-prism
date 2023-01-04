#include "CATIntersectionCheckDiagnosisImplDefine.h"

// ---------- CATFaceFaceIntersectionCheckDiagnosis

void CATCGM_DIAG_IMPL_CLASS::GetIntersectedFaces(CATFace *&oFirstFace, CATFace *&oSecondFace) const
{
  _EmbeddedObject.GetIntersectedFaces(oFirstFace, oSecondFace);
}

int CATCGM_DIAG_IMPL_CLASS::GetAssociatedObjects(CATLISTP(CATGeometry) &ioAssociatedObjects) const
{
  return _EmbeddedObject.GetAssociatedObjects(ioAssociatedObjects);
}

CATFaceFaceIntersectionCheckDiagnosis *CATCGM_DIAG_IMPL_CLASS::Clone() const
{
  return _EmbeddedObject.Clone();
}
