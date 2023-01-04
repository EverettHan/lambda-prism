// COPYRIGHT DASSAULT SYSTEMES  1997
//=============================================================================
//
// CATMathImplicitSystem:
// Abstract class used to Solve an implicit system of functions from 
// RN-->R(N-1) with F differentiable (C1) and N >= 2.
//
//=============================================================================
//
// Usage notes:
// The result of the solve method is a set of points in RN. The first point
// is given by the user. To use this class you will need to derivate
// this abstract class and define some evaluators on your concrete system
// of functions. You will have to code Eval method and it is also 
// strongly recommended to code EvalJacobian.
// The method CheckJacobianAtPoint may help you to test EvalJacobian.
//
// XScaleRules:                                                                                 (NLD140114)
// 1) standard behaviour
//  - domains         must behave like power 1 of factory scale
//  - parameters      must behave like power 1 of factory scale
//  - function        must behave like power 1 of factory scale
//  - steps  computed must behave like power 1 of factory scale
// 2) for a system not following standard behaviour:
//  Scale behaviour may be defined by two means (from best way to worst)
//  - specify a CATMathAttrScaleOption attribute through attributes list at constructor call 
//  - use SetScaleOption()
//  - specify a CATMathAttrScaleOption attribute through attributes list when solving
//    (Solve(), CleverSolve() SolveMultipleSolutions())
//  Evaluators must apply the following recipes for not standard behaviour
//  - Eval()
//           should call UnScaleX()        on parameters         before computation
//                       ScaleFx()         on functions result   before exit
//                       ScaleJacobianFX() on Jacobian  result   before exit
//  - EvalTangent()
//           should call UnScaleX()        on parameters         before computation
//           should normalize result                             before exit
//  - EvalTangentField()
//           should call UnScaleX()        on parameters         before computation
//           should unscale result to a scale independant result before exit
//  - EvalConstraint() and EvalConstraintJacobian()
//           should call UnScaleX()        on parameters         before computation
//                       ScaleGx()         on functions result   before exit
//                       ScaleJacobianGX() on Jacobian  result   before exit
//  CAUTION: Class not fully migrated / certified for non standard scale option                 (NLD280714)
//     use of standard scale option strongly recommended
//
//=============================================================================
//   /03/97 PSH Creation
// 18/02/08 NLD Ajout _ScaleOption et _UseScaleOption
//              Ajout de SetScaleOption() pour pouvoir redefinir le ScaleOption
//              apres le constructeur (commode pour classes derivees)
// 05/03/08 NLD _UnScaleX_Spy, _ScaleFX_Spy for XScale debug purpose
// 11/04/08 NLD Ajout ComputeEpsilonSquaredPower() pour factorisation entre SolveOnHyperPlane()
//              Ajout argument optionnel iDomainScaled a SolveOnHyperPlane() et SafeSolveOnHyperPlane()
//              pour eviter re-scale multiple
// 20/05/08 NLD Ajout _IsContainingLevel2
// 13/07/09 NLD Ajout _CGMLevel
//              SubdomainMinDistance() est renommee SubdomainMinSquareDistance()
// 02/07/10 FDS _BufferForTangentComputation
// 09/07/10 KJD _MandatorySaturations et _IsSaturated
// 23/07/10 NLD Ajout _MultipleAlloc_N
//              Ajout _CurrentSolAlloc_N
// 15/02/11 NLD Reodonnancement complet des données pour debug
//              Ajout ____________________MileStone*
//              Ajout _ConfigOptions pour regroupement et recensement versionning
//              _ImplicitSystemIsContainingLevel2 remplace _IsContainingLevel2
// 13/04/11 NLD Ajout de _Sweep_XScaleR20SP7
// 19/04/11 NLD _TolObject devient de type CATFullTolerance
// 10/10/11 NLD Securisation post-exception de ComputeBranch() qui rend une erreur le cas échéant
// 01/12/11 kjd Ajout _Marching_FindLastPointWithBS_Situation1Failure
// 09/12/11 NLD Ajout AddSetInSet() et AddPointWithTol()
//              AddPoint() et AddPointWithTol() rendent desormais l'indicateur d'insertion
//              AddPoint()        est renommée AddNewPoint()
//              AddPointWithTol() est renommée AddNewPointWithTol()
//              pour respecter la nomenclature de CATMathSetOfPoints()
// 12/12/11 NLD Ajout _Marching_ReviewV1
//              ComputeRattrappe() est renommée ComputeRattrap()
// 13/12/11 NLD Ajout _Sweep_XScaleR22SP1
// 11/05/12 kjd Ajout _SolPointNb
// 24/05/12 NLD Ajout méthodes de gestion des ensembles de points:
//              Reset(), RemovePoint(), RemovePoints()
// 28/05/12 NLD Ajout GetOrEvalLastTangent()
//              Ajout ReallocationIfNecessary()
// 06/06/12 NLD Ajout InitializeSolve()
//              Ajout _Sweep_XScaleR22SP3
// 20/06/12 NLD Ajout Truncate()
// 10/07/12 NLD Ajout CATMathC1Disc_Diag pour partage des codes de retour de FindC1Discontinuity()
// 26/09/12 R1Y Fixed IR-123092 by modifying algorithms for marching (KJD) and curve-splitting (XMH).
// 08/01/13 Q48 Make EvalSingularTangents virtual (for CATFunctionIntersectionSurSur)
// 25/06/13 NLD _ScaleOption et _UseScaleOption passent de private en protected pour acces en lecture par classes derivees
// 12/07/13 NLD _Lambda est renomme _LambdaStep pour eviter confusion avec le _lambda relatif au re-scale
// 15/07/13 NLD Ajout _Marching_PredictionCloseToBorder_V2
//              Smart indent for variables declaration
//              Smart indent for methods   declaration
// 18/07/13 NLD Ajout _Sweep_XScaleR23SP3
// 31/07/13 Q48 Make EvalTangentField protected (for CATFunctionIntersectionSurSur)
// 04/10/13 kjd Ajout ComputeOrientation()
// 08/01/14 kjd Ajout _Marching_Solve_RemoveInitFromExits
// 15/01/14 NLD Ajout XScaleRules
// 19/03/14 kjd Ajout _Marching_FindNewPoint_BorderDivergence,
//              Ajout _Marching_FindNewPoint_SafeNewtonForBorder,
// 18/04/14 NLD Ajout _Sweep_XScaleR24SP3
// 22/04/14 R1Y Added RemoveDuplicateTangents().
//              (code isolation for derivation)
// 22/07/14 NLD Ajout regles d'evaluation dans XScaleRules
//              pour Eval(), EvalTangent(), EvalTangentField(), EvalConstraint(), EvalConstraintJacobian()
// 28/07/14 NLD Ajout InitLevel()
//              Ajout InitXScale()
//              Ajout RemoveListOfMarchingDiagnostic()
//              Regroupement des methodes Solve*()
//              ComputeRattrap() est renommee ComputeBranchRattrap()
// 15/05/14 kjd Ajout _FindLastPoint_SingularityWithoutSingularSystem
// 02/10/14 kjd Ajout _Marching_StopOnFirstPoint                      (CGM_Versionning_Marching_StopOnFirstPoint)
// 20/10/14 kjd Ajout _Marching_FindNewPoint_RootWithJacobian         (CGM_Versionning_Marching_FindNewPoint_RootWithJacobian)
// 09/12/14 kjd Ajout _Marching_SearchEndPoint_EndPointAttempts       (CGM_Versionning_Marching_SearchEndPoint_EndPointAttempts)
//              et    _EndPointAttempts
// 10/12/14 kjd Ajout _Marching_Solve_RemoveInitFromExits2            (CGM_Versionning_Marching_Solve_RemoveInitFromExits2)
// 04/01/15 kjd Ajout _Marching_Solve_RemoveInitFromExits3            (CGM_Versionning_Marching_Solve_RemoveInitFromExits3)
// 16/01/15 kjd Ajout _Marching_FindNewPoint_Loop                     (CGM_Versionning_Marching_FindNewPoint_Loop)
// 18/01/15 kjd Ajout _Marching_Solve_StartPointInMaxDomain           (CGM_Versionning_Marching_Solve_StartPointInMaxDomain)
// 19/02/15 kjd Ajout _Marching_Solve_AddMaxDomainSet                 (CGM_Versionning_Marching_Solve_AddMaxDomainSet)
// 06/03/15 kjd Ajout _Marching_ManageSingularity_BranchOrEndPoint    (CGM_Versionning_Marching_ManageSingularity_BranchOrEndPoint)
// 11/03/15 kjd Ajout _AcceptLoopInMaxDomain
// 10/04/15 jsx Ajout _XScale_Geometry_R25_SP3
// 17/04/15 kjd Ajout _IndexStartPoint
// 20/07/15 jsx retour sur SolveOnConstraint_Public le type des arg ne suffit pas a differencier les 2 methodes
//              si on change un nom, par cast le compilo utilie l'utre sans faire d'erreur de compil
//              Il faut rechercher a la main les utilisations avec un certain type d'argument 
//              => je lelivrerai vendredi avec un flag 
// 24/07/15 JSX flag NewNameForPublicNoneVirtualMethod
// 11/05/16 kjd Ajout _Marching_Stockage_EndPointRejected                   (CGM_Versionning_Marching_Stockage_EndPointRejected)
// 18/04/17 KJD Ajout _Marching_RunMultipleSol_DiagManagement_Loop (RI454402)
// 04/08/17 KJD Ajout _Marching_RunMultipleSol_StartDiagManagement
// 29/08/17 kjd Ajout VisualizeDiags()
// 14/09/17 kjd Ajout _Marching_InsideDomain_BorderTol
// 20/10/17 NLD Ajout _XScale_Geometry_R28_SP1
// 04/01/18 NLD Ajout SolveAddSetInSet
// 20/02/18 NLD Ajout RunSafe()
// 21/02/18 NLD Ajout _ThrowProhibited_RestoreIfThrow
//              Ajout _StopByDomain_AddSetInStandardCase
// 21/02/18 NLD Ajout AddSetInArrayOfSet()
// 20/08/18 KJD GetJacobian becomes a const method
// 31/08/18 F4E Add _Marching_Run_TooSmallStep_StopByDomainNearEndPointRetake   (CGM_Versionning_Marching_Run_TooSmallStep_StopByDomainNearEndPointRetake)
// 12/10/18 F4E Add _Marching_SearchEndPoint_SingularityRestriction             (CGM_Versionning_Marching_SearchEndPoint_SingularityRestriction)
// 17/02/20 NLD RunMultipleSolutions() peut rendre une erreur en argument de sortie
// 10/08/21 Q48 Add _Marching_CleverSolve_MaxSingularity
// 18/08/21 Q48 Add _Marching_SingularPoint_NotBackwards (IR-847477)
// 07/03/22 Q48 Add new IsNull signature (no need to call Eval first)
//=============================================================================

#ifndef CATMathImplicitSystem_H
#define CATMathImplicitSystem_H

#define CATMathImplicitSystem_UseCATFullTolerance "NLD190411"


class CATMathIntervalND;
class CATMathSetOfPointsND;
class CATMathAttrList;
class CATMathNxNFullMatrix;
class CATMathNxNFullSymMatrix;
class CATMathAttrMultipleDomain;
class CATMathAttrDecomposition;
class CATMathSystem;
class CATMathSetOfLongs;
class CATSoftwareConfiguration;
class CATError;

#include "YN000FUN.h"
#include "CATMathDef.h"
#include "CATMathDiagnostic.h"
#include "CATMathInline.h"
#include "CATCGMVirtual.h"

#include "CATTolerance.h"
#ifdef CATMathImplicitSystem_UseCATFullTolerance
#include "CATToleranceAccess.h" // pour CATFullTolerance
#endif

#include "CATMathAttrScaleOption.h"

// Diagnostic
#include "CATMathStopDiagnostic.h"
class CATListPtrCATMathMarchingDiagnostic;
class CATMathMarchingDiagnostic;

ExportedByYN000FUN extern const CATMathAttrId AttrDomain;
ExportedByYN000FUN extern const CATMathAttrId AttrParamDistortion;

//                                          Codes de retour de FindC1Discontinuity et de ses semblables
//                                          dans autres classes; définis ici pour partage; NLD100712
//                                          - Attention à l'ordre: il y a des tests d'inegalité sur ces valeurs
//                                            de retour
typedef enum {CATMathC1Disc_0NoDiscontinuityFound  =  0,
              CATMathC1Disc_1DiscontinuityFound    =  1,
              CATMathC1Disc_Moins1UnableToConverge = -1,
              CATMathC1Disc_Moins99InputError      = -99
             }CATMathC1Disc_Diag;
          //  CATMathC1Disc_Moins100InputError     = -100;// specifique CATMathInterpol


//-----------------------------------------------------------------------------
class ExportedByYN000FUN CATMathImplicitSystem  : public CATCGMVirtual
{ 
  public:  
//----------------------------------------------------------
//  Constructor (iN is the number of unknowns of the system)
//----------------------------------------------------------
//  CAUTION: almost no attribute type taken into account in iAttributes
//           (except for CATMathAttrScaleOption)                        (implementation    IEY240107)
//           other attributes must be specified through solving methods.                   NLD280714
                                        CATMathImplicitSystem       (      CATSoftwareConfiguration *  iConfig          ,
                                                                     const CATLONG32                   iN               ,
                                                                     const CATTolerance              & iTolObject       = CATGetDefaultTolerance(),
                                                                     const CATMathAttrList          *  iAttributes      = NULL                    );
//------------
//  Destructor
//------------
    virtual                            ~CATMathImplicitSystem       ();

//----------------
//  Other Methods
//----------------

//  Get the number of unknowns of the system (N) 
    INLINE  CATLONG32                   GetNumberOfVariables        () ; 

// This method can be used only if the diagnostic is StoByEndPoints....
//  Get the numero of the End points in the local set of EndingPoints
    INLINE  CATLONG32                   GetIndexEndPoint            () ; 

            void                        SetIndexEndPoint            (      CATLONG32                   index            ) ; 

// This method can be used only if SolveMultipleSolution is called.
// Get the extremities diagnostic of the solution.
            void                        GetStartEndDiagnosticsOfSol (      CATLONG32                   iNumSol          ,
                                                                           CATMathStopDiagnostic     & oStartDiag       ,
                                                                           CATMathStopDiagnostic     & oEndDiag         ) ; 

//-----------------------------------------------
// Solve methods and solve results access methods
//-----------------------------------------------
//  Compute the marching algorithm :
//   Given a starting point in RN and a normalized oriented tangent in RN at 
//   this point, the Solve method finds a set of sorted points Xi where F(Xi)=0
//   and each point is in a Domain [Min X1, Max X1]x...x[Min X(N-1), Max X(N-1)]
//   (EvalTangent() may be used for iStartTangent computation)
//   The mode of repartition of the points and the density are given by the
//   iAttributes argument.
//   The CATMathDiagnostic is CATMathOK if the Solve found a set of points.  
//   Otherwise a failure diagnostic is given: 
//    . CATMathNullVector: The StartPoint is singular 
//   -- If you want to decompose the starting space in spaces of smaller dimension
//   you can use the iAttributes: "CATMathAttrDecomposition",
//   you have to build an array Tab[n], where n is the number of decomposition wanted
//   and you have to initialized each case of the array:
//   Tab[0]=p, Tab[1]=q,.....,Tab[n-1]=r, where the values p,q,...,r are the number 
//   of variables you want in each decomposed space.
//   -- If you want all the variables to reach the boundaries of the domain, you
//   must use the iAttribute: "CATMathAttrMultipleDomain"
//   you have to build an array to decompose the starting space as described above, and
//   a max domain which allows some variables to go out of the basic domain in order
//   that the other variables reached the border of the basic domain.  

    virtual CATMathDiagnostic           Solve                       (const CATMathIntervalND         & iDomain           , 
                                                                     const double                   *  iStartPoint       , 
                                                                           double                   *  iStartTangent     ,
                                                                           CATMathSetOfPointsND      & oSetOfPoints      ,
                                                                     const CATMathAttrList          *  iAttributes       = NULL);
//  Compute the marching algorithm :
//   Given a start point in RN in or on the domain and the start Tangent,the Solve method
//   finds  sets of sorted points Xi where F(Xi)=0,
//   and each point is in a Domain [Min X1, Max X1]x...x[Min X(N-1), Max X(N-1)]
//   The mode of repartition of the points and the density are given by the
//   iAttributes argument.
//   The CATMathDiagnostic is CATMathOK if the Solve found sets of points.
//   Otherwise a failure diagnostic is given: 
//    . CATMathNullVector: The StartPoint is singular   
    virtual CATMathDiagnostic           CleverSolve                 (const CATMathIntervalND         & iDomain          ,
                                                                           CATLONG32                 & NumberOfSolutions,
                                                                           CATLONG32                 & Size             ,
                                                                           double                   *  iStartPoint      ,
                                                                           double                   *  iStartTangent    ,
                                                                           CATMathSetOfPointsND    **& oSetOfPoints     ,
                                                                     const CATMathAttrList          *  iAttributes      = NULL);
//  Compute the marching algorithm :
//   Given a set of starting points in RN on the border of the domain and an other of
//   interior starting points, the Solve method finds sets of sorted points Xi where
//   F(Xi)=0,and each point is in a Domain [Min X1, Max X1]x...x[Min X(N-1), Max X(N-1)]
//   The mode of repartition of the points and the density are given by the
//   iAttributes argument.
//   The CATMathDiagnostic is CATMathOK if the Solve found sets of points.
//   Otherwise a failure diagnostic is given:
//    . CATMathNullVector: The StartPoint is singular
    virtual CATMathDiagnostic           SolveMultipleSolutions      (const CATMathIntervalND         & iDomain          ,
                                                                           CATLONG32                 & NumberOfSolutions,
                                                                           CATLONG32                 & Size             ,
                                                                           CATMathSetOfPointsND      & iStartPoints     , 
                                                                           CATMathSetOfPointsND    **& oSetOfPoints     ,
                                                                     const CATMathAttrList          *  iAttributes      = NULL);

//  Convergence to DF(X)=0 and check if F(X) = 0, to see if there is a Jump
//  to an other branch
//   An initial guess ioX is given for X.
//   The CATMathDiagnostic is CATMathOK if the Solve found a solution ioX. 
//   Otherwise a failure diagnostic is given:
//    . CATMathMaxIteration
//    . CATMathOutOfDomain
    virtual CATMathDiagnostic           SolveOnBifurcation          (const CATMathIntervalND         & iDomain          ,
                                                                           double                   *  ioX              ,
                                                                           double                   *  DF               ,
                                                                           CATBoolean                  iDomainScaled    = FALSE);

//  Convergence to F(X)=0 and <iN,X>+iD = 0 a Hyperplane (normal iN)
//   An initial guess ioX is given for X.
//   The CATMathDiagnostic is CATMathOK if the Solve found a solution ioX. 
//   Otherwise a failure diagnostic is given:
//    . CATMathMaxIteration  
//    . CATMathSingularJacobian 
//    . CATMathOutOfDomain 
    virtual CATMathDiagnostic           SolveOnHyperPlane           (const CATMathIntervalND         & iDomain          ,
                                                                     const double                   *  iN               ,
                                                                     const double                      iD               ,
                                                                           double                   *  ioX              ,
                                                                           CATBoolean                  iDomainScaled    = FALSE);

// Same method as above but with "SafeNewton" like solving strategy (should be more local for cases where many solutions may exist).
// Returns CATMathOK if a solution has been found, otherwise a failure diagnostic:
//  CATMathNoConvergence
//  CATMathSingularJacobian
//  CATMathMaxIteration
    virtual CATMathDiagnostic           SolveSafeOnHyperPlane       (const CATMathIntervalND         & iDomain          ,
                                                                     const double                   *  iN               ,
                                                                     const double                      iD               ,
                                                                           double                   *  ioX              ,
                                                                           CATBoolean                  iDomainScaled    = FALSE
                                                                    );
//  Convergence to F(X)=0 and G(X) = 0 a constraint 
//   An initial guess ioXRoot is given for X.
//   The CATMathDiagnostic is CATMathOK if the Solve found a point. 
//   Otherwise a failure diagnostic is given:
//    . CATMathMaxIteration  
//    . CATMathSingularJacobian 
//    . CATMathOutOfDomain (then oOutDiag = smallest border rank)


    // Warning : this NON-virtual method calls the second one
#define NewNameForPublicNoneVirtualMethod "Excuse moi partenaire, mais ca meriterait de suivre une nomenclature CATMathImplicitSystem_*"
#ifdef NewNameForPublicNoneVirtualMethod
    virtual CATMathDiagnostic           SolveOnConstraint_Public    (const CATMathIntervalND         & iDomain          ,
#else
            CATMathDiagnostic           SolveOnConstraint           (const CATMathIntervalND         & iDomain          ,
#endif
                                                                           double                   *  ioXRoot          ,
                                                                           CATLONG32                 & oOutDiag         );
// virtual mothod in Protected now
protected:
    virtual CATMathDiagnostic           SolveOnConstraint           (const CATMathIntervalND         & iDomain          ,
                                                                           double                   *  ioXRoot          ,
                                                                           CATBoolean                  iDomainScaled    = FALSE);
public:

    // Solver for a singular point on domain border.
    // The CATMathOption CATMathBorderSingularity is required.
            CATMathDiagnostic           SolveOnBorderSingularity    (const CATMathIntervalND         & iDomain          ,
                                                                           double                   *  XRoot            );

    // same as SolveOnBorderSingularity with the tuning of the sag
    virtual CATMathDiagnostic           SolveOnBorderBifurcation    (const CATMathIntervalND         & iDomain          ,
                                                                     const double                      iSag             ,
                                                                           double                   *  ioX              ,
                                                                           CATBoolean                  iDomainScaled    = FALSE);


//  Get the ending diagnostic of marching algorithm:
//   . CATMathStopByDomain:        The last point is on the boundary of the domain
//   . CATMathStopByStartingPoint: The last point has looped to the start point  
//   . CATMathStopInsideDomain:    The last point is singular and is strictly inside 
//                                 the Domain (cusp, ...)
//   . CATMathStopByConstraint:    The last point is a zero of the constraint
//   . CATMathStopBySingularPoint: The last point is a singularity
//   . CATMathStopByEndPoints:     The last point is a point given by the user
//
    virtual CATMathStopDiagnostic       GetDiagnostic               ()                                                    const;

//  Get the ending diagnostic of the last marching algorithm, plus the convergence method
//  used on the last point.
//  Notice that the diagnostic is a sum of bits.
            void                        GetRunInfo                  (      CATMathStopDiagnostic     & oSmartDiagnostic ,
                                                                           CATLONG32                 & oConvergenceInfo );



//----------------
//  Other Methods
//----------------
            CATMathDiagnostic           FindC1Discontinuity         (const CATMathIntervalND         & iDomain          ,
                                                                     const double                   *  iP0              ,
                                                                     const double                   *  iT0              ,
                                                                     const double                   *  iP1              ,
                                                                     const double                   *  iT1              ,
                                                                           double                   *  ioPLeft          ,
                                                                           double                   *  ioPRight         ,
                                                                           double                   *  ioTLeft          ,
                                                                           double                   *  ioTRight         ,
                                                                           int                         iOrientation     ,
                                                                           CATMathC1Disc_Diag        & oFound           );


            CATMathDiagnostic           ComputeMiddlePoint          (const double                   *  iP0              ,
                                                                     const double                   *  iP1              ,
                                                                           double                   *  ioPHalf          ,
                                                                           double                   *  iAllocated       ,
                                                                     const CATMathIntervalND         & iDomain          ,
                                                                           double                      iLambda          );

//------------
//  Evaluators
//------------

// Evaluators: iX is a point in RN.
//  . oFX = F(iX) is the image of iX by F. oFX is in R(N-1) and is already allocated.
//  . oJacobianFX is the jacobian of F at iX and is in R(N*(N-1)) 
//    and is already allocated. 
//  . oTX is the tangent at iX and is in RN and is already allocated.
//  . IsNull is a function to determine if iFX = F(iX) can be considered as null 
//    at iX and oSquareNormFX is any norm of F(X) (any norm? it is a squared norm in default implementation!)
    virtual void                        Eval                        (const double                   *  iX               ,
                                                                           double                   *  oFX              ) = 0;

    virtual void                        EvalJacobian                (const double                   *  iX               ,
                                                                           CATMathNxNFullMatrix     *  oJacobianFX      );

    virtual void                        Eval                        (const double                   *  iX               ,
                                                                           double                   *  oFX              ,
                                                                           CATMathNxNFullMatrix     *  oJacobianFX      );

    virtual CATBoolean                  IsNull                      (const double                   *  iX               ,
                                                                     const double                   *  iFX              ,
                                                                           double                    & oSquareNormFX    ,
                                                                     const CATMathNxNFullMatrix     *  iJacobianFX      = 0);
      
    virtual CATBoolean                  IsNull                      (const double                   *  iX               ,
                                                                           double                    & oNormFX          );

    virtual CATBoolean                  IsTangentNull               (const double                   *  iX               ,
                                                                     const double                   *  iDFX             ,
                                                                           double                    & oSquareNormDFX   );

// Eval normalized tangent at a point X (Implicit Function theorema)
    virtual CATMathDiagnostic           EvalTangent                 (const double                   *  iX               ,
                                                                           double                   *  oTX              );

// Eval norm of tangent at a point
           double                       EvalNormOfTangent           (const double                   *  iX               );

// Evaluators for constraints: iX is a Point in RN and G the constraint.
// All the marching point will verify G(iX) >= 0.
//  . oGX = G(iX) is the image of iX by G : RN-->R1
//  . oJacobianGX is the jacobian of G at iX and is in RN = (dG/dX1, ..., dG/dXN)
//    and is already allocated. 
    virtual void                        EvalConstraint              (const double                   *  iX               ,
                                                                           double                    & oGX              );

    virtual void                        EvalConstraintJacobian      (const double                   *  iX               ,
                                                                           double                   *  oJacobianGX      );

    virtual void                        EvalConstraint              (const double                   *  iX               ,
                                                                           double                    & oGX              ,
                                                                           double                   *  oJacobianGX      );

// Using this option make the Solve to stop when passing throught a point from a given
// set of end points. iCheckUps is a sum of values corresponding to the check ups you
// want to be performed :
//   - 1  Check Tangent (the tangent at end point must be in the same direction as the trajectory)
//   - 2  Check Is Null (end points that are not "IsNull" will be ignored)
            void                        SetEndPoints                (      CATMathSetOfPointsND     *  iEndSetPoints    ,
                                                                           CATLONG32                   iCheckUps        = 0);

// Inclusion of a point in the sampled curve defined by the set of points.
    virtual CATLONG32                   IsContaining                (const CATMathIntervalND         & iDomain          ,
                                                                     const CATMathSetOfPointsND     *  iSet             ,
                                                                     const double                   *  iX               ,
                                                                     const double                   *  iTangent         = 0);

// Step calculation : find step at point iXCur (Tangent at this point is iTgtCur).
// The previous point and the previous tangent are iXPrev and iTgtPrev.
   virtual double                       EvalStep                    (const double                   *  iXPrev           ,
                                                                     const double                   *  iTgtPrev         ,
                                                                     const double                   *  iXCur            ,
                                                                     const double                   *  iTgtCur          );


// Eval Tangent not normalised at a point, and return the number of tangents found.
    virtual CATLONG32                   EvalSingularTangents        (const double                   *  iX               ,
                                                                           double                   *  oTX1             ,
                                                                           CATLONG32                 & ioNb             );
    virtual CATLONG32                   MaxNumTangents              ()                                                     const;

// Test if two points are nearly equals
    virtual CATLONG32                   EqualPoints                 (const double                   *  iXPt1            ,
                                                                     const double                   *  iXPt2            );

// Test if a point is singular
    virtual CATLONG32                   IsSingularPoint             (const double                   *  iXPt             );

            CATMathSystem             * GetSingularSystem           ();

//- Debug   
//-  CheckJacobianAtPoint is a method that can be used to check if EvalJaconbian 
//-  is correct at point iX  

  //        void                        CheckJacobianAtPoint        (const double                   *  iX               );
            void                        SetClient                   ();

// En attendant une software config
            void                        SetLevel                    (      CATLONG32                   iLevel           );

            void                        SetScaleOption              (      CATMathAttrScaleOption   *  iScaleOption     ) ;

  // XGN 13/06/2003 : in certain cases, we need to be able to release the tolerance for root
  // always a relative value, not depending on factory scale. NLD190208
    virtual void                        SetEpsSol                   (      double                      NewEpsSol        );

/////////////
 protected:
/////////////

            void                        SetDiagnostic               (      CATMathStopDiagnostic       iDiagnostic      );

//  Verify if each point is really on the curve solution
    virtual CATBoolean                  IsRoot                      (const double                   *  iX               ,
                                                                     const double                   *  iFX              ,
                                                                           double                    & oSquareNormFX    ,
                                                                     const CATMathNxNFullMatrix     *  iJacobianFX      = 0);

    virtual CATBoolean                  IsRootSpecific              (const double                   *  iX               ,
                                                                     const double                   *  iFX              ,
                                                                           double                    & oSquareNormFX    ,
                                                                     const CATMathNxNFullMatrix     *  iJacobianFX      = 0);

// Eval estimated hessien at a point in dimension 2
    virtual void                        EvalHessian                 (const double                   *  iX               ,
                                                                           double                   *  oT2XY            );

//
// Return Step at Current point where curvature and sag are given and step
// must be between MinStep and MaxStep
            double                      EvalStepWithSquareCurvature (const double                      iSquareCurvature ,
                                                                     const double                      iSag             , 
                                                                     const double                      iMinStep         ,
                                                                     const double                   *  iMaxStep         );

// Return a system to find the singular points in Rn
    virtual void                        SetSingularSystem           (      CATMathSystem            *  iSystemUser      );

//  Compute the tangent in a neighbourhood of a point X
    virtual void                        FindTangent                 (      CATLONG32                   iUsage           ,
                                                                     const double                   *  iX               ,
                                                                           double                   *  iTX              ,
                                                                           double                   *  oTX              ,
                                                                           double                    & ioStep           );

// Find marching orientation at starting  point  
            void                        Orientation                 (const double                   *  iCurrentTangent  ,
                                                                           double                   *  iStartTangent    );

//  Compute the marching algorithm :
//   Given a starting point in RN and a normalized oriented tangent in RN at 
//   this point, the Solve method finds a set of sorted points Xi where F(Xi)=0
//   and each point is in a Domain [Min X1, Max X1]x...x[Min X(N-1), Max X(N-1)]
    virtual CATMathDiagnostic           Run                         (const CATMathIntervalND         & Domain           ,
                                                                     const double                   *  StartPoint       ,
                                                                           double                   *  StartTangent     ,
                                                                           CATMathSetOfPointsND      & SetOfPoints      );

//  Compute the marching algorithm :
//  Same as above but exception free: returning oError if caught
//  N.B if method derivation (not recommended), only Run() must be derived
            CATMathDiagnostic           RunSafe                     (const CATMathIntervalND         & Domain           ,
                                                                     const double                   *  StartPoint       ,
                                                                           double                   *  StartTangent     ,
                                                                           CATMathSetOfPointsND      & SetOfPoints      ,
                                                                           CATError                 *& oError           );

/*
    virtual CATMathDiagnostic           RunNew                      (const CATMathIntervalND         & Domain           ,
                                                                     const double                   *  StartPoint       ,
                                                                           double                   *  StartTangent     ,
                                                                           CATMathSetOfPointsND      & SetOfPoints      );
*/


    virtual CATLONG32                   FindConstraintChangeOfSign  (const CATMathIntervalND         & iDomain          ,
                                                                     const CATMathSetOfPointsND      & iSetOfPoints     ,
                                                                           double                   *  ioX              ,
                                                                           double                    & oSquareDistanceWithPreviousPoints);

    virtual void                        SetStartMarchingDiagnostic  (      CATMathMarchingDiagnostic*  iDiag            ,
                                                                           CATLONG32                   iNumSol          );

    virtual void                        SetEndMarchingDiagnostic    (      CATMathMarchingDiagnostic*  iDiag            ,
                                                                           CATLONG32                   iNumSol          );

    virtual void                        SetStartDiagnostic          (      CATMathStopDiagnostic       iDiag            ,
                                                                           CATLONG32                   iNumSol          );

    virtual void                        SetEndDiagnostic            (      CATMathStopDiagnostic       iDiag            ,
                                                                           CATLONG32                   iNumSol          );

    virtual CATMathMarchingDiagnostic * GetBranchDiagnostic         ();

   // Test if a the constraint is reached in the good Point
    virtual CATLONG32                   IsConstraintPointOK         (const double                   *  iStartPoint      ,
                                                                           double                   *  iStartTangent    );

   // Search if there is a crossing or not. If there is a singular point, add it
   // and stop if it is requiered. 
    virtual CATLONG32                   ManageSingularity           (const CATMathIntervalND         & iDomain          ,
                                                                           double                   *  NextPoint        ,
                                                                           double                   *  NextTangent      ,
                                                                           CATLONG32                   idiagNextPoint   ,
                                                                           double                    & ioCosAngle       ,
                                                                           CATLONG32                 & ioSlowDown       ,
                                                                           double                    & scal             ,
                                                                           CATMathSetOfPointsND      & SetOfPoints      );

            CATLONG32                   KeepStartOfMarch            (      CATMathSetOfPointsND      & SetOfPoints      );

            double                      SubdomainMinSquareDistance  (const double                   *  pt1              ,
                                                                     const double                   *  pt2              );

  // Data initialisation
  //                                                             pkc le 22/06/2005 mis en protected pour classe derivee
            void                        Initialize                  (const double                   *  iStartPoint      ,
                                                                     const double                   *  iStartTangent    );

  // methods which unscale the parameter (homogenous to the scale )to the natural param
  // methods which scale F so  this vector becomes homogenous to the scale .
            void                        UnScaleX                    (const double                   *  iX               ,
                                                                           double                   *  oX               );
            void                        ScaleFx                     (      double                   *  iFx              ,
                                                                           double                   *  oFx              );
            void                        ScaleJacobianFX             (      CATMathNxNFullMatrix     *  iJacobianFX      ,
                                                                           CATMathNxNFullMatrix     *  oJacobianFX      );
    virtual void                        ScaleGx                     (      double                   *  iGx              ,
                                                                           double                   *  oGx              );
    virtual void                        ScaleJacobianGX             (      double                   *  iJacobianGX      ,
                                                                           double                   *  oJacobianGX      );
            void                        ComputeScaledDomain         (      CATMathIntervalND         & ioDomain         );

            void                        ComputeUnScaledRoots        (      CATMathSetOfPointsND      & ioRoots          );

            void                        ComputeUnScaledRoots        (      double                   *  ioRoots          );

  // Method which  intervines in the control process of the marching.
  // This method is dedicated to be overriden to implement a concrete geometric criterion (void default implementation)
    virtual CATBoolean                  ValidateNextPoint           (      double                   *  CurrentPoint     ,
                                                                           double                   *  NextPoint        ,
                                                                           double                   *  CurrentTangent   ,
                                                                           double                   *  NextTangent      );

  // Advanced Prediction Method 
    virtual void                        AdvancedPrediction          ();

 // Eval Tangent not normalised at a point
            void                        EvalTangentField            (const double                   *  iX               ,
                                                                           double                   *  oTX              ,
                                                                           double                    & prod             );
// Method which removes the duplicate tangents
   virtual void                        RemoveDuplicateTangents      (      CATLONG32                   iN               ,
                                                                           double                   *  ioTX1            ,
                                                                           CATLONG32                 & ioNbTg           ) const;

/////////////
 protected:
/////////////
  // Input
        int ____________________MileStoneProtectedData__________;
  const CATLONG32                            _N;
        short                                _CGMLevel;
        CATLONG32                            _Level;
        CATSoftwareConfiguration           * _Config;


  // Options
        int              ____________________MileStoneOptions_Protected;
        CATLONG32                            _BorderSingularity,
                                             _CheckStepAtBorder;
        CATLONG32                            _CheckStep,
                                             _Client;
        CATMathSystem                      * _SingularSystem;
        CATBoolean                           _AcceptLoopInMaxDomain;

  // Marching data
        int               ____________________MileStoneMarchingData_Protected;
        double                               _Sag,
                                             _MinStep,
                                             _MaxStep;
        // XGN 13/06/2003 : adjustable tolerance for root
        double                               _EpsSol;
        double                             * _MaxStepVect ;
        double                             * _CurrentPoint  ,
                                           * _PreviousPoint ,
                                           * _NextPoint     ,
                                           * _PredictedPoint,
                                           * _StartPoint    ,
                                           * _NewPoint      ,
                                           * _TmpPoint      ;
        CATBoolean                         * _IsSaturated   ;
        CATLONG32                          * _SaturatedVar  ;


  // Output diagnosis
        CATLONG32                            _SingularTangent,
                                             _PseudoSingular,
                                             _Orientation;
  // Diagnosis
        CATMathStopDiagnostic                _BranchDiagnostic;
        CATListPtrCATMathMarchingDiagnostic* _ListStartDiagnostics;
        CATListPtrCATMathMarchingDiagnostic* _ListEndDiagnostics;


        int               ____________________MileStoneXScaleData_Protected;
      // XScale
  #ifdef CATMathImplicitSystem_UseCATFullTolerance
  const CATFullTolerance                   & _TolObject; //   const CATTolerance & _TolObject;
  #else
  const CATTolerance                       & _TolObject; 
  #endif
        double                             * _mu        ,
                                           * _lambda,
                                           * _lambdaG   ;
        CATBoolean                           _ToBeScaled;
        int                                  _UseScaleOption ;
        CATMathAttrScaleOption               _ScaleOption    ; // N.B not to be modified by derived classes: use SetScaleOption() if necessary 


        double                             * _ParamDistortion; //KJD 10Jul09 : RI664293

/////////////
 private:
/////////////
        int               ____________________MileStonePrivateData____________;

        int               ____________________MileStoneOptions;

     struct ConfigOptionsData
       {
        int                                  _ImplicitSystemIsContainingLevel2,
                                             _Sweep_XScaleR19SP6,
                                             _Marching_ActivateLevel8AsDefaultLevel,
                                             _Marching_ParamDistortion,
                                             _Marching_StabilizeQuadraticForm,
                                             _Marching_NonCompleteSetAccepted_TestPointValidity,
                                             _Marching_CheckLastPoints,
                                             _Marching_VerySlowEvolution,
                                             _Marching_FindNewPoint_BorderTreatment,
                                             _Marching_Controles_TangentsInSingularArea,
                                             _Sweep_XScaleR20SP7,
                                             _Marching_Stockage_ScalarComputation,
                                             _Marching_SingularInitCase,
                                             _Marching_FindLastPointWithBS_Situation1Failure,
                                             _Marching_ReviewV1,
                                             _Sweep_XScaleR22SP1,
                                             _Sweep_XScaleR22SP3,
                                             _Marching_CleverSolve_DiagUpdate,
                                             _Marching_SearchEndPoint_ProximityTolerance,
                                             _Marching_DecodingOption_TooThinDomain,
                                             _Marching_FindTangent_StillSingular,
                                             _Marching_RunMultipleSolutions_DiagManagement,
                                             _Marching_Stockage_CurvedSolutionWithEndPoint,
                                             _Marching_PredictionCloseToBorder_V2,
                                             _Sweep_XScaleR23SP3,
                                             _Marching_FindLastPointWithBS_NextPointEval,
                                             _Marching_FindTangent_SingularRegion,
                                             _Marching_Solve_RemoveInitFromExits,
                                             _Marching_FindNewPoint_BorderDivergence,
                                             _Marching_FindNewPoint_SafeNewtonForBorder,
                                             _Sweep_XScaleR24SP3,
                                             _FindLastPoint_SingularityWithoutSingularSystem,
                                             _Marching_StopOnFirstPoint,
                                             _Marching_FindNewPoint_RootWithJacobian,
                                             _Marching_Solve_RemoveInitFromExits2,
                                             _Marching_SearchEndPoint_EndPointAttempts,
                                             _Marching_Solve_RemoveInitFromExits3,
                                             _Marching_FindNewPoint_Loop,
                                             _Marching_Solve_StartPointInMaxDomain,
                                             _Marching_ManageSingularity_BranchOrEndPoint,
                                             _Marching_Solve_AddMaxDomainSet,
                                             _Marching_CleverSolve_Loop,
                                             _Marching_InitializeSolve_ResetInverse,
                                             _XScale_Geometry_R25_SP3,
                                             _Marching_Stockage_EndPointRejected,
                                             _Marching_RunMultipleSol_DiagManagement_Loop,
                                             _Marching_RunMultipleSol_StartDiagManagement,
                                             _Marching_InsideDomain_BorderTol,
                                             _XScale_Geometry_R28_SP1,
                                             _Marching_CheckCurrentSegment_SamePoints,
                                             _ThrowProhibited_RestoreIfThrow,
                                             _StopByDomain_AddSetInStandardCase,
                                             _Marching_Run_TooSmallStep_StopByDomainNearEndPointRetake,
                                             _Marching_SearchEndPoint_SingularityRestriction,
                                             _Marching_CleverSolve_MaxSingularity,
                                             _Marching_SingularPoint_NotBackwards
                                             ;
                                             

       };
        ConfigOptionsData                    _ConfigOptions;

        CATLONG32                            _StopOnSingularity,
                                             _DecompositionOn,
                                             _OnlyDecomposition,
                                             _NotInverse,
                                             _AcceptNonCompleteSet,
                                             _FirstCst,
                                             _LocalTests;
        CATLONG32                            _StoreTangent,
                                             _StoreVector;

        double                             * _Metric;

        double                               _MinDomain;
        CATMathIntervalND                  * _MaxDomain;
        CATMathAttrMultipleDomain          * _MultipleDomain;
        CATMathIntervalND                  * _CurrentDomain;
        CATBoolean                         * _MandatorySaturations; //Tab of domains whose the saturation is required via the CATMathAttrMultipleDomain

        int               ____________________MileStoneInternal;
        CATLONG32                            _Limite,
                                             _ConstraintsMaxDomain,
                                             _SingPt;
        CATLONG32                            _IndexEndPoint,
                                             _IndexStartPoint,
                                             _EndPointAttempts,
                                             _TryRattrap;
        CATLONG32                            _InMaxDomain,
                                             _ThrowProhibited;
        CATMathAttrDecomposition           * _Decomposition;
        CATBoolean                           _PostponeOrientationCheck;

        int               ____________________MileStoneMarchingData;
        double                             * _CurrentTangent,
                                           * _PreviousTangent,
                                           * _NextTangent,
                                           * _StartTangent;
        double                               _CurrentStep,
                                             _DistanceStartHyperplane;
        CATLONG32                            _SolPointNb; //kjd 11May2012

        CATMathSetOfPointsND               * _LocalSet;

        int               ____________________MileStoneEvalData;
        double                             * _Vec1ND,
                                           * _Vec2ND,
                                           * _FX,
                                           * _deltaX;
        double                               _LambdaStep;                      // anciennement _Lambda
        double                             * _BufferForTangentComputation;
        double                             * _MultipleAlloc_N;
        double                             * _CurrentSolAlloc_N;
        CATMathNxNFullMatrix               * _Jacobian;


        int               ____________________MileStoneDiagnosisData;
  // Avertissement : ne pas passer en protected (utiliser GetDiagnostic, SetDiagnostic, GetRunInfo, ...)
        CATMathStopDiagnostic                _Diagnostic,
                                             _SmartDiagnostic;
        CATLONG32                            _ConvergenceInfo,
                                             _TmpConvergenceInfo,
                                             _Filter;
  // Fin Avertissement

  //    CATMathSetOfLongs                  * _ResultStartDiagnostics;
  //    CATMathSetOfLongs                  * _ResultEndDiagnostics;

        CATBoolean                           _CPUThresholdReached;  //KJD 8Jun09 : RI663318
        CATLONG32                            _PointNbAtPreviousStep;//KJD 8Jun09 : RI663318

        int               ____________________MileStoneXScaleData;
        int                                  _UnScaleX_Spy,        //NLD050308 for debug purpose
                                             _ScaleFX_Spy ;        //NLD050308 for debug purpose


/////////////
 private:
/////////////

// Init level data (versionning)
            void                        InitLevel                   (      CATSoftwareConfiguration *  iConfig          );

// Init XScale data
            void                        InitXScale                  (const CATMathAttrList          *  iAttributes      );


// Decoding the options
            void                        DecodingOption              (const CATMathIntervalND         & iDomain          ,
                                                                     const CATMathAttrList          *  iAttributes      = NULL);

// Methode de prediction du nouveau point
            void                        Prediction                  (const CATMathIntervalND         & Domain           ,
                                                                           CATLONG32                   FirstPoint       ,
                                                                           double                      Lambda           ,
                                                                           CATLONG32                   SignConstraint   ,
                                                                           CATMathSetOfPointsND      & SetOfPoints      );
// Methode de correction du point predit i.e convergence de la prediction
            void                        Correction                  (const CATMathIntervalND         & Domain           ,
                                                                           CATLONG32                 & diagNextPoint    ,
                                                                           CATLONG32                 & PointStored      ,
                                                                           double                      Lambda           ,
                                                                           CATLONG32                 & CptTan           ,
                                                                           CATLONG32                 & TangentEnd       ,
                                                                           CATMathSetOfPointsND      & SetOfPoints      );

// Methode qui regroupe les differents controles sur le nouveau point
           void                         Controles                   (const CATMathIntervalND         & Domain           ,
                                                                           CATLONG32                 & CPUError         ,
                                                                           CATLONG32                 & CPUErrorThreshold,
                                                                           CATLONG32                 & SignConstraint   ,
                                                                           CATLONG32                 & FirstPoint       ,
                                                                           CATLONG32                 & diagNextPoint    ,
                                                                           double                    & GX               ,
                                                                           CATLONG32                 & EndPointsGX      ,
                                                                           CATLONG32                 & index            ,
                                                                           CATMathSetOfPointsND      & SetOfPoints      ,
                                                                           double                    & Lambda           ,
                                                                           double                    & scal             ,
                                                                           double                    & CosAngle         ,
                                                                           CATLONG32                 & Exit             ,
                                                                           CATLONG32                 & PointStored      ,
                                                                     const double                   *  iStartPoint      ,
                                                                           double                   *  iStartTangent    );


   // ------------------------
   // Set of points management
   // ------------------------
   // Reset set of points
            void                        Reset                       (      CATMathSetOfPointsND      & Set              );

   // Add a point and its associated tangent if it is required... (And only if different from last point (NLD150713 instead if "from existing points")
            CATLONG32                   AddNewPoint                 (const double                   *  Point            ,
                                                                           double                   *  Tangent          ,
                                                                           CATMathSetOfPointsND      & SetOfPoints      );

   // Same but with specific tolerance (see CATMathSetOfPointsND::AddNewPoint())
   // (tolerance management by CATMathSetOfPointsND: Add if at least one coordinate differs by at least iTolerance, from last point)
            CATLONG32                   AddNewPointWithTol          (const double                   *  Point            ,
                                                                           double                   *  Tangent          ,
                                                                           CATMathSetOfPointsND      & SetOfPoints      ,
                                                                           double                      iTolerance       );

            CATLONG32                   TryToAddPoint               (      CATMathSetOfPointsND      & Set              );

            void                        RemovePoint                 (const CATLONG32                   iIndexToRemove   ,
                                                                           CATMathSetOfPointsND      & SetOfPoints      );

            void                        RemovePoints                (const CATMathSetOfLongs         & iPointsIndex     ,
                                                                           CATMathSetOfPointsND      & SetOfPoints      );
            void                        Truncate                    (      CATLONG32                   NbToKeep         ,
                                                                           CATMathSetOfPointsND      & SetOfPoints      );

            void                        GetOrEvalLastTangent        (      CATMathSetOfPointsND      & SetOfPoints      ,
                                                                           int                         iEvalSingular    ,
                                                                     const double                   *  X                ,
                                                                           double                   *  TX               );


            void                        Stockage                    (const CATMathIntervalND         & Domain           ,
                                                                           CATLONG32                 & diagStockage     ,
                                                                           CATLONG32                 & diagNextPoint    ,
                                                                           double                      GX               ,
                                                                           CATLONG32                   EndPointsGX      ,
                                                                           double                    & Lambda           ,
                                                                           CATLONG32                 & index            ,
                                                                           CATMathSetOfPointsND      & SetOfPoints      ,
                                                                     const double                   *  StartPoint       ,
                                                                           double                   *  StartTangent     );

   // Add a singular point and if it is requested, a tangent
            void                        AddSingularPoint            (const double                   *  iPoint           ,
                                                                           double                   *  iTangent         ,
                                                                           CATMathSetOfPointsND      & ioSetOfPoints    ,
                                                                     const double                      Tol              );

  // Reset the solutions which are not able to finish correctly.
            void                        ClearBadSolution            (const double                   *  iPoint           ,
                                                                           double                   *  iTangent         ,
                                                                           CATMathSetOfPointsND      & SetOfPoints      );

   // Test if a End Point is really on the solution and add it if yes
            CATLONG32                   IsEndPointOK                (const CATMathIntervalND         & iDomain          ,
                                                                           CATLONG32                   diag             ,
                                                                     const double                   *  iStartPoint      ,
                                                                           CATMathSetOfPointsND      & SetOfPoints      );

  // Test if a End Point is really on the solution and add it if yes
            CATLONG32                   IsPredictionOK              (      double                   *  Point            );

  // Search if a point of the endpoint set is near the solution.
            CATLONG32                   SearchEndPoint              (      CATLONG32                   iIsSingular      ,
                                                                           double                      iRatioTol        = 0.);

  // Compute and mange the constraint on the new point.
            void                        ManageConstraint            (      double                    & GX               ,
                                                                           CATLONG32                 & SignConstraint   );

  // Replace Previous by current and current by next
            void                        SwapPointsAndTangents       (      double                   *  PreviousPoint    ,
                                                                           double                   *  CurrentPoint     ,
                                                                           double                   *  NextPoint        ,
                                                                           double                   *  PreviousTangent  ,
                                                                           double                   *  CurrentTangent   ,
                                                                           double                   *  NextTangent      );
  // Initialize and verify data for a good run
            CATLONG32                   InitializeRun               (const CATMathIntervalND         & iDomain          ,
                                                                           double                      GX               ,
                                                                     const double                   *  iStartPoint      , 
                                                                           double                   *  iStartTangent    ,
                                                                           CATMathSetOfPointsND      & ioSetOfPoints    );
  // Wrap function calls for orientation calculation for ease of use
            void                        ComputeOrientation          (const double                   *  StartPoint       ,
                                                                           double                   *  StartTangent     );

   // Metric initialization
            void                        SetMetric                   (const CATMathIntervalND         & iDomain          ); 

   // Find step at starting point
            void                        InitializeStep              (const double                   *  iStartPoint      ,
                                                                     const double                   *  iStartTangent    ,
                                                                           double                    & oStep            );  

// Compute the MaxStep
            void                        ComputeMaxStep              (const CATMathIntervalND         & iDomain          );

// Predictor of Next Point
            void                        Predictor                   (const double                      iLambda          );

// Verify if Current Point is not too far from PreviousPoint
// If the result is one, it's ok.
            CATLONG32                   VerifyStep                  (const CATLONG32                   iFirst           ,
                                                                     const double                      iLambda          );

// Verify if Next Point is not too far from CurrentPoint
// If the result is one, it's ok.
            CATLONG32                   VerifyNewPoint              ();

// Verify if the set of point result is ok.
// If the result is one, it's ok.
            CATLONG32                   VerifySet                   (const CATMathIntervalND         & Domain           ,
                                                                     const CATMathSetOfPointsND     *  iSet             );

// Test if the prediction is in or out of the domain.
            CATLONG32                   OutOfDomain                 (const CATMathIntervalND         & Domain           ,
                                                                           CATLONG32                 & FixedVar         );

// Test if the point is on the border of the domain.
            CATBoolean                  PointOnDomainBorder         (const CATMathIntervalND         & Domain           , 
                                                                           CATLONG32                 & FixedVar         );

// Test if the prediction cross the start point, in case of loop.
            void                        CrossStartPoint             (      double                    & reverse_next     ,
                                                                           double                    & reverse_prev     );

// Verify if StartTangent is correctly oriented in the domain
// If not, change the orientation of the tangent.
            void                        VerifyStartTangent          (const CATMathIntervalND         & iDomain          ,  
                                                                     const double                   *  iStartPoint      ,
                                                                           double                   *  ioStartTangent   );

// Compute the scalar product when decomposition is required
            void                        ComputeScal                 (      double                    & ioScal           ,
                                                                           CATLONG32                   iOnlyDec         ,
                                                                           double                   *  iCurrentTangent  = NULL,
                                                                           double                   *  iNextTangent     = NULL);

// Compute the prediction on the border
            void                        ComputePrediction           (const CATMathIntervalND         & iDomain          ,
                                                                     const double                   *  Adr              ,
                                                                     const double                   *  iCPoint          ,
                                                                     const double                   *  iNPoint          ,
                                                                           CATLONG32                   Var              ,
                                                                           CATLONG32                   border           ,
                                                                           double                   *  oPredPoint       );

// Branch rattrap: extend solution until border (<-- "Compute the rattrappe (???) until the border")
            void                        ComputeBranchRattrap        (      CATMathIntervalND         & WorkDomain       ,
                                                                     const double                   *  Point            ,
                                                                           double                   *  Newtg            ,
                                                                           CATMathSetOfPointsND     *  SetOfPoints      );
   
// Eval estimated square curvature at a point
            double                      EvalSquareCurvature         (const double                   *  iX               ,
                                                                     const double                   *  iTX              ,
                                                                     const double                   *  iXPrev           ,
                                                                     const double                   *  iTXPrev          );

// Check if the marching algorithm has gone from one branch to another
            CATLONG32                   JumpOfBranch                (const CATMathIntervalND         & iDomain          ,
                                                                           double                   *  iCurrentPoint    ,
                                                                           double                   *  iCurrentTangent  ,
                                                                           double                   *  iNextPoint       );  

            CATLONG32                   SingularPointRelevance      (      double                   *  pt_next          ,
                                                                           double                   *  CurrentX         ,
                                                                           double                   *  NextX            ,
                                                                           double                   *  milieu           );

// Find a new point inside the domain or on the boundary of the domain
            CATLONG32                   FindNewPoint                (const CATMathIntervalND         & iDomain          ,
                                                                     const double                   *  iStartPoint      ,
                                                                     const double                   *  iStartTangent    ,
                                                                     const CATLONG32               &  iSetOfPointsSize ,
                                                                           CATLONG32                 & oVar             ,
                                                                           CATMathDiagnostic         & iodiag           );


// Find a new point on the boundary of the domain near a bifurcation
            CATLONG32                   FindLastPoint               (const CATMathIntervalND         & iDomain          ,
                                                                           CATLONG32                 & oVar             );

// Used by FindLastPoint if the CGMLevel is sufficient
            CATLONG32                   FindLastPointWithBS         (const CATMathIntervalND         & iDomain          ,
                                                                           CATLONG32                 & oVar             );
// Find if the point is the curve is or not tangent to the domain
            CATLONG32                   IsTangentPoint              (const CATMathIntervalND         & iDomain          ,
                                                                     const double                   *  iX               ,
                                                                     const double                   *  iTX              ,
                                                                     const CATLONG32                   ivar             ,
                                                                     const double                      tol              );

// Test if the set computed by the run is valid (i.e. long enough, etc)
            CATBoolean                   IsValidSet                 (      CATMathIntervalND         & Domain           ,
                                                                           CATMathSetOfPointsND     *  TabOfSets        );

// Validate the set ending tangent to the boundary of the domain
            CATBoolean                   CheckLastPoints            (      CATMathSetOfPointsND      & SetOfPoints      );

// Check if current segment is really solution (no hole) in some difficult cases
            CATBoolean                   CheckCurrentSegment        ();
   
//  Compute the marching algorithm on one branch of solution:
//   Given a starting point in RN and a normalized oriented tangent in RN at 
//   this point, the Solve method finds  sets of sorted points Xi where F(Xi)=0
//   and each point is in a Domain [Min X1, Max X1]x...x[Min X(N-1), Max X(N-1)]
            CATMathDiagnostic            ComputeBranch              (      CATMathIntervalND         & Domain           ,
                                                                           CATLONG32                 & nb               ,
                                                                           CATLONG32                 & i                ,
                                                                     const double                   *  StartPoint       ,
                                                                           double                   *  StartTangent     ,
                                                                           CATMathSetOfPointsND    **& SetOfPoints      ,
                                                                           CATListPtrCATMathMarchingDiagnostic & ListOfDiag,
                                                                           CATError                 *& oError           );

//  Compute the marching algorithm on a domain:
//  manage the computation of the branches
            CATMathDiagnostic            RunMultipleSolutions       (const CATMathIntervalND         & Domain           ,
                                                                           CATLONG32                 & NumberOfSolutions,
                                                                           CATLONG32                 & size             ,
                                                                           double                   *  StartPoint       ,
                                                                           CATMathSetOfPointsND    **& GeneralSet       ,
                                                                           double                   *  StartTangent     ,
                                                                           CATError                 *& oError           );
// Increase the size of a tab os setofpoints
            void                         Reallocation               (      CATLONG32                   newsize          ,
                                                                           CATLONG32                 & oldsize          ,
                                                                           CATMathSetOfPointsND    **& TabOfSets        );
// Increase the size of a tab of setofpoints if necessary
            void                         ReallocationIfNecessary    (      CATLONG32                   NecessarySize    ,
                                                                           CATLONG32                 & ioSize           ,
                                                                           CATLONG32                   NumberOfSolutions,
                                                                           CATMathSetOfPointsND    **& TabOfSets        );

            void                         RemoveListOfMarchingDiagnostic
                                                                    (      CATListPtrCATMathMarchingDiagnostic*& ioList);

//  Expand the domain to the maxdomain:
//  Verify, first,  that the max domain is not equal as the domain
//  Compute the good direction for the extention.
   virtual CATLONG32                     ExpandDomain               (      CATMathIntervalND         & Domain           ,
                                                                     const double                   *  Point            );

// Store the current domain in the private data _CurrentDomain
           void                          SetCurrentDomain           (const CATMathIntervalND         & Domain           );

// Test if a point is interior of a domain
           CATLONG32                     InsideDomain               (      CATMathIntervalND         & WorkDomain       ,
                                                                     const double                   *  Init             ,
                                                                     const double                   *  iTangent         );
// Visualisation et aide de debug
           void                          VisualizeEntries           (const char                     *  MethodName       ,
                                                                     const CATMathIntervalND         & Domain           ,
                                                                     const CATLONG32                   NumberOfStartPoints,
                                                                     const double                   *  StartPoint       ,
                                                                           double                   *  StartTangent     );

           void                          VisualizeResult            (      CATMathSetOfPointsND      & oSetOfPoints     ,
                                                                           int                         iLevel           );
           void                          VisualizeDiags             (                                                   );

           double                        GetSquareDistance          (const double                   *  iP0              ,
                                                                     const double                   *  iP1              );

           CATBoolean                    FindConstraintChangeOfSign (const CATMathIntervalND         & iDomain          ,
                                                                     const double                   *  iX1              ,
                                                                           double                      iValue1          ,
                                                                     const double                   *  iX2              ,
                                                                           double                      iValue2          ,
                                                                           double                   *  ioX              ,
                                                                           double                    & oSquareDistanceWithPreviousPoints);

   virtual void                          ComputePseudoNorm          (double &ioNorm                                     ,
                                                                     double &ioProduct                                  );
           
protected:
   virtual CATLONG32                     FindConstraintChangeOfSign (const CATMathIntervalND         & iDomain          ,
                                                                     const double                   *  iX0              ,
                                                                           double                      iValue0          ,
                                                                     const double                   *  iX1              ,
                                                                           double                      iValue1          ,
                                                                     const double                   *  iX2              ,
                                                                           double                      iValue2          , 
                                                                           double                   *  ioX              ,
                                                                           double                    & oSquareDistanceWithPreviousPoints);

// subprogram for SolveOnHyperPlane
           double                        ComputeEpsilonSquaredPower (const double                   *  u                ,
                                                                     const double                      d                ,
                                                                           double                   *  XRoot            ,
                                                                           int                         UseXRoot         ) ;

// Solve the quadratic form a x^2+ 2*b*xy + c y^2=0,
// return the number of solutions and fill the solutions in oSolutions
// N.B a,b,c should not depend on scale NLD211207
           CATLONG32                     SolveQuadraticForm         (const double                      a                ,
                                                                     const double                      b                ,
                                                                     const double                      c                ,
                                                                           double                      oSolutions    [4],
                                                                     const CATTolerance              & iTolObject       );

// Adds a set in a set considering implicit set of points type (managed with _StoreTangent and _StoreVector)
           void                          AddSetInSet                (      CATMathSetOfPointsND     *  iSet             ,
                                                                     const CATMathSetOfPointsND     *  iSetToConcatenate,
                                                                           CATBoolean                  iMerge           );
// Copy a set in a new Set
           CATMathSetOfPointsND        * NewSet                     (      CATMathSetOfPointsND     *  iSet             );

// Add a set in an array of sets, with reallocation if necessary, size increase, and number of sets increment
           void                          AddSetInArrayOfSet         (      CATMathSetOfPointsND     *  iSet             ,
                                                                           CATLONG32                 & oNbSet           ,
                                                                           CATLONG32                 & size             ,
                                                                           CATMathSetOfPointsND    **& TabOfSets        );


// Data initialisations needed for the solve (single or multiple)
           void                          InitializeSolve            ();

protected:
// (Solve subroutine) Indicates if current Set must be added in global solution set
           int                           SolveAddSetInSet           ();


           void VectorialProduct                                    (const CATLONG32              N                     ,
                                                                           CATMathNxNFullMatrix * M                     ,
                                                                           double               * DFX                   );

           double                        ComputeMatrixNorm          (      CATLONG32                   iN               ,
                                                                     const CATMathNxNFullMatrix     *  iM               );
//WARNING : GetJacobian  doesn't fill the matrix if its size is not the same as the one of the internal attribute _Jacobian
           void                          GetJacobian                (       CATMathNxNFullMatrix &ioJac                 ) const; 
};

//----------------------------------------------------------------------------------------------------------------
//                                              INLINE
//----------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------
INLINE     CATLONG32 CATMathImplicitSystem::GetNumberOfVariables ()
{
   return _N;
}

//----------------------------------------------------------------------------------------------------------------
INLINE     CATLONG32 CATMathImplicitSystem::GetIndexEndPoint     ()
{
   return _IndexEndPoint;
}

#endif
