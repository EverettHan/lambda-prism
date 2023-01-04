// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATConfusionEdgeCurveSur :
// Class for crossing intersections between an EdgeCurve and a Surface used
// by the Shell and Thickness operators
//
//=============================================================================
// Usage notes:
//
//
//=============================================================================
// Jan. 99 Creation                                 X. Gourdon
//=============================================================================

#ifndef CATConfusionEdgeCurveSur_H
#define CATConfusionEdgeCurveSur_H

#include "Y30C3XGG.h"

#include "CATMathDef.h"
#include "CATSurLimits.h"
#include "CATCGMVirtual.h"
#include "CATCreateConfusionEdgeCurveSur.h"

class CATGeoFactory;
class CATCurve;
class CATEdgeCurve;
class CATPointOnEdgeCurve;
class CATSurface;
class CATSurParam;
class CATSoftwareConfiguration;

class ExportedByY30C3XGG CATConfusionEdgeCurveSur : public CATCGMVirtual
{

public:

  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------
  CATConfusionEdgeCurveSur(CATGeoFactory * iFactory,
                           CATSoftwareConfiguration * iConfig,
                           CATEdgeCurve * iECrv, 
                           CATPointOnEdgeCurve * iStartPOEC,
                           CATPointOnEdgeCurve * iEndPOEC,
                           CATCurve * iPCrv0,
                           CATCurve * iPCrv1,
                           CATSurface * iSurface,
                           CATSurLimits & iSurLimits,
                           CATSurParam * iSurParamStart[2],
                           CATSurParam * iSurParamEnd[2]);

  ~CATConfusionEdgeCurveSur();
                             
  
  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------
  
  // Return an edgecurve if there is confusion between iStartPOEC and iEndPOEC,
  // else return 0
  CATEdgeCurve * GetEdgeCurve(CATPointOnEdgeCurve *& oStart,
                              CATPointOnEdgeCurve *& oEnd);
  
  // Running the operator
  void Run();
  
private:
  
  // Input data
  CATGeoFactory * _Factory;
  CATSoftwareConfiguration * _Config;
  CATEdgeCurve * _ECrv;
  CATPointOnEdgeCurve * _StartPOEC, * _EndPOEC;
  CATCurve * _PCrv0, * _PCrv1;
  CATSurface * _Surf;
  CATSurLimits _SurLim;
  CATSurParam * _SurParamStart[2], * _SurParamEnd[2];

  // Output data
  CATPointOnEdgeCurve * _OutputStart, * _OutputEnd;
  CATEdgeCurve * _OutputECrv;
};

#endif
