// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATMathCheckFunctionX
// Debugging class for CATMathFunctionX class.
//
//===================================================================
// Usage notes:
//
//===================================================================

#ifndef CATMathCheckFunctionX_H
#define CATMathCheckFunctionX_H

#include "CATMathInterval.h"
#include "YN000DEV.h"
#include "CATCGMVirtual.h"

class  CATMathFunctionX;

const CATMathInterval DefaultInterval(-0.3,1.3);
const double MyEps = 1.e-10;

//-------------------------------------------------------------------
class ExportedByYN000DEV CATMathCheckFunctionX : public CATCGMVirtual
{
public:
  CATMathCheckFunctionX(const CATMathFunctionX * F, const double iEps = MyEps);

  // CheckAll calls all the other CheckXXX methods.
  // Value returned is 0 if OK, else the first non zero value of the CheckXXX methods if KO.
  CATLONG32 CheckAll( const double x = 0.5, CATMathInterval * iD = NULL,
		const CATLONG32 iNbPoints = 10);

  // Test IsA() and IsAKindOf(). value returned is between 1 and 9 if KO
  CATLONG32 CheckIsA();

  // Comparison of derivatives with the approximations of the derivative
  // Value returned is between 10 and 19 if KO
  CATLONG32 CheckDerivatives(const double x);

  // Test that the Eval method which evaluates _F and its derivatives is coherent
  // Value returned is between 20 and 50 if KO
  CATLONG32 CheckMultiDerivEval(const double x);

  // Test that the value of _F(x) with x in iD belongs to _F(iD).
  // Value returned is between 50 and 59 if KO
  CATLONG32 CheckIntervalEvals(const CATMathInterval & iD);

  // Test that the Eval method which evaluates _F and its derivatives is coherent on
  // the intervals
  // Value returned is between 60 and 99 if KO
  CATLONG32 CheckMultiDerivIntervalEval(const CATMathInterval & iD);

  // Test the the evaluator on the grid is coherent. 
  // Value returned is between 100 and 129 if KO
  CATLONG32 CheckGridEval(const CATMathInterval & iD, const CATLONG32 iNbPoints = 10);

  // Test Duplicate and DeepDuplicate methods
  // Value returned is between 130 and 131 if KO
  CATLONG32 CheckDuplicate(const CATMathInterval & iD, const CATLONG32 iNbPoints = 10);

private:
  CATLONG32 SubCheckInterval(const CATMathInterval & iD, 
			const CATMathOption iOptions,
			const CATMathInterval & IF,
			const CATMathInterval & IDF,
			const CATMathInterval & ID2F,
			const CATMathInterval & ID3F);

  const CATMathFunctionX * _F;
  double _Eps;
};

#endif
