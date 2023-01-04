#ifdef _Coverage_GOO
#ifndef CATCompactFunctionImpNodeUV_H
#define CATCompactFunctionImpNodeUV_H
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
class CATCompactFunctionImpNodeU;
class CATCompactFunctionImpNodeV;

class CATCompactFunctionImpNodeUV : public CATCompactFunctionImpNode
{
public:
	CATCompactFunctionImpNodeUV()
		: CATCompactFunctionImpNode(),
		_West(0),
		_East(0),
		_South(0),
		_North(0),
		_South_West(0),
		_South_East(0),
		_North_West(0),
		_North_East(0)
	{};
	//
	CATCompactFunctionImpNodeUV(double iVal[2][2])
		: CATCompactFunctionImpNode(iVal),
		_West(0),
		_East(0),
		_South(0),
		_North(0),
		_South_West(0),
		_South_East(0),
		_North_West(0),
		_North_East(0)
	{};
	//
	~CATCompactFunctionImpNodeUV()
	{
		ResetAll();
	};
	//
	void ResetAll()
	{
		delete _North_East; _North_East =0;
		delete _North_West; _North_West =0;
		delete _South_East; _South_East =0;
		delete _South_West; _South_West =0;
		delete _North; _North =0;
		delete _South; _South =0;
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

private:
	//
	friend class CATCompactApproxImp;
	friend class CATCompactFunctionImp;
  friend class CATCompactDump;

	//
	// fields
	CATCompactFunctionImpNodeU *_West;
	CATCompactFunctionImpNodeU *_East;
	CATCompactFunctionImpNodeV *_South;
	CATCompactFunctionImpNodeV *_North;
	CATCompactFunctionImpNodeUV *_South_West;
	CATCompactFunctionImpNodeUV *_South_East;
	CATCompactFunctionImpNodeUV *_North_West;
	CATCompactFunctionImpNodeUV *_North_East;
};
#endif
#endif
