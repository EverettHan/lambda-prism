//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CATMathSolveX :
// Concrete class used to solve one variable functions.
//
//=============================================================================
// Usage notes:
//
//=============================================================================
//   /07/98 XGN Creation
//   /09/01 XGN AdaptativeSubSolve
// 08/07/05 cqi SetCheckExtremities()
// 18/07/05 cqi SolveNewtonWithInitOld(), SetOldNewtonWithInit()
// 10/03/06 cqi SetDichotomy()
// 02/06/06 cqi SetEpsRoot()
// 09/01/08 NLD Ajout _OKScaleReviewed et SetOKScaleReviewed() pour exclusion du controle des attributs deja certifies
// 16/01/08 NLD Ajout _NbUnReviewedAttributes
//              Ajout argument iIsScaleReviewed a SetTolerance() et SetEpsRoot()
// 01/02/08 NLD XScale. (aide au debug) ajout de CATMathSolveXParallelDebugCond() pour factorisation
//              Ajout _StandardRunCase
// 04/02/08 NLD XScale. argument iDerivate a CATMathSolveXParallelDebugCond()
// 18/12/08 NLD Ajout de _CATSquaredScaledEpsRoot  et _CATSquaredEpsRoot
// 16/01/09 NLD Gestion de configuration
//              - Ajout iConfig en argument optionnel du constructeur 
//              - Ajout _Config et _CGMLevel
// 06/03/09 NLD Initialize() recoit desormais iDerivate, et les racines par pointeur
//              pour etre appelable depuis SolveNewton()
//              Ajout _Initialized
// 30/07/09 NLD Parametrisation des traces pour usage dans fenetre de CGMReplay
//              Ajout SetDebugOutput(), _DebugOutput, _ActiveTraces
// 07/08/09 NLD Ajout SolveNewtonDebug() pour faciliter isolation de problemes
// 02/05/11 NLD _TolObject devient de type CATFullTolerance pour accès controlé et optimisé
// 09/02/16 NLD XScale: Ajout SolveNewtonWithInitFunctionX()
// 12/07/17 KJD Addition of _MaxDepthState to check if the operator is dealing with Solve_MaxDepth
// 18/09/17 NLD Smart indent
// 19/09/17 NLD Suppression de SolveNewtonWithInitOld() inactif depuis 09/01/09
//              (settings pris en compte par SolveNewtonWithInit())
// 10/03/21 JSX Change SolveNewtonDebug en SolveNewtonPrivate
// 15/05/21 JSX remove virtual on DSolve SolveMonotone SolveDichotomy
//=============================================================================

#ifndef CATMathSolveX_H
#define CATMathSolveX_H

#define CATMathSolveX_UseCATFullTolerance "NLD020511"

#include "YN000FUN.h"

#include "CATMathDef.h"
#include "CATMathInterval.h"
#include "CATMathDiagnostic.h"
#include "CATCGMVirtual.h"
#include "CATTolerance.h"
#ifdef CATMathSolveX_UseCATFullTolerance
#include "CATToleranceAccess.h" // pour CATFullTolerance
#endif

#include "CATMathFunctionX.h"

class CATMathSetOfPointsND;
class CATMathConstraint;
class CATSoftwareConfiguration;
class CATCGMOutput;


//-----------------------------------------------------------------------------
class ExportedByYN000FUN CATMathSolveX : public CATCGMVirtual
{
// public methods
public:
  //-----------------------------------------------------------------
  // Objects management
  //-----------------------------------------------------------------
                            CATMathSolveX         (const CATMathFunctionX        * iF         ,
                                                   const CATTolerance            & iTolObject = CATGetDefaultTolerance(),
                                                         CATSoftwareConfiguration* iConfig    = NULL);
  
  virtual                  ~CATMathSolveX();
  
  //-----------------------------------------------------------------
  // Setting methods
  //-----------------------------------------------------------------  
          void              SetConstraint         (const CATMathConstraint   *  iConstraint      );

          void              SetSamplingValue      (const CATLONG32              iSampling        );

          void              SetTolerance          (const double                 iTolerance       ,
                                                   const CATBoolean             IsAbsolute       = 0,
                                                         CATBoolean             iIsScaleReviewed = 0);

          void              SetCheckExtremities   (      CATBoolean             iEnable          = TRUE);

          void              SetOldNewtonWithInit  (      CATBoolean             iEnable          = TRUE);

  // This method allows to switch on a dichotomy solving approach if Lagrange Newton algorithm
  // requires too much iterations to arrive at the true root (typically large horizontal shape).
  //
  // iEnable   : TRUE to enable this method, FALSE to disable.
  // iNbIter   : to define the number of dichotomy steps (bracketing interval will be reduced by a factor 2^iNbIter).
  // iStartIter: to control the start iteration that triggers dichotomy.
          void              SetDichotomy          (      CATBoolean             iEnable          ,
                                                         CATLONG32              iNbIter          ,
                                                         CATLONG32              iStartIter       );

  // To take into account big numerical error internal to the evaluation of the function to solve.
  // NB.: the given tolerance iEpsRoot is supposed to have the same scale than the function to solve.
          void              SetEpsRoot            (const double                 iEpsRoot         ,
                                                         CATBoolean             iIsScaleReviewed = 0);
  
  //void SetToleranceObject(const CATTolerance & iTolObject);
          void              SetOKScaleReviewed() ;

  // Defines output file (default: cgmout); 
          void              SetDebugOutput        (      CATCGMOutput         * iDebugOutput     ,
                                                         int                    iActiveTraces    = 0) ;
  
  //-----------------------------------------------------------------
  // Running the operator
  //-----------------------------------------------------------------
  
          CATMathDiagnostic Run                   (const CATMathInterval      & iD               ,
                                                         CATMathSetOfPointsND & oRoots           );
  
  
  // Lagrange Newton algorithm.
  // iD id the interval where the root is.
  // iF is the interval [function(Dmin), function(Dmax)] which must contain 0.
  // iDerivate indicate if we solve the function or its derivative.
  // ioResult is the initial point and the result.
  virtual CATMathDiagnostic SolveNewton           (const CATMathInterval      & iD               ,
                                                   const double                 iFmin            ,
                                                   const double                 iFmax            ,
                                                   const CATLONG32            & iDerivate        ,
                                                         double               & ioResult         ) const;
  
  // Lagrange Newton algorithm.
  // iD       is the interval where the root is.
  // iInit    is the initial point.
  // ioResult is the result.

  // N.B see forward SolveNewtonWithInitFunctionX() for automatic function and input/output scaling. NLD090216
  virtual CATMathDiagnostic SolveNewtonWithInit   (const CATMathInterval      & iD               ,
                                                         double               & iInit            ,
                                                         double               & ioResult         ) const;
  
  //- Adaptative discretisation solver starting from a setofpoints
          CATMathDiagnostic AdaptativeSubSolve    (      double                 it0              ,
                                                         double                 it1              ,
                                                         double                 iF0              ,
                                                         double                 iF1              ,
                                                         CATLONG32              iDepth           = 0);

  // if IsNull is true for all points in iD, then the function is considered as null
  // A simple root on a non vanishing function should satisfy IsRoot, which is stronger than IsNull.
  virtual CATBoolean        IsNull                (const double                 x                ,
                                                   const double                 fx               ,
                                                         double               & oNormfx          ,
                                                   const double               * dfx              = 0) const;

  virtual CATBoolean        IsRoot                (const double                 x                ,
                                                   const double                 fx               ,
                                                         double               & oNormfx          ,
                                                   const double               * dfx              = 0) const;

          void              Initialize            (const CATMathInterval      & iD               ,
                                                         CATMathSetOfPointsND *  oRoots          ,
                                                   const CATLONG32               iDerivate       = FUNCTION);

          CATMathDiagnostic RunOnPolynom          (const CATLONG32               iDegree         ,
                                                   const double                * iCoeff          ,
                                                   const double                  iShift          = 0.);

          CATMathDiagnostic RunOnTrigonometric    (const double                  iAmplitude      ,
                                                   const double                  iFreq           ,
                                                   const double                  iPhase          ,
                                                   const double                  iOffset         );

protected:

   // !! JSX 03/05/2021 The only authorized ovverrrding class is CATSystemPcrvPcrv 
  virtual CATMathDiagnostic RSolve                (const CATMathInterval       & iD              ,
                                                         CATLONG32               iDepth          = 0);
  // !! JSX 03/05/2021 The only authorized ovverrrding class is CATSystemPcrvPcrv 
  virtual CATMathDiagnostic Solve_MaxDepth        (const CATMathInterval       & D               );

/*virtual*/
          CATMathDiagnostic DSolve                (const CATMathInterval       & iD              ,
                                                   const CATLONG32               iSample         );

/*virtual*/
          CATMathDiagnostic SolveMonotone         (const CATMathInterval       & iD              );

  virtual CATMathDiagnostic AddRoot               (const double                  iRoot           );

  virtual CATBoolean        IsAllNull             ();

/*virtual*/
          CATMathDiagnostic SolveDichotomy        (      double                & ioMin           ,
                                                         double                & ioMax           ,
                                                         double                & ioFmin          ,
                                                         double                & ioFmax          ,
                                                   const CATLONG32             & iDerivate       ,
                                                         double                & oResult         ) const;
  private: // jsx 10/03/2021
  // internal use only
          CATMathDiagnostic SolveNewtonPrivate(            int                     iDebugWithSolveNewtonFunctionX,
                                                   const CATMathInterval       & iD              ,
                                                   const double                  iFmin           ,
                                                   const double                  iFmax           ,
                                                   const CATLONG32             & iDerivate       ,
                                                         double                & ioResult        ) const;


// 01/02/08 NLD XScale. (aide au debug) ajout de CATMathSolveXParallelDebugCond() pour factorisation
          void              CATMathSolveXParallelDebugCond
                                                  (const CATMathInterval       & iD              ,
                                                   const CATLONG32             & iDerivate       ) ;

  // protected data
protected:
  
        CATSoftwareConfiguration* _Config ;
        int                       _CGMLevel ;

  const CATMathFunctionX        * _F;
        CATMathInterval           _Domain;
        CATMathSetOfPointsND    * _Roots;
  
        CATLONG32                 _Sampling;
  const CATMathConstraint       * _Constraint;
        double                    _MinWidth;

  // tolerance data
        double                    _Tolerance;
        CATBoolean                _IsAbsolute;

        CATBoolean                _DerivativeUnprecise; // Default is FALSE, permit to enlarge the minimum precision required to consider 
                                                        // that the derivative is a root, when the derivative is not precise

  // To avoid testing that the function is null everywhere more than once
        CATBoolean                _NotNullKnown;

  // Check if extremities are roots at IsRoot sense (RSolve only)
        CATBoolean                _CheckExtremities;

  // To switch on old version of SolveNewtonWithInit (ie. with uncomplete stop criterion)
        CATBoolean                _OldNewtonWithInit;

  // To check if the operator is dealing with Solve_MaxDepth
        CATBoolean                _MaxDepthState;
        
  // Dichotomy data
        CATBoolean                _Dichotomy;
        CATLONG32                 _MaxIterDicho,
                                  _StartIterDicho;

  #ifdef CATMathSolveX_UseCATFullTolerance
  const CATFullTolerance        & _TolObject; //   const CATTolerance & _TolObject;
  #else
  const CATTolerance            & _TolObject;
  #endif
        double                    _CATScaledEpsRoot,
                                  _CATEpsRoot;
        double                    _CATSquaredScaledEpsRoot,
                                  _CATSquaredEpsRoot ;
  // NLD090108
        CATBoolean                _OKScaleReviewed ;
  // NLD160108
        int                       _NbUnReviewedAttributes ;

        int                       _Initialized ;

        int                       _StandardRunCase ;

  // Debug and traces system
        CATCGMOutput            * _DebugOutput ;
        int                       _ActiveTraces ;
};

//-----------------------------------------------------------------
// Solve Newton with Init, with automatic XScale management of funciton, input and output,
// using attributes
//----------------------------------------------------------------------------------------------
// Lagrange Newton algorithm.
// iD      is the interval where the root is.
// iInit   is the initial point.
// iAttributes are the solver attributes
//   - CATMathAttrTolObject                   should be specified in XScale context
//   - CATMathAttrScaleOption                 should be specified in XScale context
//   - CATMathAttrDoubleValue "EpsilonRoot"   may    be speficied for advanced use
// oResult is the result.
//
// All input and output are in user space (scaling to CATMathSolveX hypothesis is only done internally)
//
//----------------------------------------------------------------------------------------------
// Creation NLD090216

// Managed attributes:
// 
// N.B implemented in CATMathFunctionX.cpp
//-----------------------------------------------------------------
ExportedByYN000FUN
CATMathDiagnostic SolveNewtonWithInitFunctionX(const CATMathFunctionX        * iFunction   ,
                                               const CATMathInterval         & iD          ,
                                                     double                    iInit       ,
                                               const CATMathAttrList         * iAttributes ,
                                                     CATSoftwareConfiguration* iConfig     ,
                                                     double                  & oResult     );

#endif

