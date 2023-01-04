#ifndef CATPGMLiveShapeServices_h_
#define CATPGMLiveShapeServices_h_

// COPYRIGHT DASSAULT SYSTEMES 2015

#include "CATGMModelInterfaces.h"
#include "CATBoolean.h"

class CATFace;
class CATGeoFactory;
class CATSoftwareConfiguration;

class ExportedByCATGMModelInterfaces CATPGMLiveShapeServices
{
public:
  static CATBoolean AreVisuallyIdenticalFaces(
    CATFace &iPreviousFace,
    CATFace &iResultFace,
    CATGeoFactory &iFactory,
    CATSoftwareConfiguration *ipConfig);

};

#endif /* CATPGMLiveShapeServices_h_ */
