#ifndef CATPGMCreatePowerCloudOfPoints_h_
#define CATPGMCreatePowerCloudOfPoints_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"

class CATPowerCldPolygon;
class CATCloudOfPoints;



ExportedByCATGMOperatorsInterfaces CATPowerCldPolygon *CATPGMCreatePowerCloudOfPoints(
  const CATCloudOfPoints *iCloudOfPts,
  const double iTol);

// ***********************************
// Basics methods to build a Location
// ***********************************
ExportedByCATGMOperatorsInterfaces CATPowerCldPolygon *CATPGMCreatePowerCloudOfPoints(
  const int inbPoints,
  const double *ixyz,
  const double iTol);

#endif /* CATPGMCreatePowerCloudOfPoints_h_ */
