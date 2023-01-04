#ifndef ListPOfCATJointFillet_h
#define ListPOfCATJointFillet_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATCGMLISTPP_Declare.h"

class CATJointFillet;

CATCGMLISTPP_DECLARE(CATJointFillet);

typedef CATLISTP(CATJointFillet) ListPOfCATJointFillet;

#include "YI00IMPL.h"

class CATCGMOutput;
/**
 * @nodoc
 * Writes the tags of the cell manifolds of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByYI00IMPL CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATJointFillet& iToWrite);

#endif
