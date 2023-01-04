/**
 * @COPYRIGHT DASSAULT SYSTEMES 2003
 */

//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2003
// DESCRIPTION : Class for following CGM Cleaner rule :
//               "PPO_1, POEC Spec param Inside Spec curve Maxlimits
//
// Jun. 03	Creation                                                 AJM
//=============================================================================

#ifndef CATGeoClnPOECSpecParamOutsideSpecCurve_h
#define CATGeoClnPOECSpecParamOutsideSpecCurve_h

#include "ExportedByCATCGMGeoClnGeom.h"
#include "CATGeoCln.h"

class CATPointOnEdgeCurve;

CATCGMCLEANER_RULE_GEOM_DECLARE_BEGIN(CATGeoClnPOECSpecParamOutsideSpecCurve)

  static void GetToleranceFromEnv(const char *pEnvVarName, double &ioTolerance);

  int CheckPOECSpecParamOutsideSpecCurve(const CATPointOnEdgeCurve* pPOECToCheck,
                                         const double idTolerance1,
                                         const double idTolerance2);

CATCGMCLEANER_RULE_GEOM_DECLARE_END()

#endif

