#ifndef CATTopPrismContextForFastRun_h
#define CATTopPrismContextForFastRun_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2010
// 
//==========================================================================
// 2010 WEEK 30 LAY Creation
//==========================================================================
#include "CATGMOperatorsInterfaces.h"
#include "CATTopExtrudeContextForFastRun.h"


class ExportedByCATGMOperatorsInterfaces CATTopPrismContextForFastRun: public CATTopExtrudeContextForFastRun
{
public:
  /**
   * Constructor
   */
  CATTopPrismContextForFastRun();

protected:
  /**
   * Destructor
   */
  virtual ~CATTopPrismContextForFastRun(); // -> delete can't be called
};

#endif /* CATTopPrismContextForFastRun_h_ */
