// COPYRIGHT DASSAULT SYSTEMES  1999
//===========================================================================
// Class CATCGMJournalFilter 
//---------------------------------------------------------------------------
// Avr. 2002    Migration vers CATCGMHashTable                  HCN
//===========================================================================

#ifndef CATCGMJournalFilter_H
#define CATCGMJournalFilter_H

#include  "YP00IMPL.h"
#include "CATCGMHashTable.h"
#include "CATCGMNewArray.h"

class CATGeometry;

class   ExportedByYP00IMPL  CATCGMJournalFilter : public CATCGMHashTable
{
public:

  CATCGMJournalFilter(int iEstimatedSize = 0);
  ~CATCGMJournalFilter();
  CATCGMNewClassArrayDeclare;
};

#endif 
