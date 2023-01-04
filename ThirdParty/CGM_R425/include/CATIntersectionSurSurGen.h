// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CATIntersectionSurSurGen.h
//  Base class for intersection of surfaces from which derive
//  Intersection Plane/Surface, Plane/Plane and Surface/Surface
//=============================================================================
// Usage Notes:
//
// This class contains common objects to intersections sursur operators
//=============================================================================
// Jan. 99   Creation                                    X. Gourdon
// Dec. 99   Modifications                               P. Sebah
// 28/11/08 NLD Utilisation de CATCGMOperatorDebug pour outillage standard de debug/mesure
// 03/12/09 NLD Ajout RequireLockSurfaces() pour centraliser toutes les requetes de Lock()
// 26/07/10 NLD Ajout SetSoftwareConfiguration() pour delegation initialisation dans CATDataSurSurGen.cpp
// 29/03/12 XMH Split curves by the start/ends of other solution curves (IntersectionSurSur_SplitAdmissibleCurve)
// 10/04/12 XMH Simplify borders of a confused region (IR151284), added CreateQuinticAdmissibleCurveData
// 17/05/12 XMH Add SetExitSingular
// 12/07/12 XMH ApplyParameterDistortion (to fix IR123092 regression)
// 26/09/12 R1Y Fixed IR-123092 by modifying algorithms for marching (KJD) and curve-splitting (XMH).
// 21/09/12 Q48 Treatment of _TryAgain and init points in cone apex case (to fix IR173164)
// 11/10/12 Q48 Add debug code to try to reduce search limits for loop init finding (IR 160593)
// 29/11/12 R1Y Added and used the enum CornerLocation2D.
// 04/12/12 Q48 Added ComputeSingularTangents - temporary function to classify singular points
//                - associated to flag IntersectionSurSur_SingularPointTangents
// 12/12/12 Q48 Changed _ImplicitSystem to CATFunctionIntersectionSurSur* (from CATMathImplicitSystem*)
// 08/01/13 Q48 Moved ComputeSingularTangents to CATFunctionIntersectionSurSur
// 18/01/13 R1Y Added functionality for help points (under PS_Direct_Singular_HelpPoints).
// 15/03/13 Q48 Added debug trace and visual debug (SSGEN_MarchedPoints)
// 25/03/13 Q48 Added debug functionality for swapping surfaces in replay ReadInput
// 12/04/13 Q48 Update to use CATIntersectionSurSurGen::CATSurSurResultPointType enum
// 13/05/13 Q48 Make IsSingularPoint public for IntersectionMultiSurf
// 16/07/13 Q48 Add _ParamDistortion to cache the values (and debug to give warning / error)
// 27/08/13 Q48 Add Set / Get methods for temporary G2-Fillet mode
// 02/09/13 Q48 Move some code for cone-apex cases to CATUtilSurSurGen
// 25/09/13 Q48 Add _ToleranceFactorForDegeneratePoints to simplify tolerances and propagate to SSWI
// 25/10/13 R1Y Added MaxNumTangents()
// 30/10/13 Q48 Add visual debug (moved common functions from SSWI)
// 27/11/13 Q48 Added TestAndAlignTangentToBorder for IR168167
// 19/12/13 Q48 Added IsPointOnBorder3D for PS-Direct (for IR 264588)
// 27/01/14 Q48 Added CATSurSurResultPointPoleTgtStatus enum
// 25/03/14 Q48 Filter curves and points from loop-init (convergence for IR-283344)
// 15/04/14 Q48 Add ComputeReturningPoints_Sphere (for IR-160593)
// 12/05/14 Q48 Add data access functions for self-intersection (CATIntersectionAutoSur)
// 27/05/14 Q48 X-scale migration - remove access to default constructor
// 11/06/14 Q48 Implement X-scale in replay mechanism
// 03/07/14 Q48 Add CATSurSurResultCurveType enum
// 24/07/14 Q48 Add CATAutoSurCurveData (self-intersection) as friend class
// 24/07/14 Q48 Refactor IsAPole (make utility method static for friend AutoIntersection)
// 12/09/14 Q48 Add InterOpImprovedInit to result point type
// 23/09/14 Q48 Enhancements to param-distortion mechanism for PS-Direct IR317503
// 22/10/14 Q48 Remove _ReadingInterOpHelpPoints from replay mechanism
// 14/11/14 Q48 Fix to replay mechanism to avoid SSGen / SSWI type confusion
// 26/02/15 Q48 Add methods for refactor of CleanParasiticCurves
// 31/03/15 Q48 Add _FoundMissedBorders for ComputeIndexes
// 20/05/15 Q48 Add methods for SpherePole tangent calculation
// 21/05/15 Q48 Refactor code in CleanCurves (add CleanCurveSolutions_SingularCurves)
// 13/10/15 Q48 Small refactor of IsAPole code
// 17/11/15 Q48 Add variable and method to allow user to set CGM replay prefix name
// 24/11/15 Q48 Add SoftwareConfiguration to CATSurSurResultPoint
// 26/11/15 Q48 Add method to account for parameter distortion in border calculation
// 20/05/16 Q48 Signature changes for CleanCurves project (joined curves for G0 or G1)
// 04/11/16 Q48 IR-480859: Add methods to reduce search domain for returning points (performance)
// 23/03/17 Q48 Small refactor of canonical methods
// 21/04/17 PKC compilation warning
// 22/03/18 Q48 Add computation singular pole init (sphere / cylinder only)
// 06/04/18 Q48 Add computation singular pole init (pointed generic fillet)
// 10/04/19 Q48 Added IntersectionSpecExtrapol for IR-671945
// 15/05/19 Q48 Small tidy of CleanCurve methods
// 18/06/19 Q48 Refactor to remove ReturningPoint from point-type (replaced by FromSurSur init type)
// 04/07/19 Q48 IR-663523: function signatures for tangent / border methods
// 04/09/19 Q48 IR-702010 and IR-706427: use different 3D box for border / loop init searches
// 01/10/19 Q48 IR-713445: add FromPoleTgt (and _Analytic) to CATSurSurInitType
// 13/11/19 Q48 Migrated some IsPointOnBorder methods from SurSurWithInits
// 13/11/19 Q48 Add mutable for some lazy data (Domain / ImplicitSystem)
// 12/03/20 Q48 Add C++ keywords for some functions
// 21/07/20 Q48 Add argument to CleanCurveSolutions to treat only identical curves
// 21/08/20 Q48 Enum for CATSurSurResultPoint treated type
// 09/09/20 Q48 Update to signature of SetIntersectionSpec
// 28/04/21 Q48 Refactor some init methods for border init search
// 07/07/21 Q48 Move ImproveStartingPoint to this class (from CATUtilSurSurGen)
//=============================================================================

#ifndef CATIntersectionSurSurGen_h
#define CATIntersectionSurSurGen_h

// Define the following variable to allow help points to be entered for singular cases with PS Direct.
//#define PS_Direct_Singular_HelpPoints

// Intersectors
#include "CATIntersectionSurSur.h"
#include "CATCreateIntersectionSurSurGen.h"
//#include "Y30C3XGG.h"


// Basic types
#include "CATDataType.h"
#include "CATBoolean.h"
#include "CATString.h"
#include "CATUnicodeString.h"

// C++11
#include "CATGeoOpVirtual.h"


// Mathematics
#include "CATMathBox.h"
#include "CATMathVector.h"


// Geometric objects
#include "CATCrvParam.h"
#include "CATSurParam.h"
#include "CATSurLimits.h"
#include "CATIsoParameter.h"
#include "CATDistortionUtility.h"


// Geometric operators
#include "CATPipeData.h"


// GMModel
#include "CATIntersectionSign.h"
#include "CATIntersectionOrientation.h"
class CATGeoODTScaleManager; // Q48 (06/2014): X-scale


// Debug
#include "CATCGMOperatorDebug.h"
#include "CATGeoOpTimer.h"
#include "CATGeoOpDebug.h" // must be included to get #define GEOPDEBUG to be propagated here

#ifdef GEOPDEBUG
#include "CATMathStopDiagnostic.h"
class CATMultiThreadSurSurGen;
class CATCrvCell;
class CATGeoConnectorCell;
#endif

// Temp
#include "CATGeoOpArchiTEMP.h"

// Intersectors
class CATSurSurResultPoint;
class CATSurSurResultCurve;
class CATSurSurResultLoop;
class CATSurSurResultAdmissibleCurve;


// GeometricObjects
class CATGeoFactory;
class CATSurface;
class CATCurve;
class CATPCurve;
class CATEdgeCurve;
class CATSetOfCrvParams;
class CATSetOfSurParams;
class CATCartesianPoint;
class CATPointOnSurface;
class CATPointOnEdgeCurve;
class CATCGMAttrIsopar;


//Geometric Operators
class CATGeoConnectorCell;
class CATFunctionIntersectionSurSur;


// Mathematics
class CATSoftwareConfiguration;
class CATMathPoint;
class CATMathPoint2D;
class CATTolerance;
class CATMathSetOfLongs;


// Advanced Mathematics
class CATMathSetOfPointsND;
class CATMathSetOfPointsNDTwoTangents;
class CATMathSetOfPointsNDWithVectors;
class CATMathImplicitSystem;
class CATMathIntervalND;
class CATMathFunctionXY;


struct CATCrvCrvInit {
  CATLONG32 _IndexCrv[2];
  CATCrvParam _Param[2];
};

// Corner location for a 2D region.
// Note that these values should not be modified, as they are used as indexes of arrays.
enum CornerLocation2D { BottomLeft = 0,
                        TopLeft,
                        BottomRight,
                        TopRight };

struct CATPtSurInit {
  CornerLocation2D _CornerIndex;
  CATLONG32 _SurIndex;
  CATSurParam _Param;
};

class ExportedByY30C3XGG CATIntersectionSurSurGen : public CATIntersectionSurSur
{
friend class CATIntersectionAutoSurImp;
friend class CATAutoSurCurveData;

public:

  // CAUTION: as these values are streamed in CGMReplay files, NO insertion is allowed
  //          value associated to each id must never change throughout this object life
  //          NLD 2012 Feb 09th
  enum CATIntersectionSpec { IntersectionSpecDefault,
                             IntersectionSpecFillet,
                             IntersectionSpecSweepTopo,
                             IntersectionSpecInterOp,
                             IntersectionSpecExtrapol};

  /*typedef*/ // PKC 21/04/2017 useless typedef in C++, compilation warning 
  enum CATSurSurResultCurveType { UnknownCurve = -1,
                                  AdmissibleCurve = 0,
                                  InteriorCurve };

  /*typedef*/ // PKC 21/04/2017 useless typedef in C++, compilation warning 
  enum CATSurSurResultPointType { SingularPoint = 0, 
                                  MarchOneWay, 
                                  DeformationPoint, 
                                  MarchBothWays, 
                                  ExitOnly, 
                                  SpherePole, 
                                  IncompleteExtremity,
                                  //ReturningPoint,
                                  InterOpImprovedInit };

  enum CATSurSurResultPointTreatedType { NotTreated = 0,
                                         BadInput,
                                         InACurve,
                                         IsolatedPt };

  enum CATSurSurInitType { UnknownInitType = 0,
                           FromCrvCrv,
                           FromCrvSur_Pt,
                           FromCrvSur_Crv,
                           FromSurSur,
                           FromPoleTgt,
                           FromPoleTgt_Analytic };

  enum CATSurSurResultPointPoleTgtStatus { NotAPole = 0, 
                                           PoleAnalytic, 
                                           PoleNotTreated, 
                                           PoleTgtOK, 
                                           PoleTgtKO };
  
  // 30/10/19: Q48 - now redundant and replaced by two new enums
  //enum BorderType { UnkownBorder = -1,
  //                  NotOnBorder,
  //                  Umin,
  //                  Umax,
  //                  Vmin,
  //                  Vmax };

  enum BorderUV{ BorderNotUV = -1,
                 BorderU = 0,
                 BorderV = 1 };

  enum BorderExtrem { BorderMin = -1,
                      BorderNo = 0,
                      BorderMax = 1 };

  class BorderInfo
  {
  public:
    BorderInfo();
    BorderInfo(const short iSurf, const BorderUV iBorderUV, const BorderExtrem iBorderExtrem);
    BorderInfo(const BorderInfo & iBorderData);

    ~BorderInfo();

    short BorderIndex() const;

    short        _BorderSurf;
    BorderUV     _BorderUV;
    BorderExtrem _BorderExtrem;

    GEOPDEBUG_CMD(static CATUnicodeString Debug_Print(const BorderExtrem iExtrem));
    GEOPDEBUG_CMD(static CATUnicodeString Debug_Print(const BorderExtrem iExtrem[], const CATLONG32 iNum));
  };

  //
  //-----------------------------------------------------------------------
  //- Object management : Constructor and destructor
  //-----------------------------------------------------------------------
  //

protected:
  CATIntersectionSurSurGen(); // not to be used (even for CGMReplay) - this is not X-scale compliant

public:
  CATIntersectionSurSurGen(CATGeoFactory            * iFactory, 
                           CATSoftwareConfiguration * iConfig,
                           CATSurface               * iSurface1, 
                           CATSurface               * iSurface2);

  virtual ~CATIntersectionSurSurGen();
  //
  //-----------------------------------------------------------------------
  //- Iterators management
  //-----------------------------------------------------------------------
  //
  //  For point solution : retrieve all the points solution of the intersection
  //  with various available format.
  //
  virtual CATLONG32 GetNumberOfPoints() const;
  virtual void BeginningPoint();
  virtual CATBoolean NextPoint();
  //
  virtual void GetSurParam(CATSurParam & oSurParam1, CATSurParam & oSurParam2);
  virtual void GetImplicitSystemStartPoint(double *oStartPoint, double *oStartTangent);
  virtual CATCartesianPoint * GetCartesianPoint();
  virtual CATPointOnSurface * GetPointOnSurface(CATSurface * iSurface);
  virtual void GetSingularPoints(CATSetOfCrvParams * &oSetOfSingParams);
  virtual void GetExitPoints(CATSetOfCrvParams * &oSetOfExitParams);
  virtual CATMathSetOfLongs * GetExitNumero();
  virtual void GetExitPoint(CATLONG32 ExitNumero, CATCrvParam &ExitParam);
  virtual CATMathSetOfPointsND * GetInitPoints() ;
  //
  // For curve solutions : retrieve all the intersection curves 
  //
  virtual CATLONG32 GetNumberOfCurves() const;
  virtual CATLONG32 GetNumberOfCurveSolutions() const;
  virtual void BeginningCurve();
  //
  virtual CATBoolean NextCurve();
  virtual CATPCurve * GetPCurve(CATSurface * iSurface);
  virtual CATPCurve * GetPCurve(CATLONG32 iIndexOperand);
  virtual CATEdgeCurve * GetEdgeCurve();
  virtual CATEdgeCurve * GetEdgeCurve(CATPointOnEdgeCurve * &oPOECStart, CATPointOnEdgeCurve * &oPOECEnd);
  virtual CATCurve * GetCurve();
  virtual CATIntersectionSign GetSignatureOn(CATSurface * iSurface);
  virtual CATIntersectionCrossing GetCrossingOn(CATSurface * iSurface);
  virtual CATSurSurResultCurveType GetCurveType() const;
  virtual CATLONG32 GetUnstableWarning(); // ase-sdp 19jun03- 0 = ok, 1 = the result curve is unstable

  virtual void GetDefinitionPoints(CATMathSetOfPointsNDTwoTangents & oSet) const;

  virtual void GetFirstPointAndTangent(double oPt[], double oTgt[]) const;
  virtual void GetLastPointAndTangent(double oPt[], double oTgt[]) const;

  virtual void GetCurveData(CATSurSurResultCurve *&) const; // only for use within GeometricOperators

  virtual void GetStartingPointsIndex(CATLONG32 & oBegin, CATLONG32 & oEnd);
  
  //
  // Test if Point are singular
  //
  virtual CATBoolean IsSingularPoint(const double *iXPt);

  virtual void ComputeMarchingTangent(const double       iPt[4], 
                                            CATLONG32  & oNbTangent, 
                                            double     * oTangent);
  //
  // For confused faces : retrieve the confusion zone as closed sets of curves
  //
  virtual CATLONG32 GetNumberOfSurfaces() const;
  virtual void BeginningSurface();
  virtual CATBoolean NextSurface();
  //
  virtual CATLISTP(CATPCurve)    GetSurfaceBoundaries(CATSurface                  * iSurface, 
                                                      CATIntersectionOrientation ** oPCrvOrientation    = NULL,
                                                      CATIntersectionOrientation  * oContourOrientation = NULL);
  
  virtual CATLISTP(CATEdgeCurve) GetSurfaceBoundaries(CATIntersectionOrientation ** oECrvOrientation,
                                                      CATIntersectionOrientation  * oLoopOrientation1,
                                                      CATIntersectionOrientation  * oLoopOrientation2);
  
  virtual CATLISTP(CATEdgeCurve) GetSurfaceBoundaries(CATIntersectionOrientation **  oECrvOrientation,
                                                      CATIntersectionOrientation  *  oLoopOrientation1,
                                                      CATIntersectionOrientation  *  oLoopOrientation2,
                                                      CATLONG32                   *& oStartIndexes,
                                                      CATLONG32                   *& oEndIndexes);

  virtual const CATLONG32 GetSurfaceBoundaryCurveData(CATIntersectionOrientation   *  oPCrvOrientation[],
                                                      CATIntersectionOrientation    & oLoopOrientation1,
                                                      CATIntersectionOrientation    & oLoopOrientation2,
                                                      CATSurSurResultCurve        **& oResultCurves);

  virtual CATSoftwareConfiguration* GetSoftwareConfiguration() const CATGEOOverride CATGEOFinal;;
  //
  //-----------------------------------------------------------------------
  //- Set methods
  //-----------------------------------------------------------------------
  //
  virtual void SetSurface(CATSurface * iNewSecondSurface);
  // CAUTION: These boxes have to include the SurLimits of the surface
  virtual void SearchInBox(const CATMathBox& i3DBox);
  virtual void SetBoxSurf0(const CATMathBox& i3DBox0);
  virtual void SetBoxSurf1(const CATMathBox& i3DBox1);

  virtual void HoldDomain(CATSurLimits * iLimits1, CATSurLimits * iLimits2);
  virtual void SetLimits(CATSurLimits  * iNewLimitsForSurface1, CATSurLimits * iNewLimitsForSurface2);
  virtual void SetCanonicalPCurveOnPlane();
  virtual void SetUnstableWarning();
  virtual int GetTangentDiagnostic(int * oCheckGap);
  //
  // Default behaviour : confusions, loops and indexes are searched
  //
  virtual void SetConfusionSearch(CATBoolean iConfusionSearch);
  virtual void SetLoopSearch(CATBoolean iLoopSearch);
  virtual void SetIndexSearch(CATBoolean iIndexSearch);
  virtual void SetTangentSolutionComputation();

  //
  // These methods are specials functions for intersection with inits.
  //

  virtual void SetNonCutting(CATBoolean iDoNotCut=1);
  virtual void SetOnlyBetweenInits(CATBoolean iOnlyBetweenInits=1);
  virtual void SetTangentSol(CATBoolean iTangentSol=1);
  
  virtual void SetIntersectionSpec(const CATIntersectionSpec iIntersectionSpec,
                                   const CATLONG32           iSpecVersion = -1);

  //
  // Mode pour chu
  //

  virtual void SetConvergeInit(CATBoolean iReconv=1);
  virtual void SetExtrapol(CATBoolean iBoolean);
  virtual void SetStartingPoints(CATSetOfSurParams   & SetSurParam1, 
                                 CATSetOfSurParams   & iSetSurParam2,
                                 CATIntersectionSign * iSignatureOnFirstSurface = 0, 
                                 double              * iTangents = NULL, 
                                 CATBoolean            LoopSearch = 1);
  virtual void ReachBoundaryOf(CATSurface * iSurface);
  // IndexOperand should have the value 0 or 1
  // same method than previous for StartingPoints
  // on the same surface intersection itself
  virtual void ReachBoundaryOf(CATLONG32 IndexOperand);
  virtual void SetOptimizedAttribute();

  virtual void SetTemporaryG2FilletMode(const CATBoolean);
  virtual CATBoolean GetTemporaryG2FilletMode() const;

  CATLONG32 MaxNumTangents();

  //
  //-----------------------------------------------------------------------
  //- Running the operator
  //-----------------------------------------------------------------------
  //
  //CATCGMOperatorDebugDeclareRun(CATIntersectionSurSurGen, CATIntersectionSurSur);
  virtual int RunOperator();
  //
  //-----------------------------------------------------------------------
  //- Utility methods
  //-----------------------------------------------------------------------
  //

  static CATBoolean IsPointOnBorder3D(      CATSoftwareConfiguration  * iConfig,
                                            CATGeoFactory             * iFactory,
                                      const CATSurface               ** iSurface,
                                      const CATMathIntervalND         & iDomain, 
                                      const double                    * iPoint,
                                            CATLONG32                 * oSaturatedVar,
                                            double                    * oDist,
                                      const double                      iTol);

  //
  //=============================================================================
  // Protected methods
  //=============================================================================
  //
protected:
  //
  //-----------------------------------------------------------------------
  //- Main Run subroutines
  //-----------------------------------------------------------------------
  //
  virtual void Run2();
  //
  virtual CATBoolean CheckInputs();     // Check the inputs

  virtual void Reset();
  virtual CATLONG32 IsIntersecting();         // Test if the surfaces may intersect
  virtual void ComputeBorderPoints();         // Find the starting points on a border of one surface
  
  virtual void ComputeReturningPoints();      // Find starting point for loop solutions
  
  virtual CATBoolean ComputeReturningPoints_Sphere(const short, 
                                                   const CATSurLimits[]); // Find starting point for loop solutions - sphere case

  virtual void ComputePolePolePoints();       // Find starting point when the surface has poles
  virtual void MultiMarching();               // Marching from all the starting point
  virtual void FindMissedBorders();           // Find Missed Admissible Curves in Borders(Between Point Solutions)
  virtual void FindMissedBorders_New();
  virtual CATLONG32 CleanSolutions();         // Clean redundant solutions
  virtual void ComputeIndexes();              // Compute all the indexes (extremities numerotation)
  virtual void ComputeConfusedFaces();        // Find the confused faces (as loop of curves)
  virtual void ComputeSignatures();           // Signature management
  // virtual CATLONG32 EliminateSingularInit(); // Gestion des inits singuliere (Cas Plan Sphere passant par les poles)
  //
  //-----------------------------------------------------------------------
  //- Internal subroutines
  //-----------------------------------------------------------------------
  
  CATBoolean AreLimitsValid(const CATSurLimits & iLimits) const;
  CATBoolean CheckSurfaceLimitsSupport(const CATSurface* iSurf, const CATSurLimits & iLimits) const;

  
  //
  // Test if there may be returning points
  //
  CATBoolean IsReturningPoint();
 
  void ReturningPointsLight();
 
  //
  // Special case tangent calculation routines
  //
  CATBoolean ComputeMarchingTangent_SpherePoleCase(const CATLONG32   iSphereLevel,
                                                   const double      iAngleTol,
                                                   const CATBoolean  iIsAPole[2],
                                                   const double      iPt[4], 
                                                         CATLONG32 & oNbTangent, 
                                                         double    * oTangent);

  static double GetSphereParamUnit(const CATSurface * iSurface,
                                         CATBoolean & oError);

  CATBoolean ComputeMarchingTangent_SpherePoleCase_Analytic(const short  iIndexSphere,
                                                            const double iPt[]);

  CATBoolean ComputeMarchingTangent_SpherePoleCase_Singular_Analytic(const short      iIndexSphere,
                                                                     const double     iPt[],
                                                                     const CATBoolean iIsNorthPole);

  CATBoolean ComputeMarchingTangent_ConeApexCase_Analytic(const short  iIndexCone,
                                                          const double iPt[]);

  CATBoolean TestAndSnapAngleToBorder(const CATCone      * iCone,
                                      const CATSurLimits & iSurLimits,
                                            CATAngle     & ioAngle1,
                                            CATAngle     & oAngle2,
                                            CATBoolean   & oTwoBorderCase) const;
  
  CATBoolean TestAndSnapAngleToBorder(const CATSphere    * iSphere,
                                      const CATSurLimits & iSurLimits,
                                      const double         iRadiusForParam,
                                            CATAngle     & ioAngle1,
                                            CATAngle     & oAngle2,
                                            CATBoolean   & oTwoBorderCase) const;

  CATBoolean TestAndSnapAngleToBorder(const CATAngle     iLowBorder_Max,
                                      const CATAngle     iUppBorder_Max,
                                      const CATAngle     iLowBorder_Current,
                                      const CATAngle     iUppBorder_Current,
                                            CATAngle   & ioAngle1,
                                            CATAngle   & oAngle2,
                                            CATBoolean & oTwoBorderCase) const;

  void NormalizeTangent(double ioTgt[]) const;

  //
  // Compute issued from a single starting point (fixation of marching parameters)
  //
  virtual void SingleComponentMarching(      CATSurSurResultPoint * iStartPoint, 
                                       const CATBoolean             iRespectTangent,
                                       const CATBoolean             iReduceSag = FALSE);

  CATBoolean IsOnSingularBorder(CATMathSetOfPointsND * iMarchedSets[],
                                CATLONG32              iNumMarchedSets) const;

  CATBoolean IsBetweenSingularBorders(CATMathSetOfPointsND * iMarchedSets[],
                                      CATLONG32              iNumMarchedSets) const;
  
  virtual void ComputeMarchingTangent(const double                              iPt[], 
                                            CATLONG32                         & oNbTangent,
                                            double                            * oTangent,
                                            CATSurSurResultPointPoleTgtStatus * oPoleStatus);

  void AddPointToMarchingEndPoints(const CATSurSurResultPoint * iPt);

  CATSurSurResultPointPoleTgtStatus UpdateInitAtPole(const double iPt[]);

  CATSurSurResultPointPoleTgtStatus UpdateInitAtPoleSingular(const double    iPt[],
                                                             const short     iSurfDegen,
                                                             const CATLONG32 iDegenerate);

  CATBoolean ComputeInit_SingularPole_GenFillet(const double iPt[],
                                                const short  iSurfDegen);

  virtual void IsAPole(const double    iPt[],
                             CATLONG32 ioIsDegenerated[]) const;

  static void DoIsAPole(      CATSoftwareConfiguration *       iConfig,
                        const CATSurface               * const iSurf[],
                        const CATMathFunctionXY        * const iGlobalEq[2][3],
                        const double                           iPt[],
                        const CATSurLimits                     iSurLimits[],
                        const double                           iTolSq,
                              CATLONG32                        oIsDegenerated[]);

  static CATBoolean IsAtSpherePole2D(const CATSurface * iSurface,
                                     const double       iPt[],
                                     const double       iTolerance);
  
  CATBoolean IsAtSpherePole4D(const double iPt[], 
                              const double iTolerance) const;

  CATBoolean IsAtConeApex4D(const double[]) const;
  CATBoolean IsAtConeApex2D(const double[], const short) const;
  CATBoolean IsAtConeApex3D(const CATMathPoint&, const short) const;

  void ComputeTangents();

  void ComputePointEntropy(CATSurSurResultPoint * ioPoint);

#ifndef Q48_IntSurSur_KeepImproveStartingPointInterface
  CATLONG32 ImproveStartingPoint(const CATSurSurResultPoint * iPoint,
                                       double                 oPt[]) const;
#endif // Q48_IntSurSur_KeepImproveStartingPointInterface

  CATBoolean IsMatchingPointType(const CATSurSurResultPoint * iPt,
                                 const CATLONG32              iNumTypes,
                                 const CATSurSurInitType      iTypes[]) const;

  void OrderPointsForMarching(const CATSurSurInitType   iType,
                                    CATMathSetOfLongs & ioOrderedIndices) const;

  void OrderPointsForMarching(const CATLONG32           iNumTypes,
                              const CATSurSurInitType   iTypes[],
                                    CATMathSetOfLongs & ioOrderedIndices) const;

  virtual void ReverseTangent(      CATSurSurResultPoint * ioPoint,
                              const double                 iPt[],
                              const double                 iTangent[]);

  void TestAndAlignTangentToBorder(const double       iPt[],
                                         double       ioTangent[],
                                   const CATLONG32  * iIsPointOnBorder = NULL) const;

  void TestAndAlignTangentToBorder(const double       iPt[],
                                         double       ioTangent[],
                                         CATBoolean & oTgtInDomain,
                                   const CATLONG32  * iIsPointOnBorder = NULL) const;

  CATBoolean DoIsAPointOnBorder(const CATSurSurResultPoint * iPt,
                                const double                 iTol,
                                      BorderExtrem         * oBorderInfo = NULL,
                                const CATBoolean             iWithSurf = FALSE) const;

  CATBoolean DoIsAPointOnBorder(const double         iPt4D[],
                                const double         iTol,
                                      BorderExtrem * oBorderInfo = NULL,
                                const CATBoolean     iWithSurf = FALSE) const;

  void UpdatePointOnBorder(const CATMathIntervalND    & iDomain,
                           const CATSurSurResultPoint * iPoint,
                           const double                 iPoint4D,
                           const short                  iIndex4D,
                                 BorderExtrem         & ioSaturatedVar) const;

  CATBoolean IsAdmissiblePointToRemove(const CATSurSurResultPoint           * iPoint,
                                       const CATSurSurResultAdmissibleCurve * iBorderCurve) const;

  CATBoolean RattrappePole(CATSurSurResultPoint * iStartPoint);

  int FastAutoIntersection2Offset();
  void ComputeInternalSingularPoints();

  // Return 1 if a canonical intersection is found, else return 0
  CATBoolean ComputeCanonicalIntersection();
  CATBoolean ComputeCanonicalIntersection_SphereCylinder();
  
  // Performance boxing / limits
  // ---------------------------

  CATBoolean ReduceDomainForReturningPoints(CATSurLimits   ioSurLim[],
                                            CATMathBox   & ioSearchInBox) const;

  CATBoolean ComputeSearchInBoxForBorderPoints(const short        iSurf,
                                                     CATMathBox & oSearchInBox) const;

  CATBoolean ComputeSearchInBoxForReturningPoints(const CATSurLimits   iSurLim[],
                                                        CATMathBox   & oSearchInBox) const;

  CATBoolean TryToReduceSurfaceLimits(CATSurLimits ioSurLim[]) const;

  CATBoolean TestSearchInBoxGain(const CATSurLimits[], CATBoolean[]) const;

  CATBoolean ApplySearchInBox(const short, const CATSurLimits&, CATSurLimits&) const;

  
  //
  // Intersection frontier-frontier
  //
  void IntersectFrontierFrontier(const CATTolerance   & iTol, 
                                 CATCurve             * iFrontier0, 
                                 CATCurve             * iFrontier1,
                                 CATMathSetOfPointsND & oSolutions);
  //
  // Intersection curve (frontier)-surface
  //
  void IntersectFrontierSurface(const CATLONG32         iSurf, 
                                      CATCurve        * iFrontier,
                                const CATIsoParameter   IsoPar,
                                const CATSurParam     & SurParamOnIso,
                                const CATLONG32         iIsoparIndex,
                                const double          * iStart = 0, 
                                const double          * iEnd = 0);

  void FillAdmissibleInits_CrvCrv(const CATLONG32              iSurf,
                                  const CATLONG32              iIsoparIndex,
                                        CATMathSetOfPointsND & ioAdmissibleInits) const;

  void FillAdmissibleInits_Corner(const CATLONG32              iSurf,
                                  const CATLONG32              iIsoparIndex,
                                  const CATCrvLimits         & iIsoParLimits,
                                        CATMathSetOfPointsND & ioAdmissibleInits) const;

  // Analysis of admissible curves
  // -----------------------------

  CATBoolean IsAnAdmissibleCurveOnBorder() const;
  
  CATBoolean IsAnAdmissibleCurveOnBorder(const short      iBorder,
                                         const CATBoolean iRequireFullBorder) const;
  
  CATBoolean IsAnAdmissibleCurveOnBorder(const short        iBorder,
                                         const short        iMinMax,
                                         const CATBoolean   iRequireFullBorder,
                                               CATLONG32  * oAdmissibleCurveIndex = NULL) const;
  
  CATBoolean IsAdmissibleCurveOnBorder(const CATLONG32  iCurveIndex,
                                       const short      iBorder,
                                       const short      iMinMax,
                                       const CATBoolean iRequireFullBorder) const;


  //
  // Return 1 if a confused face defined by the arguments exists, else return 0
  //
  CATBoolean ComputeConfusedFace(CATSurSurResultCurve ** iResultCurveTab,
                                 const CATLONG32         iNbResultCurve);
  // Tries to replace a confused region bounded by self-intersecting closed curve  
  // by a region defined by a rectangular parameter region of the first surface
  void SimplifyConfusedRegion();
  
  // Test if a tangential line in R4 is solution
  CATLONG32 TangentSolve(const double                          *  iStartPoint, 
                               double                          *  ioStartTangent, 
                               CATMathSetOfPointsNDWithVectors *& oSet, 
                         const CATBoolean                         iNotInverse = FALSE);

  // Test for tangent solution, 2D-linear (ie. in UV or RS)
  // Mode : 0 specific case _NbPoints == 2 ; 1 for general case _NbPoints >= 2
  // Force: 0 the method auto-checks that it is called only one time ; 1 to force the method to execute
  CATLONG32 TangentSolve_Bis(const CATLONG32 iMode);
  
  // Loops finding from indexes
  CATBoolean FindLoopFromConnector(CATGeoConnectorCell * iStartConnector,
                                   CATGeoConnectorCell * iEndConnector,
                                   CATMathSetOfLongs   & ioPath);

  //
  // Clean redundant solutions 
  //

  CATBoolean ConsiderCurveForCleaning(const CATSurSurResultCurve* iCurve) const;

  void CleanCurveSolutions(const CATBoolean iOnlyIdentical = FALSE);

  CATBoolean CleanCurveSolutions_IncludedCurve(const CATLONG32 iCurveIndex0, 
                                               const CATLONG32 iCurveIndex1,
                                               const double    iStartPt0[],
                                               const double    iMidPt0[],
                                               const double    iEndPt0[],
                                               const CATLONG32 iStart0In1,
                                               const CATLONG32 iMid0In1,
                                               const CATLONG32 iEnd0In1);

  CATBoolean CleanCurveSolutions_SingularCurves(const CATLONG32 iCurveIndex1, 
                                                const CATLONG32 iCurveIndex2);
  void CleanPointSolutions();
  void CleanCurveInSurface();
  void CleanSurfaceInSurface();
  void CleanPointInSurface();
  void CleanPointInCurve();
  void CleanParasiticCurves();
  void CleanParasiticCurves_Stage1(const CATBoolean iProcessJoinedCurves);
  
  CATBoolean GetCurveExtremityPoint(const CATLONG32  iCurveIndexInInclusionList,
                                    const CATBoolean iCurveOrienationInInclusionList,
                                    const CATLONG32  iNumCurvesInInclusionList,
                                    const CATLONG32  iCurveIndex,
                                          double     oPt4D[]) const;

  void CleanParasiticCurves_Stage2(const CATBoolean iProcessJoinedCurves);
  void CleanParasitesIntCurves();

  virtual CATBoolean AreInitListsTheSame(const CATMathSetOfLongs * iCurveInitList0,
                                         const CATMathSetOfLongs * iCurveInitList1) const;

  CATLONG32 IsCurveValidToClean(CATSurSurResultCurve * iCurveSolution1, CATSurSurResultCurve * iCurveSolution2); 
  CATBoolean IntersectPlinePline(const CATMathPoint2D & A0, const CATMathVector2D & D0,
                                 const CATMathPoint2D & A1, const CATMathVector2D & D1,
                                 double & ou, double & ov, const double iTol);

  void FindJoinedCurves(const CATBoolean          iAllowAdmissible,
                              CATMathSetOfLongs & ioIndexSet) const;

  void FindJoinedCurvesDirection(const CATBoolean          iForwards,
                                 const CATBoolean          iAllowAdmissible,
                                       CATMathSetOfLongs & ioIndexSet) const;

  virtual CATBoolean AreInitListsJoined(const CATLONG32  iCurveIndex1,
                                        const CATBoolean iCurveOrientation1,
                                        const CATLONG32  iCurveIndex2,
                                        const CATBoolean iCurveOrientation2) const;

  void NegateSetOfLongs(CATMathSetOfLongs & ioSet) const;

  CATBoolean AreEqualPoints3D(const double iPt4D0[],
                              const double iPt4D1[]) const;

  CATBoolean AreEqualPoints4D(const double iPt4D0[],
                              const double iPt4D1[]) const;

  CATBoolean IsFullLimits(const short iSurf,
                          const short iUV) const;

  void GetCurveExtremityAndMidPoints(const CATLONG32 iCurveIndex,
                                           double    oStartPt[],
                                           double    oMidPt[],
                                           double    oEndPt[]);

  //
  // Split AdmissibleCurve 
  //
  CATBoolean SplitAdmissibleCurve();
  CATBoolean InclusionOfExtremities(CATSurSurResultCurve * iCurve2, CATSurParam iUV[2]);
  //-----------------------------------------------------------------
  // Check The Pcurve Intersection
  // * Curve with small thickness (Resolution)
  //--------------------------------------
  CATLONG32 IsCurveValidAdvanced(CATSurSurResultCurve *iCurveSolution); 
  //
  //-----------------------------------------------------------------------
  //- Check  subroutines
  //-----------------------------------------------------------------------
  //
  virtual void CheckIndexPoint(char    * iMethod) const;
  virtual void CheckIndexCurve(char    * iMethod) const;
  virtual void CheckIndexSurface(char  * iMethod) const;
  virtual void CheckOperand(CATSurface * iSurface, char * iMethod) const;
  virtual CATBoolean CheckInfiniteSurface(const CATLONG32 iIndexSurface) const;
  //
  //-----------------------------------------------------------------------
  //- Utility  subroutines
  //-----------------------------------------------------------------------
  //
  void InitializeCommon();
  void RequireLockSurfaces();// locks surfaces if not already done
  CATLONG32 GetSurfaceIndex(CATSurface * iSurface);
  
  // Create the isopar u=iFixedVar (if iVar==0) or v=iFixedVar (if iVar==1) on the surface iSurf
  CATCurve* CreateIsopar(const int    iSurf, 
                         const int    iVar, 
                         const double iFixedVar);

  CATCurve* DoCreateIsopar(const int    iSurf, 
                           const int    iVar, 
                           const double iFixedVar);


  void SimplifyIsopar(CATCurve * & Isopar, CATSurface * Surf);

  CATBoolean IsoParCurves_GetAttribute(const short iSurfIndex);
  void       IsoParCurves_PutAttribute(const short iSurfIndex);
  
  // Create and add the data for a quintic admissible curve obtained from a CATIntersectionCrvSur result
  //   Case: iIsoPar == CATNotIsoParametric
  //   - iSetR4 must be a CATMathSetOfPointsNDWithVectors from which all data is extracted
  //   - iCurveLimits, iSurfLimits, iSurParamOnIso, iDeltaU, iDeltaV are ignored
  //   Case : iIsoPar == CATIsoParamU || iIsoPar == CATIsoParamV
  //   - iSetR4 should be a  CATMathSetOfPointsNDTwoTangents
  //   - iCurveLimits, iSurfLimits, iSurParamOnIso, iDeltaU, iDeltaV are required
  //   ioCurve - data is added to this admissible curve
  void CreateQuinticAdmissibleCurveData(CATIntersectionCrvSur           * iOper,
                                        CATMathSetOfPointsNDTwoTangents * iSetR4,
                                        const CATCurve                  * iCrv,
                                        const CATCrvLimits              & iCurveLimits,
                                        int                               iSurf,
                                        const CATSurLimits              & iSurfLimits,
                                        const CATIsoParameter             iIsoPar,
                                        const CATSurParam               & iSurParamOnIso,
                                        double                            iDeltaU,
                                        double                            iDeltaV,
                                        CATSurSurResultAdmissibleCurve  * ioCurve);

  // Parameter distortion
  // --------------------

  CATBoolean ApplyParameterDistortion(const CATBoolean iAllSurfaceTypes = FALSE);
  
  CATDistortionUtility::ParamDistortionType FetchParameterDistortion(const CATSurParam    iUVRS[],
                                                                           double         oParamDistoration[], 
                                                                     const CATBoolean     iAllSurfTypes = FALSE,
                                                                     const CATSurLimits * iSurLimits = NULL) const;

  CATDistortionUtility::ParamDistortionType FetchParameterDistortion(const CATSurLimits  iSurLimits[],
                                                                           double        oParamDistortion[], 
                                                                      const CATBoolean   iAllSurfTypes) const;

  //
  // Management of equations and domain
  //
  
  void ComputeImplicitSystem() const;  // only computed once when needed --> mutable
  void ComputeDomain() const;          // only computed once when needed --> mutable
  void ComputeGlobalEquations() const; // only computed once when needed --> mutable
  
  //
  // Evaluators
  //
  
  void EvalPoint(const double iPt[4], CATMathPoint & oPtR3);
  double SquareDistancePrecision(double iUVRS [4]);
  // void EvalRatioLength (double iUVRS[4], double & oRatio);
  // void EvalRatioCone (double & oRatio);
  void HasPoleAndReduceDomain(CATLONG32 iSurf, double ioUVDomain [4]);
  
         CATLONG32 IsIdenticalPoint(const double         iPt0[4], 
                                    const CATMathPoint & iPt0R3, 
                                    const double         iPt1[4], 
                                    const CATMathPoint & iPt1R3,
                                    const CATLONG32      iIndex = -1);

  static CATLONG32 IsIdenticalPoint(const double                     iPt0[4], 
                                    const CATMathPoint             & iPt0R3, 
                                    const double                     iPt1[4], 
                                    const CATMathPoint             & iPt1R3,
                                    const CATTolerance             & iTolObject,
                                          CATGeoFactory            * iFactory,
                                          CATSoftwareConfiguration * iConfig,
                                          CATSurface               * iSurf[],
                                    const CATLONG32                  iIndex = -1);

  CATLONG32 IsPointValid(double iPt[4]);
  CATLONG32 IsPointInLoop(CATSurParam iUV[2], CATSurSurResultLoop * iLoop);

  CATLONG32 IsCurveValid(      CATMathSetOfPointsND * iSet, 
                         const CATBoolean             iTangentCheck = FALSE);
  
  CATBoolean IsCurveValid_StopInsideDomain(CATMathSetOfPointsND * iSet);

  CATBoolean IsCurveValid_ReturningPoint(CATMathSetOfPointsND * iSet);

  CATBoolean IsCurveValid_LoopCurve(CATMathSetOfPointsND * iSet);
  
  short IsPointOnAnAdmissibleCurve(const double          iPt[],
                                   const CATBoolean      iIncreaseTolForSingular = FALSE,
                                         double        * oPtOnCurve = NULL,
                                         BorderExtrem  * oBorderInfo = NULL) const;

  CATLONG32 IsPCurveValid(CATMathSetOfPointsND * iSet, 
                          CATLONG32              iNbPt, 
                          CATLONG32              iIndex,
                          double                 iStartR4[4], 
                          double                 iEndR4[4], 
                          CATLONG32            & oClosed);

  CATBoolean IsFrontierSurfIntersecting(const short iSurf, const short iFrontier);
  
  void RemoveRedundantCurves();
  void ImprovePoint(double iPoint[4], double iS0[4], double iS1[4], double oPoint[4]);
  CATBoolean RelimitCurve(CATSurSurResultCurve * iCurve0, int iStartEnd0,
                          CATSurSurResultCurve * iCurve1, int iStartEnd1,
                          CATSoftwareConfiguration *Config);
  // void CutAndCreateNewCurveSol(int iNumber, double iPt[4]);

  void CopyData4D(const double iData[], double oData[]) const;
  
  //
  //-----------------------------------------------------------------------
  //- Storage  subroutines
  //-----------------------------------------------------------------------
  //
  CATSurSurResultPoint* CreatePointSolution(      CATGeoFactory            * iFactory, 
                                                  CATSoftwareConfiguration * iConfig,
                                                  CATSurface               * iSurface1, 
                                                  CATSurface               * iSurface2,
                                            const double                     iUVRS[4], 
                                            const CATSurSurResultPointType   iPointType) const;

  CATSurSurResultPoint* DuplicatePointSolution(const CATSurSurResultPoint * iPoint);

  void StorePointSolution(CATSurSurResultPoint * iPointSol);
  
  CATSurSurResultPoint* StorePointSolution(const double                   iUVRS[4], 
                                           const CATSurSurResultPointType iPointType,
                                           const CATSurSurInitType        iInitType = UnknownInitType);

  void StoreCurveSolution(CATSurSurResultCurve * iCurveSol);
  void StoreSurfaceSolution(CATSurSurResultLoop * iSurfaceSol);

  void RemoveCurveSolutions();
  void RemoveSurfaceSolutions();

  //
  //-----------------------------------------------------------------------
  //- Debug  subroutines
  //-----------------------------------------------------------------------
  //
  //void PatInteractiveDebug(const CATMathSetOfPointsND * iPoints) const;
  //void IsoparInteractiveDebug(CATCurve * Curve) const;
  virtual void SaveSurfacesForDebug();

  // Utilities
  // ---------

  GEOPDEBUG_CMD(CATLONG32 Debug_GetPointIndex(const CATSurSurResultPoint * iPoint) const);

  // Trace
  // -----

  //GEOPDEBUG_CMD(CATUnicodeString Debug_StringFromMarchingDiagnostic(const CATMathStopDiagnostic) const);
  GEOPDEBUG_CMD(double Debug_DistanceBetween4DPoints(const double[], const double[]) const);
  GEOPDEBUG_CMD(void Debug_CheckTangentAligments(const double[], const CATLONG32, const double[]) const);
  GEOPDEBUG_CMD(void Debug_CheckForParameterDistortion() const);
  GEOPDEBUG_CMD(void Debug_PrintOperatorStatus(const CATUnicodeString&) const);
  GEOPDEBUG_CMD(void Debug_PrintCrvCrvInits() const);
  GEOPDEBUG_CMD(void Debug_PrintPtSurInits() const);

  GEOPDEBUG_CMD(void Debug_PrintPointSolutions(const CATBoolean iLongInfo = TRUE) const);
  GEOPDEBUG_CMD(void Debug_PrintConnectors(const CATCrvCell* iCells, const CATLONG32 iNumCells, const CATGeoConnectorCell* iConnectors, const CATLONG32 iNumConnectors) const);

  GEOPDEBUG_CMD(CATUnicodeString CurveIndexStr(const CATLONG32 iIndex) const);
  GEOPDEBUG_CMD(void Debug_PrintCurveSolution(CATEdgeCurve* iEdgeCurve) const);

  GEOPDEBUG_CMD(void Debug_CheckSurfaceLimitsSupport(const short iSurf) const);

  // Visual
  // ------
  
  GEOPDEBUG_CMD(void DrawPointSol(const int * iRGB = NULL) const);
  GEOPDEBUG_CMD(virtual void DrawTangents_PointSol(const int * iRGB = NULL) const);
  GEOPDEBUG_CMD(void DrawTangents(const double iParam[4], const double iTangents[4], const int * iRGB = NULL) const);
  
  GEOPDEBUG_CMD(void Debug_CheckSetOfMarchedPoints(CATMathSetOfPointsND**, const CATLONG32) const);
  GEOPDEBUG_CMD(void Debug_CheckMarchedPoints(const CATMathSetOfPointsND*, const CATBoolean, const short* iIndexInArray = NULL) const);

  //GEOPDEBUG_CMD(void Debug_PrintSetOfMarchedPoints(CATMathSetOfPointsND**, const CATLONG32) const);
  //GEOPDEBUG_CMD(void Debug_PrintMarchedPoints(const CATMathSetOfPointsND*, const short* iIndexInArray = NULL) const);

  // Function - note activating these may change the behaviour
  // ---------------------------------------------------------

  GEOPDEBUG_CMD(void Debug_SwapSurfacesInReadInput());
  GEOPDEBUG_CMD(void Debug_ConeApex_IntroduceTangentNoise(const short, const short, CATAngle&, short&) const);

  GEOPDEBUG_CMD(CATBoolean Debug_FilterSingularInit(const double[]) const);

  // Utility - useful helper functions
  // ---------------------------------

  //
  static const CATString * GetDefaultOperatorId() { return & _OperatorId; };

  //=============================================================================
  // Protected data
  //=============================================================================
  //
protected:
  // 
  // - Temporary variable : to remove when init-exit won't be treated by the same code
  //
  CATBoolean _InitExitCase, _IsMarching, _IsLock,  _AllowedAttribut;
  CATCGMAttrIsopar * _AttrSurf[2];
  CATBoolean _TgtSolveBisDone;

  //
  // Input (or default) parameters
  //
  const CATTolerance & _TolObject;
  CATGeoFactory * _ImplicitFactory;
  CATSurface * _Surf[2], * _SurfRep[2]; 
  CATSurLimits _SurLimits[2];
  double _SurfSize[2];
  CATSoftwareConfiguration * _Config;

  static const double DISTORTION_FACTOR_UPPER;
  static const double DISTORTION_FACTOR_LOWER;

  // Tolerance of admissibility
  // --------------------------

  const double _Tolerance; // initialised from _TolObject
  const double _SquareTol;

  static const double _ToleranceFactorForDegeneratePoints;
  static const double _ToleranceFactorForZeroTangentElement;

  // Search box for the intersection
  // -------------------------------

  CATMathBox _SearchInBox, _SurfBox[2];
  CATLONG32 _NbInitExit, _Limit1ToReach, _Limit2ToReach;
  
  // Options parameters
  // ------------------

  CATBoolean _LoopSearch, _ConfusionSearch, _IndexSearch, _TryAgain, _UnstableWarning,_TangentComputation;
  
  // Useful parameters (for marching)
  // --------------------------------

  mutable CATFunctionIntersectionSurSur * _ImplicitSystem;
  mutable CATMathIntervalND * _Domain;
  mutable CATMathIntervalND * _MaxDomain;
  mutable const CATMathFunctionXY * _GlobalEq[2][3];
  
  // Isopar storage
  // --------------

  CATBoolean _IsInfinite[2];
  CATBoolean _ForceBorderPLine;
  CATCurve * _Isopar[2][4];
  CATSurface * _SurfForIsopar[2];
  //
  // Curve/Curve init storage
  //
  CATLONG32 _NbCrvCrvInits;
  CATCrvCrvInit _CrvCrvInits[16];
  //
  // Corner/Surface init storage
  //
  CATLONG32 _NbPtSurInits;
  CATPtSurInit _PtSurInits[32];
  //
  // Number of indexes
  //
  CATLONG32 _NbIndexes;
  CATBoolean _FoundMissedBorders; // used for performance in ComputeIndexes
  //
  // Internal error diagnostic (an identified problem as occured)
  //
  CATLONG32 _Error;
  
  //
  // Internal data
  //
  
  CATMathSetOfPointsND * _InternalSingularPoints;
  CATMathSetOfPointsND * _MarchingConstraintPoints; // always passed to marching (cone-apex / sphere-pole etc)
  
  CATDistortionUtility::ParamDistortionType _HasParamDistortion;
  double _ParamDistortion[4];

  //------------------------
  // - Iterators parameters
  //------------------------
  //
  // For point solutions 
  //
  CATLONG32 _NbPoints, _NbAllocPoints, _IndexPoint;
  CATSurSurResultPoint ** _PointSol;
  //
  // For curve solutions
  //
  CATLONG32 _NbCurves, _NbBackUpCrv, _NbAllocCurves, _IndexCurve;
  CATSurSurResultCurve ** _CurveSol;
  CATSurSurResultCurve ** _BackUpCurveSol;
  //
  // For confused face solution
  //
  CATLONG32 _NbSurfaces, _NbBackUpSur, _NbAllocSurfaces, _IndexSurface;
  CATSurSurResultLoop ** _SurfaceSol;
  CATSurSurResultLoop ** _BackUpSurfaceSol;

  //
  // For performance optimization
  //
  CATPipeData _PipeData[2];
  CATBoolean _NonIntersection[2][4]; // non-intersection of corresponding isopar with opposing surface


  //========================================================================
  // Gestion CGMReplay
  //========================================================================
protected:
  friend class CATGeoStreamFactory; 

  // private static data
  static CATString _OperatorId;
  static CATGeoOpTimer _Timer;
   
  // Visualisation
  CATBoolean _DrawnInputGeometries;

public:

  virtual const CATString * GetOperatorId();
  //-----------------------------------------------------------------------
  //- Gestion timer 
  //-----------------------------------------------------------------------  
  virtual CATGeoOpTimer * GetTimer();

  //-----------------------------------------------------------------------
  //- Gestion Mode Record 
  //-----------------------------------------------------------------------  

  void SetNameForReplay(const CATUnicodeString&);

  virtual CATExtCGMReplay* IsRecordable(short & LevelOfRuntime, short &VersionOfStream);
  virtual void WriteInput(CATCGMStream  & os);
  virtual void WriteOutput(CATCGMStream & os);
  virtual CATBoolean ValidateOutput(CATCGMStream & ioStream, CATCGMOutput & os, int VersionNumber = 1);
          CATBoolean ValidateOutputCommon(CATCGMStream & ioStream, CATCGMOutput & os, const int iVersionOfStream, const CATBoolean iCheckData);
  
  virtual void Dump( CATCGMOutput & os );

  CATBoolean VisualizeGeometry() const;

  virtual void DumpOutput(CATCGMStream& ioStream, CATCGMOutput& os,int VersionNumber=1);
  virtual void DumpOutput(CATCGMOutput & os);
  virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);

  void DrawSurfaceBorders(const CATSurLimits   iLimits[], const int* iRGB) const;
  void DrawSurfaceBorders(const short iSurf, const CATSurLimits & iLimits,   const int* iRGB) const;

  void DrawSearchInBox() const;

  static CATGeoODTScaleManager* ReadStreamHeaderInfo(      CATCGMStream              & ioStream,
                                                     const short                       iVersionOfStream,
                                                           CATGeoFactory            *& oFactory,
                                                           CATSurface               *& oSurf1,
                                                           CATSurface               *& oSurf2,
                                                           CATSoftwareConfiguration *& oConfig,
                                                           CATBoolean                & oIsSSGenOper);

  virtual void ReadInput(      CATCGMStream          & ioStream,
                         const int                     iVersionOfStream,
                               CATGeoODTScaleManager * iScaleManager);

  protected:

    virtual CATBoolean IsSurSurGenOperator() const;

    CATUnicodeString _NameForReplay;

  public:

  //private:
  void SetSoftwareConfiguration(CATSoftwareConfiguration* iSoftwareConfiguration);
};

//--------------------------------------------------
// Global functions and utilities
//--------------------------------------------------
ExportedByY30C3XGG int DebugCheminement();
#endif
