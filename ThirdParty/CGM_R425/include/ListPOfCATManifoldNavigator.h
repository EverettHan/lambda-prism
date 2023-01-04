#ifndef ListPOfCATManifoldNavigator_h
#define ListPOfCATManifoldNavigator_h

// COPYRIGHT DASSAULT SYSTEMES  2011

#include "CATCGMLISTPP_Declare.h"
#include "CATGMModelInterfaces.h"

class CATManifoldNavigator;

/** 
 * @collection CATLISTP(CATManifoldNavigator)
 * Collection class for pointers to DRep Navigators.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */

CATCGMLISTPP_DECLARE(CATManifoldNavigator);

typedef CATLISTP(CATManifoldNavigator) ListPOfCATManifoldNavigator;

class CATCGMOutput;
/**
 * @nodoc
 * Writes the tags of the cell manifolds of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByCATGMModelInterfaces CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATManifoldNavigator& iToWrite);

#endif
