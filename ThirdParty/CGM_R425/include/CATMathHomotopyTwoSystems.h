// COPYRIGHT DASSAULT SYSTEMES  1997
//=============================================================================
//
// CATMathHomotopyTwoSystems:
// Class used to Solve an implicit system of functions from 
// R(N+1)-->RN of form F(L, X) = (1-L)*F1(X) + L*F2(X). F1 and F2 are two 
// differentiable functions (C1) from RN-->RN.
// L is the parameter of the homotopy and is in [0,1].
//
//=============================================================================
//
// Usage notes:
// The result of the SolveHomotopy method is two sets of points.
// The first one is in dimension 1 (Li values) and the second one is
// in dimension N-1 (Xi values). 
//
//=============================================================================


#ifndef CATMathHomotopyTwoSystems_H  
#define CATMathHomotopyTwoSystems_H  

class CATMathIntervalND;
class CATMathSetOfPointsND;
class CATMathNxNFullMatrix;
class CATMathSystem;
class CATSoftwareConfiguration;

#include "YN000FUN.h"
#include "CATMathImplicitSystem.h"
#include "CATMathDef.h"
#include "CATMathDiagnostic.h"
#include "CATMathStopDiagnostic.h"
#include "CATCGMNewArray.h"

//-----------------------------------------------------------------------------
class ExportedByYN000FUN CATMathHomotopyTwoSystems : public CATMathImplicitSystem
{ 
  public:

     //Do not use
     CATMathHomotopyTwoSystems (const CATLONG32 iNMinus1,
                                CATMathSystem *iFirstFunctionX, 
                                CATMathSystem *iSecondFunctionX);
     CATMathHomotopyTwoSystems (CATSoftwareConfiguration * iConfig,const CATLONG32 iNMinus1,CATMathSystem *iFirstFunctionX, 
                                CATMathSystem *iSecondFunctionX, const CATTolerance & iTolObject=CATGetDefaultTolerance());

     ~CATMathHomotopyTwoSystems ();
      CATCGMNewClassArrayDeclare;
  //
  //  Compute the marching algorithm 
  //   Given a starting point X in RN the Solve method finds a set of sorted points (Li,Xi)
  //   in RN where F(Li,Xi)=0 and each point is in a Domain
  //   [Min X1, Max X1]x...x[Min XN, Max XN]
  //   The mode of repartition of the points and the density are given by the
  //   iAttributes argument.
  //   The CATMathDiagnostic is CATMathOK if the Solve found a set of points.  
  //   We have L0 = iLInit; By default, iLInit = 0.
  //
     virtual CATMathDiagnostic SolveHomotopy (const CATMathIntervalND &iDomain, 
                                              const double *iStartPoint,
                                              CATMathSetOfPointsND &oSetOfPointsL,
                                              CATMathSetOfPointsND &oSetOfPointsX,
					      const double iLInit=0.);
//
// Evaluators: iX is a point in RN.
//  . oFX = F(iX) is the image of iX by F. oFX is in RN and is already allocated. 
//  . oJacobianFX is the jacobian of F at iX and is in R(N*(N+1)) 
//    and is already allocated. 
//
    virtual void Eval         (const double *iX, double *oFX);
    virtual void EvalJacobian (const double *iX, CATMathNxNFullMatrix *oJacobianFX); 
    virtual void Eval         (const double *iX, double *oFX, CATMathNxNFullMatrix *oJacobianFX);

  protected:
    CATMathSystem *_FX1, *_FX2;
    CATMathNxNFullMatrix *_DFX1Eval, *_DFX2Eval;
    double *_FX1Eval, *_FX2Eval;
    CATLONG32 _N, _NPlus1;
};  
#endif  
