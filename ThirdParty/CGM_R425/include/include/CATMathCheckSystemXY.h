/*-*-C++-*-*/
//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
//===================================================================
//
// CATMathCheckSystemXY
// Debugging class for CATMathSystemXY class.
//
//===================================================================
// Usage notes:
//
//===================================================================
#ifndef CATMathCheckSystemXY_H
#define CATMathCheckSystemXY_H

#include <stdlib.h>

#include "YN000DEV.h"

#include "CATMathInterval2D.h"
#include "CATCGMVirtual.h"

class CATMathSystemXY;

const double CheckSystemXYEps = 2.e-5;

//-------------------------------------------------------------------
class ExportedByYN000DEV CATMathCheckSystemXY  : public CATCGMVirtual
{
public:
	CATMathCheckSystemXY(const CATMathSystemXY * iSystem, CATMathInterval2D & iDomain, const double iEps = CheckSystemXYEps);
	~CATMathCheckSystemXY();
	
	// CheckAll calls all the other CheckXXX methods.
	// Value returned is 0 if OK, else the first non zero value of the CheckXXX methods if KO.
	CATLONG32 CheckAll(const double * iX=NULL);
	
	// Value returned is between 1 and 4 if KO
	CATLONG32 CheckFirstDeriv(const double * iX=NULL);
	
	// Value returned is between 11 and 16 if KO
	CATLONG32 CheckSecondDeriv(const double * iX=NULL);
	
	// Value returned is between (21, 26) or (31, 36) if KO
	CATLONG32 CheckGridEval(const CATLONG32 * iNbPoints = NULL);
	
	// Test that the Multi Eval method which evaluates _System and its derivatives is coherent
	// Value returned is between (41, 46) or (51, 56) if KO
	CATLONG32 CheckMultiEval(const double * iX=NULL);
	
	
private:
	// Private Data
	// system to check
	const CATMathSystemXY * _MathSystem;
	// Tolerance for comparisons
	double _Eps;
	// Domain
	CATMathInterval2D _Domain;
};

#endif
