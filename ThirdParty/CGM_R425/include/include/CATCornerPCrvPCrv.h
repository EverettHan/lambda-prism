// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATCornerPCrvPCrv :
// Interface class for operator of corner between two PCurves
//
//=============================================================================
//
// Usage Notes:
//
//=============================================================================
// May. 97    Creation          
// 28/08/02 ALV Creation de la methode GetConfusion(). 
// 05/06/07 GPV Creation de la methode NoCurveLengthCheckForCompleteMode()  
// 05/07/07 GPV Creation de la methode SetLimits2() 
//=============================================================================
#ifndef CATCornerPCrvPCrv_h
#define CATCornerPCrvPCrv_h

#include "CATMathDef.h"
#include "CATCreateCornerPCrvPCrv.h"
#include "CATCGMOperator.h"
#include "Y30C1XMM.h"

class CATCircle;
class CATPCircle;
class CATPointOnCurve;
class CATPCurve;
class CATGeoFactory ;
class CATPointOnSurface;
class CATCrvLimits;

class ExportedByY30C1XMM CATCornerPCrvPCrv : public CATCGMOperator
{
  CATCGMVirtualDeclareClass(CATCornerPCrvPCrv);
 public:

   //-----------------------------------------------------------------------
   //- Virtual destructor
   //-----------------------------------------------------------------------

   virtual ~CATCornerPCrvPCrv () ;
   CATCornerPCrvPCrv (CATGeoFactory * factory) ;


   //-----------------------------------------------------------------------
   //- Public Interface Methods
   //-----------------------------------------------------------------------

   // Running the operator
   virtual int Run () = 0 ;

   // Number of solutions
   virtual CATLONG32 GetNumberOfCorners () const = 0 ;

   // Iterators
   virtual void BeginningCorner () = 0 ;
   virtual CATBoolean NextCorner () = 0 ;

   // Methods which can be used after each NextCorner () call
   virtual CATPointOnCurve *GetPointOnPCurve (const CATPCurve *PCurve) const = 0 ; 
   virtual CATPCircle *GetCircle () const =0;
   virtual CATCircle *Get3DCircle () const =0;

   // Methods to set limits on the PCurve(s)
   virtual void SetLimits (const CATPCurve *PCurve, const CATCrvLimits &CurveLimits) = 0; 
   virtual void SetLimits2 (const CATCrvLimits &CurveLimits1, const CATCrvLimits &CurveLimits2) = 0; 

   // Confusion for intersection between the parallels.
   virtual CATBoolean GetConfusion () = 0;

   // Method to disable curve length check when creating the PCircle (corner in complete mode ONLY)   
   virtual void SetNoCurveLengthCheckForCompleteMode() = 0;
}; 
#endif

