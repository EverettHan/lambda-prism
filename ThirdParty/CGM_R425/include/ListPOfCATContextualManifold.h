#ifndef ListPOfCATContextualManifold_h
#define ListPOfCATContextualManifold_h

#include "CATCGMLISTPP_Declare.h"
#include "YI00IMPL.h"

class CATContextualManifold;

CATCGMLISTPP_DECLARE(CATContextualManifold);

/** @nodoc */
typedef CATLISTP(CATContextualManifold) ListPOfCATContextualManifold;

class CATCGMOutput;
/**
 * @nodoc
 * Writes the tags of the cell manifolds of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByYI00IMPL CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATContextualManifold& iToWrite);

#endif
