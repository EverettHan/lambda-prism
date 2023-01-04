/**
 * @COPYRIGHT DASSAULT SYSTEMES 2004
 */

//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2004
// DESCRIPTION : Class for following CGM Cleaner rule :
//               "INF_3", Body (completely) should be inside ModelSize
//
// Jun. 04	Creation                                                 AJM
//=============================================================================

#ifndef CATGeoClnINFCheckBodyInModelSize_h
#define CATGeoClnINFCheckBodyInModelSize_h

#include "ExportedByCATCGMGeoClnTopo.h"
#include "CATGeoCln.h"

class CATBody;

CATCGMCLEANER_RULE_TOPO_DECLARE_BEGIN(CATGeoClnINFCheckBodyInModelSize)

  int CheckBodyInModelSize(CATBody *ipBodyToCheck);

CATCGMCLEANER_RULE_TOPO_DECLARE_END()

#endif

