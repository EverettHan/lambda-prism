#ifndef ListPOfCATManifoldGroup_h
#define ListPOfCATManifoldGroup_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATCGMLISTPP_Declare.h"
#include "CATGMModelInterfaces.h"

class CATManifoldGroup;

/** 
 * @collection CATLISTP(CATManifoldGroup)
 * Collection class for pointers to geometric features.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */

CATCGMLISTPP_DECLARE(CATManifoldGroup);

typedef CATLISTP(CATManifoldGroup) ListPOfCATManifoldGroup;

class CATCGMOutput;
/**
 * @nodoc
 * Writes the tags of the cell manifolds of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByCATGMModelInterfaces CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATManifoldGroup& iToWrite);

#endif
