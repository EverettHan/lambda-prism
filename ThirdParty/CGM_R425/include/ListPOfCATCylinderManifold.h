#ifndef ListPOfCATCylinderManifold_h
#define ListPOfCATCylinderManifold_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATCGMLISTPP_Declare.h"
#include "CATGMModelInterfaces.h"

class CATCylinderManifold;

/** 
 * @collection CATLISTP(CATCylinderManifold)
 * Collection class for pointers to geometric features.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */

CATCGMLISTPP_DECLARE(CATCylinderManifold);

typedef CATLISTP(CATCylinderManifold) ListPOfCATCylinderManifold;

class CATCGMOutput;
/**
 * @nodoc
 * Writes the tags of the cell manifolds of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByCATGMModelInterfaces CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATCylinderManifold& iToWrite);

#endif
