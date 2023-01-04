// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
//
// CATExtractNormalAlongDir :
// Interface class for an operator that computes along a PCurve all the normal to the surface 
// which are perpendicular to a given direction
//
//=============================================================================
//
// Usage Notes:
//
//=============================================================================
// Mai 03    Creation                      FDS
//=============================================================================
#ifndef CATExtractNormalAlongDir_h
#define CATExtractNormalAlongDir_h

#include "CATMathDef.h"
#include "CreateTangentAlongDir.h"
#include "CATCGMOperator.h"
#include "Y30C3XGG.h"

class CATPointOnCurve;
class CATPCurve;
class CATGeoFactory ;
class CATPointOnSurface;
class CATCrvLimits;
class CATMathDirection;

class ExportedByY30C3XGG CATExtractNormalAlongDir : public CATCGMOperator
{
 public:
   //-----------------------------------------------------------------------
   //- Constructor
   //-----------------------------------------------------------------------
   CATExtractNormalAlongDir (CATGeoFactory * factory) ;

   //-----------------------------------------------------------------------
   //- Virtual destructor
   //-----------------------------------------------------------------------
   virtual ~CATExtractNormalAlongDir () ;

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

