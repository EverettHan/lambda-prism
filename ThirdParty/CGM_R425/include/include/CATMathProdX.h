#ifndef CATMathProdX_h
#define CATMathProdX_h
// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CATMathProdX :
// class of product of two functions  of one variable
//
//=============================================================================
// Usage notes:
//
//=============================================================================
#include "CATIACGMLevel.h"
#include "YN000FUN.h"
#include "CATMathFoundationX.h"

class CATMathProdXDel;

class ExportedByYN000FUN CATMathProdX : public CATMathFoundationX
{
 public:
  //-----------------------------------------------------------------
  //- Object Management
  //-----------------------------------------------------------------
  CATMathProdX(const CATMathFunctionX * iP, const CATMathFunctionX * iQ);
  virtual ~CATMathProdX();

  CATMathFunctionX * Duplicate() const;
  CATMathFunctionX * DeepDuplicate() const;
#if defined ( CATIACGMR216CAA )
  CATMathFunctionX * DeepDuplicateWithTol(const CATTolerance *ipTolObject) const ;
#endif
  //-----------------------------------------------------------------
  //- Information Methods
  //-----------------------------------------------------------------
  CATMathClassId IsA() const;
	/** @nodoc */
  int GetDirectComponents(const int iSizeOfComponents, const CATMathFunctionGeneral **ioComponents) const;
  CATBoolean IsAKindOf(const CATMathClassId ClassId) const;
  CATBoolean IsOption(const CATMathOption iOption) const;

  //-----------------------------------------------------------------
  //- Evaluators on doubles
  //-----------------------------------------------------------------
  double Eval(const double & t) const;
  double EvalFirstDeriv(const double & t) const;
  double EvalSecondDeriv(const double & t) const;
  double EvalThirdDeriv(const double & t) const;

  void Eval(const double t, const CATMathOption iOption,
	    double * f, double * df = 0, double * d2f = 0) const;

  //-----------------------------------------------------------------
  // Evaluators on intervals
  //-----------------------------------------------------------------
  CATMathInterval Eval(const CATMathInterval & x) const;
  CATMathInterval EvalFirstDeriv(const CATMathInterval & x) const;
  CATMathInterval EvalSecondDeriv(const CATMathInterval & x) const;

  void Eval(const CATMathInterval & I, const CATMathOption iOptions,
	    CATMathInterval * f, CATMathInterval * df = 0, 
	    CATMathInterval * d2f = 0) const;

  //-----------------------------------------------------------------
  // Private data
  //-----------------------------------------------------------------
 private:

  const CATMathFunctionX *_P, *_Q;
  friend class CATMathProdXDel;
};
#endif
