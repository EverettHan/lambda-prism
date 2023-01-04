#ifndef CATIPGMSurfacicGeoOpeItfBldr_h
#define CATIPGMSurfacicGeoOpeItfBldr_h

#include "CATGMOperatorsInterfaces.h"
#include "CATBaseUnknown.h"

class CATIPGMGeoFilling;
class CATGeoFactory;
class CATSurface;
class CATMathBeamFE;
class CATPowerCldPolygon;
class CATCloudOfPoints;
class CATIPGMPowerCurveSmooth;
class CATMathSetOfPointsND;
class CATSoftwareConfiguration;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMSurfacicGeoOpeItfBldr;

/**
 * Factory of implementations of CGM interfaces for the framework SurfacicGeoOperators.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMSurfacicGeoOpeItfBldr: public CATBaseUnknown
{
  CATDeclareInterface;
public:

  virtual CATIPGMGeoFilling *CATPGMCreateGeoFilling(
    CATGeoFactory *iFactory,
    CATSurface *iInitialSurface) = 0;

  virtual CATMathBeamFE *CATCGMCreateBeamFE(const int idegree, const int iOrder) = 0;

  virtual CATPowerCldPolygon *CATPGMCreatePowerCloudOfPoints(
    const CATCloudOfPoints *iCloudOfPts,
    const double iTol) = 0;

  virtual CATPowerCldPolygon *CATPGMCreatePowerCloudOfPoints(
    const int inbPoints,
    const double *ixyz,
    const double iTol) = 0;

  virtual CATIPGMPowerCurveSmooth *CATPGMCreatePowerCurveSmoothOp(
    CATGeoFactory *iFactory,
    CATMathSetOfPointsND *iPoints,
    const double iTolerance,
    const int iDegree,
    const int iNbMaxOfArcs,
    CATSoftwareConfiguration *iConfig) = 0;
};

/**
 * Returns the factory of implementations of interfaces for the framework SurfacicGeoOperators.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
CATIPGMSurfacicGeoOpeItfBldr *CATCGMGetSurfacicGeoOpeItfBldr();

#endif /* CATIPGMSurfacicGeoOpeItfBldr_h */
