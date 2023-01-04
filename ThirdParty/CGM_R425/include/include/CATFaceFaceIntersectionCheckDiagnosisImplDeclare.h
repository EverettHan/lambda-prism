#include "CATIntersectionCheckDiagnosisImplDeclare.h"

  // ---------- CATFaceFaceIntersectionCheckDiagnosis

  virtual void GetIntersectedFaces(CATFace *&oFirstFace, CATFace *&oSecondFace) const;

  virtual int GetAssociatedObjects(CATLISTP(CATGeometry) &ioAssociatedObjects) const;

  virtual CATFaceFaceIntersectionCheckDiagnosis *Clone() const;
