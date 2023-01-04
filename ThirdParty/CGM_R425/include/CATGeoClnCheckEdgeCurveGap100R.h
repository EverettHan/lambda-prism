/**
 * @COPYRIGHT DASSAULT SYSTEMES 2005
 */

//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2005
// DESCRIPTION : Class for following CGM Cleaner rule :
//               "ECG_2, EdgeCurve Gap Difference > 100R"
//
// May. 05	Creation                                                 BQJ
//=============================================================================

#ifndef CATGeoClnCheckEdgeCurveGap_h
#define CATGeoClnCheckEdgeCurveGap_h

#include "ExportedByCATCGMGeoClnGeom.h"
#include "CATGeoCln.h"

class CATTrivialMapX;
class CATIdentityMapX;
class CATSetOfPointsMapX;
class CATMapX;
class CATEdgeCurve;

//-------------------------   +++ ComputeMaxGap +++   ------------------------

double ComputeMaxGap(CATEdgeCurve *pEC);

//-------------------------   --- ComputeMaxGap ---   ------------------------

CATCGMCLEANER_RULE_GEOM_DECLARE_BEGIN(CATGeoClnCheckEdgeCurveGap100R)

  int CheckEdgeCurveGap(CATEdgeCurve* ipEdgeCurveToCheck);

CATCGMCLEANER_RULE_GEOM_DECLARE_END()

#endif

