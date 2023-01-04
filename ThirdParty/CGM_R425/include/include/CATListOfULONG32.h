#ifndef  CATListOfULONG32_h_
#define  CATListOfULONG32_h_

// COPYRIGHT DASSAULT SYSTEMES  2005

#include  <CATCollec.h>

#include  <CATRCOLL_Clean.h>
#include  <CATRCOLL_AllFunct.h>
//
#define  CATRCOLL_ValCompare
#define  CATRCOLL_ValQuickSort

#include  <CATCGMKernel.h>
#undef  CATCOLLEC_ExportedBy
#define  CATCOLLEC_ExportedBy  ExportedByCATCGMKernel

#include  <CATRCOLL_Declare.h>

#include "CATDataType.h"

/** 
 * Defines the collection class CATListOfULONG32
 *  for CATULONG32 values.
 * All the methods of values collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */
CATRCOLL_DECLARE( CATULONG32 )

typedef    CATRCOLL(CATULONG32)  CATListOfULONG32 ;

////////////
#undef CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy
#endif  
