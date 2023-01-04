#ifndef CATShellOperatorContextForFastRun_h
#define CATShellOperatorContextForFastRun_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2009
// 
//==========================================================================
// Mar. 10  Creation                                   JJ3
//==========================================================================
#include "CATGMOperatorsInterfaces.h"
#include "CATContextForFastRun.h"


class ExportedByCATGMOperatorsInterfaces CATShellOperatorContextForFastRun: public CATContextForFastRun
{
public:
  /**
   * Constructor
   */
  CATShellOperatorContextForFastRun();

protected:
  /**
   * Destructor
   */
  virtual ~CATShellOperatorContextForFastRun(); // -> delete can't be called
};

#endif /* CATShellOperatorContextForFastRun_h_ */
