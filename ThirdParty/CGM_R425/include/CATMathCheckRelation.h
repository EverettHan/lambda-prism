/*-*-C++-*-*/
//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2000
//===================================================================
//
// CATMathCheckRelation
// Debugging class for CATMathRelation class.
//
//===================================================================
// Usage notes:
//
//===================================================================
#ifndef CATMathCheckRelation_H
#define CATMathCheckRelation_H

#include <stdlib.h>

#include "CATMathInterval.h"
#include "YN000DEV.h"
#include "CATCGMVirtual.h"

class CATMathRelation;
class CATMathIntervalND;

const double CheckRelationEps = 1.e-4;

//-------------------------------------------------------------------
class ExportedByYN000DEV CATMathCheckRelation : public CATCGMVirtual
{
public:
	CATMathCheckRelation(const CATMathRelation * iRelation, const double iEps = CheckRelationEps);
	~CATMathCheckRelation();
	
	// CheckAll calls all the other CheckXXX methods.
	// Value returned is 0 if OK, else the first non zero value of the CheckXXX methods if KO.
	CATLONG32 CheckAll(double * iAlpha=NULL, double * iBeta=NULL);
	
	// Comparison of Jacobian Matrix with the approximations of the Jacobian Matrix
	// Value returned is between 10 and 19 if KO
	CATLONG32 CheckJacobian(double * iAlpha=NULL, double * iBeta=NULL);
	
	// Test that the Eval method which evaluates _Relation and its derivatives is coherent
	// Value returned is between 20 and 29 if KO
	CATLONG32 CheckMultiEval(double * iAlpha=NULL, double * iBeta=NULL);
	
	
private:
	// Private Data
	// system to check
	const CATMathRelation * _MathRelation;
	// Tolerance for comparisons
	double _Eps;
	// Size of the relation
	CATLONG32 _IntDim;
	CATLONG32 _ExtDim;
};

#endif
