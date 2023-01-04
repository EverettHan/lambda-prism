#ifndef CATPGMGeoFace_h_
#define CATPGMGeoFace_h_

// COPYRIGHT DASSAULT SYSTEMES 2020

#include "CATGMModelInterfaces.h"

class CATGeoFaceLimitTree;
class CATMathFunctionXY;
class CATIPGMPositionPtLoop;
class Voxel3D;

class ExportedByCATGMModelInterfaces CATPGMGeoFace
{
public:
  /**
   * Constructor
   */
  CATPGMGeoFace();

  /**
   * Destructor
   */
  virtual ~CATPGMGeoFace();

};

#endif /* CATPGMGeoFace_h_ */
