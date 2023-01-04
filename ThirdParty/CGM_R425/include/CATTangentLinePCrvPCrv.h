// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CATTangentLinePCrvPCrv :
// Interface class for operator of TangentLine between two PCurves
//
//=============================================================================
//
// Usage Notes:
//
//=============================================================================
// Mar 99    Creation                      T. Phung
// Aout 99   Modification                  PTO
//=============================================================================
#ifndef CATTangentLinePCrvPCrv_h
#define CATTangentLinePCrvPCrv_h

#include "CATMathDef.h"
#include "CreateTangentLinePCrvPCrv.h"
#include "CATCreateTangentLinePCrvPCrv.h"
#include "CATGeoOperator.h"
#include "Y30C1XMM.h"

class CATLine;
class CATPLine;
class CATPointOnCurve;
class CATPCurve;
class CATGeoFactory ;
class CATPointOnSurface;
class CATCrvLimits;

class ExportedByY30C1XMM CATTangentLinePCrvPCrv : public CATGeoOperator
{
 public:
   //-----------------------------------------------------------------------
   //- Constructor
   //-----------------------------------------------------------------------
   CATTangentLinePCrvPCrv (CATGeoFactory * factory) ;

   //-----------------------------------------------------------------------
   //- Virtual destructor
   //-----------------------------------------------------------------------
   virtual ~CATTangentLinePCrvPCrv () ;

   //-----------------------------------------------------------------------
   //- Public Interface Methods
   //-----------------------------------------------------------------------
   // Singularities Detection (such singularities are not treated for the moment)
   virtual short DetectsSingularities() const = 0;
  
   // Number of solutions
   virtual CATLONG32 GetNumberOfTangentLines () const = 0 ;

   // Iterators
   virtual void BeginningTangentLine () = 0 ;
   virtual CATBoolean NextTangentLine () = 0 ;

   // Methods which can be used after each NextTangentLine () call
   // oIsSingular = 1 if the tangent computed at current point is null
   // oIsConfusedPoint = 1 if the 3D solution on PCurve1 and the 3D solution on PCurve2 are confused
   virtual CATPointOnCurve *GetPointOnPCurve (const CATPCurve *PCurve, short &oIsSingular, short &oIsConfusedPoint) const = 0 ; 
   virtual CATPLine *GetPLine () const =0;
   virtual CATLine  *Get3DLine () const =0;

   // Setting Limits
   virtual void SetLimits (const CATPCurve *PCurve, const CATCrvLimits &CurveLimits) = 0; 
}; 
#endif

