/**
 * @COPYRIGHT DASSAULT SYSTEMES 2004
 */

//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2004
// DESCRIPTION : Class for following CGM Cleaner rule :
//               "ECG_1, EdgeCurve Stored/Actual Gap > Resolution"
//
// Jul. 04	Creation                                                 AJM
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

double ComputeMaxGap(CATTrivialMapX *pTMX, CATEdgeCurve *pEC);
double ComputeMaxGap(CATSetOfPointsMapX *pSPMX, CATEdgeCurve *pEC);
double ComputeMaxGap(CATMapX *pMapX, CATEdgeCurve *pEC);

double ComputeMaxGap(CATEdgeCurve *pEC);

//-------------------------   --- ComputeMaxGap ---   ------------------------

CATCGMCLEANER_RULE_GEOM_DECLARE_BEGIN(CATGeoClnCheckEdgeCurveGap)

  int CheckEdgeCurveGap(CATEdgeCurve* ipEdgeCurveToCheck);

CATCGMCLEANER_RULE_GEOM_DECLARE_END()

#endif

