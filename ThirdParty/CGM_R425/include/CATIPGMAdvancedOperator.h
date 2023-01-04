#ifndef CATIPGMAdvancedOperator_h_
#define CATIPGMAdvancedOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2018

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMDRepOperator.h"

class CATAdvancedExtTopOperator;
class CATCGMStream;
class CATIPGMPersistentOperator;
class CATlsoContext;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMAdvancedOperator;

class ExportedByCATGMOperatorsInterfaces CATIPGMAdvancedOperator: public CATIPGMDRepOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMAdvancedOperator();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMAdvancedOperator(); // -> delete can't be called
};

#endif /* CATIPGMAdvancedOperator_h_ */
