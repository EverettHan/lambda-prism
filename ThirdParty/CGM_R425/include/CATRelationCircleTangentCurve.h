//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  2000
//=============================================================================
//
// CATRelationCircleTangentCurve:
//  Implement the relation defining a circle tangent to a curve
//
//=============================================================================
//
// Usage Notes:
//
//=============================================================================

#ifndef CATRelationCircleTangentCurve_H
#define CATRelationCircleTangentCurve_H

#include "Y30C1XMM.h"

#include "CATRelationCircle.h"


#include "CATCrvLimits.h"

class CATMathFunctionX;
class CATPCurve;


class ExportedByY30C1XMM CATRelationCircleTangentCurve : public CATRelationCircle {
public :
	
	//-----------------------
	// Object Management
	//-----------------------
	CATRelationCircleTangentCurve(CATPCurve * iPCrv, const CATCrvLimits &iLimits);
	virtual ~CATRelationCircleTangentCurve();
	
	void SetPCurve(CATPCurve *iPCrv, const CATCrvLimits &iLimits);
	
	
	//-----------------------
	// Information methods :
	//-----------------------
	CATMathClassId IsA() const;
	CATBoolean IsAKindOf(CATMathClassId iClassId) const;
	
	CATBoolean IsLinear() const;
	
	CATLONG32 GetExteriorDimension() const; // return 1
	
	CATMathInterval GetExteriorDomain(CATLONG32 iExteriorParamIndex) const;
	
	CATPCurve *GetPCurve() const;
	
	//--------------
	// Evaluators :
	//--------------
	// alpha[..] are the interior parameters : alpha[0] = Center_U, alpha[1] = Center_V, alpha[2] = Radius
	// beta[..] the exterior parameters : beta[0] = CrvParam on Crv ; oFx[..] the output
	// The size of oFX[] is 1+GetExteriorDimension()
	void Eval(double * iAlpha, double * iBeta, double * oFX) const;
	
	// for oJac : M = 2 and N = 3
	void EvalJacobian(double * iAlpha, double * iBeta, CATMathMxNFullMatrix * oJac) const;
	
	// Multi-evaluator, for oJac : M = 2 and N = 3
	void Eval(double * iAlpha, double * iBeta, double * oFX, CATMathMxNFullMatrix * oJac) const;
	
private :
	// private data
	CATPCurve *_PCrv;
	const CATMathFunctionX * _GlobalEquationU;
	const CATMathFunctionX * _GlobalEquationV;
	CATMathInterval _Limits;
};


#endif

