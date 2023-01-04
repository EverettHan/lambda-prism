/*-*-C++-*-*/
//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
//===================================================================
//
// CATMathCheckImplicitSystem
// Debugging class for CATMathImplicitSystem class.
//
//===================================================================
// Usage notes:
//
//===================================================================
#ifndef CATMathCheckImplicitSystem_H
#define CATMathCheckImplicitSystem_H

#include <stdlib.h>

#include "CATMathInterval.h"
#include "YN000DEV.h"
#include "CATCGMVirtual.h"

class CATMathImplicitSystem;
class CATMathIntervalND;

const double CheckSystemEps = 1.e-4;

//-------------------------------------------------------------------
class ExportedByYN000DEV CATMathCheckImplicitSystem : public CATCGMVirtual
{
public:
	CATMathCheckImplicitSystem(const CATMathImplicitSystem * iSystem, const double iEps = CheckSystemEps);
	~CATMathCheckImplicitSystem();
	
	// CheckAll calls all the other CheckXXX methods.
	// Value returned is 0 if OK, else the first non zero value of the CheckXXX methods if KO.
	CATLONG32 CheckAll(const double * iX=NULL);
	
	// Comparison of Jacobian Matrix with the approximations of the Jacobian Matrix
	// Value returned is between 10 and 19 if KO
	CATLONG32 CheckJacobian(const double * iX=NULL);
	
	// Test that the Eval method which evaluates _System and its derivatives is coherent
	// Value returned is between 20 and 29 if KO
	CATLONG32 CheckMultiEval(const double * iX=NULL);
	
	
private:
	// Private Data
	// system to check
	const CATMathImplicitSystem * _MathSystem;
	// Tolerance for comparisons
	double _Eps;
	// Size of the system
	CATLONG32 _N;
};

#endif
