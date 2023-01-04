#ifndef ListPOfCATHEdge_h
#define ListPOfCATHEdge_h

// COPYRIGHT DASSAULT SYSTEMES  2019

#include "CATCGMLISTPP_Declare.h"
#include "ExportedByCATTopologicalObjects.h"

class CATHEdge;

/** 
 * @collection CATLISTP(CATHEdge)
 * Collection class for pointers to geometric features.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */

CATCGMLISTPP_DECLARE(CATHEdge);

typedef CATLISTP(CATHEdge) ListPOfCATHEdge;

class CATCGMOutput;
/**
 * @nodoc
 * Writes the tags of the cell manifolds of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByCATTopologicalObjects CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATHEdge& iToWrite);

#endif
