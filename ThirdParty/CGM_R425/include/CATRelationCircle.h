//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  2000
//=============================================================================
//
// CATRelationCircle:
//  Abstract class used to define Relations that constrain a circle
//
//=============================================================================
//
// Usage Notes:
//
//=============================================================================

#ifndef CATRelationCircle_H
#define CATRelationCircle_H

#include "Y30C1XMM.h"

#include "CATMathRelation.h"

class ExportedByY30C1XMM CATRelationCircle : public CATMathRelation {
public :
    virtual ~CATRelationCircle();
	virtual CATMathClassId IsA() const;
	virtual CATBoolean IsAKindOf(CATMathClassId iClassId) const;
	
	CATLONG32 GetInteriorDimension() const; // The interior dimension of the CATRelationCircle is 3
	
	// alpha[..] are the interior parameters : alpha[0] = Center_U, alpha[1] = Center_V, alpha[2] = Radius
	// beta[..] the exterior parameters, oFx[..] the output
	// The size of oFX[] is 1+GetExteriorDimension()
	virtual void Eval(double * iAlpha, double * iBeta, double * oFX) const=0;
	
};


#endif

