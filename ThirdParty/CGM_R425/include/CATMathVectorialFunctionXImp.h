// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
//
// CATMathVectorialFunctionXImp :
// Derived class of polynoms of five degrees
//
//=============================================================================
// Usage notes:
// Base class : CATMathPolynomX
//
//=============================================================================


#ifndef CATMathVectorialFunctionXImp_H
#define CATMathVectorialFunctionXImp_H

#include "CATMathVectorialFunctionX.h"
#include "YN000FUN.h"

#include "CATTolerance.h"

class CATSoftwareConfiguration;
class CATMathFunctionX;

class ExportedByYN000FUN CATMathVectorialFunctionXImp : public CATMathVectorialFunctionX
{
public :
  //---------------------------------------------------------------
  // Constructors
  //---------------------------------------------------------------
  CATMathVectorialFunctionXImp (const CATLONG32 iN, const CATMathFunctionX **iFX);
  CATMathVectorialFunctionXImp (CATSoftwareConfiguration   *iSoftwareConfiguration,const CATLONG32 iN, const CATMathFunctionX **iFX,const CATTolerance &iTol=CATGetDefaultTolerance());
  //---------------------------------------------------------------
  // Evaluators
  //--------------------------------------------------------------- 
  void Eval (const double  iX, double *oFX) const;
  void EvalFirstDeriv   (const double  iX, double *oDFX) const; 
  void EvalSecondDeriv  (const double  iX, double *oD2FX) const; 
  void Eval             (const double  iX, double *oFX, double *oDFX) const;
  void EvalDeriv        (const double  iX, double *oDFX, double *oD2FX) const;
 
private:
  CATLONG32 _Nloc;
  const CATMathFunctionX **_FX;
};

#endif


