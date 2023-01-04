/**
 * @COPYRIGHT DASSAULT SYSTEMES 2003
 */

//=============================================================================
//
// DESCRIPTION : Class for following CGM Cleaner rule :
//               "PSS_0" CATGeoClnPCurveOutSideSupport
//
//Jun. 03	Creation                                                 RHA
//=============================================================================

#ifndef CATGeoClnPCurveOutSideSupport_h
#define CATGeoClnPCurveOutSideSupport_h

#include "ExportedByCATCGMGeoClnGeom.h"
#include "CATGeoCln.h"
#include "CATCGMNewArray.h"

class CATPCurve;

CATCGMCLEANER_RULE_GEOM_DECLARE_BEGIN(CATGeoClnPCurveOutSideSupport)

  int CheckLimits(CATPCurve * iPCurve, double iTolerance);

CATCGMCLEANER_RULE_GEOM_DECLARE_END()

#endif
