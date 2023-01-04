/**
 * @COPYRIGHT DASSAULT SYSTEMES 2007
 */

//=============================================================================
//
// DESCRIPTION : Class for following CGM Cleaner rule :
//               "EFL_0, FullLoop Check : A Full Loop should not contain more than one edge.
//
// Mar. 07	Creation                                                 RR
//=============================================================================

#ifndef CATGeoClnOnlyOneEdgeInFullLoop_h
#define CATGeoClnOnlyOneEdgeInFullLoop_h

#include "ExportedByCATCGMGeoClnTopo.h"
#include "CATGeoCln.h"

class CATLoop;

CATCGMCLEANER_RULE_TOPO_DECLARE_BEGIN(CATGeoClnOnlyOneEdgeInFullLoop)

int OnlyOneEdgeInFullLoop(CATLoop* pLoopToCheck);

CATCGMCLEANER_RULE_TOPO_DECLARE_END()

#endif

