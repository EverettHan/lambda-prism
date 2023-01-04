#ifndef CATICGMPersistentOperator_h_
#define CATICGMPersistentOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2013

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATIACGMLevel.h"

#ifdef CATIACGMR421CAA
#include "CATICGMAdvancedOperator.h"
#else
#include "CATICGMDRepOperator.h"
#endif

class CATCGMPad;
class CATCGMStream;
class CATPersistentBody;
class CATPersistentCellInfra;
class CATPersistentExtTopOperator;
class CATlsoPersistentContext;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMPersistentOperator;

#ifdef CATIACGMR421CAA
class ExportedByCATGMOperatorsInterfaces CATICGMPersistentOperator: public CATICGMAdvancedOperator
#else
class ExportedByCATGMOperatorsInterfaces CATICGMPersistentOperator: public CATICGMDRepOperator
#endif
{
public:
  /**
   * Constructor
   */
  CATICGMPersistentOperator();

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMPersistentOperator(); // -> delete can't be called
};

#endif /* CATICGMPersistentOperator_h_ */
