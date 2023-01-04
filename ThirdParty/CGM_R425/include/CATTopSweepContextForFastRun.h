#ifndef CATTopSweepContextForFastRun_h
#define CATTopSweepContextForFastRun_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2014
// 
//==========================================================================
// Jun. 14  Creation                                   G5S
//==========================================================================
#include "CATGMOperatorsInterfaces.h"
#include "CATTopExtrudeContextForFastRun.h"


class ExportedByCATGMOperatorsInterfaces CATTopSweepContextForFastRun: public CATTopExtrudeContextForFastRun
{
public:
  /**
   * Constructor
   */
  CATTopSweepContextForFastRun();

protected:
  /**
   * Destructor
   */
  virtual ~CATTopSweepContextForFastRun(); // -> delete can't be called
};

#endif /* CATTopSweepContextForFastRun_h_ */
