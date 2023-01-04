// COPYRIGHT DASSAULT SYSTEMES 2009
#ifndef CATListOfCATCGMSortableAttribute_h
#define CATListOfCATCGMSortableAttribute_h
/* 
 * collection CATLISTP(CATCGMSortableAttribute)
 * Collection class for pointers CATCGMSortableAttribute.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 * used only in the context of incremental stream where there are several stream to manage.
 */

#include "CATCGMSortableAttribute.h"

#include "CATCGMLISTPP_Declare.h"

CATCGMLISTPP_DECLARE(CATCGMSortableAttribute);

typedef CATLISTP(CATCGMSortableAttribute ) ListPOfCATCGMSortableAttribute ;

ExportedByCATCGMFusion int CATCGMSortableAttributeCompareFunction(CATCGMSortableAttribute* AttributeA,CATCGMSortableAttribute* AttributeB);


#endif
