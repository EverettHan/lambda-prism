/**
 * @COPYRIGHT DASSAULT SYSTEMES 2004
 */

//============================================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2004
// DESCRIPTION : Class for following CGM Cleaner rule :
//               "ULO_1, Check curve useful limits inclusion in maxlimits"
//               "Check for ref curve and curve from MapX for an edge curve,
//                that curve useful limits are included in it's max limits."
//
// Jan.2004	 AJM  Creation
//============================================================================================

#ifndef CATGeoClnCurveLimitsUsefulOutsideMax_h
#define CATGeoClnCurveLimitsUsefulOutsideMax_h

#include "ExportedByCATCGMGeoClnGeom.h"
#include "CATGeoCln.h"

class CATEdgeCurve;

CATCGMCLEANER_RULE_GEOM_DECLARE_BEGIN(CATGeoClnCurveLimitsUsefulOutsideMax)

  int CheckCurveUsefulLimitsOutsideMaxLimits(CATEdgeCurve* ipEdgeCurveToCheck);

CATCGMCLEANER_RULE_GEOM_DECLARE_END()

#endif

