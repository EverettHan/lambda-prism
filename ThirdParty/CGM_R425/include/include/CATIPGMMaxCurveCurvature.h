#ifndef CATIPGMMaxCurveCurvature_h_
#define CATIPGMMaxCurveCurvature_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"

class CATCrvLimits;
class CATCrvParam;
class CATCurve;
class CATPCurve;
class CATSoftwareConfiguration;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMMaxCurveCurvature;

class ExportedByCATGMModelInterfaces CATIPGMMaxCurveCurvature: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMMaxCurveCurvature();

  /**
 *@nodoc
 */
  virtual double GetMaxCurvature() = 0;

  virtual void GetCrvParam(CATCrvParam &oParam) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMMaxCurveCurvature(); // -> delete can't be called
};

/**
 * @nodoc
 * @param iFactory
 * @param iSoftwareConfiguration
 * @param iCurve
 * @param iLimits
 * Limits on iCurve that are useful for the application.
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMMaxCurveCurvature *CATPGMCreateMaxCurveCurvature(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iSoftwareConfiguration,
  CATCurve *iCurve,
  const CATCrvLimits &iLimits);

/**
 * @nodoc
 * @param iFactory
 * @param iSoftwareConfiguration
 * @param iPCurve
 * @param iLimits
 * Limits on iPCurve that are useful for the application.
 * @param iOrientation
 * Orientation in which you want eval MaxCurvature on Surface.
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMMaxCurveCurvature *CATPGMCreateMaxCurveCurvature(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iSoftwareConfiguration,
  CATPCurve *iPCurve,
  const CATCrvLimits &iLimits,
  short iOrientation = 0);

#endif /* CATIPGMMaxCurveCurvature_h_ */
