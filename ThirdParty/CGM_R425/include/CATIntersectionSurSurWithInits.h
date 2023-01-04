/* -*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATIntersectionSurSurWithInits.h
// interface of surface sweep intersection class
/**
 * Interface representing the operator of the intersection of two CATSurfaces
 * to build the sweep surface.
 *<br>The operator offers the isolated solutions (curves) and the
 * confusion solutions (surfaces).
 *<ul>
 *<li>The CATIntersectionSweep operator is designed to be open to external 
 * implementations.
 *<li>It is created with the <tt>CreateIntersection</tt> method within a 
 *<tt>CATGeoFactory</tt>, but is not streamable. 
 *<li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed. 
 *<li>In case of <tt>ADVANCED</tt>
 * mode, the user may precise options with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method.
 *<li>The results are accessed thanks to iterators, that allow to handle
 * multiple solutions.
 *<li> The operator is removed from the memory with the <tt>Remove</tt> method.
 *</ul>
 */
//
//=============================================================================
// Usage Notes:
//
//  This is an abstract class to handle implementation by ObjectOriented way
// for boolean operation
//=============================================================================
//   /02/99 STY Creation                                   S.Tremey
//   /12/97 CKN Documentation                              C. Keribin
// 01/12/08 NLD Utilisation de CATCGMOperatorDebug pour outillage standard de debug/mesure
// 14/02/11 NLD Ajout Init()
//              _MinStep         remplace _minstep
//              _Guides_Mode     remplace _guides_mode
//              _NbDirtyInit     remplace _InitCrad
//              _NbTangentInit   remplace _TangentInit
//              _StartingVectors remplace _startingvectors
//              Reordonnancement logique des variables pour facilite d'acces au debugger,
//              et ajout de quelques __________________________MileStone*
//              Suppression _numberOfResults
// 15/11/11 XMH Replaced _FilletSpec, _SweepTopoSpec and _InterOp spec by enum _IntersectionSpec
// 08/05/12 Q48 Moved CheckInclusionInRefCurve to CATIntersectionSurSurTg
// 17/05/12 XMH Add SetExitSingular
// 19/11/12 Q48 IR 176404: added handling of duplicate init points
// 18/01/13 R1Y Added functionality for help points (under PS_Direct_Singular_HelpPoints).
// 15/03/13 Q48 Moved Debug function DrawTangents to SurSurGen
// 12/04/13 Q48 Update to use CATIntersectionSurSurGen::CATSurSurResultPointType enum
// 18/04/13 Q48 Change #ifdef PS_Direct_Singular_HelpPoints to environment variable InterOp_SSWI_HelpPoints
// 25/04/13 Q48 Refactor reconvergence (public method for InterOp); enhance near-singular reconvergence
// 13/05/13 Q48 Modifications for InterOp: singular point marchable classification and help point mechanism
// 10/07/13 Q48 Fix to tangent-solve mechanism (IntersectionSurSurWithInits_TangentSolve)
// 11/07/13 Q48 Add Set / Get methods for temporary G2-Fillet mode
// 31/07/13 Q48 Development for G2-Fillet project (IntersectionSurSur_SingularPointTangentsSecondOrder)
// 02/09/13 Q48 Development for SurSurTg project (SSWI post-processing remaining inits)
// 01/10/13 Q48 Add scalar product utility function for multi-surface intersection
// 02/10/13 Q48 Add IsAPointTangentToBorder for multi-surface intersection
// 09/10/13 Q48 Update to InterOp check for "init-off-surface" cases
// 10/10/13 Q48 Stablise singular / pseudo-singular point reconvergence
// 10/10/13 Q48 Fix to deformation mechanism when marching both ways from an init
// 10/10/13 Q48 Add debug code to check the internal consistency of result curves
// 23/10/13 Q48 Add more utility methods for InterOpSpec
// 24/10/13 Q48 Add _ReverseResultOrientation for directional output for InterOp
// 30/13/13 Q48 Moved common visual debug functions to SSGEN for use there
// 31/10/13 Q48 Add functionality to correct end tangents of curves ending at singular points
// 03/12/13 Q48 Add more utility methods for IntersectionMultiSurface
// 17/12/13 Q48 Add utility and debug methods
// 04/03/14 R1Y Add GetMarchingDiagnostic()
// 18/03/14 Q48 Add utility method FindBestTangentIndex for MultiSurface
// 24/03/14 Q48 Add _IntersectionSpecVersion for G2-Fillet "temporary" mechanism
// 27/05/14 Q48 X-scale migration - remove access to default constructor
// 11/06/14 Q48 Implement X-scale in replay mechanism
// 23/09/14 Q48 Enhancements to param-distortion mechanism for PS-Direct IR317503
// 20/10/14 Q48 Add methods for choice of P-line support in ConnectOneInitExit
// 22/10/14 Q48 Removed help points reading / writing from replay
// 22/10/14 Q48 Utility methods for InterOpSpec
// 14/11/14 Q48 Fix to replay mechanism to avoid SSGen / SSWI type confusion
// 19/03/15 Q48 New method to manage calls to SurSurTg
// 01/04/16 Q48 New reconvergence methods and internal class
// 29/09/16 Q48 Add method to switch curve iterator to specific solution curve
// 21/04/17 PKC compilation warning
// 21/05/18 Q48 Restructure of SurSurTgBloc for multi-guides project
// 14/11/18 Q48 Small tidy of deformation point data structure
// 19/11/18 Q48 Utility methods to launch confusion between unprocessed singular inits
// 28/01/19 Q48 Add versioning to PS-Direct method ComputeInitTangents
// 10/04/19 Q48 Added IntersectionSpecExtrapol for IR-671945
// 04/07/19 Q48 Add some CATGeoOverride
// 13/11/19 Q48 Migrated some IsPointOnBorder methods to SurSurGen
// 12/06/20 Q48 Small method refactor
// 21/08/20 Q48 Multi-guide convergence: tolerances and init processing after SSTg
// 09/09/20 Q48 Update to signature of SetIntersectionSpec and add some CATGeoOverride
// 08/04/22 Q48 Remove ReachBoundaryOf (duplicate of method in SurSurGen)
// 02/08/22 Q48 IR-968231: Signature correction in RecordTangentSolveResult_TidyForReturn
//=============================================================================

#ifndef CATINTERSECTIONSURSURWITHINITS_H
#define CATINTERSECTIONSURSURWITHINITS_H

// #define CATIntersectionSurSurWithInits_KeepOldConstructor

#include "Y30C3XGG.h"

//#define _DeformFillet

#include "CATIntersectionSurSurGen.h"
class SurSurTgBloc;
class CATIntersectionSurSurTg_InitSetInfo;
#include "CATIntersectionSign.h"

// System
#include "CATUnicodeString.h"

// Utlities
#include "CATGeoOpVirtual.h"

// Geometric Objects
#include "CATPointOnEdgeCurve.h"
#include "CATSetOfCrvParams.h"
#include "CATCrvLimits.h"
#include "CATSetOfCrvParams.h"

// Mathematics
#include "CATMathDiagnostic.h"
#include "CATMathBox.h"
#include "CATMathIntervalND.h"
#include "CATMathStopDiagnostic.h"
#include "CATMathSetOfLongs.h"
#include "CATCGMNewArray.h"

// Geometric operators
#include "CATCreateIntersectionSurSurWithInits.h"

// Debug
#include "CATGeoOpDebug.h" // must be included to get #define GEOPDEBUG to be propagated here
#include "CATCGMOperatorDebug.h"

class CATSurface;
class CATCartesianPoint;
class CATPointOnSurface;
class CATCurve;
class CATPCurve;
class CATEdgeCurve;
class CATGeoFactory;
class CATMathSetOfPointsND;
class CATMathSetOfPointsNDTwoTangents;
class CATMathSetOfPointsNDWithVectors;
class CATMathFunctionXY;
class CATMathSystemSpecialPoints;
class CATSurLimits;
class CATSurSurResultPoint;
class CATSurSurResultCurveWithInits;
class CATMathAttrList;
class CATIntersectionSurSurTg;

class CATGeoODTScaleManager; // Q48 (06/2014): X-scale

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class istream;
#endif
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ofstream;
#endif

struct CATStartingPointsInputBloc 
{
  CATSetOfSurParams     SetOfInit1;
  CATSetOfSurParams     SetOfInit2;
  CATIntersectionSign * SignOnSurf1;
  double              * Tangents;
  CATBoolean            LoopSearch;
  void Reset(CATLONG32 i);
};

class ExportedByY30C3XGG CATIntersectionSurSurWithInits : public CATIntersectionSurSurGen
{
 public:

/**
 * Constructor.
 */
  CATIntersectionSurSurWithInits(CATGeoFactory            * factory,
                                 CATSoftwareConfiguration * iConfig,
                                 CATSurface               * iSurface1,
                                 CATSurface               * iSurface2);

#ifdef CATIntersectionSurSurWithInits_KeepOldConstructor
  // please always use a CATSoftwareConfiguration (previous CTOR)
  CATIntersectionSurSurWithInits( CATGeoFactory * factory,
                                  CATSurface    * iSurface1,
                                  CATSurface    * iSurface2);
#endif

private:
  CATIntersectionSurSurWithInits(); // not to be used (even for CGMReplay) - this is not X-scale compliant

public:
  CATCGMNewClassArrayDeclare;        // Pool allocation

/**
 * Destructor.
 */
   virtual ~CATIntersectionSurSurWithInits();

   CATCGMOperatorDebugDeclareRun(CATIntersectionSurSurWithInits,CATIntersectionSurSurGen);

  //-----------------------------------------------------------------------
  //- Iterators management
  //-----------------------------------------------------------------------

  // Switch the curve iterator to match a particular edge curve from a result curve
  CATBoolean SwitchToCurve(const CATEdgeCurve*);

  //-----------------------------------------------------------------------
  // Warning: these three methods should only be called after calling GetEdgeCurve
  //-----------------------------------------------------------------------
  // Returns the set of crvparam corresponding to the singularities of the
  // curve considered.
  void GetSingularPoints(CATSetOfCrvParams *& oSetOfSingParams);

  // Returns the set of crvparam corresponding to the inits/exits on the 
  // curve considered, in the inital order given by SetStartingPoints.
  void GetExitPoints(CATSetOfCrvParams *& SetOfExitParams);

  // Returns the crvparam corresponding to the init/exit with index ExitNumero 
  void GetExitPoint(CATLONG32     ExitNumero,
                    CATCrvParam & ExitParam);
  //-----------------------------------------------------------------------

  // Returns the set of the numbers of init/exits traversed by the curve,
  // in the chronological order of traversal.
  CATMathSetOfLongs * GetExitNumero();

/**
 * Modifies the CATSurfaces limits to be taken into account by the CATIntersectionSurSurWithInits
 * operator.
 *<br> It does not change the current CATSurfaces limits. 
 *     The proposed limits have to be included in the current limits.
 *<br> With a NULL pointer, the current limits of the surface is used.
 *<br> The <tt>Run</tt> method then should be called before reading the solutions.
 */
   virtual void SetLimits(CATSurLimits  * iNewLimitsForSurface1,
                          CATSurLimits  * iNewLimitsForSurface2);

    /* Method to Specify the point from which a solution begins or ends     */
    /* GlobalParams are iNumberOfStartingPoints quadruplets (u1,v1,u2,v2)   */
    /* The CATIntersectionSign should be provided for each StartingPoint    */
    /* it represents the signature of the expected solution passing through */
    /* the corresponding StartingPoint on the first surface operand         */

/**
 * Imposes initial and/or final points of the resulting surface of
 * a CATIntersectionSurSurWithInits operator. 
 *<br>In case of <tt>ADVANCED</tt> mode.
 * @param iSetOfInitParamsOnSurface1
 * The pointer to a CATSetOfSurParam containing initial and/or final
 * points of the solution on the first surface.
 * @param iSetOfInitParamsOnSurface2
 * The pointer to a CATSetOfSurParam containing initial and/or final
 * points of the solution on the second surface, they should be identical in
 * space with those of the previous CATSetOfSurparam.
 *<br> This argument and the following one give the 
 * definition of the pieces of the CATIntersectionSurSur.
 * @param iStartingSignatureOnFirstSurface
 * The driving direction of the intersection edge on the first surface
 * with regards to each surface
 * normals at each points of <tt>iSetOfInitPoints</tt>.
 * The natural way of the intersection edge at the starting point
 * is such that the tangent at this point has the same direction as the
 * vector product of the normals of each surface. 
 *<br>Consider that the surface normal represents the outside of the matter
 * delimited by a surface. A positive signature implies that the resulting 
 * matter of the intersection is on the edge left.
 * <dl><dt><tt>CATIntersectionSignPositive</tt><dd>The resulting 
 * matter of the intersection is on the edge left.
 *     <dt><tt>CATIntersectionSignNegative</tt><dd>The resulting 
 * matter of the intersection is on the edge right.
 *     <dt><tt>CATIntersectionSignSameDirection</tt><dd> 
 *     <dt><tt>CATIntersectionSignOppositeDirection</tt><dd>
 *     <dt><tt>CATIntersectionSignUnknown</tt><dd>
 *     <dt><tt>CATIntersectionSignUnset</tt><dd></dl> 
 * @param iTangents
 * When the signature is NonCrossing type, a dimension 3 vector 
 * has to be given to indicate the starting direction.
 *<br> The <tt>Run</tt> method then should be called before reading solutions.
 */

  virtual void SetStartingPoints(CATSetOfSurParams   & iSetSurParam1, 
                                 CATSetOfSurParams   & iSetSurParam2,
                                 CATIntersectionSign * iSignatureOnFirstSurface=0,
                                 double              * iTangents = NULL, 
                                 CATBoolean            LoopSearch = TRUE);

  void AddStartingPointCluster(const CATLONG32           iIndexPreferredInit,
                               const CATMathSetOfLongs & iListInitsInCluster);

  class InitCluster
  {
  public:
    InitCluster(const CATLONG32 iIndexPreferredInit, const CATMathSetOfLongs & iListInitsInCluster);
    ~InitCluster();

    CATLONG32 GetPrincipalIndex() const;

    void Beginning() const;
    CATBoolean Next(CATLONG32 & oIndex) const;

    CATBoolean Contains(const CATLONG32   iTestIndex,
                              CATLONG32 & oIndex) const;

  private:
            CATLONG32 _PrincipalInitIndex;
    mutable CATMathSetOfLongs _ClusterInitIndices;
  };

  class InitClusterList
  {
  public:
    InitClusterList();
    ~InitClusterList();

    int Size() const;

    void AddCluster(const InitCluster*);
    const InitCluster* GetCluster(int iIndex) const;

    void ClearList();

  private:
    CATListPV _ListClusters;
  };

  // Method to reconverge (relax) the input point to the intersection of the two surfaces. The
  // input must be a 4D array (UVRS) of the surface parameters to be reconverged.

  class ReconvStatus
  {
  public:

    /*typedef*/ // PKC 21/04/2017 useless typedef in C++, compilation warning 
    enum ReconvStatusFlag { ReconvUnknown, ReconvKO, ReconvOK };
    /*typedef*/ // PKC 21/04/2017 useless typedef in C++, compilation warning 
    enum ReconvStatusDist { ReconvNotMoved, ReconvMoved, ReconvMovedFar, ReconvMovedVeryFar };

    ReconvStatus();
    ReconvStatus(const ReconvStatus &);
    ReconvStatus(const ReconvStatusFlag iFlag);
    ReconvStatus(const ReconvStatusFlag iFlag, const ReconvStatusDist iDist);
    ~ReconvStatus();

    void SetData(const ReconvStatusFlag iFlag, const ReconvStatusDist iDist);
    void SetData(const ReconvStatusFlag iFlag);

    CATBoolean IsSet() const;

    CATBoolean IsOK() const;
    CATBoolean IsKO() const;
    CATBoolean IsMoved() const;
    CATBoolean IsMovedFar() const;
    CATBoolean IsMovedVeryFar() const;

    void SetDistanceSq(const double iDistSq);
    double GetDistanceSq() const;
    double GetDistance() const;

    GEOPDEBUG_CMD(CATUnicodeString DebugStatus() const);

  private:

    ReconvStatusFlag _ReconvStatusFlag;
    ReconvStatusDist _ReconvStatusDist;

    double _DistanceSqMoved3D;
  };

  virtual ReconvStatus ReconvergeStartingPoint(double   ioInitPt[],
                                               double * oDistSq4D = NULL);

  // Test whether this operator can march out of the given singular point. The input is a 4D
  // (UVRS) array of the starting point. The return CATBoolean indicates whether the point can
  // be marched from. If it can be marched from, the other outputs give the number of tangents
  // (CATLONG32&), up to three 4D tangent directions (double[]) and whether the init is at the 
  // pole of a surface (CATBoolean&).

  void ComputeInitTangents(const double       iInitPt[],
                                 CATLONG32  & oNumTangents, 
                                 double       oTangents[],
                                 CATBoolean & oSingularInitIsConfused,
                                 CATBoolean & oSingularInitAtPole,
                                 CATBoolean & oClassification,
                           const short        iVersionMode);

  CATBoolean ComputeInitTangent(const double iInitPt[],
                                      double oNonSingularTangent[]);

  CATMathStopDiagnostic GetMarchingDiagnostic() const;

  // Test if any of the PointSolution tangents are similar to the supplied guide tangent
  CATBoolean AreInitPointTangentsSimilarToGuide(const CATMathVector & iGuideTangent);

  void ComputePoint3D(const double         iPt4D[],
                            CATMathPoint & oPt3D) const;

  CATBoolean Compute3DTangentFrom4DTangent(const double          iInitPt4D[], 
                                           const double          iTgt4D[],
                                                 CATMathVector & oTgt3D);

  CATBoolean Compute4DTangentFrom3DTangent(const double          iInitPt4D[], 
                                           const CATMathVector & iTgt3D,
                                                 double          oTgt4D[]);

  double ComputeScalarProductBetweenTangent4DAndGuide(const CATMathVector & iGuideDirection,
                                                      const double          iPoint4D[], 
                                                      const double          iTangent4D[]);

  double ComputeScalarProductBetweenTangent2DAndGuide(const CATMathVector & iGuideDirection,
                                                      const short           iSurfIndex,
                                                      const double          iPoint2D[], 
                                                      const double          iTangent2D[]);
 
  short FindBestTangentIndex(const double[], const double[], const CATLONG32, CATBoolean &);

  // Test if the input point (4D array UVRS) lies on the intersection
  CATBoolean IsAnIntersectionPoint(const double iInitPt[]);

  CATBoolean IsAPointOnBorder(const double         iPt[],
                                    BorderExtrem * oSaturatedVar = NULL) const;

  CATBoolean IsPointTangentToBorder(const double       iPt[], 
                                    const double       iTgt[], 
                                          CATBoolean * oTgtBorder = NULL) const;

  CATBoolean IsPointCrossingABorder(const double iPt[],
                                    const double iTgt[]) const;

  // Check whether the currect curve stops / starts on a singular point which isn't an init.
  CATBoolean CheckStopOnNonInitSingularity();
  CATBoolean CheckStartOnNonInitSingularity();

  // Method to allow the operator to know when an InterOp help point is being used
  void SetUsingInterOpHelpPoint(const CATBoolean iUseHelpPoint);

  // Cette methode renvoie un setofpointsND des inits passees en entrees.
  // This method returns a CATMathSetOfPointsND of inits.
  // Very useful when the reconvergence of inits is requested.
  CATMathSetOfPointsND * GetInitPoints();
  CATMathSetOfPointsNDWithVectors *GetResult() const;

  /*
  // Triggers the method ComputeTangentIntersection in the normal run between precise inits with the specified indices.
  // For example, if Init1 = {2,3,4} and Init2 = {1,0,5}, then we will attempt to find the tangent solutions
  // between 2 and 1, 3 and 0, 4 and 5.
  void SetConnectInit(CATMathSetOfLongs *Init1, CATMathSetOfLongs *Init2);
  // Calculate the tangent solutions
  void ComputeTangentIntersection(CATSetOfSurParams &iSetSurParam1, CATSetOfSurParams &iSetSurParam2,
                                  CATCurve *iCurve1 = NULL, CATCurve * iCurve2 = NULL);
  */

  void SetIgnoreConfusedSurfaces();

  ///**
  // * Extrapolates the CATIntersectionSurSur solution until one of the operands boundary.
  // *<br>This method has priority on the <tt>HoldDomain</tt> method: the solution
  // * can go outside the domain defined by <tt>HoldDomain</tt>.
  // *<br> The <tt>Run</tt> method then should be called before reading solutions.
  // */
  //   void ReachBoundaryOf(CATSurface * iSurface);
  //  /* IndexOperand should have the value 0 or 1 */
  //  /* same method than previous for StartingPoints */
  //  /* on the same surface intersection itself      */
  //   void ReachBoundaryOf(CATLONG32 IndexOperand);

/**
 * Do not use. For specific use only
 * Authorize solutions close to a boundary to go out of the domain
 */
  void SetExtrapol(CATBoolean iBoolean);
  // Mode pour sro
  virtual void SetNonCutting(CATBoolean iDoNotCut = 1) CATGEOOverride;
  virtual void SetOnlyBetweenInits(CATBoolean iOnlyBetweenInits = 1) CATGEOOverride;
  virtual void SetPerfoMode(CATLONG32 iPerfoMode = 1);
  virtual void SetExtrapolation(CATBoolean iExtra = 1);
  virtual void SetExtrapolationValue(double iTol);
  virtual void SetOnlyTangentComputation(CATBoolean iTangent = 1);
  // Mode pour chu
  virtual void SetConvergeInit(CATBoolean iReconv = 1) CATGEOOverride;
  // Sty week 49/05 recallage des inits si a moins de la resolution du bord
  virtual void SetRecalInit(CATBoolean iRecal = 1);
  virtual void SetRespectSignature(CATBoolean iRespect = 1);
  CATLONG32 AreThereSingularities();
  CATBoolean AreSurfacesConfused();
  
  // Mode pour ASE
  virtual void SetTangentSol(CATBoolean iTanSol = 1) CATGEOOverride;

  // Note: iSpecVersion only taken into account in InterOpSpec
  virtual void SetIntersectionSpec(const CATIntersectionSpec iIntersectionSpec,
                                   const CATLONG32           iSpecVersion = -1) CATGEOOverride;
  
  CATIntersectionSpec GetIntersectionSpec() const;
  
  virtual void ResetOptionsInterOp();

  virtual void SetForceWithInits(); // For InterOpSpec
  virtual void SetForceTryConfusion(); // For InterOpSpec

  virtual void SetReverseResults(const CATBoolean iReverse = TRUE);
  CATBoolean GetReverseResults() const;

  virtual void SetTemporaryG2FilletMode(const CATBoolean iMode);
  CATBoolean GetTemporaryG2FilletMode() const;
  
  virtual void SetExitSingular(const CATBoolean iExitSingular);

  // Mode for PRL Only
  // User can reset Checking Ovelapping Surface 
  // Warning: In this case you should ensure that the surfaces overlap, 
  // to have a stable behaviour and to increase performance
  void SetCheckSurfsOverlap(CATBoolean CheckSurfsOverlap);
  
  // *** SHL only ***
  // Activate SurSurTg mode: please also refer to the usage notes
  // of CATIntersectionSurSurTg.
  // The order of the inits passed via SetStartingPoints must respect
  // the convention of CATIntersectionSurSurTg, with init 0 
  // corresponding to the Start limit and init 1 corresponding to the
  // End limit.
  // The start_type and end_type shorts: 0 for smooth and 1 for
  // sharp. Beware: a sharp-type init will be reconverged by the
  // operator (of course, such reconvergence should normally induce
  // a very small movement); a smooth-type init will be left
  // untouched, but it must have a diametre < resolution or the
  // operator will reject it.
  // The PCurve iInitPCrv must lie on a surface belonging to the
  // equivalence class of the corresponding iSurface under the
  // equivalence relation generated by "surface A is an offset of
  // surface B".

  // deprecated: use the version below

  // Activate SurSurTg (guide PCurves) mode

  // 1. The guide curves must be given in the same order as the surfaces.
  //    You must pass CrvLimits along with the PCurves. You can omit at
  //    most one PCurve (pass null pointers). The PCurves don't necessarily
  //    lie on the intersected surfaces : the PCurve iGuidePCrv must lie
  //    on a surface belonging to the equivalence class of the corresponding
  //    iSurface under the equivalence relation generated by "surface A is
  //    an offset of surface B".

  // 2. As with the CATIntersectionSurSurTg operator, there are a start and
  //    an end side of the guides, which are determined by the orientation
  //    of Guide1 (Guide2 if there's no Guide1). At each end of the guides,
  //    you must pass an index (istart_index, iend_index). If it's a smooth
  //    end, pass the index of the corresponding init as given to
  //    SetStartingPoints; otherwise, pass -1.
  //    ----> you must provide one init at each _smooth_ end of the guides;
  //          if you don't, the operator will reject the input and fail.
  // In the case where the user wants us to take into account inits 
  // that don't map to the guide pcurves, and for which we will try a  
  // pline-pline solution (between the init and the extremity of guide pcurves)
  // then the index and type must be provided
  //   type = -1 point is the start of the guide pcurve
  //   type =  1 point is the end of the guide pcurve 
  //   type = -2 point to the side of the start of the guide pcurves
  //   type =  2 point to the side of the end of the guide pcurves  
  // In the case where the user wants to provide interior inits which could be points of singularity 
  // then the user must provide the SetOfCrvParam1 and SetOfCrvParam2 that correspond to the 4 parameter values for the type
  // dans le cas ou l'utilisateur veut fournir des inits interieurs qui seraient eventuellement des points de singularite    
  // l'utilistateur doit fournir les SetOfCrvParam1 et SetOfCrvParam2 ce cas correspond a la valuer 4 de paramtre Type
  //   type =  0 interior point
  //   type =  3 inconn
  
  void UseGuidePCurves( CATPCurve          * iGuidePCrv1, 
                        CATPCurve          * iGuidePCrv2,
                        const CATCrvLimits * iCrvLimits1,
                        const CATCrvLimits * iCrvLimits2,
                        short                iOriPC2vsPC1, 
                        double               itol,
                        short                istart_index, 
                        short                iend_index,
                        double             * iqualitytol  = NULL,
                        short                iMayTryAgain = -1);

  // Sometimes users need an intersection within a precision iTol between inits and a larger precision (iqualitytol) elsewhere 
  // new dedicated interface for extrapolation Cf. OBH /DPS, 
  // index table of indices of inits 
  // Type_Guid_Pos displacements of inits
  //----------------------------|(-2)-----[(-1)----------|(0)-----------](1)-----|(+2)
  // SetOfCrvParam1 crvsparams inits of the first pcurve  (pour les inits out on mettra le crvparam de l'init(out/start) extremite des pcurve guides)
  // SetOfCrvParam2            inits of the second pcurve (pour les inits out on mettra le crvparam de l'init(out/start) extremite des pcurve guides)
  // si l'uitlisateur souaite que l'extrapolation de l'edge curve ne soit deforme (quitte a decouper sur l'extremite des pcurve guides )
  // sur la zone des intra guides il doit utiliser l'option SetRespectShapeOut; 
  void UseGuidePCurves( CATPCurve          * iGuidePCrv1, 
                        CATPCurve          * iGuidePCrv2,
                        const CATCrvLimits * iCrvLimits1,
                        const CATCrvLimits * iCrvLimits2,
                        short                iOriPC2vsPC1, 
                        double               itol,
                        double             * iqualitytol,
                        CATMathSetOfLongs  * index          = NULL, 
                        CATMathSetOfLongs  * Type_Guid_Pos  = NULL,
                        CATSetOfCrvParams  * SetOfCrvParam1 = NULL,
                        CATSetOfCrvParams  * SetOfCrvParam2 = NULL,
                        short                iMayTryAgain   = -1);

  //Pour que l'extrapolation de l'edge curve ne soit Pas deforme 
  //sur la zone des intra guides (quitte a decouper sur l'extremite des pcurve guides )
  void SetRespectShapeOut(CATBoolean iRespectShapeOut);

  CATBoolean IsSingularPoint(const double * iXPt);
  CATBoolean IsInSingularNeighbourhood(const double * iXPt);
  CATBoolean CheckDistinctHelpPoint(const CATSurParam[], const CATSurParam[]);

  int ComputeMyUniqueTangentVector(CATMathVector * oVector);

protected:

  void Run2();
  void Reset(CATBoolean iKeepCurveSol = FALSE);
  void MultiMarching();
  void MultiMarchingFillet();

  CATBoolean MultiMarchingFillet_FilletContact();

  // Utility functions
  CATBoolean IsAnIntersectionPoint(const CATSurSurResultPoint * iInitPoint,
                                   const CATBoolean             iLargeTol = FALSE);

  CATBoolean IsAnIntersectionPoint(const double     iInitPt[],
                                   const CATBoolean iLargeTol);

  // Computations issued from a single starting point
  CATLONG32 SingleComponentMarching(CATSurSurResultPoint * iStartPoint);
  void SingleComponentMarchingFillet(CATSurSurResultPoint * iStartPoint);
  void TryJokerSolution(CATSurSurResultPoint * Init);
  void TryWithLargerDomain(CATSurSurResultPoint * Exit);

  // Intersection curve-surface
  void IntersectFrontierSurface(const CATLONG32         iSurf, 
                                CATCurve              * iFrontier,
                                CATLONG32               iPointIndex, 
                                const CATIsoParameter   iIsoPar,
                                const CATBoolean        iReverse,
                                const CATSurParam     & iSurParamOnIso);

  void RemoveDuplicatePoints();
  void EliminateClusterInits(const CATLONG32 iParentPointIndex);

  CATLONG32 CleanSolutions() CATGEOOverride; // Clean redundant solutions

  CATBoolean AreInitListsTheSame(const CATMathSetOfLongs * iCurveInitList0,
                                 const CATMathSetOfLongs * iCurveInitList1) const CATGEOOverride;

  CATBoolean AreInitListsJoined(const CATLONG32  iCurveIndex1,
                                const CATBoolean iCurveOrientation1,
                                const CATLONG32  iCurveIndex2,
                                const CATBoolean iCurveOrientation2) const;


private:

  // Options:
  //
  CATLONG32 __________________________MileStoneOptions;
  CATBoolean _CheckSurfsOverlap, _Guides_Mode, _RespectShapeOut;
  
  CATBoolean _DoNotCut;
  CATBoolean _NotUntilBorder;
  CATBoolean _Reconv;

  CATBoolean _Recal;
  CATBoolean _OnlyTangentComputation;
  CATBoolean _AllowTryConfusion;
  CATBoolean _ForceTryConfusion;
  CATBoolean _BorderBifurcate;

  CATIntersectionSpec _IntersectionSpec;
  CATLONG32           _IntersectionSpecVersion;

  // This flag controls whether to reverse the result curve objects (for InterOp spec which has a direction)
  CATBoolean _ReverseResultOrientation;

  CATBoolean _ExitSingular;
  CATBoolean _PerfoMode;
  CATBoolean _TangentSol;
  CATBoolean _RespectSign;
  CATBoolean _ExtrapolationAllowed;
  double     _ExtrapolationValue;

  int       __________________________MileStoneDeformData;
  
  CATBoolean _HasDeformationPts;
  CATLONG32  _DeformNbSol;
  double     _DeformPoint[4];

  int       __________________________MileStoneInits;
  CATLONG32 _NbInitialInitPoints;
  CATLONG32 _NbInitialInitPointsValid;
  CATLONG32 _IndexFirstInitPointValid;
  CATLONG32 _IndexSecondInitPointValid;
  CATLONG32 _NbTangentInit, _NbDirtyInit;
  
  CATMathSetOfPointsND * _EndPointsForMarching;

  CATMathSetOfPointsND * _InitPoints;
  CATMathSetOfPointsND * _ReconvergedUserInitPoints;
  CATMathSetOfLongs    * _ReconvergedUserInitPointsMapping;
  CATLONG32              _NbInitExitCache;
  CATLONG32              _NbDuplicateInits;

  CATBoolean             _HasInitPointSignature;
  CATMathSetOfLongs _ReconvergedInits;
  
  CATStartingPointsInputBloc _InputBloc;

  CATBoolean                 _TreatInitClusters;
  InitClusterList            _InitClusters;

  double * _StartingVectors;

  CATDistortionUtility::ParamDistortionType _InitIsDistorted;
  double _InitDistortion[4];

  CATBoolean _UsingInterOpHelpPoint;

  CATLONG32 __________________________MileStoneOthers;
  double _MinStep, _MaxStep;
  CATBoolean _MinStepFromInitSeparation;


  int       __________________________MileStoneResultManagement;
  
  // CATLONG32 _Orientation,
  CATLONG32 _PlnCyl;
  CATLONG32 _Confusion, _PointIndex;
  int _SizeOfArrayOfSetOfPoints;
  // CATLONG32 _numberOfResults;
  CATMathSetOfPointsNDWithVectors **_resultSets;

  SurSurTgBloc * _SurSurTgBloc; // Defined in CATIntersectionSurSurTgInitData
  CATBoolean     _SurSurTgSuccess;

  int       __________________________MileStoneTolerance;
  static const double _MaxAngle_SimilarTangents;

  //-----------------------------------------------------------------------
  void Init();

  CATBoolean IsDefaultSpec() const;
  CATBoolean IsFilletSpec() const;
  CATBoolean IsSweepTopoSpec() const;
  CATBoolean IsInterOpSpec() const;
  CATBoolean IsExtrapolSpec() const;

  short UseSecondOrderSingularTangents() const;
  CATBoolean ComputeSecondOrderSingularTangents() const;

  CATMathSetOfPointsND * DoGetInitPoints() const;

  struct Border
  {
  enum CrossingInfo { Unknown = 0, Inside, Along, Outside };
  };

  CATBoolean ClassifyBorderPointTangent(const double                 iPt[], 
                                        const double                 iTgt[], 
                                              CATBoolean           & oBorderTangentPoints,
                                              CATBoolean           & oBorderOutsideCrossingPoints,
                                              CATBoolean           & oBorderInsideCrossPoints,
                                              Border::CrossingInfo * oCrossing = NULL) const;

  void TreatCaseOfAlignedExit();

  // Methods for the reconvergence of init points
  virtual ReconvStatus DoStartingPointReconvergence_Bifurcation(const CATMathIntervalND & iDomain,
                                                                      double              ioInitPt[],
                                                                      CATMathDiagnostic & oDiag,
                                                                const CATBoolean          iIsOnBorder = FALSE);

  virtual ReconvStatus DoStartingPointReconvergence_Bifurcation2(const CATMathIntervalND & iDomain,
                                                                       double              ioInitPt[],
                                                                       CATMathDiagnostic & oDiag);

  virtual ReconvStatus DoStartingPointReconvergence_HyperPlane(const CATMathIntervalND & iDomain,
                                                                     double              ioInitPt[],
                                                                     CATMathDiagnostic & oDiag,
                                                               const CATBoolean          iAlwaysUpdate = FALSE);

  virtual ReconvStatus DoStartingPointReconvergence_Combined(const CATMathIntervalND & iDomain,
                                                                   double              ioInitPt[]);

  virtual ReconvStatus ReconvergeStartingPoint(double ioInitPt[], const CATIntersectionSign iSign);
  virtual ReconvStatus ReconvergeStartingPoint1(double ioInitPt[]);
  virtual ReconvStatus ReconvergeStartingPoint2(double ioInitPt[], const CATIntersectionSign iSign);
  virtual ReconvStatus ReconvergeStartingPoint3(double ioInitPt[], const CATIntersectionSign iSign);
  virtual ReconvStatus ReconvergeStartingPoint4(double ioInitPt[], const CATIntersectionSign iSign);

  virtual void FillReconvergenceStatus(const double              iPt4D_Before[],
                                       const double              iPt4D_After[],
                                       const CATMathDiagnostic & iDiag,
                                             ReconvStatus      & ioStatus) const;

  short PickTangentForReconvergence(const double    iInitPt[], 
                                    const CATLONG32 iNumTgts,
                                    const double    iTgts[]) const;

  virtual CATBoolean TestIfInitHasMoved4D(const double   iOrigPt[],
                                          const double   iReconvPt[]) const;
  virtual CATBoolean TestIfInitHasMoved3D(const double   iOrigPt[],
                                          const double   iReconvPt[],
                                                double * oSqDist = NULL) const;

  CATLONG32 Orientation(const double startingPoint[4], 
                        const int    PointIndex,
                              double startingTangent[4]);

  CATBoolean ComputeLastSegmentDirection(const CATMathSetOfPointsNDWithVectors & iSol,
                                               double                            oDir[]) const;
  
  CATBoolean ComputeSegmentDirection(const CATMathSetOfPointsNDWithVectors & iSol,
                                     const CATLONG32                         iIndex,
                                           double                            oDir[]) const;

  // For curves which end on a singular init
  CATBoolean TestAndCorrectCurveEndTangentAtInit(const CATLONG32                         iPointSolIndex,
                                                       CATMathSetOfPointsNDWithVectors & iSol) const;
  
  // For curves which end on a singular point which isn't an init
  CATBoolean TestAndCorrectCurveEndTangent(CATMathSetOfPointsNDWithVectors & iSol) const;

  CATBoolean TestAndCorrectCurveTangent(      CATMathSetOfPointsNDWithVectors & ioSol,
                                        const CATLONG32                         iIndex) const;
  
  CATBoolean TestAndCorrectCurveTangentAtInit(const CATLONG32                         iPointSolIndex,
                                                    CATMathSetOfPointsNDWithVectors & ioSol,
                                              const CATLONG32                         iIndex) const;

  CATBoolean ValidExitPoint(const double iExitPoint[],
                            const double iTangent[],
                            const int    iStartIndex,
                            const int    iPointIndex);

  CATBoolean ValidNewInit(const int    iPointIndex,
                          const double iTangent[]) const;

  CATBoolean ValidNewInit(const CATSurSurResultPoint * iPoint,
                          const double                 iTangent[]) const;
  
  CATBoolean FindInitCopyIndexWithBestMatchTangent(const CATLONG32   iRefPointIndex,
                                                   const double      iTangent[],
                                                         CATLONG32 & oBestPointIndex) const;

  CATBoolean FindExitBorderPointCorrespondingTo(const double            * iPt,
                                                const CATLONG32           icoor,
                                                      CATMathSetOfLongs & ioindice);

  CATBoolean FindCornerPointCorrespondingTo(const double    * iPt,
                                            const CATLONG32   icoor,
                                            const CATLONG32   iSurf, 
                                                  double    * ioPoint);
  
  //CATLONG32 ComputeBorderSolution(const BorderExtrem iFixedVar[]);

  CATLONG32 ComputeBorderSolution(const CATSurSurResultPointType   iType, 
                                  const double                   * iStartPoint, 
                                  const double                   * iStartTangent,
                                  const BorderExtrem               iFixedVar[],
                                  const CATBoolean                 iFullSolution = FALSE);

  // Treatment of regions (surfaces) of confusion
  CATBoolean ComputeConfusion(const CATBoolean iAllowLargeTol);
  CATBoolean ComputeIdenticalSurfaces();
  CATBoolean CanTryConfusion() const;
  CATBoolean CanTryConfusion_SSTg() const;

  CATBoolean IsACurveContainingInits(const CATLONG32 iInitIndex0,
                                     const CATLONG32 iInitIndex1) const;

  void ConnectRemainingSingularInits();
  CATBoolean IsInitValidForConfusion(const CATLONG32           iInitIndex,
                                     const CATMathSetOfLongs & iListInitsCurveInterior,
                                     const CATMathSetOfLongs & iListInitsCurveExtremity,
                                     const CATBoolean          iFromInit) const;

  short FindIsoparPLine(CATSurSurResultPoint * iStartPoint, 
                        CATSurSurResultPoint * iEndPoint, 
                        short                  k);

  CATBoolean ComputePlineSurface(const CATSurSurResultPoint * iStartPoint,
                                 const CATSurSurResultPoint * iEndPoint,
                                 const short                  iSurf,
                                 const CATBoolean             iAllowLargeTol = FALSE);

  CATLONG32 ConnectAllInitExit( const CATLONG32 iInitIndex,
                                const CATLONG32 iExitIndex);

  CATBoolean ConnectOneInitExit(const CATSurSurResultPoint * iInit, 
                                      CATSurSurResultPoint * iExit,
                                const CATBoolean             iApplyTangentRequirement = TRUE);

  CATBoolean TryMonoArcDeformation();

  CATLONG32 ComputeBranch(const double                          *   iStartPoint,
                                CATLONG32                         & i,
                          const CATLONG32                           iSize, 
                                double                          *   iStartTangent,
                                CATMathSetOfPointsNDWithVectors **& TabOfSets,
                                CATMathSetOfLongs               **  SetOfExitIndex,
                                CATMathSetOfLongs               **  SetOfSingularIndex,
                                CATMathSetOfLongs               **  SetOfInitExitNumero);

  CATLONG32 UpdateTangentsOnBorder(const double       iPt[],
                                         double       ioTgt[],
                                         BorderExtrem oBorders[]) const;

  CATBoolean ExpandDomain(const BorderExtrem iBorders[]);

  CATLONG32 IsGoodInit(CATSurSurResultPointType   iType,  
                       double                   * startingPoint,
                       double                   * startingTangent = NULL);

  CATLONG32 VerifyTangent(double       * startingPoint,
                          double       * startingTangent,
                          BorderExtrem   SaturatedVar[4],
                          double         Tol);
  
  void ComputeImplicitSystem();
  void ComputeIndexes();

  void GetDeformPoints(CATMathSetOfPointsND & oDeformPoints);
  CATBoolean IsDeformationNeeded(const CATLONG32 iExitIndex);
  
  void Reallocation(CATLONG32                           size,
                    CATMathSetOfPointsNDWithVectors **& Sets);
  void Reallocation(CATLONG32             size,
                    CATMathSetOfLongs **& Sets);
  void UpdateSet(CATMathSetOfLongs *& set,
                 CATLONG32            a);
  void Sort(CATMathSetOfLongs *& ioset1,
            CATMathSetOfLongs *& ioset2);
  
  void ReverseTangent(      CATSurSurResultPoint * ioPoint, 
                      const double                 iPt[],
                      const double                 iTangent[]) CATGEOOverride;
  
  void ComputeTangents();
  void CloneInitPoint(const double    iPt[4],
                      const CATLONG32 iPointIndex);
  void ComputeTangentOrientation(const CATLONG32 iCurrPointIndex,
                                 const CATLONG32 iOrigPointIndex,
                                 const double    iPt[4],
                                       double    ioTangent[4]);

  CATLONG32 ComputeExitIndex(CATLONG32 indexpointinset) const;

  CATLONG32 CleverInitSolve(double                            * StartPoint,
                            double                            * StartTangent,
                            CATLONG32                         & NumberOfSolutions,
                            CATLONG32                         & size,
                            CATLONG32                           sens,
                            CATMathSetOfPointsNDWithVectors **& resultSets,
                            CATMathSetOfLongs               **& SetOfExitIndex,
                            CATMathSetOfLongs               **& SetOfSingularIndex,
                            CATMathSetOfLongs               **& SetOfInitExitNumero);

  CATBoolean AreBranchesDuplicated(CATMathSetOfPointsND * iMarchedPointsBr1,
                                   CATMathSetOfPointsND * iMarchedPointsBr2,
                                   CATMathSetOfLongs    * iInitExitListBr1,
                                   CATMathSetOfLongs    * iInitExitListBr2) const;

  CATBoolean SnapEndPointToConeApex(double      ioEndPt4D[],
                                    CATLONG32 & oApexInitIndex) const;
  CATBoolean SnapEndPointToDegeneratePoint(double      ioEndPt4D[],
                                           CATLONG32 & oReplaceInitIndex);
  CATBoolean SnapEndPointToInterOpInit(const CATLONG32   iNumMarchedPts,
                                       const double      iStartPt4D[],
                                             double      ioEndPt4D[], 
                                             CATLONG32 & oReplaceInitIndex);

  void InitializeSets(CATLONG32 Size,
                      CATMathSetOfLongs               ** SetOfExitIndex, 
                      CATMathSetOfLongs               ** SetOfSingularIndex,
                      CATMathSetOfLongs               ** SetOfInitExitNumero,
                      CATMathSetOfPointsNDWithVectors ** regularSets);

  CATLONG32 ComputeTangentSolveData(CATSurSurResultPoint * iStartPoint,
                                    double                 StartTangent[4],
                                    CATLONG32            * oIsoParVar = NULL);

  void RecordTangentSolveResult(      CATLONG32                            singularBis,
                                      CATSurSurResultPointType             Type,
                                      CATLONG32                          & RegularNum,
                                      CATMathSetOfPointsNDWithVectors  *   tmp,
                                      CATMathSetOfPointsNDWithVectors  *   tmpBis,
                                      CATMathSetOfPointsNDWithVectors  **& regularSets,
                                      CATMathSetOfLongs                **& SetOfExitIndex,
                                      CATMathSetOfLongs                **& SetOfSingularIndex,
                                      CATMathSetOfLongs                **& SetOfInitExitNumero,
                                const CATLONG32                        *   iCoordIsoPar = NULL);

  void RecordTangentSolveResult_TidyForReturn(CATMathSetOfPointsNDWithVectors *& ioRegularSet,
                                              CATLONG32                        & ioRegularNum) const;

  CATBoolean IsTangentSolveInitAtCurveExtremity(const CATMathSetOfLongs & iIndices,
                                                const CATLONG32           iIndex,
                                                const double              iPt4D[]) const;

  CATBoolean ConstructTangentSolveCurveData(const CATBoolean           iCurveStartOnBorder,
                                            const CATBoolean           iCurveEndOnBorder,
                                            const CATBoolean           iCurveStartIsSingular,
                                            const CATBoolean           iCurveEndIsSingular,
                                            const CATMathSetOfLongs  & iInitIndices,
                                                  CATMathSetOfLongs *& ioExitIndex,
                                                  CATMathSetOfLongs *& ioSingularIndex,
                                                  CATMathSetOfLongs *& ioInitExitNumero);

  void InitializeStartingPoints( const CATSetOfSurParams   & iSetSurParam1,
                                 const CATSetOfSurParams   & iSetSurParam2,
                                 const CATIntersectionSign * iSignatureOnFirstSurface,
                                 const double              * iTangents, 
                                 const CATBoolean            iConvergeAfterSurSurTg,
                                 const CATBoolean            iRemoveDuplicateInits);                                      

  void EliminateInits(const CATBoolean iWithTangents,
                      const CATLONG32  iStartCurveIndex = 0,
                      const CATLONG32  iMarchedInitIndex = -1);

  void RattrapeDeLaDerniereChance();
  short SmoothSharpStatus(const CATSurParam SurParam[2],
                                double      iSeuil);
  
  CATBoolean IsBadMarchingResult(const CATMathSetOfPointsNDWithVectors * iSolution);
  
  CATLONG32 IsBorderReached(const CATPCurve    * PCrv,
                            const CATCrvParam  & cp,
                            const CATSurface   * Surf, 
                            const CATSurLimits & sl,
                                  double         tol);
  void RattrapeMonoArcDef();
  void ReplaceReconvInitsWithNonReconvInitsInResultList(CATMathSetOfLongs ** SetOfInitExitNumero,
                                                        CATLONG32            RegularNum);
  
  short ChooseSupportOfPLine(const CATSurSurResultPoint * iStartPoint, 
                             const CATSurSurResultPoint * iEndPoint, 
                                   double               & oDist) const;

  short ChooseSupportOfPLine_ChordAlignment(const CATSurSurResultPoint * iStartPoint, 
                                            const CATSurSurResultPoint * iEndPoint) const;

  CATBoolean ChooseSupportOfPLine_InitDistance(const CATSurSurResultPoint * iPoint,
                                                     short                & oNumSurf) const;

  void ComputeUnstableWarning(CATSurSurResultCurve            * CurveSol, 
                              CATMathSetOfPointsNDWithVectors * SetOfPoints,
                              CATMathSetOfLongs               * InitExitNumero);
  
  //CATBoolean IsPointOnPcurve(CATLONG32 iIndexPoint);
  void UpgradeToNewInterface();
  
  const HRESULT RunSurSurTg(CATBoolean & oConvergeAfterSurSurTg);

  void SurSurTgHook();

  void PassInits(const CATIntersectionSurSurTg_InitSetInfo * iInitSet,
                       CATIntersectionSurSurTg             * ioOp, 
                       short                               & oInitKO, 
                       double                              & oLargerThreshold, 
                       CATMathSetOfLongs                   & ioInitsMapping);

  void SurSurTgHook1();
  void SurSurTgHook2();
  void SurSurTgHook2(const int iInitSetIndex);
  //void SurSurTgHook3();
  //CATBoolean Canonical();

  CATBoolean DidSurSurWithInitsFindAnyCurves() const;
  CATBoolean ContinueProcessAfterSurSurTg() const;

  CATLONG32 PointBorder(      short    dim,
                        const double * x,
                        const double * dom,
                              double   tol);
  
  void InsertArtificialInits();
  void RemoveArtificialInits();
  
  void UpdateStartingPoint();

  // If an init has more than one tangent, a CATSurSurResultPoint is created for each direction ("copies")
  void FillListOfAllCopiedPointSolutionIndices(const CATSurSurResultPoint * iInit, 
                                                     CATMathSetOfLongs    & oListOfCopies) const;

  void LastChanceFilletAttemptFromFirstInitAndCopies();
  void LastChanceFilletAttemptFromPointSolution(CATSurSurResultPoint * Init);

  // Compute adjusted minstep in case of close inits in R4 but very far in 3D
  void ComputeMinStep();
  CATBoolean ComputeDomainPseudoWidth(const double   iTangent[],
                                            double & oWidth) const;

  CATBoolean AreUVRSPointAndTangentDuplicated(const CATSurSurResultPoint * iPoint0,
                                              const CATSurSurResultPoint * iPoint1,
                                              const CATBoolean             iIsFilletInit) const;

  CATBoolean AreUVPointsDuplicated(const double iPt0[],
                                   const double iPt1[]) const;

  CATBoolean AreUVTangentsDuplicated(const double iT0[],
                                     const double iT1[]) const;
  
  CATLONG32 GetInitIndexFromValidInitIndex(const CATLONG32 iValidInitIndex) const;
  CATLONG32 GetValidInitIndexFromInitIndex(const CATLONG32 iInitIndex) const;

  void UpdateNumberOfInits();

  // Functions to use InterOp help points
  CATBoolean UsingInterOpHelpPoint() const;
  void InterOpCheckAndCorrectSolution(CATLONG32                       & ioNumSol,
                                      CATMathSetOfPointsNDWithVectors * ioResultSets[],
                                      CATMathSetOfLongs               * ioExitIndex[],
                                      CATMathSetOfLongs               * ioInitExitNumero[],
                                      CATMathSetOfLongs               * ioSingularityIndex[]);

  void InterOpCheckSolutionStartToEnd(const CATLONG32           iNumMarchPts,
                                            CATMathSetOfLongs * iExitIndex,
                                            CATMathSetOfLongs * iInitExitNumero,
                                            CATBoolean          iInitRequiredAtExtremity,
                                            CATBoolean        & oContainsInit,
                                            CATBoolean        & oInitAtExtremity,
                                            CATBoolean        & oCorrectOrientation) const;

  CATUnicodeString StringFromIntersectionSpec() const;

//=========
// Debug
//=========
  
  GEOPDEBUG_CMD(void DrawTangents_PointSol(const int * iRGB = NULL) const);
  GEOPDEBUG_CMD(void DrawTangents_Inits() const);
  
  GEOPDEBUG_CMD(CATLONG32 Debug_TestPointProximityToInitPoints(const double iPt4D[], const double iTol) const);
  GEOPDEBUG_CMD(void Debug_CheckSetOfMarchedPointsWithInits(CATMathSetOfPointsND ** iArrayOfSetOfPoints, CATMathSetOfLongs ** iArrayOfInitExitNumero, const CATLONG32 iArraySize) const);
  GEOPDEBUG_CMD(void Debug_CheckMarchedPointsWithInits(const CATMathSetOfPointsND * iSetOfPoints, const CATLONG32 iFirstIndex, const CATMathStopDiagnostic  iEndDiag) const);
  GEOPDEBUG_CMD(void Debug_CheckMarchedPointsWithInits(const CATMathSetOfPointsND * iSetOfPoints, const CATMathSetOfLongs * iInitExitNumero, const CATMathStopDiagnostic iEndDiag) const);
  GEOPDEBUG_CMD(void Debug_CheckMarchedPointsWithInits(const CATMathSetOfPointsND * iSetOfPoints, const CATMathSetOfLongs * iInitExitNumero, const short * iIndexInArray = NULL) const);
  GEOPDEBUG_CMD(void Debug_CheckMarchingEndPoint(const CATMathStopDiagnostic iDiag, const CATMathSetOfPointsNDWithVectors * iResultSet) const);
  GEOPDEBUG_CMD(CATBoolean Debug_CheckPLineInitExitSolution(const CATMathSetOfPointsND * iSetOfPoints, const CATSurSurResultPoint * iExit) const);
  GEOPDEBUG_CMD(CATBoolean Debug_IsTangentSolveCurveExtremityValid(const CATMathSetOfPointsNDWithVectors * iSet, const CATMathSetOfLongs * iGoodIndices, const CATBoolean iStart) const);

  GEOPDEBUG_CMD(void Debug_CheckCurveSolutions() const);
  GEOPDEBUG_CMD(CATBoolean Debug_CheckCurveExtremity(const CATLONG32 iCurveIndex, const CATBoolean iStart, const CATBoolean iDeform) const);
  GEOPDEBUG_CMD(CATBoolean Debug_CheckCurveInterior(const CATLONG32 iCurveIndex) const);
  GEOPDEBUG_CMD(CATBoolean Debug_CheckCurveExitPoints(const CATLONG32 iCurveIndex) const);
  GEOPDEBUG_CMD(void Debug_PrintCurveData(const CATLONG32 iCurveIndex) const);

  GEOPDEBUG_CMD(void Debug_PrintInitPointDistances() const);
  GEOPDEBUG_CMD(void Debug_PrintInitDuplicateList() const);

  // Debug functions for splitting intersecting curves - activated via SSWI_SplitIntersectingCurves
  GEOPDEBUG_CMD(void Debug_SplitIntersectingPairs());
  GEOPDEBUG_CMD(void Debug_SplitResultCurve(CATSurSurResultCurveWithInits * iCurve, CATMathSetOfLongs & iInit));
  GEOPDEBUG_CMD(CATBoolean Debug_SplitResultCurve(CATSurSurResultCurveWithInits *  iCurve, const CATLONG32 iInit, CATSurSurResultCurveWithInits *& oCurve0, CATSurSurResultCurveWithInits *& oCurve1));


//========================================================================
// CGMReplay management
//========================================================================
protected:
  friend class CATGeoStreamFactory; 

  // private static data
  static CATString     _OperatorId;
  static CATGeoOpTimer _Timer;

  // Visualisation
  CATLISTP(CATGeometry) _ListDrawnInputInits;

public:
  
  const CATString * GetOperatorId();
  //-----------------------------------------------------------------------
  //- Timer management
  //-----------------------------------------------------------------------  
  CATGeoOpTimer * GetTimer();

  //-----------------------------------------------------------------------
  //- Mode Record management
  //-----------------------------------------------------------------------  
  
  CATExtCGMReplay *IsRecordable(short & LevelOfRuntime,
                                short & VersionOfStream);
  virtual void WriteInput(CATCGMStream & os);
  virtual void WriteOutput(CATCGMStream & os);
  virtual CATBoolean ValidateOutput(CATCGMStream & ioStream,
                                    CATCGMOutput & os,
                                    int            VersionNumber = 1);
  virtual void Dump(CATCGMOutput & os);
  virtual void DumpOutput(CATCGMOutput & os);
  virtual void DumpOutput(CATCGMStream & ioStream,
                          CATCGMOutput & os,
                          int            VersionNumber = 1);
  virtual CATCGMOperator::CATCheckDiagnostic CheckOutput(CATCGMOutput & os);

  virtual void ReadInput(      CATCGMStream          & ioStream,
                         const int                     iVersionOfStream,
                               CATGeoODTScaleManager * iScaleManager);

protected:

  virtual CATBoolean IsSurSurGenOperator() const;
          CATBoolean ReadLongIntoBoolean(CATCGMStream & ioStream);
};
#endif
