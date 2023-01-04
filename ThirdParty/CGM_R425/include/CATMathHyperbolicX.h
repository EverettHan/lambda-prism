#ifndef CATMathHyperbolicX_H
#define CATMathHyperbolicX_H

// COPYRIGHT DASSAULT SYSTEMES 1999

//=============================================================================
// 30/09/11 R1Y Added access functions (for comparing geometries).
//=============================================================================

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
#include "CATIACGMLevel.h"
#include "YN000FUN.h"

#include "CATMathFunctionX.h"

class ExportedByYN000FUN CATMathHyperbolicX : public CATMathFunctionX
{
 public:
  CATMathHyperbolicX(const double a,
		     const double b,
		     const double c,
		     const double w);
  CATCGMNewClassArrayDeclare;

  CATMathClassId IsA() const;
  int GetDirectComponents(const int iSizeOfComponents, const CATMathFunctionGeneral **ioComponents) const;
  CATBoolean IsAKindOf(const CATMathClassId iClassId) const;
  CATBoolean IsATypeOf(const CATMathFunctionXTypeId iType) const;  
  CATBoolean IsOption(const CATMathOption iOption) const;
  CATMathFunctionX * Duplicate() const;
  CATMathFunctionX * DeepDuplicate() const;
#if defined ( CATIACGMR216CAA )
  CATMathFunctionX * DeepDuplicateWithTol(const CATTolerance *ipTolObject) const ;
#endif

  double GetCoeffA() const;
  double GetCoeffB() const;
  double GetCoeffC() const;
  double GetCoeffW() const;

  double Eval(const double & t) const;
  double EvalFirstDeriv(const double & t) const;
  double EvalSecondDeriv(const double & t) const;
  CATMathInterval Eval(const CATMathInterval & x) const;
  CATMathInterval EvalFirstDeriv(const CATMathInterval & x) const;
  CATMathInterval EvalSecondDeriv(const CATMathInterval & x) const;

//- Derivative
  CATMathHyperbolicX Deriv() const;

//- operator <<
  friend ExportedByYN000FUN ostream & operator <<
    (ostream& os, CATMathHyperbolicX & f);

 private:
  double _a, _b, _c, _w;
};
#endif
