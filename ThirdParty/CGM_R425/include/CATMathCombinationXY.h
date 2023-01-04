#ifndef CATMathCombinationXY_h
#define CATMathCombinationXY_h

// COPYRIGHT DASSAULT SYSTEMES  1999
#include "CATIACGMLevel.h"

#include "YN000FUN.h"

#include "CATMathFoundationXY.h"

class CATMathCombinationXYDel;

class ExportedByYN000FUN CATMathCombinationXY : public CATMathFoundationXY
{
 private:
  CATLONG32 _N;
  double * _coef;
  const CATMathFunctionXY ** _Functions;
  friend class CATMathCombinationXYDel;


 public:
  CATMathCombinationXY(const CATLONG32 & N,
		       const CATMathFunctionXY ** functions,
		       const double * coef,
		       const double constant = 0.);
  CATMathCombinationXY(const CATMathCombinationXY & f);
  CATMathCombinationXY & operator = (const CATMathCombinationXY & c);

  void Set(const CATMathFunctionXY ** functions,
           const double * coef,
           const double constant = 0.);

  virtual ~CATMathCombinationXY();
  CATCGMNewClassArrayDeclare;

  CATBoolean IsAKindOf(const CATMathClassId ClassId) const;
#ifdef CATIACGMV5R21
  CATBoolean IsATypeOf(const CATMathFunctionXYTypeId iType) const;
#endif
  CATMathClassId IsA() const;
  int GetDirectComponents(const int iSizeOfComponents, const CATMathFunctionGeneral **ioComponents) const;
  CATBoolean IsOption(const CATMathOption iOption) const;
  CATMathFunctionXY * Duplicate() const;
  CATMathFunctionXY* DeepDuplicate() const ;
#if defined ( CATIACGMR216CAA )
  CATMathFunctionXY * DeepDuplicateWithTol(const CATTolerance *ipTolObject) const ;
#endif

  //-----------------------------------------------------------------
  // Evaluators on doubles
  //-----------------------------------------------------------------
  
  double Eval(const double & u, const double & v) const;
  double EvalFirstDerivX(const double & u, const double & v) const;
  double EvalFirstDerivY(const double & u, const double & v) const;
  double EvalSecondDerivX2(const double & u, const double & v) const;
  double EvalSecondDerivXY(const double & u, const double & v) const;
  double EvalSecondDerivY2(const double & u, const double & v) const;
  /** 
  * Evaluates simultaneously the value, and all the first, second and third partial derivatives 
  */
  void EvalUpToThirdDeriv(const double iu, const double iv,double & oF, double & oFx,  double & oFy,
    double & oFx2, double & oFxy, double & oFy2,double & oFx3, double & oFx2y, double & oFxy2, double & oFy3) const; 
  /** 
  * Evaluates the value of third partials derivatives 
  */
  void EvalAllThirdDerivs(const double iu, const double iv, double & oFx3, double & oFx2y, double & oFxy2, double & oFy3) const;
  double EvalThirdDerivX3(const double & u, const double & v) const;
  double EvalThirdDerivX2Y(const double & u, const double & v) const;
  double EvalThirdDerivXY2(const double & u, const double & v) const;
  double EvalThirdDerivY3(const double & u, const double & v) const;

   //
   // Evaluator of function and derivatives at the same time :
   // iOption is a command which contains which derivatives are requested
   // (usually, iOption = OptionEval + OptionEvalFirstDeriv)
   //
  void Eval(const double u, const double v, 
            const CATMathOption iOptions,
            double * f,
            double * fx =0, double * fy=0,
            double * fx2=0, double *fxy=0, double *fy2=0) const;
   
   // Multi-evaluation of function and derivatives on a regular 
   // grid of Nu x Nv points delimited by  [uStart,uEnd] x [vStart,vEnd]
   // If NbPoints[0]=1 and/or NbPoints[1]=1 then the evaluations
   // are made on the smallest corresponding coordinate in iDomain
   // WARNING : the pointers must be previously allocated if the
   // corresponding evaluations are needed.
   // The value f[Nv*i+j] contains Eval(x_i,y_j) ...
   //
  void Eval(const CATMathIntervalND & iDomain, const CATLONG32 * NbPoints,
            const CATMathOption iOptions,
            double * f,
            double * fx =0, double * fy=0,
            double * fx2=0, double *fxy=0, double *fy2=0) const;


  //-----------------------------------------------------------------
  // Evaluators on intervals
  //-----------------------------------------------------------------

  CATMathInterval Eval(const CATMathInterval & Du,
            const CATMathInterval & Dv, const CATTolerance & iTolObject=CATGetDefaultTolerance()) const;
  CATMathInterval EvalFirstDerivX(const CATMathInterval & u,
				    const CATMathInterval & v) const;
  CATMathInterval EvalFirstDerivY(const CATMathInterval & u,
				    const CATMathInterval & v) const;
  CATMathInterval EvalSecondDerivX2(const CATMathInterval & u,
				    const CATMathInterval & v) const;
  CATMathInterval EvalSecondDerivXY(const CATMathInterval & u,
				    const CATMathInterval & v) const;
  CATMathInterval EvalSecondDerivY2(const CATMathInterval & u,
				    const CATMathInterval & v) const;
  void Eval(const CATMathInterval & Du, const CATMathInterval & Dv,
	          const CATMathOption iOptions,CATMathInterval * f,
	          CATMathInterval * fx =0, CATMathInterval * fy=0,
	          CATMathInterval * fx2=0, CATMathInterval *fxy=0, 
	          CATMathInterval *fy2=0, const CATTolerance & iTolObject=CATGetDefaultTolerance()) const;
};
#endif
