#ifndef CATCreateSmartifyBody_H
#define CATCreateSmartifyBody_H

#ifndef NULL
#define NULL 0
#endif

#include "ExportedByCATTopologicalObjects.h"
#include "CATBoolean.h"

class CATCGMJournalList;
class CATSmartifyBody;
class CATGeoFactory;
class CATTopData;
class CATBody;
class CATListPtrCATBody;
class CATListPtrCATCGMJournal;
class CATListPtrCATBody;
class ListOfListOfIntegers;

/**
 * Creates a CATSmartifyBody operator that uses 2 journals to create associations between elements
 * of bodies <ToSmartify> and <Reference>.
 */
ExportedByCATTopologicalObjects CATSmartifyBody * CATCreateSmartifyBodyUsingJournals(CATGeoFactory * iFactory,
                                                                                     CATTopData * iTopData,
                                                                                     CATBody * iToSmartify,
                                                                                     CATBody * iReference,
                                                                                     CATCGMJournalList * iToSmartifyJournal,
                                                                                     CATCGMJournalList * iReferenceJournal);

/**
 * Creates a CATSmartifyBody operator that operates on a list of bodies and journals.  
 * iTopData doesn't need a journal in this case.
 */
ExportedByCATTopologicalObjects CATSmartifyBody * CATCreateSmartifyMultiBody(CATGeoFactory * iFactory,
                                                                             CATTopData * iTopData,
                                                                             CATListPtrCATBody & iBodiesToSmartify,
                                                                             CATListPtrCATBody & iReferenceBodies,
                                                                             CATListPtrCATCGMJournal & iJournalsToSmartify,
                                                                             CATListPtrCATCGMJournal & iReferenceJournals,
                                                                             ListOfListOfIntegers * iJournalCrossDependency = NULL);

/** @nodoc @nocgmitf */
ExportedByCATTopologicalObjects CATSmartifyBody * CATCreateSmartifyBodyAfterOperation(CATGeoFactory * iFactory,
                                                                                      CATTopData * iTopData,
                                                                                      CATBody * iToSmartify,
                                                                                      CATCGMJournalList * iOperationJournal,
                                                                                      CATListPtrCATBody * iOperationCopyInputs,
                                                                                      CATListPtrCATBody * iOperationNOCopyInputs);

#endif



