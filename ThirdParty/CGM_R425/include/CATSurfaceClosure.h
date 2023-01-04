// COPYRIGHT DASSAULT SYSTEMES 1999
//=============================================================================
// Aug 99 Creation                       XGN
//
//=============================================================================
// Usage notes:
//  This operator is used to get the closure information of a surface along a 
//  given Isopar direction
//=============================================================================
#ifndef CATSurfaceClosure_H
#define CATSurfaceClosure_H

#include "Y30A3HGG.h"

#include "CATCGMOperator.h"

#include "CATMathDef.h"

#include "CATSurLimits.h"
#include "CATIsoParameter.h"

class CATGeoFactory;
class CATSurface;
class CATSurParamReport;
class CATSoftwareConfiguration;

class ExportedByY30A3HGG CATSurfaceClosure : public CATCGMOperator
{
  CATCGMVirtualDeclareClass(CATSurfaceClosure);
 public:
  //-----------------------------------------------------------------------
  //- Object management
  //-----------------------------------------------------------------------
  //Use the constructor with CATSoftwareConfiguration
  CATSurfaceClosure (CATGeoFactory *iFactory,
                     CATSurface  *iSurface);

  CATSurfaceClosure (CATGeoFactory *iFactory,CATSoftwareConfiguration * iConfig,
                     CATSurface  *iSurface);

  ~CATSurfaceClosure();
  //-----------------------------------------------------------------------
  //- Settings methods
  //-----------------------------------------------------------------------
  
  // Default is current limits
  void SetLimits(const CATSurLimits & iLimits);
  // No default
  void SetIsoparType(const CATIsoParameter iIsoType); // U or V

  //-----------------------------------------------------------------------
  //- Get methods
  //-----------------------------------------------------------------------

  CATBoolean IsClosedG0(); 
  CATBoolean IsClosedG1(); 
  //  CATBoolean IsClosedG2(); Not yet implemented

  // Return an object which permits to report surface parameter between one isopar of
  // the close and the other.
  // WARNING : the returned pointer is owned by the caller and must be deleted by the caller.
  // Note (Implicit specification) :
  // the returned CATSurParamReport has direct report from isopar min to isopar max.
  CATSurParamReport * GetParamReport();

  //-----------------------------------------------------------------------
  //- Running the operator
  //-----------------------------------------------------------------------

  
  int Run();

protected:
  CATBoolean ComputeG1Closure();

protected:
  CATSurface * _Surface;
  CATSurLimits _SurLimits;
  CATIsoParameter _IsoType;
  CATSoftwareConfiguration * _Config;

  CATLONG32 _IsClosedG0, _IsClosedG1, _IsClosedG2; // =-1 if not evaluated
};

/**
 * return [out, delete]
 */
ExportedByY30A3HGG CATSurfaceClosure *CATCreateSurfaceClosure(CATGeoFactory *iFactory,CATSoftwareConfiguration * iConfig,
  CATSurface  *iSurface);

#endif
