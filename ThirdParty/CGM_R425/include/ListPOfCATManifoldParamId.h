#ifndef ListPOfCATManifoldParamId_h
#define ListPOfCATManifoldParamId_h

// COPYRIGHT DASSAULT SYSTEMES  2011

#include "CATCGMLISTPP_Declare.h"
#include "CATGMModelInterfaces.h"

class CATManifoldParamId;

/** 
 * @collection CATLISTP(CATManifoldParamId)
 * Collection class for pointers to geometric features.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */

CATCGMLISTPP_DECLARE(CATManifoldParamId);

typedef CATLISTP(CATManifoldParamId) ListPOfCATManifoldParamId;

class CATCGMOutput;
/**
 * @nodoc
 * Writes the tags of the cell manifolds of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByCATGMModelInterfaces CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATManifoldParamId& iToWrite);

#endif
