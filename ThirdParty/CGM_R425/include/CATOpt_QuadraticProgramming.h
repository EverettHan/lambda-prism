//=============================================================================
// Usage notes:
//=============================================================================
// June 2017      Creation (SMT1)
// March 2018 SMT1 : Performance: Avoid solving K naively and instead use the block structure and the inverse of B that is provided
//                   as an input. Update derived data (_ABinv, _ABinvAt...) instead of recomputing it for each iteration              
//=============================================================================

// Minimize 1/2 * <x,Bx> - <x,b>
// subject to Ax = a, Cx <= c
// B nxn, symmetric, positive definite
// A mxn, m<=n, full rank
// C pxn, p<=n, full rank
// Direct solver. The solution is obtained by solving one set of linear equations.


#ifndef CATOpt_QP_H
#define CATOpt_QP_H

#include "YN000OPT.h"
#include "CATMathNxNFullSymMatrix.h"
#include "CATMathMxNMatrix.h"
#include "CATMathNxNMatrix.h"
#include "CATMathOptFunction.h"
#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATUnicodeString.h"
#include "CATTolerance.h"
#include "CATToleranceAccess.h"
#include "CATSoftwareConfiguration.h"
#include "CATSoftwareConfigurationAddRef.h"


//#define UseScaleInputs

class ExportedByYN000OPT CATOpt_QuadraticProgramming
{
public:

  CATOpt_QuadraticProgramming(CATSoftwareConfiguration *  iConfig,  const CATTolerance  & iTolObject, CATMathNxNFullSymMatrix &iB, double * ib, CATMathMxNMatrix & iA, double *ia);
  CATOpt_QuadraticProgramming(CATSoftwareConfiguration *  iConfig,  const CATTolerance  & iTolObject, CATMathNxNFullSymMatrix &iB, double * ib, CATMathMxNMatrix & iA, double *ia, CATMathMxNMatrix & iC, double *ic);

  ~CATOpt_QuadraticProgramming();

  CATBoolean Run();
  void SetBinv(CATMathNxNFullSymMatrix *iBinv);
  double * GetResult();
  double * GetMultipliers();

private:
#ifdef UseScaleInputs
  void ScaleInputs();
#endif
  void Update_K();
  void Initialize_K();
  CATMathDiagnostic SolveK();
  CATBoolean ComputeLambdaMu();
  void Update_ActiveSetAndSol();
  void Verify();
  void Print(double * iVect, CATULONG32 iSize, CATUnicodeString iName);
  void Print(CATMathNxNFullSymMatrix * iMat, CATUnicodeString iName);

  CATMathNxNFullSymMatrix  _B, *_Binv,*_K, *_ABinvAt;
  CATMathMxNMatrix  _A, _C, *_ABinv, *_ActiveConstr, *_ActiveConstrTrans;
  double * _b, *_a, *_c, *_x, *_p, * _sol, *_bv;
  double _ScaleFactor;
  CATLONG32 _N, _M, _L;
  CATLONG32 _LastToggled;
  CATBoolean * _ActiveSet;
  CATBoolean _UseIneqCon;
  CATBoolean _diag;
  CATBoolean _MultipliersUpToDate;

  CATSoftwareConfiguration  * _pConfig;
  const CATFullTolerance    & _TolObject;
};


#endif
