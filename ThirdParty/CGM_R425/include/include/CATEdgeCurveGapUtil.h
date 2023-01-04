/**
 * @COPYRIGHT DASSAULT SYSTEMES 2004
 */

//=============================================================================
//
// COPYRIGHT   : DASSAULT SYSTEMES 2004
// DESCRIPTION : Class for following CGM Cleaner rule :
//               "ECG_1, EdgeCurve Stored/Actual Gap > Resolution"
//
// Jul. 04	Creation                                                 BQJ
//=============================================================================

#ifndef CATEdgeCurveGapUtil_h
#define CATEdgeCurveGapUtil_h

#include "YP00IMPL.h"
#include "CATBoolean.h"
#include "CATListOfCATCurves.h"

class CATTrivialMapX;
class CATIdentityMapX;
class CATSetOfPointsMapX;
class CATMapX;
class CATEdgeCurve;

class ExportedByYP00IMPL CATEdgeCurveGapUtil
{
public:
  static double ComputeMaxGap(CATTrivialMapX     *pTMX , CATEdgeCurve *pEC = 0, CATBoolean iGapToCompute = FALSE);
  static double ComputeMaxGap(CATSetOfPointsMapX *pSPMX, CATEdgeCurve *pEC = 0, CATBoolean iGapToCompute = FALSE);
  static double ComputeMaxGap(CATMapX            *pMapX, CATEdgeCurve *pEC = 0, CATBoolean iGapToCompute = FALSE);
  static double ComputeMaxGap(                           CATEdgeCurve *pEC ,    CATBoolean iGapToCompute = FALSE);
  
  static double ComputeMaxGap2                          (CATEdgeCurve *pEC);
  static int    GetCompCurves     (CATEdgeCurve *pEC, CATLISTP(CATCurve) &CurveList);
  static double ComputeMaxGapBasic(CATEdgeCurve *pEC, CATLISTP(CATCurve) &CurveList);

};

#endif

