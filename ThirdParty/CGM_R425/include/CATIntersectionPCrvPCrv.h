// COPYRIGHT DASSAULT SYSTEMES 1998
//===================================================================
//
// CATIntersectionPCrvPCrv
//  Intersection of two PCurves
//
//===================================================================
//      97    Creation                                      S.Royer
// May. 98    Modif on new specifications (tolerances and confusions)
//                                                          X. Gourdon
// 28/11/08 NLD Utilisation de CATCGMOperatorDebug pour outillage standard de debug/mesure
// 05/12/08 NLD Mieux: afin d'eviter des impacts de compilation des applications appelantes,
//              on declare toujours Run() et on l'implemente avec CATCGMOperatorDebugRunResult()
// 21/01/09 NLD Ajout de _EliminationTol qui remplace une donnee statique
// 10/06/09 JSX Ajout de _SquareScaleSaved pour opti perfo
// 18/12/09 NLD Ajout de GetCurrentConfusionExtremityParam() pour resolution OLK
// 21/07/10 JSX Ajout method SetPcurve sans POEC;
//              _MaxTol devient _MaxUVTol il ne faudrait qd meme pas confondre !
//              On evite certains recalcul (pour SweepCDS)
//              _OptiSetPCrv_SquareScale et _OptiSetPCrv_TolUV remplace _PCrv1Computed 
//              factorisation avec SetPCurve_Init
// 16/09/11 FDS Data members alignement + allocation optimisation
// 18/07/13 Q48 IR-210309: add _TangentialTol_CurvatureFactor to allow to increase tolerance
// 02/05/14 Q48 Added treatment of P-lines on closed surfaces
// 17/02/14 XMH Add method SetPCurves
// 05/08/15 XMH Add _LockPCurves. When FALSE caller takes responibility for lock/unlock of PCurves.
// 05/12/16 R1Y Added a reference (to the existing pointer argument) in Remove().
// 16/05/19 JSX Move many Method/data to private, order data (start with input saved by replay)
// 01/07/20 Q48 Add IsExtremityPoint for IR-755773
// 18/03/21 Q48 Add IsIsolatedExtremityPoint for IR-755773
//===================================================================

#ifndef CATINTERSECTIONPCRVPCRV_H
#define CATINTERSECTIONPCRVPCRV_H

//===================================================================
// Geometric Operators
#include "Y30C1XMM.h"
#include "CATGeoOperator.h"
#include "CATGeoOpDebug.h"

// System
#include "CATString.h"

// Mathematics
#include "CATMathDef.h"
#include "CATMathInline.h"
#include "CATSkillValue.h"
#include "CATTolerance.h"

// Geometric Object
#include "CATGeoFactory.h"
#include "CATCrvLimits.h"

// GMModelInterface
#include "CATConst2D.h"
#include "CATIntersectionPCrvPCrvSign.h"
#include "CATGeoOpTimer.h"

// ----------------------------------------
// Mathematics
class CATMathVector2D;
class CATSoftwareConfiguration;

// Advanced Mathematics
class CATMathAttrList;
class CATMathFunctionX;
class CATMathInterval2D;
class CATMathSetOfPointsND;

// Geometric Object
class CATSurParam;
class CATPCurve;
class CATEdgeCurve;
class CATPointOnCurve;
class CATPointOnEdgeCurve;

// Geometric Operators
class CATInclusionPtPCrvCx2;

// Local Declaration
class CATPCrvPCrvResultPoint;
class CATPCrvPCrvResultConfusion;

//===================================================================
class ExportedByY30C1XMM CATIntersectionPCrvPCrv : public CATGeoOperator
{
  CATCGMVirtualDeclareClass(CATIntersectionPCrvPCrv);
 public:

  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------
  CATIntersectionPCrvPCrv (       CATGeoFactory            * Factory,
                                  CATSoftwareConfiguration * iConfig,
                            const CATPCurve                * Pcurve1,
                            const CATPCurve                * Pcurve2);

  CATIntersectionPCrvPCrv (       CATGeoFactory            * Factory,
                                  CATSoftwareConfiguration * iConfig,
                            const CATPCurve                * Pcurve1,
                            const CATCrvLimits             & Limit1,
                            const CATPCurve                * Pcurve2,
                            const CATCrvLimits             & Limit2,
                            const CATBoolean                 iLockPCurves = TRUE);
  
  CATIntersectionPCrvPCrv (       CATGeoFactory            * Factory,
                                  CATSoftwareConfiguration * iConfig,
                            const CATEdgeCurve             * iECrv1,
                            const CATPCurve                * Pcurve1,
                            const CATCrvLimits             & Limit1,
                            const CATEdgeCurve             * iECrv2,
                            const CATPCurve                * Pcurve2,
                            const CATCrvLimits             & Limit2,
                            const CATPointOnEdgeCurve      * iStart1,
                            const CATPointOnEdgeCurve      * iEnd1,
                            const CATPointOnEdgeCurve      * iStart2,
                            const CATPointOnEdgeCurve      * iEnd2);
  
  //- Destructor
  ~CATIntersectionPCrvPCrv();

  CATSoftwareConfiguration * GetSoftwareConfiguration() const;
  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------  
  //NLD051208 Run() inconditionnel au lieu de CATCGMOperatorDebugDeclareRun(CATIntersectionPCrvPCrv,CATGeoOperator);
  int Run();

  /** @nodoc @nocgmitf */
  virtual int RunOperator();

  // SET
  
  void SetExtremityTol(const double tol );
  void SetConfusionTol(const double tol ); 
  void SetNoTangentialExtremitySolution(const CATPointOnEdgeCurve * iPOEC1, const double iTol1,
                                        const CATPointOnEdgeCurve * iPOEC2, const double iTol2);
  // 3D tangential tolerance; defaut is 0.01*resolution
  void SetTangentialTolerance(double iTangentialTol);
  //Activation de la stabilisation
  //Stabilization des zones de confusion - methode en cours de conv voir avec EAB pour utilisation
  void SetStabilizeConfusions(CATBoolean iIsStabilize = TRUE);
  
  //Remplace une des pcurves intersectees (la premiere). 
  void SetPCurve (const CATPCurve *PCurve, const CATPointOnEdgeCurve * iStart2, const CATPointOnEdgeCurve * iEnd2);
  void SetPCurve (const CATPCurve *PCurve , const CATCrvLimits &Limit);
  void SetPCurves(const CATPCurve *PCurve0, const CATCrvLimits &Limit0, 
                  const CATPCurve *PCurve1, const CATCrvLimits &Limit1,
                  const CATBoolean iCheckSurfaces = TRUE);

  // GET
  // Reading point results
  INLINE CATLONG32 GetNumberOfPoints() const;
  INLINE void BeginningPoint();
  INLINE CATLONG32 NextPoint();
  //
  // Si les deux Pcurves sont les memes (iIndex =1 pour la premiere et iIndex = 2 pour la deuxieme)
  //
  void          GetCurveParam(const CATPCurve * Pcurve, CATCrvParam & oParam,  const CATLONG32 Index=-1) const;
  void GetStartConfusionParam(const CATPCurve * Pcurve, CATCrvParam & oParam,  const CATLONG32 Index=0) const;
  void   GetEndConfusionParam(const CATPCurve * Pcurve, CATCrvParam & oParam,  const CATLONG32 Index=0) const;
  //
  //
  CATPointOnCurve                 * GetPointOnCurve        (const CATPCurve    * Pcurve) const;
  CATPointPositionOnCurve           GetPointPositionOnCurve(const CATPCurve    * Pcurve) const;
  CATIntersectionPCrvPCrvSign       GetPointSignature      (const CATPCurve    * Pcurve) const;
  CATIntersectionPCrvPCrvSign       GetPointSignature      (const CATEdgeCurve * iECrv) const;
  CATIntersectionPCrvPCrvCrossing   GetPointCrossing       (const CATPCurve    * Pcurve) const;
  CATIntersectionPCrvPCrvCrossing   GetPointCrossing       (const CATEdgeCurve * iECrv) const;

//#define DuplicatedExtremityPoint
  #ifdef DuplicatedExtremityPoint
  CATBoolean IsExtremityPoint(const CATPCurve* Pcurve) const;
  #endif //DuplicatedExtremityPoint

  // IR-755773: For testing in collaboration with JHN. Please do not use.
  CATBoolean IsIsolatedExtremityPoint() const;

  //
  //Reading Signature and Crossing Point results on EdgeCurve
  //
  CATIntersectionPCrvPCrvSign    GetPointSignatureOnEdgeCurve(const CATEdgeCurve * iECrv) const;
  CATIntersectionPCrvPCrvCrossing GetPointCrossingOnEdgeCurve(const CATEdgeCurve * iECrv) const;
  //
  // Reading mixed solutions
  //
  INLINE CATLONG32 GetNumberOfMixedPoints() const;
  INLINE void BeginningMixedPoint();
  INLINE CATLONG32 NextMixedPoint();
  CATPointOnEdgeCurve * GetStartMixedSolution(const CATEdgeCurve * iECrv, const CATPCurve * Pcurve, const CATLONG32 Index=0);
  CATPointOnEdgeCurve * GetEndMixedSolution  (const CATEdgeCurve * iECrv, const CATPCurve * Pcurve, const CATLONG32 Index=0);
  void GetMixedLimits(const CATPCurve * Pcurve, CATCrvLimits & oLimit) const;
  //
  // Reading confusion results
  //
  INLINE CATLONG32 GetNumberOfConfusions() const;
  INLINE void BeginningConfusion();
  INLINE CATLONG32 NextConfusion();
  CATEdgeCurve * GetEdgeCurve();
  
  // Confusion result relative to PCurve only
  void GetConfusionLimits(const CATPCurve * Pcurve, CATCrvLimits & oLimit) const;
  // Get extremity parameter of current confusion
  // iExtremity=0: start, =1: end
  void   GetCurrentConfusionExtremityParam(const CATPCurve * Pcurve, int iExtremity, CATCrvParam& oParam) const;
  CATPointOnCurve * GetConfusionStartPoint(const CATPCurve * Pcurve) const;
  CATPointOnCurve *   GetConfusionEndPoint(const CATPCurve * Pcurve) const;
  CATPointPositionOnCurve GetConfusionStartPositionOnCurve(const CATPCurve * Pcurve) const;
  CATPointPositionOnCurve   GetConfusionEndPositionOnCurve(const CATPCurve * Pcurve) const;

  // Confusion results relative to EdgeCurve containing PCurve
  CATPointOnEdgeCurve * GetPointOnEdgeCurve   (const CATEdgeCurve * iECrv, const CATPCurve * Pcurve, const CATLONG32 iIndex=0) const;
  CATPointOnEdgeCurve * GetConfusionStartPoint(const CATEdgeCurve * iECrv, const CATPCurve * Pcurve =0, const CATLONG32 iIndex=0) const;
  CATPointOnEdgeCurve * GetConfusionEndPoint  (const CATEdgeCurve * iECrv, const CATPCurve * Pcurve =0, const CATLONG32 iIndex=0) const;

  // A confusion is degenerated on Edge of index iIndex if it is shorter than the resolution 
  // on this Edge and larger than the resolution on the other edge.
  CATBoolean IsConfusionDegenerated(const CATLONG32 iIndex) const;
  // @nocgmitf Not implemented
  CATEdgeCurve * GetConfusionBetweenEdgeCurves(CATPointOnEdgeCurve * & oPOECStart, 
                                               CATPointOnEdgeCurve * & oPOECEnd);

  //=======================================================================
  // Methodes obsoletes (ne plus utiliser)
  //=======================================================================
  CATPointPositionOnCurve GetPointPositionOnCurve(const CATEdgeCurve * iECrv) const;
  CATPointPositionOnCurve GetConfusionStartPositionOnCurve(const CATEdgeCurve * iECrv) const;
  CATPointPositionOnCurve GetConfusionEndPositionOnCurve(const CATEdgeCurve * iECrv) const;
  // XGN 28-04-98
  // if returned pointer is not 0, ParamMapping can be used to construct the merged-curve 
  // resulting from the confusion.
  // The returned pointer must be deleted by the caller
  CATMathSetOfPointsND * GetParamMapping();
  // Specialized method for Boolean : return 0 for classical solution,
  // return 1 when the point solution was obtained as a confusion
  // degenerated on one side as a point.
  CATBoolean GetPointSolutionType() const;

 private:
  //=======================================================================
  //- Protected Methods
  //=======================================================================

  void DefaultInitialize();

  CATLONG32 Run2();
  
  CATLONG32 RunPLinePLine();
  CATLONG32 RunPLinePLine_Segment();
  CATLONG32 RunPLinePLine_Segment(const CATCrvParam&, 
                                  const CATCrvParam&, 
                                  const CATCrvParam&, 
                                  const CATCrvParam&,
                                  const double* = NULL);

  CATLONG32 RunPLinePCircle(const int pcurve1IsAPLine);
  CATLONG32 RunPCirclePCircle();
  // Run intersection if the two curves are the same.
  // Return 1 if computation is over.
  // Return 0 if intersection still need to be computed.
  CATLONG32 RunSameTag();

  
  CATBoolean IntersectBoundingBoxes(CATLONG32 ArcStart1, CATLONG32 ArcEnd1,
                                    CATLONG32 ArcStart2, CATLONG32 ArcEnd2,
                                    const double uMin, const double uMax,
                                    const double vMin, const double vMax,
                                    const CATLONG32   WhichPCurve, const CATLONG32 NbArc2,
                                    CATLONG32 & iMin1, CATLONG32 & iMax1, CATLONG32 & iMin2, CATLONG32 & iMax2);
  CATBoolean TestPreInclusion(const double u, const double v,
                              const double * uMin, const double * uMax,
                              const double * vMin, const double * vMax,
                              const CATLONG32 iMin, const CATLONG32 iMax, const double Tolerance);

  virtual CATLONG32 IntersectArcArc(const CATMathInterval2D & Def,
                                    const CATLONG32 n1,
                                    const CATMathFunctionX * U1,
                                    const CATMathFunctionX * V1,
                                    const CATLONG32 n2,
                                    const CATMathFunctionX * U2,
                                    const CATMathFunctionX * V2,
                                    CATMathAttrList * attributes = 0);

  CATLONG32 ExtremityAndConfusion(const CATCrvParam * iStart1,
                                  const CATCrvParam * iEnd1,
                                  const CATCrvParam * iStart2,
                                  const CATCrvParam * iEnd2);

  CATLONG32 ExtremityAndConfusion(const CATSurParam & UVS1,
                                  const CATSurParam & UVE1,
                                  const CATSurParam & UVS2,
                                  const CATSurParam & UVE2);

  CATLONG32 ExtremityAndConfusion();

  void StorePointSolution(const CATCrvParam & par1,
                          const CATCrvParam & par2,
                          CATBoolean iAdjust=0);


  void StoreConfusionSolution(const CATCrvParam & Start1,
                              const CATCrvParam & End1,
                              const CATCrvParam & Start2,
                              const CATCrvParam & End2,
                              CATMathSetOfPointsND * iParamMap=0,
                              double iMaxGap=0);

  void StoreMixedSolution(const CATCrvParam & Start1,
                          const CATCrvParam & End1,
                          const CATCrvParam & Start2,
                          const CATCrvParam & End2);
  
  void StoreSpecialPoints();
  void DestroyResults();

  void TreatNoTangentialExtremitySolution(const CATPointOnEdgeCurve * iPOEC, const double iTol);

  void InitializeUVTolerance (int &IsPole, CATBoolean &UVDistorsion);
  //
  // Post treatment methods
  //
  void EliminateMultiplePoints();
  void FindConfusionBetweenZeros();
  void EliminatePointsInsideConfusion();
  void UpdateMixedSolutions();
  void AdjustCrossingSolutions();
  void ReorderMixedSolutions();
  
  //
  // Compute logical signatures and crossings
  // 
  void ComputeLogicalSignature();

  //
  // Utilities
  //
  int GetIndex(const CATEdgeCurve * iECrv, const CATPCurve * Pcurve, const CATLONG32 iIndex=0) const;
  // iTol must be scaled 
  CATPointOnEdgeCurve * ComputePointOnEdgeCurve(const CATCrvParam & iParam, int iIndex, double iTol) const;
  CATLONG32 AdjustParamOnPCrv(CATCrvParam & ioParam, int iPCrvIndex, CATCrvParam  * oNewParam=0);
  void SortPointSolutions(int iCurveIndex);

  void RemoveRedundantPoints(const CATBoolean iRemoveSpecialPoints = FALSE);
  void RemoveRedundantConfusions();
  void RemoveRedundantMixed();

  //
  // Error handling methods
  //
  void CheckIndexPoint(char * iMethod) const;
  void CheckIndexMixed (char * iMethod) const;
  void CheckIndexConfusion(char * iMethod) const;
  //
  // Check Mixed and Confusion Solutions
  //
  CATBoolean CheckMixedSolutions();
  CATBoolean CheckConfusionSolutions();
  CATBoolean IntersectSegmentSegment(const CATMathPoint2D & A0, const CATMathVector2D & D0,
                                     const CATMathPoint2D & A1, const CATMathVector2D & D1,
                                     double & ou, double & ov);
  
  //Stabilization des zones de confusion - methode en cours de conv voir avec EAB pour utilisation
  void TreatStabilizeConfusion();

  void ComputeSquareScaleSave();
  CATBoolean IsPointIncludedInPlineOnPlane(const CATSurParam & M,int iPCrvIndex,const CATSurParam & UVS,
                                           const CATSurParam & UVE,CATCrvParam & oParam);

  void SetPCurve_Init(const CATPCurve *Pcurve);

  //=======================================================================
  //- Protected Data
  //=======================================================================
  private:
  // SAVE in input of the CGMReplay
  CATSoftwareConfiguration *_Config;
  short _CGMLevel;
  const CATTolerance & _Tolerance;

  // Data about the curves.
  const CATPCurve    * _PCrv[2];
  const CATEdgeCurve * _ECrv[2];
  const CATPointOnEdgeCurve * _PoecS[2], * _PoecE[2];  // Points on curve when they exist.
  const CATPointOnEdgeCurve * _POECNoSol1, * _POECNoSol2;// Data to avoid extremities tangential solution 
  CATCrvParam _OriginalStart[2], _OriginalEnd[2];
  double     _TolExtremity;          // Tolerence for extremities.
  CATBoolean _StabilizationRequired; // Stabilization
  double     _TangentialTol;         // Tangential tolerance is 3D (defaut is 0.01*Resolution;can be set to the resolution in the Crv/Crv specifications)
  double     _TolConfusion;          // Tolerence for confusion.  ==> !!!!!! to put in replay
   
  // NotSaved
  CATCrvParam _Start[2], _End[2];
  CATCrvParam * _SameTagBackUp; // Backup for 4 CATCrvParam to be allocation only when necessary

  // Lock/Unlock of PCurves
  //   TRUE : The default is for the operator to lock/unlock pcurves. 
  //   FALSE: The caller takes responsibility for lock/unlock. take great care!
  //          Performance gain when the operator is called multiple times on a set of pcurves.
  CATBoolean _LockPCurves;

   
  // Internal constant 
  double _TangentialTol_CurvatureFactor;
  double _EliminationTol;  // Tolerance for Elimination
  double _MaxUVTol;        // Max of all tolerance, for internal use on the bounding box




  
  // Extremities of bouding boxes of arcs
  double * _uMin1, * _uMax1, * _vMin1, * _vMax1;
  double * _uMin2, * _uMax2, * _vMin2, * _vMax2;
  //
  int * _CanIntersectArcs;
  double _SquareScaleStart[2], _SquareScaleEnd[2];
  // Pointer to the param mapping
  CATMathSetOfPointsND * _SpecialPoints;

  double _TolNoSol1, _TolNoSol2;

  // en cas de multirun, tolerance precedemment calculée avec la courbe non mofifiée
  double _UVTolOnCurve1;

  //------------------------
  // - Iterators parameters for point , mixed and confusion solutions 
  //------------------------
  CATLONG32 _NbPoints, _NbAllocPoints, _IndexPoint;
  CATLONG32 _NbMixed, _NbAllocMixed, _IndexMixed;
  CATLONG32 _NbConfusions, _NbAllocConfusions, _IndexConfusion;
  //
  CATPCrvPCrvResultPoint * _PointSolStatic;
  CATPCrvPCrvResultPoint ** _PointSol;
  CATPCrvPCrvResultConfusion ** _MixedSol;
  CATPCrvPCrvResultConfusion ** _ConfusionSol;

  


  CATBoolean _SquareScaleSaved;

  // Data to avoid unuseful computation
  //la deuxieme courbe n'a pas ete pas modifiée
  CATBoolean _OptiSetPCrv_SquareScale;// _SquareScaleStart[1] et  _SquareScaleEnd[1]  a conserver
  CATBoolean _OptiSetPCrv_TolUV; //  _UVTolOnCurve1 a conserver 

//========================================================================
// Debug
//========================================================================

  GEOPDEBUG_CMD(void Debug_PrintOperatorStatus(const CATUnicodeString iPlace, const CATBoolean iDetail = FALSE) const);
  GEOPDEBUG_CMD(void Debug_PrintPointSolutions() const);
  GEOPDEBUG_CMD(void Debug_PrintMixedSolutions() const);
  GEOPDEBUG_CMD(void Debug_PrintConfusionSolutions() const);

  GEOPDEBUG_CMD(void Debug_EvalPoint(const CATCrvParam & iParam0, const CATCrvParam & iParam2) const);

//========================================================================
// Gestion CGMReplay
//========================================================================
protected:
  friend class CATGeoStreamFactory; 

  // private static data
  static CATString _OperatorId;
  static CATGeoOpTimer _Timer;

public:
  
  /** @nodoc @nocgmitf */
  const CATString * GetOperatorId();
  //-----------------------------------------------------------------------
  //- Gestion timer 
  //-----------------------------------------------------------------------  
  CATGeoOpTimer * GetTimer();

  //-----------------------------------------------------------------------
  //- Gestion Mode Record 
  //-----------------------------------------------------------------------  

  /** @nodoc @nocgmitf */
  CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  /** @nodoc @nocgmitf */
  virtual void WriteInput(CATCGMStream  & ioStream);
  /** @nodoc @nocgmitf */
  virtual void WriteOutput(CATCGMStream & ioStream);
  /** @nodoc @nocgmitf */
  virtual CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  /** @nodoc @nocgmitf */
  virtual void Dump( CATCGMOutput& os ) ;
  /** @nodoc @nocgmitf */
  virtual void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  /** @nodoc @nocgmitf */
  virtual void DumpOutput(CATCGMOutput& os);
  /** @nodoc @nocgmitf */
  virtual CATCGMOperator::CATCheckDiagnostic CheckInput(CATCGMOutput & ioStream);
  /** @nodoc @nocgmitf */
  virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & ioStream);
  
};

//-----------------------------------------------------------------------
// INLINE 
//-----------------------------------------------------------------------  

INLINE void CATIntersectionPCrvPCrv::BeginningPoint()
{ 
   _IndexPoint = -1; 
}


INLINE CATLONG32  CATIntersectionPCrvPCrv::NextPoint()
{ 
   _IndexPoint++;
   return (_IndexPoint<_NbPoints);
}

INLINE void CATIntersectionPCrvPCrv::BeginningMixedPoint()
{ 
   _IndexMixed = -1; 
}

INLINE CATLONG32  CATIntersectionPCrvPCrv::NextMixedPoint()
{ 
   _IndexMixed++;
   return (_IndexMixed<_NbMixed);
}

INLINE void CATIntersectionPCrvPCrv::BeginningConfusion()
{ 
   _IndexConfusion = -1; 
}

INLINE CATLONG32  CATIntersectionPCrvPCrv::NextConfusion()
{ 
   _IndexConfusion++;
   return (_IndexConfusion<_NbConfusions);
}

INLINE CATLONG32 CATIntersectionPCrvPCrv::GetNumberOfPoints() const
{ 
   return _NbPoints; 
}

INLINE CATLONG32 CATIntersectionPCrvPCrv::GetNumberOfMixedPoints() const
{
  return _NbMixed;
}

INLINE CATLONG32 CATIntersectionPCrvPCrv::GetNumberOfConfusions() const
{ 
  return _NbConfusions; 
}

//-----------------------------------------------------------------------
//-----------------------------------------------------------------------  


ExportedByY30C1XMM 
CATIntersectionPCrvPCrvSign CATIntersectionPCrvPCrvSignature(const CATPCurve *Pcurve1, const CATCrvParam & p1,
                                                                                const CATPCurve *Pcurve2, const CATCrvParam & p2 );

ExportedByY30C1XMM 
CATIntersectionPCrvPCrvSign CATIntersectionPCrvPCrvSignature(const CATPointOnCurve *p1, const CATPointOnCurve *p2);

ExportedByY30C1XMM 
CATIntersectionPCrvPCrvSign CATIntersectionPCrvPCrvSignature(const CATPointOnEdgeCurve *iPOEC1, const CATPCurve * iPCrv1, 
                                                             const CATPointOnEdgeCurve *iPOEC2, const CATPCurve * iPCrv2);
//V1 & V2 should be non scaled vectors, ie with Factory Scale = 1
ExportedByY30C1XMM 
CATIntersectionPCrvPCrvSign CATIntersectionPCrvPCrvSignature(const CATMathVector2D & V1, const CATMathVector2D & V2);

ExportedByY30C1XMM 
CATIntersectionPCrvPCrv* CATCreateIntersection(CATGeoFactory * Factory, CATSoftwareConfiguration *_Config,
                                               const CATPCurve *Pcurve1,
                                               const CATPCurve *Pcurve2,
                                               const CATSkillValue skill = BASIC);

ExportedByY30C1XMM 
CATIntersectionPCrvPCrv* CATCreateIntersection(CATGeoFactory * Factory, CATSoftwareConfiguration *_Config,
                                               const CATPCurve *Pcurve1, const CATCrvLimits &Limit1,
                                               const CATPCurve *Pcurve2, const CATCrvLimits &Limit2,
                                               const CATSkillValue skill = BASIC);

ExportedByY30C1XMM 
CATIntersectionPCrvPCrv* CATCreateIntersection(CATGeoFactory * Factory, CATSoftwareConfiguration *_Config,
                                               const CATPointOnEdgeCurve * iPoec1On1, const CATPointOnEdgeCurve * iPoec2On1,
                                               const CATPCurve * iPCrv1, 
                                               const CATPointOnEdgeCurve * iPoec1On2, const CATPointOnEdgeCurve * iPoec2On2,
                                               const CATPCurve * iPCrv2,
                                               const CATSkillValue skill = BASIC);

ExportedByY30C1XMM 
CATIntersectionPCrvPCrv* CATCreateIntersectionNoCheck(CATGeoFactory * Factory, CATSoftwareConfiguration *_Config,
                                                      const CATPointOnEdgeCurve * iPoec1On1, const CATPointOnEdgeCurve * iPoec2On1,
                                                      const CATPCurve * iPCrv1,
                                                      const CATPointOnEdgeCurve * iPoec1On2, const CATPointOnEdgeCurve * iPoec2On2,
                                                      const CATPCurve * iPCrv2,
                                                      const CATSkillValue skill = BASIC);

ExportedByY30C1XMM 
void Remove(CATIntersectionPCrvPCrv *& Intersection);


#endif
