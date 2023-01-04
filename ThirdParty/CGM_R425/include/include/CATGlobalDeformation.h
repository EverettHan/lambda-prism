// COPYRIGHT DASSAULT SYSTEMES 1997 
//==========================================================================
//
// CATGlobalDeformation:
// Interface class of the Global Deformation  Operator.
//
//==========================================================================
//
// Usage notes:
// This class can be used as is for simple Deformation or derived
// in order to implement specific algorithm or capabilities.
//
//========================================================================== 
// July. 97     Creation                       Daniels
//========================================================================== 

#ifndef CATGlobalDeformation_H
#define CATGlobalDeformation_H

#include "CATGMOperatorsInterfaces.h"


#include "CATPGMCreateGlobalDeformation.h"
#include "CATMathDef.h"
#include "CATCGMVirtual.h"

//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATGlobalDeformation : public CATCGMVirtual
{
  public :

    virtual ~CATGlobalDeformation();
    virtual void Run()=0;
//
//
//  Get logical result  
// 
    virtual CATLONG32 GetDiagnostic() =0;
};

#endif
