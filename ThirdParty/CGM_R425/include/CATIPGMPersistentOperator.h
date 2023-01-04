#ifndef CATIPGMPersistentOperator_h_
#define CATIPGMPersistentOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2009

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMAdvancedOperator.h"

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMPersistentOperator;

class ExportedByCATGMOperatorsInterfaces CATIPGMPersistentOperator: public CATIPGMAdvancedOperator
{
public:
  /**
   * @nodoc
   * Constructor
   */
  CATIPGMPersistentOperator();

protected:
  /**
   * @nodoc
   * Destructor
   */
  virtual ~CATIPGMPersistentOperator(); // -> delete can't be called
};

#endif /* CATIPGMPersistentOperator_h_ */
