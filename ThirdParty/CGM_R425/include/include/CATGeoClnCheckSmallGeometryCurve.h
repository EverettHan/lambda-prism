/**
 * @COPYRIGHT DASSAULT SYSTEMES 2004
 */

//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2004
// DESCRIPTION : Class for following CGM Cleaner rule :
//               "CSG_1, Curve Arc Smaller than Resolution"
//
// Jul. 04	Creation                                                 AJM
//=============================================================================

#ifndef CATGeoClnCheckSmallGeometryCurve_h
#define CATGeoClnCheckSmallGeometryCurve_h

#include "ExportedByCATCGMGeoClnGeom.h"
#include "CATGeoCln.h"

class CATCurve;

CATCGMCLEANER_RULE_GEOM_DECLARE_BEGIN(CATGeoClnCheckSmallGeometryCurve)

  int CheckSmallGeometryCurve(CATCurve* ipCurveToCheck);

CATCGMCLEANER_RULE_GEOM_DECLARE_END()

#endif

