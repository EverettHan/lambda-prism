//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  2003
//=============================================================================
//
// CATMathSystemSingCrvSur:
//   Singular system for Curve-Surface connect operators.
//
//=============================================================================
// Feb 2003 klx Creation
// 06/06/16 NLD Constructeur avec software configuration
// 10/06/16 NLD Suppression definitive du constructeur sans configuration
//=============================================================================

#ifndef CATMathSystemSingCrvSur_H
#define CATMathSystemSingCrvSur_H

#include "CATMathDef.h"
#include "CATMathSystem.h"
#include "YN000FUN.h"

class CATSoftwareConfiguration;
class CATMathFunctionX;
class CATMathFunctionXY;
class CATMathNxNFullMatrix;
class CATMathIntervalND;

//-----------------------------------------------------------------------------
class ExportedByYN000FUN CATMathSystemSingCrvSur : public CATMathSystem 
{ 
 public:

  CATMathSystemSingCrvSur(      CATSoftwareConfiguration*  iConfig        ,
                          const CATTolerance             & iTolObject     ,
                          const CATMathFunctionX        *  iFunctionCrv[3],
                          const CATMathFunctionXY       *  iFunctionSur[3],
                          const CATMathAttrList         *  attributes     = NULL);

  virtual void Eval         (const double               * iSX        ,
                                   double               * oFX        );

  virtual void EvalJacobian (const double               * iX         ,
                                   CATMathNxNFullMatrix * oJacobianFX); 

  virtual void Eval         (const double               * iSX        ,
                                   double               * oFX        ,
                                   CATMathNxNFullMatrix * oJacobianFX);  

private:
  const CATMathFunctionX  *_Function1[3];
  const CATMathFunctionXY *_Function2[3];
  
};

#endif  
