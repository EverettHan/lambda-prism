#ifndef ListOfCATIPGMDRepGroup_H
#define ListOfCATIPGMDRepGroup_H

// COPYRIGHT DASSAULT SYSTEMES 2001

#include "CATCGMLISTPP_Declare.h"
#include "CATGMModelInterfaces.h"

class CATIPGMDRepGroup;

/** 
 * @collection CATLISTP(CATLump)
 * Collection class for pointers to geometric features.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */


CATCGMLISTPP_DECLARE(CATIPGMDRepGroup);

typedef CATLISTP(CATIPGMDRepGroup) ListPOfCATIPGMDRepGroup;

class CATCGMOutput;
/**
 * @nodoc
 * Writes the tags of the cells of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByCATGMModelInterfaces CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATIPGMDRepGroup& iToWrite);

#endif
