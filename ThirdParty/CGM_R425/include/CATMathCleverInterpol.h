// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATMathCleverInterpol:
//   Base class for quintic polynomial C2 interpolation of an object
//   after the marching algorithm, with reconvergence on the parameters to 
//   have the best possible interpolation.
//
//=============================================================================
// Usage notes:
//
//  This base class works for interpolation of a curve defined by an implicit
//  equation but can be derived for other problems (for example, fillet interpolation)
//
//  The number of subelements generated tries to be as small as possible, with 
//  the constraint on the tolerance for the Quality evaluator.
//
//
//=============================================================================
// 11/04/08 PKC Versionning
// 22/05/08 NLD XScale. passage par CATHardTol() pour detection dynamique
//              Introduction de CATMathCleverInterpol_DummyDoNotUseDefaultTol
//              et CATMathCleverInterpol_DoNotUseSpecialArgForDefaultTol
//              Et finalement suppression de la valeur par defaut de la tolerance
//              et de tous les arguments par defaut
// 28/04/16 NLD Regroupement des declarations de donnees + explications
//              Reordonnancement des methodes en conformite avec la classe mere
//              Smart indent
//              Correction de la signature de ShapeQuality()
// 20/04/17 NLD Mise en conformite de l'ordre des tolerances de RunSingular()
//              (tol, qualitytol) au lieu de (qualitytol, tol) avec l'implementation et les appelants
//              (avec commentaires d'utilisation et etude historique detaillee)
//              XScale rules pour les methodes specifiques Quality() et SingularQualityAtPoint()
//=============================================================================
// xx/xx/xx NLD Revoir l'ordre des arguments de ShapeQuality() et SingularQuality()
//              ainsi que BorderConstraint(),
//              (pas du tout homogenes aux autres methodes)
//              (utilises seulement dans AdvancedMathematics)
//              et aussi
//              RunSingular(), (ATTENTION: utilisation dans GeometricOperators())
//              OptimalArc(), ValidateArc(), InitializeArc()
//              cela dit cet ordre correspond a la logique des valeurs de Liberties
// xx/xx/xx NLD l'argument Liberties (STY300402) vient comme un cheveu sur la soupe au milieu des coordonnees, a remonter. NLD280416
//              (en fait c'est parce que ce qui peut etre libre commence a T0, T1, apres P0, P1 qui ne le sont pas)
//              (InitializeArc(), OptimalArc(),
//              RunSingular(), (ATTENTION: utilisation dans GeometricOperators())
//=============================================================================

#ifndef CATMathCleverInterpol_h
#define CATMathCleverInterpol_h

#include "YN000FUN.h"

#include "CATMathInterpol.h"
#include "CATMathDiagnostic.h"
#include "CATMathDef.h"

class CATMathImplicitSystem;
class CATMathIntervalND;
class CATMathSetOfPointsND;
class CATSoftwareConfiguration;

// #define CATMathCleverInterpol_DummyDoNotUseDefaultTol          1E-10 
// #define CATMathCleverInterpol_DoNotUseSpecialArgForDefaultTol -10000.0 

class ExportedByYN000FUN CATMathCleverInterpol : public CATMathInterpol
{

  CATCGMVirtualDeclareClass(CATMathCleverInterpol);

public:


  //                    // Tolerances du constructeur (NLD220508)
  //                    // (voir classe mere CATMathInterpol)
  //                    // - iTolerance:
  //                    //   - la tolerance doit varier comme le
  //                    //     carre de l'echelle
  //                    //   - par defaut elle etait de 1E-10 en echelle 1
  //                    //     mais l'appelant doit toujours la redefinir
  //                    //     et tenir compte du Scale (au carre)
  //                    //   - une valeur strictement negative quelconque
  //                    //     fait utiliser la tolerance par defaut de CATMathInterpol
  //                    //     prenant automatiquement en compte le scale
  //                    // - iAcceptableTolerance (tolerance d'acceptation)
  //                    //   - si valeur nulle cette tolerance d'acceptation
  //                    //     sera consideree comme egale a la valeur issue de iTolerance
                     CATMathCleverInterpol     (      CATSoftwareConfiguration *  iConfig              ,
                                                const CATLONG32                   iN                   ,
                                                      CATMathImplicitSystem    *  iSystem              ,
                                                const CATMathIntervalND        *  iDomain              ,
                                                const double                      iTolerance           ,
                                                const double                      iAcceptableTolerance ,
                                                const CATTolerance              & iTolObject           );

  virtual           ~CATMathCleverInterpol();

// -----------------------------------------------------------------------
//  Run Of The Algorithm
// -----------------------------------------------------------------------

  //
  // From iSet, which contains points and normed tangents of a solution of iSystem,
  // compute optimal nodal vector, points, tangents and secondderivatives in oResult
  // such that the interpolating Hermite quintics  have a precision at most iTolerance.
  //
  // More precisely, oParameters, oPoints, oTangents and oSecondDerivatives contain
  // a certain number K of values in R^N (in R for oParameters)
  // (usually significantly less than the number of points in iSet)
  // such that for (i>=1) :
  // * The Hermite polynomial Pi of degree 5 defined by
  //
  //   Pi (0) = oPoints           [i-1],      
  //   Pi'(0) = oTangents         [i-1],
  //   Pi"(0) = oSecondDerivatives[i-1],
  //
  //   Pi (oParameters[i]) = oPoints           [i], 
  //   Pi'(oParameters[i]) = oTangents         [i],
  //   Pi"(oParameters[i]) = oSecondDerivatives[i],
  //
  //   verify the property : Quality(Pi(t)) < iTolerance    for t in [0,oParameters[i]]
  //
  // * P(0) and P'(0) corresponds to the starting point and tangent of iSet
  // * P(K-1) and P'(K-1) corresponds the ending point and tangent of iSet
  //
  // Comments :
  //   * Usually, oPoints[i] and oTangents[i] are point of iSet. In some rare case, some 
  //     new points are added if the required precision could not be reached.
  //   * oSecondDerivatives[i] are computed thanks to an approximation from close normed tangents.
  //   * The resulting piecewise curve defined with P0,P1,P2,... is of class C2.
  //
  virtual void       Run                       (      CATMathSetOfPointsNDWithVectors
                                                                               & iSet                  ,
                                                      CATMathSetOfPointsND     & oParameters           ,
                                                      CATMathSetOfPointsND     & oPoints               ,
                                                      CATMathSetOfPointsND     & oTangents             ,
                                                      CATMathSetOfPointsND     & oSecondDerivatives    );

// -----------------------------------------------------------------------
//  Specific For Implicit Interpol (Public)
// -----------------------------------------------------------------------

/**
 * Add a point at specified local parameter on arc Narc (starting at 0), except if this
 * insertion would lead to a small arc. Return 0 if the additional point could not be 
 * computed, 1 otherwise.
 * Narc will be modified so that you may cut at corresponding position.
 * This method is designed to be called outside the run.
 */
  virtual CATBoolean AddPointAtParam           (      CATLONG32                & Narc                  ,
                                                      double                     w0                    ,
                                                      CATMathSetOfPointsND    *  ioParameters          ,
                                                      CATMathSetOfPointsND    *  ioPoints              ,
                                                      CATMathSetOfPointsND    *  ioTangents            , 
                                                      CATMathSetOfPointsND    *  ioSecondDerivatives   ,
                                                      CATLONG32                  iReconvergeDeltaParam = 1);


  virtual CATBoolean AddPointOnArc             (      CATLONG32                & Narc                  ,
                                                const double                  *  iPoint                ,
                                                      CATMathSetOfPointsND    *  ioParameters          ,
                                                      CATMathSetOfPointsND    *  ioPoints              ,
                                                      CATMathSetOfPointsND    *  ioTangents            , 
                                                      CATMathSetOfPointsND    *  ioSecondDerivatives   ,
                                                      CATBoolean               & oNewPointAdded,
                                                      double * iParam = NULL);

protected:

    virtual CATBoolean ComputePointAtParam     (       CATLONG32                & Narc                 ,
                                                       double                     w0                   ,
                                                       CATMathSetOfPointsND    *  ioParameters         ,
                                                       CATMathSetOfPointsND    *  ioPoints             ,
                                                       CATMathSetOfPointsND    *  ioTangents           , 
                                                       CATMathSetOfPointsND    *  ioSecondDerivatives  ,
                                                       double                  *  ioNewPoint           );

    virtual CATBoolean ComputeDerivForPointAtParam(      double                *  ioNewPoint           , 
                                                   const double                *RefTangent             );

    virtual double  ReconvergeDeltaParam        (      CATLONG32                & Narc,
                                                       CATMathSetOfPointsND    * ioParameters         ,
                                                       CATMathSetOfPointsND    * ioPoints             ,
                                                       CATMathSetOfPointsND    * ioTangents           ,
                                                       CATMathSetOfPointsND    * ioSecondDerivatives  ,
                                                       double                  *  iNewPoint           );

    virtual CATBoolean CheckPointProximity      (       CATLONG32                & Narc,
                                                        CATMathSetOfPointsND    * ioPoints,
                                                        double                  *  iNewPoint);


// -----------------------------------------------------------------------
//  Best Interpol With Derivatives
// -----------------------------------------------------------------------

/**
 * Indicates that the quality computation needs the derivatives of quintics
 * which index is >= iFirstIndex and < iLastIndex. This is the new way to use
 * this functionnality - then you won't need to overload Interpol, BestInterpol
 * and IsAcceptable.
 */
          void       SetQualityNeedsDerivatives(      CATLONG32                  iFirstIndex           ,
                                                      CATLONG32                  iLastIndex            );

/**
 * Possible implementation for BestInterpol, using derivatives of the current quintic.
 * You must also overload Interpol and IsAcceptable(const double*, const double*, ..)
 */
  virtual double     BestInterpolWithDer       (const double                  *  iP0                   ,
                                                const double                  *  iT0                   ,
                                                const double                  *  iC0                   ,
                                                const double                  *  iP1                   ,
                                                const double                  *  iT1                   ,
                                                const double                  *  iC1                   ,
                                                      double                  *  iAlreadyAllocated     ,
                                                      CATLONG32                  iExtraN               ,
                                                      double                   & oDeltaParam           ,
                                                const CATLONG32                  iNbSample             ,
                                                const CATBoolean                 iEasyInterpol         = 0);

          void       GetQuinticCoef            (      double                  *  ioA                   ,
                                                      double                  *  ioB                   ,
                                                      double                  *  ioC                   ,
                                                const double                  *  iP0                   ,
                                                const double                  *  iT0                   ,
                                                const double                  *  iC0                   ,
                                                const double                  *  iP1                   ,
                                                const double                  *  iT1                   ,
                                                const double                  *  iC1                   );

  virtual void        GetQuinticDerCoef        (      CATLONG32                  iExtraN               ,
                                                      double                  *  ioA                   ,
                                                      double                  *  ioB                   ,
                                                      double                  *  ioC                   , 
                                                const double                  *  iP0                   ,
                                                const double                  *  iT0                   ,
                                                const double                  *  iC0                   ,
                                                const double                  *  iP1                   ,
                                                const double                  *  iT1                   ,
                                                const double                  *  iC1                   );

          double      GetQualityAtParam        (      double                  *  iA                    ,
                                                      double                  *  iB                    ,
                                                      double                  *  iC                    , 
                                                      double                  *  iDA                   ,
                                                      double                  *  iDB                   ,
                                                      double                  *  iDC                   , 
                                                      double                  *  iX                    ,
                                                      double                     iParam                ,
                                                      CATLONG32                  iExtraN               , 
                                                      CATBoolean                 iCheckIfInDomain      ,
                                                      CATBoolean               & oInDomain             );

          void        GetQualityDerivatives    (      double                  *  iA                    ,
                                                      double                  *  iB                    ,
                                                      double                  *  iC                    ,
                                                      double                  *  iDA                   ,
                                                      double                  *  iDB                   ,
                                                      double                  *  iDC                   ,
                                                      double                  *  iX                    ,
                                                      double                     iParam                ,
                                                      double                     iH                    ,
                                                      CATLONG32                  iExtraN               ,
                                                      double                     iQ                    ,
                                                      double                   & oDQ                   ,
                                                      double                   & oD2Q                  );


// -----------------------------------------------------------------------
//  Mandatory Services Required By Mother Class
// -----------------------------------------------------------------------

  // Ces methodes sont documentees dans la classe mere
  // Certaines methodes sont non virtuelles expres, il ne faut pas les
  // rederiver.

// -----------------------------------------------------------------------
//  Functionnal Evaluators
// -----------------------------------------------------------------------



/**
 * Retrieve data from the initial set.
 */
          void       GetDataFromISet           (      CATMathSetOfPointsND     & iSet                  ,
                                                      CATLONG32                  iPos                  ,
                                                      double                  *  oParam                = 0,
                                                      double                  *  oP                    = 0,
                                                      double                  *  oT                    = 0);

/**
 * Retrieve or compute point from the initial set.
 */
          void       GetPointFromISet          (      CATMathSetOfPointsND     & iSet                  ,
                                                      CATLONG32                  iPos                  ,
                                                      double                  *  oParam                = 0,
                                                      double                  *  oP                    = 0);
/**
 * Eval current quintic.
 */
  virtual void       EvalQuintic               (const double                     iParam                ,
                                                      double                  *  oFX                   );

public:
/** 
 * Compute point, tangent and second derivative in the dimension of
 * interpolation. Point and tangent computed in the dimesion of marching
 * may have to be given as inputs.
 * iOrientation = -1 for a derivative on the left, 1 on the right and 0 
 *   for both sides.
 */
          void       ComputeData               (      double                     iParam                ,
                                                      double                  *  ioP                   ,
                                                      double                  *  ioT                   ,
                                                      double                  *  ioC                   ,
                                                      int                        iOrientation          );

protected:
// -----------------------------------------------------------------------
//  Quality Evaluators
// -----------------------------------------------------------------------
/** 
 * Compute the quality of the current arc at specified ratio. (homogeneous to power 2 of factory scale)
 */
          double     Quality                   (const double                     iRatio                ,
                                                const double                     iParam0               ,
                                                const double                     iParam1               ,
                                                const double                     iDeltaParam           ,
                                                      CATBoolean               & ioCheckDomain         );

/** 
 * Compute the quality of the specified arc at middle point. (homogeneous to power 2 of factory scale)
 */
          double    QualityOpt                 (const double                     iParam0,
                                                const double                     iParam1               ,
                                                const double                     iDeltaParam           ,
                                                      CATBoolean               & ioCheckDomain         );

/** 
 * Compute and store internal data before one or more calls to QualityOpt.
 * This method is systematically called before QualityOpt.
 * iOnlyDelta = 1 if and only if only the delta parameter has changed since
 * last call.
 */
          void       PrepareQualityOpt         (const double                  *  iP0                   ,
                                                const double                  *  iT0                   ,
                                                const double                  *  iC0                   ,
                                                const double                  *  iP1                   ,
                                                const double                  *  iT1                   ,
                                                const double                  *  iC1                   ,
                                                const double                     iDeltaParam           ,
                                                      CATBoolean                 iOnlyDelta            );

// -----------------------------------------------------------------------
//  Quality Control And Parametrization Management
// -----------------------------------------------------------------------
/** 
 * Point checker (called on the first point only).
 */
  virtual void       CheckValidityOfPoint      (      CATMathSetOfPointsND     & iSet                  ,
                                                const double                  *  iP                    ,
                                                      double                  *  ioT                   ,
                                                      double                  *  ioC                   ,
                                                      double                     iCosMin               ,
                                                      CATBoolean               & oIsSingularLeft       );

/** 
 * Point checker (called on the end point and on each required point).
 */
  virtual void       CheckValidityOfLastPoint  (const double                  *  iP0                    ,
                                                const double                  *  iT0                    ,
                                                const double                  *  iP1                    ,
                                                      double                  *  ioT1                   ,
                                                      double                  *  ioC1                   ,
                                                      double                     iCosMin                ,
                                                      CATBoolean               & oIsSingularRight       );


          void       StoreParameter            (      CATMathSetOfPointsND     & ioParams              ,
                                                      double                     iParam                ,
                                                      CATLONG32                  iArcInfo              );

          void       StoreFirstParameter       (      CATMathSetOfPointsND     & ioParams              ,
                                                      double                     iParam                );

          void       CompleteParameters        (      CATMathSetOfPointsND     & ioParameters          );

  virtual double     GetCosAngleBetweenTangents(      CATMathSetOfPointsND     & iSet                  ,
                                                const double                  *  iT0                   ,
                                                      CATLONG32                  iPoint1               );

  virtual double     GetCosAngleBetweenTangents(      CATMathSetOfPointsND     & iSet                  ,
                                                      CATLONG32                  iPoint0               ,
                                                      CATLONG32                  iPoint1               );

  virtual CATBoolean Verif                     (      CATMathSetOfPointsND     & iSet                  ,
                                                      CATMathSetOfPointsND     & oParameters           ,
                                                      CATMathSetOfPointsND     & oPoints               ,
                                                      CATMathSetOfPointsND     & oTangents             ,
                                                      CATMathSetOfPointsND     & oSecondDerivatives    ,
                                                      CATMathSetOfPointsND    *  oCorrespondingInitialParams);

#ifdef CATMathInterpol_AdvQualityComparison
          void       StoreInvalidArcs           (     CATMathSetOfPointsND     & ioParams              ,
                                                      CATLONG32                  iArcInfo              );
#endif

/**
 * Compute the default value for the delta parameter (before reconvergence).
 */
  virtual double     InitializeDeltaParam      (const double                     iParam0               ,
                                                const double                     iParam1               ,
                                                const double                  *  iP0                   ,
                                                const double                  *  iT0                   ,
                                                const double                  *  iC0                   ,
                                                const double                  *  iP1                   ,
                                                const double                  *  iT1                   ,
                                                const double                  *  iC1                   );

  // BestInterpol(): see mother class

/**
 * Return the finite difference step to use during the minimization of the function
 *   DeltaParam |-> Quality_of_the_arc
 */
  virtual double     GetFiniteDifferenceStep   (      double                     iDeltaParam           ,
                                                      double                     iParam0               ,
                                                      double                     iParam1               );

// -----------------------------------------------------------------------
//  Insertion Management
// -----------------------------------------------------------------------
/**
 * Compute a new point inside the arc, and do some various controls.
 * The point is chosen at the middle (by default or at _Lambda if set via SetMiddleValue()) in case of an implicit interpol,
 * or at parameter oParam in case of an explicit interpol.
 * The return value is 0 in case of success, -2 or another value < -2
 * corresponding to a failure diagnostic otherwise.
 */
  virtual enum ConvergenceInfo ComputeDataAtMiddle (  double                   & oParam                ,
                                                const double                     iParam0               ,
                                                const double                     iParam1               ,
                                                const double                  *  iP0                   ,
                                                const double                  *  iT0                   ,
                                                const double                  *  iC0                   ,
                                                const double                  *  iP1                   ,
                                                const double                  *  iT1                   ,
                                                const double                  *  iC1                   ,
                                                      double                     iMinLength            ,
                                                      double                  *  ioPHalf               ,
                                                      double                  *  ioTHalf               ,
                                                      double                  *  ioCHalf               );

  // GetCosAngleBetweenTangents moved above
  // CheckValidityOfPoint       moved above
  // CheckValidityOfLastPoint   moved above
  // Verif                      moved above



// -----------------------------------------------------------------------
//  Original Services That Are Often Derivated In Sub Classes
// -----------------------------------------------------------------------

  virtual void       ComputeDataAtPoint        (      double                  *  ioP                   ,
                                                      double                  *  ioT                   ,
                                                      double                  *  ioC                   );

  //                                                          (homogeneous to power 2 of factory scale)
  virtual double     Quality                   (const double                  *  iX                    );

  virtual CATBoolean IsAcceptable              (const double                  *  iX                    );

  virtual CATBoolean IsAcceptable              (const double                  *  iP0                   ,
                                                const double                  *  iT0                   ,
                                                const double                  *  iC0                   ,
                                                const double                  *  iP1                   ,
                                                const double                  *  iT1                   ,
                                                const double                  *  iC1                   ,
                                                      double                     ialpha                ,
                                                      CATLONG32                  iNbSample             );

// -----------------------------------------------------------------------
//  Other Auxiliary Methods (not in mother class)
// -----------------------------------------------------------------------

  virtual void    ComputeVectorFieldOrientation(const double                  *  iP                    ,
                                                const double                  *  iT                    );

          CATMathDiagnostic
                  ComputeNeighborPointAndTangent(     double                  *  iP                    ,
                                                      double                  *  iT                    ,
                                                      double                     iStep                 ,
                                                      double                  *  ioNeighborX           ,
                                                      double                  *  ioNeighborT           );

  virtual CATLONG32  IsSingularExtremity       (const double                  *  iP                    ,
                                                const double                  *  iT                    ,
                                                const double                  *  iC                    );

  // This service is called when T0.THalf and _VectorFieldOrientation have
  // opposite sign,where THalf is the tangent at the  candidate point for
  // insertion, and T0 is the tangent at the current point.
  // Sometimes, it is needed to reverse the orientation of the vector field (for
  // example, we have passed over a singularity and we did not want to stop). In
  // that case, the tangent should be reversed and the candidate can be accepted.
  // Return code :
  //  0 - Do not accept this point
  //  1 - Accept this point and reverse _VectorFieldOrientation (the caller should reverse iTHalf if T0.THalf <0)
  // Default behaviour : return 0.
  virtual int        CheckVectorFieldOrientation(     double                  *  iPHalf                ,
                                                      double                  *  iTHalf                );


public:

// -----------------------------------------------------------------------
// Deformation Methods  (not in mother class)
// -----------------------------------------------------------------------
  // XScale rules: (NLD200417)
  // CAUTION:                   <@CAUTION_ScalePower1_ForThisTolerance>
  //    in following methods,
  //    and unlike tolerance arguments of constructors, and unlike quality functions
  //    both tol and qualitytol (really) seems to be homogeneous and varying like power 1 of factory scale. NLD190417
  // 
  // About RunSingular and its tolerances
  // - tol and qualitytol
  //   (obh) tol        est le seuil de la singular quality au bout   de l'arc deforme
  //         qualitytol est le seuil de la singular quality au milieu de l'arc deforme
  //   (NLD) In fact the square values of these tolerances are used as threshold
  //         for comparison to SingularQualityAtPoint() results
  //         which behave like power 2 of factory scale
  //                                                            // Commentaires sur l'evolution historique:
  //                                                            // - RunSingular methode    introduite par 60.FIXPARTKLX 18/03/03
  //                                                            // - tol         tolerance  introduite par 63.FIXPARTKLX 10/04/03
  //                                                            // - qualitytol  tolerance  introduite par 76.FIXPARTSTY 07/02/05
  //                                                            //                          (mais en fait 200.FIXPARTOBH 02/02/05,
  //                                                            //                           branche morte en est a l'origine)
  //                                                            //                          en meme temps que dans OptimalArc() et ValidateArc()
  //                                                            //                          mais pas dans le meme ordre
  //                                                            //                          ici                   (qualitytol, tol)
  //                                                            //                          ailleurs              (tol, qualitytol)
  //                                                            //                          dans l'implementation (tol, qualitytol) (incoherence)
  //                                                            //                          dans les appelants    (tol, qualitytol)
  //                                                            //                          (CATIntersectionSurSurTg qui les distingue)
  //                                                            //                          (CATIntersectionSurSurWithInits qui passe les deux memes valeurs)
  //                                                            // - tolerances inversees ici                 FIXPARTNLD 20/04/17
  //                                                            //   SANS CONSEQUENCE ET SANS CORRECTION DE SOURCE
  //                                                            //   pour passer a l'ordre naturel (tol, qualitytol)
  //                                                            // - tolerances documentees ici               FIXPARTNLD 20/04/17
  //                                                            //   d'apres le source (commentaires obh que je rectifie)
  // - Liberties
  //   je recupere la documentation dans l'implementation, et je commente. NLD200417
  //   - Find a nicely shaped solution arc in _N-space between P0 and P1 by optimization over
  //     the free variables indicated by Liberties: 1 = T0, 2 = T1, 4 = C0, 8 = C1, 16 = delta
  //   - compte tenu du fonctionnement de Liberties, qui privilegie un ordre d'arguments T0, T1, C0, C1
  //     il est difficile de realigner cet ordre sur l'ordre standard P0, T0, C0, P1, T1, C1 de cette classe
  //   
  //    

  
  virtual CATLONG32  RunSingular               (      double                  *  P0                    ,
                                                      double                  *  P1                    ,
                                                      CATLONG32                  Liberties             ,
                                                      double                  *  T0                    ,
                                                      double                  *  T1                    ,
                                                      double                  *  C0                    ,
                                                      double                  *  C1                    ,
                                                      double                   & delta                 ,
                                                      double                     tol                   ,      // <@CAUTION_ScalePower1_ForThisTolerance>
                                                      double                     qualitytol            ,      // <@CAUTION_ScalePower1_ForThisTolerance>
                                                      short                      TangentConstraint     = 0);

  // Ordre des arguments a revoir. ATTENTION, appelee par CATMathOptimalArcRN (qui est un utilitaire specifique) NLD280416
  virtual double     SingularQuality           (      double                     delta                 ,
                                                      double                  *  P0                    ,
                                                      double                  *  P1                    ,
                                                      double                  *  T0                    ,
                                                      double                  *  T1                    ,
                                                      double                  *  C0                    ,
                                                      double                  *  C1                    );

  // Ordre des arguments a revoir. NLD280416
  // N.B je mets ici cet ordre transitoirement en conformite avec l'implementation
  //     ce qui est la moindre des choses
  //     car ce n'etait pas coherent
  //     on avait l'ordre suivant: delta, P0, T0, C0, P1, T1, C1
  //     qui est l'ordre que j'aimerais avoir, car conforme a celui de la majorite des methodes
  //     de la classe mere
  // N.B la methode n'est pas derivee mais elle est appelee par CATMathOptimalArcRN (qui est un utilitaire specifique)
  virtual double     ShapeQuality              (      double                     delta                 ,
                                                      double                  *  P0                    ,
                                                      double                  *  P1                    ,
                                                      double                  *  T0                    ,
                                                      double                  *  T1                    ,
                                                      double                  *  C0                    ,
                                                      double                  *  C1                    );


          void       UseSurSurWithInitsSettings(); // reserved for CATIntersectionSurSurWithInits

  virtual double     BorderConstraint          (      double                     delta                 ,
                                                      double                  *  P0                    ,
                                                      double                  *  P1                    ,
                                                      double                  *  T0                    ,
                                                      double                  *  T1                    ,
                                                      double                  *  C0                    ,
                                                      double                  *  C1                    );
  
          double     TangentConstraint         (      double                  *  T0                    ,
                                                      double                  *  T1                    );

          void       SetValidityDomain         (const CATMathIntervalND       *  iDomain               );

protected:

  //                                                          (homogeneous to power 2 of factory scale)
  virtual double     SingularQualityAtPoint    (const double                  *  P                     );

  virtual CATLONG32  OptimalArc                (      double                   & delta                 ,
                                                      double                  *  P0                    ,
                                                      double                  *  P1                    ,
                                                      CATLONG32                  Liberties             ,
                                                      double                  *  T0                    ,
                                                      double                  *  T1                    ,
                                                      double                  *  C0                    ,
                                                      double                  *  C1                    ,
                                                      double                     ShapeQSingularQBalance,
                                                      double                   & ResultShapeQ          ,
                                                      double                   & ResultSingularQ       ,
                                                      double                     tol                   ,      // <@CAUTION_ScalePower1_ForThisTolerance>
                                                      double                     qualitytol            ,      // <@CAUTION_ScalePower1_ForThisTolerance>
                                                      short                      WithBorderConstraint  ,
                                                      short                      WithFreeDelta         = 0,
                                                      short                      TangentConstraint     = 0);

// Check that a deformed arc doesn't cause too much distortion in terms of numerical
// correctness of the solution - that is, SingularQ remains under given tolerance
// Also checks that the arc stays within the domain 
//
// return value:-1 = Internal error
//               0 = OK
//               combination (sum) of theses values (comment NLD280416)
//               1 = Bad quality
//               2 = Out of domain
  virtual CATLONG32  ValidateArc                (     double                     delta                 ,
                                                      double                  *  P0                    ,
                                                      double                  *  P1                    ,
                                                      double                  *  T0                    ,
                                                      double                  *  T1                    ,
                                                      double                  *  C0                    ,
                                                      double                  *  C1                    ,
                                                      double                     tol                   ,      // <@CAUTION_ScalePower1_ForThisTolerance>
                                                      double                     qualitytol            ,      // <@CAUTION_ScalePower1_ForThisTolerance>
                                                      short                      TangentConstraint     = 0);

  virtual void       FromImplicitToInterpol     (     double                  *  P                     );

  virtual CATLONG32  InitializeArc              (     double                   & delta                 ,
                                                      double                  *  P0                    ,
                                                      double                  *  P1                    ,
                                                      CATLONG32                  Liberties             ,
                                                      double                  *  T0                    ,
                                                      double                  *  T1                    ,
                                                      double                  *  C0                    ,
                                                      double                  *  C1                    );

  // Used by deformation to check that a solution point is in the domain
  // within a specified 3d tol. This method should be derived in subclasses,
  // so as to make sense of the 3d tol. The default implementation ignores the
  // 3d tol and works directly with parametres at a tolerance of a CATEpsg.
  virtual CATLONG32 WithinDomain               (const double                  *  X                     ,
                                                const double                  *  dom                   ,
                                                      double                     tol3d                 );

protected :

// -----------------------------------------------------------------------
//  Protected Fields
// -----------------------------------------------------------------------
  
  CATBoolean         _ComputeDataAtPoint2;

  //                              // Comme cela etait merveilleusement documente,               (merci KLX)
  //                              // - _A, _B, _C sont des sous-allocations de taille _N de _EvalBuffer
  //                              // - _EvalBuffer est lui-meme de taille totale 7*_N mais
  //                              //   de taille utilisable 4*_N (le reste pour _A _B et _C)
  //                              // - L'allocation est faite une fois pour toutes dans le constructeur
  //                              // NLD280416 
  double           * _EvalBuffer,
                   * _A,
                   * _B,
                   * _C;

  //                              // La encore, on ne s'etouffera pas sous la documentation     (merci KLX encore)
  //                              // - il s'agit d'allocations groupees
  //                              //   _dB et _dC sont des sous-allocations de _dA
  //                              // - l'allocation est faite, eventuellement, en cours de route
  //                              // - la gestion par les classes derivees est ouverte aux quatre vents
  //                              //   mais semble-t-il sans utilisation effective au 280416
  //                              // NLD280416 
  double           * _dA,
                   * _dB,
                   * _dC;

  CATMathQuinticX ** _Arc;
  CATBoolean         _SurSurWithInitsSettings;

private:

// -----------------------------------------------------------------------
//  Private Members
// -----------------------------------------------------------------------

//  int _VectorFieldOrientation;  // Pour l'instant encore dans la classe mere

};


#endif

