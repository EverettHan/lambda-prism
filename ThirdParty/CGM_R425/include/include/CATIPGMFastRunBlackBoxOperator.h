#ifndef CATIPGMFastRunBlackBoxOperator_h_
#define CATIPGMFastRunBlackBoxOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATFastRunBlackBoxCheckType.h"

class CATBody;
class CATOperatorContextForFastRun;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMFastRunBlackBoxOperator;

class ExportedByCATGMOperatorsInterfaces CATIPGMFastRunBlackBoxOperator: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMFastRunBlackBoxOperator();

  virtual void SetCheckType(CATFastRunBlackBoxCheckType iType) = 0;

  virtual CATFastRunBlackBoxCheckType GetCheckType() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMFastRunBlackBoxOperator(); // -> delete can't be called
};

/**
 * @return [out, IUnkown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMFastRunBlackBoxOperator *CATPGMCreateFastRunBlackBoxOperator(
  CATGeoFactory *ipContainer,
  CATTopData *ipData,
  CATError **iopError);

ExportedByCATGMOperatorsInterfaces CATIPGMFastRunBlackBoxOperator *CATPGMCreateFastRunBlackBoxOperator(
  CATGeoFactory *ipContainer,
  CATTopData *ipData,
  CATContextForFastRun *ipContext,
  CATError **iopError);

#endif /* CATIPGMFastRunBlackBoxOperator_h_ */
