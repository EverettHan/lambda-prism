
// COPYRIGHT DASSAULT SYSTEMES  2009
//=================================================================================
// Class to complete a CATCGMJournal
//=================================================================================
// May  09  Creation                                                      JJ3, JMA
//=================================================================================

#ifndef CATCGMJournalCompletion_h
#define CATCGMJournalCompletion_h

#include "CATGMModelInterfaces.h"
#include "CATCGMJournal.h"
#include "CATBoolean.h"

class CATBody;
class CATListPtrCATBody;
class CATCGMJournalList;
class CATSoftwareConfiguration;

// CATCGMJournalCompletion is a list of services which adds missing items or remove useless/wrong items in journal
class ExportedByCATGMModelInterfaces CATCGMJournalCompletion
{

public :

  // this type describes the operations to be done by CATCGMJournalCompletion
  enum OperationType
  {
    Unset = 0,
    CompleteWithDeletes = 1, // add delete items in journal. Was used for completion of old journal in fast run
    DesactivateUnnecessaryDeletes = 2, // inactrivate useless delete items in journal
    CompleteWithDeletesAndKeeps = 3 // add ddelete and keep items in journal. It is used for completion in old journal in fast run

  };
  virtual void SetBody(CATBody * ipBody); // set input body (copy mode)
  virtual void SetBodiesList(CATListPtrCATBody &iRefInputs);   /// set a list of input body incopy mode in journal
  virtual void SetNoCopyBodiesList(CATListPtrCATBody &iRefInputs);  // set a list of input body  in no copy mode injournal
  virtual void SetOldOutput(CATBody * ipRefOutput);     // set the output for journal
  virtual void SetJournal(CATCGMJournalList *ipJournal);    // set journal for completion
  virtual void SetJournalIsModifiable(CATBoolean iJournalIsModifiable);  // indicate if we will create a new journal or if we will use input journal for result
                                                                           // true result is in input journal
                                                                           // false result will be in a new journal to be read
  virtual void SetOperationType(CATCGMJournalCompletion::OperationType iOperationType);    // set type of operation refer to enum for values
  virtual void Run();       // run  as operators have
  virtual CATCGMJournalList * GetResult();   // get the new journal to be used when input journal is not modifiable to obtain result
  virtual ~CATCGMJournalCompletion();  // destructor

};

// 
// interface to be used for initailisng a journal completion services
// by default, it will work with SetJournalIsModifiable(TRUE) and SetOperationType(CATCGMJournalCompletion::CompleteWithDeletesAndKeeps)
ExportedByCATGMModelInterfaces CATCGMJournalCompletion * CATCreateCGMJournalCompletion(
  CATListPtrCATBody & ipOldCopyInputs, // list of input bodies in copy mode
  CATBody * ipOldOutput,               // list of output body
  CATCGMJournalList * ipJournal,       // journal to be completed
  CATSoftwareConfiguration *Config);   // software configuration for level of code

#endif
