#ifndef CATIPGMDRepOperator_h_
#define CATIPGMDRepOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2011

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMDRepOperator;

class ExportedByCATGMOperatorsInterfaces CATIPGMDRepOperator: public CATIPGMTopOperator
{
public:
  /**
   * @nodoc
   * Constructor
   */
  CATIPGMDRepOperator();

protected:
  /**
   * @nodoc
   * Destructor
   */
  virtual ~CATIPGMDRepOperator(); // -> delete can't be called
};

#endif /* CATIPGMDRepOperator_h_ */
