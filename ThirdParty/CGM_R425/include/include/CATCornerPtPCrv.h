// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATCornerPtPCrv :
// Interface class for operator of corner between a Point on Surface and  
// PCurve
//
//=============================================================================
//
// Usage Notes:
//
//=============================================================================
// Sep. 98    Creation                      
// 28/08/02 ALV Creation de la methode GetConfusion(). 
// 17/10/02 ALV Creation de la methode GetCircleTooShort().
//=============================================================================
#ifndef CATCornerPtPCrv_h
#define CATCornerPtPCrv_h

#include "CATMathDef.h"
#include "CATCreateCornerPtPCrv.h"
#include "Y30C1XMM.h"
#include "CATCGMVirtual.h"
#include "CATGeoOperator.h"
class CATCircle;
class CATPCircle;
class CATPointOnCurve;
class CATPCurve;
class CATGeoFactory ;
class CATPointOnSurface;
class CATCrvLimits;

class ExportedByY30C1XMM CATCornerPtPCrv : public CATGeoOperator
{
 public:
   //-----------------------------------------------------------------------
   //- Virtual constructor
   //-----------------------------------------------------------------------

   CATCornerPtPCrv(CATGeoFactory * factory);

   //-----------------------------------------------------------------------
   //- Virtual destructor
   //-----------------------------------------------------------------------

   virtual ~CATCornerPtPCrv () ;


   //-----------------------------------------------------------------------
   //- Public Interface Methods
   //-----------------------------------------------------------------------

   // Running the operator
   virtual int  RunOperator() = 0 ;

   // Number of solutions
   virtual CATLONG32 GetNumberOfCorners () const = 0 ;

   // Iterators
   virtual void BeginningCorner () = 0 ;
   virtual CATBoolean NextCorner () = 0 ;

   // Methods which can be used after each NextCorner () call
   virtual CATPointOnCurve *GetPointOnPCurve (const CATPCurve *PCurve) const = 0 ; 
   virtual CATPCircle *GetCircle () const =0;
   virtual CATCircle *Get3DCircle () const =0;
   virtual void SetLimits (const CATPCurve *PCurve, const CATCrvLimits &CurveLimits) = 0; 

   // Confusion for intersection between the parallels.
   virtual CATBoolean GetConfusion () = 0;

   virtual CATBoolean GetCircleTooShort () = 0;

   virtual void SetNoCurveLengthCheckForCompleteMode () = 0;
}; 
#endif

