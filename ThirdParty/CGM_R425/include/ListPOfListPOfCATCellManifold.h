// COPYRIGHT DASSAULT SYSTEMES  2000
// EDS

#ifndef __ListPOfListPOfCATCellManifold_h__
#define __ListPOfListPOfCATCellManifold_h__

#include "CATCGMLISTPP_Declare.h"
#include "CATGMModelInterfaces.h"
#include "ListPOfCATCellManifold.h"

/** 
 * @collection CATLISTP(ListPOfCATCellManifold)
 * Collection class for pointers to geometric features.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */

CATCGMLISTPP_DECLARE(ListPOfCATCellManifold);

typedef CATLISTP(ListPOfCATCellManifold) ListPOfListPOfCATCellManifold;

class CATCGMOutput;

/**
 * @nodoc
 * Writes the tags of all the faces of the lists.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByCATGMModelInterfaces CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATCellManifold& iToWrite);

#endif
