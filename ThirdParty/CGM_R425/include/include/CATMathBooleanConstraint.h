//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  2000
//=============================================================================
//
// CATMathBooleanConstraint:
//  Abstract class used to define boolean constraints to relimit the relation
//
//
//=============================================================================
//
// Usage Notes:
//
//=============================================================================

#ifndef CATMathBooleanConstraint_H
#define CATMathBooleanConstraint_H

#include "YN000FUN.h"

#include "CATMathConstant.h"

#include "CATMathInterval.h"
#include "CATCGMVirtual.h"


class ExportedByYN000FUN CATMathBooleanConstraint  : public CATCGMVirtual
{
public :
	virtual CATMathClassId IsA() const;
	virtual CATBoolean IsAKindOf(CATMathClassId iClassId) const;
	
	virtual CATLONG32 GetInteriorDimension() const=0;
	virtual CATLONG32 GetExteriorDimension() const; // par default, =0
	
	// 0<= iExteriorParamIndex < ExteriorDimension et par defaut, return [0,0]
	virtual CATMathInterval GetExteriorDomain(CATLONG32 iExteriorParamIndex) const;
	
	// alpha[..] are the interior parameters, beta[..] the exterior parameters
	virtual CATBoolean Eval(double * iAlpha, double * iBeta) const=0;
	
};


#endif

