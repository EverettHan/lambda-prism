#ifndef CATTopJoinContextForFastRun_h
#define CATTopJoinContextForFastRun_h

#include "CATContextForFastRun.h"
#include "CATGMOperatorsInterfaces.h"

class ExportedByCATGMOperatorsInterfaces CATTopJoinContextForFastRun : public CATContextForFastRun
{
public:
  /**
  * Constructor
  */
  CATTopJoinContextForFastRun();

protected:
  /**
  * Destructor
  */
  virtual ~CATTopJoinContextForFastRun(); // -> delete can't be called
};

#endif
