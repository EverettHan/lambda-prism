//=============================================================================
// Intermediate class scalar for function of two variables, having a tolerance object.
//
// It is mainly used in order to avoid 
// going through finite difference evaluators of CATMathFunctionXY
//
// It computes the right step by multiplying it by the scale tolerance object.
// this is done for extreme scale project.All functions to be solved or minimized in geometric context should 
// inherit from this class and give the right the tolerance object
//=============================================================================
//      /06 obh creation 2006
// 23/04/09 NLD Ajout EvalAllThirdDerivs()
//              Ajout EvalAllSecondDerivs()
// 20/11/18 NLD Deflaggage R21
//              Changement de notations pour arguments du constructeur, et panneautage XScale
//              Mise au propre
//=============================================================================

#ifndef CATMathBasisFunctionXY_H
#define CATMathBasisFunctionXY_H

#include "YN000FUN.h"
#include "CATMathFunctionXY.h"
#include "CATTolerance.h"


class ExportedByYN000FUN CATMathBasisFunctionXY : public CATMathFunctionXY 
{

public:
  // XScale: (NLD201118)
  // - CAUTION: the constructor does not define a CATMathAttrScaleOption attribute datum
  //            powers for X and y (iPowerScaleX and iPowerScaleY) are used
  //            only for steps computation
  //            CATMathAttrScaleOption attributes will have to be defined later on
  //            when calling, for instance, a minimizer on the function
  //            Unlike CATMathBasisFunctionX for one variable mathematical function,
  //            this function does not provide a SetScaleOption() method, as of Nov 20th 2018
  //            and the scale option attribute will be specified whenever need
  //            through arguments lists of mother class CATMathFunctionXY methods
  //            (MinimizeNewton(), ComputeOptimalImage(), ...)

  CATMathBasisFunctionXY(const CATTolerance & iTolObject  ,
                               CATLONG32      iPowerScaleX,  // (former notation p1)
                               CATLONG32      iPowerScaleY); // (former notation p2)

  ///////////////////////////////////////////////////////
  //Evaluators 
  ///////////////////////////////////////////////////////  
  virtual       double         EvalFirstDerivX   (const double & iX, const double & iY) const;
  virtual       double         EvalFirstDerivY   (const double & iX, const double & iY) const;
  virtual       double         EvalSecondDerivX2 (const double & iX, const double & iY) const;
  virtual       double         EvalSecondDerivXY (const double & iX, const double & iY) const;
  virtual       double         EvalSecondDerivY2 (const double & iX, const double & iY) const;
  virtual       double         EvalThirdDerivX3  (const double & iX, const double & iY) const;
  virtual       double         EvalThirdDerivX2Y (const double & iX, const double & iY) const;
  virtual       double         EvalThirdDerivXY2 (const double & iX, const double & iY) const;
  virtual       double         EvalThirdDerivY3  (const double & iX, const double & iY) const;
  virtual       void           EvalAllThirdDerivs(const double   iX, const double   iY,
                                                        double & ofx3, double & ofx2y, double & ofxy2, double & ofy3) const ;

  virtual       CATBoolean     IsAKindOf         (const CATMathClassId          iClassId) const;

  virtual       CATBoolean     IsATypeOf         (const CATMathFunctionXYTypeId iType)    const;

  virtual       CATMathClassId IsA               () const;

          const CATTolerance & GetToleranceObject();

protected  :
                void           EvalAllSecondDerivs(const double  iX, const double iY,
                                                         double & ofx2, double & ofxy, double & ofy2) const;

  // Tolerance management dedicated data.
  const CATTolerance & _TolObject;

  //scaled finite difference step
        double         _h1x,
                       _h1y;
        double         _h2x,
                       _h2y;
        double         _h3x,
                       _h3y;
};

#endif

