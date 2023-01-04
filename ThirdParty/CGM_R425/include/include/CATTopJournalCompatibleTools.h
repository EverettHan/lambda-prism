#ifndef CATTopJournalCompatibleTools_H_
#define CATTopJournalCompatibleTools_H_

/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES  2002
//=============================================================================
// Class for various journal operations
//=============================================================================
// Jul. 08  Creation                                                     JHN
//=============================================================================

#include "ExportedByCATTopologicalObjects.h"
#include "CATListOfCATCGMJournals.h"
#include "ListPOfCATBody.h"
#include "CATBoolean.h"

class CATCGMJournalList;
class CATBody;
class CATGeometry;
class CATCell;

ExportedByCATTopologicalObjects void 
SuppressNonCommonDelete(const CATLISTP(CATBody)& iListInBodies,
                        const CATLISTP(CATBody)& iListOutBodies,
                        const CATLISTP(CATCGMJournal)& iListOutJournals);

// Duplicates in oOutputJournal all items from all journals of iListOfJournals 
// except deletion items that are not in all journal from iListOfJournals.
// It does not manage optinnal info for deletion items.
ExportedByCATTopologicalObjects
void ConcatenateWithoutNonCommonDelete(const CATLISTP(CATCGMJournal)& iListOfJournals,
                                       CATCGMJournalList &oOutputJournal);
// Duplicates in oOutputJournal all items from all journals of iInputJournal 
// except deletion items that are not in all journal from iListOfJournals.
// It does not manage optinnal info for deletion items.
ExportedByCATTopologicalObjects
void SuppressDeleteInJournal(CATCGMJournalList * iInputJournal,
                                       CATCGMJournalList *oOutputJournal);

// Local
CATBoolean IsGeometryDeleted(CATCGMJournalList &iJournalList, CATGeometry *iGeometry);



#endif
