#ifndef CATMathPeriodicX_h
#define CATMathPeriodicX_h

// COPYRIGHT DASSAULT SYSTEMES 1999

//=============================================================================
// 04/10/11 R1Y Added access functions (for comparing geometries).
//=============================================================================
#include "CATIACGMLevel.h"

#include "YN000FUN.h"
#include "CATMathFoundationX.h"

class CATMathPeriodicXDel;

class ExportedByYN000FUN CATMathPeriodicX : public CATMathFoundationX
{
 public:
  //-----------------------------------------------------------------
  //- Object Management
  //-----------------------------------------------------------------
  CATMathPeriodicX(const CATMathFunctionX * F, double p, double t);
  CATMathPeriodicX(const CATMathPeriodicX & F);
  CATMathFunctionX * Duplicate() const;
  CATMathFunctionX * DeepDuplicate() const;
#if defined ( CATIACGMR216CAA )
  CATMathFunctionX * DeepDuplicateWithTol(const CATTolerance *ipTolObject) const ;
#endif
  virtual ~CATMathPeriodicX();
  CATCGMNewClassArrayDeclare;

  //-----------------------------------------------------------------
  //- Information Methods
  //-----------------------------------------------------------------
  CATBoolean IsAKindOf(const CATMathClassId ClassId) const;
  CATBoolean IsATypeOf(const CATMathFunctionXTypeId iType) const;    
  int GetDirectComponents(const int iSizeOfComponents, const CATMathFunctionGeneral **ioComponents) const;
  CATMathClassId IsA() const;
  CATBoolean IsOption(const CATMathOption ) const;

  double GetPeriod() const;
  double GetT0() const;

  //-----------------------------------------------------------------
  //- Evaluators
  //-----------------------------------------------------------------
  double Eval(const double & t) const;
  double EvalFirstDeriv(const double & t) const;
  double EvalSecondDeriv(const double & t) const;
  double EvalThirdDeriv(const double & t) const;

  void Eval(const double t, const CATMathOption iOption,
	    double * f, double * df = 0, double * d2f = 0) const;

  CATMathInterval Eval(const CATMathInterval & x) const;
  CATMathInterval EvalFirstDeriv(const CATMathInterval & x) const;
  CATMathInterval EvalSecondDeriv(const CATMathInterval & x) const;
  CATMathInterval EvalThirdDeriv(const CATMathInterval & x) const;


private:
  const CATMathFunctionX *_F;
  double _Period,_T0;
  friend class CATMathPeriodicXDel;
};
#endif
