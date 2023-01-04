#ifndef CATCreateComputeUVTolerance_H
#define CATCreateComputeUVTolerance_H

#include "ExportedByGeometricObjects.h"

class CATComputeUVTolerance;
class CATGeoFactory;
class CATSurface;
class CATSoftwareConfiguration;
class CATSurParam;

/**
* @nodoc
*/
ExportedByGeometricObjects
CATComputeUVTolerance * CATCreateComputeUVTolerance(      CATGeoFactory            * iFactory,
                                                          CATSoftwareConfiguration * iConfig,
                                                    const CATSurface               * iSurface,
                                                    const CATSurParam              & iSurParam,
                                                    const double                     i3DTolerance);

#endif





