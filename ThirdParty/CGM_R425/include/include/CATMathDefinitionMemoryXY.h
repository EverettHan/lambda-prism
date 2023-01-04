#ifndef CATMathDefinitionMemoryXY_H
#define CATMathDefinitionMemoryXY_H

// COPYRIGHT DASSAULT SYSTEMES  1999
#include "CATIACGMLevel.h"

#include "YN000FUN.h"

#include "CATMathInterval.h"
#include "CATMathFoundationXY.h"

class CATMathDefinitionMemoryXYDel;

class ExportedByYN000FUN CATMathDefinitionMemoryXY : public CATMathFoundationXY
{
 private:
  const CATMathFunctionXY *_F;
  CATMathInterval _DefU, _DefV, _Image, _ImageDU, _ImageDV;
  friend class CATMathDefinitionMemoryXYDel;

  const CATTolerance & _TolObject;

 public:
  CATMathDefinitionMemoryXY(const CATTolerance & iTolObject = CATGetDefaultTolerance());
  CATMathDefinitionMemoryXY(const CATMathDefinitionMemoryXY & f);

  CATMathDefinitionMemoryXY(const CATMathFunctionXY *f,
			    const CATMathInterval & DefU,
			    const CATMathInterval & DefV,
          const CATTolerance & iTolObject = CATGetDefaultTolerance());

  virtual ~CATMathDefinitionMemoryXY();
  CATCGMNewClassArrayDeclare;

  CATMathFunctionXY * Duplicate() const;
  CATMathFunctionXY * DeepDuplicate() const;
#if defined ( CATIACGMR216CAA )
  CATMathFunctionXY * DeepDuplicateWithTol(const CATTolerance *ipTolObject) const ;
#endif
  void Set(const CATMathFunctionXY *f,
	   const CATMathInterval & DefU,
	   const CATMathInterval & DefV);

  CATBoolean IsAKindOf(const CATMathClassId ClassId) const;
#ifdef CATIACGMV5R21
  CATBoolean IsATypeOf(const CATMathFunctionXYTypeId iType) const;
#endif
  CATMathClassId IsA() const;
  int GetDirectComponents(const int iSizeOfComponents, const CATMathFunctionGeneral **ioComponents) const;
  CATBoolean IsOption(const CATMathOption iOption) const;

  double GetMinParamU() const;
  double GetMaxParamU() const { return _DefU.GetMax(); }
  double GetWidthU() const;
  double GetMinParamV() const;
  double GetMaxParamV() const { return _DefV.GetMax();}
  double GetWidthV() const;
  const CATMathFunctionXY * GetFunctionXY() const;

  double Eval(const double & u, const double & v) const;
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
  
  double EvalFirstDerivX(const double & u, const double & v) const;
  double EvalFirstDerivY(const double & u, const double & v) const;
  double EvalSecondDerivX2(const double & u, const double & v) const;
  double EvalSecondDerivXY(const double & u, const double & v) const;
  double EvalSecondDerivY2(const double & u, const double & v) const;
  double EvalThirdDerivX3(const double & u, const double & v) const;
  double EvalThirdDerivX2Y(const double & u, const double & v) const;
  double EvalThirdDerivXY2(const double & u, const double & v) const;
  double EvalThirdDerivY3(const double & u, const double & v) const;

  CATMathInterval Eval(const CATMathInterval & Du,
            const CATMathInterval & Dv, const CATTolerance & iTolObject=CATGetDefaultTolerance()) const;
  CATMathInterval EvalFirstDerivX(const CATMathInterval & Dx,
				    const CATMathInterval & Dy) const;
  CATMathInterval EvalFirstDerivY(const CATMathInterval & Dx,
				    const CATMathInterval & Dy) const;
  CATMathInterval EvalSecondDerivX2(const CATMathInterval & Dx,
				    const CATMathInterval & Dy) const;
  CATMathInterval EvalSecondDerivXY(const CATMathInterval & Dx,
				    const CATMathInterval & Dy) const;
  CATMathInterval EvalSecondDerivY2(const CATMathInterval & Dx,
				    const CATMathInterval & Dy) const;
//  CATMathInterval EvalThirdDerivX3(const CATMathInterval & Dx,
//				   const CATMathInterval & Dy) const;
//  CATMathInterval EvalThirdDerivX2Y(const CATMathInterval & Dx,
//				    const CATMathInterval & Dy) const;
//  CATMathInterval EvalThirdDerivXY2(const CATMathInterval & Dx,
//				    const CATMathInterval & Dy) const;
//  CATMathInterval EvalThirdDerivY3(const CATMathInterval & Dx,
//				   const CATMathInterval & Dy) const;

protected:

  virtual CATMathFunctionXY * FormalCombination(const CATLONG32 iN, 
						const CATMathFunctionXY ** iFunc,
						const double * iCoef, 
						const double iConstant) const;
};
#endif
