#ifndef CATMathSystemXY_H
#define CATMathSystemXY_H
// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATMathSystemXY
// Abstract class of non linear 2x2 systems
//
//===================================================================
//
// Usage notes:
//
// * This is an abstract class; 
//   redefine the following pure virtual functions in derived classes:
//
//   virtual CATMathClassId IsA  ()                                   const = 0;
//   virtual double         EvalF(const double & x, const double & y) const = 0;
//   virtual double         EvalG(const double & x, const double & y) const = 0;
//
// * For maximum performance, redefine the following virtual methods
//   in derived classes:
//   void EvalF(const double    & u,
//              const double    & v, 
//                    double    & pt,
//                    double    & derivX,
//                    double    & derivY)                             const;
//   void EvalG(const double    & u,
//              const double    & v, 
//                    double    & pt,
//                    double    & derivX,
//                    double    & derivY)                             const;
//   void EvalF(const double    & uStart,
//              const double    & uEnd,
//              const double    & vStart,
//              const double    & vEnd,
//              const CATLONG32   Nu,
//              const CATLONG32   Nv,
//                    double   *  pt,
//                    double   *  derivX,
//                    double   *  derivY)                             const;
//
// * XScale behaviour:
//   Solve() methods receive user parameters, and give back user roots,
//   but internally work on rescaled parameters, varying like power 1
//   of factory scale, according to scale option (implicit, or explicit if SetScaleOption() used.
//   So, most internal methods work on rescaled parameters,
//   and this must be taken into account in methods derivations
//
//===================================================================
// 15/02/08 NLD Ajout _ScaleOption, SetScaleOption(), SetEps()
//              Ajout de _UserEpsSolSet, _UserEpsSolValue, _UserEpsSolIsRelative
//              et argument iIsRelative a SetEpsSol()
// 13/10/09 KJD introduction versioning
//              (GetVersioningLevel(), GetConfig(), _IsUnStreamed)
// 04/03/11 NLD Mise au propre du versionning: ajout Init()
//              (2eme phase avec complement imperatif de securite le 18/11/13:
//               interdiction du constructeur par defaut,
//               gestion du constructeur par copie)
// 19/09/11 NLD Ajout de SetIsUnStreamed()/GetIsUnStreamed() pour interdiction d'accès direct à _IsUnStreamed,
//              (passant de protected à private)
//              par les classes filles, et gestion cohérente des impacts de sa modification
//              Ajout de _CGMLevelNoDirectAccess
//              On met fin à de dangereuses ouvertures potentielles:
//              SetEpsSol() et SetEpsSing() sont beaucoup trop sensibles pour rester virtuelles
//              Ajout _DSolveNumber
//              Ajout de InitEpsSol()
// 21/09/11 NLD Ajout de GetAbsErr()
// 26/09/11 R1Y Added the function GetToleranceObject() (for comparing geometries).
// 18/11/13 NLD Declaration en private des constructeurs par defaut et par copie, ainsi que de l'operateur =,
//              dont l'implementation par defaut etait forcement invalide.
//              Desactivation de l'ancien constructeur sans CATSoftwareConfiguration
//              Alternative par precompilation pour fourniture d'un constructeur par copie
//              et d'un operateur = valides
//              Reordonnancement logique des declarations des donnees membres, regroupements
//              et explicitation des roles
//              Colonnage des declarations
// 19/11/13 NLD Ajout ComputeUnScaledDomain()
//              Ajout UnScaleU() et UnScaleV(), ScaleF() et ScaleG() sur intervalles
//              Ajout ScaleDFX(), ScaleDFY(), ScaleDGX(), ScaleDGY() sur intervalles
// 21/11/13 NLD XScale:
//              - Specification des hypotheses pour les arguments des methodes derivables
//                (domaine utilisateur / domaine de travail standard a la puissance 1 du scale) 
//              - Specification du comportement general dans les "Usage notes"
// 22/11/13 NLD Le seul constructeur conservé definit une valeur par defaut de la configuration,
//              afin de permettre la création de systeme sans specification explicite d'arguments
//              Ajout IsA_Safe() pour fourniture de la fonctionnalité IsA() en mode degradé
//              mais securisé directement ou indirectement sous le constructeur
//              Ajout _State
// 23/07/14 NLD Deflaggages CATMathSystemXY_ShuntInvalidConstructors
//                          CATMathSystemXY_ShuntOldConstructors
//              et          CATMathSystemXY_ImplementCopyConstructor
//===================================================================
#define CATMathSystemXY_ShuntInvalidConstructors  "Activation  NLD181113"

//===================================================================
#include "YN000FUN.h"

#include "CATMathDef.h"
#include "CATMathDiagnostic.h"
#include "CATMathSetOfPointsND.h"
#include "CATMathIntervalND.h"
#include "CATCGMVirtual.h"
#include "CATTolerance.h"
#include "CATMathAttrScaleOption.h"
//#include "CATMathScaleSystemXY.h"
//#include "CATMathNxNFullMatrix.h"
class CATMathInterval;
class CATMathInterval2D;
class CATMathAttrList;
class CATMathAttribute;
class CATMathSetOfPoints2D;
class CATSoftwareConfiguration;

//-------------------------------------------------------------------
class ExportedByYN000FUN CATMathSystemXY : public CATCGMVirtual
{

 public:
                                            //-----------------------------------------------------------------------------------------
                                            // Valid constructor to use
                                            //-----------------------------------------------------------------------------------------
   //                                                            // N.B Si un jour suppression des valeurs par defaut il faudra retablir
   //                                                            //     en private seulement,le constructeur par defaut, pour le rendre inaccessible. NLD230714
                                            CATMathSystemXY(         CATSoftwareConfiguration *  iConfig    = NULL,
                                                            const    CATTolerance              & iTolObject = CATGetDefaultTolerance(),
                                                            const    CATMathAttrList          *  iattr      = NULL);

   //-----------------------------------------------------------------------
   // special constructors and copy operator. Work in progress. TO FORGET. Use above constructor
   //-----------------------------------------------------------------------
#ifndef CATMathSystemXY_ShuntInvalidConstructors
private:

                                            // invalid constructor not to use
   //                                                            // Malheureusement celui-ci semble avoir des utilisations applicatives (hasardeuses)
   //                                                            // (Non: en fait en l'absence de construction implicite, il y avait branchement
   //                                                            // sur le constructeur sans configuration et avec tolerance par defaut)
   //                                                            // 
                                            CATMathSystemXY();
#endif

 protected:
                                            CATMathSystemXY(const    CATMathSystemXY           & iSXY);
                 CATMathSystemXY &          operator =     (const    CATMathSystemXY           & iSXY);

 public:
   //-----------------------------------------------------------------------
   //- Virtual destructor
   //-----------------------------------------------------------------------
   virtual                                 ~CATMathSystemXY();

   //-----------------------------------------------------------------
   // Information methods
   //-----------------------------------------------------------------
                 CATSoftwareConfiguration * GetConfig         ()                                                const;
                 short                      GetVersioningLevel(      char                     *  iModifId = "") const;
   virtual       CATBoolean                 IsAKindOf         (const CATMathClassId              iClassId )     const;
   virtual       CATBoolean                 IsOption          (const CATMathOption               IOption  )     const;
   virtual       CATMathClassId             IsA               ()                                                const = 0;
                 void                       SetMaxRootNumber  (      CATULONG32                  iMaxNb   );
                 CATULONG32                 GetMaxRootNumber  ()                                                const;
           const CATTolerance             & GetToleranceObject()                                                const;

   //-----------------------------------------------------------------
   // Evaluators on doubles
   //-----------------------------------------------------------------
   //
   //                                                                                                       // *** XScale: on recoit des (u, v) ramenes
   //                                                                                                       // ***         au standard (puissance 1 du Scale)
   //                                                                                                       // *** par ComputeScaledDomain().
   //                                                                                                       // *** la derivation eventuelle de ces methodes
   //                                                                                                       // *** doit donc utiliser
   //                                                                                                       // *** UnScaleU(), UnScaleV() sur les entrees
   //                                                                                                       // *** ScaleF(), ScaleG(), ScaleDFX(), ... sur les sorties                          
   //                                                                                                       //                                                         NLD191113

   // pure virtual methods
   virtual       double                     EvalF             (const double                    & x        ,
                                                               const double                    & y        ) const = 0;

   virtual       double                     EvalG             (const double                    & x        ,
                                                               const double                    & y        ) const = 0;

   // Evaluation of derivatives on doubles
   //                          for instance EvalFirstDerivFX computes first partial derivative of F with x variable.                                                   NLD191113
   virtual       double                     EvalFirstDerivFX  (const double                    & x        ,
                                                               const double                    & y        ) const;
   virtual       double                     EvalFirstDerivFY  (const double                    & x        ,
                                                               const double                    & y        ) const;

   virtual       double                     EvalFirstDerivGX  (const double                    & x        ,
                                                               const double                    & y        ) const;
   virtual       double                     EvalFirstDerivGY  (const double                    & x        ,
                                                               const double                    & y        ) const;
   
   virtual       double                     EvalSecondDerivFX2(const double                    & x        ,
                                                               const double                    & y        ) const;
   virtual       double                     EvalSecondDerivFXY(const double                    & x        ,
                                                               const double                    & y        ) const;
   virtual       double                     EvalSecondDerivFY2(const double                    & x        ,
                                                               const double                    & y        ) const;

   virtual       double                     EvalSecondDerivGX2(const double                    & x        ,
                                                               const double                    & y        ) const;
   virtual       double                     EvalSecondDerivGXY(const double                    & x        ,
                                                               const double                    & y        ) const;
   virtual       double                     EvalSecondDerivGY2(const double                    & x        ,
                                                               const double                    & y        ) const;   

   //
   // Evaluator of function and derivatives at the same time :
   // (performance are increased if redefined in derived classes)
   // iOption is a command which contains which derivatives are requested
   // (usually, iOption = OptionEval + OptionEvalFirstDeriv)
   //
   //                                                                                                       // *** XScale: on recoit des (u, v) ramenes
   //                                                                                                       // ***         au standard (puissance 1 du Scale)
   //                                                                                                       // *** par ComputeScaledDomain().
   //                                                                                                       // *** la derivation eventuelle de ces methodes
   //                                                                                                       // *** doit donc utiliser
   //                                                                                                       // *** UnScaleU(), UnScaleV() sur les entrees
   //                                                                                                       // *** ScaleF(), ScaleG(), ScaleDFX(), ... sur les sorties                          
   //                                                                                                       //                                                         NLD191113
   virtual       void                       EvalF             (const double                      u        ,
                                                               const double                      v        , 
                                                               const CATMathOption               iOptions ,
                                                                     double                   *  f        ,
                                                                     double                   *  fx       = 0,
                                                                     double                   *  fy       = 0,
                                                                     double                   *  fx2      = 0,
                                                                     double                   *  fxy      = 0,
                                                                     double                   *  fy2      = 0) const;
   virtual       void                       EvalG             (const double                      u        ,
                                                               const double                      v        , 
                                                               const CATMathOption               iOptions ,
                                                                     double                   *  f        ,
                                                                     double                   *  fx       = 0,
                                                                     double                   *  fy       = 0,
                                                                     double                   *  fx2      = 0,
                                                                     double                   *  fxy      = 0,
                                                                     double                   *  fy2      = 0) const;

   //
   // Multi-evaluation of function and derivatives on a regular 
   // grid of Nu x Nv points delimited by  iDomain
   // If NbPoints[0]=1 and/or NbPoints[1]=1 then the evaluations
   // are made on the smallest corresponding coordinate in iDomain
   // WARNING : the pointers must be previously allocated if the
   // corresponding evaluations are needed.
   // The value f[Nv*i+j] contains Eval(x_i,y_j) ...
   //
   virtual       void                       EvalF             (const CATMathIntervalND         & iDomain  ,
                                                               const CATLONG32                *  NbPoints ,
                                                               const CATMathOption               iOptions ,
                                                                     double                   *  f        ,
                                                                     double                   *  fx       = 0,
                                                                     double                   *  fy       = 0,
                                                                     double                   *  fx2      = 0,
                                                                     double                   *  fxy      = 0,
                                                                     double                   *  fy2      = 0) const;

   virtual       void                       EvalG             (const CATMathIntervalND         & iDomain  ,
                                                               const CATLONG32                *  NbPoints ,
                                                               const CATMathOption               iOptions ,
                                                                     double                   *  f        ,
                                                                     double                   *  fx       = 0,
                                                                     double                   *  fy       = 0,
                                                                     double                   *  fx2      = 0,
                                                                     double                   *  fxy      = 0,
                                                                     double                   *  fy2      = 0) const;


   //-----------------------------------------------------------------
   // Solver interfaces
   //-----------------------------------------------------------------

   //                                *********************************
   //                                * Autant la déclaration et le caractère "virtual" sont légitimes
   //                                * pour les méthodes d'évaluation Eval*() ci-dessus,
   //                                * autant, pour les methodes qui suivent,
   //                                * ils induisent de délicates ouvertures,
   //                                * (car nécessitant une définition précise des spécifications et interdictions
   //                                * et rendent plutot difficile le maintien en bon fonctionnement de la classe de base)
   //                                * Pour les méthodes suivantes,
   //                                * nous indiquons            X si existence de derivation,
   //                                *                           O sinon
   //                                *                                             (étude du 01/02/12 NLD)
   //                                * - Solve()                 O
   //                                * - SolveSafeNewton()       O
   //                                * - IsNull()                O légitime mais délicate
   //                                * - SetEpsSol()             O déclassée non virtuelle le 19/11/11 NLD
   //                                * - SetEpsSing()            O déclassée non virtuelle le 19/11/11 NLD
   //                                * - SetScaleOption()        O
   //                                * - AddSolution()           O
   //                                * - ISolve()                O
   //                                * - DSolve()                O
   //                                * - GetStepMarching()       X <-- 
   //                                * - CandidateF()            O
   //                                * - SuspectF()              O
   //                                * - CandidateFG()           O
   //                                * - CandidateFSuspectG()    O
   //                                * - TopologicalDegree()     O
   //                                * - SeparateOnEdge()        O
   //                                * - ExclusionRadiusOnZero() O
   //                                * - EdgeTreatment()         O
   //                                * - TryTopologicalDegree()  O
   //                                * - TreatEdgeSolution()     O
   //                                * - DSolveMinusBox()        O
   //                                * - NewtonDichotomy()       O
   //                                * - SafeNewton()            O
   //                                * - IsChangingSignOnEdge()  O
   //                                * - IsLoopInSquare()        O
   //                                * - TryTwoBranchesByEdge()  O
   //                                * - HyperbolicSingularity() O
   //                                * - AreSeparateSolutions()  O
   //                                * - FletcherReeves()        O
   //                                * - TryMarching()           O
   //                                * - SolveOnLine()           O
   //                                * - TreatSmallSubDomain()   O
   //                                *********************************

   // Solver on a rectangle
   //
   //                                                                                                       // *** XScale: on recoit un domaine
   //                                                                                                       // ***         dans l'espace utilisateur,
   //                                                                                                       // ***         et non pas ramene au standard (puissance 1 du Scale)
   //                                                                                                       //                                                         NLD211113
   virtual       CATMathDiagnostic          Solve             (const CATMathInterval2D         & iDomain     ,
                                                                     CATMathSetOfPointsND      & ioRoots     ,
                                                               const CATMathAttrList          *  iattributes = 0);

   //
   // Safe Newton Method to find a root in iD.
   // try to stay in iD in the iterations, using (ioX,ioY) as an init.
   // Return 1 of success, 0 else. (ioX,ioY) contains the solution in output.
   //
   //                                                                                                       // *** XScale: on recoit un domaine
   //                                                                                                       // ***         dans l'espace utilisateur,
   //                                                                                                       // ***         et non pas ramene au standard (puissance 1 du Scale)
   //                                                                                                       //                                                         NLD211113
   virtual       CATBoolean                 SolveSafeNewton   (      double                    & ioX         ,
                                                                     double                    & ioY         ,
                                                               const CATMathInterval2D         & iD          );

   //
   //  IsNull is a method to determine if (F(u),G(u)) = (f,g) can be considered as null 
   //  at (x,y) and oNorm is any norm  of (F(u),G(u)). jac is a pointer containing the 4 values
   //  of the derivatives of F and G at (x, y). jac can be null.
   //  This method can be rederived for precision problems.
   //  
   //  This default method tests if |f|+|g| < CATEpsSol * (1+|fx|+|fy|+|gx|+|gy|) if jac != 0,
   //  otherwise it tests        if |f|+|g| < CATEpsSol.
   //
   //                                                                                                       // *** XScale: on recoit des (x, y) ramenes
   //                                                                                                       // ***         au standard       (puissance 1 du Scale)
   //                                                                                                       // ***         par ComputeScaledDomain().
   //                                                                                                       // **          et des (f, g) issus de EvalF(), EvalG(),
   //                                                                                                       // **          donc homogenes et aussi au standard (puissance 1 du Scale)
   //                                                                                                       //                                                         NLD211113
   virtual       CATBoolean                 IsNull            (const double                      x           ,
                                                               const double                      y           ,
                                                               const double                      f           ,
                                                               const double                      g           ,
                                                                     double                    & oNorm       ,
                                                               const double                   *  jac         = 0);

   // In certain cases,
   // - we need to be able to release the tolerance for root                             (SDP 06/06/2001)
   // - a relative tolerance may be used to handle heterogeneous functions F and G, 
   //   then tolerance scaling will be done by this object                               (NLD150208)
   // - if not, tolerance must be given in user space
   // (method no more virtual, for consistent tolerances management)                     (NLD190911)
                 void                       SetEpsSol         (const double                      NewEpsSol   ,
                                                                     int                         iIsRelative = 0);
   
   // Set to adjust singular tolerance (used in Coupling projection)                     (RHA 24/06/2005)
   // (method no more virtual, for consistent tolerances management)                     (NLD190911)
                 void                       SetEpsSing        (const double                      NewEpsSing  );

   // To set scale option immediatly after constructor. BUT BEFORE SetEpsSol()           (NLD15/02/08)
   virtual       void                       SetScaleOption    (      CATMathAttrScaleOption   *  iScaleOption);

  // To be replaced by versionning
                 void                       SetLevel          (      CATLONG32                   iLevel      );

   //
   // protected methods
   //
 protected:
   // XScale scaling/unscaling methods:
   // - methods UnScaleU(), UnScaleV () which unscale the parameter (homogeneous to the scale )to the natural param
   // - methods ScaleF  (), ScaleG   () which   scale F and G so this these vectors become homogeneous to the scale .
   // - methods ScaleDF*(), ScaleDG* () which   scale F and G derivatives consistently with ScaleF() and ScaleG()
   // - method  ComputeScaledDomain  () which   scale domain from user     definition                           to internal definition homogeneous to the scale
   // - method  ComputeUnScaledDomain() which unscale domain from internal definition (homogeneous to the scale)to user     definition 
   // - methods ComputeUnScaledRoots () which unscale roots  from internal definition (homogeneous to the scale) to user definition
                 double                     UnScaleU          (const double                    & iu          ) const ;
                 double                     UnScaleV          (const double                    & iv          ) const ;
                 CATMathInterval            UnScaleU          (const CATMathInterval           & iu          ) const ;
                 CATMathInterval            UnScaleV          (const CATMathInterval           & iv          ) const ;
                 double                     ScaleF            (      double                    & iF          ) const ;
                 double                     ScaleG            (      double                    & iG          ) const ;
                 CATMathInterval            ScaleF            (const CATMathInterval           & iF          ) const ;
                 CATMathInterval            ScaleG            (const CATMathInterval           & iG          ) const ;
                 double                     ScaleDFX          (      double                    & iDFX        ) const ;
                 double                     ScaleDFY          (      double                    & iDFY        ) const ;
                 double                     ScaleDGX          (      double                    & iDGX        ) const ;
                 double                     ScaleDGY          (      double                    & iDGY        ) const ;

                 CATMathInterval            ScaleDFX          (const CATMathInterval           & iDFX        ) const ;
                 CATMathInterval            ScaleDFY          (const CATMathInterval           & iDFY        ) const ;
                 CATMathInterval            ScaleDGX          (const CATMathInterval           & iDGX        ) const ;
                 CATMathInterval            ScaleDGY          (const CATMathInterval           & iDGY        ) const ;

                 double                     ScaleDFX2         (      double                    & iDFX2       ) const ;
                 double                     ScaleDFXY         (      double                    & iDFXY       ) const ;
                 double                     ScaleDFY2         (      double                    & iDFY2       ) const ;
                 double                     ScaleDGX2         (      double                    & iDGX2       ) const ;
                 double                     ScaleDGXY         (      double                    & iDGXY       ) const ;
                 double                     ScaleDGY2         (      double                    & iDGY2       ) const ;

                 void                       ComputeScaledDomain (    CATMathInterval2D         & ioDomain    );
                 void                       ComputeUnScaledDomain(   CATMathInterval2D         & ioDomain    );
                 void                       ComputeUnScaledRoots(    CATMathSetOfPointsND      & ioRoots     );
                 void                       ComputeUnScaledRoots(    double                   *  ioRoots     );
 
   // redefinition d'un epsilon relatif a la fonction
                 void                       SetEps            (const double                      iNewEps     ,
                                                                     int                         iIsRelative ,
                                                                     double                    & oGlobalEps  ) ;

   virtual       CATLONG32                  AddSolution       (const double                    & x           ,
                                                               const double                    & y           );

   // Interval Solver
   //                                                                                                       // *** XScale: l'intervalle D doit avoir ete ramene
   //                                                                                                       // ***         au standard (puissance 1 du Scale)
   //                                                                                                       // *** par ComputeScaledDomain().                          NLD191113
   virtual       CATLONG32                  ISolve            (const CATMathInterval2D         & D           ,
                                                               const CATMathAttrList          *  attributes  );

   // ParmEval Solver
   //                                                                                                       // *** XScale: l'intervalle [xMin,xMax]*[yMin,yMax]  doit avoir ete ramene
   //                                                                                                       // ***         au standard (puissance 1 du Scale)
   //                                                                                                       // *** par ComputeScaledDomain().                          NLD191113
   virtual       CATLONG32                  DSolve            (const double                    & xMin        ,
                                                               const double                    & xMax        ,
                                                               const double                    & yMin        ,
                                                               const double                    & yMax        ,
                                                               const CATLONG32                   sampleX     ,
                                                               const CATLONG32                   sampleY     );

   // Step marching : valeur utilisee par TryMarching 
   // pour decider si le systeme est mal conditionne ou non
   // Pour des solveurs naturellement plus stables (ex : PCrvPCrv),
   // la valeur par defaut peut etre augmentee.
   //                                                                                                       // *** XScale: le pas rendu doit avoir ete ramene
   //                                                                                                       // ***         au standard (puissance 1 du Scale)
   //                                                                                                       // ***         car utilise sur un domaine issu de ComputeScaledDomain(). 
   //                                                                                                       // ***                                                     NLD191113
   virtual       double                     GetStepMarching   ();

   // Sets _IsUnStreamed to 1; means that system is unstreamed
                 void                       SetIsUnStreamed   ();

   // Gets _IsUnStreamed  ; 1 means that system is unstreamed
                 int                        GetIsUnStreamed   () const;



  //
  // protected data
  // --------------
protected:
  

         CATMathSetOfPointsND       * _roots        ;        // Solve roots

  const  CATMathInterval2D          * _Def          ;        // Solve definition interval

  // 
  //                                                   // XScale management. 1) (Tolerance management dedicated data)
  //                                                   // -----------------
  const  CATTolerance               & _TolObject    ;
         double                       _mu        [2],        // X and Y parameters scaling values
                                      _lambda    [2];        // F and G functions  scaling values
         CATBoolean                   _ToBeScaled   ;        // scaling indicator (indicates if X, Y, F or G not respecting standard XScale hypotheses)
  //     CATMathScaleSystemXY       * _ScaleSystem  ;

                                                       // Tolerances and steps
                                                       // --------------------
                                                       // (cqi variables; used by no derivated class as of Nov 18th 2013. NLD)
         double                       _CATUnScaledEpsSol  ;  // default EpsSol value in       standard factory.              (default: not taking into account SetEpsSol() call)
         double                       _CATScaledEpsSol    ;  // default EpsSol value scaled in current factory.              (default: not taking into account SetEpsSol() call)
         double                       _CATSqrScaledEpsSol ;  // default EpsSol value scaled in current factory, and squared. (default: not taking into account SetEpsSol() call)
         double                       _CATMathStepMarching;
  //
  // private data
  // ------------
private:
  //                                                   // Configuration and replay management
  //                                                   // -----------------------------------
         CATSoftwareConfiguration   * _Config;
         int                          _CGMLevelNoDirectAccess;
         int                          _IsUnStreamed;             // (NLD190911 de protected en private) KJD 13OCT2009 softwareconfig pour "versioning"
         CATLONG32                    _Level;


  //                                                   // Solve management
  //                                                   // ----------------
  //                                                   // Solve 1) solve specifications
         CATLONG32                    _MaxRootNb;
  //                                                   // Solve 2) solve internal data
         double                       _SmallWidthX,
                                      _SmallWidthY;
         CATLONG32                    _IllConditionnedSystemIndicator;
         CATLONG32                    _DSolveNumber;
         CATLONG32                    _DSolveDepth;
         CATLONG32                    _SingularityMaxDepth;
         CATMathIntervalND            _TmpIntervalND;         // (a usage tres local pour eviter cout de construction certainement) de protected in private le 18/11/13 NLD

  //                                                   // XScale management. 2)
  //                                                   // -----------------
         CATMathAttrScaleOption       _ScaleOption ;
         int                          _UseScaleOption ;

  //                                                   // Tolerances and steps
  //                                                   // --------------------
  //                                                   // (SDP 06/06/2001 : adjustable tolerance for root)
         int                          _UserEpsSolSet ;
         double                       _UserEpsSolValue ; 
         int                          _UserEpsSolIsRelative ;
         double                       _EpsSol,
                                      _EpsSing,
                                      _EpsNull;
         double                       _h1,
                                      _h2,
                                      _h3;

  //                                                   // Debug data
  //                                                   // ----------
         CATBoolean                   _GraphicDebug;
  //                                                   // LifeCycle data
  //                                                   // ----------
         CATBoolean                   _State;

   //
   // private methods
   // ---------------
 private:

                 void                       Init              (      CATSoftwareConfiguration *  iConfig    ,
                                                               const CATMathAttrList          *  attributes );

                 void                       InitEpsSol        (      int                         iCGMLevel  ,
                                                                     int                         iFirstCall = 0);

                 CATMathClassId             IsA_Safe          ()                                                const;

                 double                     GetAbsErr         (      int                         iCGMLevel  );

                 void                       InitByCopy        (const CATMathSystemXY           & iSXY);

   virtual CATLONG32 CandidateF        (const double & f00,
                                        const double & f01, 
                                        const double & f10,
                                        const double & f11,
                                        const double   ft00t01,
                                        const double   ft01t11,
                                        const double   ft11t10,
                                        const double   ft10t00,
                                        const double & xMin, const double & xMax,
                                        const double & yMin, const double & yMax);

   virtual CATLONG32 CandidateFG       (const double & f00    , const double & f01, 
                                        const double & f10    , const double & f11,
                                        const double   ft00t01, const double   ft01t11,
                                        const double   ft11t10, const double   ft10t00,
                                        const double & g00    , const double & g01, 
                                        const double & g10    , const double & g11,
                                        const double   gt00t01, const double   gt01t11,
                                        const double   gt11t10, const double   gt10t00,
                                        const double & xMin   , const double & xMax,
                                        const double & yMin   , const double & yMax);
   
   
   virtual CATLONG32 SuspectF          (const double & f00 ,
                                        const double & f01 , 
                                        const double & f10 ,
                                        const double & f11,
                                        const double & fx00, const double & fx01, 
                                        const double & fx10, const double & fx11,
                                        const double & fy00, const double & fy01, 
                                        const double & fy10, const double & fy11,
                                        const double & xMin, const double & xMax,
                                        const double & yMin, const double & yMax);

   virtual CATLONG32 CandidateFSuspectG(const double & f00 ,
                                        const double & f01 , 
                                        const double & f10 ,
                                        const double & f11 ,
                                        const double & g00 ,
                                        const double & g01 , 
                                        const double & g10 ,
                                        const double & g11 ,
                                        const double & gx00, const double & gx01, 
                                        const double & gx10, const double & gx11,
                                        const double & gy00, const double & gy01, 
                                        const double & gy10, const double & gy11,
                                        const double & xMin, const double & xMax,
                                        const double & yMin, const double & yMax);
  
   virtual CATLONG32 TopologicalDegree (const double & f00 ,
                                        const double & f01 , 
                                        const double & f10 ,
                                        const double & f11 ,
                                        const double & g00 ,
                                        const double & g01 , 
                                        const double & g10 ,
                                        const double & g11 ,
                                        const double & xMin, const double & xMax,
                                        const double & yMin, const double & yMax);



   virtual CATLONG32 SeparateOnEdge    (const double & f0,
                                        const double & f1,
                                        const double & g0,
                                        const double & g1,
                                        const double & t0,
                                        const double & t1,
                                        const double & ufixed, const double & u2,
                                        const CATLONG32 whatfixed,
                                              double & f, double & g);

   virtual double    ExclusionRadiusOnZero(const double & x, const double & y);   

   virtual CATLONG32 EdgeTreatment     (const double & f0,
                                        const double & f1,
                                        const double & g0,
                                        const double & g1,
                                        const double & t0,
                                        const double & t1,
                                        const double & ufixed, const double & u2,
                                        const CATLONG32 whatfixed,
                                              CATBoolean * Vanish, CATLONG32 & Index);
                   

   virtual CATLONG32 TryTopologicalDegree(const CATBoolean * Vanish, const CATLONG32 Index);
  
   virtual CATLONG32 TreatEdgeSolution  (const double & t0,
                                         const double & t1, 
                                         const double & t, const double & ufixed,  
                                         const double & u2, const CATLONG32 whatfixed);
  
   virtual CATLONG32 DSolveMinusBox     (const double & xMin, const double & xMax,
                                         const double & yMin, const double & yMax,
                                         const double & x   , const double & y, 
                                         const double & delta);   
  
  
   virtual CATLONG32 NewtonDichotomy    (const double & xMin, const double & xMax, 
                                         const double & yMin, const double & yMax);   
  
   virtual CATLONG32 SafeNewton         (      double & x   ,       double & y, 
                                         const double & xMin, const double & xMax, 
                                         const double & yMin, const double & yMax);
  
           CATLONG32 SeparateOnEdge2   (const double & f0, const double & f1,
                                        const double & g0, const double & g1,
                                        const double & t0, const double & t1,
                                        const double & ufixed, const CATLONG32 whatfixed,
                                        const double & gSing, double & dsign);   
  
           double    TryExclusion      (const double x, const double y,
                                        const double & xMin, const double & xMax,
                                        const double & yMin, const double & yMax);
  
          CATLONG32  SingularityTreatment(const double & f00, const double & f01, 
                                        const double & f10, const double & f11,
                                        const double & g00, const double & g01, 
                                        const double & g10, const double & g11,
                                        const double & xMin, const double & xMax, 
                                        const double & yMin, const double & yMax);   
  

          CATLONG32  FindSingularity(         double & x, double & y,
                                        const double & xMin, const double & xMax, 
                                        const double & yMin, const double & yMax,
                                        const CATLONG32 function);   
   

   virtual CATBoolean IsChangingSignOnEdge(const double & f0, const double & f1,
                                                 double df0,  double df1,
                                                 double tMin, double tMax, double & t,
                                           const double & u, const CATLONG32 function);

   virtual CATBoolean IsLoopInSquare      (const double & xMin, const double & xMax, 
                                           const double & yMin, const double & yMax,
                                           const double & t0  , const double & t1  ,
                                           const double & t2  , const double & t3  ,
                                           const double & z00 , const CATLONG32 function,
                                                 double & ox, double & oy);   

   virtual CATLONG32 TryTwoBranchesByEdge (const double & h0, const double & h1,
                                           const double & xMin,
                                           const double & xMax,
                                           const double & yMin,
                                           const double & yMax,
                                           const double & ufixed,
                                           const CATLONG32 whatfixed, const CATLONG32 function);

   virtual CATLONG32 HyperbolicSingularity(const double & h00, const double & h01, 
                                           const double & h10, const double & h11,
                                           const double & xMin, const double & xMax,
                                           const double & yMin, const double & yMax,
                                           const CATLONG32 function);

   virtual CATBoolean AreSeparateSolutions(const double & x0, const double & y0,
                                           const double & x1, const double & y1);   

   virtual CATBoolean FletcherReeves      (      double & x, double & y,
                                           const double & xMin, const double & xMax, 
                                           const double & yMin, const double & yMax);

   virtual CATBoolean TryMarching         (const double x0, const double y0);

   virtual CATBoolean SolveOnLine         (      double & x   ,       double & y   ,
                                           const double   a   , const double   b   ,
                                           const double   xMin, const double   xMax, 
                                           const double   yMin, const double   yMax);


   virtual CATLONG32 TreatSmallSubDomain  (const double xMin, const double xMax, 
                                           const double yMin, const double yMax);


           // Evaluation de grille par EvalF (0) ou EvalG (1)
           void      EvalGridFOrG         (      int                 i0F1G,
                                           const CATMathIntervalND & iDomain,
                                           const CATLONG32        *  NbPoints,
                                           const CATMathOption       iOptions,
                                                 double           *  f       ,
                                                 double           *  fx      ,
                                                 double           *  fy      ,
                                                 double           *  fx2     ,
                                                 double           *  fxy     ,
                                                 double           *  fy2     ) const;
};


//===================================================================
   //                                                                                                       // *** XScale: l'intervalle D doit avoir ete ramene
   //                                                                                                       // ***         au standard (puissance 1 du Scale)
   //                                                                                                       // *** par ComputeScaledDomain().
   //                                                                                                       // *** A tout le moins, x et y devraient avoir un
   //                                                                                                       // *** comportement homogene par rapport au Scale
   //                                                                                                       // *** (varier selon la meme puissance du Scale)
   //                                                                                                       // ***                                                     NLD191113
ExportedByYN000FUN CATBoolean SafeNewtonStep(const double & x     , const double & y, 
                                                   double & deltax,       double & deltay, 
                                             const double & xMin  , const double & xMax,
                                             const double & yMin  , const double & yMax);




#endif
