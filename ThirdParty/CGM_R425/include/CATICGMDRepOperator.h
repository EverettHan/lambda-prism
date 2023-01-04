#ifndef CATICGMDRepOperator_h_
#define CATICGMDRepOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2013

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"

class CATCGMJournalList;
class CATDRepBody;
class CATDRepExtTopOperator;
class CATLiveBody;
class CATPlane;
class CATlsoDRepContext;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMDRepOperator;

class ExportedByCATGMOperatorsInterfaces CATICGMDRepOperator: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMDRepOperator();

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMDRepOperator(); // -> delete can't be called
};

#endif /* CATICGMDRepOperator_h_ */
