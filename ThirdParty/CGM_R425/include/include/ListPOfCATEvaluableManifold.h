#ifndef ListPOfCATEvaluableManifold_h
#define ListPOfCATEvaluableManifold_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATCGMLISTPP_Declare.h"
#include "CATGMModelInterfaces.h"

class CATEvaluableManifold;

/** 
 * @collection CATLISTP(CATCellManifold)
 * Collection class for pointers to geometric features.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */

CATCGMLISTPP_DECLARE(CATEvaluableManifold);

typedef CATLISTP(CATEvaluableManifold) ListPOfCATEvaluableManifold;

class CATCGMOutput;
/**
 * @nodoc
 * Writes the tags of the cell manifolds of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByCATGMModelInterfaces CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATEvaluableManifold& iToWrite);

#endif
