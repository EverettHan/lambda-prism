#ifndef CATDynChamferContextForFastRun_h
#define CATDynChamferContextForFastRun_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2009
// 
//==========================================================================
// Jun. 09  Creation                                   JJ3
//==========================================================================
#include "CATGMOperatorsInterfaces.h"
#include "CATContextForFastRun.h"


class ExportedByCATGMOperatorsInterfaces CATDynChamferContextForFastRun: public CATContextForFastRun
{
public:
  /**
   * Constructor
   */
  CATDynChamferContextForFastRun();

protected:
  /**
   * Destructor
   */
  virtual ~CATDynChamferContextForFastRun(); // -> delete can't be called
};

#endif /* CATDynChamferContextForFastRun_h_ */
