#ifndef ListPOfCATBoneManifold_h
#define ListPOfCATBoneManifold_h

#include "CATCGMLISTPP_Declare.h"
#include "YI00IMPL.h"

class CATBoneManifold;

CATCGMLISTPP_DECLARE(CATBoneManifold);

/** @nodoc */
typedef CATLISTP(CATBoneManifold) ListPOfCATBoneManifold;

class CATCGMOutput;
/**
 * @nodoc
 * Writes the tags of the cell manifolds of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByYI00IMPL CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATBoneManifold& iToWrite);

#endif
