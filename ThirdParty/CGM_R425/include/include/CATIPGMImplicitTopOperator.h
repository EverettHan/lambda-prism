#ifndef CATIPGMImplicitTopOperator_h_
#define CATIPGMImplicitTopOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2022

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATCGMOutput;
class CATCGMStream;
class CATExtCGMReplay;
class CATGeoFactory;
class CATImplicitOperTopExt;
class CATString;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMImplicitTopOperator;

class ExportedByCATGMOperatorsInterfaces CATIPGMImplicitTopOperator: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMImplicitTopOperator();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMImplicitTopOperator(); // -> delete can't be called
};

#endif /* CATIPGMImplicitTopOperator_h_ */
