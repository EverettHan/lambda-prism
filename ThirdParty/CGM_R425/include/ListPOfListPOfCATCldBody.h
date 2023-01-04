// COPYRIGHT DASSAULT SYSTEMES  2016
// EDS

#ifndef __ListPOfListPOfCATCldBody_h__
#define __ListPOfListPOfCATCldBody_h__

#include "CATCGMLISTPP_Declare.h"
#include "CATGMModelInterfaces.h"
#include "ListPOfCATCldBody.h"

/** 
 * @collection CATLISTP(ListPOfCATCldBody)
 * Collection class for pointers to geometric features.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */

CATCGMLISTPP_DECLARE(ListPOfCATCldBody);

typedef CATLISTP(ListPOfCATCldBody) ListPOfListPOfCATCldBody;

class CATCGMOutput;

/**
 * @nodoc
 * Writes the tags of all the Cells of the lists.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByCATGMModelInterfaces CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATCldBody& iToWrite);

#endif
