/**
 * @COPYRIGHT DASSAULT SYSTEMES 2003
 */

//=============================================================================
//
// DESCRIPTION : Class for CGM Cleaner rules using a CATBodyDatumiser
//               (for instance FatVertex, BodyDatumiser...)
//
// Aug. 03	Creation                                                      HCN
//=============================================================================

#ifndef CATGeoClnBodyDatumiser_h
#define CATGeoClnBodyDatumiser_h

#include "ExportedByCATCGMGeoClnTopo.h"
#include "CATGeoCln.h"
#include "CATGeometryType.h"

class CATBodyDatumiser;
class CATTopData;
class CATCGMGeometryOfFatAble;

CATCGMCLEANER_RULE_TOPO_DECLARE_BEGIN(CATGeoClnBodyDatumiser)

  // Surcharge de ICGMEntityID()
  CATULONG32  ICGMEntityID() const;

  int CheckOrCleanCGMEntity(CATGeoCln::CATCGMCleanerAction iAction);

  static int CompareFunction(CATCGMGeometryOfFatAble* ipFatAble1, CATCGMGeometryOfFatAble* ipFatAble2);

  CATBodyDatumiser* GetDatumiser(CATGeometricType iEntityType, CATGeoFactory* iFactory, CATTopData& iTopData);

  virtual void SetBodyDatumiserTargetType(CATBodyDatumiser* ipBodyDatumiser) = 0;

  CATGeometricType _BodyDatumiserTargetType;

  friend class CATGeoClnFatGeometries;

CATCGMCLEANER_RULE_TOPO_DECLARE_END()

#endif

