// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATIntersectionCrvCrvCx2:
// implementation of curve curve intersection
//
//=============================================================================
// Usage Notes:
//
// Used through CATIntersection interface for general intersection and
// for boolean operation
//=============================================================================
// 28/11/08 NLD Utilisation de CATCGMOperatorDebug pour outillage standard de debug/mesure
// 20/08/14 Q48 X-scale migration of replay mechanism
// 24/02/22 S9L Best confusion obtained by minimization along arcs along solution curve
// 08/04/22 NLD 4xCode refactor through ArcLoopOnConfusion()
//=============================================================================

#ifndef CATINTERSECTCRVCRVCX2_H
#define CATINTERSECTCRVCRVCX2_H
#include "Y30C3XGG.h"
#include "CATIntersectionCrvCrv.h"
#include "CATCGMOperatorDebug.h"
#include "CATArrayManagement.h"
#include "CATMathBox.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATMathSquareDistXYs.h"

class CATHelix ;
class CATArrayManagement;
class CATCartesianPoint;
class CATCrvParam;
class CATCrvLimits;
class CATCurve;
class CATEdgeCurve;
class CATGeoFactory;
class CATPointOnCurve;
class CATPointOnEdgeCurve;
class CATMathCurve;
class CATMathBox;
class CATTryConfusionCrvCrv;
class CATIntersectionPCrvPCrv;
class CATSoftwareConfiguration;
class CATCrvCrvResultCurve;
class CATPCurve;

class CATGeoODTScaleManager;

class ExportedByY30C3XGG CATIntersectionCrvCrvCx2 : public CATIntersectionCrvCrv
{
private:
  // data
  CATCurve                 * _Curve1;
  CATCurve                 * _Curve2;
  CATSoftwareConfiguration * _SoftwareConfiguration;
  CATMathCurve             * _mathcrv1,
                           * _mathcrv2;
  CATMathPoint               _Origin;
  CATMathVector              _I,
                             _J;
  int                        _SetMathCrv1,
                             _SetMathCrv2;
  int                        _IndexPoint;
  double                   * _ParamsOnCurve1;                /* points on _Curve1 */
  double                   * _ParamsOnCurve2;                /* points on _Curve2 */
  double                   * _ReconvParamsOnCurve1;
  double                   * _ReconvParamsOnCurve2;
  CATTryConfusionCrvCrv   ** _TryConf;
  CATIntersectionPCrvPCrv  * _ResPcrv;    // (dad) results for PCrv/PCrv Intersection
  int                        _nAllocConf;
  int                        _IndexCurve;
  int                        _NumberOfPointSolutions;
  int                        _NumberOfCurveSolutions;
  int                        _SizeOfParamOnCurve;
  CATArrayManagement         _ArraySize;
  int                        _ConfusionSearch; 
  int                        _ExtremitiesSearch;
  int                        _Reconvergence;
  int                        _FastInter;
  int                        _SetBox1,
                             _SetBox2;
  CATMathBox                 _Box1,
                             _Box2;
  int                        _IndConf,
                             _NbConf;
  CATBoolean                 _Force3DCompute;
  CATBoolean                 _ForcePlaneMethod;
  CATBoolean                 _RunReconvergence;
  /* Confusion tolerance*/
  double                     _Tolerance;
  CATCrvLimits             * _LimitsOnCurve[2];
  CATHelix                 * _helix;
  CATLONG32                  _IsHelix;
  CATCrvLimits             * _LimitsOnHelix;

  //EAB - Stabilization
  CATBoolean                 _AskedForStabilization;
  CATBoolean                 _StabilizationRequired;
  CATCrvCrvResultCurve    ** _ResultConf;
  CATPCurve                * _PCurve1,
                           * _PCurve2;

  // Methods
  CATLONG32  TrivialOffsetCase         ();
  void       AppendPoint               ( double CrvParam1, double CrvParam2 );
  CATLONG32  KeepSolutionOnCurve       ( CATLONG32 CurveRange, CATCrvParam &CurveParam );
  CATLONG32  KeepSolutionOnLineOrCircle( CATLONG32 curveRange, double & CurveParam );
  // Run Methods
  void       RunLineLine(     CATCrvLimits &iLimitsLine1, CATCrvLimits &iLimitsLine2 );
  void       RunLineCircle(   CATLONG32 lineRange, CATCrvLimits &iLimitsLine,
                              CATCrvLimits &iLimitsCircle );
  void       RunLineCurve(    CATLONG32 lineRange,
                              CATCrvLimits &iLimitsLine, CATCrvLimits &iLimitsCurve,
                              CATCrvParam &CurveParam1, CATCrvParam &CurveParam2 );
  void       RunCircleCircle( CATCrvLimits &iLimitsCircle1,
                              CATCrvLimits &iLimitsCircle2 );
  void       RunCircleCurve(  CATGeoFactory *implicit, CATLONG32 circleRange,
                              CATCrvLimits &iLimitsCircle,
                              CATCrvParam &CurveParam1, CATCrvParam &CurveParam2 );
  CATLONG32  RunPlaneMethod(  CATCrvParam &Curve1Param1, CATCrvParam &Curve2Param2,
                              CATMathInterval2D &domain , CATLONG32 i, CATLONG32 j);
  void       RunCurveCurve3D( CATCrvParam &Curve1Param1, CATCrvParam &Curve2Param2,
                              CATMathInterval2D &domain  , CATLONG32 i, CATLONG32 j);
  void       RunCurveCurve(   CATCrvParam &Curve1Param1, CATCrvParam &Curve1Param2,
                              CATCrvParam &Curve2Param1, CATCrvParam &Curve2Param2 );
  void       RunPCrvPCrv( const CATPCurve *iPCurve1,const CATPCurve *iPCurve2);
  void       RunReconvergence();

  void       ArcLoopOnConfusion  (                  CATGeoFactory * ImplicitFactory   ,
                                                    double          TolParamComparison,
                                                    double          TolConfusion      ,
                                                    CATCurve      * Curve             ,
                                              const CATCrvParam   & CurveParam        ,
                                                    int             Incr              ,
                                                    CATLONG32     & FirstArc          , // entrée/sortie
                                                    CATLONG32     & LastArc           );// entrée/sortie

  
  CATLONG32  ComputeMeanPlane(const CATCrvParam & iCurve1Param1,
                              const CATCrvParam & iCurve1Param2,
                              const CATCrvParam & iCurve2Param1,
                              const CATCrvParam & iCurve2Param2 );
  // Check Methods
  void       CheckIndexPoint( char *method ) const;
  void       CheckIndexCurve( char *method ) const;
  void       CheckOperand( CATCurve *iCurve, char * method ) const;
  // Set Methods
  void       SetConfusionSearch  (int NewConfusionSearch);
  void       SetExtremitiesSearch(int NewExtremitiesSearch);
  void       SetFastIntersection (int NewFastInter); 
  void       SetBox              (CATCurve * iCurve,const CATMathBox &iBox);
  void       SetMathCurve        (CATCurve* iCurve, CATMathCurve* iMathCurve);

  // Other Methods
  CATLONG32  TestExtremitiesAndConfusions(const CATCrvLimits &Limits1,const CATCrvLimits &Limits2);
  CATLONG32  TestClosingProblem          (CATSurface *iSurface, const CATPCurve *iPCurve);
  CATLONG32  TestCrvClosed               (const CATCurve *iCurve, CATCrvParam &CrvParamStart, CATCrvParam &CrvParamEnd) const;
  void       SearchConfusionsBetweenSolutions();
  void       Reset                       ();
  void       Initialize                  (CATCurve * iCurve1, CATCurve * iCurve2);
  
  void       CorrectLimits               (CATCrvLimits & ioLim1, 
                                          CATCrvLimits & ioLim2) const;

  void       CorrectLimits               (const CATCurve     * iCurve,
                                                CATCrvLimits & ioLim) const;

  CATBoolean IsAnHelix                   (CATCurve* iCurve);
  void       ProjectMathBoxExtremitiesToDirectionOfHelix(CATCrvLimits& CurveLimitsOnHelix);

public:
  // Object Management
                      CATIntersectionCrvCrvCx2 ( CATGeoFactory            * iFactory,
                                                 CATSoftwareConfiguration * iConfig ,
                                                 CATCurve                 * iCurve1 ,
                                                 CATCurve                 * iCurve2 );
                     ~CATIntersectionCrvCrvCx2 ();
  /*  pseudo copy for CrvSur */

  int                 RunOperator();
  CATCGMOperatorDebugDeclareRun(CATIntersectionCrvCrvCx2,CATIntersectionCrvCrv);

  void                SetCurve         ( CATCurve *NewSecondCurve );
  void                SetTolerance     ( double NewTolerance);
  void                SetReconvergence ( int    NewReconvergence);
  //Activation de la stabilisation
  void                SetStabilizeConfusions(CATBoolean iIsStabilize = TRUE);
  
  void                BeginningPoint   ();
  void                BeginningCurve   ();
  void                BeginningCurveInt();
  CATBoolean          NextPoint        ();
  CATBoolean          NextCurve        ();
  CATBoolean          NextCurveInt     ();
  CATLONG32           GetNumberOfPoints() const;
  CATLONG32           GetNumberOfPointSolutions() const;
  CATLONG32           GetNumberOfCurves() const;
  CATLONG32           GetNumberOfCurveSolutions() const;
  CATCartesianPoint * GetCartesianPoint();
  CATPointOnCurve   * GetPointOnCurve( CATCurve *iCurve , const CATLONG32 iIndex=0) const;
  CATCrvParam         GetCurveParam  ( CATCurve *iCurve , const CATLONG32 iIndex=0) const;
  void                GetCurveParam  ( CATCurve* iCurve , CATCrvParam & oCrvParam, const CATLONG32 iIndex=0) const;

  CATCrvLimits        GetCurveLimits (CATCurve *iCurve) const;
  void                GetCurveLimits (CATCurve* iCurve, CATCrvLimits &oLimits) const;
  CATEdgeCurve      * GetEdgeCurve   (CATPointOnEdgeCurve * & oStart, CATPointOnEdgeCurve * & oEnd) const ;
  CATEdgeCurve      * GetEdgeCurveInt(CATPointOnEdgeCurve * & oStart, CATPointOnEdgeCurve * & oEnd) const ;
  // Tangential warning diagnostic associated to a curve solution, return TRUE is the curve solution is
  // in an instable tangential configuration
  CATBoolean          GetTangentialWarningDiagnostic() const;
  
  void                GetFirstConfusionParam    (CATCrvParam & Param1, CATCrvParam & Param2) const ;
  void                GetFirstConfusionParamInt (CATCrvParam & Param1, CATCrvParam & Param2) const ;
  void                GetSecondConfusionParam   (CATCrvParam & Param1, CATCrvParam & Param2) const ;
  void                GetSecondConfusionParamInt(CATCrvParam & Param1, CATCrvParam & Param2) const ;
  void                GetBestConfusionParam     (CATCrvParam & Param1, CATCrvParam & Param2) const ;
  void                UseLimits                 (CATCrvLimits *iLimits1ToTakeIntoAccount,
                                                 CATCrvLimits *iLimits2ToTakeIntoAccount );
  void                Force3DCompute            (CATBoolean iForce3D = TRUE);
  void                SetPlaneMethod            (CATBoolean iForcePlameMethod = TRUE);

  virtual CATSoftwareConfiguration* GetSoftwareConfiguration() const;
  //========================================================================
  // Gestion CGMReplay
  //========================================================================
protected:
  friend class CATGeoStreamFactory;
  
  // private static data
  static CATString _OperatorId;
  //static CATGeoOpTimer _Timer;
  
public:
  
  const CATString * GetOperatorId();
  //-----------------------------------------------------------------------
  //- Gestion timer
  //-----------------------------------------------------------------------  
  //CATGeoOpTimer * GetTimer();
  
  //-----------------------------------------------------------------------
  //- Gestion Mode Record 
  //-----------------------------------------------------------------------  
  
          CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  virtual void       WriteInput(CATCGMStream  & ioStream);

  virtual void       ReadInput(      CATCGMStream          & ioStream,
                               const int                     iVersionOfStream,
                                     CATGeoODTScaleManager * iScaleManager);
  
  virtual void       WriteOutput    (CATCGMStream & ioStream);
  virtual CATBoolean ValidateOutput (CATCGMStream& ioStream,  CATCGMOutput & os,int VersionNumber=1);
  virtual void       Dump           (CATCGMOutput& os ) ;
  virtual void       DumpOutput     (CATCGMOutput& os );
  virtual void       DumpOutput     (CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  
  static CATGeoODTScaleManager* ReadStreamHeaderInfo(      CATCGMStream   & ioStream,
                                                     const short            iVersionOfStream,
                                                           CATGeoFactory *& oFactory,
                                                           CATCurve      *& oCurve1,
                                                           CATCurve      *& oCurve2,
                                                           CATCrvLimits   & oLimits1,
                                                           CATCrvLimits   & oLimits2);

  virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);
  virtual CATCGMOperator::CATCheckDiagnostic CheckInput(CATCGMOutput & os);
};


#endif
