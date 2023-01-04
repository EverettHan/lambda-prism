#ifndef ListPOfCATDatumManifold_h
#define ListPOfCATDatumManifold_h

#include "CATCGMLISTPP_Declare.h"
#include "YI00IMPL.h"

class CATDatumManifold;

CATCGMLISTPP_DECLARE(CATDatumManifold);

/** @nodoc */
typedef CATLISTP(CATDatumManifold) ListPOfCATDatumManifold;

class CATCGMOutput;
/**
 * @nodoc
 * Writes the tags of the cell manifolds of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByYI00IMPL CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATDatumManifold& iToWrite);

#endif
