#ifndef CATIPGMTopCurveChecker_h_
#define CATIPGMTopCurveChecker_h_

// COPYRIGHT DASSAULT SYSTEMES 2014

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATExtTopCurveChecker;
class CATGeoFactory;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopCurveChecker;

class ExportedByCATGMOperatorsInterfaces CATIPGMTopCurveChecker: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopCurveChecker();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopCurveChecker(); // -> delete can't be called
};

/**
* External method that creates an instance of CATIPGMTopCurveChecker.
*   @param ipFactory
*     the pointer to the factory of the geometry.
*   @param ipTopdata
*     the pointer to the data defining the software configuration and the journal. 
*     If the journal inside the configuration is <tt>NULL</tt>, it is not filled.
*   @param iObjectsToCheck
*     objects to check.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopCurveChecker *CATPGMCreateTopCurveChecker(
  CATGeoFactory *ipFactory,
  CATTopData *ipTopdata,
  const ListPOfCATTopology& iObjectsToCheck);

#endif /* CATIPGMTopCurveChecker_h_ */
