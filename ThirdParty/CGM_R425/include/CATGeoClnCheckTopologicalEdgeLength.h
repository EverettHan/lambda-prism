/**
 * @COPYRIGHT DASSAULT SYSTEMES 2005
 */

//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2005
// DESCRIPTION : Class for following CGM Cleaner rule :
//               "TEL_1, Topological Edge Length > Resolution"
//
// Jul. 04	Creation                                                 BQJ
//=============================================================================

#ifndef CATGeoClnCheckTopologicalEdgeLength_h
#define CATGeoClnCheckTopologicalEdgeLength_h

#include "ExportedByCATCGMGeoClnTopo.h"
#include "CATGeoCln.h"

class CATEdge;


//-------------------------   --- Check Edge Length ---   ------------------------

CATCGMCLEANER_RULE_TOPO_DECLARE_BEGIN(CATGeoClnCheckTopologicalEdgeLength)

  int CheckTopologicalEdgeLength(CATEdge* ipEdgeToCheck);

CATCGMCLEANER_RULE_TOPO_DECLARE_END()
#endif

