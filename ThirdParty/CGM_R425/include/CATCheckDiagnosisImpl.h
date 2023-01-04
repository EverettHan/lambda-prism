#ifndef CATCheckDiagnosisImpl_h_
#define CATCheckDiagnosisImpl_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATCheckDiagnosis.h"
#include "CATCheckDiagnosis_Embed.h"
#include "CheckOperators.h"

#undef  CATCGM_DIAG_IMPL_CLASS
#define CATCGM_DIAG_IMPL_CLASS CATCheckDiagnosisImpl

class ExportedByCheckOperators CATCheckDiagnosisImpl: public CATCheckDiagnosis
{
public:
  /**
   * Constructor
   */
  CATCheckDiagnosisImpl(
    CATGeometry   * iGeometry      = (CATGeometry*)0,
    CATBoolean      iMustThrow     = FALSE,
    CATBoolean      iMustDump      = FALSE,
    CATCheckDiagnosis::MessageId       iMessageId     = CATCheckDiagnosis::NoMessage,
    const char    * iSpecifiMesage = (const char*)0);

  /**
   * Destructor
   */
  virtual ~CATCheckDiagnosisImpl();

// Declare the methods
#include "CATCheckDiagnosisImplDeclare.h"

private:
  CATCheckDiagnosisImpl(const CATCheckDiagnosisImpl &iObject); // Prohibited
  CATCheckDiagnosisImpl &operator=(const CATCheckDiagnosisImpl &iObject); // Prohibited

  CATCheckDiagnosis_Embed _EmbeddedObject;
};

#endif
