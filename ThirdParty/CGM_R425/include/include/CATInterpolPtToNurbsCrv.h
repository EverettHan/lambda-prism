 // COPYRIGHT DASSAULT SYSTEMES 1997 
//==========================================================================
//
// CATInterpolPtToNurbsCrv:
// Interface class of the Interpolation Operator for Curves.
//
//==========================================================================
//
// Usage notes:
// This class is used in order to interpolate nbpt points (and their derivatives)
// The result is a CATNurbsCurve with (nbpt- 1) arcs.
// Its degree is equal to 3 if only points are interpolated, and is equal to 5
// if first derivatives are also interpolated. 
// The NurbsCurve has a global C2 continuity. 
//========================================================================== 
// Sept. 97     Creation                   DHN
//========================================================================== 

#ifndef CATInterpolPtToNurbsCrv_H
#define CATInterpolPtToNurbsCrv_H

class CATNurbsCurve;
class CATFrFNurbsMultiForm;
class CATMathPoint;
class CATKnotVector;
class CATMathSetOfPointsND;

#include "CATPGMCreateInterpolPtToNurbsCrv.h"
#include "CATCGMVirtual.h"

#include "CATGMOperatorsInterfaces.h"


//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATInterpolPtToNurbsCrv : public CATCGMVirtual
{
  public :

    virtual                       ~CATInterpolPtToNurbsCrv();
    virtual void                   Run                    ()                                                = 0;
//
//  Setting the Points
//  N.B nvar0, nvar1, nvar2 are the index (starting at 0) in iPoints, that may be of a dimension superior to 3,
//      of X, Y and Z coordinates; additional comment NLD081119
    virtual void                   SetGlobalPoints        (const CATMathSetOfPointsND * iPoints           ,
                                                           const CATLONG32            & nvar0             ,
                                                           const CATLONG32            & nvar1             ,
                                                           const CATLONG32            & nvar2             ) = 0;
// 
//  Impose a KnotVector 
// 
    virtual void                   SetImposedKnotVector   (const CATKnotVector        * iImposedKnotVector) = 0;

// 
//  Getting the result 
// 
    virtual CATNurbsCurve        * GetNurbsCurve          ()                                                = 0;
    virtual CATFrFNurbsMultiForm * GetNurbsMultiForm      () const                                          = 0;
};

#endif
