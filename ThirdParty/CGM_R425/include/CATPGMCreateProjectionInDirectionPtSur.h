#ifndef CATPGMCreateProjectionInDirectionPtSur_h_
#define CATPGMCreateProjectionInDirectionPtSur_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATSkillValue.h"

class CATIPGMProjectionInDirectionPtSur;
class CATGeoFactory;
class CATMathVector;
class CATMathSetOfPoints;
class CATSurface;

//
/**
* @deprecated V5R13 CATPGMCreateProjectionInDirectionPtSur
* @return [out, IUnknown#Release]
*/
ExportedByCATGMModelInterfaces CATIPGMProjectionInDirectionPtSur *CATPGMCreateProjectionInDirectionPtSur(
  CATGeoFactory *iFactory,
  const CATMathVector *iDir,
  const CATMathSetOfPoints *iSet,
  const CATSurface *isurface,
  CATSkillValue iMode = BASIC);

#endif /* CATPGMCreateProjectionInDirectionPtSur_h_ */
