//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CATConnectComputer:
//
//  CATConnectCompute includes ;
//          constant radius fillet, 
//          variable radius fillet, 
//          edge-surface fillet,
//          curve-surface fillet
//          chamfer solution computations
//          tri-tangent fillet
//
//=============================================================================
// Usage notes:
//=============================================================================
// Feb 98
// 11/03/14 : XMH : Creation of CATConnectUtilities class
// 27/03/18 : SMT1 : Add _MaxDomain as a member variable to avoid it going out of scope 
//                   when the systemis handed over to the cutter
// 13/11/19 : NLD  : General reindent and alignment
// 22/04/21 : SME31 :  Update CATConnectInitData usage to handle multiple solutions - Implement GetNumberOfResults
//=============================================================================
#ifndef CATConnectComputer_h
#define CATConnectComputer_h

#include "Connect.h"
#include "CATCGMVirtual.h"

#include "CATMathIntervalND.h"
#include "CATMathSetOfPointsNDWithVectors.h"

#include "CATTolerance.h"
#include "CATIntersectionSign.h"
#include "CATListOfCATSurfaces.h"
#include "CATListOfCATSurParams.h"
#include "CATCrvLimits.h"
#include "CATICGMObject.h"

#include "CATConnectUtilities.h"
#include "CATSysMacros.h"


class CATGeoFactory;
class CATGeometry;
class CATSurface;
class CATCurve;
class CATPCurve;
class CATCrvParam;
class CATCrvLimits;
class CATEdgeCurve;
class CATPointOnEdgeCurve;

class CATMathSetOfPointsND;
class CATMathImplicitSystem;

class CATConnectTool;
class CATConnectSupport;
class CATSoftwareConfiguration;
class CATCGMStream;



#define   FactorizeDestroyResults
#define   FactorizeGetStartAndEndDiagnostic

//-----------------------------------------------------------------------------
class ExportedByConnect CATConnectComputer  : public CATCGMVirtual
   {

   public:
                                            CATConnectComputer(      CATGeoFactory            * iFactory   ,
                                                                     CATSoftwareConfiguration * iConfig    ,
                                                               const CATLONG32                  iDimension ,
                                                                     CATMathSetOfPointsND     * iInputInit = NULL,
                                                                     CATConnectTool           * iTool      = NULL);
      virtual                              ~CATConnectComputer();

      virtual       int                     Run() =0;

                    void                    SetPointingPoint(const double * iPointingPoint);

                    void                    SetPreviousSupportDimensionTable(const CATLONG32 *iTable);

      // dad (05/14/01) to know the direction in the report init
      virtual       void                    SetInitSignature(const CATLONG32 iSignature = 0);

      //PKC 01/2005
                    void                    SetOnlyInitHomotopic();

              const CATConnectUtilities   * GetConnectUtilities() const;
                    void                    SetSoftwareConfiguration(CATSoftwareConfiguration * iConfig);

                    CATLONG32               GetNumberOfSolutions() const;
                    void                    GetStartAndEndDiagnostic(CATLONG32 & oStartDiag, CATLONG32 & oEndDiag) const; 
                    void                    Beginning        ();
                    CATLONG32               Next             ();
      virtual       CATMathSetOfPointsNDWithVectors * GetResult() const;
      virtual       CATLONG32               GetInitIndex     () const;
      virtual       CATLONG32               GetConfiguration () const;

                    CATMathImplicitSystem * GetImplicitSystem() const;
              const CATMathIntervalND     * GetDomain        () const;
      virtual const CATMathIntervalND     * GetExactDomain   () const;
                    CATLONG32               GetCDimension    () const {return _Dimension;}

      virtual       CATMathSetOfLongs     * GetPointsToKeep() const;

      virtual       CATBoolean              ReportInit(const CATGeometry  * iReportGeometry,
                                                       const CATLONG32      iReportID,
                                                             double       * ioInitPoint,
                                                             double       & ioInitParam,
                                                             CATBoolean   & oSmallDeformation,
                                                       const CATCrvLimits * iReportGeometryLimits) ;


      virtual       CATBoolean              CheckResult(CATMathSetOfPointsND * set);

      // FCX 2.2003
      virtual       CATMathSetOfPointsND  * GetNaturalPointingPoints() const;

      // FCX 12.2004
      //    iInitType = 0 -> all
      //              = 1 -> only init computed by homotopy
      //              = 2 -> only init computed by systems
      virtual       CATMathSetOfPointsND  * GetComputedInit(short iInitType) const;

      virtual       CATBoolean              GetInitIsSingular(CATBoolean * ioSingularTreatmentSuccess = NULL);


      // cqi 03oct05 -------

      // Spine specific methods dedicated to variable connects:
      //  * VariableFillet
      //  * VariableFilletG1
      //  * VariableRollingEdge
      //  * VariableChordalFillet
      //  * VariableFilletD1D2

      // To set spine's domain.
                    void                    SetSpineLimits(const CATCrvLimits &iLimits);

      // Method to call for initializing marching domains. According to the strategy, this method offers
      // the  possibility to relimit spine's domain so as to avoid to compute solution over the objective
      // pointing point. iSupport1 and iSupport2 are support surfaces (in the order given to constructor),
      // iIndexSpine is index of spine parameter in implicit system points.
      //
      //  * iStrategy = 0: (Standard) fills oStart, oEnd with _SpineLimits and
      //                   oMaxStart, oMaxEnd with spine's max. limits
      //  * iStrategy = 1: if _PointingPoint and _InputInit are given, try to
      //                   relimit output values
      //
      // NB.: it does nothing for irrelevant called (see upper) or if input conditions are not
      // fullfilled (iStrategy = 1 and no _PointingPoint for instance).
      //
      virtual       void                    InitializeSpineLimits( CATSurface * iSupport1  ,
                                                                   CATSurface * iSupport2  ,
                                                                   CATLONG32    iIndexSpine,
                                                                   double     & oStart   , double     & oEnd, 
                                                                   double     & oMaxStart, double     & oMaxEnd,
                                                                   CATLONG32    iStrategy = 0);
      // -------

      // ==== SmoothLimiting specific methods ====

      // Allows to set all limiting PCurves data (tables are not duplicated).
                    void                    SetSmoothLimiting(CATLONG32              iPCrvSize ,
                                                              CATLONG32            * iPCrvID   ,
                                                              CATPCurve           ** iPCrvTable,
                                                              CATCrvLimits         * iPCrvLim  ,
                                                              short                * iPCrvSide );

      // Allows to set all limiting POECs data (tables are not duplicated).
                    void                    SetSmoothLimiting(CATLONG32              iPOECSize ,
                                                              CATLONG32            * iPOECID   ,
                                                              CATPointOnEdgeCurve ** iPOECTable,
                                                              short                * iPOECSide );


      // ==== Init loop computation option ====

      // Allows to trigger the init loop detection computation.
                    void                    DoResearchInitLoop(CATBoolean iEnable = TRUE);
                    void                    SetResearchInitLoopLines (int iNbLines = 1);

                    CATBoolean              HasInputInit() const;

                    INLINE       CATBoolean IsAlmostSmooth(){return _AlmostSmooth;}

      //=============================================================================
      // CGMReplay (SOU)
      //=============================================================================
      virtual       void                    UpdateOutput(CATCGMStream& iOutputStream);

      virtual       void                    WriteOutput(CATCGMStream& oOtherOutput) const;

      virtual       void                    PrepareStreamInput(CATLISTP(CATICGMObject)& oListObjects, CATCGMStream& oOtherInput) const;

      //
      // Canonical Fillet
                    void                    SetNumberOfResult( const CATLONG32 iNoR )
         {
         _numberOfResult = iNoR;
         }

                    void                    SetResultSets( double * iStart,
                                                           double * iEnd,
                                                           double * iVec )
         {
         _resultSets    = new CATMathSetOfPointsNDWithVectors * [1];
         _resultSets[0] = new CATMathSetOfPointsNDWithVectors ( 4, 0 );
         _resultSets[0]->AddPointWithVector( iStart, iVec );
         _resultSets[0]->AddPointWithVector( iEnd, iVec );
         }
      virtual       CATBoolean            IsCrossingPointInserted(){return FALSE;};

      CATLONG32 GetNumberOfResults() const
      {
        return _numberOfResult;
      }

   protected:
#ifdef      FactorizeDestroyResults
      virtual       void                  DestroyResults();
#endif

      virtual       void                  DefaultAttrRepartition(double &oSag, double &oMinStep, double &oMaxStep);


      // ==== Extrapolation optimization thanks to SmoothLimiting data ====

      // Let us consider the support with ID = iSupportID. Then this method must be used to set up
      // the index of U parameter in result set (iFirstCoord) and V parameter (iSecondCoord).
      // If support is of curve type, please set index of W = iFirstCoord = iSecondCoord.
      // NB.: mandatory method.
      virtual       void                  SetUpExtrapolData(CATLONG32 iSupportID, CATLONG32 iFirstCoord, CATLONG32 iSecondCoord);

      // This method should be called during Run before context extrapolation, when multiple solutions have been computed.
      // If smooth limiting data have been given, this method performs crossing analysis and set up internal diags and sets
      // so as to try to optimize further extrapolations (see IsExtrapolationAllowed).
      // iSolutionIndex is the index of the solution set to analyse with respect to _resultSets.
      virtual       void                  ExtrapolPreProcess(CATLONG32 iSolutionIndex);

      // This method checks if current solution set crosses the given limiting PCurve of index iPCrvIndex and returns a diagnostic:
      //  oDiag = -1: deep error (failure, lack of relevant data, etc.).
      //  oDiag =  0: the current solution does not cross the limiting PCurve.
      //  oDiag =  1: the current solution crosses the limiting PCurve.
      // If a solution occurs (oDiag = 1), the associated intersection point is added to _crossingPts solution set at iPCrvIndex position.
      virtual       void                  CrossingPCurveAnalysis(CATMathSetOfPointsNDWithVectors * iSet,
                                                                 CATLONG32                         iPCrvIndex,
                                                                 CATLONG32                         iSolutionIndex,
                                                                 CATLONG32                       & oDiag);

      // Overridden auxiliary function for the above that treats non-linear PCurves 
      virtual       CATBoolean            CrossingPCurveAnalysisNonLinear(CATMathSetOfPointsNDWithVectors * iSet,
                                                                          CATLONG32                         iPCrvIndex,
                                                                          CATLONG32                         iSolutionIndex);

      // Post-analysis method that checks if extrapolation of iPointToExtrapol (candidate solution point to be extrapoled) is allowed
      // with respect to previous analysis performed by ExtrapolPreProcess.
      // The method returns a diagnostic:
      //  0: extrapolation is not allowed.
      //  1: extrapolation is allowed.
      virtual       CATLONG32             IsExtrapolationAllowed(CATLONG32 iSolutionIndex, double * iPointToExtrapol);

    private:
      CATConnectComputer();
      

      //
      //=================================================================================================
      // DATA
      //=================================================================================================
      //

   protected:

      int                        _OperatorTag;        // ID of the instance of this

      CATGeoFactory            * _Factory;
      CATSoftwareConfiguration * _SoftwareConfiguration;
      const CATTolerance       & _TolObject;

      CATConnectTool           * _Profile;
      CATLONG32                  _Dimension;

      // Common
      CATEdgeCurve             * _CommonCurve;
      CATEdgeCurve            ** _CommonCurves0;
      CATEdgeCurve            ** _CommonCurves1;
      CATCrvParam              * _CommonPoint;
      CATCrvParam              * _CommonPoints0;
      CATCrvParam              * _CommonPoints1;

      short                      _CommonCurveOrient1;
      short                      _CommonCurveOrient2;
      CATLONG32                  _initIndex;
      CATLONG32                  _initPiece;

      // Init
      CATLONG32                 _InitSignature;
      CATMathSetOfPointsND    * _InputInit;
      CATMathSetOfPointsND    * _ComputedInitH; //Homotopy
      CATMathSetOfPointsND    * _ComputedInitS; //System
      CATMathSetOfPointsND    * _ComputedInitLS; //LoopSearch

      CATMathSetOfLongs *_PointsToKeep;

      // Local data.
      CATMathImplicitSystem   * _ImplicitSystem;
      CATMathIntervalND         _Domain,_MaxDomain;

      // Result data.
      CATLONG32                 _numberOfResult;
      CATLONG32                 _currentResult;
      CATMathSetOfPointsNDWithVectors ** _resultSets;

      const CATLONG32         * _PreviousSupportDimensionTable;
      const double            * _PointingPoint;

      CATLONG32               * _StartDiag,
                              * _EndDiag;

      // PKC 13/01/2005
      CATBoolean                _OnlyInitHomotopic;

      // cqi 03oct05 - Domain on spine (see below SetSpineLimits)
      CATCrvLimits _SpineLimits;

      // cqi 15feb05 - SmoothLimiting dedicated data
      // PCurve
      CATLONG32                _PCrvSize;
      CATLONG32             *  _PCrvID;
      CATPCurve             ** _PCrvTable;
      CATCrvLimits          *  _PCrvLim;
      short                 *  _PCrvSide;
      // POEC
      CATLONG32                _POECSize;
      CATLONG32             *  _POECID;
      CATPointOnEdgeCurve   ** _POECTable;
      short                 *  _POECSide;

      // Extrapolation
      CATBoolean               _extrapol1,
                               _extrapol2,
                               _extrapol3;      // flags
      CATCurve               * _SupportCrv1,
                             * _SupportCrv2,
                             * _SupportCrv3;
      CATSurface             * _Support1,
                             * _Support2;
      CATCrvLimits             _limit1,
                               _limit2;

      CATBoolean               _DoResearchInitLoop; // cqi 05dec06
      int                      _NbLinesLoopSearch;
      CATBoolean               _RelaxDomainForInits;

      CATLONG32              * _coordIndex;
      CATLONG32              * _crossingDiags;
      CATLONG32              * _crossingIndex;
      CATMathSetOfPointsND   * _crossingPts;


      CATLONG32              * _configs;

      // BlockedSphere & Suitcase
      CATBoolean               _SingularInit,
                               _SingularTreatmentSuccess;

      CATBoolean _AlmostSmooth;
   private:
     
      // Utilities
      CATConnectUtilities      _ConnectUtilities;
   };

//=================================================================================================
ExportedByConnect
CATConnectComputer * CreateConnectComputer(CATSoftwareConfiguration * iSoftwareConfiguration,
                                           CATGeoFactory            * iFactory,
                                           const CATConnectSupport  * iSupport1,
                                           const CATConnectSupport  * iSupport2,
                                           const CATConnectTool     * iProfile,
                                           CATMathSetOfPointsND     * iSetOfInitPoints,
                                           CATIntersectionSign        iStartingSignOn1,
                                           CATEdgeCurve             * iCommonCurve,
                                           CATCrvParam              * iCommonPoint,
                                           short                      iCommonCurveOrient1,
                                           short                      iCommonCurveOrient2,
                                           CATBoolean                 iLoopSearch,
                                           CATBoolean                 iRelaxDomainForInits = FALSE);

// overloaded function for tri tangent fillet
ExportedByConnect
CATConnectComputer * CreateConnectComputer(CATSoftwareConfiguration * iSoftwareConfiguration,
                                           CATGeoFactory            * iFactory,
                                           const CATConnectSupport    iSupport[3],
                                           const CATConnectTool     * iProfile,
                                           CATMathSetOfPointsND     * iSetOfInitPoints,
                                           CATIntersectionSign        iStartingSignOn1,
                                           CATEdgeCurve            ** iCommonCurve0,
                                           CATEdgeCurve            ** iCommonCurve1,
                                           CATCrvParam              * iCommonPoint0,
                                           CATCrvParam              * iCommonPoint1,
                                           CATBoolean                 iLoopSearch);

ExportedByConnect
CATConnectComputer * CreateConnectComputer(CATSoftwareConfiguration * iSoftwareConfiguration,
                                           CATGeoFactory            * iFactory,
                                           const CATConnectSupport    iSupport[3],
                                           CATMathSetOfPointsND     * iSetOfInitPoints,
                                           CATIntersectionSign        iStartingSignOn1,
                                           CATEdgeCurve            ** iCommonCurve0,
                                           CATEdgeCurve            ** iCommonCurve1,
                                           CATCrvParam              * iCommonPoint0,
                                           CATCrvParam              * iCommonPoint1,
                                           CATBoolean                 iLoopSearch);

// creator for crv sur connect
ExportedByConnect
CATConnectComputer * CreateCrvSurConnectComputer(CATSoftwareConfiguration * iSoftwareConfiguration,
                                                 CATGeoFactory            * iFactory,
                                                 const CATConnectSupport  * iSupport1,
                                                 const CATConnectSupport  * iSupport2,
                                                 const CATConnectTool     * iProfile,
                                                 CATMathSetOfPointsND     * iSetOfInitPoints,
                                                 CATBoolean                 iLoopSearch);

// creator for pt sur connect
ExportedByConnect
CATConnectComputer * CreatePtSurConnectComputer(CATSoftwareConfiguration * iSoftwareConfiguration,
                                                CATGeoFactory            * iFactory,
                                                const CATConnectSupport * iSupport1,
                                                const CATConnectSupport * iSupport2,
                                                const CATConnectTool    * iProfile,
                                                CATMathSetOfPointsND    * iSetOfInitPoints,
                                                CATMathSetOfPointsND    * iSetOfExitPoints,
                                                CATLISTP(CATSurface)    & iSurfList,
                                                CATLISTP(CATSurParam)   & iSurParamList,
                                                CATBoolean                iLoopSearch);

// creator for crv crv sur connect
ExportedByConnect
CATConnectComputer * CreateCrvCrvSurConnectComputer(CATSoftwareConfiguration * iSoftwareConfiguration,
                                                    CATGeoFactory            * iFactory,
                                                    const CATConnectSupport    iSupport[3],
                                                    const CATConnectTool     * iProfile,
                                                    CATMathSetOfPointsND     * iSetOfInitPoints,
                                                    CATBoolean                 iLoopSearch,
                                                    CATBoolean                 iUseExactDomainForInit);

// creator for crv crv sur connect
ExportedByConnect
CATConnectComputer * CreateCrvSurSurConnectComputer(CATSoftwareConfiguration * iSoftwareConfiguration,
                                                    CATGeoFactory            * iFactory,
                                                    const CATConnectSupport    iSupport[3],
                                                    const CATConnectTool     * iProfile,
                                                    CATMathSetOfPointsND     * iSetOfInitPoints,
                                                    CATBoolean                 iLoopSearch,
                                                    CATBoolean                 iUseExactDomainForInit);
ExportedByConnect
CATConnectComputer * CreateCrvCrvConnectComputer(CATSoftwareConfiguration * iSoftwareConfiguration,
                                                 CATGeoFactory            * iFactory,
                                                 const CATConnectSupport  * iSupport1,
                                                 const CATConnectSupport  * iSupport2,
                                                 const CATConnectTool     * iProfile,
                                                 CATMathSetOfPointsND     * iSetOfInitPoints,
                                                 CATBoolean                 iLoopSearch);

ExportedByConnect
CATConnectComputer * CreateDraftBothSidesSurSurComputer(CATSoftwareConfiguration * iSoftwareConfiguration,
                                                        CATGeoFactory            * iFactory,
                                                        const CATConnectSupport    iSupport[3],
                                                        const CATConnectTool     * iProfile,
                                                        CATMathSetOfPointsND     * iSetOfInitPoints,
                                                        CATBoolean                 iLoopSearch);

ExportedByConnect
CATConnectComputer * CreateDraftBothSidesCrvCrvComputer(CATSoftwareConfiguration * iSoftwareConfiguration,
                                                        CATGeoFactory            * iFactory,
                                                        const CATConnectSupport    iSupport[3],
                                                        const CATConnectTool     * iProfile,
                                                        CATMathSetOfPointsND     * iSetOfInitPoints,
                                                        CATBoolean                 iLoopSearch);
#endif
