/* -*-C++-*-*/
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================
// CATMathTransfo2DFunctionX :
//=============================================================================
//=============================================================================
// May 03  Creation                          AAD
//=============================================================================
#ifndef CATMathTransfo2DFunctionX_H
#define CATMathTransfo2DFunctionX_H

#include "YN000FUN.h"

#include "CATMathFunctionX.h"
class CATMathTransformation2D;
class CATMathSystemXY;

class ExportedByYN000FUN CATMathTransfo2DFunctionX : public CATMathFunctionX 
{

 public:

CATMathTransfo2DFunctionX(const CATMathFunctionX * iU, const CATMathFunctionX * iV, 
						  const CATMathTransformation2D & iTransfo2D, CATBoolean iUorV);  
CATMathTransfo2DFunctionX(const CATMathFunctionX * iU, const CATMathFunctionX * iV, 
						  const CATMathSystemXY * iNonLinearTransfo2D, CATBoolean iUorV);  
virtual ~CATMathTransfo2DFunctionX();  
virtual double Eval(const double & iT) const;
virtual double EvalFirstDeriv(const double & iT) const;
virtual double EvalSecondDeriv(const double & iT) const;
virtual double EvalThirdDeriv (const double & iT) const;
virtual CATMathFunctionX * Duplicate() const;
virtual CATMathClassId IsA() const;

private:
CATMathTransfo2DFunctionX();
CATMathTransfo2DFunctionX(const CATMathTransfo2DFunctionX &);
void operator = (const CATMathTransfo2DFunctionX &);

double Scale(double iU, double iV) const;
void GetScaling(); 

const CATMathFunctionX * _U;
const CATMathFunctionX * _V;
CATMathTransformation2D * _Transfo2D;
const CATMathSystemXY * _NonLinearTransfo2D;
CATMathTransformation2D * _Scaling2D;
CATBoolean _UorV;

};

#endif

