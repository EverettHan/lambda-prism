// COPYRIGHT DASSAULT SYSTEMES 2007
//=============================================================================
//
// Class designed to handle simple checking of CGMJournal structure
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Avr. 07   Creation                                     J.Morawska

//=============================================================================
#ifndef CATCGMJournalListBasicCheck_H
#define CATCGMJournalListBasicCheck_H


#include "CATCGMJournalList.h"

class ExportedByYP00IMPL CATCGMJournalListBasicCheck  
{
public:
   /** @nodoc */
  //CATCGMNewClassArrayDeclare;
  //-------------------------------------------------------------------------
  // Constructors/Destructors
  //-------------------------------------------------------------------------
  //-------------------------------------------------------------------------
  // Creates a new CATCGMJournalListBasicCheck 
  // 
  //-------------------------------------------------------------------------
CATCGMJournalListBasicCheck();
	
  virtual ~CATCGMJournalListBasicCheck();


  static CATBoolean BasicCheck(CATCGMJournalList * iList);

};

#endif
