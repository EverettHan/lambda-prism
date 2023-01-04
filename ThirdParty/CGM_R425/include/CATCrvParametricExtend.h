// COPYRIGHT DASSAULT SYSTEMES 1998 
//==========================================================================
//
// CATCrvParametricExtend:
// Interface class of the Curve Parametric Extension.
//
//==========================================================================
//
// Usage notes:
//
//========================================================================== 
//   /08/98 DHN Creation
// 07/05/15 NLD Run() rend un entier
//========================================================================== 
//
#ifndef CATCrvParametricExtend_H
#define CATCrvParametricExtend_H
//
#include "CATGMOperatorsInterfaces.h"
#include "CATPGMCreateCrvParametricExtend.h"
#include "CATCGMVirtual.h"

//
//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATCrvParametricExtend : public CATCGMVirtual
{
  public :

    virtual              ~CATCrvParametricExtend();

    virtual void          SetExtremity          (const CATCrvParam & iCrvParam    ) = 0;

    virtual void          SetExtendRatio        (const double      & iExtendRatio ) = 0;

            // Run() returns 0 if OK. Otherwise, resulting curve is wrong
    virtual int           Run                   ()                                  = 0;

};
#endif
