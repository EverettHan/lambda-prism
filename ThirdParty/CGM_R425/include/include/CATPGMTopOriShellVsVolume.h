#ifndef CATPGMTopOriShellVsVolume_h_
#define CATPGMTopOriShellVsVolume_h_

// COPYRIGHT DASSAULT SYSTEMES 2019

#include "CATGMOperatorsInterfaces.h"
#include "CATTopDefine.h"

class CATGeoFactory;
class CATShell;
class CATSoftwareConfiguration;

ExportedByCATGMOperatorsInterfaces CATOrientation CATPGMTopOriShellVsVolume(
  CATGeoFactory *iFactory,
  CATShell *iShell,
  CATSoftwareConfiguration *iConfig);

#endif /* CATPGMTopOriShellVsVolume_h_ */
