// COPYRIGHT DASSAULT SYSTEMES  1997
//=============================================================================
//
// CATMathImplicitSystemXY:
// Concrete class used to Solve an implicit system of functions from 
// R2-->R1 with F differentiable (C1) .
//
//=============================================================================

#ifndef CATMathImplicitSystemXY_h
#define CATMathImplicitSystemXY_h

#include "YN000FUN.h"
#include "CATMathDef.h"
#include "CATMathImplicitSystem.h"
#include "CATCGMNewArray.h"

class CATMathFunctionXY;
class CATMathNxNFullMatrix;
class CATSoftwareConfiguration;


class ExportedByYN000FUN CATMathImplicitSystemXY : public CATMathImplicitSystem
{
 public:
  //Do not use
  //CATMathImplicitSystemXY(const CATMathFunctionXY *iXY);
  CATMathImplicitSystemXY(CATSoftwareConfiguration * iConfig,const CATMathFunctionXY *iXY, const CATTolerance & iTolObject=CATGetDefaultTolerance());
  
  ~CATMathImplicitSystemXY();
  CATCGMNewClassArrayDeclare;

  void Eval(const double *iX, double *oFX);
  void EvalJacobian(const double *iX, CATMathNxNFullMatrix *oJacobianFX);
  void Eval(const double *iX, double *oFX, CATMathNxNFullMatrix *oJacobianFX);

 private:
  const CATMathFunctionXY *_XY;

};


#endif
