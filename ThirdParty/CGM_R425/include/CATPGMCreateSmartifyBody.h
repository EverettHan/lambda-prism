#ifndef CATPGMCreateSmartifyBody_h_
#define CATPGMCreateSmartifyBody_h_

// COPYRIGHT DASSAULT SYSTEMES 2011

#include "CATGMOperatorsInterfaces.h"

class CATBody;
class CATCGMJournalList;
class CATGeoFactory;
class CATIPGMSmartifyBody;
class CATTopData;

/**
 * Creates a CATIPGMSmartifyBody operator that uses 2 journals to create associations between elements
 * of bodies <ToSmartify> and <Reference>.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMSmartifyBody *CATPGMCreateSmartifyBodyUsingJournals(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iToSmartify,
  CATBody *iReference,
  CATCGMJournalList *iToSmartifyJournal,
  CATCGMJournalList *iReferenceJournal);

#endif /* CATPGMCreateSmartifyBody_h_ */
