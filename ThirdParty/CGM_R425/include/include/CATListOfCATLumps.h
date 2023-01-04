#ifndef CATListOfCATLumps_h
#define CATListOfCATLumps_h

// COPYRIGHT DASSAULT SYSTEMES 2001

#include "CATCGMLISTPP_Declare.h"
#include "CATGMModelInterfaces.h"

class CATLump;

/** 
 * @collection CATLISTP(CATLump)
 * Collection class for pointers to geometric features.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */


CATCGMLISTPP_DECLARE(CATLump);

typedef CATLISTP(CATLump) ListPOfCATLump;

class CATCGMOutput;
/**
 * @nodoc
 * Writes the tags of the cells of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByCATGMModelInterfaces CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATLump& iToWrite);

#endif
