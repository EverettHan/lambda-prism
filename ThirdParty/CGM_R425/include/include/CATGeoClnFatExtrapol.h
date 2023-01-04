/**
 * @COPYRIGHT DASSAULT SYSTEMES 2003
 */

//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2002
// DESCRIPTION : Class for following CGM Cleaner rule :
//               "FEX_1" Fat Extrapolations
//
// Jan. 03	Creation                                                      HCN
//=============================================================================

#ifndef CATGeoClnFatExtrapol_h
#define CATGeoClnFatExtrapol_h

#include "ExportedByCATCGMGeoClnTopo.h"
#include "CATGeoCln.h"

class CATCGMLimOfParm;

CATCGMCLEANER_RULE_TOPO_DECLARE_BEGIN(CATGeoClnFatExtrapol)

  // Surcharge de ICGMEntityID()
  CATULONG32  ICGMEntityID() const;

  int CheckOrCleanCGMEntity(CATGeoCln::CATCGMCleanerAction iAction);

  static int CompareFunction(CATCGMLimOfParm* ipFatParam1, CATCGMLimOfParm* ipFatParam2);

  friend class CATGeoClnFatGeometries;

CATCGMCLEANER_RULE_TOPO_DECLARE_END()

#endif
