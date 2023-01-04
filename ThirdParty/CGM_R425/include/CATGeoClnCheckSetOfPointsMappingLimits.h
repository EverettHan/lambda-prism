/**
 * @COPYRIGHT DASSAULT SYSTEMES 2003
 */

//============================================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2003
// DESCRIPTION : Class for following CGM Cleaner rule :
//               "SPM_1, Check SetOfPointsMapping for curve limits inclusion"
//               "Check SetOfPointsMapping for curve limits inclusion for CATSetOfPointsMapX
//               for ref/co curves of an edge curve within the resolution."
//
// Nov. 03	Creation                                                 AJM
//============================================================================================

#ifndef CATGeoClnCheckSetOfPointsMappingLimits_h
#define CATGeoClnCheckSetOfPointsMappingLimits_h

#include "ExportedByCATCGMGeoClnGeom.h"
#include "CATGeoCln.h"

class CATEdgeCurve;

CATCGMCLEANER_RULE_GEOM_DECLARE_BEGIN(CATGeoClnCheckSetOfPointsMappingLimits)

  int CheckEdgeCurveSetOfPointsMappingLimits(CATEdgeCurve* pCurveToCheck);

CATCGMCLEANER_RULE_GEOM_DECLARE_END()

#endif

