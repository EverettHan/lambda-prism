#ifndef CATTopExtrudeContextForFastRun_h
#define CATTopExtrudeContextForFastRun_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2015
// 
//==========================================================================
// 2015 WEEK 51 LD2 Creation
//==========================================================================
#include "CATGMOperatorsInterfaces.h"
#include "CATContextForFastRun.h"


class ExportedByCATGMOperatorsInterfaces CATTopExtrudeContextForFastRun: public CATContextForFastRun
{
public:
  /**
   * Constructor
   */
  CATTopExtrudeContextForFastRun();

	/*
	 * Set and get the Boolean output and journal and the non-Boolean output and journal.  
	 * The result IDs for these are 2 and 3 respectively.  
	 */
  virtual void                        SetOldBooleanResult(CATBody *iOldOutput, 
                                                  CATCGMJournalList *iOldJournal) = 0;
	virtual void                        SetOldNonBooleanResult(CATBody *iOldOutput, 
                                                     CATCGMJournalList *iOldJournal) = 0;
  virtual CATCGMJournalList         * GetOldBooleanJournal() = 0;
  virtual CATBody                   * GetOldBooleanResult() = 0;
  virtual CATCGMJournalList         * GetOldNonBooleanJournal() = 0;
  virtual CATBody                   * GetOldNonBooleanResult() = 0;

	/*
	 * Get the result ID for the Result and the Boolean result.
	 */
	virtual CATResultIDForFastRun GetNonBooleanResultID() = 0;
  virtual CATResultIDForFastRun GetBooleanResultID() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATTopExtrudeContextForFastRun(); // -> delete can't be called
};

#endif /* CATTopExtrudeContextForFastRun_h_ */
