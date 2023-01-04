// COPYRIGHT DASSAULT SYSTEMES  2000
// EDS

#ifndef __ListPOfListPOfCATCell_h__
#define __ListPOfListPOfCATCell_h__

#include "CATCGMLISTPP_Declare.h"
#include "CATGMModelInterfaces.h"
#include "CATListOfCATCells.h"

/** 
 * @collection CATLISTP(ListPOfCATCell)
 * Collection class for pointers to geometric features.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */

CATCGMLISTPP_DECLARE(ListPOfCATCell);

typedef CATLISTP(ListPOfCATCell) ListPOfListPOfCATCell;

class CATCGMOutput;

/**
 * @nodoc
 * Writes the tags of all the Cells of the lists.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByCATGMModelInterfaces CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATCell& iToWrite);

#endif
