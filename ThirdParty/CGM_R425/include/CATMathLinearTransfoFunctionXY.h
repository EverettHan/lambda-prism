//=============================================================================
// CATMathLinearTransfoFunctionXY
//
// (x,y) -> iShift + iScale * iFunc(x,y)
// 
// A 2D function that inherits from CATMathBasisFunctionXY 
//=============================================================================
// 22/10/19 F4E : Creation
// DD/MM/YY
//=============================================================================

#ifndef CATMathLinearTransfoFunctionXY_H
#define CATMathLinearTransfoFunctionXY_H

// AdvancedMathematics
#include "CATMathBasisFunctionXY.h"
#include "YN000FUN.h"

// Mathematics
#include "CATMathConstant.h" // for CATMathClassId




class CATMathFunctionXY;

class ExportedByYN000FUN CATMathLinearTransfoFunctionXY : public CATMathFunctionXY
{
  public:

   CATMathLinearTransfoFunctionXY ( CATMathFunctionXY const * iFunc, double const iShift, double const iScale );
   ~CATMathLinearTransfoFunctionXY();

   virtual CATBoolean      IsAKindOf  (const CATMathClassId             iClassId   ) const;
   virtual CATMathClassId  IsA        ()                                             const;

   virtual double  Eval               (const double & iX, const double & iY) const;
   virtual double  EvalFirstDerivX    (const double & iX, const double & iY) const;
   virtual double  EvalFirstDerivY    (const double & iX, const double & iY) const;
   virtual double  EvalSecondDerivX2  (const double & iX, const double & iY) const;
   virtual double  EvalSecondDerivXY  (const double & iX, const double & iY) const;
   virtual double  EvalSecondDerivY2  (const double & iX, const double & iY) const;
   virtual double  EvalThirdDerivX3   (const double & iX, const double & iY) const;
   virtual double  EvalThirdDerivX2Y  (const double & iX, const double & iY) const;
   virtual double  EvalThirdDerivXY2  (const double & iX, const double & iY) const;
   virtual double  EvalThirdDerivY3   (const double & iX, const double & iY) const;
   

   

private:
  double const _Shift;
  double const _Scale;
  CATMathFunctionXY const * _F;
};

#endif //CATMathLinearTransfoFunctionXY_H


