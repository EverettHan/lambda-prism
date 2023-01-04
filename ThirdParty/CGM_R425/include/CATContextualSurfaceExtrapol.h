// COPYRIGHT DASSAULT SYSTEMES 2002
//=============================================================================
//
// CATContextualSurfaceExtrapol :
//  Operator to extrapol enought two surfaces in order to make them
//  intersecting. CGM USE ONLY!
//
//=============================================================================
// Usage notes:
//
//=============================================================================
//   /11/02     Creation                          X. Gourdon
// 12/03/20 Q48 Headers etc for math versioning
//=============================================================================

#ifndef CATContextualSurfaceExtrapol_h
#define CATContextualSurfaceExtrapol_h 

// ExportedBy
#include "Y30UIUTI.h"

// Base class
#include "CATGeoOperator.h"

// C++11
#include "CATGeoOpVirtual.h"

#include "CATCreateContextualSurfaceExtrapol.h"

#include "CATMathDef.h"
#include "CATSurLimits.h"
#include "CATMathVector.h"
#include "CATMathBox.h"

class CATGeoFactory;
class CATSurface;
class CATSoftwareConfiguration;

class ExportedByY30UIUTI CATContextualSurfaceExtrapol : public CATGeoOperator
{
  public :
  //
  //-----------------------------------------------------------------------
  //- Constructor-destructor
  //-----------------------------------------------------------------------
  //
  CATContextualSurfaceExtrapol (CATGeoFactory            * iFactory,
                                CATSoftwareConfiguration * iConfig);         

  ~CATContextualSurfaceExtrapol ();
  
  //
  // Launches the operator 
  //
  int RunOperator ();
  
  //
  // Set methods
  //
  // SetDraftNeutralContext : iDraftAngle should be precised in radian
  void SetDraftNeutralContext(      CATSurface    * iNeutral,
                              const CATSurLimits  & iLimitsNeutral,
                                    CATSurface    * iSurfToDraft,
                              const CATSurLimits  & iLimitsSurfToDraft, 
                              const CATMathBox    & iContainingBox,
                              const CATMathVector & iDraftDirection,
                                    double          iDraftAngle);
  //
  // Get methods
  //
  enum CATResultDiagnostic { Success, Failure } ;

  CATContextualSurfaceExtrapol::CATResultDiagnostic GetDiagnostic();
 //
  // Returns the new contextual limits
  //
  void GetLimits (CATSurface * iSurface, CATSurLimits & oSurfContextualLimits);
  

private : 
  void RunOnDraftNeutral();
  CATBoolean IntersectLineSurface(const CATMathPoint & Pt3D,
    const CATMathVector & iVector,
    CATSurface * iSurface,
    const CATMathBox & iBox,
    double & oLength,
    CATSurParam & oSurParam);
  
  //
  //-----------------------------------------------------------------------
  //- Private data
  //-----------------------------------------------------------------------
  //

  // Input data
  CATSoftwareConfiguration * _Configuration;
  CATSurface   *_Surf[2]; 
  CATSurLimits _Limits[2]; 

  enum Context { Unset, DraftNeutral} ;
  CATContextualSurfaceExtrapol::Context _Context;

  CATMathVector _DraftDirection;
  double _DraftAngle;
  CATMathBox _ContainingBox;

  // Output data
  CATContextualSurfaceExtrapol::CATResultDiagnostic _Diagnostic;
  CATSurLimits _ContextualLimits[2];

};
//
// Create and remove 
//
ExportedByY30UIUTI CATContextualSurfaceExtrapol * 
CreateContextualSurfaceExtrapol(CATGeoFactory * iFactory,
                                CATSoftwareConfiguration * iConfig);
ExportedByY30UIUTI void Remove (CATContextualSurfaceExtrapol * iOperator);
#endif







