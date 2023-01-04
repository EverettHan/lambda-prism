#ifndef ListPOfCATHGeometry_h
#define ListPOfCATHGeometry_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATCGMLISTPP_Declare.h"
#include "ExportedByCATTopologicalObjects.h"

class CATHGeometry;

/** 
 * @collection CATLISTP(CATHGeometry)
 * Collection class for pointers to geometric features.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */

CATCGMLISTPP_DECLARE(CATHGeometry);

typedef CATLISTP(CATHGeometry) ListPOfCATHGeometry;

class CATCGMOutput;
/**
 * @nodoc
 * Writes the tags of the cell manifolds of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByCATTopologicalObjects CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATHGeometry& iToWrite);

#endif
