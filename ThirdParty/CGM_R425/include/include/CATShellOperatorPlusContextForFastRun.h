#ifndef CATShellOperatorPlusContextForFastRun_h
#define CATShellOperatorPlusContextForFastRun_h
/* -*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2009
// 
//==========================================================================
// Mar. 10  Creation                                   JJ3
//==========================================================================
#include "CATGMOperatorsInterfaces.h"
#include "CATContextForFastRun.h"


class ExportedByCATGMOperatorsInterfaces CATShellOperatorPlusContextForFastRun: public CATContextForFastRun
{
public:
  /**
   * Constructor
   */
  CATShellOperatorPlusContextForFastRun();

  //virtual CATBody * GetOldInput() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATShellOperatorPlusContextForFastRun(); // -> delete can't be called
};

#endif /* CATShellOperatorPlusContextForFastRun_h_ */
