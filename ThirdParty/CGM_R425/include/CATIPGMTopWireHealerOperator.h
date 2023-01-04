#ifndef CATIPGMTopWireHealerOperator_h_
#define CATIPGMTopWireHealerOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMTopOperator.h"

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMTopWireHealerOperator;

class ExportedByCATGMModelInterfaces CATIPGMTopWireHealerOperator: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopWireHealerOperator();

  virtual int Run() = 0;

  virtual void DetectDeadEnd(CATBoolean iDeadEnd) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopWireHealerOperator(); // -> delete can't be called
};

#endif /* CATIPGMTopWireHealerOperator_h_ */
