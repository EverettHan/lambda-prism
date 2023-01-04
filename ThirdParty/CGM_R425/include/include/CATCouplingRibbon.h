// COPYRIGHT DASSAULT SYSTEMES 
//=============================================================================
//
// CATCouplingRibbon :
// Class for junction edge in-between parallel result
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Nov. 28 2005 Creation                         REN
//=============================================================================
#ifndef CATCouplingRibbon_H
#define CATCouplingRibbon_H

#include "Y30UIUTI.h"

#include "CATSurParam.h"
#include "CATMathDef.h"
#include "CATGeoDef.h"
#include "CATCGMVirtual.h"
#include "CATCrvLimits.h"

class CATCurve;
class CATPCurve;
class CATGeoFactory;
class CATSurface;
class CATPointOnEdgeCurve;
class CATEdgeCurve;
class CATMathPoint;
class CATMathDirection;
class CATSoftwareConfiguration;

class ExportedByY30UIUTI CATCouplingRibbon   : public CATCGMVirtual
{
 public:
  CATCouplingRibbon();     
  
  CATCouplingRibbon(CATGeoFactory * iFactory,
                      CATSoftwareConfiguration * iConfig,
                      CATEdgeCurve * iECrvFirst,
                      const CATPointOnEdgeCurve * iPOEC_ECrv_First,
                      CATEdgeCurve * iECrvSecond,
                      const CATPointOnEdgeCurve * iPOEC_ECrv_Second,
                      CATEdgeCurve * iECrvBord,
                      CATPointOnEdgeCurve * iPOEC_Proj_First,
                      CATPCurve * iBord1,
                      CATPointOnEdgeCurve * iPOEC_Proj_Second,
                      CATPCurve * iBord2,
                      CATGeoContinuity   iSharpness );

  
  virtual ~CATCouplingRibbon();
    
  /*CATCouplingRibbon * CATCreateCouplingRibbon(CATGeoFactory * iFactory,
                                                  CATSoftwareConfiguration * iConfig,
                                                  CATEdgeCurve * iECrvFirst,
                                                  const CATPointOnEdgeCurve * iPOEC_ECrv_First,
                                                  CATEdgeCurve * iECrvSecond,
                                                  const CATPointOnEdgeCurve * iPOEC_ECrv_Second,
                                                  CATEdgeCurve * iECrvBord,
                                                  CATPointOnEdgeCurve * iPOEC_Proj_First,
                                                  CATPCurve * iBord1,
                                                  CATPointOnEdgeCurve * iPOEC_Proj_Second,
                                                  CATPCurve * iBord2,
                                                  CATGeoContinuity   iSharpness,
                                                  CATMathDirection  *iDirection = 0);*/

  void Run();
  
  //-----------------------------------------------------------------------
  //- Reading the results
  //-----------------------------------------------------------------------
  //
  // Returns TRUE if points are considered as coupled, FALSE else
  //
  CATBoolean GetCoupling();
  // If points are coupled and a Edge curve should be created between the two input
  // POECS, return this EdgeCurve together with the TwoPCurve or One PCurve on the Two surface.
  // 0 is returned if no such EdgeCurve exists.
  //
  // Si on est sur le deuxieme constructeur l'EdgeCurve cree si elle existe est la meme que iECrv_Bord
  // et les POECs sont les memes que iPOEC_Proj_First et iPOEC_Proj_Second.
  //
  CATEdgeCurve * GetEdgeCurve(CATPointOnEdgeCurve * & oStart, CATPointOnEdgeCurve * & oEnd);
  //
  // Return a Pcurve in The Surface
  //
  CATPCurve * GetPCurve(CATSurface * iSurface);
  //
  // Setting method
  // If  the EdgeCurve is iECrvFirst = iECrvSecond iIndex !=0 (1 and 2)
  // Else iIndex = 0;
  //
  void SetLimits(CATEdgeCurve * iEdgeCurve, CATPointOnEdgeCurve * iStartPOEC, CATPointOnEdgeCurve * iEndPOEC,  CATLONG32 iIndex=0);
  //
  // Returns TRUE if posage mode, FALSE else
  
  void SetPosageMode (CATBoolean iPosageMode=0);
 
  
protected:
 
  CATGeoFactory * _Factory;
  CATSoftwareConfiguration * _Config;
  CATEdgeCurve * _ECrv[2];
  const CATPointOnEdgeCurve * _StartPOEC, * _EndPOEC;
  CATSurface * _Surface;

  CATPointOnEdgeCurve * _StartPOEC_Proj, *_EndPOEC_Proj;
  CATSurParam * _InputSurParam[2];
  CATEdgeCurve * _ECrvBord;
  CATPCurve * _Bord1, *_Bord2;
  
  CATBoolean _Coupling,  _MergedCurveToCreate, _SimCurveToCreate;
  CATPCurve * _OutputPCrv;
  CATEdgeCurve * _OutputECrv;
  CATPointOnEdgeCurve * _LimECrv1[2];
  CATPointOnEdgeCurve * _LimECrv2[2];
  CATPointOnEdgeCurve * _LimECrv_Bord[2];
  CATGeoContinuity   _Sharpness;
  double _TrouVertex1, _TrouVertex2;
  CATBoolean _PosageMode;	  
  //-----------------------------------------------------------------------
  virtual CATBoolean TestCouplingFromTwoSurfaces() = 0;
};

#endif

