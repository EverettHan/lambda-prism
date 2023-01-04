
// COPYRIGHT DASSAULT SYSTEMES 1997 
//==========================================================================
//
// CATSegmentation:
// Interface class of the Interapproximation Operator for Curve.
//
//==========================================================================
//
// Usage notes:
//
//========================================================================== 
// July. 97     Creation                  Catherine Eymin
//========================================================================== 

#ifndef CATSegmentation_H
#define CATSegmentation_H

#include "CATGMOperatorsInterfaces.h"

#include "CreateSegmentation.h"
#include "CATCGMVirtual.h"
#include "CATPGMCreateSegmentation.h"

class CATCurve;
class CATNurbsCurve;
class CATSoftwareConfiguration;

//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATSegmentation : public CATCGMVirtual
{
  public :

    virtual ~CATSegmentation();

    virtual void Run()=0;
    virtual CATNurbsCurve ** GetResult()=0;
    virtual double GetMaxDistance(CATLONG32 &)=0;
    virtual CATLONG32   GetNbSeg()=0;
    virtual void   ComputeInterpolation()=0;

};

// To create an instance of CATSegmentation: see CATPGMCreateSegmentation.h

#endif

