#ifndef CATIPGMPolyTopOperator_h_
#define CATIPGMPolyTopOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2017

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATCGMOutput;
class CATCGMStream;
class CATExtCGMReplay;
class CATGMPolyOperTopExt;
class CATGeoFactory;
class CATString;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMPolyTopOperator;

class ExportedByCATGMOperatorsInterfaces CATIPGMPolyTopOperator: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMPolyTopOperator();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMPolyTopOperator(); // -> delete can't be called
};

#endif /* CATIPGMPolyTopOperator_h_ */
