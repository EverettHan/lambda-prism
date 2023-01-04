// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================
//
// CATIntersectionSurSurTg:
//   Intersection of two surfaces with two inits and "guiding PCurves". This 
//   operator decomposes the intersection into smooth and sharp subdomains and
//   uses a dedicated algorithm for each type of subdomain.
//=============================================================================
// Usage Notes:
//   The reference orientation is that of the first PCurve, so that the "Start"
//   init corresponds to the low limit of iCrvLimits1 and the "End" init
//   corresponds to the high limit of iCrvLimits1.
//   The input inits in a "sharp" region of the intersection _must_ be very
//   clean (mathematical zero of the intersection system). The inits in a
//   "smooth" region of the intersection need only be admissible (distance
//   between the two points on surface < resolution). Whether the start and end
//   extremities are sharp or smooth is determined by the operator. Use the
//   SmoothSharpStatus method to get the status of an extremity.
//   At an extremity of the intersection which is _sharp_, it is possible to not
//   specify an init: use the SetInitType method, with 0 meaning "init specified"
//   (default) and 1 meaning "init not specified". When an init is not specified,
//   the result intersection is limited by the first domain border crossed by the
//   marching algorithm.
//   The validity of the inits and init_types with respect to the previous
//   criteria is checked by the operator at the beginning of the Run. No result
//   is found if the specification of the inits and init_types is found abnormal.
//   The CheckAndReconvergeInit() utility allows the user to check whether his or
//   her input will be accepted by the operator. This utility also reconverges
//   _specified_ (type 0) inits at a _sharp_ extremity if necessary.
//   All methods with a short iStartOrEnd argument follow the convention:
//     0 = Start, 1 = End.
//   Any failure of the operator manifests as a null result edge curve.

//   25sep03- A new interface allows the specification of more than two
//   inits. The old interface is maintained but new developments should use
//   the new interface.
//   

//
//=============================================================================
//   /01/03     Creation                                                 S. Dauby
// 25/09/03     New interface to allow more than two inits
//   /03/04 STY Evolution
// 08/05/12 Q48 Update output to ResultCurve mechanism
// 11/07/12 Q48 Enhancement to allow two solutions if break in intersection
// 17/07/12 Q48 Addition of debug trace and visual info
// 08/11/12 Q48 Choose which guide PCrv to use to build bisector surface
// 01/02/13 Q48 Debug trace / check for inits
// 17/12/13 Q48 Tidy and re-factor in preparation for IR-242186
// 20/01/14 Q48 Smooth/sharp threshold for singular cases (IR-242186)
// 26/03/14 Q48 Update of tagent / curvatures in smooth domain (IR-279264)
// 27/05/14 Q48 Add debug trace flags
// 17/07/14 Q48 Add ValidateInputGuideLimits to prevent cleaner crash
// 19/08/14 Q48 Partial file tidy
// 21/01/15 Q48 Add ComputeGuideTangent
// 24/10/19 Q48 Remove interface-v1 for SetInit (made private for replays)
// 28/08/20 Q48 Add flags to indicate if curve and init tangent are not aligned
//=============================================================================

#ifndef CATIntersectionSurSurTg_h
#define CATIntersectionSurSurTg_h

// ExportedBy
#include "Y30C3XGG.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

class CATSurSurTgResultCurve;
class CATBiPCrvSmoothSharpFuncX;
class CATSurSurInterpol;

// Basic types
#include "CATDataType.h"
#include "CATBoolean.h"
#include "CATString.h"


// Mathematics
class CATSoftwareConfiguration;
class CATMathSetOfLongs;


// Advanced mathematics
class CATMathIntervalND;
class CATMathSetOfPointsND;
class CATMathSetOfPointsNDWithVectors;
class CATMathFunctionX;
class CATMathFunctionXY;


// Geometric objects
#include "CATSurParam.h"
#include "CATSurLimits.h"
#include "CATCrvLimits.h"

class CATGeoFactory;
class CATSurface;
class CATPCurve;
class CATPLine;
class CATEdgeCurve;
class CATPointOnEdgeCurve;
class CATSetOfCrvParams;
class CATSetOfPointsMapX;


// Geometric operators
class CATGeometryPack;
class CATProjectionPtCrv;
class CATInclusionPtCrv;
class CATInclusionPtPCrv;
class CATFunctionIntersectionSurSur;

// X-scale
class CATGeoODTScaleManager; // Q48 (07/2014): X-scale

// Debug
#include "CATGeoOpDebug.h"

#define CATSurSurTg_InitOK                      0x00000001
#define CATSurSurTg_InitReconverged             0x00000002
#define CATSurSurTg_UnreconvergeableSharpInit   0x00000004
#define CATSurSurTg_InitSmoothAttachedToSharp   0x00000008

class ExportedByY30C3XGG CATIntersectionSurSurTg : public CATGeoOperator
{
public:
  enum CATSurSurTgResultCurveType{ Unset = -1, EdgeCurveOutStart = 0, EdgeCurveOutEnd, EdgeCurveMain, EdgeCurveMulti1, EdgeCurveMulti2 };

  CATIntersectionSurSurTg(CATGeoFactory            * iFactory,
                          CATSoftwareConfiguration * iConfig,
                          CATSurface               * iSurface1, 
                          CATSurface               * iSurface2,
                          CATPCurve                * iPCrv1,
                          CATPCurve                * iPCrv2,
                          const CATSurLimits & iSurLimits1, 
                          const CATSurLimits & iSurLimits2,
                          const CATCrvLimits & iCrvLimits1,
                          const CATCrvLimits & iCrvLimits2,
                          short iOriPC2vsPC1);

  ~CATIntersectionSurSurTg();


  // ------------------------
  // -- Init input methods --
  // ------------------------

  // The next methods make up the old init specification interface. Please use the
  // new interface in new developments.
  // -----------------------------------------------------------------------------

  // OLD INTERFACE (v0)
  // ------------------

  // iType: 0 = init specified (default)
  //        1 = init not specified (the result intersection will be limited by the domain)
  
  void SetInitType(short iStartOrEnd, short iType);
  void SetInit(short iStartOrEnd, const CATSurParam & iSurParam1, const CATSurParam & iSurParam2);
  void SetReconverge(const CATBoolean iReconverge);

  // the returned value is composed of the following CATSurSurTg_InitXXX bitwise-or'ed:
  //   CATSurSurTg_InitOK          : the operator will accept the init
  //   CATSurSurTg_InitReconverged : the init was reconverged (you must pass the reconverged init
  //                                 to the operator)
  //   CATSurSurTg_UnreconvergeableSharpInit :
  //                                 the init is seen as sharp, has a wide gap, and can't be reconverged
  // in case of init_type 1, the two SurParams are meaningless
  
  CATLONG32 CheckAndReconvergeInit(short iStartOrEnd, short iType, CATSurParam& ioSurParam1, CATSurParam& ioSurParam2);

  // END OF OLD INTERFACE (v0)
  // -------------------------

  // OLD INTERFACE (v1)
  // ------------------

private:

  // Q48 18/10/19:
  //   Removed from public interface (SSWI code flow meant it was never called)
  //   Made private to preserve loading of old CGMReplays

  // iguide_pos: specifies the position of the init with respect to the guides; 0 = start, 1 = end,
  //             -1 = unspecified; if an end of the guides is smooth (see the SmoothSharpStatus method),
  //             then there must be exactly one init attached to it with iguide_pos
  // the return value is the index assigned to the init
  short SetInit(const CATSurParam & iSurParam1, const CATSurParam & iSurParam2, short iguide_pos);

  // END OF OLD INTERFACE (v1)
  // -------------------------

public:

  // NEW INTERFACE (v2)
  // ------------------

  // type = -1 point start de l'extremite des pcurves guide
  // type =  1 point end de l'extremite des pcurve guide 
  // type = -2 point out du cote start des pcurves guide
  // type =  2 point out du cote end des pcurve guie  
  // type =  0 dans le cas ou l'utilisateur veut fournir des inits interieurs qui seraient eventuellement des points de singularite    
  // l'utilistateur doit fournir les SetOfCrvParam1 et SetOfCrvParam2 ce cas correspond aux valeurs -1,0,1 de paramtre Type
  //
  short SetInit(const CATSurParam & iSurParam1,
                const CATSurParam & iSurParam2,
                const short         iGuidePos,
                const short         iCleverGuidePos,
                const CATCrvParam & iCrvParam1,
                const CATCrvParam & iCrvParam2);

  // checks that an init can be accepted by SetInit; in sharp regions, the init is reconverged; it's the
  // reconverged init you must pass to SetInit.
  // the return value is composed as in the old interface
  CATLONG32 CheckAndReconvergeInit(      CATSurParam & ioSurParam1, 
                                         CATSurParam & ioSurParam2, 
                                   const short         iGuide_pos, 
                                   const short         iArtificialinits = 0);

  // END OF NEW INTERFACE (v2)
  // -------------------------

public:

  // ------------------------
  // -- Init query methods --
  // ------------------------

  // 0 = smooth, 1 = sharp
  short SmoothSharpStatus(const short iStartOrEnd) const;
  short SmoothSharpStatus(const short iStartOrEnd, double & oVal) const;


  // ------------------------
  // -- Set option methods --
  // ------------------------

  // user-adjustable maximum diametre of the inits
  void SetInputTol(const double iTol);

  // user-adjustable maximum quality of the edge curve see deformation in run singular //RI A0479853  we qaloow a gap more than input tol in the smooth area, but just _inputtolin the cross of inits
  void SetQualityTol(const double iQualityTol);

  // adjustable smooth-sharp threshold - DO NOT USE
  void SetThreshold(const double iThreshold);
  
  // 0: relimit the result curve by the domain borders (default)
  // 1: relimit the result curve by the inits (a la SetOnlyBetweenInits of CATIntersectionSurSurWithInits)
  void SetRelimitMode(const short iRelimitMode);

  // Do Not Use mode dedie a DPS pour couper dans la zone smooth out 
  void SetRespectShapeOut(const CATBoolean iRespectShapeOut);

  // user-Allowe to extrapolate the surfaces to ensure that the surfaces overlap each others.
  void SetExtrapolation(const CATBoolean iExtrapoleAllowed);
  void SetExtrapolationValue(const double iValue);

  //user Ca reset Checking Ovelapping Surface Be careful In this case you should ensure that surafce opverlapp, to have a stable behaviour 
  //and want to increase performance //
  void SetCheckSurfsOverlap(const CATBoolean CheckSurfsOverlap = TRUE);

  // Set the indices of any articifical inits
  void SetArtificialIndices(const short[]);

  // obh renvoie la distance max de reconvergence des inits sharp
  // utile pour les operateurs qui check l'inclusion des inits par rapport au resultats a un inputtol donne
  //double GetDistanceReconvSharpInit() const;
  
  //obh do not use this option 
  //void SetUpdateBoxes(); // Q48 16/10/19: only called internally --> make private

  // ---------------------------
  // -- Result output methods --
  // ---------------------------

  // Q48, 08/05/12: modified to use new ResultCurve mechanism
  // --------------------------------------------------------

  // Access to the individual bits of output data of SurSurTg is removed. Use NextEdge() and
  // GetResultCurve() instead. The ResultCurve has access functions to get the output data, in
  // keeping with the other SurSur intersectors
  //   - Note: GetResultCurve assumes the user takes ownership of the object unless explicitly called
  //           with FALSE option.

  CATBoolean HasPossibleSolution() const;

  void GetAllInitsCrossed(CATMathSetOfLongs & oInitsCrossed,
                          CATMathSetOfLongs & oInitsNonAlignedTgt) const;

  // Reset the pointers to the beginning of the array (positon -1)
  //   - Note: you must call NextEdge() before GetResultCurve()

  void BeginningEdge();

  // Move the pointers to the next curve solution. 
  //   - Note: this creates the CATSurSurTgResultCurve if it doesn't already exist

  CATBoolean NextEdge();

  CATSurSurTgResultCurve* GetResultCurve(const CATBoolean iTakeOwnership = TRUE);


  // ++++++++++++++++
  // ++ Do not use ++
  // ++++++++++++++++

  // This function is maintained for backward compatibility with CATBlendRibHermetizationUtilities.cpp
  // Use GetResultCurve() instead if possible.
  
  CATEdgeCurve* GetEdgeCurve(CATPointOnEdgeCurve *&, CATPointOnEdgeCurve *&);

  void MayTryAgain(CATBoolean);
 

  GEOPDEBUG_CMD(CATLONG32 GetOperatorDepth() const);
  GEOPDEBUG_CMD(void SetOperatorDepth(const CATLONG32));

  class SubDomainResultData
  {
  public:

    SubDomainResultData();
    ~SubDomainResultData();

    void CopyData(const SubDomainResultData&);

    short      processed;
    short      processedInDirection;
    CATBoolean processedToBoundary;

    CATMathSetOfPointsND* localPar;
    CATMathSetOfPointsND* localPt;
    CATMathSetOfPointsND* localTg;
    CATMathSetOfPointsND* localSd;

    // Store the info as we process the sub-domains
    CATMathSetOfLongs* localInitsCrossed;
    CATMathSetOfPointsNDWithVectors* localMarchingSolPoints;
    
    // Debug
    GEOPDEBUG_CMD(void Debug_PrintStatus(short) const)

  private:
    void Clear(); // Note: easy to cause memory leaks with this
  };

  class SubDomain
  {
  public:
   
    SubDomain();
    ~SubDomain();

    void Clear(); // Note: easy to cause memory leaks with this
    void CopyData(const SubDomain&);

    short sharp;   // 0 = smooth, 1 = sharp
    double a[2];   // entre 0. et 1. delimite le sous-domaine selon _GuidePCrv[0]
    double uvrs[8];   // les inits d'intersection pour le sous-domaine
    short open_ended[2]; // 0 = init specifiee, 1 = init non-specifiee (limitation par le domaine)
    short out; //0 si c'est a l'inetrieur , out start -1, out end +1
    double a_singular;//entre 0. et 1. situe le point singulier selon le sous-domaine selon _GuidePCrv[0]
    
    short endPointsToProcess[2]; // 0: no end point, 1: end point to process, 2: end point processed

    SubDomainResultData localResultData[2];

    // Debug
    GEOPDEBUG_CMD(void Debug_PrintStatus(const short iIndex) const);
  };

private :

  int RunOperator();

  void Initialize();
  void InitializeSmoothSharpFunction();

  void CleanUp();
  void ClearGeometry();
  void ClearCurveSolutions();

  void UpgradeToNewStyleInits();
  void ComputeTol();
  CATLONG32 ValidateInput();
  
  CATLONG32 SmoothSharpDecomposition();
  void ComputeGuideTangent(const double, CATMathVector2D[]) const;

  CATLONG32 ProcessSharpSubDomains();
  CATLONG32 ProcessSmoothSubDomains();
  CATLONG32 CreateFinalResult();
  
  CATLONG32 CreateOutResults();
  CATLONG32 CreateOutResults(CATPCurve *PCrv[2], CATLONG32 i);  

  void CreateResultCurves();
  CATLONG32 GetNumberOfEdges() const;

  void StoreEdgeSolution(CATSurSurTgResultCurve* iCurveSol);
  void CheckIndexEdge(char* method) const;

  // si on renvoie la valeur 0 
    //on continue la run
  // si on renvoie la valeur 1
  //decoupe et rappel au sursurtg en interne 
  short CheckForSingularInits() const;
  CATLONG32 CutOnSingularities ();  
  
  short Reconverge(double ioUVRS[]) const;

  void SetUpdateBoxes(); // Q48 16/10/19: only called internally --> made private

public: // CPT : sinon compil KO SunOS
  // Init Classification
  // -------------------

  enum InitOnGuideType{ Unknown = 0,
                        NotOnGuide,
                        OnGuide,
                        OutsideLimits,
                        StartOrEnd,
                        StartOrEndOut,
                        OutDomain
  };

  enum InitProcessedAsType{ NotProc = 0,
                            ProcUnknown,
                            ProcStartOrEnd,
                            ProcStartOrEndOut,
                            ProcProjectedInit,
                            ProcSharpMarched,
                            ProcSingularSurSurTg
  };

  class InitClassification
  {
  public:
    InitClassification();
    ~InitClassification();

    short _Sharp; // default -1, smooth = 0, sharp = 1
    CATBoolean _Processed;

    CATBoolean _DetectedNonAligendTangent;

    InitOnGuideType _TypeOnGuide;
    InitProcessedAsType _ProcessedAs;

    CATBoolean _Singular;
    CATBoolean _Artificial;

    // Debug
    GEOPDEBUG_CMD(CATUnicodeString Debug_StringFromSharp() const)
    GEOPDEBUG_CMD(CATUnicodeString Debug_StringFromSharp(const short) const)

    GEOPDEBUG_CMD(CATUnicodeString Debug_StringFromGuideType() const)
    GEOPDEBUG_CMD(CATUnicodeString Debug_StringFromGuideType(const InitOnGuideType) const)

    GEOPDEBUG_CMD(CATUnicodeString Debug_StringFromProcessedType() const)
    GEOPDEBUG_CMD(CATUnicodeString Debug_StringFromProcessedType(const InitProcessedAsType) const)
  };

private:

  CATBoolean IsAnInitAtStartOfGuide() const;
  CATBoolean IsAnInitAtEndOfGuide() const;

  CATBoolean IsAnInitAtStartOfGuide(short & oInitIndex) const;
  CATBoolean IsAnInitAtEndOfGuide(short & oInitIndex) const;
  
  CATBoolean FindInitWithGuidePos(const short   iGuidePos, 
                                        short & oInitIndex) const;

  CATLONG32 ClassifyInitsOnGuide();

  CATBoolean TestInclusionOfInitOnCurve(      CATInclusionPtCrv *, 
                                        const short, 
                                        const CATBoolean, 
                                              double            &, 
                                              CATCrvParam       &, 
                                              short               iSurfIndex = 2);
  
  CATBoolean TestInclusionOfInitOnCurve(      CATInclusionPtPCrv * iInclusionOp[], 
                                        const short                iInitIndex,
                                        const short                iRefCurveIndex,
                                              double            &  oMinDist, 
                                              CATCrvParam       &  oCrvParam);
  
  void UpdateInitClassification(      CATMathSetOfLongs * iInitsCrossed,
                                const InitProcessedAsType iUpdateType = ProcUnknown);
  
  void UpdateInitClassification(const CATLONG32           iInitIndex, 
                                const InitProcessedAsType iUpdateType = ProcUnknown);

  void UpdateInitClassificationExtremity(const short      iInitIndex,
                                         const CATBoolean iStart);

  void InsertCrvParam(short, const CATCrvParam&, CATSetOfCrvParams*) const;

  void AddSubDomain(short sharp,double a0,double a1,
                    double uvrs0[4],double uvrs1[4],
                    short open_ended[2]);
  
  CATLONG32 ProcessIntersection();
  CATLONG32 ReProcessIntersection();

  CATLONG32 ProcessSharpSubDomain (const short i);
  CATLONG32 ProcessSmoothSubDomain(const short i);

  CATBoolean ComputeTangentAtFreeEnd(const double[], const double[], double[]) const;


  void ComputeAdequateDomains();
  void Debug(CATCGMOutput & os);
  void DebugBeforeRun(CATCGMOutput & os);
  void InsertAritificatInits();
  
  CATLONG32 PointBorder(      short    dim, 
                        const double * x, 
                        const double * dom, 
                              double   tol);
  
  CATLONG32 ValidateInit(short         i, 
                         short         InitType,
                    CATSurParam * SurParam,
                    short withReconv,
                    CATLONG32 & diag);

  CATLONG32 ValidateNewStyleInit(      CATSurParam    ioSurParam[2], 
                                 const short          iGuide_pos,
                                 const CATBoolean     iWithReconv,
                                       CATLONG32    & oDiag,
                                 const short          iArtificialinits = 0);

  double ComputeInitSizeSq(const double iInit[]) const;

  double ComputeInitSizeSq(const short         iGuideIndex,
                           const CATSurParam & iInitSurPar, 
                           const CATCrvParam & iInitCrvPar) const;

  CATLONG32 ProcessSingleSmoothSubDomain();

  CATBoolean FindInitParamOnBSurf(const CATMathPoint & iMathPoint, 
                                        CATSurface   * iSurf, 
                                  const CATSurLimits & iSurfLim,
                                  const double         iTol,
                                        CATSurParam  & oParamOnSurf) const;

  CATSurface* CreateBisectorSurf(CATSurParam & oStartOnBSurf, 
                                 CATSurParam & oEndOnBSurf,
                                 CATBoolean  & oInvertedDirBSurf);

  void IntersectBisectorSurf(       CATSurface * iBSurf, 
                             const CATSurParam & iStartOnBSurf,
                             const CATSurParam & iEndOnBSurf,
                             const CATBoolean    iInvertedDirBSurf);

  CATBoolean EnlargeDomainIfNeeded(      CATMathIntervalND & ioLocalDomain,
                                   const double              iInit[4],
                                   const double              iInit_tg[8],
                                   const int                 iSurfaceIndex);

  CATBoolean ExtrapolateSurface(      CATSurface  & iSurf, 
                                const CATSurParam & iParamToReach);

  CATBoolean CheckIfExtrapolationNeeded(const CATMathSetOfPointsNDWithVectors & iPoints,
                                        const int                               iSurfaceIndex);

  void MergePCurves();
  CATLONG32 ForceSingleSmoothSubDomain();
  CATLONG32 ReconvergeAlongBorder(double uvrs[4]);
  CATLONG32 ReconvergeSmoothSharpFrontier(double uvrs[4]);
  void RelaxSmoothSubDomains();

  short SmoothSharpStatus(const double) const;
  short TestSmoothSharpStatus(const double) const;

  short TgRefOrientation(const double   iRefA,
                         const double * iTgt) const;
  
  CATLONG32 Relax_DotProds(const short  iStartEnd, 
                           const double iDomainA, 
                           const double iPt0[], 
                           const double iPt1[], 
                                 double oDotProd[]);
  
  CATLONG32 MarchThroughInits(const short                  i, 
                              const short                  dir, 
                              const double               * init, 
                              const double               * init_tg,
                              const short open_ended, 
                              const CATMathSetOfPointsND & FirstClassEndPoints, 
                              const CATMathSetOfPointsND & SecondClassEndPoints, 
                              const CATMathSetOfLongs & SecondClassEndPointsIndices);

  CATLONG32 Interpol(SubDomain & subd);

  CATLONG32 FindIndex(const CATMathSetOfPointsND & Set, 
                      const double               * pt, 
                            double                 tol);
  
  void CheckStartAndEndInitsCrossed(const short, CATLONG32&, CATLONG32&) const;
  void FindStartAndEndInits(const short, CATLONG32&, CATLONG32&) const;
  void AdjustInitsCrossed(const short i);
  
  CATLONG32 ValidateInput1();
  CATLONG32 ValidateInput2();
  CATBoolean ValidateInputGuideLimits();
  CATBoolean ValidateInputGuideCurveMapping() const;
  CATBoolean ValidateInputGuideCurveExtremities() const;
  CATBoolean ConstructGuideMapping();

  void UpdateGuideLimitData(const CATBoolean  iHasUpdatedLimits[],
                            const CATCrvParam iUpdatedLimits[]);

  void UpdateInputGuideLimits_Inits();
  void UpdateInputGuideLimits_Consistency();

  void IncreaseSmoothSharpTol();

  CATLONG32 ValidateOutDomaine();

  CATLONG32 ConstructOutDomaineGuides();
  CATLONG32 ConstructSmoothSharpFunction();
  void AddOutSubDomaines(short i);
  
  CATLONG32 ProcessSharpSubDomain1(const short i);
  CATLONG32 ProcessSharpSubDomain2(const short i);

  short SmoothSharpStatus(const double      iPt4D[]    , const double iThreshold = -1.0) const;
  short SmoothSharpStatus(const CATSurParam iSurParam[], const double iThreshold = -1.0) const;

  short CheckNoInternalSmoothSubDomains() const;
  short CheckConsistency();
  short InsertSingularPoint();
  CATLONG32 ValidateSharpSmoothOutDomain();
  CATLONG32 ReconvergeSmoothInit(CATSurParam SurParam[2], CATLONG32 & diag, double & FX2 );  

  CATLONG32 ProcessCutCrvparam();
  CATBoolean IsSingularInitASaddlePoint(const CATLONG32, double &);
  void ComputeThresholdAroundSingularInit(const short, const double[], double &);
  CATBoolean VerifyThresholdForEndInitSignatures(const CATBoolean, const CATBoolean, double &);

  // Renvoie l'ensemble de crvparam correspondant aux init-exit poses sur la 
  // courbe consideree, dans l'ordre initialement donne par SetStartingPoints.
  void GetExitPoints(CATSetOfCrvParams *&SetOfExitParams) ;

   // Renvoie le crvparam correspondant a l'init-exit numero ExitNumero 
  void GetExitPoint(CATLONG32 ExitNumero, CATCrvParam &ExitParam) ;

  void FillSecondClassEndPoints(short, CATMathSetOfPointsND&, CATMathSetOfLongs&) const;

  CATBoolean PrepareDataForMarching(const CATLONG32              iSubDomainIndex,
                                          short                & oDir,
                                          CATMathSetOfPointsND & FirstClassEndPoints,
                                          CATMathSetOfPointsND & SecondClassEndPoints,
                                          CATMathSetOfLongs    & SecondClassEndPointsIndices, 
                                          CATLONG32            & extrapol, 
                                          short                & open_ended, 
                                          double                 init[],
                                          double                 init_tg[]);

  void GetInitsCrossedList(CATMathSetOfLongs&);
  void AddInitToResult(const short, const CATCrvParam, CATSetOfCrvParams*, CATMathSetOfLongs*);

  void UpdateBoxes();

  // from low crvparam to high crvparam on the first curve
  void SortSingularInits();
  
  void MarchingInteractiveDebug (const CATMathSetOfPointsND * iPoints,
                                       CATSurface           * Surf1, 
                                       CATSurface           * Surf2, 
                                       CATLONG32              M = 0) const;

  CATBoolean GetResultCurveData(CATLONG32, 
                                CATEdgeCurve**&, 
                                CATPointOnEdgeCurve**&,
                                CATPointOnEdgeCurve**&, 
                                CATPCurve**&, 
                                CATPCurve**&,
                                CATMathSetOfLongs**&);

  CATLONG32 CreateResultCurve();
  CATLONG32 CheckInclusionInRefCurve(const CATMathSetOfLongs&, const CATEdgeCurve*, const CATCrvLimits&, CATSetOfCrvParams&) const;

  // Methods for accessing particular result curves (eg related to the "main edge" curve). These are useful
  // in the CGM-replay functions which must read / write objects in a particular order.

  CATSurSurTgResultCurve* GetResultCurve(short, const CATSurSurTgResultCurveType&, CATLONG32* ioIndexEdge = NULL);
  CATSurSurTgResultCurve* GetResultCurve_MainEdge        (CATLONG32* ioIndexEdge = NULL);
  CATSurSurTgResultCurve* GetResultCurve_MainEdgeMulti1  (CATLONG32* ioIndexEdge = NULL);
  CATSurSurTgResultCurve* GetResultCurve_MainEdgeMulti2  (CATLONG32* ioIndexEdge = NULL);
  CATSurSurTgResultCurve* GetResultCurve_MainEdgeOutStart(CATLONG32* ioIndexEdge = NULL);
  CATSurSurTgResultCurve* GetResultCurve_MainEdgeOutEnd  (CATLONG32* ioIndexEdge = NULL);

  CATBoolean AreThereInitsRemainingToProcess(short) const;
  CATBoolean FindInitIndexAtSmoothEnd(const short, CATLONG32&) const;
  CATBoolean TestSufficientInitsForReprocessing(short) const;

  // Debug
  // -----

  GEOPDEBUG_CMD(CATLONG32 _OperatorDepth);
  GEOPDEBUG_CMD(CATBoolean _SmoothSharpConvergenceFailed);
  GEOPDEBUG_CMD(CATUnicodeString Debug_StringFromEdgeCurveType(const CATSurSurTgResultCurveType) const);

  GEOPDEBUG_CMD(void Debug_PrintInitClassification() const);
  GEOPDEBUG_CMD(void Debug_PrintInitTypes() const);

  GEOPDEBUG_CMD(void Debug_CheckBisectorSurfDirection() const);
  GEOPDEBUG_CMD(void Debug_CheckInits() const);
  
  GEOPDEBUG_CMD(void Debug_CheckPoints(const CATMathSetOfPointsND&, CATSurface*, CATSurface*, const CATUnicodeString&) const);

  GEOPDEBUG_CMD(void Debug_CheckExitCrvParam(CATSurSurTgResultCurve*, const CATLONG32, const CATCrvParam&) const);

  GEOPDEBUG_CMD(void Debug_CheckGuideCurves() const);
  GEOPDEBUG_CMD(void Debug_CheckMarchedCurves() const);
  GEOPDEBUG_CMD(void Debug_CheckEdgeQuality() const);

  GEOPDEBUG_CMD(void Debug_CheckPCurves(CATPCurve*, CATPCurve*, const CATCrvLimits&, const CATCrvLimits&) const);
  GEOPDEBUG_CMD(void Debug_CheckCurveSeparation(CATPCurve*, CATPCurve*, const CATCrvLimits&, const CATCrvLimits&) const);
  GEOPDEBUG_CMD(void Debug_CheckCurveParameterisation(CATPCurve*, CATPCurve*, const CATCrvLimits&, const CATCrvLimits&) const);

  GEOPDEBUG_CMD(void Debug_VerifySmoothSharpSolve(const CATLONG32 iNumSolverRoots) const);

  GEOPDEBUG_CMD(short Debug_HaveSingularInitSaddlePoint());
  GEOPDEBUG_CMD(void Debug_ComputeThreshold(const double[], const double[], const double[], const CATBoolean iSet = FALSE));
  GEOPDEBUG_CMD(void Debug_PrintMarchedPoints(const CATMathSetOfPointsND&) const);

  GEOPDEBUG_CMD(void Debug_PrintOperatorStatus() const);
  GEOPDEBUG_CMD(void Debug_PrintInitData() const);
  GEOPDEBUG_CMD(void Debug_PrintSubDomains() const);
  GEOPDEBUG_CMD(void Debug_PrintEdgeCurve(const CATEdgeCurve*) const);

  // ----------------
  // -- Local data --
  // ----------------

  // Input
  // -----

  CATSoftwareConfiguration * _Config;
  CATSurface * _Surf[2];
  CATSurLimits _SurLim[2];
  
  CATPCurve * _GuidePCrv[2]; // Note: these are still owned by the user and are not deleted here

  CATPLine * _GuidePCrvOutStart[2];
  CATPLine * _GuidePCrvOutEnd[2];
  
  CATCrvLimits _GuidePCrvLim[2]; // for working data (general method)

  short _OriPC2vsPC1;

  // Options
  // -------

  double _input_tol;
  double _quality_tol;
  double _input_threshold;
  CATBoolean _RespectShapeOut;
  CATBoolean _Reconverge;
  short _relimit_mode; // 0 = by domain, 1 = by inits, 2 = by inits externally, by domain internally
  
  short _inits_style; // 0 = old style, 1 = new style 2= newstyle with cleverpos
  
  // old style inits
  // ---------------

  short _InitType[2];
  CATSurParam _StartSurParam[2];
  CATSurParam _EndSurParam[2];

  // new style inits
  // ---------------

  CATSurParam * _Inits[2];
  CATCrvParam * _InitCrvParams1;
  CATCrvParam * _InitCrvParams2;
  short * _guide_pos;
  short * _clever_pos;
  short _nbInits;
  short _maxInits;
  short _ArtificalInitIndices[2]; // There can only be a maximum of two

  InitClassification* _InitClassificationOnGuide;

  // Ouput data
  // ----------

  CATLONG32 _ResultCurveGenerated[4];
  
  CATEdgeCurve * _ECrv;
  CATEdgeCurve * _ECrvOut[2];
  CATPCurve * _PCrv[2];

  CATPointOnEdgeCurve * _StartPOEC;
  CATPointOnEdgeCurve * _EndPOEC;
  CATPointOnEdgeCurve * _StartPOECOut[2];
  CATPointOnEdgeCurve * _EndPOECOut[2];
  CATMathSetOfLongs * _InitsCrossed; 
  CATMathSetOfLongs * _InitsCrossedOut[2];  
  
  // Pt[icoord =0] donne l'index du point singulier
  CATMathSetOfPointsND *  _SingularInitsOrder;
  CATSetOfCrvParams *_SetOfParamExit;
  
  // For curve solutions
  // -------------------

  CATLONG32 _NbEdges,_NbAllocEdges;
  CATLONG32 _IndexEdge;
  CATSurSurTgResultCurve **  _EdgeSol;
  CATBoolean* _EdgeSolOwned;

  // Other
  // -----

  double _Threshold; // threshold for smooth / sharp decomposition

  const CATMathFunctionX * _GPCEq[4];
  const CATMathFunctionXY * _SurfEq[6];
  
  CATBiPCrvSmoothSharpFuncX * _SmoothSharpFunc;
  CATSetOfPointsMapX        * _SmoothSharpMapping;

  CATBiPCrvSmoothSharpFuncX * _SmoothSharpFuncOut[2];
  double _extremities[4];
  double _tol;
  double _sharpangle;
  CATSurParam _BStart[2];
  CATSurParam _BEnd[2];

  CATFunctionIntersectionSurSur * _ImplicitSystem; // change to CATFunctionIntersectionSurSur ??
  CATSurSurInterpol * _Interpol;
  CATMathIntervalND * _Domain;

  CATMathSetOfPointsND * _SubDomainRoots;
  SubDomain * _SubDomains;
  SubDomain * _SubDomainsOut[2];
  short _nbSubDomains;  
  //short _nbSubDomainsIn;
  short _maxSubDomains;

  CATBoolean _dirty;
  CATBoolean _singular;
  short _out[2]; 
  short _cut_out[2];  

  CATBoolean _ExtrapolationAllowed;
  CATBoolean _CheckSurfsOverlap;
  double _ExtrapolationValue;
  CATBoolean _UpdateBoxes;
  double  _DistanceReconvSharpInit;

  // Flags and working data for processing intersections with a break
  // ----------------------------------------------------------------

  CATBoolean _MayTryAgain; // main flag controlling whether to allow multiple intersection curves

  short _Attempt; 
  // 0: 1st attempt --> try to process forwards
  // 1: 2nd attempt --> try to process backwards

  short _TryAgain; // determines the type of re-processing (see enum)

  enum TryAgainFlag{ NoReTry = 0, InwardsOnly, InwardsAndOutwards };
  // NoReTry:            no need to try again
  // InwardsOnly:        march backwards from sub-domain boundary (simple reversal of direction)
  // InwardsAndOutwards: march in both directions from the sub-domain boundary and concatenate results

  CATLONG32 _DomainStopIndex;

  // ---------------------
  // CGMReplay integration
  // ---------------------
  
private:

  // Cannot be const because C++11 not available on all platforms
  CATCrvLimits _GuidePCrvLimInput[2]; // as given by the user (do not change)

protected:
  
  friend class CATGeoStreamFactory; 
  static CATString _OperatorId;

public:

	const CATString * GetOperatorId();
  CATExtCGMReplay *IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  
  virtual void ReadInput(      CATCGMStream          & ioStream,
                         const int                     iVersionOfStream,
                               CATGeoODTScaleManager * iScaleManager,
                         const short                   iInitType[],
                         const CATSurParam             iStartSurParam[],
                         const CATSurParam             iEndSurParam[]);

  virtual void WriteInput(CATCGMStream  & os);
  virtual void WriteOutput(CATCGMStream & os);
	virtual CATBoolean ValidateOutput(CATCGMStream& ioStream, CATCGMOutput & os,int VersionNumber=1);
  virtual void Dump( CATCGMOutput& os ) ;
  virtual void DumpOutput(CATCGMOutput & os);
  virtual void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  virtual void DumpOutput(CATEdgeCurve*, CATPointOnEdgeCurve*, CATPointOnEdgeCurve*, const CATMathSetOfLongs&, CATCGMOutput&);
  virtual void DumpOutput(CATSurSurTgResultCurve*, CATCGMOutput&);
  
  virtual CATCheckDiagnostic CheckInput(CATCGMOutput & os) CATGEOOverride;
  virtual CATCheckDiagnostic CheckOutput(CATCGMOutput & os) CATGEOOverride;


  static CATGeoODTScaleManager* ReadStreamHeaderInfo(      CATCGMStream              & ioStream,
                                                     const short                       iVersionOfStream,
                                                           CATGeoFactory            *& oFactory,
                                                           CATSurface               *& oSurf1,
                                                           CATSurface               *& oSurf2,
                                                           CATPCurve                *& oGuideCurve1,
                                                           CATPCurve                *& oGuideCurve2);
    
private:
  void FillNewPackAndOldInitsCrossed(CATCGMStream      &  Str,
                                     int                  VersionNumber,
                                     CATBoolean           hasResult[3], 
                                     CATLONG32            NbEdges, 
                                     CATGeometryPack   *  oPack, 
                                     CATMathSetOfLongs ** InitsCrossed);

  void ReadOutput(CATCGMStream           & Str, 
                  CATEdgeCurve          *& ec, 
                  CATPCurve             *& pc0, 
                  CATPCurve             *& pc1,
                  CATPointOnEdgeCurve   *& startpoec, 
                  CATPointOnEdgeCurve   *& endpoec,
                  CATMathSetOfLongs      & initscrossed,
                  short                    VersionOfStream,
                  CATGeoODTScaleManager *  iScaleManager,
                  CATBoolean               streampcurves = TRUE);

  void WriteOutputEdge(CATCGMStream&, 
                       CATGeometryPack*, 
                       CATSurSurTgResultCurve*, 
                       CATBoolean iPCrv = FALSE);

  void WriteOutputEdge(CATGeometryPack*, 
                       CATSurSurTgResultCurve*, 
                       CATBoolean iPCrv = FALSE);

  void ReadInitsCrossed(CATCGMStream&, 
                        CATMathSetOfLongs*&);
};

#endif
