// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CATExtractTangentAcrossRevolDir :
// Interface class for an operator that computes all the tangents of a curve 
// parallel to a direction
//
//=============================================================================
//
// Usage Notes:
//
//=============================================================================
// Mar 00    Creation                      BHE
//=============================================================================
#ifndef CATExtractTangentAcrossRevolDir_h
#define CATExtractTangentAcrossRevolDir_h

#include "CATMathDef.h"
#include "CreateTangentAcrossRevolDir.h"
#include "CATCGMOperator.h"
#include "Y30C3XGG.h"

class CATPointOnCurve;
class CATCurve;
class CATGeoFactory ;
class CATPointOnSurface;
class CATCrvLimits;
class CATMathDirection;

class ExportedByY30C3XGG CATExtractTangentAcrossRevolDir : public CATCGMOperator
{
 public:
   //-----------------------------------------------------------------------
   //- Constructor
   //-----------------------------------------------------------------------
   CATExtractTangentAcrossRevolDir (CATGeoFactory * factory) ;

   //-----------------------------------------------------------------------
   //- Virtual destructor
   //-----------------------------------------------------------------------
   virtual ~CATExtractTangentAcrossRevolDir () ;

   //-----------------------------------------------------------------------
   //- Public Interface Methods
   //-----------------------------------------------------------------------
  // Setting methods
   virtual void SetCurve (const CATCurve *iCurve) = 0;
   virtual void SetLimits(const CATPointOnCurve *iStartPoc, const CATPointOnCurve *iEndPoc) = 0;
   virtual void SetDirection(const CATMathDirection &iDirection) = 0;
   virtual void SetAngularTol(const double iAngleInRadians) = 0 ;

   // Running the operator
   virtual int Run () = 0 ;

   // Number of solutions
   virtual CATLONG32 GetNumberOfPoints() const = 0 ;
//   virtual CATLONG32 GetNumberOfCurves() const = 0 ;

   
   // Read the Point solutions
   virtual void BeginningPoint () = 0 ;
   virtual CATBoolean NextPoint () = 0 ;
   virtual CATPointOnCurve *GetPointOnCurve () const = 0;

   // Read the Part of the Curve solutions
//   virtual void BeginningCurve () = 0 ;
//   virtual CATBoolean NextCurve () = 0 ;
//   virtual void GetPartOfCurves (CATCrvLimits &oLimits) const = 0;

}; 
#endif

