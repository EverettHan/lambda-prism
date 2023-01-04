#ifndef CATDebugUtilitiesForFastUpdate_h
#define CATDebugUtilitiesForFastUpdate_h

#include "CATBoolean.h"
#include "CATUnicodeString.h"
#include "ExportedByCATTopologicalObjects.h"
#include "CATListOfInt.h"

class CATBody;
class CATCGMJournalList;
class CATListPtrCATCGMJournal;
class CATListPtrCATBody;
class CATTopOperator;
class CATIPGMTopOperator;

class ExportedByCATTopologicalObjects CATDebugUtilitiesForFastUpdate
{
public:
   static CATBoolean Is_CGM_Topo_FastRun_Traces( );

  static CATUnicodeString Get_FastRun_Traces();

  static CATUnicodeString Get_Smartification_Traces( );

  static void ResultMappingForFastRun(CATBody & iResultBody,
    CATBody & iReferenceBody,
    CATBoolean & oBodyMappingOK,
    CATCGMJournalList * iResultJournal = NULL,
    CATCGMJournalList * iReferenceJournal = NULL,
    CATBoolean * oJournalMappingOK = NULL);

  static void ResultMappingForFastRun(CATListPtrCATBody & iResultBodies,
    CATListPtrCATBody & iReferenceBodies,
    CATListOfInt & oBodyMappingOK,
    CATListPtrCATCGMJournal * iResultJournals = NULL,
    CATListPtrCATCGMJournal * iReferenceJournals = NULL,
    CATListOfInt * oJournalMappingOK = NULL);

  static void GetContextAndSetStatusToImpossible(CATTopOperator * iTopOperator);

  static void GetContextAndSetStatusToImpossible(CATIPGMTopOperator * iTopOperator);
};

#endif
