#ifndef CATIPGMTopAdaptiveClone_h_
#define CATIPGMTopAdaptiveClone_h_

// COPYRIGHT DASSAULT SYSTEMES 2011

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopMultiResult.h"
#include "CATCGMStreamVersion.h"

class CATGeoFactory;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopAdaptiveClone;

class ExportedByCATGMOperatorsInterfaces CATIPGMTopAdaptiveClone: public CATIPGMTopMultiResult
{
public:
  /**
   * Constructor
   */
  CATIPGMTopAdaptiveClone();

  /**
 *  Set stream version that will be used to identify the incompatibles Objects
 */
  virtual void SetTargetVersion(CATCGMStreamVersion &iTargetVersion) = 0;

  /**
 * Set Input Objects.
 */
  virtual void SetInputObjects(CATLISTP(CATICGMObject) &iInputObjects) = 0;

  /**
 * Get All Results.
 */
  virtual void GetAllResults(CATLISTP(CATICGMObject) &oObjectList) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopAdaptiveClone(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopAdaptiveClone *CATPGMCreateTopAdaptiveClone(
  CATGeoFactory *iFactory,
  CATTopData &iTopData);

#endif /* CATIPGMTopAdaptiveClone_h_ */
