#ifndef CATCGMListOfCATULONGPTR_h
#define CATCGMListOfCATULONGPTR_h
// COPYRIGHT DASSAULT SYSTEMES  2002
/** 
 * @collection CATCGMListOfCATULONGPTR
 */
#include "CATMathematics.h"
#include "CATDataType.h"
#include  "CATCollec.h"

// Prepare declaration
#include  "CATRCOLL_Clean.h"
#include  "CATRCOLL_AllFunct.h"
#define	CATRCOLL_ValCompare
#define	CATRCOLL_ValQuickSort
#undef	CATCOLLEC_ExportedBy
#define	CATCOLLEC_ExportedBy	ExportedByCATMathematics

// Declaration
#include  "CATRCOLL_Declare.h"
CATRCOLL_DECLARE( CATULONGPTR )


// Commodity
typedef		CATRCOLL(CATULONGPTR)	CATCGMListOfCATULONGPTR ;

#define DELETE_PLISTCATULONGPTR_OF_OBTECTS_OF_TYPE( pList, Type)  \
                                                                  \
if (pList)                                                        \
{                                                                 \
  int NbElems = pList->Size();                                    \
  for (int NumList = 1; NumList <= NbElems; NumList++)            \
  {                                                               \
    Type* pObjectOfType = (Type*)((*pList)[NumList]);             \
                                                                  \
    if (pObjectOfType)                                            \
    {                                                             \
      delete pObjectOfType;                                       \
      pObjectOfType = NULL;                                       \
      (*pList)[NumList] = (CATULONGPTR)NULL;                      \
    }                                                             \
  }                                                               \
                                                                  \
  delete pList;                                                   \
  pList = NULL;                                                   \
}


#endif

