/**
 * @COPYRIGHT DASSAULT SYSTEMES 2003
 */

//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2003
// DESCRIPTION : Class for following CGM Cleaner rule :
//               "CWE_1, Wire Check : A Closed Wire should contain more than one edge.
//
// Jul. 03	Creation                                                 AJM
//=============================================================================

#ifndef CATGeoClnClosedWireFewerEdges_h
#define CATGeoClnClosedWireFewerEdges_h

#include "ExportedByCATCGMGeoClnTopo.h"
#include "CATGeoCln.h"

class CATWire;

CATCGMCLEANER_RULE_TOPO_DECLARE_BEGIN(CATGeoClnClosedWireFewerEdges)

  int CheckClosedWireForEdgeCount(CATWire* pWireToCheck);

CATCGMCLEANER_RULE_TOPO_DECLARE_END()

#endif

