//Utility class to compute the Parameter distortion of a surface.

#ifndef CATDISTORTIONUTILITY_H
#define CATDISTORTIONUTILITY_H

#include "Y3DYNOPE.h"
#include "CATCGMOperator.h"
#include "CATCGMVirtual.h"
#include "CATSurLimits.h"
#include "CATSurParam.h"

class CATSurface;
class CATSoftwareConfiguration;


class ExportedByY3DYNOPE CATDistortionUtility : public CATCGMVirtual
{
public:

  /*typedef*/ // PKC 21/04/2017 useless typedef in C++, compilation warning  
  enum ParamDistortionType { ParamDistortionNotCalculated = 0, SurfacesNotDistorted, SurfacesDistorted };

  static CATBoolean GetParameterDistortion(      CATSoftwareConfiguration *       iConfig,
                                           const CATSurface               * const iSurface,
                                           const CATSurLimits             &       iLimit, 
                                                 double                           ioParamDistortion[], 
                                                 ParamDistortionType      &       ioParamDistortionType,
                                           const CATTolerance             &       iTolObject,
                                           const CATBoolean                       iAllSurfaceTypes = FALSE);

  static CATBoolean GetParameterDistortion(      CATSoftwareConfiguration *       iConfig,
                                           const CATSurface               * const iSurface,
                                           const CATSurLimits             &       iLimit,
                                           const CATSurParam              &       iParam,
                                                 double                           ioParamDistortion[],
                                                 ParamDistortionType      &       ioParamDistortionType,
                                           const CATTolerance             &       iTolObject,
                                           const CATBoolean                       iAllSurfaceTypes = FALSE);

  static void ComputeParameterDistortionOnSurface(const CATSurface   * iSurf,
                                                  const CATSurParam  & iParam,
                                                  const double         iStep,
                                                        double         oDistortion[2],
                                                  const CATSurLimits & iLimits);
private:

  static CATBoolean  CanSurfaceTypeHaveDistortion(CATSoftwareConfiguration * iConfig, const CATSurface * const iSurface);
  static const CATSurface* GetBaseSurface(const CATSurface*);

  static const double DISTORTION_FACTOR_UPPER;
  static const double DISTORTION_FACTOR_LOWER;
};
#endif

