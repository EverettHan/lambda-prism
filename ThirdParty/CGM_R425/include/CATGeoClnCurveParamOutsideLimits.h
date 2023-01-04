/**
 * @COPYRIGHT DASSAULT SYSTEMES 2003
 */

//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2003
// DESCRIPTION : Class for following CGM Cleaner rule :
//               "CPO_1, Curve param outside curve limits"
//
// Sep. 03	Creation                                                 AJM
//=============================================================================

#ifndef CATGeoClnCurveParamOutsideLimits_h
#define CATGeoClnCurveParamOutsideLimits_h

#include "ExportedByCATCGMGeoClnGeom.h"
#include "CATGeoCln.h"

class CATCurve;
class CATCrvParam;

CATCGMCLEANER_RULE_GEOM_DECLARE_BEGIN(CATGeoClnCurveParamOutsideLimits)

  int CheckCurveParamOutsideLimits(const CATCurve* ipCurveToCheck);

CATCGMCLEANER_RULE_GEOM_DECLARE_END()

#endif

