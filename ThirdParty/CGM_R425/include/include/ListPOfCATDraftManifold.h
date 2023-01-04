#ifndef ListPOfCATDraftManifold_h
#define ListPOfCATDraftManifold_h

#include "CATCGMLISTPP_Declare.h"
#include "YI00IMPL.h"

class CATDraftManifold;


// ListP >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
CATCGMLISTPP_DECLARE(CATDraftManifold);
/** @nodoc */
typedef CATLISTP(CATDraftManifold) ListPOfCATDraftManifold;
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


// ListPOfListP >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
CATCGMLISTPP_DECLARE(ListPOfCATDraftManifold);
/** @nodoc */
typedef CATLISTP(ListPOfCATDraftManifold) ListPOfListPOfCATDraftManifold;
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


class CATCGMOutput;
/**
 * @nodoc
 * Writes the tags of the cell manifolds of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByYI00IMPL CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATDraftManifold& iToWrite);

#endif
