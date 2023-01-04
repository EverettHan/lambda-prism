#ifndef CATMathFunctionXYToX_H
#define CATMathFunctionXYToX_H
// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATMathFunctionXYToX
// One variable function defined by a two variables functions with
// one constant variable.
//
//===================================================================
// Usage notes:
//
//===================================================================
// Nov. 96    Creation                         S. Royer
// Mar. 97    Modif                            X. Gourdon
// 29/05/07 NLD XScale. _TolObject passe en public
//===================================================================
#include "CATIACGMLevel.h"

#include "YN000FUN.h"

#include "CATMathDef.h"
#include "CATMathInterval.h"

#include "CATMathFoundationX.h"

class CATMathAttrList;
class CATMathConstraint;
class CATMathFunctionXY;
class CATMathSetOfPointsND;
class CATMathFunctionXYToXDel;

class ExportedByYN000FUN CATMathFunctionXYToX : public CATMathFoundationX
{
// public methods
 public:
  //-----------------------------------------------------------------
  // Object Management
  //-----------------------------------------------------------------
  CATMathFunctionXYToX(const CATMathFunctionXY * fxy,
		       const double & constant,
		       const CATLONG32 & varnumber,
           const CATTolerance & iTolObject = CATGetDefaultTolerance());
  CATMathFunctionXYToX(const CATMathFunctionXYToX & f);
  virtual ~CATMathFunctionXYToX();
  CATCGMNewClassArrayDeclare;

  INLINE void SetConstant(const double & constant){_constant = constant;}

  //-----------------------------------------------------------------
  // Information methods
  //-----------------------------------------------------------------
  CATMathClassId IsA() const;
  int GetDirectComponents(const int iSizeOfComponents, const CATMathFunctionGeneral **ioComponents) const;
  CATBoolean IsAKindOf(const CATMathClassId iClassId) const;
  CATBoolean IsATypeOf(const CATMathFunctionXTypeId iType) const;    
  CATBoolean IsOption(const CATMathOption iOption) const;
   
  //-----------------------------------------------------------------
  // Evaluators on doubles
  //-----------------------------------------------------------------   
  double Eval(const double & t) const;
  double EvalFirstDeriv(const double & t) const;
  double EvalSecondDeriv(const double & t) const;
  double EvalThirdDeriv (const double & t) const;
   
  //-----------------------------------------------------------------
  // Evaluators on intervals
  //-----------------------------------------------------------------
  CATMathInterval Eval(const CATMathInterval & x) const;
  CATMathInterval EvalFirstDeriv(const CATMathInterval & x) const;
  CATMathInterval EvalSecondDeriv(const CATMathInterval & x) const;
  //CATMathInterval EvalThirdDeriv(const CATMathInterval & x) const;
   
  //-----------------------------------------------------------------
  // Duplicator
  //-----------------------------------------------------------------
  CATMathFunctionX * Duplicate() const;
  CATMathFunctionX * DeepDuplicate() const;
#if defined ( CATIACGMR216CAA )
  CATMathFunctionX * DeepDuplicateWithTol(const CATTolerance *ipTolObject) const ;
#endif
  const CATTolerance & _TolObject;

 private:
  const CATMathFunctionXY * _F;
  double _constant;
  CATMathInterval _interval;
  CATLONG32 _varnumber;
  friend class CATMathFunctionXYToXDel;

};

#endif
//automate:13/09/01:suppression include de CATMathDiagnostic.h
