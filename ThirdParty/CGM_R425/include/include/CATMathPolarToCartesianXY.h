//=============================================================================
// CATMathPolarToCartesianXY
//
// To convert from polar (R, theta) coordinates to cartesian (X,Y) coordinates
// 
// A 2D function that inherits from CATMathBasisFunctionXY 
//=============================================================================
// 28/08/19 F4E : Creation
// 27/03/20 F4E : new copy constructor
// DD/MM/YY
//=============================================================================

#ifndef CATMathPolarToCartesianXY_H
#define CATMathPolarToCartesianXY_H

// AdvancedMathematics
#include "CATMathBasisFunctionXY.h"
#include "YN000FUN.h"

// Mathematics
#include "CATMathConstant.h" // for CATMathClassId

//System
#include "CATBoolean.h"



class CATMathFunctionX;
class CATTolerance;

class ExportedByYN000FUN CATMathPolarToCartesianXY : public CATMathBasisFunctionXY
{
  public:

   // iIsEquationX : TRUE if one wants the cosine expression (that is the X coordinate function)
   CATMathPolarToCartesianXY ( const CATTolerance & iTolObject, CATBoolean iIsEquationU );
   ~CATMathPolarToCartesianXY();

   virtual CATBoolean               IsAKindOf  (const CATMathClassId             iClassId   ) const;
   virtual CATMathClassId           IsA        ()                                             const;
   virtual CATBoolean               IsOption   (const CATMathOption    iOption              ) const;
   virtual CATMathBasisFunctionXY * Duplicate  ()                                             const;

   virtual double  Eval               (const double & iR, const double & iTheta) const;
   virtual double  EvalFirstDerivX    (const double & iR, const double & iTheta) const;
   virtual double  EvalFirstDerivY    (const double & iR, const double & iTheta) const;
   virtual double  EvalSecondDerivX2  (const double & iR, const double & iTheta) const;
   virtual double  EvalSecondDerivXY  (const double & iR, const double & iTheta) const;
   virtual double  EvalSecondDerivY2  (const double & iR, const double & iTheta) const;
   virtual double  EvalThirdDerivX3   (const double & iR, const double & iTheta) const;
   virtual double  EvalThirdDerivX2Y  (const double & iR, const double & iTheta) const;
   virtual double  EvalThirdDerivXY2  (const double & iR, const double & iTheta) const;
   virtual double  EvalThirdDerivY3   (const double & iR, const double & iTheta) const; 

private:
  CATMathPolarToCartesianXY(const CATMathPolarToCartesianXY& iF);   

private:
  CATMathFunctionX * _FTrigo;
};

#endif //CATMathPolarToCartesianXY_H


