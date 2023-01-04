#ifndef CATEdgeEdgeIntersectionCheckDiagnosisImpl_h_
#define CATEdgeEdgeIntersectionCheckDiagnosisImpl_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATEdgeEdgeIntersectionCheckDiagnosis.h"
#include "CATEdgeEdgeIntersectionCheckDiagnosis_Embed.h"

#undef  CATCGM_DIAG_IMPL_CLASS
#define CATCGM_DIAG_IMPL_CLASS CATEdgeEdgeIntersectionCheckDiagnosisImpl

class ExportedByCheckOperators CATEdgeEdgeIntersectionCheckDiagnosisImpl: public CATEdgeEdgeIntersectionCheckDiagnosis
{
   public: // Methodes a usage externe
     
      //============================
      // Constucteurs et destructeurs
      //============================

      CATEdgeEdgeIntersectionCheckDiagnosisImpl(
                                            CATCheckDiagnosisLocation   iCheckDiagnosisLocation,
                                            CATEdge                   * iFirstIntersectedEdge,
                                            CATEdge                   * iSecondIntersectedEdge,
                                            CATDomain                 * iFirstIntersectedDomain,
                                            CATDomain                 * iSecondIntersectedDomain,
                                            CATTopology               * iTopologicalIntersection = (CATTopology*)0);

     CATEdgeEdgeIntersectionCheckDiagnosisImpl();
  
      virtual ~CATEdgeEdgeIntersectionCheckDiagnosisImpl();

// Declare the methods
#include "CATEdgeEdgeIntersectionCheckDiagnosisImplDeclare.h"

private:
  CATEdgeEdgeIntersectionCheckDiagnosisImpl(const CATEdgeEdgeIntersectionCheckDiagnosisImpl &iObject); // Prohibited
  CATEdgeEdgeIntersectionCheckDiagnosisImpl &operator=(const CATEdgeEdgeIntersectionCheckDiagnosisImpl &iObject); // Prohibited

  CATEdgeEdgeIntersectionCheckDiagnosis_Embed _EmbeddedObject;
};

#endif
