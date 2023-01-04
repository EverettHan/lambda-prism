#ifndef CATICGMAdvancedOperator_h_
#define CATICGMAdvancedOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2018

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMDRepOperator.h"

class CATAdvancedExtTopOperator;
class CATCGMStream;
class CATICGMPersistentOperator;
class CATlsoContext;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMAdvancedOperator;

class ExportedByCATGMOperatorsInterfaces CATICGMAdvancedOperator: public CATICGMDRepOperator
{
public:
  /**
   * Constructor
   */
  CATICGMAdvancedOperator();

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMAdvancedOperator(); // -> delete can't be called
};

#endif /* CATICGMAdvancedOperator_h_ */
