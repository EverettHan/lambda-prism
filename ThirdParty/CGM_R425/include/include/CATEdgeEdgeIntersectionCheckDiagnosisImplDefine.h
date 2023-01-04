#include "CATIntersectionCheckDiagnosisImplDefine.h"

// ---------- CATEdgeEdgeIntersectionCheckDiagnosis

void CATCGM_DIAG_IMPL_CLASS::GetIntersectedEdges(CATEdge *&oFirstEdge, CATEdge *&oSecondEdge) const
{
  _EmbeddedObject.GetIntersectedEdges(oFirstEdge, oSecondEdge);
}
