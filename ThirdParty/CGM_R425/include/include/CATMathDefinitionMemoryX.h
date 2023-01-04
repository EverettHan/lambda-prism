#ifndef CATMathDefinitionMemoryX_H
#define CATMathDefinitionMemoryX_H

// COPYRIGHT DASSAULT SYSTEMES  1999
#include "CATIACGMLevel.h"
#include "YN000FUN.h"
#include "CATMathFoundationX.h"

#include "CATMathInterval.h"

class CATMathDefinitionMemoryXDel;

class ExportedByYN000FUN CATMathDefinitionMemoryX : public CATMathFoundationX
{
 private:
  const CATMathFunctionX *_F;
  CATMathInterval _Def, _Image, _ImageD;
  friend class CATMathDefinitionMemoryXDel;

 public:
  CATMathDefinitionMemoryX();
  CATMathDefinitionMemoryX(const CATMathDefinitionMemoryX & f);
  CATMathDefinitionMemoryX(const CATMathFunctionX * f, const CATMathInterval & Def);
  virtual ~CATMathDefinitionMemoryX();
  CATCGMNewClassArrayDeclare;

  void Set(const CATMathFunctionX * f, const CATMathInterval & Def);
  CATMathFunctionX * Duplicate() const;
  CATMathFunctionX * DeepDuplicate() const; 
#if defined ( CATIACGMR216CAA )
  CATMathFunctionX * DeepDuplicateWithTol(const CATTolerance *ipTolObject) const ;
#endif

  CATMathClassId IsA() const; 
  int GetDirectComponents(const int iSizeOfComponents, const CATMathFunctionGeneral **ioComponents) const;
  CATBoolean IsAKindOf(const CATMathClassId ClassId) const;
  CATBoolean IsATypeOf(const CATMathFunctionXTypeId iType) const;  
  CATBoolean IsOption(const CATMathOption iOption) const;

  double GetMinParam() const;
  double GetMaxParam() const;
  double GetWidth() const;
  const CATMathFunctionX * GetFunctionX() const;

   //-----------------------------------------------------------------
   // Evaluators on doubles
   //-----------------------------------------------------------------   
   double Eval(const double & t) const;
   double EvalFirstDeriv(const double & t) const;
   double EvalSecondDeriv(const double & t) const;
   double EvalThirdDeriv(const double & t) const;

   //
   // Evaluator of function and derivatives at the same time :
   //
   void Eval(const double t, const CATMathOption iOption,
             double * f, double * df = 0, double * d2f = 0) const;

   //
   // MultiEvaluator on a regular one dimensional grid on I.
   //
   void Eval(const CATMathInterval & I, const CATLONG32 NbPoints,
             const CATMathOption iOption,
             double * f, double * df = 0, double * d2f = 0) const;

   //-----------------------------------------------------------------
   // Evaluators on intervals
   //-----------------------------------------------------------------
   CATMathInterval Eval(const CATMathInterval & x) const;
   CATMathInterval EvalFirstDeriv(const CATMathInterval & x) const;
   CATMathInterval EvalSecondDeriv(const CATMathInterval & x) const;
   CATMathInterval EvalThirdDeriv(const CATMathInterval & x) const;
  void Eval(const CATMathInterval & I, const CATMathOption iOptions,
	    CATMathInterval * f, CATMathInterval * df = 0, 
	    CATMathInterval * d2f = 0) const;
};
#endif
