// COPYRIGHT DASSAULT SYSTEMES 2009
#ifndef CATListOfCATCGMBinaryStream_h
#define CATListOfCATCGMBinaryStream_h
/* 
 * collection CATLISTP(CATCGMBinaryStream)
 * Collection class for pointers CATCGMBinaryStream.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 * used only in the context of incremental stream where there are several stream to manage.
 */

#include "CATCGMBinaryStream.h"

#include "CATCGMLISTPP_Declare.h"

CATCGMLISTPP_DECLARE(CATCGMBinaryStream);

typedef CATLISTP(CATCGMBinaryStream ) ListPOfCATCGMBinaryStream ;


#endif
