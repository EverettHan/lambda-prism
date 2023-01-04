#ifndef ListPOfCATLiveBody_h
#define ListPOfCATLiveBody_h

// COPYRIGHT DASSAULT SYSTEMES  2011

class CATLiveBody;

/** 
 * @collection CATLISTP(CATLiveBody)
 * Collection class for pointers to geometric features.
 * All the methods of pointer collection classes are available.
 * Refer to the articles dealing with collections in the encyclopedia. 
 */

CATCGMLISTPP_DECLARE(CATLiveBody);

typedef CATLISTP(CATLiveBody) ListPOfCATLiveBody;

#include "CATGMModelInterfaces.h"

class CATCGMOutput;
/**
 * @nodoc
 * Writes the tags of the cell manifolds of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByCATGMModelInterfaces CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATLiveBody& iToWrite);

#endif
