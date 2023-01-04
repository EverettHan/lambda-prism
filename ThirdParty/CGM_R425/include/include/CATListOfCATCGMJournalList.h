#ifndef CATListOfCATCGMJournalLists_H_
#define CATListOfCATCGMJournalLists_H_

// COPYRIGHT DASSAULT SYSTEMES  2012

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 
/** 
 * @collection CATLISTP(CATCGMJournalList)
 * Collection class for pointers to CGM journallists.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
#include "YP00IMPL.h"
#include "CATLISTPP_Clean.h"
#include "CATLISTPP_PublicInterface.h"
#include "CATLISTPP_Declare.h"

class CATCGMJournalList ;

#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByYP00IMPL

CATLISTPP_DECLARE_TS( CATCGMJournalList , 10)


#endif


