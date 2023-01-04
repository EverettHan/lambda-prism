// COPYRIGHT DASSAULT SYSTEMES 1997 
//==========================================================================
//
// CATGeodesic:
// Interface class of the Geodesic Operator.
//
//==========================================================================
//
// Usage notes:
//
//========================================================================== 
// October 97     Creation                       GDR
//========================================================================== 
//
#ifndef CATGeodesicOperator_H
#define CATGeodesicOperator_H
//
#include "FrFGeodesic.h"
#include "CreateGeodesicOperator.h"
#include "CATCGMVirtual.h"
//
#include "CATListOfCATPCurves.h"
//
//-----------------------------------------------------------------------------
class ExportedByFrFGeodesic CATGeodesicOperator : public CATCGMVirtual
{
  public :

    virtual                       ~CATGeodesicOperator()              ;
    virtual void                  Run()                             =0;
//
    virtual CATLISTP(CATPCurve)   GetGeodesic()                     =0;
};
#endif
