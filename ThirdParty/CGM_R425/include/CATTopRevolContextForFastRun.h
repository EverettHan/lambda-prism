#ifndef CATTopRevolContextForFastRun_h
#define CATTopRevolContextForFastRun_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2014
// 
//==========================================================================
// Jun. 14  Creation                                   G5S
//==========================================================================
#include "CATGMOperatorsInterfaces.h"
#include "CATTopExtrudeContextForFastRun.h"


class ExportedByCATGMOperatorsInterfaces CATTopRevolContextForFastRun: public CATTopExtrudeContextForFastRun
{
public:
  /**
   * Constructor
   */
  CATTopRevolContextForFastRun();

protected:
  /**
   * Destructor
   */
  virtual ~CATTopRevolContextForFastRun(); // -> delete can't be called
};

#endif /* CATTopRevolContextForFastRun_h_ */
