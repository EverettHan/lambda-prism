#ifdef _Coverage_GOO
#ifndef CATCompactFunctionImpNode_H
#define CATCompactFunctionImpNode_H
//
// COPYRIGHT DASSAULT SYSTEMES 2003
//
//===================================================================
// August 2003 - ALA - Creation
//===================================================================
//
//#include "CATMathDef.h" 
//#include "CATCompactFunction.h"
class CATCompactFunctionImp;
class CATCompactApproxImp;
#include "CompactFunction.h"
#include "CATMathInline.h"


class ExportedByCompactFunction CATCompactFunctionImpNode
{
public:

	CATCompactFunctionImpNode();
	//
	CATCompactFunctionImpNode(double iVal[2][2]);
	//
	virtual ~CATCompactFunctionImpNode();
	//
	double Eval(const double & iU, const double & iV) const;
	double EvalFirstDerivX(const double & iU, const double & iV) const;
	double EvalFirstDerivY(const double & iU, const double & iV) const;
	double EvalSecondDerivX2(const double & iU, const double & iV) const;
	double EvalSecondDerivXY(const double & iU, const double & iV) const;
	double EvalSecondDerivY2(const double & iU, const double & iV) const;
	double EvalThirdDerivX3(const double & iX, const double & iY) const;
	double EvalThirdDerivX2Y(const double & iX, const double & iY) const;
	double EvalThirdDerivXY2(const double & iX, const double & iY) const;
	double EvalThirdDerivY3(const double & iX, const double & iY) const;
	//
protected :
	//
	friend class CATCompactApproxImp;
	friend class CATCompactFunctionImp;
	//
	static INLINE void Hermit1(double &t, double &H0, double &H1)
	{
		double fact = t-1;
		fact *= fact;
		H0 = fact * (1.+2.*t);
		H1 = fact * t;
	};
	//
	static INLINE void Hermit1FirstDerivative(double &t, double &H0, double &H1)
	{
		double fact = t-1;
		H0 = 6.* fact * t;
		H1 = fact * (3.*t - 1.);
	};
	//
	static INLINE void Hermit1SecondDerivative(double &t, double &H0, double &H1)
	{
		H0 = 12.*t-6.;
		H1 = 6.*t-4.;
	};
	//
	static INLINE void Hermit1ThirdDerivative(double &t, double &H0, double &H1)
	{
		H0 = 12.;
		H1 = 6.;
	};
	//
	double GetC0Weigth();
	//
	// fields
	double _Val[2][2];
};
#endif
#endif
