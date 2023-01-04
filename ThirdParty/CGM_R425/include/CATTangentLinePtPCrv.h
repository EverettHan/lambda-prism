// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CATTangentLinePtPCrv :
// Interface class for operator of TangentLine between a Point on Surface and  
// PCurve
//
//=============================================================================
//
// Usage Notes:
//
//=============================================================================
// Mar 99    Creation                      T. Phung
// Aout 99   Modification                  PTO
//=============================================================================
#ifndef CATTangentLinePtPCrv_h
#define CATTangentLinePtPCrv_h

#include "CATMathDef.h"
#include "CreateTangentLinePtPCrv.h"
#include "CATCreateTangentLinePtPCrv.h"
#include "CATCGMOperator.h"
#include "Y30C1XMM.h"

class CATLine;
class CATPLine;
class CATPointOnSurface;
class CATPointOnCurve; 
class CATPCurve;
class CATGeoFactory ;
class CATPointOnSurface;
class CATCrvLimits;

class ExportedByY30C1XMM CATTangentLinePtPCrv : public CATCGMOperator
{
  CATCGMVirtualDeclareClass(CATTangentLinePtPCrv);
 public:
   //-----------------------------------------------------------------------
   //- Constructor
   //-----------------------------------------------------------------------
   CATTangentLinePtPCrv (CATGeoFactory     * factory) ;

   //-----------------------------------------------------------------------
   //- Virtual destructor
   //-----------------------------------------------------------------------
   virtual ~CATTangentLinePtPCrv () ;

   //-----------------------------------------------------------------------
   //- Public Interface Methods
   //-----------------------------------------------------------------------
   // Running the operator
   virtual int Run () = 0 ;

   // Detects 1 if we are in a case of singularity (no treatment for the moment in these cases)
   virtual short DetectsSingularities() const = 0;

   // Number of solutions
   virtual CATLONG32 GetNumberOfTangentLines () const = 0 ;

   // Iterators
   virtual void BeginningTangentLine () = 0 ;
   virtual CATBoolean NextTangentLine () = 0 ;

   // Methods which can be used after each NextTangentLine () call
   // oIsSingular = 1 if tangent computed on the current point is null
   // oIsConfusedPoint = 1 if you have only one point to compute the tangent (Point3D and CurrentPoint3D are confused)
   virtual CATPointOnCurve *GetPointOnPCurve (short &oIsSingular,
					                                    short &oIsConfusedPoint) const = 0 ; 
   virtual CATPLine *GetPLine () const =0;
   virtual CATLine  *Get3DLine () const =0;

  // Set Methods (use Run method after Set methods call)
   // Methods to change the PCurve
   virtual void SetPCurve(const CATPCurve *iPCurve) =0;
   // Methods to change the PointOnSurface
   virtual void SetPointOnSurface(const CATPointOnSurface *iPointOnSurface) =0;
   // Method to specify a CrvLimits on the PCurve 
   virtual void SetLimits (const CATCrvLimits &iCurveLimits) = 0; 
}; 
#endif

