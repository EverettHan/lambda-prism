#ifndef ListPOfCATBoneChamfer_h
#define ListPOfCATBoneChamfer_h

#include "CATCGMLISTPP_Declare.h"
#include "YI00IMPL.h"

class CATBoneChamfer;

CATCGMLISTPP_DECLARE(CATBoneChamfer);

/** @nodoc */
typedef CATLISTP(CATBoneChamfer) ListPOfCATBoneChamfer;

class CATCGMOutput;
/**
 * @nodoc
 * Writes the tags of the cell manifolds of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByYI00IMPL CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATBoneChamfer& iToWrite);

#endif
