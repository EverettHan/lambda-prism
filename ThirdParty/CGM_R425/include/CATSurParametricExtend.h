// COPYRIGHT DASSAULT SYSTEMES 1998 
//==========================================================================
//
// CATSurParametricExtend:
// Interface class of the Surface Parametric Extension.
//
//==========================================================================
//
// Usage notes:
//
//========================================================================== 
// August. 98     Creation                       DHN
//========================================================================== 
//
#ifndef CATSurParametricExtend_H
#define CATSurParametricExtend_H
//
#include "CATGMOperatorsInterfaces.h"
#include "CATPGMCreateSurParametricExtend.h"
#include "CATCGMVirtual.h"

//
//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATSurParametricExtend  : public CATCGMVirtual
{
  public :

    virtual              ~CATSurParametricExtend();
    virtual void         SetExtremity(const CATSurParam &iSurParam)=0;
    virtual void         SetExtendRatio(const double &iExtendRatio)=0;
    virtual void         Run()=0;

};
#endif
