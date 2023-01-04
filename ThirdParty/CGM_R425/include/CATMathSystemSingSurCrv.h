//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  2004
//=============================================================================
//
// CATMathSystemSingSurCrv:
//   Singular system for Curve-Surface Projection operators.
//
//=============================================================================
//   /08/02 obh Creation
// 07/06/16 NLD Changement de signature du conctructeur qui recoit
//              - la configuration
//              - l'objet tolerance en second et obligatoirement et non plus 
//                apres les fonctions et de maniere optionnelle
//=============================================================================

#ifndef CATMathSystemSingSurCrv_H
#define CATMathSystemSingSurCrv_H

#include "CATMathDef.h"
#include "CATMathSystem.h"
#include "YN000FUN.h"

class CATMathFunctionX;
class CATMathFunctionXY;
class CATMathNxNFullMatrix;
class CATMathIntervalND;
class CATSoftwareConfiguration;

//-----------------------------------------------------------------------------
class ExportedByYN000FUN CATMathSystemSingSurCrv : public CATMathSystem 
{ 
 public:

  CATMathSystemSingSurCrv(         CATSoftwareConfiguration* iConfig        ,
                             const CATTolerance            & TolObject      ,
                             const CATMathFunctionXY       * iFunctionCrv[3],
                             const CATMathFunctionX        * iFunctionSur[3],
   //                        const CATTolerance            & TolObject      = CATGetDefaultTolerance(),
                             const CATMathAttrList         * attributes     = NULL);

  virtual void Eval         (const double                  * iSX            ,
                                   double                  * oFX            ) ;

  virtual void EvalJacobian (const double                  * iX             ,
                                   CATMathNxNFullMatrix    * oJacobianFX    ); 

  virtual void Eval         (const double                  * iSX            ,
                                   double                  * oFX            ,
                                   CATMathNxNFullMatrix    * oJacobianFX    ); 

private:
  const CATMathFunctionXY  * _Function1[3];
  const CATMathFunctionX   * _Function2[3];
  
};

#endif  
