#ifdef _Coverage_GOO
#ifndef CATCompactFunctionImpNodeU_H
#define CATCompactFunctionImpNodeU_H
//
// COPYRIGHT DASSAULT SYSTEMES 2003
//
//===================================================================
// August 2003 - ALA - Creation
// 05 05 04 CCK Ajout de 	friend class CATCompactDump;
//
//===================================================================
//
//#include "CATMathDef.h" 
//#include "CATCompactFunction.h"
#include "CATCompactFunctionImpNode.h"


class CATCompactFunctionImpNodeU : public CATCompactFunctionImpNode
{
public:
	CATCompactFunctionImpNodeU()
		: CATCompactFunctionImpNode(),
		_West(0),
		_East(0)
	{};
	CATCompactFunctionImpNodeU(double iVal[2][2])
		: CATCompactFunctionImpNode(iVal),
		_West(0),
		_East(0)
	{};
	//
	~CATCompactFunctionImpNodeU()
	{
		ResetAll();
	};
	void ResetAll()
	{
		delete _East; _East =0;
		delete _West; _West =0;
	};
	//
	double Eval(const double & iU, const double & iV) const;
	double EvalFirstDerivX(const double & iU, const double & iV) const;
	double EvalFirstDerivY(const double & iU, const double & iV) const;
	double EvalSecondDerivX2(const double & iX, const double & iY) const;
	double EvalSecondDerivXY(const double & iU, const double & iV) const;
	double EvalSecondDerivY2(const double & iX, const double & iY) const;
	double EvalThirdDerivX3(const double & iX, const double & iY) const;
	double EvalThirdDerivX2Y(const double & iX, const double & iY) const;
	double EvalThirdDerivXY2(const double & iX, const double & iY) const;
	double EvalThirdDerivY3(const double & iX, const double & iY) const;

// private:
	//
	friend class CATCompactApproxImp;
	friend class CATCompactFunctionImp;
	friend class CATCompactDump;
	//
	//
	// fields
	CATCompactFunctionImpNodeU *_West;
	CATCompactFunctionImpNodeU *_East;
};
#endif
#endif
