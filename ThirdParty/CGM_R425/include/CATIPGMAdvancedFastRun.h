#ifndef CATIPGMAdvancedFastRun_h_
#define CATIPGMAdvancedFastRun_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMBasicFastRun.h"

class CATBody;
class CATContextForFastRun;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMAdvancedFastRun;

class ExportedByCATGMOperatorsInterfaces CATIPGMAdvancedFastRun: public CATIPGMBasicFastRun
{
public:
  /**
   * Constructor
   */
  CATIPGMAdvancedFastRun();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMAdvancedFastRun(); // -> delete can't be called
};

/**
 * @return [out, delete]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMAdvancedFastRun *CATPGMCreateAdvancedFastRun(
  CATGeoFactory *ipContainer,
  CATTopData *ipData,
  CATError **iopError);

ExportedByCATGMOperatorsInterfaces CATIPGMAdvancedFastRun *CATPGMCreateAdvancedFastRun(
  CATGeoFactory *ipContainer,
  CATTopData *ipData,
  CATContextForFastRun *ipContext,
  CATError **iopError);

#endif /* CATIPGMAdvancedFastRun_h_ */
