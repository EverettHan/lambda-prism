#ifndef CATTopOpUpdateBodyInError_h
#define CATTopOpUpdateBodyInError_h
//**********************************************************************
//* DON T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS *
//* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPEAR AT ANY TIME *
//**********************************************************************
//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2020
//
// DESCRIPTION : CATTopOpUpdatBodyInError declaration
//               
//=============================================================================
class CATCGMJournalList;
class CATTopData;
class CATTopOpInError;
class CATTopOperator;

#include "CATErrors.h"
#include "CATGMModelInterfaces.h"
#include "CATCGMInputError.h"
#include "ListPOfCATBody.h"

#include "CATIAV5Level.h" // to suppress
/**
* Class for reporting an error with the inputs of a topological operation.
*/
void ExportedByCATGMModelInterfaces  CATTopOpUpdateBodyInError(CATTopData *iData, CATTopOpInError * ErrorToUpdate, ListPOfCATBody & ListOfInputBody,CATCGMJournalList * JournalTillFailure );

void ExportedByCATGMModelInterfaces  CATTopOperatorBodyInError(CATTopOperator * iOpe, CATError * iError);
//

#endif
