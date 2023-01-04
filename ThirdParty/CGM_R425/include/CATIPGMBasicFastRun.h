#ifndef CATIPGMBasicFastRun_h_
#define CATIPGMBasicFastRun_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATContextForFastRun;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMBasicFastRun;

class ExportedByCATGMOperatorsInterfaces CATIPGMBasicFastRun: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMBasicFastRun();

  virtual void SetContext(CATContextForFastRun *ipContext) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMBasicFastRun(); // -> delete can't be called
};

/**
 * @return [out, delete]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMBasicFastRun *CATPGMCreateBasicFastRun(
  CATGeoFactory *ipContainer,
  CATTopData *ipData,
  CATError **iopError);

ExportedByCATGMOperatorsInterfaces CATIPGMBasicFastRun *CATPGMCreateBasicFastRun(
  CATGeoFactory *ipContainer,
  CATTopData *ipData,
  CATContextForFastRun *ipContext,
  CATError **iopError);

#endif /* CATIPGMBasicFastRun_h_ */
