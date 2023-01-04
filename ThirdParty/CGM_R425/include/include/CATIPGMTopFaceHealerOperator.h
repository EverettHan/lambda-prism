#ifndef CATIPGMTopFaceHealerOperator_h_
#define CATIPGMTopFaceHealerOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMTopOperator.h"

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMTopFaceHealerOperator;

class ExportedByCATGMModelInterfaces CATIPGMTopFaceHealerOperator: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopFaceHealerOperator();

  virtual int Run() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopFaceHealerOperator(); // -> delete can't be called
};

#endif /* CATIPGMTopFaceHealerOperator_h_ */
