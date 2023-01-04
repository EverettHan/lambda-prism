#ifndef CATPGMTopJournalCompatibleTools_h_
#define CATPGMTopJournalCompatibleTools_h_

// COPYRIGHT DASSAULT SYSTEMES 2008

#include "CATGMModelInterfaces.h"
#include "CATCollec.h"

class CATLISTP(CATBody);
class CATLISTP(CATCGMJournal);

class CATBody;
class CATCGMJournalList;
class CATCell;
class CATGeometry;

ExportedByCATGMModelInterfaces void CATPGMSuppressNonCommonDelete(
  const CATLISTP(CATBody) &iListInBodies,
  const CATLISTP(CATBody) &iListOutBodies,
  const CATLISTP(CATCGMJournal) &iListOutJournals);

// Duplicates in oOutputJournal all items from all journals of iListOfJournals 
// except deletion items that are not in all journal from iListOfJournals.
// It does not manage optinnal info for deletion items.
ExportedByCATGMModelInterfaces void CATPGMConcatenateWithoutNonCommonDelete(
  const CATLISTP(CATCGMJournal)& iListOfJournals,
  CATCGMJournalList &oOutputJournal);

// Duplicates in oOutputJournal all items from all journals of iInputJournal 
// except deletion items that are not in all journal from iListOfJournals.
// It does not manage optinnal info for deletion items.
ExportedByCATGMModelInterfaces void CATPGMSuppressDeleteInJournal(
  CATCGMJournalList *iInputJournal,
  CATCGMJournalList *oOutputJournal);

#endif /* CATPGMTopJournalCompatibleTools_h_ */
