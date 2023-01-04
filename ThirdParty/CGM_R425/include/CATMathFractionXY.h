#ifndef CATMathFractionXY_h
#define CATMathFractionXY_h

#define CATMathFractionXY_NoCopyOperator "TEST ONLY NLD070619; pour voir utilisations; pas d'utilisation"

// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATMathFractionXY:
//  Class of two variables functions fractions.
//      Frac(x, y) = _P(x, y) / _Q(x, y)
//
//=============================================================================
// 29/07/09 NLD Gestion du stream
//              - derivation de _IsStreamable()
//              - derivation de GetStreamType()
//              - derivation de Stream()
// 06/06/19 NLD Mise au propre. Smart indent
//              Deflaggages
//              Ajout argument iConfig au constructeur
//              Ajout tactique de _Config (sans infrastructure generale sur les fonctions)
//              Ajout du destructeur
// 07/06/19 NLD Le constructeur par défaut devient privé
// A VOIR
//              Ajout en privé de operator = (pour eviter mauvaise gestion de _Config tant qu'on ne le code pas)
//              XScale: suppression de la valeur par defaut de iTolObject dans le constructeur
//=============================================================================

#include "CATIACGMLevel.h"

#include "YN000FUN.h"

#include "CATMathFoundationXY.h"
#include "CATMathIntervalND.h"
#include "CATCGMStreamVersion.h"
#include "CATMathStream.h"


class CATMathFractionXYDel;
class CATSoftwareConfiguration;

class ExportedByYN000FUN CATMathFractionXY : public CATMathFoundationXY
{

 private:
                            CATMathFractionXY  ();
 #ifdef CATMathFractionXY_NoCopyOperator
 CATMathFractionXY& operator = (const CATMathFractionXY& iF);
 #endif

 public:
  //-----------------------------------------------------------------
  //- Object Management
  //-----------------------------------------------------------------
                   virtual ~CATMathFractionXY  ();

                            CATMathFractionXY  (const CATMathFunctionXY        *  P                ,
                                                const CATMathFunctionXY        *  Q                ,
                                                const CATTolerance              & iTolObject       , //= CATGetDefaultTolerance(),
                                                      CATSoftwareConfiguration *  iConfig          = NULL);

                            CATMathFractionXY  (const CATMathFractionXY         & F                );

  CATCGMNewClassArrayDeclare;

  //-----------------------------------------------------------------
  //- Information Methods
  //-----------------------------------------------------------------
        CATMathClassId      IsA                 () const;
        int                 GetDirectComponents (const int                        iSizeOfComponents,
                                                 const CATMathFunctionGeneral **  ioComponents     ) const;
        CATBoolean          IsAKindOf           (const CATMathClassId             ClassId          ) const;
        CATBoolean          IsATypeOf           (const CATMathFunctionXYTypeId    iType            ) const;
        CATBoolean          IsOption            (const CATMathOption              iOption          ) const;


  //-----------------------------------------------------------------
  //- Get Methods
  //-----------------------------------------------------------------
  const CATMathFunctionXY * GetNumerator        () const;
  const CATMathFunctionXY * GetDenominator      () const;


  //-----------------------------------------------------------------
  // Duplicator
  //-----------------------------------------------------------------
        CATMathFunctionXY * Duplicate           () const;
        CATMathFunctionXY * DeepDuplicate       () const;
        CATMathFunctionXY * DeepDuplicateWithTol(const CATTolerance *ipTolObject) const ;
  //-----------------------------------------------------------------
  // Evaluators on doubles
  //-----------------------------------------------------------------
        double              Eval              (const double & u, const double & v) const;

        double              EvalFirstDerivX   (const double & u, const double & v) const;
        double              EvalFirstDerivY   (const double & u, const double & v) const;

        double              EvalSecondDerivX2 (const double & u, const double & v) const;
        double              EvalSecondDerivXY (const double & u, const double & v) const;
        double              EvalSecondDerivY2 (const double & u, const double & v) const;
  /** 
  * Evaluates simultaneously the value, and all the first, second and third partial derivatives 
  */
        void                EvalUpToThirdDeriv(const double iu, const double iv,
                                                     double & oF,
                                                     double & oFx,  double & oFy,
                                                     double & oFx2, double & oFxy, double & oFy2,
                                                     double & oFx3, double & oFx2y, double & oFxy2, double & oFy3) const;
    /** 
  * Evaluates the value of third partials derivatives 
  */
        void                EvalAllThirdDerivs(const double iu, const double iv, double & oFx3, double & oFx2y, double & oFxy2, double & oFy3) const;
 
        double              EvalThirdDerivX3  (const double & u, const double & v) const;
        double              EvalThirdDerivX2Y (const double & u, const double & v) const;
        double              EvalThirdDerivXY2 (const double & u, const double & v) const;
        double              EvalThirdDerivY3  (const double & u, const double & v) const;
  //-----------------------------------------------------------------
  // Evaluator of function and derivatives at the same time :
  // (performance are increased if redefined in derived classes)
  // iOption is a command which contains which derivatives are
  // requested (usually, iOption = OptionEval + OptionEvalFirstDeriv)

        void                Eval              (const double u, const double v,
                                               const CATMathOption iOptions,
                                                     double * f,
                                                     double * fx =0, double * fy=0,
                                                     double * fx2=0, double *fxy=0, double *fy2=0) const;

  //-----------------------------------------------------------------
  // Multi-evaluation of function and derivatives on a regular
  // grid of Nu x Nv points delimited by  [uStart,uEnd] x [vStart,vEnd]
  // If NbPoints[0]=1 and/or NbPoints[1]=1 then the evaluations
  // are made on the smallest corresponding coordinate in iDomain
  // WARNING : the pointers must be previously allocated if the
  // corresponding evaluations are needed.
  // The value f[Nv*i+j] contains Eval(x_i,y_j) ...

        void                Eval              (const CATMathIntervalND & iDomain,
                                               const CATLONG32         * NbPoints,
                                               const CATMathOption       iOptions,
                                                     double            * f   ,
                                                     double            * fx  = 0,
                                                     double            * fy  = 0,
                                                     double            * fx2 = 0,
                                                     double            * fxy = 0,
                                                     double            * fy2 = 0) const;


  /**
  * @nodoc
  *
  * MultiEvaluator of f and its derivative on a non regular grid :
  * Evaluation of 
  *                F[i*xNbPoints+j] = Eval(xPoints[i],yPoints[j]), ...
  */
  virtual void              EvalGrid          (      CATLONG32           xNbPoints,
                                               const double            * xPoints  ,
                                                     CATLONG32           yNbPoints,
                                               const double            * yPoints  ,
                                               const CATMathOption       iOptions ,
                                                     double            * ioF      ,
                                                     double            * ioFx     = 0,
                                                     double            * ioFy     = 0) const;

   
  //-----------------------------------------------------------------
  // Evaluators on intervals
  //-----------------------------------------------------------------

  CATMathInterval Eval             (const CATMathInterval & Du,
                                    const CATMathInterval & Dv,
                                    const CATTolerance    & iTolObject = CATGetDefaultTolerance()) const;

  CATMathInterval EvalFirstDerivX  (const CATMathInterval & Du,
                                    const CATMathInterval & Dv) const;

  CATMathInterval EvalFirstDerivY  (const CATMathInterval & Du,
                                    const CATMathInterval & Dv) const;

  CATMathInterval EvalSecondDerivX2(const CATMathInterval & Du,
                                    const CATMathInterval & Dv) const;

  CATMathInterval EvalSecondDerivXY(const CATMathInterval & Du,
                                    const CATMathInterval & Dv) const;

  CATMathInterval EvalSecondDerivY2(const CATMathInterval & Du,
                                    const CATMathInterval & Dv) const;

  //-----------------------------------------------------------------
  // Interval evaluator of function and derivatives at the same time :
  // (performance are increased if redefined in derived classes)
  // iOptions is a command which contains which derivatives are requested
  // (usually, iOptions = OptionEvalInterval + OptionEvalFirstDerivInterval)
  void            Eval             (const CATMathInterval & Du,
                                    const CATMathInterval & Dv,
                                    const CATMathOption iOptions,
                                          CATMathInterval * f   ,
                                          CATMathInterval * fx  = 0, CATMathInterval * fy = 0,
                                          CATMathInterval * fx2 = 0, CATMathInterval * fxy = 0,
                                          CATMathInterval * fy2        = 0,
                                    const CATTolerance    & iTolObject = CATGetDefaultTolerance()) const;

  //-----------------------------------------------------------------
  // Multi-evaluation of interval  on a regular grid of
  // Nu x Nv sub-squares  delimited by  [uStart,uEnd] x [vStart,vEnd]
  // WARNING : the pointer Images  must be previously allocated
  // Images[Nv*i+j] contains Eval(X_i,Y_j)
  //
  // void Eval(const CATMathIntervalND & iDomain,
  //            const CATLONG32 * NbIntervals,
  //            CATMathInterval * Images) const; 

  //---------------------------------------------------------------------
  // isopar creation
  // --------------------------------------------------------------------

          CATMathFunctionX  * CreateIsoparX    (const double             & x        ) const;
          CATMathFunctionX  * CreateIsoparY    (const double             & y        ) const;

  // Formal combination

  virtual CATMathFunctionXY * FormalCombination(const CATLONG32            iN       ,
                                                const CATMathFunctionXY ** iFunc    ,
                                                const double             * iCoef    ,
                                                const double               iConstant) const;


  //-----------------------------------------------------------------
  // Stream management
  //-----------------------------------------------------------------
  /** @nodoc */
  virtual CATBoolean _IsStreamable            ( const CATCGMStreamVersion   iTargetVersion  ,
                                                      CATBoolean          & ioReversible    ) const;
  virtual short      GetStreamDomainType      (       char                  ioDomain[3]     ) const;
  virtual void       Stream                   (       CATMathStream       & Str             ,
                                                const char                  iLabelReserved[]) const ;



 private:

  //-----------------------------------------------------------------
  // Private methods
  //-----------------------------------------------------------------
  
  //-----------------------------------------------------------------
  // Interval evaluator for the denominator, returning in *f an interval
  // not containing zero.

  void EvalDenom(const CATMathInterval & Du      ,
                 const CATMathInterval & Dv      ,
                 const CATMathOption     iOptions,
                       CATMathInterval * f       ,
                       CATMathInterval * fx      = 0,
                       CATMathInterval * fy      = 0,
                       CATMathInterval * fx2     = 0,
                       CATMathInterval * fxy     = 0,
                       CATMathInterval * fy2     = 0) const;

  //-----------------------------------------------------------------
  // Recursive EvalDenom called by EvalDenom
  // 0 is returned if zero was found in the image of the denominator, else 1
  // is returned.

  CATBoolean REvalDenom(const CATMathInterval & Du,
                        const CATMathInterval & Dv, CATMathInterval & f, int & ioCounter) const;

  //-----------------------------------------------------------------
  // Rises an exception explaining that a denominator is null
  // therefore an evaluation cannot be performed.

  void ThrowForNullDenom () const;


  const CATMathFunctionXY       * _P        ,
                                * _Q        ;
  const CATTolerance            & _TolObject;
        CATSoftwareConfiguration* _Config   ;

  friend class CATMathFractionXYDel;

};
#endif
