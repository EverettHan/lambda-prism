/**
 * @COPYRIGHT DASSAULT SYSTEMES 2003
 */

//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2003
// DESCRIPTION : Class for following CGM Cleaner rule :
//               "FED_3", "Fat Edges for body completed"
//               "Check the fat edges for body completed."
//
// Dec. 03	Creation                                                 FDN
//=============================================================================

#ifndef CATGeoClnFatEdgeCompleted_h
#define CATGeoClnFatEdgeCompleted_h

#include "ExportedByCATCGMGeoClnTopo.h"
#include "CATGeoCln.h"

class CATBody;

CATCGMCLEANER_RULE_TOPO_DECLARE_BEGIN(CATGeoClnFatEdgeCompleted)

int CheckFatEdgeCompleted(const CATBody * pBodyToCheck);

CATCGMCLEANER_RULE_TOPO_DECLARE_END()

#endif

