#ifdef _Coverage_GOO
#ifndef CATCompactApproxImp_H
#define CATCompactApproxImp_H
//
// COPYRIGHT DASSAULT SYSTEMES 2003
//
//===================================================================
// August 2003 - ALA - Creation
//===================================================================
//
//#include "CATMathLimits.h"
//
//#include "CATCompactfunctionImp.h"
//
class CATMathFunctionXY;
#include "CompactFunction.h"
//
//
class ExportedByCompactFunction CATCompactApproxImp  
{
public:
	//
	CATCompactApproxImp() ;
	~CATCompactApproxImp();
	//
	//
	CATCompactFunctionImp *Run(const double &iXMin,
		const double &iXMax,
		const double &iYMin,
		const double &iYMax,
		const CATMathFunctionXY *iFunc,
		const double iC0Accuracy = 1.e-3,
		const double iC1Accuracy=CATMathInfinite);
	//
private:

	CATCompactFunctionImpNode *ApproxNode(	const double &iX,
											const double &iY,
											const double &iScaleU,
											const double &iScaleV);
	//
	void ApproxNodeU(CATCompactFunctionImpNodeU *&TheNodeU,
											  const double &iX,
											  const double &iY,
											  const double &iScaleU,
											  const double &iScaleV, 
											  short iDepthSinceSmall =0,
											  short iTotalDepth =0);
	//
	void ApproxNodeV(CATCompactFunctionImpNodeV *&TheNodeV,
											  const double &iX,
											  const double &iY,
											  const double &iScaleU,
											  const double &iScaleV, 
											  short iDepthSinceSmall =0,
											  short iTotalDepth =0);
	//
	void ApproxNodeUV(CATCompactFunctionImpNodeUV *&TheNodeUV,
												  const double &iX,
												  const double &iY,
												  const double &iScaleU,
												  const double &iScaleV, 
												  short iDepthSinceSmall =0,
												  short iTotalDepth =0);
	//
	double GetC0Weight(CATCompactFunctionImpNode *iNode) const;
	//
	// fields
	CATCompactFunctionImp *_FunctionImp;
	const CATMathFunctionXY *_FunctionInput;
	double _C0Accuracy;
	double _C1Accuracy;
};


#endif
#endif
