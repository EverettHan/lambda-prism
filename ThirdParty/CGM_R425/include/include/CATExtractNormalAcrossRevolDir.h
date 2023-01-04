// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CATExtractNormalAcrossRevolDir : Interface class for an operator that computes along a PCurve
// all the normal of a surface which are perpendicular to the local revol direction
//
//=============================================================================
//
// Usage Notes:
//
//=============================================================================
// Mai 03    Creation                      FDS
//=============================================================================
#ifndef CATExtractNormalAcrossRevolDir_h
#define CATExtractNormalAcrossRevolDir_h

#include "CATMathDef.h"
#include "CreateTangentAcrossRevolDir.h"
#include "CATCGMOperator.h"
#include "Y30C3XGG.h"

class CATPointOnCurve;
class CATPCurve;
class CATGeoFactory ;
class CATPointOnSurface;
class CATCrvLimits;
class CATMathDirection;

class ExportedByY30C3XGG CATExtractNormalAcrossRevolDir : public CATCGMOperator
{
 public:
   //-----------------------------------------------------------------------
   //- Constructor
   //-----------------------------------------------------------------------
   CATExtractNormalAcrossRevolDir (CATGeoFactory * factory) ;

   //-----------------------------------------------------------------------
   //- Virtual destructor
   //-----------------------------------------------------------------------
   virtual ~CATExtractNormalAcrossRevolDir () ;

   //-----------------------------------------------------------------------
   //- Public Interface Methods
   //-----------------------------------------------------------------------
  // Setting methods
   virtual void SetAngularTol(const double iAngleInRadians) = 0 ;

   // Running the operator
   virtual int Run () = 0 ;

   // Number of solutions
   virtual CATLONG32 GetNumberOfPoints() const = 0 ;
   virtual CATLONG32 GetNumberOfCurves() const = 0 ;

   
   // Read the Point solutions
   virtual void BeginningPoint () = 0 ;
   virtual CATBoolean NextPoint () = 0 ;
   virtual CATPointOnCurve *GetPointOnCurve () const = 0;

   // Read the Part of the Curve solutions
   virtual void BeginningCurve () = 0 ;
   virtual CATBoolean NextCurve () = 0 ;
   virtual void GetPartOfCurves (CATCrvLimits &oLimits) const = 0;

}; 
#endif

