#ifndef CATTopUntrimContextForFastRun_h
#define CATTopUntrimContextForFastRun_h

#include "CATContextForFastRun.h"
#include "CATGMOperatorsInterfaces.h"

class ExportedByCATGMOperatorsInterfaces CATTopUntrimContextForFastRun : public CATContextForFastRun
{
public:
  /**
   * Constructor
   */
  CATTopUntrimContextForFastRun();

protected:
  /**
   * Destructor
   */
  virtual ~CATTopUntrimContextForFastRun(); // -> delete can't be called
};

#endif
