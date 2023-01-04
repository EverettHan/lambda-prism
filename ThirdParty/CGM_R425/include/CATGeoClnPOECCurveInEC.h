/**
 * @COPYRIGHT DASSAULT SYSTEMES 2003
 */

//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2003
// DESCRIPTION : Class for following CGM Cleaner rule :
//               "PCE_1, POEC Curve In EdgeCurve
//
// Jun. 03	Creation                                                 AJM
//=============================================================================

#ifndef CATGeoClnPOECCurveInEC_h
#define CATGeoClnPOECCurveInEC_h

#include "ExportedByCATCGMGeoClnGeom.h"
#include "CATGeoCln.h"

class CATPointOnEdgeCurve;

CATCGMCLEANER_RULE_GEOM_DECLARE_BEGIN(CATGeoClnPOECCurveInEC)

  int CheckPOECCurveNotInEdgeCurve(const CATPointOnEdgeCurve* pPOECToCheck);

CATCGMCLEANER_RULE_GEOM_DECLARE_END()

#endif

