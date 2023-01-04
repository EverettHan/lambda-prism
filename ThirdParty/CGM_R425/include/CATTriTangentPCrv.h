// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CATTriTangentPCrv :
// Interface class for operator of TriTangent between 3 PCurves
// These PCurves must have the same support
//
//=============================================================================
//
// Usage Notes:
//
//=============================================================================
// Mar 99    Creation                      T. Phung
//=============================================================================
#ifndef CATTriTangentPCrv_h
#define CATTriTangentPCrv_h

#include "CATMathDef.h"
#include "CreateTriTangentPCrv.h"
#include "CATCreateTriTangentPCrv.h"
#include "CATCGMOperator.h"
#include "Y30C1XMM.h"

class CATCircle;
class CATPCircle;
class CATPointOnCurve;
class CATPCurve;
class CATGeoFactory ;
class CATPointOnSurface;
class CATCrvLimits;
class CATCrvParam;

class ExportedByY30C1XMM CATTriTangentPCrv : public CATCGMOperator
{
  CATCGMVirtualDeclareClass(CATTriTangentPCrv);
 public:
   //-----------------------------------------------------------------------
   //- Constructor
   //-----------------------------------------------------------------------
   CATTriTangentPCrv (CATGeoFactory * factory) ;

   //-----------------------------------------------------------------------
   //- Virtual destructor
   //-----------------------------------------------------------------------
   virtual ~CATTriTangentPCrv () ;

   //-----------------------------------------------------------------------
   //- Public Interface Methods
   //-----------------------------------------------------------------------
   // Setting Limits
   virtual void SetLimits (const CATPCurve *PCurve, 
			   const CATCrvLimits &CurveLimits) = 0; 
   // Setting RadiusDomain
   virtual void SetRadiusDomain (double iMinRadius,
				 double iMaxRadius) = 0; 
  
   // Running the operator
   virtual int Run () = 0 ;

   // Number of solutions
   virtual CATLONG32 GetNumberOfPCircles () const = 0 ;

   // Iterators
   virtual void BeginningPCircle () = 0 ;
   virtual CATBoolean NextPCircle () = 0 ;

   // Methods which can be used after each NextPCircle () call
   virtual CATPointOnCurve *GetPointOnPCurve (const CATPCurve *PCurve) const = 0 ; 
   virtual void GetCrvParam (const CATPCurve * iPCurve, CATCrvParam & oParam) const = 0;
   virtual CATPCircle *GetPCircle  () const =0;
}; 
#endif

