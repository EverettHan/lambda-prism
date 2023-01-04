#ifndef CATIntersectionCheckDiagnosisImpl_h_
#define CATIntersectionCheckDiagnosisImpl_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATIntersectionCheckDiagnosis.h"
#include "CATIntersectionCheckDiagnosis_Embed.h"

#undef  CATCGM_DIAG_IMPL_CLASS
#define CATCGM_DIAG_IMPL_CLASS CATIntersectionCheckDiagnosisImpl

class ExportedByCheckOperators CATIntersectionCheckDiagnosisImpl: public CATIntersectionCheckDiagnosis
{
   public: // Methodes a usage externe
     
      //============================
      // Constucteur et destructeurs
      //============================

      CATIntersectionCheckDiagnosisImpl(CATCheckDiagnosisLocation   iIntersectionLocation,
                                    CATDomain                 * iFirstIntersectedDomain,
                                    CATDomain                 * iSecondIntersectedDomain,
                                    CATTopology               * iAssociatedTopology = (CATTopology*)0);

      CATIntersectionCheckDiagnosisImpl();
                        
      virtual ~CATIntersectionCheckDiagnosisImpl();

// Declare the methods
#include "CATIntersectionCheckDiagnosisImplDeclare.h"

private:
  CATIntersectionCheckDiagnosisImpl(const CATIntersectionCheckDiagnosisImpl &iObject); // Prohibited
  CATIntersectionCheckDiagnosisImpl &operator=(const CATIntersectionCheckDiagnosisImpl &iObject); // Prohibited

  CATIntersectionCheckDiagnosis_Embed _EmbeddedObject;
};

#endif
