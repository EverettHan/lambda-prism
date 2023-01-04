//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  2000
//=============================================================================
//
// CATMathRelation:
//  Abstract class used to define Relations to be solved
//
//
//=============================================================================
//
// Usage Notes:
//
//=============================================================================

#ifndef CATMathRelation_H
#define CATMathRelation_H

#include "YN000FUN.h"

#include "CATMathDef.h"

#include "CATMathInterval.h"

#include "CATMathMxNFullMatrix.h"
#include "CATCGMVirtual.h"

class ExportedByYN000FUN CATMathRelation  : public CATCGMVirtual
{
public :
    virtual ~CATMathRelation();
	virtual CATMathClassId IsA() const;
	virtual CATBoolean IsAKindOf(CATMathClassId iClassId) const;
	
	virtual CATLONG32 GetInteriorDimension() const=0;
	virtual CATLONG32 GetExteriorDimension() const; // par default, =0
	
	// 0<= iExteriorParamIndex < ExteriorDimension et par defaut, return [0,0]
	virtual CATMathInterval GetExteriorDomain(CATLONG32 iExteriorParamIndex) const;
	
	virtual CATBoolean IsLinear() const; // La contrainte est-elle lineaire ?
	
	// alpha[..] are the interior parameters, beta[..] the exterior parameters, oFx[..] the output
	// The size of oFX[] is 1+GetExteriorDimension()
	virtual void Eval(double * iAlpha, double * iBeta, double * oFX) const=0;
	
	
	virtual void EvalJacobian(double * iAlpha, double * iBeta, CATMathMxNFullMatrix * oJac) const;
	
	// Multi-evaluator
	virtual void Eval(double * iAlpha, double * iBeta, double * oFX, CATMathMxNFullMatrix * oJac) const;
	
};


#endif

