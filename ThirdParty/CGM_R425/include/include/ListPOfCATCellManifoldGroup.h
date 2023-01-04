#ifndef ListPOfCATCellManifoldGroup_h
#define ListPOfCATCellManifoldGroup_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATCGMLISTPP_Declare.h"
#include "CATGMModelInterfaces.h"

class CATCellManifoldGroup;

/** 
 * @collection CATLISTP(CATCellManifoldGroup)
 * Collection class for pointers to geometric features.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */

CATCGMLISTPP_DECLARE(CATCellManifoldGroup);

typedef CATLISTP(CATCellManifoldGroup) ListPOfCATCellManifoldGroup;

class CATCGMOutput;
/**
 * @nodoc
 * Writes the tags of the cell manifolds of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */

ExportedByCATGMModelInterfaces CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATCellManifoldGroup& iToWrite);
 
#endif
