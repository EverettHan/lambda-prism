// COPYRIGHT DASSAULT SYSTEMES 
//=============================================================================
//
// CATCouplingParallel :
// Class for junction edge in-between parallel result
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Nov. 28 2005 Creation                         REN
//=============================================================================
#ifndef CATCouplingParallel_H
#define CATCouplingParallel_H

#include "Y30UIUTI.h"
#include "CATCouplingRibbon.h"

#include "CATSurParam.h"
#include "CATMathDef.h"
#include "CATGeoDef.h"
#include "CATCGMVirtual.h"
#include "CATCrvLimits.h"
#include "CATCollec.h"
#include "CATDistanceTool.h"
#include "CATConnect.h"
#include "CATParallelConnectTool.h"
#include "CATMathVector.h"

class CATCurve;
class CATPCurve;
class CATGeoFactory;
class CATSurface;
class CATPointOnEdgeCurve;
class CATPointOnSurface;
class CATEdgeCurve;
class CATMathPoint;
class CATMathDirection;
class CATSoftwareConfiguration;
class CATMathQuickDiscretizeFunctionX;
class CATPlane;
class CATConnectComputer;

class  ExportedByY30UIUTI CATCouplingParallel   : public CATCouplingRibbon
{
 public:    
  CATCouplingParallel(CATGeoFactory * iFactory,
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
                      CATBoolean  iEdgeEdgeNuplet);
       
  virtual ~CATCouplingParallel();

  CATBoolean TestCouplingFromTwoSurfaces();

  void SetParallelInfo(CATDistanceTool *iDistTool, CATSurface *iOldSurface, CATSurface *iNewSurface, double igap,
                       CATCurve *iCurve, CATLONG32 iCrvOri,CATCrvLimits &iCrvLimits,
                       CATSurface *iSurface, CATLONG32 iSurOri, CATSurLimits &iSurLimits,
                       CATParallelConnectTool *iConnectTool, CATEdgeCurve * iTrackCurve = NULL);

  // decide good poec out of the end poecs of the link edge.. Case015_JE
  CATBoolean DecideGoodPOEC(CATPointOnEdgeCurve *ispoec, CATPointOnEdgeCurve *iepoec, double &oGap, CATBoolean iInitIsInGap );
  // retrieves limit of missing sol on wiresupport
  CATPointOnEdgeCurve * GetEndPOEC();
  CATPointOnEdgeCurve * GetStartPOEC();
  void GetStartParam (CATCrvParam &ioStartParam );

  // retrieves param of the end on wiresupport
  double GetEndParam ();
  // wiresupport limits set, used to decide end on wiresupport
  void SetInputLimitsInfo(CATPointOnEdgeCurve *& iLim1POEC, CATPointOnEdgeCurve *& iLim2POEC, CATLONG32 iOri = NULL, int i = 0 );
  // decides limit of missing sol on wiresupport
  /*void FindLimitOnInputCurve(CATMathQuickDiscretizeFunctionX *& _ExplicitFunction, double &NewPar,
                             CATCrvParam iCrvParam1, CATCrvParam iCrvParamPC1);*/
  //void SetDuplicateEndPOEC(CATPointOnEdgeCurve *iPOEC);
  //sets the ParallelComputer and ParallelFunction, which is used to create&use Geodesic PtDir Ope.
  void GetParallelComputerAndFunction();
  //Returns Param of ptonSur on Pcurve
  void CreateDistMinPtCrv(CATPointOnSurface * iPtOnSurf, CATPCurve *iCurve, CATCrvParam &ioParam, double *ioDistancePtCrv = NULL);
  //Returns Intersection param on given curve & plane
  CATBoolean CreateIntersectionPlnCrv(CATPlane *iPlane, CATCurve * iCrv, CATCrvParam &ioParam );
  
  // Sets the Other end of junction-edge on wiresupport & shellsupport for Geodesic Parallel
  CATBoolean FindEndOfMissingSolutionGeo(const CATCrvParam &iSPar, const CATCrvParam &iEPar, const CATCrvParam &iPar1,
                                   CATPointOnEdgeCurve *ispoec, CATPointOnEdgeCurve *iepoec,
                                   double iTemp, double iOutSideTrack, double StartForTrial,
                                   double EndForTrial, const CATCrvParam &StartParamForTrial, double delta,
                                   CATPCurve *iCrvForEvaluation, CATBoolean endSurfIsOld);

  // Sets the Other end of junction-edge on wiresupport & shellsupport for Euclidian Parallel
  CATBoolean FindEndOfMissingSolutionEucl(const CATCrvParam &iSPar, const CATCrvParam &iEPar, const CATCrvParam &iPar1,
                                    CATPointOnEdgeCurve *ispoec, CATPointOnEdgeCurve *iepoec,
                                    double iTemp, double iOutSideTrack,double iStartForTrial,
                                    double iEndForTrial, const CATCrvParam &iStartParamForTrial, double delta,
                                    CATPCurve *iCrvForEvaluation,const  CATCrvParam &iLim2TrackCrvOnWire,
                                    const CATMathPoint &StartPointOnShellJE);

  // Computes param which is outside track on input wire support
  double GetOutSideParam(const CATCrvParam &iStartParamForTrial, const CATCrvParam &iLim1InputCurve, const CATCrvParam &iLim2InputCurve,
                         const CATCrvParam &iLim1TrackCrvOnWire, const CATCrvParam &iLim2TrackCrvOnWire, double iDelta);
  double GetOutSideParam(const CATCrvParam &iStartParamForTrial, double iDelta,const CATCrvLimits &iLim);
  void SetNewPlaneLimits(CATPlane *iPlane, CATMathPoint &iPoint);
  CATBoolean CheckSide(CATPCurve *iCrv,const CATCrvParam &iStartParam,const CATCrvParam &iIntParam, CATBoolean iUseDistMinCrvCrv, const CATCrvParam &iCrvPar);
  // Used when the initialization of ribbon is with edge-edge nuplet... Configuration 5 Cases
  void FindBothEndsOfSolution();
  CATBoolean _deleteJE;

private:
  CATDistanceTool * _DistTool;
  CATSurface * _OldSurface, *_NewSurface, *_InputSurface;  
  double _Offset, _Gap, _EndParam;
  CATConnectComputer * _Computer;
  CATMathQuickDiscretizeFunctionX * _ExplicitFunction;
  CATCurve * _InputCurve;
  CATLONG32 _CrvOri, _SurOri, _Ori0, _Ori1;
  CATCrvLimits _CrvLimits;  
  CATSurLimits _SurLimits;
  CATParallelConnectTool * _ConnectTool;
  CATPointOnEdgeCurve *_Lim1POEC, *_Lim2POEC, *_Lim11POEC, *_Lim22POEC, *_POECTrackCrvOnWire[2];
  CATMathVector _Tangent; 
  CATEdgeCurve * _TrackCurveOnWire;
  CATBoolean _EdgeEdgeNuplet;
  CATCrvParam _StartParam;
};

#endif
