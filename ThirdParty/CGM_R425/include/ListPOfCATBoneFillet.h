#ifndef ListPOfCATBoneFillet_h
#define ListPOfCATBoneFillet_h

#include "CATCGMLISTPP_Declare.h"
#include "YI00IMPL.h"

class CATBoneFillet;

CATCGMLISTPP_DECLARE(CATBoneFillet);

/** @nodoc */
typedef CATLISTP(CATBoneFillet) ListPOfCATBoneFillet;

class CATCGMOutput;
/**
 * @nodoc
 * Writes the tags of the cell manifolds of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByYI00IMPL CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATBoneFillet& iToWrite);

#endif
