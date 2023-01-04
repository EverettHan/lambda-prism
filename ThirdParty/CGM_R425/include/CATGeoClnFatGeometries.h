/**
 * @COPYRIGHT DASSAULT SYSTEMES 2003
 */


/* -*-c++-*- */
//=============================================================================
//
// DESCRIPTION : Class for following CGM Cleaner rule :
//               "FGM_1" Fat Geometries = FVX_1 + FEX_1
//
// Jan. 03  Creation                                                      HCN
//
//=============================================================================

#ifndef CATGeoClnFatGeometries_h
#define CATGeoClnFatGeometries_h

#include "ExportedByCATCGMGeoClnTopo.h"
#include "CATGeoCln.h"
#include "CATGeometryType.h"

class CATBodyDatumiser;
class CATTopData;
class CATCGMGeometryOfFatAble;

CATCGMCLEANER_RULE_TOPO_DECLARE_BEGIN(CATGeoClnFatGeometries)

  //CATBodyDatumiser* GetDatumiser(CATGeometricType iEntityType, CATGeoFactory* iFactory, CATTopData& iTopData);

  // Surcharge de ICGMEntityID()
  CATULONG32  ICGMEntityID() const;

  int CheckOrCleanCGMEntity(CATGeoCln::CATCGMCleanerAction iAction);

  static int CompareFunction(CATCGMGeometryOfFatAble* ipFatAble1, CATCGMGeometryOfFatAble* ipFatAble2);

CATCGMCLEANER_RULE_TOPO_DECLARE_END()

#endif
