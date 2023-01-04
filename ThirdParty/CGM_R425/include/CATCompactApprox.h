#ifdef _Coverage_GOO
#ifndef CATCompactApprox_H
#define CATCompactApprox_H
//
// COPYRIGHT DASSAULT SYSTEMES 2003
//
//===================================================================
// August 2003 - ALA - Creation
//===================================================================
//
//#include "CATMathLimits.h"
//
class CATCompactFunction;
class CATCompactApproxImp;
class CATMathFunctionXY;
//
class CATCompactApprox  
{
  public:
	//
	CATCompactApprox() ;
	~CATCompactApprox();
	//
	//
	CATCompactFunction *Run(double &iXMin,
		double &iXMax,
		double &iYMin,
		double &iYMax,
		CATMathFunctionXY *iFunc,
		double iC0Accuracy = 1.e-3,
		double iC1Accuracy=CATMathInfinite);
	//
private:
	CATCompactApproxImp *_ApproxImp;
	//
};


#endif
#endif
