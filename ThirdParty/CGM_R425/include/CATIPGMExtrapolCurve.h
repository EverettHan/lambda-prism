#ifndef CATIPGMExtrapolCurve_h_
#define CATIPGMExtrapolCurve_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"
#include "CATSkillValue.h"
#include "CATCrvSide.h"

class CATCurve;
class CATEdgeCurveTransientExtrapolManager;
class CATGeoFactory;
class CATPCurve;
class CATSoftwareConfiguration;
class CATSurLimits;
class CATSurface;
class CATCrvParam;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMExtrapolCurve;

class ExportedByCATGMModelInterfaces CATIPGMExtrapolCurve: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMExtrapolCurve();

  //-----------------------------------------------------------------------
  //- Public Methods
  //-----------------------------------------------------------------------
  // Returns extrapolated (or created) curve. Result can be the surface to
  // extrapolate itself (if it was extended, or if it is closed), or a newly
  // created curve.
  virtual CATCurve *GetResult() = 0;

  // Allows large gap in edge curve extrapolation. The larger gap allowed is
  // an internal tolerance of the factory.
  virtual void AllowLargeGapInEC(CATEdgeCurveTransientExtrapolManager *Manager) = 0;

  // Triggers the extrapolation
  //-----------------------------------------------------------------------

  //-----------------------------------------------------------------------
  //- Gestion timer 
  //-----------------------------------------------------------------------  
  virtual CATGeoOpTimer *GetTimer() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMExtrapolCurve(); // -> delete can't be called
};

//mode ADVANCED systematique.
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMExtrapolCurve *CATPGMCreateExtrapolation(
  CATGeoFactory *iFactory,
  CATCurve *iCurveToExtrapolate,
  CATCrvParam &iStart,
  const double iLengthEstimation,
  CATCrvSide iExtrapolDirection,
  CATSoftwareConfiguration *iConfig);

//Ne plus utiliser.
//Ne plus utiliser.
//Ne plus utiliser.
//Ne plus utiliser.
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMExtrapolCurve *CATPGMCreateExtrapolation(
  CATGeoFactory *iFactory,
  CATCurve *iCurveToExtrapolate,
  const CATCrvParam &iStart,
  const double iLengthEstimation,
  CATSkillValue iMode = BASIC,
  const short iExtrapolDirection = 0,
  CATSoftwareConfiguration *iConfig = 0);

//- iCurveToExtrapolate is the curve to extrapol
//- iStart is the parameter from which we want to extrapol. It should be in the
//  maxlimit of the curve
//- iLengthEstimation is a 3D estimation of the extrapolation length required from iStart
//_ iExtrapolDirection == -1 extrapolation is at the left
//_ iExtrapolDirection ==  1 extrapolation is at the right
//_ iExtrapolDirection ==  0 extrapolation is at the left or right (Test dependant de la position du iStart par rapport
//                                                                  au milieu des Malimits de la Curve) a supprimer des que possible
//----------------------------------------------------------------------------------------------------------------
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMExtrapolCurve *CATPGMCreateExtrapolCurve(
  CATGeoFactory *iFactory,
  CATCurve *iCurveToExtrapolate,
  CATCrvParam &iStart,
  const double iLengthEstimation,
  const short iExtrapolDirection = 0,
  CATSoftwareConfiguration *iConfig = 0);

#endif /* CATIPGMExtrapolCurve_h_ */
