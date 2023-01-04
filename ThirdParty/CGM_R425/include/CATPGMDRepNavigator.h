#ifndef CATPGMDRepNavigator_h_
#define CATPGMDRepNavigator_h_

// COPYRIGHT DASSAULT SYSTEMES 2012

#include "CATGMModelInterfaces.h"

class CATDRepNavigatorInterface;
class CATSoftwareConfiguration;
class CATBody;

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATDRepNavigatorInterface *CATPGMCreateDRepNavigatorInterface(
  CATSoftwareConfiguration *iSoftConf,
  CATBody *iBody);

#endif /* CATPGMDRepNavigator_h_ */
