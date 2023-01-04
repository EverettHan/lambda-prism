//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  2000
//=============================================================================
//
// CATRelationCircleRadius:
//  Implement the relation defining a circle with a given radius
//
//=============================================================================
//
// Usage Notes:
//
//=============================================================================

#ifndef CATRelationCircleRadius_H
#define CATRelationCircleRadius_H

#include "Y30C1XMM.h"

#include "CATRelationCircle.h"

class ExportedByY30C1XMM CATRelationCircleRadius : public CATRelationCircle {
public :
	
	//-----------------------
	// Object Management
	//-----------------------
	CATRelationCircleRadius(const double iRadius);
	
	//-----------------------
	// Information methods :
	//-----------------------
	CATMathClassId IsA() const;
	CATBoolean IsAKindOf(CATMathClassId iClassId) const;
	
	CATBoolean IsLinear() const;
	
	CATLONG32 GetExteriorDimension() const; // return 0
	
	double GetRadius() const;
	
	//--------------
	// Evaluators :
	//--------------
	// alpha[..] are the interior parameters : alpha[0] = Center_U, alpha[1] = Center_V, alpha[2] = Radius
	// beta[..] the exterior parameters : there is no beta ; oFx[..] the output
	// The size of oFX[] is 1+GetExteriorDimension()
	void Eval(double * iAlpha, double * iBeta, double * oFX) const;
	
	// for oJac : M = 1 and N = 3
	void EvalJacobian(double * iAlpha, double * iBeta, CATMathMxNFullMatrix * oJac) const;
	
	// Multi-evaluator, for oJac : M = 1 and N = 3
	void Eval(double * iAlpha, double * iBeta, double * oFX, CATMathMxNFullMatrix * oJac) const;
	
private :
	// private data
	double _Radius;
};


#endif

