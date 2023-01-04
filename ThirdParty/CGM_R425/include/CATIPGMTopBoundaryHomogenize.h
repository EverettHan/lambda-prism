#ifndef CATIPGMTopBoundaryHomogenize_h_
#define CATIPGMTopBoundaryHomogenize_h_

// COPYRIGHT DASSAULT SYSTEMES 2013

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopMultiResult.h"

class CATBody;
class CATExtTopBoundaryHomogenize;
class CATGeoFactory;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopBoundaryHomogenize;

class ExportedByCATGMOperatorsInterfaces CATIPGMTopBoundaryHomogenize: public CATIPGMTopMultiResult
{
public:
  /**
   * Constructor
   */
  CATIPGMTopBoundaryHomogenize();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopBoundaryHomogenize(); // -> delete can't be called
};

ExportedByCATGMOperatorsInterfaces CATIPGMTopBoundaryHomogenize *CATPGMCreateTopBoundaryHomogenize(
  CATGeoFactory *ipFactory,
  CATTopData *ipTopdata,
  CATBody *ipGlobalBody,
  const CATLISTP(CATBody) &iBodies,
  double iTol);

#endif /* CATIPGMTopBoundaryHomogenize_h_ */
