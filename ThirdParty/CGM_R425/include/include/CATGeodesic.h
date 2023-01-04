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
#ifndef CATGeodesic_H
#define CATGeodesic_H
//
#include "FrFGeodesic.h"
#include "CreateGeodesic.h"
//
#include "CATListOfCATPCurves.h"
#include "CATMathSetOfLongs.h"
#include "CATCGMVirtual.h"
//
class CATSurLimits;
class CATSurParam;
class CATMathVector;
//-----------------------------------------------------------------------------
class ExportedByFrFGeodesic CATGeodesic : public CATCGMVirtual
{
  public :

    virtual                       ~CATGeodesic()                          ;
    virtual void                  Run()                                 =0;
//
    virtual void                  SetLimits(CATSurLimits * iLimits)     =0;
//    virtual void                  SetLimits(CATBoolean iclosedBoundary) =0;
//
    virtual void                  GetFinalPoint(CATSurParam &oparam,
						CATMathVector &oTangent,
						CATLength &oLength)     =0;
    
    virtual void                  SetSafeLastStep();
//
  
    virtual CATLISTP(CATPCurve)   GetGeodesic()                         =0;

    virtual CATLISTP(CATPCurve)   GetGeodesicAndDiagnostic(CATMathSetOfLongs & oDiagnostic);
};
#endif
