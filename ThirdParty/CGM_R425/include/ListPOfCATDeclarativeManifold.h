#ifndef ListPOfCATDeclarativeManifold_h
#define ListPOfCATDeclarativeManifold_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATCGMLISTPP_Declare.h"
#include "CATGMModelInterfaces.h"

class CATDeclarativeManifold;

/** 
 * @collection CATLISTP(CATCellManifold)
 * Collection class for pointers to geometric features.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */

CATCGMLISTPP_DECLARE(CATDeclarativeManifold);

typedef CATLISTP(CATDeclarativeManifold) ListPOfCATDeclarativeManifold;

class CATCGMOutput;
/**
 * @nodoc
 * Writes the tags of the cell manifolds of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByCATGMModelInterfaces CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATDeclarativeManifold& iToWrite);

#endif
