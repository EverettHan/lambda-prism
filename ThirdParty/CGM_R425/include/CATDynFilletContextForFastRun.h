#ifndef CATDynFilletContextForFastRun_h
#define CATDynFilletContextForFastRun_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2009
// 
//==========================================================================
// Jun. 09  Creation                                   JJ3
//==========================================================================
#include "CATGMOperatorsInterfaces.h"
#include "CATContextForFastRun.h"


class ExportedByCATGMOperatorsInterfaces CATDynFilletContextForFastRun: public CATContextForFastRun
{
public:
  /**
   * Constructor
   */
  CATDynFilletContextForFastRun();

protected:
  /**
   * Destructor
   */
  virtual ~CATDynFilletContextForFastRun(); // -> delete can't be called
};

#endif /* CATDynFilletContextForFastRun_h_ */
