// COPYRIGHT DASSAULT SYSTEMES 1997
//=============================================================================
//
// CATComputeUVTolerance :
// Class for computing a UV radius such that the PCircle of this radius at a
// given point on the surface contains the 3D Circle of a given 3D radius 
//
//=============================================================================
// Usage notes:
//
//=============================================================================
//   /09/98      Creation (X. Gourdon)
// 21/11/19 Q48  Migration to use const surface
//=============================================================================

#ifndef CATComputeUVTolerance_H
#define CATComputeUVTolerance_H

#include "ExportedByGeometricObjects.h"

#include "CATSurParam.h"
#include "CATMathDef.h"
#include "CATCGMVirtual.h"

#include "CATCreateComputeUVTolerance.h"

class CATSurface;
class CATGeoFactory;
class CATSurLimits;
class CATSoftwareConfiguration;

class ExportedByGeometricObjects CATComputeUVTolerance   : public CATCGMVirtual
{

public :

  /**
  * @nodoc
  */
  CATComputeUVTolerance(      CATGeoFactory            * iFactory,
                              CATSoftwareConfiguration * iConfig,
                        const CATSurface               * iSurface,
                        const CATSurParam              & iSurParam,
                        const double                     i3DTolerance);
  /**
  * @nodoc
  */
  ~CATComputeUVTolerance();

  /**
  * @nodoc
  */
  double GetUVTolerance();

  /**
  * @nodoc
  */
  CATBoolean IsAPole();

  /**
  * @nodoc
  */
  // When distorsion is too large, it means that converting the 3D tolerance 
  // into a 2D tolerance that includes the 3D tolerance is too dangerous. In other words, the
  // 2D tolerance zone is too large compared to the 3D zone.
  // PLEASE NOTE : Result is significant only with a CGMLevel >= ComputeUVTolerance_NewRun
  CATBoolean IsDistorsionTooLarge();

  /**
  * @nodoc
  */
  void Run();

  /**
  * @nodoc
  */
  void SetParameters (const CATSurface * iSurface, const CATSurParam & iSurParam);

  /**
  * @nodoc
  */
  static void CATGetUVTolerance (      CATSoftwareConfiguration * iConfig,
                                 const CATSurface               * iSurface,
                                 const CATSurParam              & iSurParam,
                                 const double                   & i3DTol,
                                       double                   & oUVTolerance,
                                       CATBoolean               & oIsAPole,
                                       CATBoolean               & oDistorsionTooLarge);

private :

  CATSoftwareConfiguration *_Config;
  CATGeoFactory * _Factory;
  const CATSurface * _Surface;
  CATSurParam _SurParam;
  double _3DTol, _UVTolerance;
  CATBoolean _IsAPole, _DistorsionTooLarge;

  static void RunOldStatic ( const short         iCGMLevel,
                             const double      & i3DTol,
                             const CATSurParam & iSurParam,
                             const CATSurface  * iSurface,
                                   double        & oUVTolerance,
                                   CATBoolean    & oIsAPole,
                                   CATBoolean    & oDistorsionTooLarge);

};

/**
* @nodoc
*/
// On a given surface, permits to know if two SurLimits can intersect at a given 3D tolerance.
ExportedByGeometricObjects CATBoolean IsUVIntersectingAt3DTol(      CATSoftwareConfiguration * iConfig, 
                                                              const CATSurface               * iSurface,
                                                              const CATSurLimits             & iSurLim1,
                                                              const CATSurLimits             & iSurLim2,
                                                              const double                     i3DTol);

#endif
