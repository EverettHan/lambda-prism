#ifndef CATPGMCreateTriTangentPCrv_h_
#define CATPGMCreateTriTangentPCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATSkillValue.h"
#include "CATDataType.h"

class CATGeoFactory;
class CATPCurve;
class CATSoftwareConfiguration;
class CATIPGMTriTangentPCrv;

// Do use
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMTriTangentPCrv *CATPGMCreateTriTangentPCrv(
  CATGeoFactory *Factory,
  CATSoftwareConfiguration *iConfig,
  CATPCurve *PCurve1,
  CATLONG32 iSide1,
  CATPCurve *PCurve2,
  CATLONG32 iSide2,
  CATPCurve *PCurve3,
  CATLONG32 iSide3,
  CATSkillValue iMode = BASIC);

#endif /* CATPGMCreateTriTangentPCrv_h_ */
