// COPYRIGHT DASSAULT SYSTEMES 1998
//==========================================================================
//
// CATGeometricMatchSurface:
// Interface class of the Geometric Match Surface Operator.
//
//==========================================================================
//
// Usage notes:
// This class can be used as is for simple Match or derived
// in order to implement specific algorithm or capabilities.
//
//========================================================================== 
// Feb 98  Creation                      JBX
// Jan 99  Modification                  ALM
//========================================================================== 

#ifndef CATGeometricMatchSurface_H
#define CATGeometricMatchSurface_H

#include "CATGMOperatorsInterfaces.h"
#include "CATMatchSurface.h"
#include "CATPGMCreateGeometricMatchSurface.h"

class CATFrFCompositeCurve;

//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces 
CATGeometricMatchSurface : public CATMatchSurface
{
  public :
  
    virtual ~CATGeometricMatchSurface();
    //  Setting the Reference curve 
    //  It is a CATFrFCompositeCurve well ordoned (see CATFrFCompositeCurve.h)
    virtual void SetReferenceCurve(const CATFrFCompositeCurve *iCompositeCurve) = 0;
    
    //=========================
    //  O L D   M E T H O D S 
    //=========================
    //  Type of transition continuity
    // 1  : G0 (Default)
    // 2  : Colinear normals (G1)       
    // 3  : Curvature continuity (G2)
    virtual   void SetTransitionContinuity(CATLONG32 Continuity) = 0;
    virtual   CATLONG32 GetTransitionContinuity() const = 0;
    //  Setting the Match parameters 
    virtual void SetDefaultConfiguration(CATLONG32 &oCurveOrientationSide1,
					 CATLONG32 &oCurveOrientationSide2,
					 CATLONG32 &oTransitionOrientationSide1,
					 CATLONG32 &oTransitionOrientationSide2)=0;
    virtual void ReverseCurveOrientation(const CATLONG32 iSide) = 0; 
    virtual void SetTransitionOrientation(const CATLONG32 iSide, const CATLONG32 iorient) = 0;
    virtual void SetTangencyParameter(const CATLONG32 iSide, const double tgparam) = 0;
    virtual void SetCurvatureParameter(const CATLONG32 iSide, const double crparam) = 0;
};
#endif






