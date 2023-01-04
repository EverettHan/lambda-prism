// COPYRIGHT DASSAULT SYSTEMES  2016
// VB7

#ifndef __ListPOfListPOfCATDomain_h__
#define __ListPOfListPOfCATDomain_h__

#include "CATCGMLISTPP_Declare.h"
#include "CATGMModelInterfaces.h"
#include "ListPOfCATDomain.h"

/** 
 * @collection CATLISTP(ListPOfCATDomain)
 * Collection class for pointers to geometric features.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */

CATCGMLISTPP_DECLARE(ListPOfCATDomain);

typedef CATLISTP(ListPOfCATDomain) ListPOfListPOfCATDomain;

class CATCGMOutput;

/**
 * @nodoc
 * Writes the tags of all the faces of the lists.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByCATGMModelInterfaces CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATDomain& iToWrite);

#endif
