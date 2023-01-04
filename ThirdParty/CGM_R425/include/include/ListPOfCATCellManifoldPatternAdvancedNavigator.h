#ifndef ListPOfCATCellManifoldPatternAdvancedNavigator_h
#define ListPOfCATCellManifoldPatternAdvancedNavigator_h

#include "CATCGMLISTPP_Declare.h"
#include "YI00IMPL.h"

class CATCellManifoldPatternAdvancedNavigator;

CATCGMLISTPP_DECLARE(CATCellManifoldPatternAdvancedNavigator);

typedef CATLISTP(CATCellManifoldPatternAdvancedNavigator) ListPOfCATCellManifoldPatternAdvancedNavigator;

class CATCGMOutput;
/**
 * @nodoc
 * Writes the tags of the cell manifolds of the list.
 * @param iWhereToWrite
 * The output.
 * @param  iToWrite
 * The list to dump.
 */
ExportedByYI00IMPL CATCGMOutput& operator<<(CATCGMOutput& iWhereToWrite, const ListPOfCATCellManifoldPatternAdvancedNavigator& iToWrite);

#endif
