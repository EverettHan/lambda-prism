#ifndef CATPGMCreateIdentical_h_
#define CATPGMCreateIdentical_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATSkillValue.h"

class CATGeoFactory;
class CATIPGMIdenticalSurSur;
class CATSoftwareConfiguration;
class CATSurface;



/**
 * Creates an operator for testing if two surfaces are identicals
 * @param iMode
 * <dl><dt><tt>BASIC</tt> <dd>the operation is performed at the operator creation
 *     <dt><tt>ADVANCED</tt><dd>otherwise </dl>
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMIdenticalSurSur *CATPGMCreateIdentical(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *Config,
  CATSurface *iSurface1,
  CATSurface *iSurface2,
  CATSkillValue iMode = BASIC);

#endif /* CATPGMCreateIdentical_h_ */
