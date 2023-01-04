/**
 * @COPYRIGHT DASSAULT SYSTEMES 2004
 */

//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2004
// DESCRIPTION : Class for following CGM Cleaner rule :
//               "EIP_1", EdgeCurves With Identical PCurves
//
// Dec. 04	Creation                                                 BQJ
//=============================================================================

#ifndef CATGeoClnCheckEdgeCurveIdenticalPCurves_h
#define CATGeoClnCheckEdgeCurveIdenticalPCurves_h

#include "ExportedByCATCGMGeoClnGeom.h"
#include "CATGeoCln.h"

class CATEdgeCurve;


int CheckForIdenticalPCurve(CATEdgeCurve *pEC, CATCurve **iPCurve);


CATCGMCLEANER_RULE_GEOM_DECLARE_BEGIN(CATGeoClnCheckEdgeCurveIdenticalPCurves)

  int CheckEdgeCurveIdenticalPCurves(CATEdgeCurve* ipEdgeCurveToCheck);

CATCGMCLEANER_RULE_GEOM_DECLARE_END()

#endif

