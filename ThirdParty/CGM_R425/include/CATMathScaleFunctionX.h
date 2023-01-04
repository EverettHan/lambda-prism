#ifndef CATMathScaleFunctionX_h
#define CATMathScaleFunctionX_h

//=============================================================================
// ??/??/?? XXX Creation *** cet objet est a la bande a PKC ***
// 04/02/08 NLD _OKScaleReviewed et SetOKScaleReviewed() pour exclusion du controle des attributs deja certifies
//              Ajout GetFunction()
// 29/09/11 R1Y Added the functions GetLambda() and GetMu() (for comparing geometries).
// 07/06/19 NLD Mise au propre
//              - detabulation
//              - smart indent
//              Deflaggage
//=============================================================================
#include "CATIACGMLevel.h"

#include "CATMathFunctionX.h"
#include "YN000FUN.h"

//=============================================================================
class ExportedByYN000FUN CATMathScaleFunctionX : public CATMathFunctionX 
{
public:

  // Allows to construct a function g(t) such as : g(t) = Lambda * f( Mu * x )
                    CATMathScaleFunctionX(const CATMathFunctionX     * iF         ,
                                                double                 iLambda    ,
                                                double                 iMu        );

  virtual          ~CATMathScaleFunctionX();

  CATBoolean        IsAKindOf            (const CATMathClassId         ClassId    ) const;
  CATBoolean        IsATypeOf            (const CATMathFunctionXTypeId iType      ) const;
  CATMathClassId    IsA                  ()                                         const;
  CATBoolean        IsOption             (const CATMathOption          iOption    ) const;
  CATMathFunctionX* Duplicate            ()                                         const;
  CATMathFunctionX* DeepDuplicate        () const;
  CATMathFunctionX* DeepDuplicateWithTol (const CATTolerance         * ipTolObject) const ;
  // Evaluators basic
  double            Eval                 (const double               & T          ) const;
  double            EvalFirstDeriv       (const double               & iT         ) const;
  double            EvalSecondDeriv      (const double               & iT         ) const;
  double            EvalThirdDeriv       (const double               & iT         ) const;

  // Evaluator of function and derivatives at the same time :
  void              Eval                 (const double                 t          ,
                                          const CATMathOption          iOption    ,
                                                double               * f          ,
                                                double               * df         = 0,
                                                double               * d2f        = 0) const;

  // MultiEvaluator on a regular one dimensional grid on I.
  void              Eval                 (const CATMathInterval      & I          ,
                                          const CATLONG32              NbPoints   ,
                                          const CATMathOption          iOption    ,
                                                double               * f          ,
                                                double               * df         = 0,
                                                double               * d2f        = 0) const;

  // Evaluators on intervals
  CATMathInterval   Eval                 (const CATMathInterval      & x          ) const;

  CATMathInterval   EvalFirstDeriv       (const CATMathInterval      & x          ) const;

  CATMathInterval   EvalSecondDeriv      (const CATMathInterval      & x          ) const;

  CATMathInterval   EvalThirdDeriv       (const CATMathInterval      & x          ) const;

  void              Eval                 (const CATMathInterval      & I          ,
                                          const CATMathOption          iOptions   ,
                                                CATMathInterval      * f          ,
                                                CATMathInterval      * df         = 0,
                                                CATMathInterval      * d2f        = 0) const;

  void              ComputeScaledDomain  (const CATMathInterval      & domain     ,
                                                CATMathInterval      & scaleddomain);

  void              ComputeUnScaledRoots (const CATMathSetOfPointsND & ScaledRoots,
                                                CATMathSetOfPointsND & Roots      );


  void              SetOKScaleReviewed   () ;

  int               GetOKScaleReviewed   () const;

  const CATMathFunctionX* GetFunction    () const;

  double            GetLambda            () const;

  double            GetMu                () const;

private:
  //start temporary: virtual methods of base class
  CATMathScaleFunctionX             (const CATMathScaleFunctionX& iF);
  CATMathScaleFunctionX& operator = (const CATMathScaleFunctionX& iF);

  //end temporary

  const CATMathFunctionX * _F;
        double             _Lambda;
        double             _Mu;

        int                _OKScaleReviewed ;

};
#endif 
