// COPYRIGHT DASSAULT SYSTEMES  2000
// EDS

#ifndef __ListPOfListPOfCATFace_h__
#define __ListPOfListPOfCATFace_h__

#include "CATCGMLISTPP_Declare.h"
#include "CATGMModelInterfaces.h"
#include "ListPOfCATFace.h"

/** 
 * @collection CATLISTP(ListPOfCATFace)
 * Collection class for pointers to geometric features.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */

CATCGMLISTPP_DECLARE(ListPOfCATFace);

typedef CATLISTP(ListPOfCATFace) ListPOfListPOfCATFace;

class CATCGMOutput;

/**
 * @nodoc
 * Writes the tags of all the faces of the lists.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByCATGMModelInterfaces CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATFace& iToWrite);

#endif
