#ifndef CATFaceFaceIntersectionCheckDiagnosisImpl_h_
#define CATFaceFaceIntersectionCheckDiagnosisImpl_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATFaceFaceIntersectionCheckDiagnosis.h"
#include "CATFaceFaceIntersectionCheckDiagnosis_Embed.h"

#undef  CATCGM_DIAG_IMPL_CLASS
#define CATCGM_DIAG_IMPL_CLASS CATFaceFaceIntersectionCheckDiagnosisImpl

class ExportedByCheckOperators CATFaceFaceIntersectionCheckDiagnosisImpl: public CATFaceFaceIntersectionCheckDiagnosis
{
   public: // Methodes a usage externe
     
      //============================
      // Constucteur et destructeurs
      //============================

      CATFaceFaceIntersectionCheckDiagnosisImpl(CATCheckDiagnosisLocation   iCheckDiagnosisLocation,
                                            CATFace                   * iFirstIntersectedFace,
                                            CATFace                   * iSecondIntersectedFace,
                                            CATShell                  * iFirstIntersectedDomain,
                                            CATShell                  * iSecondIntersectedDomain,
                                            CATTopology               * iTopologicalIntersection  = (CATTopology*)0,
                                            CATLISTP(CATGeometry)     * iTopologicalIntersections = (CATLISTP(CATGeometry)*)0);

      CATFaceFaceIntersectionCheckDiagnosisImpl();

      virtual ~CATFaceFaceIntersectionCheckDiagnosisImpl();

// Declare the methods
#include "CATFaceFaceIntersectionCheckDiagnosisImplDeclare.h"

private:
  CATFaceFaceIntersectionCheckDiagnosisImpl(const CATFaceFaceIntersectionCheckDiagnosisImpl &iObject); // Prohibited
  CATFaceFaceIntersectionCheckDiagnosisImpl &operator=(const CATFaceFaceIntersectionCheckDiagnosisImpl &iObject); // Prohibited

  CATFaceFaceIntersectionCheckDiagnosis_Embed _EmbeddedObject;
};

#endif
