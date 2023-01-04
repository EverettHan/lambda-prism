 // COPYRIGHT DASSAULT SYSTEMES 1997 
//==========================================================================
//
// CATInterpolPtToPNurbs:
// Interface class of the Interpolation Operator for PCurves.
//
//==========================================================================
//
// Usage notes:
// This class is used in order to interpolate nbpt points (and their derivatives)
// The result is a CATPNurbs with (nbpt- 1) arcs.
// Its degree is equal to 3 if only points are interpolated, and is equal to 5
// if first derivatives are also interpolated. 
// The PNurbs has a global C2 continuity. 
//========================================================================== 
// Sept. 97     Creation                   DHN
//========================================================================== 

#ifndef CATInterpolPtToPNurbs_H
#define CATInterpolPtToPNurbs_H

class CATPNurbs;
class CATFrFNurbsMultiForm;
class CATSurface;
class CATKnotVector;
class CATMathSetOfPointsND;

#include "CATPGMCreateInterpolPtToPNurbs.h"
#include "CATCGMVirtual.h"

#include "CATGMOperatorsInterfaces.h"


//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATInterpolPtToPNurbs : public CATCGMVirtual
{
  public :

    virtual ~CATInterpolPtToPNurbs();
    virtual void Run()=0;
//
//  Setting the Points
//
    virtual void SetGlobalPoints(const CATMathSetOfPointsND * iPoints,
				const CATLONG32 & nvar0,
				const CATLONG32 & nvar1, const CATLONG32 & nvar2,
			        CATSurface * iSupport)=0;
// 
//  Impose a KnotVector 
// 
    virtual void SetImposedKnotVector(const CATKnotVector *iImposedKnotVector)=0;
// 
//  Getting the result 
// 
    virtual CATPNurbs *GetPNurbs()=0;
    virtual CATFrFNurbsMultiForm *GetNurbsMultiForm() const=0;
};

#endif
