// COPYRIGHT DASSAULT SYSTEMES 1997 
//==========================================================================
//
// CATBreakCurve:
// Interface class of the Break Curve Operator.
//
//==========================================================================
//
// Usage notes:
//
//========================================================================== 
// September 97     Creation                       GDR
//========================================================================== 
//
#ifndef CATBreakCurve_H
#define CATBreakCurve_H
//
#include "CATGMOperatorsInterfaces.h"
#include "CATMathDef.h"
#include "CATPGMCreateBreakCurve.h"
#include "CATCGMVirtual.h"
//
class CATCurve;
//
//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATBreakCurve : public CATCGMVirtual
{
  public :

    virtual              ~CATBreakCurve();
    virtual void         Run()=0;
//
//  Getting the Break result 
// 
    virtual CATLONG32         GetNumberOfBreakCurves()        const=0;
    virtual void         BeginningBreakCurve()                =0;
    virtual CATBoolean   NextBreakCurve()                     =0;
    virtual CATCurve*    GetBreakCurve()                 const=0;
    virtual void         SetGlobalBreakCurve(CATCurve *) const=0;
};
#endif
