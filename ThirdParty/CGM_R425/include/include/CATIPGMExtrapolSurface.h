#ifndef CATIPGMExtrapolSurface_h_
#define CATIPGMExtrapolSurface_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"
#include "CATExtrapolSurfaceSide.h"
#include "CATSkillValue.h"
#include "CATExtrapolVectFormEnum.h"

class CATEdgeCurve;
class CATEdgeCurveTransientExtrapolManager;
class CATGeoFactory;
class CATPCurve;
class CATSoftwareConfiguration;
class CATSurface;
class CATSurParam;
class CATMathVector2D;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMExtrapolSurface;

class ExportedByCATGMModelInterfaces CATIPGMExtrapolSurface: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMExtrapolSurface();

  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------
  // Returns extrapolated (or created) surface. Result can be the surface to
  // extrapolate itself (if it was extended, or if it is closed), or a newly
  // created surface.
  // 
  // Also returns parameter that matches iStart on the extrapolated surface.  
  // There are 3 cases :
  //    - surface was extended : then this parameter is the same as iStart in
  //      the constructor (same pointer).
  //    - surface is closed, and the extrapolation passed the closure. Then
  //      this parameter is the match of iStart on the other side of the sur-
  //      face closure
  //    - a new surface was created. Then this parameter is the match of iStart
  //      on the new surface
  // Surface side (0 to 8) are also provided as an output to be more explicit.
  //-----------------------------------------------------------------------
  virtual CATSurface *GetResult(CATSurParam **oNewParam) = 0;

  // Check for an existing result with the same inputs
  //-----------------------------------------------------------------------
  virtual CATSurface *CheckForExistingResult(
    CATSurface *iSurfaceToExtrapolate,
    CATExtrapolSurfaceSide iSurfaceSide) = 0;

  // Stores extrapolated surface as an attribute on the surface itself.
  //-----------------------------------------------------------------------
  virtual void StoreAsExistingResult(
    CATSurface *iSurfaceToExtrapolate,
    CATSurface *iExtrapolatedSurface,
    CATExtrapolSurfaceSide iSurfaceSide) = 0;

  // Static function to obtain the parameter-space value of the extrapolation length in either the U- or V-parameter direction. 
  static double GetExtrapolParamLength(
    CATSoftwareConfiguration * const iConfig,
    const CATTolerance &iTolObject,
    const CATSurface * const iSurface,
    const CATSurParam &iStartParam,
    const CATBoolean iIsParamDirU,
    const double iExtrapol3dLength);

  // Different methods for different kinds of surfaces
  //-----------------------------------------------------------------------
  virtual void RunOnPlane() = 0;

  virtual void RunOnCylinder() = 0;

  virtual void RunOnNurbsSurface() = 0;

  virtual void RunOnSweepSurface() = 0;

  virtual void RunOnConnect() = 0;

  virtual void RunOnGenericFillet() = 0;

  virtual void RunOnDraft() = 0;

  virtual void RunOnTabCylinder() = 0;

  virtual void RunOnRevolSurface() = 0;

  virtual void RunOnOffsetSurface() = 0;

  virtual void RunOnDirectionalSurface() = 0;

  virtual void RunOnSpecSurface() = 0;

  virtual void RunOnSubdivSurface() = 0;

  virtual void GenerateLongerSurface() = 0;

  virtual void GetOtherSurfaceEnd() = 0;

  virtual void RunOnOffsetWithRepGenericFillet() = 0;

  virtual short NeedsExtrapolationOnSide(CATExtrapolSurfaceSide iSide) = 0;

  // ... etc
  // Allows large gap in extrapolation of the edge curve underlying a bisector
  // surface. The larger gap allowed is an internal tolerance of the factory.
  virtual void AllowLargeGapInBisector(CATEdgeCurveTransientExtrapolManager *ECTEMan) = 0;

  //-----------------------------------------------------------------------
  //- Gestion timer 
  //-----------------------------------------------------------------------  
  virtual CATGeoOpTimer *GetTimer() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMExtrapolSurface(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMExtrapolSurface *CATPGMCreateExtrapolation(
  CATGeoFactory *iFactory,
  CATSurface *iSurfaceToExtrapolate,
  CATSurParam *iStart,
  CATExtrapolSurfaceSide iSurfaceSide,
  const CATMathVector2D &iVectorEstimation,
  short iAllowSurfaceCreation = 1,
  CATSkillValue iMode = ADVANCED,
  CATSoftwareConfiguration *iConfig = 0,
  const CATExtrapolVectFormEnum iVectorEstimationForm = CATExtrapolVectForm_Unknown);

#endif /* CATIPGMExtrapolSurface_h_ */
