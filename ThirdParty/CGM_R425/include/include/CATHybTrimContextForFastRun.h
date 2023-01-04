#ifndef CATHybTrimContextForFastRun_h
#define CATHybTrimContextForFastRun_h

#include "CATContextForFastRun.h"
#include "CATGMOperatorsInterfaces.h"

class ExportedByCATGMOperatorsInterfaces CATHybTrimContextForFastRun : public CATContextForFastRun
{
public:
  /**
   * Constructor
   */
  CATHybTrimContextForFastRun();

protected:
  /**
   * Destructor
   */
  virtual ~CATHybTrimContextForFastRun(); // -> delete can't be called
};

#endif
