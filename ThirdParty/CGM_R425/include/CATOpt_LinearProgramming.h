//=============================================================================
// Class to solve linear constraint optimisation problems using the simplex method.
// Iterative solver that converges after finitely many steps.
//min e*x
//s.t Ax =a, Cx <= c
//=============================================================================
// Usage notes:
//=============================================================================
// June 2017      Creation (SMT1)
// March 2018     SMT1 Use sparse matrices to represent _AJinv and elementary operations
//=============================================================================


#ifndef CATOpt_LP_H
#define CATOpt_LP_H

#include "YN000OPT.h"
#include "CATMathNxNFullSymMatrix.h"
#include "CATMathMxNMatrix.h"
#include "CATMathOptFunction.h"
#include "CATMathSetOfLongs.h"
#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATMathSparseMxNMatrix.h"

class ExportedByYN000OPT CATOpt_LinearProgramming
{
public:

  CATOpt_LinearProgramming(CATMathMxNMatrix & iC, double * ic, double * ie);
  CATOpt_LinearProgramming(CATMathMxNMatrix & iA, CATMathMxNMatrix & iC, double * ia, double * ic, double * ie);
  CATOpt_LinearProgramming(CATMathMxNMatrix & iA, CATMathMxNMatrix & iC, double * ia, double * ic);

  ~CATOpt_LinearProgramming();

  CATBoolean Run();
  double * GetResult();
  CATBoolean* GetActiveSet();
private:

  void Init(CATMathMxNMatrix & iA, CATMathMxNMatrix & iC, double * ia, double * ic);
  void AddObjective();
  void DoOneRun();
  CATBoolean FindUpdateIndex(CATLONG32& ioIndex, CATLONG32& ioSign);
  CATBoolean FindIndexToReplace(CATLONG32& ioOldIndex, CATLONG32 iSign);
  CATBoolean UpdateIndexSets(CATLONG32 iOldIndex, CATLONG32 iNewIndex);
  CATBoolean UpdateAJinv(CATLONG32 iOldIndex);
   // void Print(CATMathMxNMatrix M);

  CATMathMxNMatrix *_B;
  double * _b,* _x, *_sol, *_e, *_a, *_temp;
  CATLONG32 _m,_p,_q, _t;
  CATLONG32 _N,_M,_L;
  CATMathSetOfLongs *_J, *_K;
  CATMathSparseMxNMatrix *_AJinv;
  CATBoolean _diag;
  CATBoolean _ObjectiveSet;
};


#endif

