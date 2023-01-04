#ifndef CATPGMCreateTangentAlongDir_h_
#define CATPGMCreateTangentAlongDir_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATMathDirection.h"
#include "CATSkillValue.h"

class CATCurve;
class CATIPGMExtractTangentAlongDir;
class CATGeoFactory;
class CATPointOnCurve;

/**
* @deprecated V5R13 CATPGMCreateTangentAlongDir 
* @return [out, IUnknown#Release]
*/
ExportedByCATGMModelInterfaces CATIPGMExtractTangentAlongDir *CATPGMCreateTangentAlongDir(
  CATGeoFactory *Factory,
  CATCurve *Curve,
  CATMathDirection &Direction,
  CATPointOnCurve *StartPoc,
  CATPointOnCurve *EndPoc,
  CATSkillValue iMode = BASIC);

#endif /* CATPGMCreateTangentAlongDir_h_ */
