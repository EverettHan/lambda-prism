// COPYRIGHT DASSAULT SYSTEMES 2009
#ifndef CATListOfCATCGMStream_h
#define CATListOfCATCGMStream_h
/* 
 * collection CATLISTP(CATCGMStream)
 * Collection class for pointers CATCGMStream.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 * used only in the context of incremental stream where there are several stream to manage.
 */

#include "CATCGMStream.h"

#include "CATCGMLISTPP_Declare.h"

CATCGMLISTPP_DECLARE(CATCGMStream);

typedef CATLISTP(CATCGMStream ) ListPOfCATCGMStream ;


#endif
