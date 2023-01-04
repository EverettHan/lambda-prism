#ifndef ListPOfCATCellManifoldGroupNavigator_h
#define ListPOfCATCellManifoldGroupNavigator_h

// COPYRIGHT DASSAULT SYSTEMES  2010

#include "CATCGMLISTPP_Declare.h"
#include "CATGMModelInterfaces.h"

class CATCellManifoldGroupNavigator;

/** 
 * @collection CATLISTP(CATCellManifoldGroupNavigator)
 * Collection class for pointers to geometric features.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */

CATCGMLISTPP_DECLARE(CATCellManifoldGroupNavigator);

typedef CATLISTP(CATCellManifoldGroupNavigator) ListPOfCATCellManifoldGroupNavigator;

class CATCGMOutput;
/**
 * @nodoc
 * Writes the tags of the cell manifolds of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByCATGMModelInterfaces CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATCellManifoldGroupNavigator& iToWrite);

#endif
