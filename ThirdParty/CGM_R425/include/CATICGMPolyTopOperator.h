#ifndef CATICGMPolyTopOperator_h_
#define CATICGMPolyTopOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2020

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"

class CATBody;
class CATCGMOutput;
class CATCGMStream;
class CATExtCGMReplay;
class CATGMPolyOperTopExt;
class CATGeoFactory;
class CATString;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMPolyTopOperator;

class ExportedByCATGMOperatorsInterfaces CATICGMPolyTopOperator: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMPolyTopOperator();

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMPolyTopOperator(); // -> delete can't be called
};

#endif /* CATICGMPolyTopOperator_h_ */
