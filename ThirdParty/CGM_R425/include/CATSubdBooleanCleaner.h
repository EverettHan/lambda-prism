#ifndef CATSubdBooleanCleaner_h
#define CATSubdBooleanCleaner_h

// COPYRIGHT DASSAULT SYSTEMES 1999


#include "BOOPER.h"
class CATCXBody;
class CATCXDomain;
class CATCXCell;
#include "ListPOfCATBody.h"
#ifndef NULL
#define NULL 0
#endif

class CATTopOperator;
class CATTopData;

ExportedByBOOPER void CATSubdBooleanCleaner(CATCXBody            *Body1,
                                            CATCXBody            *Body2 = NULL,
                                            int                   CheckSecondBody = 1,
                                            CATTopOperator       *iOperateur = NULL,
                                            const CATTopData     *iTopData   = NULL,
                                            int                   ChkFirstBody = 1);

ExportedByBOOPER void CATSubdCleanIsoAndLowerDimContents(CATCXCell*);

ExportedByBOOPER void CATSubdBooleanCleaner(ListPOfCATBody &ilistBody,
                                            CATTopOperator       *iOperateur = NULL,
                                            const CATTopData     *iTopData   = NULL);

#endif
