#ifndef ListPOfCATManifoldRibbonNavigatorInterface_h
#define ListPOfCATManifoldRibbonNavigatorInterface_h

// COPYRIGHT DASSAULT SYSTEMES  2011

#include "CATCGMLISTPP_Declare.h"
#include "CATGMModelInterfaces.h"

class CATManifoldRibbonNavigatorInterface;

/** 
 * @collection CATLISTP(CATManifoldRibbonNavigatorInterface)
 * Collection class for pointers to geometric features.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */

CATCGMLISTPP_DECLARE(CATManifoldRibbonNavigatorInterface);

typedef CATLISTP(CATManifoldRibbonNavigatorInterface) ListPOfCATManifoldRibbonNavigatorInterface;

class CATCGMOutput;
/**
 * @nodoc
 * Writes the tags of the cell manifolds of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByCATGMModelInterfaces CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATManifoldRibbonNavigatorInterface& iToWrite);

#endif
