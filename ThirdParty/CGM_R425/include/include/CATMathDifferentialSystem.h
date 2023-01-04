// COPYRIGHT DASSAULT SYSTEMES  1997
//=============================================================================
//
// CATMathDifferentialSystem:
// Abstract class used to solve a differential system of dimension N>=2.
//
//=============================================================================
//
// Usage notes:
//
// The pure virtual functions which are to be implemented for each specific
// application are the following:
//  - void Eval (const double * iX, const double iP, double * oFX) const
//
// The virtual functions that can be re-implemented:
//  - void InitializeSolverConstants(double & Toler) const
//    This virtual function sets the tolerance Toler to 1.e-6
//    for the Solve method.
//
// XScaleRules:                                                                                 (NLD281113)
//  - there is no ScaleOption (of typeCATMathAttrScaleOption) describing the differential system :
//    scale behaviour is imposed
//  - domains         must behave like power 1 of factory scale
//  - parameters      must behave like power 1 of factory scale
//  - points computed must behave like power 1 of factory scale
//  - steps  computed must behave like power 1 of factory scale
//  - see also local XScaleRules for some methods
//=============================================================================
// 29/10/13 NLD Detabulation, smart indent
//              Ajout _Config, ajout iConfig dans constructeur
// 05/11/13 NLD Ajout _XScaleV1
// 28/11/13 NLD Suppression des valeurs par defaut pour les arguments du constructeur
//              XScale: ajout XScaleRules: specification des conventions XScale
//              (globales et locales pour les differentes methodes)
//   /08/16 s9l ComputeNextPoint() from private to virtual and protected
//=============================================================================

#ifndef CATMathDifferentialSystem_H  
#define CATMathDifferentialSystem_H  

#include "YN000FUN.h"
#include "CATMathDef.h"
#include "CATMathDiagnostic.h"
#include "CATMathInline.h"
#include "CATMathStopDiagnostic.h"
#include "CATCGMVirtual.h"
#include "CATTolerance.h"

class CATMathAttrList;
class CATMathIntervalND;
class CATMathSetOfPointsND;
class CATSoftwareConfiguration;

class ExportedByYN000FUN CATMathDifferentialSystem : public CATCGMVirtual 
{
 public:  
  //---------------------------------------------------------------------------
  // Object Management.
  //---------------------------------------------------------------------------
  CATMathDifferentialSystem (const CATLONG32                 iN      ,
                             const CATTolerance            & iTol    , // NLD281113 = CATGetDefaultTolerance(),
                                   CATSoftwareConfiguration* iConfig   // NLD281113 = NULL
                            );
  virtual ~CATMathDifferentialSystem();

  //-------------------------------
  // Miscellaneous public methods.
  //-------------------------------

  INLINE CATLONG32 GetNumberOfVariables()     const;

  // Solving algorithm:
  //   This method implements an Embedded Runge-Kutta algorithm
  //   with the order couple 5(4) (IRK54) and a number of layers
  //   (nombre d etages) of 7.
  virtual CATMathDiagnostic Solve (const double                *  iStartPoint      ,
                                   const double                   iStartParameter  ,
                                   const double                   iMaximumParameter,
                                   const CATMathIntervalND     *  iDomain          ,
                                         CATMathSetOfPointsND   & oSetOfPoints     ,
                                         CATMathSetOfPointsND   & oSetOfParameters ,
                                         CATMathSetOfPointsND  *  oSetOfDerivatives, // Renvoie en plus les valeurs F[X] pour eviter de les recalculer plus tard
                                         CATMathStopDiagnostic  & oStopDiagnostic  ,
                                   const CATMathAttrList       *  iAttributes      = 0 )     const;

  virtual CATMathDiagnostic Solve (const double                *  iStartPoint      ,
                                   const double                   iStartParameter  ,
                                   const double                   iMaximumParameter,
                                   const CATMathIntervalND     *  iDomain          ,
                                         CATMathSetOfPointsND   & oSetOfPoints     ,
                                         CATMathSetOfPointsND   & oSetOfParameters ,
                                         CATMathStopDiagnostic  & oStopDiagnostic  ,
                                   const CATMathAttrList       *  iAttributes      = 0)     const;

  // Computes only one step given by "iStep"
  virtual void     ComputeOneStep (const double                *  iStartPoint       ,
                                   const double                *  iStartDeriv       ,
                                   const double                   iStartParameter   ,
                                   const double                   iStep             ,
                                         double                *  oEndPointDer      ,
                                         double                *  oEndParameter     ,
                                         CATMathStopDiagnostic  & oStopDiagnostic   ,
                                   const CATMathAttrList       *  iAttributes       = 0)     const;
  
  // Evaluators.
  // ----------
  // XScaleRules: iX  value must behave like power 1 of factory scale (iX is a point)                                  (NLD281113) 
  //              iP  value must behave like power 1 of factory scale (iP is a parameter)                              (NLD281113) 
  //              oFX values must all be scale independant                                                             (NLD281113) 
  virtual void     Eval           (const double                *  iX                ,
                                   const double                   iP                ,
                                         double                *  oFX               )     const = 0;
  
  // Optional method used to define bounds for step-size adjustments performed during solving computations.
  // iMaxStep: upper bound used to treshold step-size.
  // iMinStep: optional lower bound used to treshold step-size.
  // NB.: if both min and max steps are precised, a specified step-size strategy will be adopted (more cautious one).
  // XScaleRules: both step minimum and maximum must behave like power 1 of factory scale (iX is a parameter)          (NLD281113) 
          void     SetMaxStep     (      double                   iMaxStep          ,
                                         double                *  iMinStep          = 0);

  // This option allows to check if ComputeLastStep succeeded.
  // If it failed, last point computed which lies on domain's border
  // is erroneous and a strongest sub solving strategy is adopted.
          void     SetSafeLastStep();

  // This option allows to increase error control when computation
  // is outside domain. This has for effect to delay the last step
  // computation if error is too important: step is reduced, and 
  // computation goes on.
  // NB.: this mode activates also SafeLastStep mode.
          void     SetIncreaseErrorControl();

 protected:
  //-----------------
  // Protected Data.
  //-----------------
  // Number of variables.
        CATLONG32                   _N        ;
  const CATMathIntervalND        *  _Domain   ;
  const CATTolerance              & _TolObject;
        CATSoftwareConfiguration *  _Config   ;
        int                         _XScaleV1 ; // Corrections XScale version 1. NLD051113

  //----------------------------------
  // Miscellaneous protected methods.
  //----------------------------------

  // Compute the next point and the error from the current point,
  // the current parameter and the current step.
  virtual CATMathStopDiagnostic ComputeNextPoint
                                                (      double                 & ioParam          ,
                                                       double                 & ioStep           )     const; // S9L020816

 private:
  //---------------
  // Private Data.
  //---------------
  // Data for local optimisations.
        CATMathDifferentialSystem*  _localthis   ;
        double                   *  _CurrentPoint,
                                 *  _NextPoint   ,
                                 *  _YFactors    ,
                                 *  _Error       ;
        double                      _Toler       ,
                              _maxParam    ;
      //CATBoolean                _UserMaxStep;
        CATLONG32                   _UserMaxStep ; // 0: no values defined; 1: max step given; 2: min and max step given (new step-size strategy).
        double                      _maxStep     ,
                                    _minStep     ;
        double                      _LastEvaluatedParam,
                                    _OldEvaluatedParam;

  // Safe last step mode
        CATBoolean                  _SafeLastStep;
        CATBoolean                  _ForceSubSolve;

  // Increase error control mode
        CATBoolean                  _IncreaseErrorControl;

  //--------------------------------
  // Miscellaneous private methods.
  //--------------------------------

  //
  // After initializations have been done in Solve, 
  // launch the resolution of the differential system
  virtual CATMathDiagnostic SubSolve(const double                *  iStartPoint      ,
                                     const double                   iStartParameter  ,
                                     const double                   iMaximumParameter,
                                           CATMathSetOfPointsND   & oSetOfPoints     ,
                                           CATMathSetOfPointsND   & oSetOfParameters ,
                                           CATMathSetOfPointsND  *  oSetOfDerivatives, // Give NULL if you are not interested.
                                           CATMathStopDiagnostic  & oStopDiagnostic  )     const;

  // This virtual function sets Toler to 1.e-6 and Stab to 1.e-10 for the Solve method.
  // (Stab is the maximal error admissible between two successive SubSolve.)
  // It can be re programmed by any application if this value doesn t suit.
  // XScaleRules: both values must be scale independant                                         (NLD281113) 
  virtual void InitializeSolverConstants  (double                 & Toler            ,
                                           double                 & Stab             )     const;

  // Computes the Step from the point and the previous Step.
          void ComputeInitialStep   (const double                   iParam           ,
                                           double                 & ioStep           )     const;


  // * Basic old method without increase error control before launching ComputeLastStep procedure *
          CATMathStopDiagnostic ComputeNextPointBasic
                                    (      double                 & ioParam          ,
                                           double                 & ioStep           )     const;

  // -------------- ComputeNextPoint dedicated sub-methods --------------
  // FindNextPoint: this method start from current point and try to
  //                compute the best possible next point by reducing
  //                step so as to reach maximum error less than Toler.
  // Inputs  = iParam (start parameter), ioStep (initial step)
  //           iMaxIter: maximum num. of iteration used for step reduction
  //           iStrategy: 0 = stop iterations if stopped by max. domain
  //                      1 = reduce step by 2 if stopped by max. domain
  //                          and continue iterations.
  //
  // Outputs = ioStep (final step), _NextPoint
  //           oErrorMax: if given, oErrorMax is filled with max. error
  //           computed. NB.: with iStrategy = 0, if iterations stopped
  //           because of max. domain, max. error is not computed, and
  //           oErrorMax is filled with -1.
  //                                                                // XScale: output oErrorMax is independant from scale. NLD051113
          void FindNextPoint        (const double                   iParam           ,
                                           double                 & ioStep           ,
                                           CATLONG32                iMaxIter         ,
                                           CATLONG32                iStrategy        = 0   ,
                                           double                *  oErrorMax        = NULL) const;


  // Compute current max. error of next point using DOPRI5 formulas.
  // Detailed errors by composant are stored in _Error[i].
  //                                                                // XScale: output oErrorMax is independant from scale. NLD051113
          void ComputeError         (const double                   iStep            ,
                                           double                 & oErrorMax        )       const;

  // Force coordinates of next point which lies on borders at a
  // numerical tolerance to be equal to associated border value.
          void StabilizeBorderPoints()                                                       const;

  // Swap current and next points when a solution has been found.
          void SwapPoints           ()     const;

  // This method must be call when FindNextPoint gets out of domain.
  //
  // It simulates the first computation steps of ComputeLastStep
  // so as to control if error is not too big.
  // It returns TRUE if it seems safe to try ComputeLastStep, FALSE
  // if it is better to reduce step and continue solving algorithm.
  //
  // iParam   = start param.
  // ioStep   = first step used in ComputeLastStep method.
  // iMaxIter = max. number of iterations used to divide by 2. ioStep
  //            until computation returns a point inside domain used
  //            for error control.
  // oError   = max. error computed, associated to ioStep (could be -1.
  //            if no point inside domain has been computed).
  //                                                                // XScale: output oError    is independant from scale. NLD051113
          CATBoolean TryLastStep    (const double                   iParam           ,
                                           double                 & ioStep           ,
                                           CATLONG32                iMaxIter         ,
                                           double                 & oError           )       const;

  // When a solution point has been found at (iParam+iStep), it returns
  // relevant diagnostic for solving continuation.
 CATMathStopDiagnostic GetDiagnostic(const double                   iParam           ,
                                     const double                   iStep            )       const;
  // --------------------------------------------------------------------

  // This method checks if it safe to trigger a last step dichotomy. It returns TRUE if so, FALSE otherwise
  // and reduce by a quite good factor ioStep in that case.
  // NB.: the method is not available if min and max step have not been stored since it has to rely on these data
  // to take a decision.
  CATBoolean IsCandidateForLastStep (const double                   iParam           ,
                                           double                 & ioStep           )      const;

  // If the last predicted point is outside of the domain, get
  // the solution point of the domain s border.
  CATMathStopDiagnostic ComputeLastStep(   double                 & ioParam          ,
                                           double                 & ioStep           ,
                                     const double                   iWeigth          ,
                                     const CATLONG32                iPosition        )      const;

  // Get the step for the next iteration.
  //                                                                // XScale: input  iError    is independant from scale. NLD051113
             void            GetStep(const double                   iParam           ,
                                     const double                   iError           ,
                                           double                 & ioStep           )      const;

  // Same as above but with optional inputs that allows to control step-size strategy.
  //                                                                // XScale: input  iError    is independant from scale. NLD051113
             void GetStepWithOptions(const double                   iParam           ,
                                     const double                   iError           ,
                                           double                 & ioStep           ,
                                     const double                   iMarginFactor    ,
                                     const double                   iLowerFactor     ,
                                     const double                   iHigherFactor    )      const;

  //                                                                // XScale: input  iError    is independant from scale. NLD051113
  virtual    void TresholdStepWithContext
                                    (const double                   iParam           ,
                                           double                *  iCurrentPt       ,
                                     const double                   iError           ,
                                           double                 & ioStep           )      const;

  // Compute the IRK54 factors
          CATMathStopDiagnostic
                      ComputeFactors(const double                    iParam          ,
                                     const double                    iStep           ,
                                           double                *   oParam          = 0,
                                           int                   *   corrInd         = 0)   const;

  // Restore the seventh factor.
          void        Restore7thFactor()                                                    const;

  // Compute a tolerance and test wether _NextPoint is outside domain
          CATBoolean  NextPointOutsideDomain()                                              const;


  // Dump method for debug.
          void        PrintCurrentData
                                    (const double                    iParam          ,
                                     const double                    iStep           )      const;

};

//---------------------------------------------------------------------------
//                               INLINE
//---------------------------------------------------------------------------
INLINE CATLONG32 CATMathDifferentialSystem::GetNumberOfVariables()     const
{
 return _N;
}

#endif
