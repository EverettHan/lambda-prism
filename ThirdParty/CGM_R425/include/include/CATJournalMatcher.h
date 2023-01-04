#ifndef CATJournalMatcher_h
#define CATJournalMatcher_h

// COPYRIGHT DASSAULT SYSTEMES  2001

#include "ExportedByCATTopologicalObjects.h"
#include "CATDataType.h"
#include "CATCGMVirtual.h"

class CATCGMJournal;

class ExportedByCATTopologicalObjects CATJournalMatcher : public CATCGMVirtual
{
public:

  virtual void AddJournal(const CATCGMJournal * iJournal) = 0;

  virtual CATLONG32 GetEquivalentCellTag(CATLONG32 iTag) = 0;
};

ExportedByCATTopologicalObjects CATJournalMatcher * CreateJournalMatcher(const char * iReferenceFile,
                                         int iForceWrite = 0);

ExportedByCATTopologicalObjects void Remove(CATJournalMatcher *& ioJournalMatcher);

#endif
